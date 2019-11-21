#pragma once
#ifndef BIGINT_H
#define BIGINT_H
class bigint{
private:
	//음수 : -1, 0 : 0, 양수 : 1
	int sign;
	int len;
	int* digit;
	//아래 operation은 절대값끼리의 계산임
	//a>b인 조건 필요
	friend bigint add(bigint a, bigint b);
	//a>b인 조건 필요
	friend bigint sub(bigint a, bigint b);
	friend bigint mul(bigint a, bigint b);
	friend bigint div(bigint a, bigint b, bigint& remain);
	//진수 배
	void left_shift(int);
	//진수 배만큼 나눔
	void right_shift(int);

	friend int cmp(const bigint&, const bigint&);
	int at(int);
	int at(int) const;
	int get_sign() const;
	int get_len() const;
public:
	~bigint();
	bigint();
	bigint(const bigint&);
	//양수 배열을 bigint로 변환.
	bigint(int* arr, int size);
	//int를 bigint로 변환해서 저장
	bigint(long long);
	void print();
	bigint& operator=(const bigint&);
	friend bigint operator+(const bigint&, const bigint&);
	friend bigint operator-(const bigint&, const bigint&);
	friend bigint operator*(const bigint&, const bigint&);
	friend bigint operator/(const bigint&, const bigint&);
	friend bigint operator%(const bigint&, const bigint&);
};
#endif