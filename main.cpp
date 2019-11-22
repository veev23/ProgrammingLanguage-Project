#include "bigint.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
void BigIntegerTest() {
	int a, b, c, d;
	bigint A;
	while (cin >> a >> b) {
		A = bigint(a) + bigint(b);
		cout << A;
		cout << '\n';
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
