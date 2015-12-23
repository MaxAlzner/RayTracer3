#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define GLM_FORCE_RADIANS

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

#if 0
#if !defined(min)
#define min(x, y) (x < y ? x : y)
#endif
#if !defined(max)
#define max(x, y) (x > y ? x : y)
#endif
#endif

namespace ray
{

	typedef FIBITMAP IMAGETYPE;

}

#include "RayTracer_typedef.h"
#include "RayTracer_shape.h"
#include "RayTracer_material.h"
#include "RayTracer_light.h"
#include "RayTracer_trace.h"