#include "ListSequenceMutable.h"
#include <cassert>
#include "LinkedList.h"
#include "ShrdPtr.h"

void Test1_OfLinkedList()
{
	const int n = 3;
	int arr[n] = { 1 ,2 ,3 };

	LinkedList<int> list(arr, n);
	assert(list.GetLength() == n);
	assert(list.GetFirst() == arr[0]);
	assert(list.GetLast() == arr[n - 1]);
	for (int i = 0; i < n; i++)
	{
		assert(arr[i] == list.Get(i));
	}
}

void Test2_OfLinkedList()
{
	const int n1 = 3;
	int arr1[n1] = { 1 ,2 ,3 };
	const int element = 10;
	const int n2 = 4;
	int arr2[n2] = { 1 ,2 ,3, 10 };

	LinkedList<int> list(arr1, n1);
	list.Append(element);
	assert(list.GetLength() == n2);
	for (int i = 0; i < n2; i++)
	{
		assert((arr2[i] == list.Get(i)));
	}
}

void Test3_OfLinkedList()
{
	const int n1 = 3;
	int arr1[n1] = { 1 ,2 ,3 };
	const int element = 10;
	const int n2 = 4;
	int arr2[n2] = { 10, 1 ,2 ,3 };

	LinkedList<int> list(arr1, n1);
	list.Prepend(element);
	assert(list.GetLength() == n2);
	for (int i = 0; i < n2; i++)
	{
		assert(arr2[i] == list.Get(i));
	}
}

void Test4_OfLinkedList()
{
	const int n1 = 3;
	int arr1[n1] = { 1 ,2 ,3 };
	const int element = 10;
	const int position = 2;
	const int n2 = 4;
	int arr2[n2] = { 1 ,2 , 10 ,3 };

	LinkedList<int> list(arr1, n1);
	list.InsertAt(element, position);
	assert(list.GetLength() == n2);
	for (int i = 0; i < n2; i++)
	{
		assert(arr2[i] == list.Get(i));
	}
}

void Test1_OfListSequenceMutable()
{
    const int n = 3;
    int arr[n] = { 1, 2, 3 };

    ListSequenceMutable<int> list_seq(arr, n);
    assert(list_seq.GetLength() == n);
    assert(list_seq.GetFirst() == arr[0]);
    assert(list_seq.GetLast() == arr[n - 1]);
    for (int i = 0; i < n; i++)
    {
        assert(arr[i] == list_seq.Get(i));
    }
}

void Test2_OfListSequenceMutable()
{
    const int n1 = 3;
    int arr1[n1] = { 1, 2, 3 };
    const int element = 10;
    const int n2 = 4;
    int arr2[n2] = { 1, 2, 3, 10 };

    ListSequenceMutable<int> list_seq(arr1, n1);
    list_seq.Append(element);
    assert(list_seq.GetLength() == n2);
    for (int i = 0; i < n2; i++)
    {
        assert(arr2[i] == list_seq.Get(i));
    }
}

void Test3_OfListSequenceMutable()
{
    const int n1 = 3;
    int arr1[n1] = { 1, 2, 3 };
    const int element = 10;
    const int n2 = 4;
    int arr2[n2] = { 10, 1, 2, 3 };

    ListSequenceMutable<int> list_seq(arr1, n1);
    list_seq.Prepend(element);
    assert(list_seq.GetLength() == n2);
    for (int i = 0; i < n2; i++)
    {
        assert(arr2[i] == list_seq.Get(i));
    }
}

void Test4_OfListSequenceMutable()
{
    const int n1 = 3;
    int arr1[n1] = { 1, 2, 3 };
    const int element = 10;
    const int position = 2;
    const int n2 = 4;
    int arr2[n2] = { 1, 2, 10, 3 };

    ListSequenceMutable<int> list_seq(arr1, n1);
    list_seq.InsertAt(element, position);
    assert(list_seq.GetLength() == n2);
    for (int i = 0; i < n2; i++)
    {
        assert(arr2[i] == list_seq.Get(i));
    }
}

void Test5_OfListSequnceMutable()
{
	const int n1 = 5;
	int arr1[n1] = { 1 ,2 ,3, 4, 5 };

	ListSequenceMutable<int> list_seq(arr1, n1);
	for (int i = 0; i < n1; i++)
	{
		for (int j = i + 1; j < n1; j++)
		{
			ListSequenceMutable<int> sub_seq = *(list_seq.GetSubsequence(i, j));
			assert(sub_seq.GetLength() == j - i + 1);
			for (int x = i; x < j; x++)
			{

				assert(arr1[x] == sub_seq.Get(x - i));
			}
		}
	}
}



int main()
{
	Test1_OfListSequenceMutable();
	Test2_OfListSequenceMutable();
	Test3_OfListSequenceMutable();
	Test4_OfListSequenceMutable();
	Test5_OfListSequnceMutable();
	Test1_OfLinkedList();
	Test2_OfLinkedList();
	Test3_OfLinkedList();
	Test4_OfLinkedList();
}


