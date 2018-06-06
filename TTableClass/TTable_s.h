#pragma once






template<class TKey, class TValue>
struct TRecord
{
	TKey key;
	TValue value;
};



template <class TKey, class TValue>
class TTable
{
protected: 
		int dataCount;
		int eff;
		
public:	
	TTable()
		{
			dataCount = 0;
			eff = 0;
		}

	void resetEff()
	{
		eff = 0;
	}

	int getEff()
	{
		return eff;
	}

	
};