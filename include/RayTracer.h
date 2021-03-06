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

#define NOMINMAX
#include <Windows.h>

#include <algorithm>

#endif

#include <string>
#include <vector>
#include <list>
#include <map>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <rapidxml.hpp>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#if 0
#include <shape.h>
#endif

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
	
	struct ray_t;
	struct lumination_t;
	struct rayhit_t;
	struct fragment_t;
	struct lighting_t;
	
	struct traceable_t;
	
	class texturefilter_t;
	class material_t;
	class light_t;
	
	class camera_t;
	class tracestack_t;
	class tracepath_t;
	class emitter_t;
	
	struct scene_t;
	
}

#include "RayTracer_typedef.h"
#include "RayTracer_material.h"
#include "RayTracer_shape.h"
#include "RayTracer_light.h"
#include "RayTracer_trace.h"
#include "RayTracer_scene.h"