
#include "../include/RayTracer.h"

namespace ray
{
	
	lumination_t pointlight_t::luminance(const fragment_t& fragment)
	{
		if (fragment._material == 0)
		{
			return lumination_t(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f));
		}
		
		glm::vec3 l = glm::vec3(this->_position - fragment._position);
		// float d = glm::length(l);
		l = normalize(l);
		// float atten = std::min(this->_intensity / d, 1.0f);
		return fragment._material->shade(lighting_t(l, /*this->occlusion(fragment) * atten*/1.0f), fragment);
	}
	
	float pointlight_t::occlusion(const fragment_t& fragment)
	{
		// if (fragment.material != 0)
		// {
		// 	glm::vec3 toLight = this->object->transform->position - fragment.position;
		// 	ray_t to(fragment.position, glm::normalize(toLight), glm::length(toLight));
		// 	Fragment occluded = this->object->stack->trace(to, 0);
		// 	return occluded.material != 0 && occluded.material != fragment.material ? 0.0f : 1.0f;
		// }
		
		return 0.0f;
	}
	
}