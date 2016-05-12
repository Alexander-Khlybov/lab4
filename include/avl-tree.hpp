#include "bst.hpp"

const short leftSubtreeIsDeeper = -1;
const short rightSubtreeIsDeeper = 1;
const short treeIsBalanced = 0;

template<class KeyType>
class AVL_TREE : public BST {

	void doSingleLeftRotation	(NODE<KeyType>*&);
	void doSingleRightRotation	(NODE<KeyType>*&);
	void doDoubleLeftRotation	(NODE<KeyType>*&);
	void doDoubleRightRotation	(NODE<KeyType>*&);

	void updateLeftTree	(NODE<KeyType>*&);
	void updateRightTree(NODE<KeyType>*&);
	
	void doRecursiveInsertion	(NODE<KeyType>*&, NODE<KeyType>*);
	void doRecursiveErasing		(NODE<KeyType>*&, const KeyType&);
public:
	AVL_TREE(void) : BST() {}
	AVL_TREE(const AVL_TREE<KeyType>&);
	AVL_TREE(const BST<KeyType>&);
	virtual ~AVL_TREE(void);

	virtual void erase	(const KeyType&);
	virtual void insert	(const KeyType&);
};

template<class KeyType>
void AVL_TREE<KeyType>::doSingleLeftRotation(NODE<KeyType>*& node){
	NODE<KeyType>* tmp1 = node;
	NODE<KeyType>* tmp2 = tmp1->right_;
	NODE<KeyType>* a	= tmp2->left_;

	tmp1->right_	= a;
	tmp2->left_		= tmp1;
	tmp2->parent_	= tmp1->parent_;
	tmp1->parent_	= tmp2;

	if (a != NULL) a->parent_ = tmp1;

	tmp1->balance_ = getDepth(tmp1->left_) - getDepth(tmp1->right_);
	tmp2->balance_ = getDepth(tmp2->left_) - getDepth(tmp2->right_);

	node = tmp2;
}

template<class KeyType>
void AVL_TREE<KeyType>::doSingleRightRotation(NODE<KeyType>*& node){
	NODE<KeyType>* tmp1 = node;
	NODE<KeyType>* tmp2 = tmp1->left_;
	NODE<KeyType>* a	= tmp2->right_;

	tmp1->left_		= a;
	tmp2->right_	= tmp1;
	tmp2->parent_	= tmp1->parent_;
	tmp1->parent_	= tmp2;

	if (a != NULL) a->parent_ = tmp1;

	tmp1->balance_ = getDepth(tmp1->left_) - getDepth(tmp1->right_);
	tmp2->balance_ = getDepth(tmp2->left_) - getDepth(tmp2->right_);

	node = tmp2;
}

template<class KeyType>
void AVL_TREE<KeyType>::doDoubleLeftRotation(NODE<KeyType>*& node){
	NODE<KeyType>* tmp1 = node;
	NODE<KeyType>* tmp2 = tmp1->right_;
	NODE<KeyType>* tmp3 = tmp2->left_;
	NODE<KeyType>* a	= tmp3->left_;
	NODE<KeyType>* b	= tmp3->right_;

	tmp3->left_		= tmp1;
	tmp3->right_	= tmp2;
	tmp3->parent_	= tmp1->parent_;
	tmp1->parent_	= tmp3;
	tmp2->parent_	= tmp3;
	tmp2->left_		= b;
	tmp1->right_	= a;

	if (a != NULL) a->parent_ = tmp1;
	if (b != NULL) b->parent_ = tmp2;

	tmp1->balance_ = getDepth(tmp1->left_) - getDepth(tmp1->right_);
	tmp2->balance_ = getDepth(tmp2->left_) - getDepth(tmp2->right_);
	tmp3->balance_ = getDepth(tmp3->left_) - getDepth(tmp3->right_);

	node = tmp3;
}

template<class KeyType>
void AVL_TREE<KeyType>::doDoubleRightRotation(NODE<KeyType>*& node){
	NODE<KeyType>* tmp1 = node;
	NODE<KeyType>* tmp2 = tmp1->left_;
	NODE<KeyType>* tmp3 = tmp2->right_;
	NODE<KeyType>* a	= tmp3->left_;
	NODE<KeyType>* b	= tmp3->right_;

	tmp3->right_	= tmp1;
	tmp3->left_		= tmp2;
	tmp3->parent_	= tmp1->parent_;
	tmp1->parent_	= tmp3;
	tmp2->parent_	= tmp3;
	tmp2->right_	= a;
	tmp1->left_		= b;

	if (a != NULL) a->parent_ = tmp2;
	if (b != NULL) b->parent_ = tmp1;

	tmp1->balance_ = getDepth(tmp1->left_) - getDepth(tmp1->right_);
	tmp2->balance_ = getDepth(tmp2->left_) - getDepth(tmp2->right_);
	tmp3->balance_ = getDepth(tmp3->left_) - getDepth(tmp3->right_);

	node = tmp3;
}

template<class KeyType>
void AVL_TREE<KeyType>::updateLeftTree(NODE<KeyType>*& node){
	NODE<KeyType> *tmp;
	tmp = node->left_;
	if		(tmp->balance_ == leftSubtreeIsDeeper)	doSingleRightRotation(node);
	else if (tmp->balance_ == rightSubtreeIsDeeper) doDoubleRightRotation(node);
}

template<class KeyType>
void AVL_TREE<KeyType>::updateRightTree(NODE<KeyType>*& node){
	NODE<KeyType> *tmp;
	tmp = node->right_;
	if		(tmp->balance_ == rightSubtreeIsDeeper) doSingleLeftRotation(node);
	else if (tmp->balance_ == leftSubtreeIsDeeper)	doDoubleLeftRotation(node);
}

template<class KeyType>
void AVL_TREE<KeyType>::doRecursiveInsertion(NODE<KeyType>*& tree, NODE<KeyType>* node){
	if (node->data_ < tree->data_) {
		if (tree->left_ == NULL) {
			tree->left_ = node;
			node->parent_ = tree;
		}else
			doRecursiveInsertion(tree->left_, node);
	}else {
		if (tree->right_ == NULL) {
			tree->right_ = node;
			node->parent_ = tree;
		}else
			doRecursiveInsertion(tree->right_, node);
	}

	switch (getDepth(tmp->left_) - getDepth(tmp->right_) {
	case 2:
		updateLeftTree(tree);
		break;
	case -2:
		updateRightTree(tree);
	}
}

template<class KeyType>
void AVL_TREE<KeyType>::doRecursiveErasing(NODE<KeyType>*& tree, const KeyType& data){
	if (tree == NULL) return;
	if (data < tree->data_) doRecursiveErasing(tree->left_, data);
	if (data > tree->data_) doRecursiveErasing(tree->right_, data);
	if (data == tree->data_) {
		if (tree->left_ == NULL && tree->right_ == NULL) {
			if	(tree->parent_->left_ == tree) tree->parent_->left_ = NULL;
			else tree->parent_->right_ = NULL;
			delete tree;
		}else if (tree->right_ == NULL) {
			if	(tree->parent_->left_ == tree) tree->parent_->left_ = tree->left_;
			else tree->parent_->right_ = tree->left_;
			tree->left_->parent_ = tree->parent_;
			delete tree;
		}else if (tree->left_ == NULL) {
			if	(tree->parent_->left_ == tree) tree->parent_->left_ = tree->right_;
			else tree->parent_->right_ = tree->right_;
			tree->right_->parent_ = tree->parent_;
			delete tree;
		} else{
			NODE<KeyType>* tmpNext	= findNext(tree);
			NODE<KeyType>* tmp		= tmpNext->parent_;

			tmpNext->right_->parent_ = tmpNext->parent_;

			if	(tmpNext->parent_->left_ == tmpNext) tmpNext->parent_->left_ = tmpNext->right_;
			else tmpNext->parent_->right_ = tmpNext->right_;

			tmpNext->parent_	= tree->parent_;
			tmpNext->left_		= tree->left_;
			tmpNext->right_		= tree->right_;
			delete tree;

			while (tmp != tmpNext) {
				switch (getDepth(tmp->left_) - getDepth(tmp->right_) {
				case 2:
					updateLeftTree(tmp);
					break;
				case -2:
					updateRightTree(tmp);
				}
				tmp = tmp->parent_;
			}
		}
	}
	updateLeftTree(tmp);
	updateRightTree(tmp);
}

template<class KeyType>
AVL_TREE<KeyType>::AVL_TREE(const AVL_TREE<KeyType>& tree){
	root_ = NULL;
	count = tree.count;
	vector<NODE<KeyType>* > v = tree.recPostOrder();
	for (size_t i = 0; i < count; i++) insert(v[i - 1]->data_);
}

template<class KeyType>
AVL_TREE<KeyType>::AVL_TREE(const BST<KeyType>& tree){
	root_ = NULL;
	count = tree.count;
	vector<NODE<KeyType>* > v = tree.recPostOrder();
	for (size_t i = 0; i < count; i++) insert(v[i - 1]->data_;
}

template<class KeyType>
AVL_TREE<KeyType>::~AVL_TREE(void){
	vector<NODE<KeyType>* > v = recPostOrder();
	for (size_t i = count; i > 0; i--) delete v[i - 1];
	count = 0;
}

template<class KeyType>
void AVL_TREE<KeyType>::erase(const KeyType& data){
	if (root_ == NULL) return;
	NODE<KeyType>* treeRoot = root_;
	if (find(data) != NULL) count--;
	doRecursiveErasing(treeRoot, data);
	root_ = treeRoot;
}

template<class KeyType>
void AVL_TREE<KeyType>::insert(const KeyType& data){
	NODE<KeyType>* treeRoot = root_, *node;

	node = new NODE<KeyType>(data, NULL);
	if (node == NULL)
		throw exception("Bad memory allocation.");

	doRecursiveInsertion(treeRoot, node);
	root_ = treeRoot;
	count++;
}
