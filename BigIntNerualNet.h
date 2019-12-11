#pragma once
#ifndef BIGINTNERUALNET_H
#define BIGINTNERUALNET_H
#include "bigint.h"
class BigIntNerualNet {
	bool test;
	int layer_cnt;
	//node_num[i] : ���̾� �� ��� ��
	int* node_num;
	//layer[i][j] : i��° ���̾�, j��° ���
	bigint **layers;
	//weight[l][i][j] : l��° ���̾�� l+1��° ���̾�� weight, i -> j
	bigint ***weight;
	void InitNNTest();
	void FeedForwardTest();
public:
	BigIntNerualNet();
	~BigIntNerualNet();
	void InitNN();
	void FeedForward();
	void ShowResult();
	void TestFFAlgorithm(string path);
	void TestFFAlgorithm();
};
#endif