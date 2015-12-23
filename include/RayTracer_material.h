#pragma once

namespace ray
{
	
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