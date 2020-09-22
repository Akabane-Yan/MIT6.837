#ifndef _ORTHOGRAPHICCAMERA_H_
#define _ORTHOGRAPHICCAMERA_H_

#include <assert.h>

#include "camera.h"

class OrthographicCamera : public Camera{

public:

	OrthographicCamera(Vec3f c, Vec3f d, Vec3f u, float s) {
		cent = c;
		d.Normalize();
		der = d;
		Vec3f h;
		Vec3f::Cross3(h, d, u); //Differ from Java?
		h.Normalize();
		hor = h;
		if (u.Dot3(d) == 0) {
			up = u;
		}
		else {
			Vec3f::Cross3(h, der, hor);
			float cosv = h.Dot3(u) / (h.Length() * u.Length());
			if (cosv > 0) {
				h.Normalize();
				up = h;
			}
			else {
				Vec3f::Cross3(h, hor, der);
				h.Normalize();
				up = h;
			}
		}
		size = s;
	}

	virtual Ray generateRay(Vec2f point) {
		Vec3f Ro = cent - (size / 2) * (up + hor) + point.x() * size * hor + point.y() * size * up;
		return Ray(Ro, der);
	}

	virtual float getTMin() const {
		return -FLT_MAX; //TBD, and FLT_MIN is positive
	}

private:

	Vec3f cent;
	Vec3f der;
	Vec3f up;
	Vec3f hor;
	float size;


};


#endif

