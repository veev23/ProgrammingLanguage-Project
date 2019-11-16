#include "bigint.h"
#include <algorithm>
using namespace std;
#define JINSU 10
//앞이 크면 1, 같으면 0, 뒤가 크면 -1
int cmp(const bigint a, const bigint b){
	if (a.get_len() != b.get_len()) {
		if (a.get_len() > b.get_len()) return 1;
		else return -1;
	}
	for (int i = 0; i < a.get_len(); i++) {
		if (a.at(i) > b.at(i)) return 1;
		else if (a.at(i) < b.at(i)) return -1;
	}
	return 0;
}
bigint::~bigint() {
	delete[] digit;
}
/*
일의자리가 index 0에 위치
*/
bigint::bigint() {
	this->len = 1;
	this->sign = 0;
	this->digit = new int;
	digit[0] = 0;
}
bigint::bigint(int* arr, int sz) {
	this->len = sz;
	this->sign = 1;
	this->digit = new int[sz];
	for (int i = 0; i < sz; i++) {
		digit[i] = arr[i];
	}
}
bigint::bigint(long long num) {
	int arr[20], iter=0;
	while (num > 0) {
		arr[iter++] = num % 10;
		num /= 10;
	}
	//0인 경우
	if (iter == 0) {
		iter = 1;
		arr[0] = 0;
		this->len = 1;
		this->sign = 0;
	}
	else {
		this->len = iter;
		this->sign = 1;
	}
	this->digit = new int[iter];
	for (int i = 0; i < iter; i++) {
		digit[i] = arr[i];
	}
};

void bigint::print(){
	for (int i = this->get_len()-1; i >= 0; i--) {
		cout << this->at(i);
	}
}
bigint& bigint::operator=(const bigint& tmp) {
	this->len = tmp.get_len();
	this->sign = tmp.get_sign();
	this->digit = new int[tmp.get_len()];
	for (int i = 0; i < tmp.get_len(); i++) {
		this->digit[i] = tmp.at(i);
	}
	return *this;
};

bigint add(bigint a, bigint b) {
	if (b.get_sign() == 0) return a;
	if (a.get_sign() == 0) return b;
	int a_len = a.get_len();
	int b_len = b.get_len();
	int* tmp = new int[a_len + 1];
	int carry = 0;
	//작은 길이만큼 덧셈
	for (int i = 0; i < b_len; i++) {
		tmp[i] = a.at(i) + b.at(i) + carry;
		if (tmp[i] < JINSU) {
			carry = 0;
		}
		else {
			tmp[i] -= JINSU;
			carry = 1;
		}
	}
	//나머지 길이만큼 대입+캐리
	for (int i = b_len; i < a_len; i++) {
		tmp[i] = a.at(i) + carry;
		if (tmp[i] < JINSU) {
			carry = 0;
		}
		else {
			tmp[i] -= JINSU;
			carry = 1;
		}
	}
	int result_len;
	if (carry) {
		tmp[a_len] = 1;
		result_len = a_len + 1;
	}
	else {
		result_len = a_len;
	}
	delete[] tmp;
	bigint result(tmp, result_len);
	return result;
};
bigint sub(bigint a, bigint b) {
	if (b.get_sign() == 0) {
		return 0; //빼는 수가 0일 경우
	}
	if (cmp(a, b) == 0) {
		return 0; //두 수가 같은 경우
	}
	int a_len = a.get_len();
	int b_len = b.get_len();
	int* tmp = new int[a_len];
	int carry = 0;
	//작은 길이만큼 뺄셈
	for (int i = 0; i < b_len; i++) {
		tmp[i] = a.at(i) - b.at(i) - carry;
		if (tmp[i] >= 0) {
			carry = 0;
		}
		else {
			tmp[i] += JINSU;
			carry = 1;
		}
	}
	//나머지 길이만큼 대입+캐리
	for (int i = b_len; i < a_len; i++) {
		tmp[i] = a.at(i) - carry;
		if (tmp[i] >= 0) {
			carry = 0;
		}
		else {
			tmp[i] += JINSU;
			carry = 1;
		}
	}
	//쓰지 않는 자리 정리
	int result_len;
	for (result_len = a_len - 1; result_len >= 0; result_len--) {
		if (tmp[result_len]) break;
	}
	delete[] tmp;
	bigint result(tmp, result_len+1);
	return result;
};
bigint mul(bigint a, bigint b) {
	if (a.get_sign() == 0 || b.get_sign() == 0) {
		return 0;
	}
	const int a_len = a.get_len();
	const int b_len = b.get_len();
	const int len = a_len + b_len;
	int* tmp = new int[len];
	for (int i = 0; i < len; i++) tmp[i] = 0;

	//자리수 별로 곱셈
	for (int ai = 0; ai < a_len; ai++) {
		for (int bi = 0; bi < b_len; bi++) {
			tmp[ai + bi] += a.at(ai) * b.at(bi);
		}
	}

	//JINSU값 이상을 떨구고 캐리
	int carry = 0;
	for (int i = 0; i < len; i++) {
		tmp[i] += carry;
		if (tmp[i] < JINSU) {
			carry = 0;
			continue;
		}
		carry = tmp[i] / JINSU;
		tmp[i] = tmp[i] % JINSU;
	}
	//쓰지 않는 자리 정리
	int result_len;
	for (result_len = len - 1; result_len >= 0; result_len--) {
		if (tmp[result_len]) break;
	}
	delete[] tmp;
	bigint result(tmp, result_len + 1);
	return result;
}
bigint div(bigint a, bigint b, bigint& remain) {
	int diff = a.get_len() - b.get_len();
	//a>b거나 0인 경우 0 반환 
	if (diff < 0 || b.get_sign() == 0) {
		remain = a;
		return 0;
	}
	b.left_shift(diff);
	int* q_arr = new int[diff];
	for(int i =1; i<=diff; i++){
		bigint tmp = b;
		for (int j = 0; j < JINSU; j++) {
			if (cmp(a, tmp) == -1) {
				q_arr[diff - i] = j;
				break;
			}
			else {
				a = a - tmp;
			}
		}
	}
	bigint q(q_arr, diff);
	delete[] q_arr;
	return q;
}
bigint operator+(const bigint a, const bigint b) {
	if (a.get_len() < b.get_len()) {
		return add(b, a);
	}
	return add(a, b);
};
bigint operator-(const bigint a, const bigint b) {
	return sub(a, b);
};
bigint operator*(const bigint a, const bigint b) {
	return mul(a,b);
};
bigint operator/(const bigint a, const bigint b) {
	bigint dummy;
	return div(a, b, dummy);
};
bigint operator%(const bigint a, const bigint b) {
	bigint remain;
	div(a, b, remain);
	return remain;
};
void bigint::left_shift(int n) {
	int len = this->get_len() + n;
	int* tmp = new int[len];
	int i;
	for (i = 0; i < this->get_len(); i++) {
		tmp[i] = this->at(i);
	}
	for (; i < len; i++) {
		tmp[i] = 0;
	}
	bigint b(tmp, len);
	*this = b;
	delete[] tmp;
}
int bigint::at(int idx) {
	return this->digit[idx];
}
int bigint::at(int idx) const {
	return this->digit[idx];
}
int bigint::get_sign() const{
	return this->sign;
}
int bigint::get_len() const {
	return this->len;
}