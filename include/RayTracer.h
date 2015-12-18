#pragma once

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <inttypes.h>
#include <float.h>

#include <string>
#include <vector>
#include <list>
#include <map>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <FreeImage.h>

#if defined(__linux__)


#elif defined(_WIN32)

#include <Windows.h>

#endif

#include "RayTracer_typedef.h"