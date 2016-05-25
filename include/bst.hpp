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

	NODE() : left_(NULL), right_(NULL), parent_(NULL) {}
	NODE(const KeyType& data, NODE* parent, NODE* left = NULL, NODE* right = NULL) :
		data_(data), parent_(parent), left_(left), right_(right) {}
	NODE(const NODE& node) : data_(node.data_), parent_(node.parent_),
		left_(node.left_), right_(node.right_) {}
};

template<class KeyType>
class BST {
	NODE<KeyType>*	getNodeForErasing(const KeyType&);
	NODE<KeyType>*	getMinNodeForErasing(void);
protected:
	NODE<KeyType>* root_;
	void recursiveErase(NODE<KeyType>*&);
	NODE<KeyType>* copy(NODE<KeyType>*, NODE<KeyType>*);
public:
	BST(void) : root_(NULL) {}
	BST(const BST<KeyType>& tree) { root_ = copy(tree.root_, NULL); }
	~BST(void);

	void 	insert		(const KeyType&);
	void 	erase		(const KeyType&);
	void	eraseMinNode(void);

	NODE<KeyType>* 	find 	(const KeyType&)const;
	NODE<KeyType>* 	findMin	(NODE<KeyType>* node = NULL)const;
	NODE<KeyType>* 	findMax	(NODE<KeyType>* node = NULL)const;
	NODE<KeyType>* 	findPrev(NODE<KeyType>*)const;
	NODE<KeyType>* 	findNext(NODE<KeyType>*)const;

	size_t	getSize	(void)const { return recPostOrder().size(); }

	vector<NODE<KeyType>* > recPostOrder(void)const;
};

template<class KeyType>
NODE<KeyType>* BST<KeyType>::getNodeForErasing(const KeyType& data){
	NODE<KeyType>* tmp = NULL;
	NODE<KeyType>* tmp1 = NULL;
	NODE<KeyType>* tmp2 = find(data);
	if	(tmp2->left_ != NULL && tmp2->right_ != NULL) tmp1 = findNext(tmp2);
	else tmp1 = tmp2;
	if	(tmp1->left_ != NULL) tmp = tmp1->left_;
	else tmp = tmp1->right_;
	if (tmp != NULL) tmp->parent_ = tmp1->parent_;
	if (tmp1->parent_) {
		if	(tmp1 == tmp1->parent_->left_) tmp1->parent_->left_ = tmp;
		else tmp1->parent_->right_ = tmp;
	}
	tmp2->data_ = tmp1->data_;
	return tmp1;
}

template<class KeyType>
NODE<KeyType>* BST<KeyType>::getMinNodeForErasing(void){
	if (root_ == NULL)
		throw exception("You can not erase minimal node from empty tree.");

	NODE<KeyType>* node = findMin();

	if (node->parent_ == NULL) {
		if (node->right_ == NULL) {
			root_ = NULL;
			return node;
		}
		root_ = node->right_;
		root_->parent_ = NULL;
		node->right_ = NULL;
		return node;
	}

	node->parent_->left_ = node->right_;
	node->right_ = node->parent_ = NULL;
	return node;
}

template<class KeyType>
void BST<KeyType>::recursiveErase(NODE<KeyType>*& node){
	if (node == NULL) return;
	if (node->left_		!= NULL) recursiveErase(node->left_);
	if (node->right_	!= NULL) recursiveErase(node->right_);
	delete node;
	node = NULL;
}

template<class KeyType>
NODE<KeyType>* BST<KeyType>::copy(NODE<KeyType>* tree, NODE<KeyType>* parent){
	if (tree == NULL) return NULL;
	NODE<KeyType>* tmp = new NODE<KeyType>(tree->data_, parent);
	tmp->left_ = copy(tree->left_, tmp);
	tmp->right_ = copy(tree->right_, tmp);
	return tmp;
}

template<class KeyType>
BST<KeyType>::~BST(void){
	recursiveErase(root_);
}

template<class KeyType>
void BST<KeyType>::insert(const KeyType& data){
	if (root_ == NULL){
		root_ = new NODE<KeyType>(data, NULL, NULL, NULL);
		return;
	}

	NODE<KeyType>* tmp = root_;
	NODE<KeyType>* prev = new NODE<KeyType>;
	while (tmp != NULL){
		prev = tmp;
		if (tmp->data_ <= data) tmp = tmp->right_;
		else tmp = tmp->left_;
	}
	if (prev->data_ <= data)
		prev->right_ = new NODE<KeyType>(data, prev);
	else prev->left_ = new NODE<KeyType>(data, prev);


	//NODE<KeyType>* tmp = root_;
	//NODE<KeyType>* prev;
	//while(tmp != NULL){
	//	prev = tmp;
	//	if	(tmp->data_ < data) tmp = tmp->right_;
	//	else tmp = tmp->left_;
	//}
	//if	(prev->data_ <= data) prev->right_ = new NODE<KeyType>(data, prev);
	//else prev->left_ = new NODE<KeyType>(data, prev);
}

template<class KeyType>
void BST<KeyType>::erase(const KeyType& data){
	delete getNodeForErasing(data);
}

template<class KeyType>
void BST<KeyType>::eraseMinNode(void){
	delete getMinNodeForErasing();
}

template<class KeyType>
NODE<KeyType>* BST<KeyType>::find(const KeyType& data) const{
	if (root_ == NULL)
		throw exception("Tree is empty;");
	NODE<KeyType> *tmp = root_;
	while (tmp != NULL && tmp->data_ != data){
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
		node = root_;
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
		node = root_;
	if (node == NULL)
		throw exception("Start node is empty.");
	NODE<KeyType>* maxNode = node;
	while (maxNode->right_ != NULL)
		maxNode = maxNode->right_;
	return maxNode;
}

template<class KeyType>
NODE<KeyType>* BST<KeyType>::findPrev(NODE<KeyType>* node) const{
	if (node == 0)
		throw exception("Start node is empty.");
	KeyType data = node->data_;
	if (node->left_ != 0)
		return findMax(node->left_);
	while (node->parent_ != NULL && node->parent_->left_ == node) node = node->parent_;
	if (node->parent_ == NULL)
		throw exception("Previous node does not exist");
	return node->parent_;
}

template<class KeyType>
NODE<KeyType>* BST<KeyType>::findNext(NODE<KeyType>* node) const{
	if (node == 0)
		throw exception("Start node is empty.");
	KeyType data = node->data_;
	if (node->right_ != 0)
		return findMin(node->right_);
	while (node->parent_ != NULL && node->parent_->right_ == node) node = node->parent_;
	if (node->parent_ == NULL)
		throw exception("Next node does not exist");
	return node->parent_;
}

template<class KeyType>
vector<NODE<KeyType>* > BST<KeyType>::recPostOrder(void) const {
	if (root_ == 0)
		return vector<NODE<KeyType>* >(0);
	stack<NODE<KeyType>* > s, res;
	s.push(root_);
	while (!s.empty()) {
		NODE<KeyType> *tmp = s.top();
		s.pop();
		if (tmp != NULL) {
			res.push(tmp);
			if (tmp->right_ != 0) s.push(tmp->right_);
			if (tmp->left_ != 0) s.push(tmp->left_);
		}
	}
	vector<NODE<KeyType>* > v(res.size());
	while (!res.empty()) {
		v[res.size() - 1] = res.top();
		res.pop();
	}
	return v;
}