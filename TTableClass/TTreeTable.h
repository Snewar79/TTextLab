#pragma once
#include "TTable_s.h"
#include <stack>
template <class TKey, class TValue>
struct TNode {
	int bal;
	TRecord<TKey, TValue> record;
	TNode *pLeft, *pRight;
};

template <class TKey, class TValue>
class TTreeTable : public TTable<TKey, TValue> {
protected:


	TNode<TKey, TValue> *pRoot;

	TNode<TKey, TValue> *pCurr;

	std::stack<TNode<TKey, TValue>*> _stack;

	TNode<TKey, TValue> **pRes;

	int pos;

public:
	TTreeTable()
	{
		pRoot = pCurr = NULL;
	}

	bool findRecord(TKey _key) 
	{
		pRes = &pRoot;
		while (*pRes != NULL) 
		{
			eff++;
			if ((*pRes)->record.key == _key)
				return true;
			if ((*pRes)->record.key < _key)
				pRes = &(*pRes)->pRight;
			else pRes = &(*pRes)->pLeft;
		}
		return false;
	}

	void insertRecord(TRecord<TKey, TValue> _record)
	{
		if (!findRecord(_record.key))
		{
			*pRes = new TNode<TKey, TValue>();
			(*pRes)->record = _record;
			//(*pRes)->record.periodicity = 1;
			dataCount++;
		}
		//else //(*pRes)->record.periodicity++;

	}

	void Delete(TKey _key) 
	{
		if (!findRecord(_key)) return;
		TNode<TKey, TValue> *tmp = *pRes;
		if (!tmp->pLeft)
			*pRes = tmp->pRight;
		else if (!tmp->pRight)
			*pRes = tmp->pLeft;

		else 
		{
			TNode<TKey, TValue> *find = tmp->pLeft;
			TNode<TKey, TValue> **iter;
			iter = &(*pRes)->pLeft;
			while (find->pRight) 
			{
				eff++;
				iter = &(*iter)->pRight;
				find = find->pRight;
			}
			tmp->record = find->record;
			tmp = find;
			*iter = find->pLeft;
		}
		dataCount--;
		delete tmp;
	}
	virtual void clear() 
	{
		if (!dataCount) return;
		std::stack<TNode<TKey, TValue>*> st;
		while (!st.empty())
			st.pop();
		for (Reset(); !isEnd(); goNext())
			st.push(pCurr);
		while (!st.empty())
		{
			delete st.top();
			st.pop();
		}
		dataCount = 0;
		eff = 0;
		pCurr = pRoot = nullptr;
	}
	void Reset()
	{
		while (_stack.empty())
			_stack.pop();
		pos = 0;
		pCurr = pRoot;
		while (pCurr->pLeft != NULL) {
			_stack.push(pCurr);
			pCurr = pCurr->pLeft;
		}

	}
	bool isEnd()
	{
		return pos == dataCount;
	}

	void goNext()
	{
		pos++;
		if (pCurr->pRight != NULL) {
			pCurr = pCurr->pRight;
			while (pCurr->pLeft != NULL) {
				_stack.push(pCurr);
				pCurr = pCurr->pLeft;
			}
		}
		else if (!_stack.empty())
		{
			pCurr = _stack.top();
			_stack.pop();
		}
	}

	bool isFull() const {
		return false;
	}

	TRecord<TKey, TValue> getCurr()
	{ 
		return pCurr->record; 
	}
};