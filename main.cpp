#include "bigint.h"
#include "BigIntNerualNet.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
int main() {
	bigint::BigIntegerTest1(2100000000, 2000000000);
	bigint::BigIntegerTest2("BigIntegerTestFile.txt");
	
	BigIntNerualNet nn;
	//input number
	nn.TestFFAlgorithm("FFTestFile.txt");
	nn.InitNN();
	nn.FeedForward();
	nn.ShowResult();
	
	_CrtDumpMemoryLeaks();
	return 0;
}
