
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
	printf("%s\n", filename.c_str());
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
				printf("  pref: %s = %s\n", key.c_str(), value.c_str());
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
		printf("Scanning working directory : %s\n", env.c_str());
		dirent* read = 0;
		while ((read = readdir(directory)) != 0)
		{
			std::string filename(read->d_name);
			if (filename != "." && filename != "..")
			{
				std::string filetype = filename.substr(filename.find_last_of(".") + 1);
				filename = resolvepath(env, filename);
				printf(" found: %s\n", filename.c_str());
				if (filetype == "ini") { parse_ini(filename); }
			}
		}
    }
    
    closedir(directory);
}

int main(int argc, char** argv)
{
	ensurefolder(workingdir());
	ensureprefs();

	FreeImage_Initialise();
	shape_init();

    scan();
    
    photo_t photo(pref_i("photo_x"), pref_i("photo_y"));
    tracestack_t stack;
    stack._traceables.push_back(new tracesphere_t(vec4(0.0f, 0.0f, 0.0f, 1.0f), 4.0f));
    stack._lights.push_back(new pointlight_t(vec4(0.4f, 4.0f, 0.0f, 1.0f), vec4(1.0f), 1.0f));
    camera_t camera(shape_transformation(vec3(0.0f, 0.0f, -4.0f), vec3(1.0f), vec3(0.0f)), vec2(4.0f, 3.0f), 1.6f);
    
    photo.trace(stack, camera);
    FIBITMAP* bitmap = photo.rasterize();
    FreeImage_Save(FIF_PNG, bitmap, resolvefile("test.png").c_str(), 0);
    
    photo.release();
    
	_getch();
	shape_release();
	FreeImage_DeInitialise();
    return 0;
}