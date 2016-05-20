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
		
		inline ray_t operator+() const
		{
			return ray_t(+this->_origin, +this->_forward);
		}
		inline ray_t operator-() const
		{
			return ray_t(-this->_origin, -this->_forward);
		}
		inline ray_t& operator+=(const ray_t& other)
		{
			this->_origin += other._origin;
			this->_forward = glm::normalize(this->_forward + other._forward);
			return *this;
		}
		inline ray_t& operator+=(const glm::vec4& v)
		{
			this->_origin += v;
			return *this;
		}
		inline ray_t& operator+=(const glm::vec3& v)
		{
			this->_origin += glm::vec4(v, 0.0f);
			return *this;
		}
		inline ray_t& operator+=(const float v)
		{
			this->_origin += v;
			return *this;
		}
		inline ray_t& operator-=(const ray_t& other)
		{
			this->_origin -= other._origin;
			this->_forward = glm::normalize(this->_forward - other._forward);
			return *this;
		}
		inline ray_t& operator-=(const glm::vec4& v)
		{
			this->_origin -= v;
			return *this;
		}
		inline ray_t& operator-=(const glm::vec3& v)
		{
			this->_origin -= glm::vec4(v, 1.0f);
			return *this;
		}
		inline ray_t& operator-=(const float v)
		{
			this->_origin -= v;
			return *this;
		}
		inline ray_t& operator*=(const ray_t& other)
		{
			this->_origin *= other._origin;
			this->_forward = glm::normalize(this->_forward * other._forward);
			return *this;
		}
		inline ray_t& operator*=(const glm::vec4& v)
		{
			this->_origin *= v;
			this->_forward = glm::normalize(this->_forward * glm::vec3(v));
			return *this;
		}
		inline ray_t& operator*=(const glm::vec3& v)
		{
			this->_origin *= glm::vec4(v, 1.0f);
			this->_forward = glm::normalize(this->_forward * v);
			return *this;
		}
		inline ray_t& operator*=(const float v)
		{
			this->_origin *= v;
			this->_forward = glm::normalize(this->_forward * v);
			return *this;
		}
		inline ray_t& operator/=(const ray_t& other)
		{
			this->_origin /= other._origin;
			this->_forward = glm::normalize(this->_forward / other._forward);
			return *this;
		}
		inline ray_t& operator/=(const glm::vec4& v)
		{
			this->_origin /= v;
			this->_forward = glm::normalize(this->_forward / glm::vec3(v));
			return *this;
		}
		inline ray_t& operator/=(const glm::vec3& v)
		{
			this->_origin /= glm::vec4(v, 1.0f);
			this->_forward = glm::normalize(this->_forward / v);
			return *this;
		}
		inline ray_t& operator/=(const float v)
		{
			this->_origin /= v;
			this->_forward = glm::normalize(this->_forward / v);
			return *this;
		}
		
		/// <summary>
		/// Origin vertex of the ray.
		/// </summary>
		glm::vec4 _origin;
		/// <summary>
		/// Forward directional vector of the ray.
		/// </summary>
		glm::vec3 _forward;
		
	};
	
	inline ray_t operator+(const ray_t& r0, const ray_t& r1)
	{
		return ray_t(r0._origin + r1._origin, glm::normalize(r0._forward + r1._forward));
	}
	inline ray_t operator+(const ray_t& r, const glm::vec4& v)
	{
		return ray_t(r._origin + v, r._forward);
	}
	inline ray_t operator+(const glm::vec4& v, const ray_t& r)
	{
		return ray_t(v + r._origin, r._forward);
	}
	inline ray_t operator+(const ray_t& r, const glm::vec3& v)
	{
		return ray_t(r._origin + glm::vec4(v, 0.0f), r._forward);
	}
	inline ray_t operator+(const glm::vec3& v, const ray_t& r)
	{
		return ray_t(glm::vec4(v, 0.0f) + r._origin, r._forward);
	}
	inline ray_t operator+(const ray_t& r, const float v)
	{
		return ray_t(r._origin + v, r._forward);
	}
	inline ray_t operator+(const float v, const ray_t& r)
	{
		return ray_t(v + r._origin, r._forward);
	}
	
	inline ray_t operator-(const ray_t& r0, const ray_t& r1)
	{
		return ray_t(r0._origin - r1._origin, glm::normalize(r0._forward - r1._forward));
	}
	inline ray_t operator-(const ray_t& r, const glm::vec4& v)
	{
		return ray_t(r._origin - v, r._forward);
	}
	inline ray_t operator-(const glm::vec4& v, const ray_t& r)
	{
		return ray_t(v - r._origin, r._forward);
	}
	inline ray_t operator-(const ray_t& r, const glm::vec3& v)
	{
		return ray_t(r._origin - glm::vec4(v, 0.0f), r._forward);
	}
	inline ray_t operator-(const glm::vec3& v, const ray_t& r)
	{
		return ray_t(glm::vec4(v, 0.0f) - r._origin, r._forward);
	}
	inline ray_t operator-(const ray_t& r, const float v)
	{
		return ray_t(r._origin - v, r._forward);
	}
	inline ray_t operator-(const float v, const ray_t& r)
	{
		return ray_t(v - r._origin, r._forward);
	}
	
	inline ray_t operator*(const ray_t& r0, const ray_t& r1)
	{
		return ray_t(r0._origin * r1._origin, glm::normalize(r0._forward * r1._forward));
	}
	inline ray_t operator*(const ray_t& r, const glm::vec4& v)
	{
		return ray_t(r._origin * v, glm::normalize(r._forward * glm::vec3(v)));
	}
	inline ray_t operator*(const glm::vec4& v, const ray_t& r)
	{
		return ray_t(v * r._origin, glm::normalize(glm::vec3(v) * r._forward));
	}
	inline ray_t operator*(const ray_t& r, const glm::vec3& v)
	{
		return ray_t(r._origin * glm::vec4(v, 1.0f), glm::normalize(r._forward * v));
	}
	inline ray_t operator*(const glm::vec3& v, const ray_t& r)
	{
		return ray_t(glm::vec4(v, 1.0f) * r._origin, glm::normalize(v * r._forward));
	}
	inline ray_t operator*(const ray_t& r, const float v)
	{
		return ray_t(r._origin * v, glm::normalize(r._forward * v));
	}
	inline ray_t operator*(const float v, const ray_t& r)
	{
		return ray_t(v * r._origin, glm::normalize(v * r._forward));
	}
	
	inline ray_t operator/(const ray_t& r0, const ray_t& r1)
	{
		return ray_t(r0._origin / r1._origin, glm::normalize(r0._forward / r1._forward));
	}
	inline ray_t operator/(const ray_t& r, const glm::vec4& v)
	{
		return ray_t(r._origin / v, glm::normalize(r._forward / glm::vec3(v)));
	}
	inline ray_t operator/(const glm::vec4& v, const ray_t& r)
	{
		return ray_t(v / r._origin, glm::normalize(glm::vec3(v) / r._forward));
	}
	inline ray_t operator/(const ray_t& r, const glm::vec3& v)
	{
		return ray_t(r._origin / glm::vec4(v, 1.0f), glm::normalize(r._forward / v));
	}
	inline ray_t operator/(const glm::vec3& v, const ray_t& r)
	{
		return ray_t(glm::vec4(v, 1.0f) / r._origin, glm::normalize(v / r._forward));
	}
	inline ray_t operator/(const ray_t& r, const float v)
	{
		return ray_t(r._origin / v, glm::normalize(r._forward / v));
	}
	inline ray_t operator/(const float v, const ray_t& r)
	{
		return ray_t(v / r._origin, glm::normalize(v / r._forward));
	}
	
	/// <summary>
	/// Contains methods and properties for an object's transformation.
	/// </summary>
	struct transform_t
	{
		
		inline transform_t() :
			_position(0.0f, 0.0f, 0.0f, 1.0f),
			_forward(0.0f, 0.0f, 1.0f),
			_right(1.0f, 0.0f, 0.0f),
			_up(0.0f, 1.0f, 0.0f),
			_scale(1.0f, 1.0f, 1.0f) {}
		/// <param name="position">4 dimensional vector representing the position of the transformation.</param>
		/// <param name="forward">3 dimensional vector representing the forward direction of the transformation.</param>
		/// <param name="right">3 dimensional vector representing the left and right direction of the transformation.</param>
		/// <param name="up">3 dimensional vector representing the up and down direction of the transformation.</param>
		/// <param name="scale">3 dimensional vector representing the scale of the transformation.</param>
		inline transform_t(
			const glm::vec4& position,
			const glm::vec3& forward,
			const glm::vec3& right,
			const glm::vec3& up,
			const glm::vec3& scale) :
			_position(position),
			_forward(forward),
			_right(right),
			_up(up),
			_scale(scale),
			_translation(glm::scale(scale) * glm::translate(glm::vec3(position))),
			_space(glm::vec4(right, 0.0f), glm::vec4(forward, 0.0f), glm::vec4(up, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) {}
		/// <param name="translation">4 dimensional matrix representing the position and scale of the transformation.</param>
		/// <param name="space">4 dimensional matrix representing the transformation space of the transformation.</param>
		inline transform_t(const glm::mat4& translation, const glm::mat4& space) :
			_position(translation * (space * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))),
			_forward(glm::vec3(translation * (space * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)))),
			_right(glm::vec3(translation * (space * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)))),
			_up(glm::vec3(translation * (space * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)))),
			_scale(glm::mat3(space) * glm::vec3(1.0f, 1.0f, 1.0f)),
			_translation(translation),
			_space(space) {}
		inline ~transform_t() {}
		
		/// <summary>
		/// Maps the given 4 dimensional vector in relation to the transform's position, orientation, and scale.
		/// </summary>
		inline glm::vec4 map(const glm::vec4& v) const
		{
			return (this->_translation * (this->_space * v));
		}
		
		/// <summary>
		/// Maps the given 3 dimensional vector in relation to the transform's position, orientation, and scale.
		/// </summary>
		inline glm::vec3 map(const glm::vec3& v) const
		{
			return glm::vec3(this->_translation * (this->_space * glm::vec4(v, 0.0f)));
		}
		
		/// <summary>
		/// Position of the transformation.
		/// </summary>
		glm::vec4 _position;
		/// <summary>
		/// Forward directional vector of the transformation.
		/// </summary>
		glm::vec3 _forward;
		/// <summary>
		/// Right directional vector of the transformation.
		/// </summary>
		glm::vec3 _right;
		/// <summary>
		/// Up directional vector of the transformation.
		/// </summary>
		glm::vec3 _up;
		/// <summary>
		/// Scale of the transformation.
		/// </summary>
		glm::vec3 _scale;
		/// <summary>
		/// Translating and scale matrix of the transformation.
		/// </summary>
		glm::mat4 _translation;
		/// <summary>
		/// Rotational space matrix of the transformation.
		/// </summary>
		glm::mat4 _space;
		
	};
	
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
			_diffuse(diffuse, diffuse, diffuse, 1.0f),
			_specular(specular, specular, specular, 1.0f) {}
		inline ~lumination_t() {}
		
		/// <summary>
		/// Flattens the lumination colors into single color channel.
		/// </summary>
		/// <returns>4 dimensional vector representing a color (R, G, B, A).</returns>
		inline glm::vec4 flatten() const
		{
			return glm::max(this->_diffuse + ((glm::vec4(1.0f) - this->_diffuse) * this->_specular), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		}
		
		inline lumination_t operator+() const
		{
			return lumination_t(+this->_diffuse, +this->_specular);
		}
		inline lumination_t operator-() const
		{
			return lumination_t(-this->_diffuse, -this->_specular);
		}
		inline lumination_t& operator+=(const lumination_t& other)
		{
			this->_diffuse += other._diffuse;
			this->_specular += other._specular;
			return *this;
		}
		inline lumination_t& operator+=(const glm::vec4& v)
		{
			this->_diffuse += v;
			this->_specular += v;
			return *this;
		}
		inline lumination_t& operator+=(const float v)
		{
			this->_diffuse += v;
			this->_specular += v;
			return *this;
		}
		inline lumination_t& operator-=(const lumination_t& other)
		{
			this->_diffuse -= other._diffuse;
			this->_specular -= other._specular;
			return *this;
		}
		inline lumination_t& operator-=(const glm::vec4& v)
		{
			this->_diffuse -= v;
			this->_specular -= v;
			return *this;
		}
		inline lumination_t& operator-=(const float v)
		{
			this->_diffuse -= v;
			this->_specular -= v;
			return *this;
		}
		inline lumination_t& operator*=(const lumination_t& other)
		{
			this->_diffuse *= other._diffuse;
			this->_specular *= other._specular;
			return *this;
		}
		inline lumination_t& operator*=(const glm::vec4& v)
		{
			this->_diffuse *= v;
			this->_specular *= v;
			return *this;
		}
		inline lumination_t& operator*=(const float v)
		{
			this->_diffuse *= v;
			this->_specular *= v;
			return *this;
		}
		inline lumination_t& operator/=(const lumination_t& other)
		{
			this->_diffuse /= other._diffuse;
			this->_specular /= other._specular;
			return *this;
		}
		inline lumination_t& operator/=(const glm::vec4& v)
		{
			this->_diffuse /= v;
			this->_specular /= v;
			return *this;
		}
		inline lumination_t& operator/=(const float v)
		{
			this->_diffuse /= v;
			this->_specular /= v;
			return *this;
		}
		
		/// <summary>
		/// Diffuse base color.
		/// </summary>
		glm::vec4 _diffuse;
		/// <summary>
		/// Specular highlight color.
		/// </summary>
		glm::vec4 _specular;
		
	};
	
	inline lumination_t operator+(const lumination_t& l0, const lumination_t& l1)
	{
	    return lumination_t(l0._diffuse + l1._diffuse, l0._specular + l1._specular);
	}
	inline lumination_t operator+(const lumination_t& l, const glm::vec4& v)
	{
	    return lumination_t(l._diffuse + v, l._specular + v);
	}
	inline lumination_t operator+(const glm::vec4& v, const lumination_t& l)
	{
	    return lumination_t(v + l._diffuse, v + l._specular);
	}
	inline lumination_t operator+(const lumination_t& l, const float v)
	{
	    return lumination_t(l._diffuse + v, l._specular + v);
	}
	inline lumination_t operator+(const float v, const lumination_t& l)
	{
	    return lumination_t(v + l._diffuse, v + l._specular);
	}
	
	inline lumination_t operator-(const lumination_t& l0, const lumination_t& l1)
	{
	    return lumination_t(l0._diffuse - l1._diffuse, l0._specular - l1._specular);
	}
	inline lumination_t operator-(const lumination_t& l, const glm::vec4& v)
	{
	    return lumination_t(l._diffuse - v, l._specular - v);
	}
	inline lumination_t operator-(const glm::vec4& v, const lumination_t& l)
	{
	    return lumination_t(v - l._diffuse, v - l._specular);
	}
	inline lumination_t operator-(const lumination_t& l, const float v)
	{
	    return lumination_t(l._diffuse - v, l._specular - v);
	}
	inline lumination_t operator-(const float v, const lumination_t& l)
	{
	    return lumination_t(v - l._diffuse, v - l._specular);
	}
	
	inline lumination_t operator*(const lumination_t& l0, const lumination_t& l1)
	{
	    return lumination_t(l0._diffuse * l1._diffuse, l0._specular * l1._specular);
	}
	inline lumination_t operator*(const lumination_t& l, const glm::vec4& v)
	{
	    return lumination_t(l._diffuse * v, l._specular * v);
	}
	inline lumination_t operator*(const glm::vec4& v, const lumination_t& l)
	{
	    return lumination_t(v * l._diffuse, v * l._specular);
	}
	inline lumination_t operator*(const lumination_t& l, const float v)
	{
	    return lumination_t(l._diffuse * v, l._specular * v);
	}
	inline lumination_t operator*(const float v, const lumination_t& l)
	{
	    return lumination_t(v * l._diffuse, v * l._specular);
	}
	
	inline lumination_t operator/(const lumination_t& l0, const lumination_t& l1)
	{
	    return lumination_t(l0._diffuse / l1._diffuse, l0._specular / l1._specular);
	}
	inline lumination_t operator/(const lumination_t& l, const glm::vec4& v)
	{
	    return lumination_t(l._diffuse / v, l._specular / v);
	}
	inline lumination_t operator/(const glm::vec4& v, const lumination_t& l)
	{
	    return lumination_t(v / l._diffuse, v / l._specular);
	}
	inline lumination_t operator/(const lumination_t& l, const float v)
	{
	    return lumination_t(l._diffuse / v, l._specular / v);
	}
	inline lumination_t operator/(const float v, const lumination_t& l)
	{
	    return lumination_t(v / l._diffuse, v / l._specular);
	}
	
	/// <summary>
	/// Contains methods and properties for the result of a ray hitting a shape.
	/// </summary>
	struct rayhit_t
	{
		
		inline rayhit_t() :
			_distance(-1.0f),
			_intersection(0.0f, 0.0f, 0.0f, 1.0) {}
		/// <param name="ray">Ray that caused the hit.</param>
		/// <param name="distance">Distance from the ray origin to the intersection.</param>
		/// <param name="intersection">Intersection point where the hit occured.</param>
		/// <param name="texcoord">Texture coordinate on the shape where the hit occured.</param>
		/// <param name="normal">Surface normal on the shape where the hit occured.</param>
		/// <param name="tangent">Surface tangent on the shape where the hit occured.</param>
		/// <param name="binormal">Surface binormal on the shape where the hit occured.</param>
		inline rayhit_t(
			const ray_t& ray,
			const float distance,
			const glm::vec4& intersection) :
			_ray(ray),
			_distance(distance),
			_intersection(intersection) {}
		inline ~rayhit_t() {}
		
		/// <summary>
		/// Gets a value indicating whether or not the hit is empty.
		/// </summary>
		inline bool empty() const { return this->_distance < 0.0f; }
		
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
		
	};
	
	/// <summary>
	/// Contains methods and properties for the calculated surface data for a point in space.
	/// </summary>
	struct fragment_t
	{
		
		inline fragment_t() :
			_material(0),
			_position(0.0f),
			_texcoord(0.0f),
			_space(1.0f),
			_normal(0.0f, 0.0f, 1.0f),
			_tangent(1.0f, 0.0f, 0.0f),
			_binormal(0.0f, 1.0f, 0.0f),
			_view(0.0f, 0.0f, 1.0f),
			_transparency(0.0f),
			_reflectivity(1.0f),
			_color(1.0f, 0.0f, 1.0f, 1.0f),
			_specular(0.0f),
			_emissive(0.0f) {}
		/// <param name="material">Surface's material.</param>
		/// <param name="position">Position of the surface fragment.</param>
		/// <param name="texcoord">Texture coordinate of the surface fragment.</param>
		/// <param name="normal">Surface normal of the fragment.</param>
		/// <param name="tangent">Surface tangent of the fragment.</param>
		/// <param name="binormal">Surface binormal of the fragment.</param>
		/// <param name="view">View direction of the surface fragment.</param>
		/// <param name="transparency">Transparency value of the surface fragment.</param>
		/// <param name="reflectivity">Reflectivity value of the surface fragment.</param>
		/// <param name="color">Base color of the surface fragment.</param>
		/// <param name="specular">Specular color of the surface fragment.</param>
		/// <param name="emissive">Emissive color of the surface fragment.</param>
		inline fragment_t(
			material_t* material,
			const glm::vec4& position,
			const glm::vec2& texcoord,
			const glm::vec3& normal,
			const glm::vec3& tangent,
			const glm::vec3& binormal,
			const glm::vec3& view,
			const float transparency,
			const float reflectivity,
			const glm::vec4& color,
			const glm::vec4& specular,
			const glm::vec4& emissive) :
			_material(material),
			_position(position),
			_texcoord(texcoord),
			_space(tangent, binormal, normal),
			_normal(normal),
			_tangent(tangent),
			_binormal(binormal),
			_view(view),
			_transparency(transparency),
			_reflectivity(reflectivity),
			_color(color),
			_specular(specular),
			_emissive(emissive) {}
		inline ~fragment_t() {}
		
		/// <summary>
		/// Bounces the given ray off of the fragment position and surface normal.
		/// </summary>
		/// <returns>Transformed ray that has been reflected.</returns>
		inline ray_t reflect(const ray_t& ray) { return ray_t(this->_position, glm::reflect(-ray._forward, this->_normal)); }
		
		/// <summary>
		/// Surface's material.
		/// </summary>
		material_t const * _material;
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
		/// Surface normal at the position.
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
	
	/// <summary>
	/// Contains methods and properties for the calculated lighting data used for shading a surface fragment.
	/// </summary>
	struct lighting_t
	{
		
		inline lighting_t() :
			_direction(0.0f, 0.0f, 1.0f),
			_color(1.0f),
			_attenuation(0.0f) {}
		/// <param name="position">3 dimensional vector representing the position of the light.</param>
		/// <param name="attenuation">Attenuation power of the light, must be zero to one value.</param>
		inline lighting_t(const glm::vec3& direction, const float attenuation) :
			_direction(direction),
			_color(1.0f),
			_attenuation(std::min(std::max(attenuation, 0.0f), 1.0f)) {}
		/// <param name="position">3 dimensional vector representing the position of the light.</param>
		/// <param name="color">4 dimensional vector representing the color of the light.</param>
		/// <param name="attenuation">Attenuation power of the light, must be zero to one value.</param>
		inline lighting_t(const glm::vec3& direction, const glm::vec4& color, const float attenuation) :
			_direction(direction),
			_color(color),
			_attenuation(std::min(std::max(attenuation, 0.0f), 1.0f)) {}
		inline ~lighting_t() {}
		
		/// <summary>
		/// Direction of the lighting.
		/// </summary>
		glm::vec3 _direction;
		/// <summary>
		/// Color of the lighting.
		/// </summary>
		glm::vec4 _color;
		/// <summary>
		/// Attenuation power of the lighting must be zero to one.
		/// </summary>
		float _attenuation;
		
	};
	
}