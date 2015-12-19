#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <inttypes.h>
#include <float.h>

#if defined(__linux__)


#elif defined(_WIN32)

#include <Windows.h>

#endif

#include <string>
#include <vector>
#include <list>
#include <map>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <shape.h>

#include <FreeImage.h>

#include "RayTracer_typedef.h"
#include "RayTracer_shape.h"