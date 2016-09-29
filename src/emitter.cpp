
#include "../include/RayTracer.h"

namespace ray
{

#if 0
	bool photo_t::empty() const
	{
		return this->_buffer == 0 || this->_width < 1 || this->_height < 1;
	}

	void photo_t::resize(const size_t width, const size_t height)
	{
		tracepath_t* old = this->_buffer;
		size_t oldWidth = this->_width;
		size_t oldHeight = this->_height;
		this->_width = std::max(width, (size_t)1ul);
		this->_height = std::max(height, (size_t)1ul);
		this->_buffer = (tracepath_t*)calloc(this->_width * this->_height, sizeof(tracepath_t));
		if (old != 0)
		{
			for (size_t i = 0; i < oldHeight && i < this->_height; i++)
			{
				memcpy(this->_buffer + (this->_width * i), old + (oldWidth * i), std::min(oldWidth, this->_width) * sizeof(tracepath_t));
			}
			
			free(old);
		}
	}
	void photo_t::release()
	{
		if (this->_buffer != 0)
		{
			free(this->_buffer);
		}
		
		this->_buffer = 0;
		this->_width = 0;
		this->_height = 0;
	}
	
	void photo_t::trace(const tracestack_t& stack, const camera_t& camera)
	{
		for (size_t i = 0; i < this->_height; i++)
		{
			for (size_t k = 0; k < this->_width; k++)
			{
				ray_t ray = camera.cast(float(k) / float(this->_width), float(i) / float(this->_height));
				rayhit_t hit;
				const traceable_t* obj = stack.nearest(ray, &hit);
				if (obj != 0)
				{
					tracepath_t* path = &(this->operator[](glm::ivec2(k, i)));
					*path = tracepath_t(obj->fragmentate(hit), stack, 0, 0);
				}
			}
		}
	}

	IMAGETYPE* photo_t::rasterize() const
	{
		FIBITMAP* bitmap = FreeImage_Allocate(this->_width, this->_height, 32);
		if (!this->empty())
		{
			for (size_t i = 0; i < this->_height; i++)
			{
				for (size_t k = 0; k < this->_width; k++)
				{
					tracepath_t* path = &(this->operator[](glm::ivec2(k, i)));
					lumination_t albedo = path->albedo();
					glm::vec4 color = albedo.flatten();
					RGBQUAD pixel = {
						(uint8_t)(color.b * 255.0f),
						(uint8_t)(color.g * 255.0f),
						(uint8_t)(color.r * 255.0f),
						(uint8_t)(color.a * 255.0f)
					};
					FreeImage_SetPixelColor(bitmap, k, i, &pixel);
				}
			}
		}
		
		return bitmap;
	}

	tracepath_t& photo_t::operator[](const glm::ivec2& coord) const
	{
		return this->_buffer[((coord.y % this->_height) * this->_width) + (coord.x % this->_width)];
	}
#endif

}