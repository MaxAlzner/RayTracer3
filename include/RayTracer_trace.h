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
		inline camera_t(const shape_transformation& transform, const glm::vec2& aperture, const float focalDepth) :
			_p0(glm::vec3(transform.apply(glm::vec4(-aperture.x / 2.0f, -aperture.y / 2.0f, 0.0f, 0.0f)))),
			_u(glm::vec3(transform.apply(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)))),
			_v(glm::vec3(transform.apply(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f)))),
			_focal(glm::vec3(transform.apply(glm::vec4(0.0f, 0.0f, 0.0f, -focalDepth)))) {}
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
	struct tracestack_t
	{
		
		inline tracestack_t() {}
		inline ~tracestack_t() {}
		
		/// <summary>
		/// List of traceable objects.
		/// </summary>
		std::list<traceable_t*> _traceables;
		/// <summary>
		/// List of lights to illuminate the traceable objects.
		/// </summary>
		std::list<light_t*> _lights;
		// /// <summary>
		// /// Camera that will cast all traced rays.
		// /// </summary>
		// camera_t* _camera;
		
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
	
	/// <summary>
	/// Contains methods and properties the result of tracing a scene of traceable objects.
	/// </summary>
	class photo_t
	{
	public:

		inline photo_t() :
			_buffer(0),
			_width(0),
			_height(0),
			_reflectDepth(0),
			_multiSampleRate(0) {}
		/// <param name="width">Width of the photo.</param>
		/// <param name="height">Height of the photo.</param>
		/// <param name="reflectDepth">Reflection depth of the photo.</param>
		/// <param name="multiSampleRate">Multi sample rate of the photo.</param>
		inline photo_t(const size_t width, const size_t height, const size_t reflectDepth = 0, const size_t multiSampleRate = 0) :
			_buffer(0),
			_width(0),
			_height(0),
			_reflectDepth(reflectDepth),
			_multiSampleRate(multiSampleRate) { this->resize(width, height); }
		inline ~photo_t() { this->release(); }

		/// <summary>
		/// Gets a value indicating whether or not the photo is empty.
		/// </summary>
		bool empty() const;

		/// <summary>
		/// Resizes the buffer of trace paths.
		/// </summary>
		/// <param name="width">Width of the new buffer.</param>
		/// <param name="height">Height of the new buffer.</param>
		void resize(const size_t width, const size_t height);
		/// <summary>
		/// Frees the buffer.
		/// </summary>
		void release();
		
		/// <summary>
		/// Traces the stack of traceable objects and puts the resulting trace paths into the trace path buffer.
		/// </summary>
		/// <param name="stack">Stack of traceable objects.</param>
		/// <param name="camera">Camera from which the traced rays originate from.</param>
		void trace(const tracestack_t& stack, const camera_t& camera);

		/// <summary>
		/// Rasteries the buffer of traced paths into a image.
		/// </summary>
		/// <returns>An image object.</returns>
		IMAGETYPE* rasterize() const;

		/// <summary>
		/// Gets a trace path from the buffer by a 2 dimensional vector.
		/// </summary>
		/// <param name="coord">Coordinate inside of the buffer based on it's width and height.</param>
		tracepath_t& operator[](const glm::ivec2& coord) const;

	protected:

		/// <summary>
		/// Buffer of trace paths, allocated based on the width and height.
		/// </summary>
		tracepath_t* _buffer;
		/// <summary>
		/// Width of the trace path buffer.
		/// </summary>
		size_t _width;
		/// <summary>
		/// Height of the trace path buffer.
		/// </summary>
		size_t _height;
		/// <summary>
		/// How many times to reflect off of a traced surface.
		/// </summary>
		size_t _reflectDepth;
		/// <summary>
		/// How many ray to trace per pixel on a axis.
		/// </summary>
		size_t _multiSampleRate;

	};

}