
#include "../include/RayTracer.h"

namespace ray
{

	void tracepath_t::clear()
	{
		if (this->_reflection != 0)
		{
			delete this->_reflection;
			this->_reflection = 0;
		}
		
		if (this->_passthrough != 0)
		{
			delete this->_passthrough;
			this->_passthrough = 0;
		}
	}
	
	lumination_t tracepath_t::albedo() const
	{
		lumination_t albedo(0.0f, 0.0f);
		if (this->_stack != 0)
		{
			for (std::list<light_t*>::const_iterator i = this->_stack->_lights.begin(); i != this->_stack->_lights.end(); i++)
			{
				light_t* light = *i;
				if (light != 0)
				{
					albedo += light->luminance(this->_fragment);
				}
			}
		}
		
		return albedo;
	}

	const fragment_t tracepath_t::fragment() const
	{
		return this->_fragment;
	}

	tracepath_t& tracepath_t::operator=(const fragment_t& frag)
	{
		this->clear();
		this->_fragment = frag;
		return *this;
	}
	
}