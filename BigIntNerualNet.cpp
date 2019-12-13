#include "BigIntNerualNet.h"
#pragma warning(disable : 4996)
#define LAYER_RANGE 30
#define LAYERNODES_RANGE 30
#define WEIGHT_RANGE 10000
#define INPUTNODE_RANGE 2100000000
BigIntNerualNet::BigIntNerualNet() {
};
BigIntNerualNet::~BigIntNerualNet() {
	for (int i = 0; i < layer_cnt; i++) {
		delete[] layers[i];
	}
	delete[] layers;

	for (int layer = 0; layer < layer_cnt - 1; layer++) {
		for (int i = 0; i < node_num[layer]; i++) {
			delete[] weight[layer][i];
		}
		delete[] weight[layer];
	}
	delete[] weight;
	delete[] node_num;
}

void BigIntNerualNet::TestFFAlgorithm(string path) {
	this->file_input.open(path);
}
void BigIntNerualNet::InitNNTest() {
	cout << "\n---InitNNTest---\n";
	cout << "layer별 노드 수 : ";
	for (int i = 0; i < layer_cnt; i++) {
		cout << node_num[i] << ' ';
	}
	cout << "\ninput layer : ";
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
	cout << "\n---FeedForwardTest---\n";
	for (int layer = 1; layer < layer_cnt - 1; layer++) {
		cout << "layer " << layer << " : ";
		for (int node = 0; node < node_num[layer]; node++) {
			cout << layers[layer][node] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
void BigIntNerualNet::InitNN() {
	if (file_input.is_open()) {
		//레이어 수
		file_input >> layer_cnt;
		layers = new bigint*[layer_cnt];
		node_num = new int[layer_cnt];
		weight = new bigint**[layer_cnt - 1];
		//레이어 별 노드 수
		for (int i = 0; i < layer_cnt; i++) {
			file_input >> node_num[i];
			layers[i] = new bigint[node_num[i]];
		}

		for (int layer = 0; layer < layer_cnt - 1; layer++) {
			weight[layer] = new bigint*[node_num[layer]];
			for (int i = 0; i < node_num[layer]; i++) {
				weight[layer][i] = new bigint[node_num[layer + 1]];
			}
		}
		//레이어별 weight
		for (int layer = 0; layer < layer_cnt - 1; layer++) {
			int fixed_weight;
			file_input >> fixed_weight;
			for (int i = 0; i < node_num[layer]; i++) {
				for (int j = 0; j < node_num[layer + 1]; j++) {
					weight[layer][i][j] = fixed_weight;
				}
			}
		}
		//input 레이어의 노드 입력
		for (int i = 0; i < node_num[0]; i++) {
			file_input >> this->layers[0][i];
		}
	}
	else {
		layer_cnt = rand() % LAYER_RANGE + 2;
		layers = new bigint*[layer_cnt];
		node_num = new int[layer_cnt];
		weight = new bigint**[layer_cnt - 1];
		for (int i = 0; i < layer_cnt; i++) {
			node_num[i] = rand() % LAYERNODES_RANGE + 1;
			layers[i] = new bigint[node_num[i]];
		}

		for (int layer = 0; layer < layer_cnt - 1; layer++) {
			weight[layer] = new bigint*[node_num[layer]];
			for (int i = 0; i < node_num[layer]; i++) {
				weight[layer][i] = new bigint[node_num[layer + 1]];
			}
		}
		//레이어별 weight
		for (int layer = 0; layer < layer_cnt - 1; layer++) {
			for (int i = 0; i < node_num[layer]; i++) {
				for (int j = 0; j < node_num[layer + 1]; j++) {
					weight[layer][i][j] = rand() % WEIGHT_RANGE;
				}
			}
		}
		//한 레이어의 노드들 입력
		for (int i = 0; i < node_num[0]; i++) {
			this->layers[0][i] = rand() % INPUTNODE_RANGE + 1;
		}
	}
	InitNNTest();
};
void BigIntNerualNet::FeedForward() {
	for (int layer = 1; layer < layer_cnt; layer++) {
		for (int node = 0; node < node_num[layer]; node++) {
			for (int i = 0; i < node_num[layer - 1]; i++) {
				layers[layer][node] += layers[layer - 1][i] * weight[layer - 1][i][node];
			}
		}
	}
	FeedForwardTest();
};
void BigIntNerualNet::ShowResult() {
	cout << "\n---FeedForwardTest---\n";
	int layer = layer_cnt - 1;
	cout << "output layer : ";
	for (int node = 0; node < node_num[layer]; node++) {
		cout << layers[layer][node] << '\n';
	}
	cout << endl;
};