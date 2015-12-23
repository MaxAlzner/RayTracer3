
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
		return lumination_t(1.0f, 1.0f);
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