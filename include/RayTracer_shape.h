#pragma once

namespace ray
{

	/// <summary>
	/// Contains methods and properties for a shape that is traceable by a ray.
	/// </summary>
	struct traceable_t
	{

		/// <summary>
		/// Calculates whether or not the the shape is intersected by the given ray.
		/// </summary>
		/// <param name="ray">A ray to intersect with the shape.</param>
		/// <param name="hit">Pointer to a rayhit, if the ray does intersect with the object the calculated rayhit will be outputted here.</param>
		virtual bool hitbyray(const ray_t& ray, rayhit_t* hit) = 0;

	};

	/// <summary>
	/// Contains methods and properties for a traceable sphere.
	/// </summary>
	class tracesphere_t : public traceable_t
	{
	public:

		inline tracesphere_t() :
			_center(0.0f, 0.0f, 0.0f, 1.0f),
			_radius(0.0f) {}
		/// <param name="center">4 dimensional vector representing the center of the sphere.</param>
		/// <param name="radius">Radius of the sphere.</param>
		inline tracesphere_t(const glm::vec4& center, const glm::vec4::value_type radius) :
			_center(center),
			_radius(radius) {}
		inline ~tracesphere_t() {}

		/// <summary>
		/// Calculates whether or not the the shape is intersected by the given ray.
		/// </summary>
		/// <param name="ray">A ray to intersect with the shape.</param>
		/// <param name="hit">Pointer to a rayhit, if the ray does intersect with the object the calculated rayhit will be outputted here.</param>
		bool hitbyray(const ray_t& ray, rayhit_t* hit);

	protected:

		/// <summary>
		/// Center of the sphere.
		/// </summary>
		glm::vec4 _center;
		/// <summary>
		/// Radius of the sphere.
		/// </summary>
		glm::vec4::value_type _radius;

	};

	/// <summary>
	/// Contains methods and properties for a traceable axis-aligned cube.
	/// </summary>
	class traceaxiscube_t : traceable_t
	{
	public:

		inline traceaxiscube_t() :
			_p0(0.0f, 0.0f, 0.0f, 1.0f),
			_p1(0.0f, 0.0f, 0.0f, 1.0f) {}
		/// <param name="p0">4 dimensional vector representing the most minimum corner of the cube.</param>
		/// <param name="p1">4 dimensional vector representing the most maximum corner of the cube.</param>
		inline traceaxiscube_t(const glm::vec4& p0, const glm::vec4& p1) :
			_p0(glm::min(p0.x, p1.x), glm::min(p0.y, p1.y), glm::min(p0.z, p1.z), glm::min(p0.w, p1.w)),
			_p1(glm::max(p0.x, p1.x), glm::max(p0.y, p1.y), glm::max(p0.z, p1.z), glm::max(p0.w, p1.w)) {}
		/// <param name="center">4 dimensional vector representing the center of the cube.</param>
		/// <param name="width">Width of the cube.</param>
		/// <param name="height">Height of the cube.</param>
		inline traceaxiscube_t(const glm::vec4& center, const glm::vec4::value_type width, const glm::vec4::value_type height, const glm::vec4::value_type depth) :
			_p0(center - glm::vec4(width / 2.0f, height / 2.0f, depth / 2.0f, 0.0f)),
			_p1(center + glm::vec4(width / 2.0f, height / 2.0f, depth / 2.0f, 0.0f)) {}
		inline ~traceaxiscube_t() {}

		/// <summary>
		/// Calculates whether or not the the shape is intersected by the given ray.
		/// </summary>
		/// <param name="ray">A ray to intersect with the shape.</param>
		/// <param name="hit">Pointer to a rayhit, if the ray does intersect with the object the calculated rayhit will be outputted here.</param>
		bool hitbyray(const ray_t& ray, rayhit_t* hit);

	protected:

		/// <summary>
		/// Lowest corner of the cube.
		/// </summary>
		glm::vec4 _p0;
		/// <summary>
		/// Highest corner of the cube.
		/// </summary>
		glm::vec4 _p1;

	};

}