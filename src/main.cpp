
#include "../include/RayTracer.h"

#include <stdio.h>
#include <dirent.h>

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
    return (folder + "//") + filename;
#else
    return std::string();
#endif
}

void parse_ini(const std::string& filename)
{
    
}

void scan()
{
    std::string env = workingdir();
    DIR* directory = opendir(env.c_str());
    if (directory == 0)
    {
#if defined(__linux__)
        mkdir(env.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
#elif defined(_WIN32)
		_mkdir(env.c_str());
#endif
        directory = opendir(env.c_str());
    }
    
    printf("scanning working directory : %s\n", env.c_str());
    dirent* read = 0;
    while ((read = readdir(directory)) != 0)
    {
        std::string filename(read->d_name);
        if (filename != "." && filename != "..")
        {
            std::string filetype = filename.substr(filename.find_last_of(".") + 1);
            printf(" found: %s\n", filename.c_str());
            if (filetype == "ini") { parse_ini(filename); }
        }
    }
    
    closedir(directory);
}

    
int main(int argc, char** argv)
{
	FreeImage_Initialise();
	shape_init();
    printf("started\n");
    scan();
    
    photo_t photo(240, 160);
    tracestack_t stack;
    stack._traceables.push_back(new tracesphere_t(vec4(0.0f, 0.0f, 0.0f, 1.0f), 4.0f));
    stack._lights.push_back(new pointlight_t(vec4(0.4f, 4.0f, 0.0f, 1.0f), vec4(1.0f), 1.0f));
    camera_t camera(shape_transformation(vec3(0.0f, 0.0f, -4.0f), vec3(1.0f), vec3(0.0f)), vec2(4.0f, 3.0f), 1.6f);
    
    photo.trace(stack, camera);
    FIBITMAP* bitmap = photo.rasterize();
    FreeImage_Save(FIF_PNG, bitmap, "test.png", 0);
    
    photo.release();
    
	_getch();
	shape_release();
	FreeImage_DeInitialise();
    return 0;
}