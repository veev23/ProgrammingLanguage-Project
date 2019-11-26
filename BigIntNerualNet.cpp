#include "BigIntNerualNet.h"

BigIntNerualNet::BigIntNerualNet() {
};
void BigIntNerualNet::InitNNTest() {
};
void BigIntNerualNet::FeedForwardTest() {
};
void BigIntNerualNet::InitNN() {
	for (int layer = 0; layer < LAYER_CNT; layer++) {
		for (int i = 0; i < MAX_NODES; i++) {
			cin >> this->layer[layer][i];
		}
	}
};
void BigIntNerualNet::FeedForward() {
};
void BigIntNerualNet::ShowResult() {
};