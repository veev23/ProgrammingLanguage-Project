#include "bigint.h"
#include <iostream>
using namespace std;
int main() {
	long long int a, b;
	bigint A;
	while (cin >> a >> b) {
		A = a % b;
		A.print(); cout << '\n';
	}
	return 0;
}