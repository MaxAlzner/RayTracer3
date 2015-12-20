
#include "../include/RayTracer.h"

#include <stdio.h>
#include <dirent.h>

#if defined(__linux__)

#include <sys/stat.h>
#include <sys/types.h>

#define _getch getch

#elif defined(_WIN32)

#include <direct.h>
#include <conio.h>

#endif

static std::map<std::string, std::string> preferences;

std::string workingdir()
{
#if defined(__linux__)
    return std::string(getenv("HOME")) + "/.raytracer";
#elif defined(_WIN32)
    return std::string(getenv("APPDATA")) + "\\RayTracer";
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
    
	_getch();
	shape_release();
	FreeImage_DeInitialise();
    return 0;
}