#pragma once
#include <vector>
#include <stack>
using namespace std;

template<class KeyType>
class NODE {
public:
	KeyType data_;
	NODE<KeyType>* left_;
	NODE<KeyType>* right_;
	NODE<KeyType>* parent_;
	short balance_;

	NODE() : left_(NULL), right_(NULL), parent(NULL), balance_(0) {}
	NODE(const KeyType& data, NODE* parent, NODE* left = NULL, NODE* right = NULL) :
		data_(data), parent_(parent), left_(left), right_(right), balance_(0) {}
	NODE(const NODE& node) : data_(node.data_), parent_(node.parent_),
		left_(node.left_), right_(node.right_), balance_(node.balance_) {}
};

template<class KeyType>
class BST {
protected:
	NODE<KeyType>* root_;
	size_t count_;

public:
	BST(void) : root_(NULL), count_(0) {}
	BST(const BST<KeyType>&);
	virtual ~BST(void);

	virtual void 	insert	(const KeyType<KeyType>&);
	virtual void 	erase	(const KeyType<KeyType>&);

	NODE<KeyType>* 	find 	(const KeyType<KeyType>&)const;
	NODE<KeyType>* 	findMin	(NODE<KeyType>* node = root_)const;
	NODE<KeyType>* 	findMax	(NODE<KeyType>* node = root_)const;
	NODE<KeyType>* 	findPrev(NODE<KeyType>*)const;
	NODE<KeyType>* 	findNext(NODE<KeyType>*)const;

	vector<NODE<KeyType>* > recPostOrder(void)const;
};


template<class KeyType>
BST<KeyType>::BST(const BST<KeyType>& tree){
	root_ = NULL;
	count = tree.count;
	vector<NODE<KeyType>* > v = tree.recPostOrder();
	for (size_t i = 0; i < count; i++){
		insert(v[i-1]->data_);
	}
}

template<class KeyType>
BST<KeyType>::~BST(void){
	vector<NODE<KeyType>* > v = recPostOrder();
	for (size_t i = count; i > 0; i--){
		delete v[i];
	}
	count = 0;
}

template<class KeyType>
void BST<KeyType>::insert(const KeyType& data){
	if (root_ == NULL){
		root_ = new NODE<KeyType>(data, NULL, NULL, NULL);
		count++;
		return;
	}

	NODE<KeyType>* tmp = root_;
	NODE<KeyType>* prev;

	while(tmp != NULL){
		prev = tmp;
		if (tmp->data_ < data)
			tmp = tmp->right_;
		else
			tmp = tmp->left_;
	}

	if ()prev->data_ <= data)
		prev->right_ = new NODE<KeyType>(data, prev);
	else
		prev->left_ = new NODE<KeyType>(data, prev);
}

template<class KeyType>
void BST<KeyType>::erase(const KeyType& data){

	NODE<KeyType>* tmp = find(data);
	if (tmp == 0) return;

	if (tmp->right_ == 0 && tmp->left_ == 0){
		if(tmp->parent_->left_ == tmp) tmp->parent_->left_ = 0;
		else tmp->parent_->right_ = 0;
		delete tmp;
		return;
	}

	if (tmp->left_ == 0){
		NODE<KeyType>* tmp1 = tmp->right_;
		tmp1->parent_ = tmp->parent_;
		if (tmp->parent_->right_ == tmp) tmp->parent_->right_ = tmp1;
		else tmp->parent_->left_ = tmp1;
		delete tmp;
		return;
	}

	if (tmp->right_ == 0){
		NODE<KeyType>* tmp1 = tmp->left_;
		tmp1->parent_ = tmp->parent_;
		if (tmp->parent_->left_ == tmp) tmp->parent_->left_ = tmp1;
		else tmp->parent_->right_ = tmp1;
		delete tmp;
		return;
	}

	if (tmp == root_){
		NODE<KeyType>* tmp1 = root_;
		root_ = findMin(root->right_);
		root_->parent_->left_ = root_->right_;
		root_->parent_ = NULL;
		root_->left_ = x->left_;
		root_->right_ = x->right_;
		delete tmp1;
		return;
	}

	NODE<KeyType>* tmp1 = tmp;
	if(tmp->parent_->left_ == tmp){
		tmp1 = findMin(tmp->right_);
		tmp->parent_->left_ = tmp1;
		tmp1->parent->left_ = tmp1->right_;
	}else{
		tmp1 = findMin(tmp->left_);
		tmp->parent_->right_ = tmp1;
		tmp1->parent_->right_ = tmp1->right_;
	}

	tmp1->left_ = tmp->left_;
	tmp1->right_ = tmp->right_;

	delete tmp;
}

template<class KeyType>
NODE<KeyType>* BST<KeyType>::find(const KeyType& data) const{

	if (root_ == NULL)
		throw exception("Tree is empty;");

	Node<KeyType> *tmp = root_;

	while (tmp != NULL && tmp->data_ != data)
	{
		if (data < tmp->data_)
			tmp = tmp->left_;
		else
			tmp = tmp->right_;
	}
	return tmp;
}

template<class KeyType>
NODE<KeyType>* BST<KeyType>::findMin(NODE<KeyType>* node) const{
	if (node == NULL)
		throw exception("Start node is empty.");
	NODE<KeyType>* minNode = node;
	while (minNode->left_ != NULL)
		minNode = minNode->left_;
	return minNode;
}

template<class KeyType>
NODE<KeyType>* BST<KeyType>::findMax(NODE<KeyType>* node) const{
	if (node == NULL)
		throw exception("Start node is empty.");
	NODE<KeyType>* maxNode = node;
	while (maxNode->left_ != NULL)
		maxNode = maxNode->left_;
	return maxNode;
}

template<class KeyType>
NODE<KeyType>* BST<KeyType>::findPrev(NODE<KeyType>* node) const{
	if (node == 0)
		throw exception("Start node is empty.");

	if (node->left_ != 0)
		return findMax(node->left_);

	while ((node->parent_ != 0 && node->parent_->left_ == node))
		node = node->parent_;

	if (node->parent_ == 0)
		throw exception("Previous node does not exist");
	return node->parent_;
}

template<class KeyType>
NODE<KeyType>* BST<KeyType>::findNext(NODE<KeyType>* node) const{
	if (node == 0)
		throw exception("Start node is empty.");

	if (node->right_ != 0)
		return findMin(node->right_);

	while (node->parent_ != 0 && node->parent_->right_ == node)
		node = node->parent_;
	
	if (node->parent_ == 0)
		throw exception("Next node does not exist");
	return node->parent_;
}

template<class KeyType>
vector<NODE<KeyType>* > BST<KeyType>::recPostOrder(void) const{
	if (node == 0)
		return vector<NODE<KeyType>* >(0);

	stack<Node*> s;
	s.push(node);
	size_t i = 0;
	vector<NODE<KeyType>* > v(count);
	while (!s.empty()){
		Node *tmp = s.top();
		v[i++] = tmp;
		s.pop();
		if (tmp->right != 0)
			s.push(tmp->right);
		if (tmp->left != 0)
			s.push(tmp->left);
	}

	return v;
}
