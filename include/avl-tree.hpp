#include "bst.hpp"

const short leftSubtreeIsDeeper = -1;
const short rightSubtreeIsDeeper = 1;
const short treeIsBalanced = 0;

template<class KeyType>
class AVL_TREE : public BST<KeyType> {
	int	 getDepth(NODE<KeyType>* node = NULL)const;

	void doSingleLeftRotation	(NODE<KeyType>*&);
	void doSingleRightRotation	(NODE<KeyType>*&);
	void doDoubleLeftRotation	(NODE<KeyType>*&);
	void doDoubleRightRotation	(NODE<KeyType>*&);

	void updateLeftTree	(NODE<KeyType>*&);
	void updateRightTree(NODE<KeyType>*&);

	void makeBalancing	(NODE<KeyType>*&);
	
	void doRecursiveInsertion	(NODE<KeyType>*&, NODE<KeyType>*);
	NODE<KeyType>* getNodeForErasing(NODE<KeyType>*&, const KeyType&);
public:
	AVL_TREE(void) : BST() {}
	AVL_TREE(const AVL_TREE<KeyType>& tree) : BST(tree) {}
	AVL_TREE(const BST<KeyType>&);
	virtual ~AVL_TREE(void);

	virtual void erase	(const KeyType&);
	virtual void insert	(const KeyType&);
};

template<class KeyType>
int AVL_TREE<KeyType>::getDepth(NODE<KeyType>* node) const{
	if (node == NULL)
		return -1;
	int left = getDepth(node->left_);
	int right = getDepth(node->right_);
	node->balance_ = right - left;
	return (right > left) ? (right + 1) : (left + 1);
}

template<class KeyType>
void AVL_TREE<KeyType>::doSingleRightRotation(NODE<KeyType>*& node){

	NODE<KeyType>* tmp1 = node;
	NODE<KeyType>* tmp2 = tmp1->left_;
	NODE<KeyType>* a = tmp2->right_;

	tmp1->left_ = a;
	tmp2->right_ = tmp1;
	tmp2->parent_ = tmp1->parent_;
	tmp1->parent_ = tmp2;

	if (a != NULL) a->parent_ = tmp1;

	getDepth(tmp1);
	getDepth(tmp2);

	node = tmp2;
}

template<class KeyType>
void AVL_TREE<KeyType>::doSingleLeftRotation(NODE<KeyType>*& node){

	NODE<KeyType>* tmp1 = node;
	NODE<KeyType>* tmp2 = tmp1->right_;
	NODE<KeyType>* a = tmp2->left_;

	tmp1->right_ = a;
	tmp2->left_ = tmp1;
	tmp2->parent_ = tmp1->parent_;
	tmp1->parent_ = tmp2;

	if (a != NULL) a->parent_ = tmp1;

	getDepth(tmp1);
	getDepth(tmp2);

	node = tmp2;
}

template<class KeyType>
void AVL_TREE<KeyType>::doDoubleRightRotation(NODE<KeyType>*& node){
	NODE<KeyType>* tmp1 = node;
	NODE<KeyType>* tmp2 = tmp1->left_;
	NODE<KeyType>* tmp3 = tmp2->right_;
	NODE<KeyType>* a = tmp3->left_;
	NODE<KeyType>* b = tmp3->right_;

	tmp3->right_ = tmp1;
	tmp3->left_ = tmp2;
	tmp3->parent_ = tmp1->parent_;
	tmp1->parent_ = tmp3;
	tmp2->parent_ = tmp3;
	tmp2->right_ = a;
	tmp1->left_ = b;

	if (a != NULL) a->parent_ = tmp2;
	if (b != NULL) b->parent_ = tmp1;

	getDepth(tmp1);
	getDepth(tmp2);
	getDepth(tmp3);

	node = tmp3;


}

template<class KeyType>
void AVL_TREE<KeyType>::doDoubleLeftRotation(NODE<KeyType>*& node){
	NODE<KeyType>* tmp1 = node;
	NODE<KeyType>* tmp2 = tmp1->right_;
	NODE<KeyType>* tmp3 = tmp2->left_;
	NODE<KeyType>* a = tmp3->left_;
	NODE<KeyType>* b = tmp3->right_;

	tmp3->left_ = tmp1;
	tmp3->right_ = tmp2;
	tmp3->parent_ = tmp1->parent_;
	tmp1->parent_ = tmp3;
	tmp2->parent_ = tmp3;
	tmp2->left_ = b;
	tmp1->right_ = a;

	if (a != NULL) a->parent_ = tmp1;
	if (b != NULL) b->parent_ = tmp2;

	getDepth(tmp1);
	getDepth(tmp2);
	getDepth(tmp3);

	node = tmp3;
}

template<class KeyType>
void AVL_TREE<KeyType>::updateLeftTree(NODE<KeyType>*& node){
	if (node == NULL) return;
	if		(node->left_->balance_ == leftSubtreeIsDeeper)	doSingleRightRotation(node);
	else if (node->left_->balance_ == rightSubtreeIsDeeper) doDoubleRightRotation(node);
}

template<class KeyType>
void AVL_TREE<KeyType>::updateRightTree(NODE<KeyType>*& node){
	if (node == NULL) return;
	if		(node->right_->balance_ == rightSubtreeIsDeeper) doSingleLeftRotation(node);
	else if (node->right_->balance_ == leftSubtreeIsDeeper)	doDoubleLeftRotation(node);
}

template<class KeyType>
void AVL_TREE<KeyType>::makeBalancing(NODE<KeyType>*& node){
	if (node == NULL)
		return;
	getDepth(node);
	short balance = node->balance_;

	switch (balance){
		case 2:
			updateRightTree(node);
		case -2:
			updateLeftTree(node);
	}
}

template<class KeyType>
void AVL_TREE<KeyType>::doRecursiveInsertion(NODE<KeyType>*& tree, NODE<KeyType>* node){
	if (tree == NULL) return;
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

	makeBalancing(tree);
}

template<class KeyType>
NODE<KeyType>* AVL_TREE<KeyType>::getNodeForErasing(NODE<KeyType>*& tree, const KeyType& data){
	if (tree == NULL) return NULL;
	NODE<KeyType>* nodeForAnnihilation = NULL;
	if (data < tree->data_)
		nodeForAnnihilation = getNodeForErasing(tree->left_, data);
	else if (data > tree->data_)
		nodeForAnnihilation = getNodeForErasing(tree->right_, data);
	else {
		if (tree->left_ == NULL && tree->right_ == NULL) {
			if	(tree->parent_->left_ == tree) tree->parent_->left_ = NULL;
			else tree->parent_->right_ = NULL;
			return tree;
		}else if (tree->right_ == NULL) {
			nodeForAnnihilation = tree;
			NODE<KeyType>* tmp = tree->left_;
			tmp->parent_ = tree->parent_;
			if	(tree->parent_->left_ == tree) tree->parent_->left_ = tmp;
			else tree->parent_->right_ = tmp;

			return nodeForAnnihilation;
		}else if (tree->left_ == NULL) {
			nodeForAnnihilation = tree;
			NODE<KeyType>* tmp = tree->right_;
			tmp->parent_ = tree->parent_;
			if	(tree->parent_->left_ == tree) tree->parent_->left_ = tmp;
			else tree->parent_->right_ = tree->right_;

			return nodeForAnnihilation;
		} else{
			NODE<KeyType>* tmpNext	= findNext(tree);
			NODE<KeyType>* tmp		= tmpNext->parent_;

			if (tmpNext->parent_->left_ == tmpNext)
				tmp->left_ = tmpNext->right_;
			else
				tmp->right_ = tmpNext->right_;

			tmpNext->parent_	= tree->parent_;
			tmpNext->left_		= tree->left_;
			tmpNext->right_		= tree->right_;

			if (tmpNext->left_ != NULL)
				tmpNext->left_->parent_ = tmpNext;
			if (tmpNext->right_ != NULL)
				tmpNext->right_->parent_ = tmpNext;

			while (tmp != NULL && tmp != tmpNext) {
				makeBalancing(tmp);
				tmp = tmp->parent_;				
			}
			nodeForAnnihilation = tree;

			tree = tmpNext;
		}
	}
	makeBalancing(tree);
	return nodeForAnnihilation;
}

template<class KeyType>
AVL_TREE<KeyType>::AVL_TREE(const BST<KeyType>& tree){
	root_ = NULL;
	count = tree.count;
	vector<NODE<KeyType>* > v = tree.recPostOrder();
	for (size_t i = 0; i < count; i++) insert(v[i]->data_);
}

template<class KeyType>
AVL_TREE<KeyType>::~AVL_TREE(void){
	recursiveErase(root_);
}

template<class KeyType>
void AVL_TREE<KeyType>::erase(const KeyType& data){
	if (root_ == NULL) return;
	NODE<KeyType>* tmp = root_;
	delete getNodeForErasing(tmp, data);
	root_ = tmp;
}

template<class KeyType>
void AVL_TREE<KeyType>::insert(const KeyType& data){
	NODE<KeyType>* node = new NODE<KeyType>(data, NULL);
	if (node == NULL)
		throw exception("Bad memory allocation.");
	if (root_ == NULL) {
		root_ = node;
		root_->parent_ = NULL;
		return;
	}

	doRecursiveInsertion(root_, node);
}
