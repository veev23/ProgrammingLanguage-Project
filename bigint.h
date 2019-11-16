#pragma once
#ifndef BIGINT_H
#include <iostream>
class bigint{
private:
	//���� : -1, 0 : 0, ��� : 1
	int sign;
	int len;
	int* digit;
	//�Ʒ� operation�� ���밪������ �����
	//a>b�� ���� �ʿ�
	friend bigint add(bigint a, bigint b);
	//a>b�� ���� �ʿ�
	friend bigint sub(bigint a, bigint b);
	friend bigint mul(bigint a, bigint b);
	friend bigint div(bigint a, bigint b, bigint& remain);
	//���� ��
	void left_shift(int);
public:
	~bigint();
	bigint();
	//��� �迭�� bigint�� ��ȯ.
	bigint(int* arr, int size);
	//int�� bigint�� ��ȯ�ؼ� ����
	bigint(long long);
//	friend ostream& operator<<(ostream&, const bigint&);
	void print();
	bigint& operator=(const bigint&);
	friend bigint operator+(const bigint, const bigint);
	friend bigint operator-(const bigint, const bigint);
	friend bigint operator*(const bigint, const bigint);
	friend bigint operator/(const bigint, const bigint);
	friend bigint operator%(const bigint, const bigint);
	int at(int);
	int at(int) const;
	int get_sign() const;
	int get_len() const;
};
#endif