
#include "TTreeTable.h"
#include "TTable_s.h"
#include "TArrayTable.h"
#include "TSortTable.h"
#include "THashTable.h"
#include <time.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#define N 3000

TRecord<std::string, int> randRecord(int length);
std::string randSt(int length);

int main()
{
	std::srand(time(NULL));
	TTreeTable<std::string, int> treeTable;
	THashTable<std::string, int> hashTable(N);
	TSortTable<std::string, int> sortTable(N);
	TArrayTable<std::string, int> arrTable(N);
	std::string set[N];

	std::cout << "Testing on " << N << " records:\n\n";

	std::cout << "On inserting\n";
	for (int i = 0; i < N; i++)
	{
		
		TRecord<std::string, int> r = randRecord(3);
		set[i] = r.key;
		//TRecord<std::string, int> ins = randRecord(5);
		treeTable.insertRecord(r);
		hashTable.insertRecord(r);
		sortTable.insertRecord(r);
		arrTable.insertRecord(r);

	}
	std::cout << "AVG eff for each:\n";
	std::cout << "Tree " << treeTable.getEff()/N << "\n" << "Hash " << hashTable.getEff()/N << "\n" << "Array "<<  arrTable.getEff()/N << "\n" << "Sort "<< sortTable.getEff()/N << "\n";
	
	treeTable.resetEff();
	hashTable.resetEff();
	sortTable.resetEff();
	arrTable.resetEff();

	std::cout << "\nOn finding\n";
	for (int i = 0; i < N; i++)
	{
		bool random = rand() % 8;
		
		if (random < 1)
		{
			treeTable.findRecord(randSt(3));
			hashTable.findRecord(randSt(3));
			sortTable.findRecord(randSt(3));
			arrTable.findRecord(randSt(3));
		}
		else
		{
			treeTable.findRecord(set[i]);
			hashTable.findRecord(set[i]);
			sortTable.findRecord(set[i]);
			arrTable.findRecord(set[i]);


		}


	}
	std::cout << "AVG eff for each:\n";
	std::cout << "Tree " << treeTable.getEff() / N << "\n" << "Hash " << hashTable.getEff() / N << "\n" << "Array " << arrTable.getEff() / N << "\n" << "Sort " << sortTable.getEff() / N << "\n";


	


	return 0;
}

TRecord<std::string, int> randRecord(int length)
{

	std::string out;
	for (int i =0; i < length; i++)
		out += 'a' + std::rand() % 26;
	return TRecord<std::string, int>{out, 0};
}


std::string randSt(int length)
{

	std::string out;
	for (int i = 0; i < length; i++)
		out += 'a' + std::rand() % 26;

	return out;
}