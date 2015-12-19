#pragma once

namespace ray
{

	struct traceable_t
	{

		virtual bool hitbyray(const ray_t& ray, rayhit_t* hit) = 0;

	};

	class tracesphere_t : traceable_t
	{
	public:

		inline tracesphere_t() :
			_center(0.0f, 0.0f, 0.0f, 1.0f),
			_radius(0.0f) {}
		inline tracesphere_t(const glm::vec4& center, const glm::vec4::value_type radius) :
			_center(center),
			_radius(radius) {}
		inline ~tracesphere_t() {}

		bool hitbyray(const ray_t& ray, rayhit_t* hit);

	protected:

		glm::vec4 _center;
		glm::vec4::value_type _radius;

	};

	class traceaxiscube_t : traceable_t
	{
	public:

		inline traceaxiscube_t() :
			_p0(0.0f, 0.0f, 0.0f, 1.0f),
			_p1(0.0f, 0.0f, 0.0f, 1.0f) {}
		inline traceaxiscube_t(const glm::vec4& p0, const glm::vec4& p1) :
			_p0(glm::min(p0.x, p1.x), glm::min(p0.y, p1.y), glm::min(p0.z, p1.z), glm::min(p0.w, p1.w)),
			_p1(glm::max(p0.x, p1.x), glm::max(p0.y, p1.y), glm::max(p0.z, p1.z), glm::max(p0.w, p1.w)) {}
		inline traceaxiscube_t(const glm::vec4& center, const glm::vec4::value_type width, const glm::vec4::value_type height, const glm::vec4::value_type depth) :
			_p0(center - glm::vec4(width / 2.0f, height / 2.0f, depth / 2.0f, 0.0f)),
			_p1(center + glm::vec4(width / 2.0f, height / 2.0f, depth / 2.0f, 0.0f)) {}
		inline ~traceaxiscube_t() {}

		bool hitbyray(const ray_t& ray, rayhit_t* hit);

	protected:

		glm::vec4 _p0;
		glm::vec4 _p1;

	};

}