/*
 * Heap.h
 *
 *  Created on: 2014年11月14日
 *      Author: keyming
 */

#ifndef FIXEDSIZEHEAP_H_
#define FIXEDSIZEHEAP_H_
#include <queue>
#include <algorithm>

namespace myutility{


template < typename T, typename _Comp = std::less<T> >
class FixedSizeHeap{
private:
	int heapSize;
	int realSize;
	std::priority_queue<T, std::vector<T>, _Comp> innerHeap;
	_Comp comp;
public:
	FixedSizeHeap():heapSize(1024), realSize(0){
	}
	FixedSizeHeap(int size):heapSize(size), realSize(0){
	}
	void push(const T & elem){
		if(realSize < heapSize){
			innerHeap.push(elem);
			realSize++;
			return ;
		}
		const T t = innerHeap.top();
		if(comp(t, elem)){
			innerHeap.pop();
			innerHeap.push(elem);
		}
	}
	void pop(){
		innerHeap.pop();
		realSize--;
		return ;
	}
	bool empty()const{
		return innerHeap.empty();
	}
	T top(){
		return innerHeap.top();
	}
};




}



#endif /* FIXEDSIZEHEAP_H_ */
