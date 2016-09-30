
#include "../include/RayTracer.h"

#include <stdio.h>
#include <dirent.h>

#include <fstream>
#include <sstream>
#include <algorithm>

#if defined(__linux__)

#include <sys/stat.h>
#include <sys/types.h>
#include <curses.h>

#define _getch getch

#elif defined(_WIN32)

#include <direct.h>
#include <conio.h>

#endif

using namespace ray;
using namespace glm;

static const char* commandname = "raytracer";

static std::map<std::string, std::string> preferences;

inline std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first) + 1);
}

inline std::string workingdir()
{
#if defined(__linux__)
    return std::string(getenv("HOME")) + "/.raytracer";
#elif defined(_WIN32)
    return std::string(getenv("APPDATA")) + "\\RayTracer";
#else
    return std::string();
#endif
}

inline std::string resolvepath(const std::string& folder, const std::string& filename)
{
#if defined(__linux__)
    return (folder + "/") + filename;
#elif defined(_WIN32)
    return (folder + "\\") + filename;
#else
    return std::string();
#endif
}

inline bool fileexists(const std::string& filename)
{
	if (FILE* file = fopen(filename.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	
	return false;
}

inline std::string resolvefile(const char* filename)
{
	return resolvepath(workingdir(), std::string(filename));
}

inline void ensurefolder(const std::string& folder)
{
	DIR* directory = opendir(folder.c_str());
	if (directory == 0)
	{
#if defined(__linux__)
		mkdir(folder.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
#elif defined(_WIN32)
		_mkdir(folder.c_str());
#endif
		directory = opendir(folder.c_str());
	}
	else
	{
		closedir(directory);
	}
}

void ensureprefs()
{
	std::string filename = resolvefile("default.ini");
	// printf("%s\n", filename.c_str());
	if (!fileexists(filename))
	{
		std::ofstream file(filename.c_str());
		if (file.is_open())
		{
			file << "\n";
			file << "# tracer photo\n";
			file << "photo_x = 240\n";
			file << "photo_y = 160\n";
		}
		else
		{
			printf("Failed to open to write: %s\n", filename.c_str());
		}
		
		file.close();
	}
}

inline int pref_i(const std::string& key)
{
	return atoi(preferences[key].c_str());
}
inline double pref_f(const std::string& key)
{
	return atof(preferences[key].c_str());
}
inline bool pref_b(const std::string& key)
{
	std::string value = preferences[key];
	std::transform(value.begin(), value.end(), value.begin(), tolower);
	return value == "true";
}

void parse_ini(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (!line.empty() && line[0] != '#')
			{
				size_t seperator = line.find_first_of('=');
				std::string key = trim(line.substr(0, seperator));
				std::string value = trim(line.substr(seperator + 1));
				printf("  %s = %s\n", key.c_str(), value.c_str());
				preferences[key] = value;
			}
		}
	}
	else
	{
		printf("Failed to open to read: %s\n", filename.c_str());
	}
	
	file.close();
}

void scan()
{
    std::string env = workingdir();
    DIR* directory = opendir(env.c_str());
    if (directory != 0)
    {
		// printf("Scanning working directory : %s\n", env.c_str());
		dirent* read = 0;
		while ((read = readdir(directory)) != 0)
		{
			std::string filename(read->d_name);
			if (filename != "." && filename != "..")
			{
				std::string filetype = filename.substr(filename.find_last_of(".") + 1);
				filename = resolvepath(env, filename);
				// printf("Found file : %s\n", filename.c_str());
				if (filetype == "ini") { parse_ini(filename); }
			}
		}
    }
    
    closedir(directory);
}

inline void cleanup()
{
	// _getch();
	// shape_release();
	FreeImage_DeInitialise();
}

inline void printmissing()
{
	printf("%s: missing file operand\n", commandname);
	printf("Usage: %s [OPTION]... [TARGET]...\n\n", commandname);
	printf("Try '%s --help' for more information.\n", commandname);
}

inline void printhelp()
{
	printf("Usage: %s [OPTION]... [TARGET]...\n\n", commandname);
}

int main(int argc, char** argv)
{
	ensurefolder(workingdir());
	ensureprefs();
	
	FreeImage_Initialise();
	// shape_init();
	
	atexit(cleanup);
    // scan();
    
    std::string scenepath;
    std::list<char> options;
    if (argc == 1)
    {
    	printmissing();
    	return 2;
    }
	else if (argc == 2)
	{
		std::string arg = argv[1];
		if (!arg.empty() && arg[0] == '-')
		{
			if (arg == "--help")
			{
				printhelp();
				return 0;
			}
			else
			{
				printmissing();
				return 2;
			}
		}
		
		scenepath = arg;
	}
	else if (argc == 3)
	{
		std::string arg = argv[1];
		if (!arg.empty() && arg[0] == '-')
		{
			arg = arg.substr(1);
			for (std::string::iterator i = arg.begin(); i != arg.end(); i++)
			{
				options.push_back(*i);
			}
		}
		
		scenepath = argv[2];
	}
    else
    {
    	printf("Invalid arguments\n");
    	return 2;
    }
    
    scene_t s0;
    read_scene(scenepath.c_str(), s0);
    
    // std::ifstream file(resolvefile("demo-scene.json").c_str(), std::ios::binary | std::ios::ate);
    // std::streamsize size = file.tellg();
    // file.seekg(0, std::ios::beg);
    // char* buffer = (char*)malloc(size);
    // if (file.read(buffer, size))
    // {
    // 	printf("%s\n", buffer);
    	
    // 	rapidjson::Document json;
    // 	json.Parse(buffer);
    // 	rapidjson::Value& camera = json["camera"];
    // 	printf("  %s\n", camera.IsObject() ? "true" : "false");
    // 	// rapidjson::Value& test = json["test"];
    // 	// printf("  %s\n", test.IsNull() ? "true" : "false");
    // 	printf("  %s\n", json.HasMember("camera") ? "true" : "false");
    // 	printf("  %s\n", json.HasMember("lights") ? "true" : "false");
    // 	printf("  %s\n", json.HasMember("stack") ? "true" : "false");
    // 	printf("  %s\n", json.HasMember("test") ? "true" : "false");
    // }
    
    // free(buffer);
    
	// photo_t photo(pref_i("photo_x"), pref_i("photo_y"));
	
	// FIBITMAP* uvgrid01 = FreeImage_Load(FIF_JPEG, resolvefile("uvgrid01.jpg").c_str(), JPEG_DEFAULT);
	// FIBITMAP* uvgrid02 = FreeImage_Load(FIF_PNG, resolvefile("uvgrid02.png").c_str(), PNG_DEFAULT);
	// lambert_t lambert0;
	// lambert0.attach(texturefilter_t(uvgrid01, SAMPLETYPE_LINEAR), TEXTURETYPE_COLOR);
	// blinn_t blinn0(48.0f);
	// blinn0.attach(texturefilter_t(uvgrid02, SAMPLETYPE_LINEAR), TEXTURETYPE_COLOR);
	
	// tracestack_t stack;
	
	// tracesphere_t sphere0(vec4(0.0f, 0.0f, 0.0f, 1.0f), 2.4f);
	// sphere0.attach(&blinn0);
	// stack._traceables.push_back(&sphere0);
	
	// traceaxiscube_t cube0(vec4(3.0f, 0.0f, 0.0f, 1.0f), 4.0f, 4.0f, 4.0f);
	// cube0.attach(&lambert0);
	// stack._traceables.push_back(&cube0);
	
	// stack._lights.push_back(new pointlight_t(vec4(0.4f, 1.0f, -3.0f, 1.0f), vec4(1.0f), 1.0f));
	
	// camera_t camera(shape_transformation(vec3(0.0f, 0.0f, -4.0f), vec3(1.0f), vec3(0.0f)), vec2(4.0f, 3.0f), 2.4f);
	
	// photo.trace(stack, camera);
	// FIBITMAP* bitmap = photo.rasterize();
	// FreeImage_Save(FIF_PNG, bitmap, resolvefile("test.png").c_str(), 0);
    
    // photo.release();
    
    return 0;
}