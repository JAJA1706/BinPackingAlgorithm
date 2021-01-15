#include "BinPackingBST.h"
#include <iostream>
#define BIN_SIZE 1


Node* BinPackingBST::insertNode( Node* root, float required_size ) {
	if (root == nullptr) {
		Node* new_node = new Node;
		new_node->occupied_size_ = required_size;
		new_node->left_ = nullptr;
		new_node->right_ = nullptr;
		return new_node;
	}

	else if (root->occupied_size_ > required_size)
		root->left_ = insertNode( root->left_, required_size );

	else //(root->occupied_size_ <= required_size)
		root->right_ = insertNode(root->right_, required_size);

	return root;
}

//find min value in tree
Node* BinPackingBST::minValue(Node* root) {
	Node* temp = root;
	while (temp->left_ != nullptr)
		temp = temp->left_;

	return temp;
}

Node* BinPackingBST::deleteNode( Node* root, float size_to_be_deleted ) {
	if (root == nullptr)
		return root;

	if (size_to_be_deleted > root->occupied_size_)
		root->right_ = deleteNode(root->right_, size_to_be_deleted);

	else if (size_to_be_deleted < root->occupied_size_)
		root->left_ = deleteNode(root->left_, size_to_be_deleted);

	else {
		//one or zero child cases
		//I'm starting with left because two child case uses it often
		if (root->left_ == nullptr) {
			Node* temp = root->right_;
			delete(root);
			return temp;
		}

		else if (root->right_ == nullptr) {
			Node* temp = root->left_;
			delete(root);
			return temp;
		}

		//two child case
		Node* temp = minValue(root->right_);
		root->occupied_size_ = temp->occupied_size_;
		root->right_ = deleteNode(root->right_, temp->occupied_size_);
	}
	return root;
}

//look for best bin to alocate given size
Node* BinPackingBST::searchBestBin(Node* root, float required_size) {
	if (root == nullptr)
		return nullptr;

	if ( BIN_SIZE < root->occupied_size_ + required_size)
		return searchBestBin(root->left_, required_size);

	else if ( BIN_SIZE > root->occupied_size_ + required_size) {
		if (root->right_ != nullptr) {
			Node* temp = searchBestBin(root->right_, required_size);
			if (temp != nullptr)
				return temp;
		}
		else {
			return root;
		}
	}

	return root;
}


int BinPackingBST::bestFitBST(std::vector<float>& items_size) {
	Node* temp;
	float occup_size;
	int num_of_bins = 0;
	for (size_t i = 0, size = items_size.size(); i < size; ++i) {
		temp = searchBestBin(root_, items_size[i]);
		if (temp == nullptr) {
			++num_of_bins;
			root_ = insertNode(root_, items_size[i]);
		}
		else {
			occup_size = temp->occupied_size_;
			root_ = deleteNode(root_, temp->occupied_size_);
			root_ = insertNode(root_, occup_size + items_size[i]);
		}
	}
	return num_of_bins;
}

void BinPackingBST::deleteBST(Node* root) {
	if (root != nullptr) {
		deleteBST(root->left_);
		deleteBST(root->right_);
		delete(root);
	}
}

/*void printTree(Node* root)
{
	if (root != NULL)
	{
		printTree(root->left_);
		std::cout << root->occupied_size_;
		printTree(root->right_);
	}
}*/