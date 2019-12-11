#include "bigint.h"
#define JINSU 10
//앞이 크면 1, 같으면 0, 뒤가 크면 -1
int cmp(const bigint& a, const bigint& b) {
	if (a.get_len() != b.get_len()) {
		if (a.get_len() > b.get_len()) return 1;
		else return -1;
	}
	for (int i = a.get_len() - 1; i >= 0; i--) {
		if (a.digit[i] > b.digit[i]) return 1;
		else if (a.digit[i] < b.digit[i]) return -1;
	}
	return 0;
}
void bigint::set_number(int num) {
	int arr[20], iter = 0;
	while (num > 0) {
		arr[iter++] = num % JINSU;
		num /= JINSU;
	}
	//0인 경우
	if (iter == 0) {
		*this = bigint();
	}
	else {
		this->len = iter;
		this->sign = 1;
		this->digit = new int[iter];
		for (int i = 0; i < iter; i++) {
			digit[i] = arr[i];
		}
	}
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
	this->digit = new int[1];
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
bigint::bigint(int num) {
	this->set_number(num);
};
bigint::bigint(const bigint& tmp) {
	this->len = tmp.get_len();
	this->sign = tmp.get_sign();
	this->digit = new int[tmp.get_len()];
	for (int i = 0; i < tmp.get_len(); i++) {
		this->digit[i] = tmp.digit[i];
	}
}
bigint& bigint::operator=(const bigint& tmp) {
	if (this == &tmp) {
		return *this;
	}
	this->len = tmp.get_len();
	this->sign = tmp.get_sign();
	delete[] this->digit;
	this->digit = new int[tmp.get_len()];
	for (int i = 0; i < tmp.get_len(); i++) {
		this->digit[i] = tmp.digit[i];
	}
	return *this;
};

bigint add(const bigint& a, const bigint& b) {
	if (b.get_sign() == 0) return a;
	if (a.get_sign() == 0) return b;
	int a_len = a.get_len();
	int b_len = b.get_len();
	int* tmp = new int[a_len + 1];
	int carry = 0;
	//작은 길이만큼 덧셈
	for (int i = 0; i < b_len; i++) {
		tmp[i] = a.digit[i] + b.digit[i] + carry;
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
		tmp[i] = a.digit[i] + carry;
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
	bigint result(tmp, result_len);
	delete[] tmp;
	return result;
};
bigint sub(const bigint& a, const bigint& b) {
	if (b.get_sign() == 0) {
		return a; //빼는 수가 0일 경우
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
		tmp[i] = a.digit[i] - b.digit[i] - carry;
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
		tmp[i] = a.digit[i] - carry;
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
	bigint result(tmp, result_len + 1);
	delete[] tmp;
	return result;
};
bigint mul(const bigint& a, const bigint& b) {
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
			tmp[ai + bi] += a.digit[ai] * b.digit[bi];
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
	bigint result(tmp, result_len + 1);
	delete[] tmp;
	return result;
}
bigint div(bigint a, bigint b, bigint& remain) {
	int diff = a.get_len() - b.get_len();
	//a<b거나 0인 경우 0 반환 
	if (cmp(a,b) < 0|| b.get_sign() == 0) {
		remain = a;
		return 0;
	}
	b.left_shift(diff);
	int* q_arr = new int[diff + 1];

	bigint tmp = b;
	for (int i = 0; i <= diff; i++) {
		q_arr[diff - i] = 0;
		for (int j = 1; j <= JINSU; j++) {
			if (cmp(a, tmp) != -1) {
				a = a - tmp;
				q_arr[diff - i] = j;
			}
			else {
				break;
			}
		}
		tmp.right_shift(1);
	}
	//쓰지 않는 자리 정리
	int result_len;
	for (result_len = diff; result_len >= 0; result_len--) {
		if (q_arr[result_len]) break;
	}
	bigint result(q_arr, result_len + 1);
	remain = a;
	delete[] q_arr;
	return result;
}
bigint operator+(const bigint& a, const bigint& b) {
	if (a.get_len() < b.get_len()) {
		return add(b, a);
	}
	return add(a, b);
};
bigint& bigint::operator+=(const bigint& op) {
	*this = *this + op;
	return *this;
}
bigint operator-(const bigint& a, const bigint& b) {
	return sub(a, b);
};
bigint operator*(const bigint& a, const bigint& b) {
	return mul(a, b);
};
bigint operator/(const bigint& a, const bigint& b) {
	bigint dummy;
	return div(a, b, dummy);
};
bigint operator%(const bigint& a, const bigint& b) {
	bigint remain;
	div(a, b, remain);
	return remain;
};
void bigint::left_shift(int n) {
	int len = this->get_len() + n;
	int* tmp = new int[len];
	int i;
	for (i = n; i < len; i++) {
		tmp[i] = this->digit[i - n];
	}
	for (i = 0; i < n; i++) {
		tmp[i] = 0;
	}
	bigint b(tmp, len);
	*this = b;
	delete[] tmp;
}
void bigint::right_shift(int n) {
	int len = this->get_len() - n;
	if (len < 1) {
		*this = 0;
		return;
	}
	int* tmp = new int[len];
	for (int i = 0; i < len; i++) {
		tmp[i] = this->digit[i + n];
	}
	bigint b(tmp, len);
	*this = b;
	delete[] tmp;
}
int bigint::get_sign() const {
	return this->sign;
}
int bigint::get_len() const {
	return this->len;
}
ostream& operator<<(ostream& os, const bigint& num) {
	for (int i = num.get_len() - 1; i >= 0; i--) {
		os << num.digit[i];
	}
	return os;
}
istream& operator>>(istream& os, bigint& num) {
	int input;
	os >> input;
	num.set_number(input);
	return os;
}
void bigint::BigIntegerTest1(int op1, int op2) {
	bigint a(op1), b(op2);
	cout << "BIGINT TEST 1\n";
	cout << a << '+' << b << '=' << a + b << '\n';
	cout << a << '*' << b << '=' << a * b << '\n';
	cout << a << '/' << b << '=' << a / b << '\n';
	cout << a << '%' << b << '=' << a % b << '\n';
}
void bigint::BigIntegerTest2(string path) {
	bigint result;
	bigint input[10000];
	int idx = 0;
	ifstream input_stream(path);
	while (input_stream >> input[idx++]);
	for (int i = 0; i < idx/2; i++) {
		result += input[i] * input[i + idx / 2];
	}
	cout << "BIGINT TEST 2\n";
	cout << result << '\n';
}