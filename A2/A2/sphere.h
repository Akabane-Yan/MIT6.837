#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <math.h>

#include "vectors.h"
#include "object3D.h"


class Sphere : public Object3D {

public:
	Sphere(Vec3f c, float r, Material *m) : Object3D(m) {
		cent = c;
		rad = r;
	}
	Sphere() {}

	virtual bool intersect(const Ray &r, Hit &h, float tmin) {
		Vec3f Rd = r.getDirection(), Ro = r.getOrigin();
		float a = Rd.Dot3(Rd);
		float b = 2 * (Ro.Dot3(Rd) - Rd.Dot3(cent));
		float c = Ro.Dot3(Ro) - 2 * Ro.Dot3(cent) + cent.Dot3(cent) - rad * rad;
		float del = b * b - 4 * a * c;
		if (del < 0) return false;
		else if (del == 0) {
			float t = -b / a;
			if (t > tmin && t < h.getT()) {
				h.set(t, mat, r);
				return true;
			}
			return false;
		}
		else {
			float sd = sqrt(del);
			float t1 = (-b - sd) / (2 * a), t2 = (-b + sd) / (2 * a);
			if (t1 > tmin && t1 < h.getT()) {
				h.set(t1, mat, r);
				return  true;
			}
			else if (t2 > tmin && t2 < h.getT()) {
				h.set(t2, mat, r);
				return true;
			}
			return false;
		}
	}

private:

	Vec3f cent;
	float rad;

};


#endif
