#include "sphere.h"

Vec3f getNormal(const Ray &r, float t, const Vec3f &c) {
	Vec3f normal = r.getOrigin() + r.getDirection() * t - c;
	normal.Normalize();
	return normal;
}


bool Sphere::intersect(const Ray &r, Hit &h, float tmin) {
	Vec3f Rd = r.getDirection(), Ro = r.getOrigin();
	float a = Rd.Dot3(Rd);
	float b = 2 * (Ro.Dot3(Rd) - Rd.Dot3(cent));
	float c = Ro.Dot3(Ro) - 2 * Ro.Dot3(cent) + cent.Dot3(cent) - rad * rad;
	float del = b * b - 4 * a * c;
	Vec3f temp;
	if (del < 0) return false;
	else if (del == 0) {
		float t = -b / a;
		if (t > tmin && t < h.getT()) {
			temp = getNormal(r, t, cent);
			h.set(t, mat, temp, r);
			return true;
		}
		return false;
	}
	else {
		float sd = sqrt(del);
		float t1 = (-b - sd) / (2 * a), t2 = (-b + sd) / (2 * a);
		if (t1 > tmin && t1 < h.getT()) {
			temp = getNormal(r, t1, cent);
			h.set(t1, mat, temp, r);
			return  true;
		}
		else if (t2 > tmin && t2 < h.getT()) {
			temp = getNormal(r, t2, cent);
			h.set(t2, mat, temp, r);
			return true;
		}
		return false;
	}
}