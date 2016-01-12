
#include "../include/RayTracer.h"

namespace ray
{
	
	void material_t::attach(const texturefilter_t& filter, const TEXTURETYPE type)
	{
		switch (type)
		{
		case TEXTURETYPE_COLOR:
			this->_colormap = filter;
		case TEXTURETYPE_NORMAL:
			this->_normalmap = filter;
		case TEXTURETYPE_SPECULAR:
			this->_specularmap = filter;
		case TEXTURETYPE_TRANSPARENCY:
			this->_transparencymap = filter;
		case TEXTURETYPE_REFLECTIVITY:
			this->_reflectivitymap = filter;
		case TEXTURETYPE_EMISSIVE:
			this->_emissivemap = filter;
		case TEXTURETYPE_DISPLACEMENT:
			this->_displacementmap = filter;
		default:
			break;
		}
	}
	
	glm::vec4 material_t::color(const glm::vec2& texcoord) const
	{
		return glm::vec4(1.0f);
		//return this->_colormap.sample(texcoord);
	}
	glm::vec3 material_t::normal(const glm::vec2& texcoord) const
	{
		return glm::normalize((glm::vec3(this->_normalmap.sample(texcoord)) * 2.0f) - 1.0f);
	}
	glm::vec4 material_t::specular(const glm::vec2& texcoord) const
	{
		return this->_specularmap.sample(texcoord);
	}
	glm::vec4 material_t::emissive(const glm::vec2& texcoord) const
	{
		return this->_emissivemap.sample(texcoord);
	}
	float material_t::transparency(const glm::vec2& texcoord) const
	{
		glm::vec4 color = this->_transparencymap.sample(texcoord);
		return (color.r + color.g + color.b) / 3.0f;
	}
	float material_t::reflectivity(const glm::vec2& texcoord) const
	{
		glm::vec4 color = this->_reflectivitymap.sample(texcoord);
		return (color.r + color.g + color.b) / 3.0f;
	}
	
	lumination_t lambert_t::shade(const lighting_t& lighting, const fragment_t& fragment) const
	{
		return lumination_t(
			fragment._color * glm::max(glm::dot(fragment._normal, lighting._direction), 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	lumination_t phong_t::shade(const lighting_t& lighting, const fragment_t& fragment) const
	{
		return lumination_t(
			fragment._color * glm::max(glm::dot(fragment._normal, lighting._direction), 0.0f),
			fragment._specular * glm::max(glm::pow(glm::dot(glm::reflect(-lighting._direction, fragment._normal), fragment._view), this->_exponent), 0.0f));
	}

	lumination_t blinn_t::shade(const lighting_t& lighting, const fragment_t& fragment) const
	{
		return lumination_t(
			fragment._color * glm::max(glm::dot(fragment._normal, lighting._direction), 0.0f),
			fragment._specular * glm::max(glm::pow(glm::dot(glm::normalize(fragment._normal + fragment._view), fragment._view), this->_exponent), 0.0f));
	}

}