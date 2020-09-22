#include <fstream>
#include "matrix.h"
#include "ifs.h"

//The dragon photo is not perfect
int main() {

	IFS ifs("triangle.txt");
	Image ima(400, 400);
	ifs.Render(ima, 50000, 30);
	ima.SaveTGA("triangle.tga");
	
	return 0;
}