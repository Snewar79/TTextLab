#pragma once


#include "TTable_s.h"




template <class TKey, class TValue>
class TArrayTable : public TTable<TKey, TValue>
{
	
protected:
	TRecord<TKey, TValue> * tableTop;
	int size;
	int curr;

public:
	TArrayTable(int _size = 50)
	{
		size = _size;
		tableTop = new TRecord<TKey, TValue>[size];
		curr = 0;
	}

	int findRecord(TKey key)
	{

		curr = 0;
		for (int i = 0; i < dataCount; i++)
		{
			eff++;
		
			if (tableTop[curr].key == key)
			{
				//curr = i;
				return 1;
			}
			else
			{
				curr++;
			}

		}
		return 0;
	}

	int insertRecord(TRecord<TKey, TValue> rec)
	{
		if (findRecord(rec.key))
		{
			return 0;
		}

		if (!isFull())
		{
			tableTop[curr] = rec;
			dataCount++;
			return 1;
		}

		throw - 1;
		
	}


	int deleteRecord(TKey key)
	{
		if (findRecord(key))
		{
			tableTop[curr] = tableTop[dataCount];
			dataCount--;
			return 1;
		}
		return 0;
	
	}


	int isFull()
	{
		if (dataCount == size)
			return 1;
		else 
			return 0;
	}
	
	int isEmpty()
	{
		if (dataCount == 0)
			return 1;
		else
			return 0;	
	}



	~TArrayTable()
	{
		delete[] tableTop;
	
	}


};