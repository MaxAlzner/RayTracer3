
#include "../include/RayTracer.h"

namespace ray
{
	
	ray_t camera_t::cast(const glm::vec2& coord) const
	{
		return this->cast(coord.x, coord.y);
	}
	ray_t camera_t::cast(const float u, const float v) const
	{
		glm::vec3 origin = this->_p0 + (this->_u * u) + (this->_v * v);
		return ray_t(origin, glm::normalize(origin - this->_focal));
	}
	
}