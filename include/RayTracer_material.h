#pragma once

namespace ray
{
	
	/// <summary>
	/// Enumeration for texture sampling types.
	/// </summary>
	enum SAMPLETYPE
	{
		/// <summary>
		/// Sample the nearest pixel to the texture coordinate.
		/// </summary>
		SAMPLETYPE_NEAREST,
		/// <summary>
		/// Bias the sampling based on how close the texture coordinate is to nearby pixels.
		/// </summary>
		SAMPLETYPE_LINEAR
	};
	
	/// <summary>
	/// Enumeration for type of textures.
	/// </summary>
	enum TEXTURETYPE
	{
		TEXTURETYPE_COLOR,
		TEXTURETYPE_NORMAL,
		TEXTURETYPE_SPECULAR,
		TEXTURETYPE_TRANSPARENCY,
		TEXTURETYPE_REFLECTIVITY,
		TEXTURETYPE_EMISSIVE,
		TEXTURETYPE_DISPLACEMENT,
	};
	
	/// <summary>
	/// Contains methods and properties for referencing and sampling a texture.
	/// </summary>
	class texturefilter_t
	{
	public:
		
		inline texturefilter_t() :
			_texture(0),
			_type(SAMPLETYPE_NEAREST) {}
		/// <param name="source">Image to sample from.</param>
		/// <param name="type">Sampling techniue to use.</param>
		inline texturefilter_t(IMAGETYPE* source, const SAMPLETYPE type) :
			_texture(source),
			_type(type) {}
		inline ~texturefilter_t() {}
		
		/// <summary>
		/// Samples the texture by the given texture coordinate, using the filter's sampling type.
		/// </summary>
		/// <param name="texcoord">2 dimensional vector representing a uv position inside of the texture.</param>
		/// <returns>4 dimensional vector representing the color of a pixel.</returns>
		glm::vec4 sample(const glm::vec2& texcoord) const;
		
	protected:
		
		/// <summary>
		/// Transforms the given byte channels into a 4 dimensional vector.
		/// </summary>
		/// <param name="red">Byte containing the red color channel.</param>
		/// <param name="green">Byte containing the green color channel.</param>
		/// <param name="blue">Byte containing the blue color channel.</param>
		/// <param name="alpha">Byte containing the alpha channel.</param>
		/// <returns>4 dimensional vector containing each channel as a floating point.</returns>
		static glm::vec4 unpack(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha);
		
		/// <summary>
		/// Texture image file.
		/// </summary>
		IMAGETYPE* _texture;
		/// <summary>
		/// Type of sampling technique to use.
		/// </summary>
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
		virtual lumination_t shade(const lighting_t& lighting, const fragment_t& fragment) const = 0;
		
		/// <summary>
		/// Sets the given texture filter to the material's corresponding texture.
		/// </summary>
		/// <param name="filter">Texture filter.</param>
		/// <param name="type">Type of material texture.</param>
		void attach(const texturefilter_t& filter, const TEXTURETYPE type);
		
		/// <summary>
		/// Gets the material's color at the given texture coordinate.
		/// </summary>
		/// <param name="texcoord">2 dimensional vector representing a texture coordinate.</param>
		/// <returns>4 dimensional vector representing color.</returns>
		glm::vec4 color(const glm::vec2& texcoord) const;
		/// <summary>
		/// Gets the material's surface normal at the given texture coordinate.
		/// </summary>
		/// <param name="texcoord">2 dimensional vector representing a texture coordinate.</param>
		/// <returns>3 dimensional vector representing a surface normal.
		glm::vec3 normal(const glm::vec2& texcoord) const;
		/// <summary>
		/// Gets the material's specular color at the given texture coordinate.
		/// </summary>
		/// <param name="texcoord">2 dimensional vector representing a texture coordinate.</param>
		/// <returns>4 dimensional vector representing specular color.</returns>
		glm::vec4 specular(const glm::vec2& texcoord) const;
		/// <summary>
		/// Gets the material's emissive color at the given texture coordinate.
		/// </summary>
		/// <param name="texcoord">2 dimensional vector representing a texture coordinate.</param>
		/// <returns>4 dimensional vector representing emissive color.</returns>
		glm::vec4 emissive(const glm::vec2& texcoord) const;
		/// <summary>
		/// Gets the material's transparency value at the given coordinate.
		/// </summary>
		/// <param name="texcoord">2 dimensional vector representing a texture coordinate.</param>
		/// <returns>Transparency value.</returns>
		float transparency(const glm::vec2& texcoord) const;
		/// <summary>
		/// Gets the material's reflectivity value at the given coordinate.
		/// </summary>
		/// <param name="texcoord">2 dimensional vector representing a texture coordinate.</param>
		/// <returns>Reflectivity value.</returns>
		float reflectivity(const glm::vec2& texcoord) const;
		
	protected:
		
		texturefilter_t _colormap;
		texturefilter_t _normalmap;
		texturefilter_t _specularmap;
		texturefilter_t _transparencymap;
		texturefilter_t _reflectivitymap;
		texturefilter_t _emissivemap;
		texturefilter_t _displacementmap;
		
	};
	
	/// <summary>
	/// Contains methods and properties for a lambert material.
	/// </summary>
	class lambert_t : public material_t
	{
	public:

		inline lambert_t() {}
		inline ~lambert_t() {}

		/// <summary>
		/// Calculates lumination for a given surface fragment.
		/// </summary>
		/// <param name="lighting">Lighting data to illuminate the surface.</param>
		/// <param name="fragment">Surface to be illuminated.</param>
		/// <returns>Lumination for the surface fragment.</returns>
		lumination_t shade(const lighting_t& lighting, const fragment_t& fragment) const;

	};

	/// <summary>
	/// Contains methods and properties for a phong material.
	/// </summary>
	class phong_t : public material_t
	{
	public:

		inline phong_t() : _exponent(16.0f) {}
		/// <param name="exponent">Value used in calculating the material's highlight.</param>
		inline phong_t(const float exponent) : _exponent(exponent) {}
		inline ~phong_t() {}

		/// <summary>
		/// Calculates lumination for a given surface fragment.
		/// </summary>
		/// <param name="lighting">Lighting data to illuminate the surface.</param>
		/// <param name="fragment">Surface to be illuminated.</param>
		/// <returns>Lumination for the surface fragment.</returns>
		lumination_t shade(const lighting_t& lighting, const fragment_t& fragment) const;

	protected:

		float _exponent;

	};

	/// <summary>
	/// Contains methods and properties for a blinn material.
	/// </summary>
	class blinn_t : public material_t
	{
	public:

		inline blinn_t() : _exponent(32.0f) {}
		/// <param name="exponent">Value used in calculating the material's highlight.</param>
		inline blinn_t(const float exponent) : _exponent(exponent) {}
		inline ~blinn_t() {}

		/// <summary>
		/// Calculates lumination for a given surface fragment.
		/// </summary>
		/// <param name="lighting">Lighting data to illuminate the surface.</param>
		/// <param name="fragment">Surface to be illuminated.</param>
		/// <returns>Lumination for the surface fragment.</returns>
		lumination_t shade(const lighting_t& lighting, const fragment_t& fragment) const;

	protected:

		float _exponent;

	};

}