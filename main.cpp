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
	TestFFAlgorithm()�� ȣ������ ������ random number�� ����, ������ BigIntNeraulNet.cpp���� ���� ����
	TestFFAlgorithm(���ϸ�)�� ȣ���ϸ� �ش� ���Ͽ��� �о����
	*/
	nn.TestFFAlgorithm("FFTestFile.txt");
	nn.InitNN();
	nn.FeedForward();
	nn.ShowResult();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}
