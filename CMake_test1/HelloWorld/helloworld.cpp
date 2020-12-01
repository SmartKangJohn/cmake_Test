// CMake_test1.cpp: 定义应用程序的入口点。
//

#include "helloworld.h"

#ifndef USE_MYMATH
#define USE_MYMATH 1
#endif // !USE_MYMATH


#ifdef USE_MYMATH
#include "../MyMathFunctions/MathFunctions.h"
#pragma comment(lib, "../../bulid/MyMathFunctions/Debug/MyMathFunctions.lib")
#endif

using namespace std;

int main()
{
	cout << "Hello World!" << endl;
	cout << "Hello CMake。" << endl;
	printf("current Version %d.%d\n", HELLOWORLD_VERSION_MAJOR, HELLOWORLD_VERSION_MINOR);

	double s1;
#ifdef USE_MYMATH
	s1 = mysqrt(9.);
#else
	s1 = 0.;
#endif
	printf("s1 = %f\n", s1);
	system("pause");
	return 0;
}
