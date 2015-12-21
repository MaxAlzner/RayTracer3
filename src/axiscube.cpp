
#include "../include/RayTracer.h"

namespace ray
{
	using namespace glm;

	bool traceaxiscube_t::hitbyray(const ray_t& ray, rayhit_t* hit)
	{
		float a = 1.0f / ray._forward.x;
		float b = 1.0f / ray._forward.y;
		float c = 1.0f / ray._forward.z;
		float txmin = a >= 0.0f ? (this->_p0.x - ray._origin.x) * a : (this->_p1.x - ray._origin.x) * a;
		float tymin = b >= 0.0f ? (this->_p0.y - ray._origin.y) * b : (this->_p1.y - ray._origin.y) * b;
		float tzmin = c >= 0.0f ? (this->_p0.z - ray._origin.z) * c : (this->_p1.z - ray._origin.z) * c;
		float txmax = a >= 0.0f ? (this->_p1.x - ray._origin.x) * a : (this->_p0.x - ray._origin.x) * a;
		float tymax = b >= 0.0f ? (this->_p1.y - ray._origin.y) * b : (this->_p0.y - ray._origin.y) * b;
		float tzmax = c >= 0.0f ? (this->_p1.z - ray._origin.z) * c : (this->_p0.z - ray._origin.z) * c;
		float t0 = txmin > tymin ? txmin : tymin;
		float t1 = txmax < tymax ? txmax : tymax;
		int facein = txmin > tymin ? ((a >= 0.0f) ? 0 : 3) : ((b >= 0.0f) ? 1 : 4);
		// int faceout = txmax < tymax ? ((a >= 0.0f) ? 3 : 0) : ((b >= 0.0f) ? 4 : 1);
		if (tzmin > t0)
		{
			t0 = tzmin;
			facein = (c >= 0.0f) ? 2 : 5;
		}

		if (tzmax < t1)
		{
			t1 = tzmax;
			// faceout = (c >= 0.0f) ? 5 : 2;
		}

		float kEpsilon = 1.0f;
		if (t0 < t1 && t1 > kEpsilon)
		{
			float t = t0 > kEpsilon ? t0 : t1;

			//if (t <= ray.length)
			//{
				vec4 intersection = ray._origin + vec4(ray._forward * t, 0.0f);
				float width = abs(this->_p1.x - this->_p0.x);
				float height = abs(this->_p1.y - this->_p0.y);
				float depth = abs(this->_p1.z - this->_p0.z);
				vec3 toInnerEdge(this->_p0 - intersection);
				vec3 toOuterEdge(this->_p1 - intersection);
				vec2 texcoord;
				vec3 normal;
				vec3 tangent;
				vec3 binormal;
				switch (facein)
				{
				case 0:
					texcoord = vec2(abs(toOuterEdge.z) / (depth), abs(toInnerEdge.y) / (height));
					normal = vec3(-1.0f, 0.0f, 0.0f);
					tangent = vec3(0.0f, 0.0f, -1.0f);
					binormal = vec3(0.0f, -1.0f, 0.0f);
					break;
				case 1:
					texcoord = vec2(abs(toInnerEdge.x) / (width), abs(toOuterEdge.z) / (depth));
					normal = vec3(0.0f, -1.0f, 0.0f);
					tangent = vec3(1.0f, 0.0f, 0.0f);
					binormal = vec3(0.0f, 0.0f, -1.0f);
					break;
				case 2:
					texcoord = vec2(abs(toInnerEdge.x) / (width), abs(toInnerEdge.y) / (height));
					normal = vec3(0.0f, 0.0f, -1.0f);
					tangent = vec3(1.0f, 0.0f, 0.0f);
					binormal = vec3(0.0f, -1.0f, 0.0f);
					break;
				case 3:
					texcoord = vec2(abs(toInnerEdge.z) / (depth), abs(toInnerEdge.y) / (height));
					normal = vec3(1.0f, 0.0f, 0.0f);
					tangent = vec3(0.0f, 0.0f, 1.0f);
					binormal = vec3(0.0f, 1.0f, 0.0f);
					break;
				case 4:
					texcoord = vec2(abs(toInnerEdge.x) / (width), abs(toInnerEdge.z) / (depth));
					normal = vec3(0.0f, 1.0f, 0.0f);
					tangent = vec3(1.0f, 0.0f, 0.0f);
					binormal = vec3(0.0f, 0.0f, 1.0f);
					break;
				case 5:
					texcoord = vec2(abs(toOuterEdge.x) / (width), abs(toInnerEdge.y) / (height));
					normal = vec3(0.0f, 0.0f, 1.0f);
					tangent = vec3(1.0f, 0.0f, 0.0f);
					binormal = vec3(0.0f, 1.0f, 0.0f);
					break;
				default:
					break;
				}

				if (dot(normal, ray._forward) < 0.0f)
				{
					if (hit != 0)
					{
						*hit = rayhit_t(
							ray,
							t,
							intersection,
							texcoord,
							normal,
							tangent,
							binormal);
					}

					return true;
				}
			//}
		}

		return false;
	}

}