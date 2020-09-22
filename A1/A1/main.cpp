#include "scene_parser.h"
#include "orthographiccamera.h" //without this sp cannot use generateRay
#include "hit.h"
#include "ray.h"
#include "group.h"
#include "image.h"

int main() {
	SceneParser sp("scene1_07.txt");

	int wid = 200, hei = 200;
	Image ima1(wid, hei), ima2(wid, hei);
	float delx = 1.0f / wid, dely = 1.0f / hei;

	float x, y, dmin = -2.0f, dmax = 2.0f, d;
	Vec2f temp;
	Ray ray;
	for (int i = 0; i < hei; i++) {
		y = dely * i;
		for (int j = 0; j < wid; j++) {
			x = delx * j;
			temp.Set(x, y);
			ray = sp.getCamera()->generateRay(temp);
			Hit hit;
			if (sp.getGroup()->intersect(ray, hit, sp.getCamera()->getTMin())) {
				ima1.SetPixel(j, i, hit.getMaterial()->getDiffuseColor());
				d = 1.0f - ((hit.getT() - dmin) / (dmax - dmin));
				if (d > 1.0f) ima2.SetPixel(j, i, Vec3f(1.0f, 1.0f, 1.0f));
				else if (d < 0.0f) ima2.SetPixel(j, i, Vec3f(0.0f, 0.0f, 0.0f));
				else ima2.SetPixel(j, i, Vec3f(d, d, d));
			}
			else
				ima1.SetPixel(j, i, sp.getBackgroundColor());
		}
	}

	ima1.SaveTGA("scene1_07.tga");
	ima2.SaveTGA("depth1_07.tga");
	return 0;
}