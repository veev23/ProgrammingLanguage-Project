#pragma once
#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
using namespace std;
class bigint {
private:
	//���� : -1, 0 : 0, ��� : 1
	int sign;
	int len;
	int* digit;
	//�Ʒ� operation�� ���밪������ �����
	//a>b�� ���� �ʿ�
	friend bigint add(const bigint& a, const bigint& b);
	//a>b�� ���� �ʿ�
	friend bigint sub(const bigint& a, const bigint& b);
	friend bigint mul(const bigint& a, const bigint& b);
	friend bigint div(bigint a, bigint b, bigint& remain);
	//���� ��
	void left_shift(int);
	//���� �踸ŭ ����
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
	//��� �迭�� bigint�� ��ȯ.
	bigint(int* arr, int size);
	//int�� bigint�� ��ȯ�ؼ� ����
	bigint(int);
	bigint& operator=(const bigint&);
	friend bigint operator+(const bigint&, const bigint&);
	friend bigint operator-(const bigint&, const bigint&);
	friend bigint operator*(const bigint&, const bigint&);
	friend bigint operator/(const bigint&, const bigint&);
	friend bigint operator%(const bigint&, const bigint&);
	friend ostream& operator<<(ostream&, const bigint&);
};
#endif