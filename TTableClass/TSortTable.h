#pragma once

#include "TArrayTable.h"

template <class TKey, class TValue>
class TSortTable : public TArrayTable<TKey, TValue>
{


public:
	
	TSortTable(int _size) : TArrayTable(_size)
	{
		
	}
	

	int findRecord(TKey key)
	{
		int l = 0, r = dataCount - 1;
		int m;

		if (isEmpty())
		{
			curr = 0;
			return 0;
		}


		while (l <= r)
		{
			eff++;
			m = (l + r) / 2;
			if (tableTop[m].key == key)
			{
				curr = m;
				return 1;
			}
			
			if (tableTop[m].key > key)
			{
				r = m - 1;
			}

			if (tableTop[m].key < key)
			{
				l = m + 1;
			}
		}
		curr = r + 1;
		return 0;	
	}

	int insertRecord(TRecord<TKey, TValue> record)
	{

		if (isEmpty())
		{
			curr = 0;
			tableTop[0] = record;
			dataCount++;
			return 1;
		}


		if (findRecord(record.key))
		{
			return 0;
		}
		
		for (int i = dataCount; i > curr; i--)
		{
			tableTop[i] = tableTop[i - 1];
			eff++;
		}

		tableTop[curr] = record;
		dataCount++;
		return 1;

	}


	int deleteRecord(TKey key)
	{
		if (findRecord(key))
		{
			for (int i = curr; i < dataCount - 1; i++)
			{
				tableTop[i] = tableTop[i + 1];
			}
			dataCount--;
			return 1;
		}
		return 0;
	
	
	}

	void reset()
	{
		curr = 0;
	}

	void goNext()
	{
		curr++;
	}

	int isEnd()
	{
		if (curr == dataCount)
			return 1;
		else 
			return 0;
	}




	TValue getCurrValue()
	{
		return tableTop[curr].value;
	
	}


};