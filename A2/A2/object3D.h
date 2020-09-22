#ifndef _OBJECT3D_H_
#define	_OBJECT3D_H_

#include "material.h"
#include "ray.h"
#include "hit.h"

class Object3D {

public:

	Object3D() {
		mat = NULL;
	}
	Object3D(Material * m) {
		mat = m;
	}

	virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;

protected: // TBD

	Material * mat;

};



#endif // !_OBJECT3D_H

