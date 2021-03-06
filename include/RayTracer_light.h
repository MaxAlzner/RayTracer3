#pragma once

namespace ray
{
	
	/// <summary>
	/// Contains methods and properties for illuminating a traceable surface.
	/// </summary>
	class light_t
	{
	public:
		
		inline light_t() :
			_intensity(0.0f) {}
		/// <param name="intensity">Intensity value for the light, must be positive.</param>
		inline light_t(const float intensity) :
			_intensity(std::max(intensity, 0.0f)) {}
		inline ~light_t() {}
		
		/// <summary>
		/// Calculates the luminance generated by the light for the given surface fragment.
		/// </summary>
		/// <param name="fragment">Surface fragment to illuminate.</param>
		/// <returns>Lumination for the surface fragment.</returns>
		virtual lumination_t luminance(const fragment_t& fragment) = 0;
		
		/// <summary>
		/// Calculates a scalar value of how much the given surface fragment is in shadow.
		/// </summary>
		/// <param name="fragment">Surface fragment to occlude.</param>
		/// <returns>Scalar value for how occluded the surface fragment is.</returns>
		virtual float occlusion(const fragment_t& fragment) = 0;
		
	protected:
		
		/// <summary>
		/// Intensity value of the light.
		/// </summary>
		float _intensity;
		
	};
	
	/// <summary>
	/// Contains methods and properties for a point light.
	/// </summary>
	class pointlight_t : public light_t
	{
	public:
		
		inline pointlight_t() :
			light_t() {}
		/// <param name="position">4 dimensional vector representing the position of the light.</param>
		/// <param name="color">4 dimensional vector representing the color of the light.</param>
		/// <param name="intensity">Intensity value for the light, must be positive.</param>
		inline pointlight_t(const glm::vec4& position, const glm::vec4& color, const float intensity) :
			light_t(intensity),
			_position(position),
			_color(color) {}
		inline ~pointlight_t() {}
		
		/// <summary>
		/// Calculates the luminance generated by the light for the given surface fragment.
		/// </summary>
		/// <param name="fragment">Surface fragment to illuminate.</param>
		/// <returns>Lumination for the surface fragment.</returns>
		lumination_t luminance(const fragment_t& fragment);
		
		/// <summary>
		/// Calculates a scalar value of how much the given surface fragment is in shadow.
		/// </summary>
		/// <param name="fragment">Surface fragment to occlude.</param>
		/// <returns>Scalar value for how occluded the surface fragment is.</returns>
		float occlusion(const fragment_t& fragment);
		
	protected:
		
		/// <summary>
		/// Position of the point light.
		/// </summary>
		glm::vec4 _position;
		/// <summary>
		/// Color of the point light.
		/// </summary>
		glm::vec4 _color;
		
	};
	
}