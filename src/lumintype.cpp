
#include "../include/RayTracer.h"

namespace ray
{
    
    inline glm::vec4 lumination_t::flatten() const
    {
        return this->_diffuse + ((glm::vec4(1.0f) - this->_diffuse) * this->_specular);
    }
	
	inline lumination_t lumination_t::operator+() const
	{
	    return lumination_t(+this->_diffuse, +this->_specular);
	}
	inline lumination_t lumination_t::operator-() const
	{
	    return lumination_t(-this->_diffuse, -this->_specular);
	}
	inline lumination_t& lumination_t::operator+=(const lumination_t& other)
	{
	    this->_diffuse += other._diffuse;
	    this->_specular += other._specular;
	    return *this;
	}
	inline lumination_t& lumination_t::operator+=(const glm::vec4& v)
	{
	    this->_diffuse += v;
	    this->_specular += v;
	    return *this;
	}
	inline lumination_t& lumination_t::operator+=(const float v)
	{
	    this->_diffuse += v;
	    this->_specular += v;
	    return *this;
	}
	inline lumination_t& lumination_t::operator-=(const lumination_t& other)
	{
	    this->_diffuse -= other._diffuse;
	    this->_specular -= other._specular;
	    return *this;
	}
	inline lumination_t& lumination_t::operator-=(const glm::vec4& v)
	{
	    this->_diffuse -= v;
	    this->_specular -= v;
	    return *this;
	}
	inline lumination_t& lumination_t::operator-=(const float v)
	{
	    this->_diffuse -= v;
	    this->_specular -= v;
	    return *this;
	}
	inline lumination_t& lumination_t::operator*=(const lumination_t& other)
	{
	    this->_diffuse *= other._diffuse;
	    this->_specular *= other._specular;
	    return *this;
	}
	inline lumination_t& lumination_t::operator*=(const glm::vec4& v)
	{
	    this->_diffuse *= v;
	    this->_specular *= v;
	    return *this;
	}
	inline lumination_t& lumination_t::operator*=(const float v)
	{
	    this->_diffuse *= v;
	    this->_specular *= v;
	    return *this;
	}
	inline lumination_t& lumination_t::operator/=(const lumination_t& other)
	{
	    this->_diffuse /= other._diffuse;
	    this->_specular /= other._specular;
	    return *this;
	}
	inline lumination_t& lumination_t::operator/=(const glm::vec4& v)
	{
	    this->_diffuse /= v;
	    this->_specular /= v;
	    return *this;
	}
	inline lumination_t& lumination_t::operator/=(const float v)
	{
	    this->_diffuse /= v;
	    this->_specular /= v;
	    return *this;
	}
	
	inline lumination_t operator+(const lumination_t& l0, const lumination_t& l1)
	{
	    return lumination_t(l0._diffuse + l1._diffuse, l0._specular + l1._specular);
	}
	inline lumination_t operator+(const lumination_t& l, const glm::vec4& v)
	{
	    return lumination_t(l._diffuse + v, l._specular + v);
	}
	inline lumination_t operator+(const glm::vec4& v, const lumination_t& l)
	{
	    return lumination_t(v + l._diffuse, v + l._specular);
	}
	inline lumination_t operator+(const lumination_t& l, const float v)
	{
	    return lumination_t(l._diffuse + v, l._specular + v);
	}
	inline lumination_t operator+(const float v, const lumination_t& l)
	{
	    return lumination_t(v + l._diffuse, v + l._specular);
	}
	
	inline lumination_t operator-(const lumination_t& l0, const lumination_t& l1)
	{
	    return lumination_t(l0._diffuse - l1._diffuse, l0._specular - l1._specular);
	}
	inline lumination_t operator-(const lumination_t& l, const glm::vec4& v)
	{
	    return lumination_t(l._diffuse - v, l._specular - v);
	}
	inline lumination_t operator-(const glm::vec4& v, const lumination_t& l)
	{
	    return lumination_t(v - l._diffuse, v - l._specular);
	}
	inline lumination_t operator-(const lumination_t& l, const float v)
	{
	    return lumination_t(l._diffuse - v, l._specular - v);
	}
	inline lumination_t operator-(const float v, const lumination_t& l)
	{
	    return lumination_t(v - l._diffuse, v - l._specular);
	}
	
	inline lumination_t operator*(const lumination_t& l0, const lumination_t& l1)
	{
	    return lumination_t(l0._diffuse * l1._diffuse, l0._specular * l1._specular);
	}
	inline lumination_t operator*(const lumination_t& l, const glm::vec4& v)
	{
	    return lumination_t(l._diffuse * v, l._specular * v);
	}
	inline lumination_t operator*(const glm::vec4& v, const lumination_t& l)
	{
	    return lumination_t(v * l._diffuse, v * l._specular);
	}
	inline lumination_t operator*(const lumination_t& l, const float v)
	{
	    return lumination_t(l._diffuse * v, l._specular * v);
	}
	inline lumination_t operator*(const float v, const lumination_t& l)
	{
	    return lumination_t(v * l._diffuse, v * l._specular);
	}
	
	inline lumination_t operator/(const lumination_t& l0, const lumination_t& l1)
	{
	    return lumination_t(l0._diffuse / l1._diffuse, l0._specular / l1._specular);
	}
	inline lumination_t operator/(const lumination_t& l, const glm::vec4& v)
	{
	    return lumination_t(l._diffuse / v, l._specular / v);
	}
	inline lumination_t operator/(const glm::vec4& v, const lumination_t& l)
	{
	    return lumination_t(v / l._diffuse, v / l._specular);
	}
	inline lumination_t operator/(const lumination_t& l, const float v)
	{
	    return lumination_t(l._diffuse / v, l._specular / v);
	}
	inline lumination_t operator/(const float v, const lumination_t& l)
	{
	    return lumination_t(v / l._diffuse, v / l._specular);
	}
	
}