#pragma once

namespace ray
{
	
	class texturefilter_t
	{
	public:
		
		enum SAMPLETYPE
		{
			SAMPLETYPE_NEAREST,
			SAMPLETYPE_LINEAR
		};
		
		inline texturefilter_t() :
			_texture(0),
			_type(SAMPLETYPE_NEAREST) {}
		inline texturefilter_t(IMAGETYPE* source, const SAMPLETYPE type) :
			_texture(source),
			_type(type) {}
		inline ~texturefilter_t() {}
		
		glm::vec4 sample(const glm::vec2& texcoord) const;
		
	protected:
		
		static glm::vec4 unpack(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha);
		
		IMAGETYPE* _texture;
		SAMPLETYPE _type;
		
	};
	
	/// <summary>
	/// Contains methods and properties for shading a surface.
	/// </summary>
	class material_t
	{
	public:
		
		/// <summary>
		/// Calculates lumination for a given surface fragment.
		/// </summary>
		/// <param name="lighting">Lighting data to illuminate the surface.</param>
		/// <param name="fragment">Surface to be illuminated.</param>
		/// <returns>Lumination for the surface fragment.</returns>
		virtual lumination_t shade(const lighting_t& lighting, const fragment_t& fragment) = 0;
		
	};
	
}