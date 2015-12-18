
#include "../include/RayTracer.h"

namespace ray
{
	
	inline ray_t ray_t::operator+() const
	{
		return ray_t(+this->_origin, +this->_forward);
	}
	inline ray_t ray_t::operator-() const
	{
		return ray_t(-this->_origin, -this->_forward);
	}
	inline ray_t& ray_t::operator+=(const ray_t& other)
	{
		this->_origin += other._origin;
		this->_forward = glm::normalize(this->_forward + other._forward);
		return *this;
	}
	inline ray_t& ray_t::operator+=(const glm::vec4& v)
	{
		this->_origin += v;
		return *this;
	}
	inline ray_t& ray_t::operator+=(const glm::vec3& v)
	{
		this->_origin += glm::vec4(v, 0.0f);
		return *this;
	}
	inline ray_t& ray_t::operator+=(const float v)
	{
		this->_origin += v;
		return *this;
	}
	inline ray_t& ray_t::operator-=(const ray_t& other)
	{
		this->_origin -= other._origin;
		this->_forward = glm::normalize(this->_forward - other._forward);
		return *this;
	}
	inline ray_t& ray_t::operator-=(const glm::vec4& v)
	{
		this->_origin -= v;
		return *this;
	}
	inline ray_t& ray_t::operator-=(const glm::vec3& v)
	{
		this->_origin -= glm::vec4(v, 1.0f);
		return *this;
	}
	inline ray_t& ray_t::operator-=(const float v)
	{
		this->_origin -= v;
		return *this;
	}
	inline ray_t& ray_t::operator*=(const ray_t& other)
	{
		this->_origin *= other._origin;
		this->_forward = glm::normalize(this->_forward * other._forward);
		return *this;
	}
	inline ray_t& ray_t::operator*=(const glm::vec4& v)
	{
		this->_origin *= v;
		this->_forward = glm::normalize(this->_forward * glm::vec3(v));
		return *this;
	}
	inline ray_t& ray_t::operator*=(const glm::vec3& v)
	{
		this->_origin *= glm::vec4(v, 1.0f);
		this->_forward = glm::normalize(this->_forward * v);
		return *this;
	}
	inline ray_t& ray_t::operator*=(const float v)
	{
		this->_origin *= v;
		this->_forward = glm::normalize(this->_forward * v);
		return *this;
	}
	inline ray_t& ray_t::operator/=(const ray_t& other)
	{
		this->_origin /= other._origin;
		this->_forward = glm::normalize(this->_forward / other._forward);
		return *this;
	}
	inline ray_t& ray_t::operator/=(const glm::vec4& v)
	{
		this->_origin /= v;
		this->_forward = glm::normalize(this->_forward / glm::vec3(v));
		return *this;
	}
	inline ray_t& ray_t::operator/=(const glm::vec3& v)
	{
		this->_origin /= glm::vec4(v, 1.0f);
		this->_forward = glm::normalize(this->_forward / v);
		return *this;
	}
	inline ray_t& ray_t::operator/=(const float v)
	{
		this->_origin /= v;
		this->_forward = glm::normalize(this->_forward / v);
		return *this;
	}
	
	inline ray_t operator+(const ray_t& r0, const ray_t& r1)
	{
		return ray_t(r0._origin + r1._origin, glm::normalize(r0._forward + r1._forward));
	}
	inline ray_t operator+(const ray_t& r, const glm::vec4& v)
	{
		return ray_t(r._origin + v, r._forward);
	}
	inline ray_t operator+(const glm::vec4& v, const ray_t& r)
	{
		return ray_t(v + r._origin, r._forward);
	}
	inline ray_t operator+(const ray_t& r, const glm::vec3& v)
	{
		return ray_t(r._origin + glm::vec4(v, 0.0f), r._forward);
	}
	inline ray_t operator+(const glm::vec3& v, const ray_t& r)
	{
		return ray_t(glm::vec4(v, 0.0f) + r._origin, r._forward);
	}
	inline ray_t operator+(const ray_t& r, const float v)
	{
		return ray_t(r._origin + v, r._forward);
	}
	inline ray_t operator+(const float v, const ray_t& r)
	{
		return ray_t(v + r._origin, r._forward);
	}
	
	inline ray_t operator-(const ray_t& r0, const ray_t& r1)
	{
		return ray_t(r0._origin - r1._origin, glm::normalize(r0._forward - r1._forward));
	}
	inline ray_t operator-(const ray_t& r, const glm::vec4& v)
	{
		return ray_t(r._origin - v, r._forward);
	}
	inline ray_t operator-(const glm::vec4& v, const ray_t& r)
	{
		return ray_t(v - r._origin, r._forward);
	}
	inline ray_t operator-(const ray_t& r, const glm::vec3& v)
	{
		return ray_t(r._origin - glm::vec4(v, 0.0f), r._forward);
	}
	inline ray_t operator-(const glm::vec3& v, const ray_t& r)
	{
		return ray_t(glm::vec4(v, 0.0f) - r._origin, r._forward);
	}
	inline ray_t operator-(const ray_t& r, const float v)
	{
		return ray_t(r._origin - v, r._forward);
	}
	inline ray_t operator-(const float v, const ray_t& r)
	{
		return ray_t(v - r._origin, r._forward);
	}
	
	inline ray_t operator*(const ray_t& r0, const ray_t& r1)
	{
		return ray_t(r0._origin * r1._origin, glm::normalize(r0._forward * r1._forward));
	}
	inline ray_t operator*(const ray_t& r, const glm::vec4& v)
	{
		return ray_t(r._origin * v, glm::normalize(r._forward * glm::vec3(v)));
	}
	inline ray_t operator*(const glm::vec4& v, const ray_t& r)
	{
		return ray_t(v * r._origin, glm::normalize(glm::vec3(v) * r._forward));
	}
	inline ray_t operator*(const ray_t& r, const glm::vec3& v)
	{
		return ray_t(r._origin * glm::vec4(v, 1.0f), glm::normalize(r._forward * v));
	}
	inline ray_t operator*(const glm::vec3& v, const ray_t& r)
	{
		return ray_t(glm::vec4(v, 1.0f) * r._origin, glm::normalize(v * r._forward));
	}
	inline ray_t operator*(const ray_t& r, const float v)
	{
		return ray_t(r._origin * v, glm::normalize(r._forward * v));
	}
	inline ray_t operator*(const float v, const ray_t& r)
	{
		return ray_t(v * r._origin, glm::normalize(v * r._forward));
	}
	
	inline ray_t operator/(const ray_t& r0, const ray_t& r1)
	{
		return ray_t(r0._origin / r1._origin, glm::normalize(r0._forward / r1._forward));
	}
	inline ray_t operator/(const ray_t& r, const glm::vec4& v)
	{
		return ray_t(r._origin / v, glm::normalize(r._forward / glm::vec3(v)));
	}
	inline ray_t operator/(const glm::vec4& v, const ray_t& r)
	{
		return ray_t(v / r._origin, glm::normalize(glm::vec3(v) / r._forward));
	}
	inline ray_t operator/(const ray_t& r, const glm::vec3& v)
	{
		return ray_t(r._origin / glm::vec4(v, 1.0f), glm::normalize(r._forward / v));
	}
	inline ray_t operator/(const glm::vec3& v, const ray_t& r)
	{
		return ray_t(glm::vec4(v, 1.0f) / r._origin, glm::normalize(v / r._forward));
	}
	inline ray_t operator/(const ray_t& r, const float v)
	{
		return ray_t(r._origin / v, glm::normalize(r._forward / v));
	}
	inline ray_t operator/(const float v, const ray_t& r)
	{
		return ray_t(v / r._origin, glm::normalize(v / r._forward));
	}
	
}