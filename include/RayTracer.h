#pragma once

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include <direct.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <FreeImage.h>

#if defined(__linux__)


#elif defined(_WIN32)

#include <Windows.h>

#endif

namespace ray
{

	struct ray_t
	{
		inline ray_t() :
			_origin(0.0f, 0.0f, 0.0f, 1.0f),
			_forward(0.0f, 0.0f, 1.0f) {}
		inline ray_t(const glm::vec3& origin, const glm::vec3& forward) :
			_origin(origin, 1.0f),
			_forward(forward) {}
		inline ray_t(const glm::vec4& origin, const glm::vec3& forward) :
			_origin(origin),
			_forward(forward) {}
		inline ~ray_t() {}

		inline ray_t operator+=(const ray_t& other);
		inline ray_t operator+=(const glm::vec4& v);
		inline ray_t operator+=(const glm::vec3& v);
		inline ray_t operator+=(const float v);
		inline ray_t operator-=(const ray_t& other);
		inline ray_t operator-=(const glm::vec4& v);
		inline ray_t operator-=(const glm::vec3& v);
		inline ray_t operator-=(const float v);
		inline ray_t operator*=(const ray_t& other);
		inline ray_t operator*=(const glm::vec4& v);
		inline ray_t operator*=(const glm::vec3& v);
		inline ray_t operator*=(const float v);
		inline ray_t operator/=(const ray_t& other);
		inline ray_t operator/=(const glm::vec4& v);
		inline ray_t operator/=(const glm::vec3& v);
		inline ray_t operator/=(const float v);

		glm::vec4 _origin;
		glm::vec3 _forward;

	};

	static inline ray_t operator+(const ray_t& r0, const ray_t& r1);
	static inline ray_t operator+(const ray_t& r, const glm::vec4& v);
	static inline ray_t operator+(const glm::vec4& v, const ray_t& r);
	static inline ray_t operator+(const ray_t& r, const glm::vec3& v);
	static inline ray_t operator+(const glm::vec3& v, const ray_t& r);
	static inline ray_t operator+(const ray_t& r, const float v);
	static inline ray_t operator+(const float v, const ray_t& r);

	static inline ray_t operator-(const ray_t& r0, const ray_t& r1);
	static inline ray_t operator-(const ray_t& r, const glm::vec4& v);
	static inline ray_t operator-(const glm::vec4& v, const ray_t& r);
	static inline ray_t operator-(const ray_t& r, const glm::vec3& v);
	static inline ray_t operator-(const glm::vec3& v, const ray_t& r);
	static inline ray_t operator-(const ray_t& r, const float v);
	static inline ray_t operator-(const float v, const ray_t& r);

	static inline ray_t operator*(const ray_t& r0, const ray_t& r1);
	static inline ray_t operator*(const ray_t& r, const glm::vec4& v);
	static inline ray_t operator*(const glm::vec4& v, const ray_t& r);
	static inline ray_t operator*(const ray_t& r, const glm::vec3& v);
	static inline ray_t operator*(const glm::vec3& v, const ray_t& r);
	static inline ray_t operator*(const ray_t& r, const float v);
	static inline ray_t operator*(const float v, const ray_t& r);

	static inline ray_t operator/(const ray_t& r0, const ray_t& r1);
	static inline ray_t operator/(const ray_t& r, const glm::vec4& v);
	static inline ray_t operator/(const glm::vec4& v, const ray_t& r);
	static inline ray_t operator/(const ray_t& r, const glm::vec3& v);
	static inline ray_t operator/(const glm::vec3& v, const ray_t& r);
	static inline ray_t operator/(const ray_t& r, const float v);
	static inline ray_t operator/(const float v, const ray_t& r);

}