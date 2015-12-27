
#include "../include/RayTracer.h"

namespace ray
{
	
	glm::vec4 texturefilter_t::sample(const glm::vec2& texcoord) const
	{
		if (this->_texture != 0)
		{
			size_t width = FreeImage_GetWidth(this->_texture);
			size_t height = FreeImage_GetHeight(this->_texture);
			if (this->_type == SAMPLETYPE_NEAREST)
			{
				RGBQUAD pixel;
				if (FreeImage_GetPixelColor(this->_texture, (int)texcoord.x, (int)texcoord.y, &pixel))
				{
					return unpack(pixel.rgbRed, pixel.rgbGreen, pixel.rgbBlue, pixel.rgbReserved);
				}
			}
			else if (this->_type == SAMPLETYPE_LINEAR)
			{
				glm::vec2 increment = 1.0f / glm::vec2(float(width), float(height));
				glm::vec2 uv0 = glm::vec2(fmod(texcoord.x, increment.x), fmod(texcoord.y, increment.y)) / increment;
				glm::vec2 uv1 = 1.0f - uv0;
				glm::vec2 linear0 = glm::normalize(uv0) * 0.25f;
				glm::vec2 linear1 = glm::normalize(glm::vec2(uv1.x, uv0.y)) * 0.25f;
				glm::vec2 linear2 = glm::normalize(glm::vec2(uv0.x, uv1.y)) * 0.25f;
				glm::vec2 linear3 = glm::normalize(uv1) * 0.25f;
				size_t x0 = (size_t)(texcoord.x * float(width));
				size_t y0 = (size_t)(texcoord.y * float(height));
				size_t x1 = std::min(x0 + 1, width);
				size_t y1 = std::min(y0 + 1, height);
				RGBQUAD pixel0, pixel1, pixel2, pixel3;
				if (FreeImage_GetPixelColor(this->_texture, x0, y0, &pixel0) &&
					FreeImage_GetPixelColor(this->_texture, x1, y0, &pixel1) &&
					FreeImage_GetPixelColor(this->_texture, x0, y1, &pixel2) &&
					FreeImage_GetPixelColor(this->_texture, x1, y1, &pixel3))
				{
					return
						(unpack(pixel0.rgbRed, pixel0.rgbGreen, pixel0.rgbBlue, pixel0.rgbReserved) * glm::length(linear0)) +
						(unpack(pixel1.rgbRed, pixel1.rgbGreen, pixel1.rgbBlue, pixel1.rgbReserved) * glm::length(linear1)) +
						(unpack(pixel2.rgbRed, pixel2.rgbGreen, pixel2.rgbBlue, pixel2.rgbReserved) * glm::length(linear2)) +
						(unpack(pixel3.rgbRed, pixel3.rgbGreen, pixel3.rgbBlue, pixel3.rgbReserved) * glm::length(linear3));
				}
			}
		}
		
		return glm::vec4(0.0f);
	}
	
	glm::vec4 texturefilter_t::unpack(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha)
	{
		return glm::vec4(
			((float)red) / 255.0f,
			((float)green) / 255.0f,
			((float)blue) / 255.0f,
			((float)alpha) / 255.0f
		);
	}
	
}