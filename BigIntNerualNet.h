#pragma once
#ifndef BIGINTNERUALNET_H
#define BIGINTNERUALNET_H
#include "bigint.h"
class BigIntNerualNet {
	bool test;
	int layer_cnt;
	//node_num[i] : 레이어 별 노드 수
	int* node_num;
	//layer[i][j] : i번째 레이어, j번째 노드
	bigint **layers;
	//weight[l][i][j] : l번째 레이어에서 l+1번째 레이어간의 weight, i -> j
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