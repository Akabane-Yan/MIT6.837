#ifndef _IFS_H_
#define _IFS_H_

#include "matrix.h"
#include "image.h"

class IFS {
	
public:

	IFS() {
		num = 0;
		chan = NULL;
		tran = NULL;
	}
	IFS(const char *filename) {
		Input(filename);
	}
	~IFS() {
		delete[] chan;
		delete[] tran;
	}

	void Input(const char *filename);
	void Once(Vec4f *vec, int len);
	void Render(Image &ima, int cnt, int tim);

private:

	int num;
	float *chan;
	Matrix *tran;

};




#endif
