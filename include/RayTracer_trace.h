#pragma once

namespace ray
{

	/// <summary>
	/// Contains methods and properties for a camera that casts rays.
	/// </summary>
	class camera_t
	{
	public:
		
		inline camera_t() :
			_p0(0.0f, 0.0f, 0.0f),
			_u(0.0f, 0.0f, 0.0f),
			_v(0.0f, 0.0f, 0.0f),
			_focal(0.0f, 0.0f, 0.0f) {}
		/// <param name="aperture">2 dimensional vector representing the dimensions of the camera's viewport.</param>
		/// <param name="focalDepth">How far away the focal point is from the center of the viewport.</param>
		inline camera_t(const transform_t& transform, const glm::vec2& aperture, const float focalDepth) :
			_p0(glm::vec3(transform.map(glm::vec4(-aperture.x / 2.0f, -aperture.y / 2.0f, 0.0f, 1.0f)))),
			_u(glm::vec3(transform.map(glm::vec4(aperture.x, 0.0f, 0.0f, 0.0f)))),
			_v(glm::vec3(transform.map(glm::vec4(0.0f, aperture.y, 0.0f, 0.0f)))),
			_focal(glm::vec3(transform.map(glm::vec4(0.0f, 0.0f, -focalDepth, 1.0f)))) {}
		inline ~camera_t() {}
		
		/// <summary>
		/// Calculates a ray from the camera's viewport.
		/// </summary>
		/// <param name="coord">2 dimensional vector representing a point of the viewport.</param>
		/// <returns>Ray going out from the focal point at the specified point on the viewport.</returns>
		ray_t cast(const glm::vec2& coord) const;
		/// <summary>
		/// Calculates a ray from the camera's viewport.
		/// </summary>
		/// <param name="u">Point on the viewport's x-axis.</param>
		/// <param name="v">Point on the viewport's y-axis.</param>
		/// <returns>Ray going out from the focal point at the specified point on the viewport.</returns>
		ray_t cast(const float u, const float v) const;
		
	protected:
		
		/// <summary>
		/// Top-left corner of the camera's viewport.
		/// </summary>
		glm::vec3 _p0;
		/// <summary>
		/// X-axis directional vector of the camera's viewport.
		/// </summary>
		glm::vec3 _u;
		/// <summary>
		/// Y-axis directional vector of the camera's viewport.
		/// </summary>
		glm::vec3 _v;
		/// <summary>
		/// Focal point of the camera;
		/// </summary>
		glm::vec3 _focal;
		
	};
	
	/// <summary>
	/// Contains methods and properties for a stack of objects used in tracing a scene.
	/// </summary>
	class tracestack_t
	{
	public:
		
		inline tracestack_t() {}
		inline ~tracestack_t() {}

		/// <summary>
		/// Gets the traceable object that is nearest to the given ray.
		/// </summary>
		/// <param name="ray">Ray to trace to intersect with the stack of traceable objects.</param>
		/// <param name="hit">Pointer to a rayhit, if the ray does intersect with any of the stack of objects the calculated rayhit will be outputted here.</param>
		/// <returns>The nearest traceable object or null if no objects where hit.</returns>
		const traceable_t* nearest(const ray_t& ray, rayhit_t* hit = 0) const;
		/// <summary>
		/// Gets the traceable object that is farthest from the given ray.
		/// </summary>
		/// <param name="ray">Ray to trace to intersect with the stack of traceable objects.</param>
		/// <param name="hit">Pointer to a rayhit, if the ray does intersect with any of the stack of objects the calculated rayhit will be outputted here.</param>
		/// <returns>The farthest traceable object or null if no objects where hit.</returns>
		const traceable_t* farthest(const ray_t& ray, rayhit_t* hit = 0) const;
		
		/// <summary>
		/// List of traceable objects.
		/// </summary>
		std::list<traceable_t*> _traceables;
		/// <summary>
		/// List of lights to illuminate the traceable objects.
		/// </summary>
		std::list<light_t*> _lights;
		
	};

	/// <summary>
	/// Contains methods and properties for a link in the path that a ray has taken as it hits surfaces.
	/// </summary>
	class tracepath_t
	{
	public:

		inline tracepath_t() :
			_stack(0),
			_reflection(0),
			_passthrough(0) {}
		inline tracepath_t(const fragment_t& frag, const tracestack_t& stack, tracepath_t* reflection = 0, tracepath_t* passthrough = 0) :
			_fragment(frag),
			_stack((tracestack_t*)&stack),
			_reflection(reflection),
			_passthrough(passthrough) {}
		inline ~tracepath_t() { this->clear(); }
		
		/// <summary>
		/// Clears all linked path segments.
		/// </summary>
		void clear();
		
		/// <summary>
		/// Calculates the lumination for the trace path.
		/// </summary>
		/// <returns>Lumination value for the surface at this segment of the trace path.</returns>
		lumination_t albedo() const;

		/// <summary>
		/// Gets the fragment for this segment of the path.
		/// </summary>
		const fragment_t fragment() const;

		/// <summary>
		/// Sets this path segment to the given fragment.
		/// </summary>
		tracepath_t& operator=(const fragment_t& frag);

	protected:

		/// <summary>
		/// Path segment's surface fragment that has been hit by a ray.
		/// </summary>
		fragment_t _fragment;
		/// <summary>
		/// Stack of objects that are involved in the traced scene.
		/// </summary>
		tracestack_t* _stack;
		/// <summary>
		/// Path segment's next link that has been reflected off of this segment's fragment.
		/// </summary>
		tracepath_t* _reflection;
		/// <summary>
		/// Path segment's next link that has been passed through from this segment's fragment.
		/// </summary>
		tracepath_t* _passthrough;

	};
	
	enum MULTISAMPLETYPE
	{
		MULTISAMPLETYPE_SINGLE = 0x0001,
		MULTISAMPLETYPE_QUAD = 0x0002,
		MULTISAMPLETYPE_OCT = 0x0003,
		
		MULTISAMPLETYPE_EDGE = 0x0010,
		MULTISAMPLETYPE_RADIUS = 0x0020,
		MULTISAMPLETYPE_RANDOM = 0x0030
	};
	
	/// <summary>
	/// Contains methods and properties of an emitter that traces rays.
	/// </summary>
	class emitter_t
	{
	public:
		
		inline emitter_t() :
			_reflectDepth(0),
			_multiSample(MULTISAMPLETYPE_SINGLE | MULTISAMPLETYPE_EDGE) {}
		/// <param name="reflectDepth">Reflection depth of the photo.</param>
		/// <param name="multiSampleRate">Multi sample rate of the photo.</param>
		inline emitter_t(const size_t reflectDepth, const int multiSample) :
			_reflectDepth(reflectDepth),
			_multiSample(multiSample) {}
		inline ~emitter_t() {}
		
		void emit(const scene_t& scene, tracepath_t& path);
		
	protected:
		
		/// <summary>
		/// How many times to reflect off of a traced surface.
		/// </summary>
		size_t _reflectDepth;
		/// <summary>
		/// How many ray to trace per pixel on a axis.
		/// </summary>
		int _multiSample;
		
	};

}