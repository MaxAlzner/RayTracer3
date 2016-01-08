
#include "../include/RayTracer.h"

namespace ray
{

	const traceable_t* tracestack_t::nearest(const ray_t& ray, rayhit_t* hit) const
	{
		float check = FLT_MAX;
		const traceable_t* nearest = 0;
		for (std::list<traceable_t*>::const_iterator i = this->_traceables.begin(); i != this->_traceables.end(); i++)
		{
			rayhit_t _hit;
			const traceable_t* obj = *i;
			if (obj != 0 && obj->hitbyray(ray, &_hit))
			{
				if (_hit._distance < check)
				{
					nearest = obj;
					check = _hit._distance;
					if (hit != 0)
					{
						*hit = _hit;
					}
				}
			}
		}

		return nearest;
	}
	const traceable_t* tracestack_t::farthest(const ray_t& ray, rayhit_t* hit) const
	{
		float check = 0.0f;
		const traceable_t* farthest = 0;
		for (std::list<traceable_t*>::const_reverse_iterator i = this->_traceables.rbegin(); i != this->_traceables.rend(); i++)
		{
			rayhit_t _hit;
			const traceable_t* obj = *i;
			if (obj != 0 && obj->hitbyray(ray, &_hit))
			{
				if (_hit._distance >= check)
				{
					farthest = obj;
					check = _hit._distance;
					if (hit != 0)
					{
						*hit = _hit;
					}
				}
			}
		}

		return farthest;
	}

}