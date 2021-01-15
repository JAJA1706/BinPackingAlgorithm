#ifndef BINBST_H
#define BINBST_H

#include <vector>

struct Node {
	float occupied_size_;
	struct Node* left_;
	struct Node* right_;
};
typedef struct Node Node;

class BinPackingBST {
public:
	BinPackingBST() : root_(nullptr) {}
	~BinPackingBST() { deleteBST(root_); }
	int bestFitBST( std::vector<float>& items_size );
private:
	Node* insertNode(Node* root, float required_size);
	Node* deleteNode(Node* root, float size_to_be_deleted);
	Node* searchBestBin(Node* root, float required_size);
	Node* minValue(Node* root);
	void deleteBST(Node* root);

	Node* root_;
};

#endif
