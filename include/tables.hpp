#pragma once
#include <iostream>
using namespace std;

template<class KeyType>
class TAB_RECORD {
protected:
	KeyType key_;
public:
	TAB_RECORD(const KeyType& key) : key_(key){}
	KeyType getKey(void)const { return key_; }
};

template<class DataType>
class TABLE {
protected:
	size_t size_;
	size_t count_;
	size_t cur_;
public:
	TABLE(size_t size) : size_(size), count_(0), cur_(0) {}

	virtual TAB_RECORD<DataType>* find	(const DataType&)const = 0;
	virtual void		insert	(const TAB_RECORD<DataType>&) = 0;
	virtual void		erase	(double) = 0;

	int		isEmpty	(void)const { return count_ == 0; }
	int		isFull	(void)const { return count_ == size_;}
	size_t	getCount(void)const { return count_; }

	virtual void	reset		(void) { cur_ = 0; }
	virtual int		goNext		(void) { cur_++; return isTabEnded() ? 1 : 0 * cur_++; }
	virtual int		isTabEnded	(void)const { return cur_ == count_; }
};

template<class DataType>
class SCAN_TABLE : public TABLE {
protected:
	TAB_RECORD<DataType>** recs_;
	void repackUp(void);
public:
	SCAN_TABLE(size_t size);
	virtual ~SCAN_TABLE(void);

	virtual TAB_RECORD<DataType>* find(const DataType&)const;
	virtual void		insert(const TAB_RECORD<DataType>&);
	virtual void		erase(const DataType&);
};

template<class DataType>
void SCAN_TABLE<DataType>::repackUp(void){
	for (size_t i = cur_; i < count_ - 1; i++) {
		recs_[i] = recs_[i + 1];
	}
	count--;
}

template<class DataType>
SCAN_TABLE<DataType>::SCAN_TABLE(size_t size) : TABLE<DataType>(size) {
	recs_ = new TAB_RECORD<DataType>*[size];
	for (size_t i = 0; i < size; i++) {
		recs_[i] = NULL;
	}
}

template<class DataType>
SCAN_TABLE<DataType>::~SCAN_TABLE(void){
	for (size_t i = 0; i < size_; i++) {
		delete recs_[i];
	}
	delete[]recs_;
}

template<class DataType>
TAB_RECORD<DataType>* SCAN_TABLE<DataType>::find(const DataType& key) const{
	for (cur_ = 0; cur_ < count_; cur_++) {
		if (recs_[cur_]->getKey() == key) return recs_[cur_];
	}
	return NULL;
}

template<class DataType>
void SCAN_TABLE<DataType>::insert(const TAB_RECORD<DataType>& rec){
	if (isFull())
		throw exception("Table is full.");
	recs_[count_++] = new TAB_RECORD<DataType>(rec.getKey());
}

template<class DataType>
void SCAN_TABLE<DataType>::erase(const DataType& key){
	if (isEmpty()) return;
	if (find(key) == NULL)
		throw exception("Key was not found.");
	delete recs_[cur_];
	repackUp();
	recs_[count + 1] = NULL;
}

template<class DataType>
class SORT_TABLE : public SCAN_TABLE<DataType> {
protected:
	void repackDown(void);
	void binSearch(const DataType&);
	void sort(void);
public:
	SORT_TABLE(size_t size) : SCAN_TABLE<DataType>(size) {}
	SORT_TABLE(const SCAN_TABLE&) { sort(); }
	virtual ~SORT_TABLE(void);

	virtual TAB_RECORD<DataType>* find(const DataType&)const;
	virtual void		insert(const TAB_RECORD<DataType>&);
	virtual void		erase(const DataType&);
};

template<class DataType>
void SORT_TABLE<DataType>::repackDown(void){
	for (size_t i = count_; i > cur_; i--) {
		recs_[i] = recs_[i - 1];
	}
	count_++;
}

template<class DataType>
void SORT_TABLE<DataType>::binSearch(const DataType& key){
	size_t left = 0;
	size_t right = count_;
	size_t mid;

	while(left <= right){
		mid = left + (right - left) / 2;
		if (key < recs_[mid]->getKey()) right = mid - 1;
		else if (key > recs_[mid]->getKey()) left = mid + 1;
		else {
			cur_ = mid;
			return;
		}
		cur_ = right_;
	}
}

template<class DataType>
void SORT_TABLE<DataType>::sort(void){
	int i, j, nMin;
	TAB_RECORD<DataType>* c;
	for (i = 0; i < count_; i++){
		nMin = i;
		for (j = i + 1; j < count_; j++)
			if (recs_[j]->getKey() < recs_[nMin]->getKey())
				nMin = j;
		c = recs_[i];
		recs_[i] = recs_[nMin];
		recs_[nMin] = c;
	}
}

template<class DataType>
SORT_TABLE<DataType>::~SORT_TABLE(void){
	for (size_t i = 0; i < size_; i++) {
		delete recs_[i];
	}
	delete[]recs_;
}

template<class DataType>
TAB_RECORD<DataType>* SORT_TABLE<DataType>::find(const DataType& key) const{
	binSearch(key);
	return recs_[cur_] ? recs_[cur_] : NULL;
}

template<class DataType>
void SORT_TABLE<DataType>::insert(const TAB_RECORD<DataType>& rec){
	if (isFull())
		throw exception("Table is full.");
	find(rec.getKey());
	repackDown();
	recs_[cur_] = new TAB_RECORD<DataType>(rec.getKey());
}

template<class DataType>
void SORT_TABLE<DataType>::erase(const DataType& key){
	if (isEmpty()) return;
	if (find(key) == NULL)
		throw exception("Key was not found.");
	delete recs_[cur_];
	repackUp();
	recs_[count + 1] = NULL;
}
