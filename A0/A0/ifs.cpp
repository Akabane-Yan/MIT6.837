#include <assert.h>
#include <string.h>
#include "ifs.h"

void IFS::Input(const char *filename) {
	assert(filename != NULL);
	const char *ext = &filename[strlen(filename) - 4];
	assert(!strcmp(ext, ".txt"));
	FILE *file = fopen(filename, "r");
	fscanf(file, "%d", &num);
	chan = new float[num];
	tran = new Matrix[num];
	for (int i = 0; i < num; i++) {
		fscanf(file, "%f", chan + i);
		tran[i].Read3x3(file);
	}
	fclose(file);
}

void IFS::Once(Vec4f *vec, int len) {
	for (int i = 0; i < len; i++) {
		float f = rand() / (RAND_MAX + 1.0f), p = 0.0f;
		int ind = 0;
		for (; ind < num; ind++) {
			p += chan[ind];
			if (f <= p) break;
		}
		tran[ind].Transform(vec[i]);
	}
}

//If the Image paremeter is not reference, there will be sth wrong
//It may because there is no correct copy Constructor
void IFS::Render(Image &ima, int cnt, int tim) {
	int hei = ima.Height(), wid = ima.Width();
	Vec4f *vec = new Vec4f[cnt];
	float temxf, temyf;
	for (int i = 0; i < cnt; i++) {
		temxf = rand() / (RAND_MAX + 1.0f);
		temyf = rand() / (RAND_MAX + 1.0f);
		vec[i].Set(temxf, temyf, 0.0f, 1.0f);
	}
	for (int i = 0; i < tim; i++) {
		Once(vec, cnt);
	}

	Vec3f temp(1.0f, 1.0f, 1.0f);
	ima.SetAllPixels(temp);
	temp.Set(0.0f, 0.0f, 0.0f);

	int tempxi, tempyi;
	for (int i = 0; i < cnt; i++) {
		tempxi = (int)(vec[i].x() * wid);
		tempyi = (int)(vec[i].y() * hei);
		if (tempxi >= 0 && tempxi < wid && tempyi >= 0 && tempyi < hei) {
			ima.SetPixel(tempxi, tempyi, temp);
		}
	}

	delete[] vec;
}
