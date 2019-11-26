#include "bigint.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
void BigIntegerTest() {
	bigint a, b, c, d;
	bigint A;
	while (cin >> a >> b) {
		A = a / b;
		cout << A << '\n';
	}
}
int main() {
	BigIntegerTest();
	/*BigIntNerualNet nn;
	nn.InitNN();
	nn.FeedForward();
	nn.ShowResult();
	*/
	_CrtDumpMemoryLeaks();
	return 0;
}
