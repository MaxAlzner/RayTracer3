#pragma once

namespace ray
{
	
	/// <summary>
	/// Contains methods and properties for a ray datatype.
	/// Rays have an origin point and a directional vector.
	/// </summary>
	struct ray_t
	{
		
		inline ray_t() :
			_origin(0.0f, 0.0f, 0.0f, 1.0f),
			_forward(0.0f, 0.0f, 1.0f) {}
		/// <param name="origin">3 dimensional vector representing the origin of the ray.</param>
		/// <param name="origin">3 dimensional vector representing the direction of the ray.</param>
		inline ray_t(const glm::vec3& origin, const glm::vec3& forward) :
			_origin(origin, 1.0f),
			_forward(forward) {}
		/// <param name="origin">4 dimensional vector representing the origin of the ray.</param>
		/// <param name="origin">3 dimensional vector representing the direction of the ray.</param>
		inline ray_t(const glm::vec4& origin, const glm::vec3& forward) :
			_origin(origin),
			_forward(forward) {}
		inline ~ray_t() {}
		
		inline ray_t operator+() const;
		inline ray_t operator-() const;
		inline ray_t& operator+=(const ray_t& other);
		inline ray_t& operator+=(const glm::vec4& v);
		inline ray_t& operator+=(const glm::vec3& v);
		inline ray_t& operator+=(const float v);
		inline ray_t& operator-=(const ray_t& other);
		inline ray_t& operator-=(const glm::vec4& v);
		inline ray_t& operator-=(const glm::vec3& v);
		inline ray_t& operator-=(const float v);
		inline ray_t& operator*=(const ray_t& other);
		inline ray_t& operator*=(const glm::vec4& v);
		inline ray_t& operator*=(const glm::vec3& v);
		inline ray_t& operator*=(const float v);
		inline ray_t& operator/=(const ray_t& other);
		inline ray_t& operator/=(const glm::vec4& v);
		inline ray_t& operator/=(const glm::vec3& v);
		inline ray_t& operator/=(const float v);
		
		/// <summary>
		/// Origin vertex of the ray.
		/// </summary>
		glm::vec4 _origin;
		/// <summary>
		/// Forward directional vector of the ray.
		/// </summary>
		glm::vec3 _forward;
		
	};
	
	inline ray_t operator+(const ray_t& r0, const ray_t& r1);
	inline ray_t operator+(const ray_t& r, const glm::vec4& v);
	inline ray_t operator+(const glm::vec4& v, const ray_t& r);
	inline ray_t operator+(const ray_t& r, const glm::vec3& v);
	inline ray_t operator+(const glm::vec3& v, const ray_t& r);
	inline ray_t operator+(const ray_t& r, const float v);
	inline ray_t operator+(const float v, const ray_t& r);
	
	inline ray_t operator-(const ray_t& r0, const ray_t& r1);
	inline ray_t operator-(const ray_t& r, const glm::vec4& v);
	inline ray_t operator-(const glm::vec4& v, const ray_t& r);
	inline ray_t operator-(const ray_t& r, const glm::vec3& v);
	inline ray_t operator-(const glm::vec3& v, const ray_t& r);
	inline ray_t operator-(const ray_t& r, const float v);
	inline ray_t operator-(const float v, const ray_t& r);
	
	inline ray_t operator*(const ray_t& r0, const ray_t& r1);
	inline ray_t operator*(const ray_t& r, const glm::vec4& v);
	inline ray_t operator*(const glm::vec4& v, const ray_t& r);
	inline ray_t operator*(const ray_t& r, const glm::vec3& v);
	inline ray_t operator*(const glm::vec3& v, const ray_t& r);
	inline ray_t operator*(const ray_t& r, const float v);
	inline ray_t operator*(const float v, const ray_t& r);
	
	inline ray_t operator/(const ray_t& r0, const ray_t& r1);
	inline ray_t operator/(const ray_t& r, const glm::vec4& v);
	inline ray_t operator/(const glm::vec4& v, const ray_t& r);
	inline ray_t operator/(const ray_t& r, const glm::vec3& v);
	inline ray_t operator/(const glm::vec3& v, const ray_t& r);
	inline ray_t operator/(const ray_t& r, const float v);
	inline ray_t operator/(const float v, const ray_t& r);
	
	/// <summary>
	/// Contains methods and properties for calculated lumination datatype.
	/// </summary>
	struct lumination_t
	{
		
		inline lumination_t() :
			_diffuse(0.0f),
			_specular(0.0f) {}
		/// <param name="diffuse">4 dimensional vector representing the base diffuse color.</param>
		/// <param name="diffuse">4 dimensional vector representing the highlight specular color.</param>
		inline lumination_t(const glm::vec4& diffuse, const glm::vec4& specular) :
			_diffuse(diffuse),
			_specular(specular) {}
		/// <param name="diffuse">Base diffuse color as scalar value.</param>
		/// <param name="diffuse">Highlight specular color as scalar value.</param>
		inline lumination_t(const float diffuse, const float specular) :
			_diffuse(diffuse),
			_specular(specular) {}
		inline ~lumination_t() {}
		
		/// <summary>
		/// Flattens the lumination colors into single color channel.
		/// </summary>
		/// <returns>4 dimensional vector representing a color (R, G, B, A).</returns>
		inline glm::vec4 flatten() const;
		
		inline lumination_t operator+() const;
		inline lumination_t operator-() const;
		inline lumination_t& operator+=(const lumination_t& other);
		inline lumination_t& operator+=(const glm::vec4& v);
		inline lumination_t& operator+=(const float v);
		inline lumination_t& operator-=(const lumination_t& other);
		inline lumination_t& operator-=(const glm::vec4& v);
		inline lumination_t& operator-=(const float v);
		inline lumination_t& operator*=(const lumination_t& other);
		inline lumination_t& operator*=(const glm::vec4& v);
		inline lumination_t& operator*=(const float v);
		inline lumination_t& operator/=(const lumination_t& other);
		inline lumination_t& operator/=(const glm::vec4& v);
		inline lumination_t& operator/=(const float v);
		
		/// <summary>
		/// Diffuse base color.
		/// </summary>
		glm::vec4 _diffuse;
		/// <summary>
		/// Specular highlight color.
		/// </summary>
		glm::vec4 _specular;
		
	};
	
	inline lumination_t operator+(const lumination_t& l0, const lumination_t& l1);
	inline lumination_t operator+(const lumination_t& l, const glm::vec4& v);
	inline lumination_t operator+(const glm::vec4& v, const lumination_t& l);
	inline lumination_t operator+(const lumination_t& l, const float v);
	inline lumination_t operator+(const float v, const lumination_t& l);
	
	inline lumination_t operator-(const lumination_t& l0, const lumination_t& l1);
	inline lumination_t operator-(const lumination_t& l, const glm::vec4& v);
	inline lumination_t operator-(const glm::vec4& v, const lumination_t& l);
	inline lumination_t operator-(const lumination_t& l, const float v);
	inline lumination_t operator-(const float v, const lumination_t& l);
	
	inline lumination_t operator*(const lumination_t& l0, const lumination_t& l1);
	inline lumination_t operator*(const lumination_t& l, const glm::vec4& v);
	inline lumination_t operator*(const glm::vec4& v, const lumination_t& l);
	inline lumination_t operator*(const lumination_t& l, const float v);
	inline lumination_t operator*(const float v, const lumination_t& l);
	
	inline lumination_t operator/(const lumination_t& l0, const lumination_t& l1);
	inline lumination_t operator/(const lumination_t& l, const glm::vec4& v);
	inline lumination_t operator/(const glm::vec4& v, const lumination_t& l);
	inline lumination_t operator/(const lumination_t& l, const float v);
	inline lumination_t operator/(const float v, const lumination_t& l);
	
	/// <summary>
	/// Contains methods and properties for the result of a ray hitting a shape.
	/// </summary>
	struct rayhit_t
	{
		
		inline rayhit_t() :
			_distance(FLT_MAX),
			_intersection(0.0f, 0.0f, 0.0f, 1.0),
			_texcoord(0.0f),
			_normal(0.0f, 0.0f, 1.0f),
			_tangent(1.0f, 0.0f, 0.0f),
			_binormal(0.0f, 1.0f, 0.0f)/*,
			_surface(0)*/ {}
		/// <param name="ray">Ray that caused the hit.</param>
		/// <param name="distance">Distance from the ray origin to the intersection.</param>
		/// <param name="intersection">Intersection point where the hit occured.</param>
		/// <param name="texcoord">Texture coordinate on the shape where the hit occured.</param>
		/// <param name="normal">Surface normal on the shape where the hit occured.</param>
		/// <param name="tangent">Surface tangent on the shape where the hit occured.</param>
		/// <param name="binormal">Surface binormal on the shape where the hit occured.</param>
		/// <param name="surface">Pointer to the surface shape.</param>
		inline rayhit_t(
			const ray_t& ray,
			const float distance,
			const glm::vec4& intersection,
			const glm::vec2& texcoord,
			const glm::vec3& normal,
			const glm::vec3& tangent,
			const glm::vec3& binormal/*,
			void const * surface*/) :
			_ray(ray),
			_distance(distance),
			_texcoord(texcoord),
			_normal(normal),
			_tangent(tangent),
			_binormal(binormal)/*,
			_surface(surface)*/ {}
		inline ~rayhit_t() {}
		
		/// <summary>
		/// Ray that caused the hit.
		/// </summary>
		ray_t _ray;
		/// <summary>
		/// Distance from the ray origin to the intersection.
		/// </summary>
		float _distance;
		/// <summary>
		/// Intersection point where the hit occured.
		/// </summary>
		glm::vec4 _intersection;
		/// <summary>
		/// Texture coordinate on the shape where the hit occured.
		/// </summary>
		glm::vec2 _texcoord;
		/// <summary>
		/// Surface normal on the shape where the hit occured.
		/// </summary>
		glm::vec3 _normal;
		/// <summary>
		/// Surface tangent on the shape where the hit occured.
		/// </summary>
		glm::vec3 _tangent;
		/// <summary>
		/// Surface binormal on the shape where the hit occured.
		/// </summary>
		glm::vec3 _binormal;
		/// <summary>
		/// Pointer to the surface shape.
		/// </summary>
		// void* _surface;
		
	};
	
	/// <summary>
	/// Contains methods and properties for the calculated lighting data for a point in space.
	/// </summary>
	struct fragment_t
	{
		
		inline fragment_t() :
			// _material(0),
			_position(0.0f),
			_texcoord(0.0f),
			_space(1.0f),
			_normal(0.0f, 0.0f, 1.0f),
			_tangent(1.0f, 0.0f, 0.0f),
			_binormal(0.0f, 1.0f, 0.0f),
			_view(0.0f, 0.0f, 1.0f),
			_transparency(0.0f),
			_reflectivity(1.0f),
			_color(1.0f),
			_specular(1.0f),
			_emissive(0.0f) {}
		// inline fragment_t(const rayhit_t& hit, void& material) :
		// 	_material(&material),
		// 	_position(hit.intersection),
		// 	_texcoord(hit.texcoord),
		// 	_space(hit.tangent, hit.binormal, hit.normal),
		// 	_normal(glm::normalize(this->_space * this->_material->surfaceNormal(this->_texcoord))),
		// 	_tangent(glm::cross(-hit.binormal, this->_normal)),
		// 	_binormal(glm::cross(this->_tangent, this->_normal)),
		// 	_view(-hit.ray.direction),
		// 	_transparency(this->_material->surfaceTransparency(this->_texcoord)),
		// 	_reflectivity(this->_material->surfaceReflectivity(this->_texcoord)),
		// 	_color(this->_material->surfaceColor(this->_texcoord)),
		// 	_specular(this->_material->surfaceSpecular(this->_texcoord)),
		// 	_emissive(this->_material->surfaceEmissive(this->_texcoord)) {}
		inline ~fragment_t() {}
		
		/// <summary>
		/// Bounces the given ray off of the fragment position and surface normal.
		/// </summary>
		/// <returns>Transformed ray that has been reflected.</returns>
		inline ray_t reflect(const ray_t& ray) { return ray_t(this->_position, glm::reflect(-ray._forward, this->_normal)); }
		
		// void const * _material;
		/// <summary>
		/// Surface position of the fragment.
		/// </summary>
		glm::vec4 _position;
		/// <summary>
		/// Texture coordinate on the surface at the position.
		/// </summary>
		glm::vec2 _texcoord;
		/// <summary>
		/// Surface space matrix at the position.
		/// </summary>
		glm::mat3 _space;
		/// <summary>
		/// Surface normal at he position.
		/// </summary>
		glm::vec3 _normal;
		/// <summary>
		/// Surface tangent at the position.
		/// </summary>
		glm::vec3 _tangent;
		/// <summary>
		/// Surface binormal at the position.
		/// </summary>
		glm::vec3 _binormal;
		/// <summary>
		/// View directional vector the position.
		/// </summary>
		glm::vec3 _view;
		/// <summary>
		/// Transparency value tthe position.
		/// </summary>
		float _transparency;
		/// <summary>
		/// Reflectivity value tthe position.
		/// </summary>
		float _reflectivity;
		/// <summary>
		/// Base color at the position.
		/// </summary>
		glm::vec4 _color;
		/// <summary>
		/// Specular color at the position.
		/// </summary>
		glm::vec4 _specular;
		/// <summary>
		/// Emissive color at the position.
		/// </summary>
		glm::vec4 _emissive;
		
	};
	
}