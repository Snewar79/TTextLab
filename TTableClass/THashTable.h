#pragma once




#include "TTable_s.h"





template <class TKey, class TValue>
class THashTable : public TTable<TKey, TValue>
{


protected:
		int size;
		TRecord<TKey, TValue> * tableTop;
		int curr;
		int step;
		int firstAmp;
public:

	THashTable(int _size)
	{
		curr = 0;
		size = _size;
		tableTop = new TRecord<TKey, TValue>[size];
		for (int i = 0; i < size; i++)
		{
			tableTop[i].key = "";
		}
		step = 177;

		//hashFunc("Lol");
	}


	int hashFunc(TKey key)
	{
		int out = 0;
		for (int i = 0; i < key.length(); i++)
		{
			out += (key[i] << 2) % 37;
		}
		return out;
	}

	int findRecord(TKey key)
	{
		int hash = hashFunc(key);
		int count = 0;
		curr = -1;
		eff++;
		int tmp = hash % size;

		while (tableTop[tmp].key != "" && tableTop[tmp].key != key)
		{
			if (tableTop[tmp].key == "&" && curr == -1) 
				curr = tmp;
			tmp += step;
			tmp %= size;
			eff++;
			if (count++ > size + 1)
			{
				return 0;
			}
		}

		if (tableTop[tmp].key == key)
		{
			curr = tmp;
			return 1;
		}
		else
		{
			if (curr == -1) curr = tmp;
			return 0;
		}

		throw - 1;
		
	}


	int insertRecord(TRecord<TKey, TValue> rec)
	{
		if (findRecord(rec.key))
			return 0;
		else
		{	
			int pl = curr % size;
			tableTop[pl] = rec;
			dataCount++;
			return 1;
			
		}
		return -1;
	}

	int deleteRecord(TKey key)
	{
		if (findRecord(key))
		{
			tableTop[curr] = TRecord<TKey, TValue>{ "&" };
				dataCount--;
				return 1;
		}
		return 0;	
	
	}


	int isFull()
	{
		return dataCount == size;
	}
	
	int isEmpty()
	{
		return dataCount == 0;
	}
	

	void reset()
	{
		curr = 0;
		while ((tableTop[curr] == "" || tableTop[curr] == "&") && curr < size)
		{
			curr++;
		}
	}


	void goNext()
	{
		curr++;
		while ((tableTop[curr] == "" || tableTop[curr] == "&") && curr < size)
		{
			curr++;
		}	
	}


	int isEnd()
	{
		return curr >= size;	
	}


};