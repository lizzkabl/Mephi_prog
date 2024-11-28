#include <iostream>
#include "SortedSequenceOnSequence.h"
#include "DictionaryOnSequence.h"
#include "Statistic.h"
#include "test.h"
#include "Histogram.h"
using namespace std;

template<class T>
void Enter(SortedSequenceOnSequence<T>* seq, int* range)
{
	cout << "let's fullfill your sequence, " << "enter size of your sequence" << "\n";
	int size_1;
	cin >> size_1;
	while (size_1 < 1)
	{
		cout << "size have to be greater than 0\n";
		cin >> size_1;
	}
	int elem;

	cout << "enter your elements\n";
	for (int i = 0; i < size_1; i++)
	{
		cin >> elem;
		seq->Add(elem);
	}
	cout << "enter range\n";

	cin >> *range;
	
	while (*range < 1 )
	{
		cout << "range have to be greater than 1\n";
		cin >> *range;
	}
}

int main()
{
	RunAllTests();

	bool working = true;
	while (working)
	{
		SortedSequenceOnSequence<int> seq;
		int range;
		Enter(&seq, &range);
		Histogram<int> h;
		DictionaryOnSequence<int, int> dict= h.CreateHistogram(seq, range);
		Statistic<int> stat;

		for (int i = 0; i < dict.GetCount()-1; i++)
		{
			cout << "Set " << i << " {"<< seq.Get(dict.Get(i));
			for (int j = dict.Get(i)+1; j <  dict.Get(i+1); j++)
			{
				cout << ", " << seq.Get(j);
			}
			SortedSequenceOnSequence<int> help_seq(*seq.GetSubsequence(dict.Get(i), dict.Get(i + 1) - 1));
			cout << "} - Count:"<< seq.GetLength() << "\n";

			stat.PrintStatistics(std::cout, help_seq);
		}
		cout << "Set " << dict.GetCount()-1 << " {"<< seq.Get(dict.Get(dict.GetCount() - 1));
		for (int j = dict.Get(dict.GetCount() - 1)+1; j < seq.GetLength() ; j++)
		{
			cout <<", "<< seq.Get(j);
		}
		SortedSequenceOnSequence<int> help_seq(*seq.GetSubsequence(dict.Get(dict.GetCount() - 1), seq.GetLength() - 1));
		cout << "} - Count:" << seq.GetLength() << "\n";
		
		stat.PrintStatistics(std::cout, help_seq);

		cout << "\n"<<"\n";
		//histogram
		h.PrintHistogram(std::cout, dict, seq.GetLength());
		cout << "\n";
		//exit
		int exit;
		cout << "enter 1, if you want to end programm, if want to go on press 0\n";
		cin >> exit;
		if (exit == 1)
		{
			working = false;
		}
	}
}

