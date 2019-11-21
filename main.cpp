#define _CRT_SECURE_NO_WARNINGS
#include "bigint.h"
#include <iostream>
using namespace std;
int main() {
	long long int a, b;
	bigint A;
	while (cin >> a >> b) {
		A= bigint(a) / bigint(b);
		A.print(); 
		cout<< '\n';
	}
	return 0;
}
