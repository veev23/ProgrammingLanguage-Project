#include "BigIntNerualNet.h"

BigIntNerualNet::BigIntNerualNet() {
	cout << "레이어 수를 입력하세요.\n";
	cin >> layer_cnt;
	layers = new bigint*[layer_cnt];
	node_num = new int[layer_cnt];
	weight = new bigint**[layer_cnt - 1];
	cout << "각 레이어별 노드 수를 입력하세요.\n";
	for (int i = 0; i < layer_cnt; i++) {
		cin >> node_num[i];
		layers[i] = new bigint[node_num[i]];
	}

	for (int layer = 0; layer < layer_cnt - 1; layer++) {
		weight[layer] = new bigint*[node_num[layer]];
		for (int i = 0; i < node_num[layer]; i++) {
			weight[layer][i] = new bigint[node_num[layer + 1]];
		}
	}
};
BigIntNerualNet::~BigIntNerualNet() {
	for (int i = 0; i < layer_cnt; i++) {
		delete[] layers[i];
	}
	delete[] layers;
	delete[] node_num;

	for (int layer = 0; layer < layer_cnt - 1; layer++) {
		for (int i = 0; i < node_num[layer]; i++) {
			delete[] weight[layer][i];
		}
		delete[] weight[layer];
	}
	delete[] weight;
}
void BigIntNerualNet::InitNNTest() {
	cout << "---InitNNTest---\n";
	cout << "input layer " << " (" << node_num[0] << "): ";
	for (int node = 0; node < node_num[0]; node++) {
		cout << layers[0][node] << ' ';
	}
	cout << endl;
	for (int layer = 0; layer < layer_cnt - 1; layer++) {
		cout << "layer " << layer + 1 << "-" << layer + 2 << "\n";
		for (int i = 0; i < node_num[layer]; i++) {
			cout << "w" << i << " : ";
			for (int j = 0; j < node_num[layer + 1]; j++) {
				cout << weight[layer][i][j] << ' ';
			}
			cout << endl;
		}
	}
}
void BigIntNerualNet::FeedForwardTest() {
}
void BigIntNerualNet::InitNN() {
	cout << "\n---initNN---\n";
	cout << "input layer : ";
	for (int i = 0; i < node_num[0]; i++) {
		cin >> this->layers[0][i];
	}
	cout << "input weight\n";
	for (int layer = 0; layer < layer_cnt - 1; layer++) {
		cout << "layer " << layer + 1 << "-" << layer + 2 << " : ";
		for (int i = 0; i < node_num[layer]; i++) {
			for (int j = 0; j < node_num[layer + 1]; j++) {
				cin >> weight[layer][i][j];
			}
		}
	}

	InitNNTest();
};
void BigIntNerualNet::FeedForward() {
};
void BigIntNerualNet::ShowResult() {
};