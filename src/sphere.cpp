
#include "../include/RayTracer.h"

namespace ray
{
	using namespace glm;

	bool tracesphere_t::hitbyray(const ray_t& ray, rayhit_t* hit) const
	{
		vec3 p = vec3(ray._origin - this->_center);
		float a = dot(ray._forward, ray._forward);
		float b = dot(vec3((p * 2.0f)), ray._forward);
		float c = dot(p, p) - (this->_radius * this->_radius);
		float d = (b * b) - (4.0f * a * c);
		if (d >= 0.0f)
		{
			float e = sqrt(d);
			float t0 = (-b - e) / (2.0f * a);
			float t1 = (-b + e) / (2.0f * a);
			if (t0 >= 0.0f && t1 >= 0.0f)
			{
				float t = t0 < t1 ? t0 : t1;

				//if (t <= ray.length)
				//{
					vec4 intersection = ray._origin + vec4(ray._forward * t, 0.0f);
					vec3 normal = glm::normalize(vec3(intersection) - vec3(this->_center));
					// vec3 tangent = cross(normal, vec3(0.0f, 1.0f, 0.0f));
					// vec3 binormal = cross(normal, tangent);
					if (dot(normal, ray._forward) < 0.0f)
					{
						if (hit != 0)
						{
							*hit = rayhit_t(
								ray,
								t,
								intersection/*,
								clamp(vec2((normal.x + 1.0f) / 2.0f, (normal.y + 1.0f) / 2.0f), vec2(0.0f), vec2(1.0f)),
								normal,
								tangent,
								binormal*/);
						}

						return true;
					}
				//}
			}
		}

		return false;
	}
	
	fragment_t tracesphere_t::fragmentate(const rayhit_t& hit) const
	{
		vec3 normal = glm::normalize(vec3(hit._intersection) - vec3(this->_center));
		vec3 tangent = cross(normal, vec3(0.0f, 1.0f, 0.0f));
		vec2 uv = clamp(vec2((normal.x + 1.0f) / 2.0f, (normal.y + 1.0f) / 2.0f), vec2(0.0f), vec2(1.0f));
		return fragment_t(
			this->_material,
			hit._intersection,
			uv,
			normal,
			tangent,
			cross(normal, tangent),
			-hit._ray._forward,
			this->_material != 0 ? this->_material->transparency(uv) : 0.0f,
			this->_material != 0 ? this->_material->reflectivity(uv) : 0.0f,
			this->_material != 0 ? this->_material->color(uv) : vec4(1.0f, 0.0f, 1.0f, 1.0f),
			this->_material != 0 ? this->_material->specular(uv) : vec4(0.0f),
			this->_material != 0 ? this->_material->emissive(uv) : vec4(0.0f));
	}
	
}