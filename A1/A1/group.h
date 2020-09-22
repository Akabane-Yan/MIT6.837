#ifndef _GROUP_H_
#define _GROUP_H_

#include "object3D.h"

class Group : public Object3D {

public:

	Group(int n) { //TBD
		num = n;
		obj = new Object3D*[n];
	}
	~Group() { //TBD
		for (int i = 0; i < num; i++) {
			delete obj[i];
		}
		delete[] obj;
	}
	virtual bool intersect(const Ray &r, Hit &h, float tmin) {
		bool flag = false;
		for (int i = 0; i < num; i++) {
			flag |= obj[i]->intersect(r, h, tmin); //TBD
		}
		return flag;
	}
	void addObject(int index, Object3D *o) {
		obj[index] = o;
	}

private:

	int num;
	Object3D **obj; // TBD

};





#endif _GROUP_H_
