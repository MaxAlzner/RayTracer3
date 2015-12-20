#pragma once

namespace ray
{

	class tracepath_t
	{
	public:

		inline tracepath_t() {}
		inline ~tracepath_t() {}

		const fragment_t fragment() const;

		traceable_t& operator=(const fragment_t& frag);

	protected:

		fragment_t _fragment;

	};

	class photo_t
	{
	public:

		inline photo_t() {}
		inline ~photo_t() {}

		bool empty() const;

		void resize(const size_t width, const size_t height);
		void release();

		IMAGETYPE* rasterize() const;

		tracepath_t& operator[](const size_t index);

	protected:

		tracepath_t* _buffer;
		size_t _width;
		size_t _height;
		size_t _reflectDepth;
		size_t _multiSample;

	};

}