#include "bigint.h"
#include "BigIntNerualNet.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
int main() {
	bigint::BigIntegerTest1(2100000000, 2000000000);
	bigint::BigIntegerTest2("BigIntegerTestFile.txt");
	BigIntNerualNet nn;
	/*
	TestFFAlgorithm()을 호출하지 않으면 random number로 설정, 범위는 BigIntNeraulNet.cpp에서 설정 가능
	TestFFAlgorithm(파일명)을 호출하면 해당 파일에서 읽어들임
	*/
	nn.TestFFAlgorithm("FFTestFile.txt");
	nn.InitNN();
	nn.FeedForward();
	nn.ShowResult();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}
