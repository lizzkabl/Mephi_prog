#pragma once
#include <cassert>
#include "SetOnSequence.h"
#include "SetOnBinaryTree.h"
#include "SortedSequenceOnSequence.h" 
#include "DictionaryOnSequence.h" 
#include "BinaryTree.h"
#include "Histogram.h"

void Test_SetOnSequence_InsertAndContains()
{
    SetOnSequence<int> set;
    set.Insert(5);
    set.Insert(3);
    set.Insert(8);

    assert(set.Contains(5) == true);
    assert(set.Contains(3) == true);
    assert(set.Contains(8) == true);
    assert(set.Contains(10) == false); 
}

void Test_SetOnSequence_Empty() 
{
    SetOnSequence<int> set;
    assert(set.Empty() == true); 
    set.Insert(1);
    assert(set.Empty() == false); 
}

void Test_SetOnSequence_Get() 
{
    SetOnSequence<int> set;
    set.Insert(1);
    set.Insert(2);
    set.Insert(3);

    assert(set.Get(0) == 1);
    assert(set.Get(1) == 2);
    assert(set.Get(2) == 3);
}

void Test_SetOnSequence_Pop() 
{
    SetOnSequence<int> set;
    set.Insert(1);
    set.Insert(2);
    set.Insert(3);

    set.Pop(2);

    assert(set.Contains(2) == false);
}

void Test_SetOnSequence_SubSet() 
{
    SetOnSequence<int> set1;
    SetOnSequence<int> set2;

    set1.Insert(1);
    set1.Insert(2);

    set2.Insert(1);

    assert(set1.SubSet(&set2) == true); 
    set2.Insert(3);

    assert(set2.SubSet(&set1) == false); 
}


void Test_SetOnBinaryTree_InsertAndContains()
{
    SetOnBinaryTree<int> set;
    set.Insert(5);
    set.Insert(3);
    set.Insert(8);

    assert(set.Contains(5) == true);
    assert(set.Contains(3) == true);
    assert(set.Contains(8) == true);
    assert(set.Contains(10) == false);
}

void Test_SetOnBinaryTree_Empty()
{
    SetOnBinaryTree<int> set;
    assert(set.Empty() == true);
    set.Insert(1);
    assert(set.Empty() == false);
}

void Test_SetOnBinaryTree_Get()
{
    SetOnBinaryTree<int> set;
    set.Insert(1);
    set.Insert(2);
    set.Insert(3);

    assert(set.Get(1) == 2);
    assert(set.Get(2) == 1); 
    assert(set.Get(3) == 3);  
}

void Test_SetOnBinaryTree_Pop()
{
    SetOnBinaryTree<int> set;
    set.Insert(1);
    set.Insert(2);
    set.Insert(3);

    set.Pop(2);

    assert(set.Contains(2) == false);
}

void Test_SetOnBinaryTree_SubSet()
{
    SetOnBinaryTree<int> set1;
    SetOnBinaryTree<int> set2;

    set1.Insert(1);
    set1.Insert(2);

    set2.Insert(1);

    assert(set1.SubSet(&set2) == true);

    set2.Insert(3);

    assert(set2.SubSet(&set1) == false); 
}



void Test_SortedSequenceOnSequence_Constructor()
{
    SortedSequenceOnSequence<int> sortedSeq;
    assert(sortedSeq.IsEmpty() == true);
    assert(sortedSeq.GetLength() == 0);
}

void Test_SortedSequenceOnSequence_AddElements()
{
    SortedSequenceOnSequence<int> sortedSeq;
    sortedSeq.Add(5);
    sortedSeq.Add(3);
    sortedSeq.Add(8);
    sortedSeq.Add(1);

    assert(sortedSeq.GetLength() == 4);
    assert(sortedSeq.Get(0) == 1);
    assert(sortedSeq.Get(1) == 3);
    assert(sortedSeq.Get(2) == 5);
    assert(sortedSeq.Get(3) == 8);
}

void Test_SortedSequenceOnSequence_GetFirstAndLast() 
{
    SortedSequenceOnSequence<int> sortedSeq;
    sortedSeq.Add(5);
    sortedSeq.Add(3);
    sortedSeq.Add(8);
    sortedSeq.Add(1);

    assert(sortedSeq.GetFirst() == 1);
    assert(sortedSeq.GetLast() == 8);
}

void Test_SortedSequenceOnSequence_IndexOf() 
{
    SortedSequenceOnSequence<int> sortedSeq;
    sortedSeq.Add(5);
    sortedSeq.Add(3);
    sortedSeq.Add(8);
    sortedSeq.Add(1);

    assert(sortedSeq.IndexOf(5) == 2);
    assert(sortedSeq.IndexOf(1) == 0);
    assert(sortedSeq.IndexOf(8) == 3);
}

void Test_SortedSequenceOnSequence_GetSubsequence() 
{
    SortedSequenceOnSequence<int> sortedSeq;
    sortedSeq.Add(5);
    sortedSeq.Add(3);
    sortedSeq.Add(8);
    sortedSeq.Add(1);

    SortedSequenceOnSequence<int>* subseq = sortedSeq.GetSubsequence(1, 3);

    assert(subseq->GetLength() == 3);
    assert(subseq->Get(0) == 3);
    assert(subseq->Get(1) == 5);
    assert(subseq->Get(2) == 8);

    delete subseq; 
}

void Test_SortedSequenceOnSequence_BinarySearch() {
    SortedSequenceOnSequence<int> sortedSeq;
    sortedSeq.Add(5);
    sortedSeq.Add(3);
    sortedSeq.Add(8);
    sortedSeq.Add(1);

    assert(sortedSeq.BinarySearch(5) == true);
    assert(sortedSeq.BinarySearch(2) == false); 
}

void Test_SortedSequenceOnSequence_IsEmpty() {
    SortedSequenceOnSequence<int> sortedSeq;

    assert(sortedSeq.IsEmpty() == true); 

    sortedSeq.Add(1);

    assert(sortedSeq.IsEmpty() == false); 
}



void Test_DictionaryOnSequence_Constructor()
{
    DictionaryOnSequence<int, std::string> dict;
    assert(dict.GetCount() == 0);
}

void Test_DictionaryOnSequence_AddAndGet() 
{
    DictionaryOnSequence<int, std::string> dict;
    dict.Add(1, "one");
    dict.Add(2, "two");
    dict.Add(3, "three");

    assert(dict.Get(1) == "one");
    assert(dict.Get(2) == "two");
    assert(dict.Get(3) == "three");
}

void Test_DictionaryOnSequence_ContainsKey() 
{
    DictionaryOnSequence<int, std::string> dict;
    dict.Add(1, "one");
    dict.Add(2, "two");

    assert(dict.ContainsKey(1) == true);
    assert(dict.ContainsKey(2) == true);
    assert(dict.ContainsKey(3) == false); 
}

void Test_DictionaryOnSequence_Remove()
{
    DictionaryOnSequence<int, std::string> dict;
    dict.Add(1, "one");
    dict.Add(2, "two");

    assert(dict.GetCount() == 2);

    dict.Remove(1);

    assert(dict.GetCount() == 1);
    assert(dict.ContainsKey(1) == false); 
}


void Test_BinaryTree_DeleteNode()
{
    BinaryTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);

    tree.DeleteNode(5);

    tree.DeleteNode(10);
    assert(tree.Search(15) == 15);
}

void Test_BinaryTree_Get()
{
    BinaryTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Insert(3);
    tree.Insert(7);

    assert(tree.Get(1) == 10);  
    assert(tree.Get(2) == 5); 
    assert(tree.Get(4) == 3);  
    assert(tree.Get(3) == 15); 
    assert(tree.Get(5) == 7);
}

void Test_Histogram_Create() 
{
    SortedSequenceOnSequence<int> seq;
    seq.Add(1);
    seq.Add(2);
    seq.Add(3);
    seq.Add(10);
    seq.Add(11);
    seq.Add(12);

    Histogram<int> histogram;
    DictionaryOnSequence<int, int> dict = histogram.CreateHistogram(seq, 5);

    assert(dict.GetCount() == 2); 
    assert(dict.Get(0) == 0);     
    assert(dict.Get(1) == 3);        

}

void Test_Histogram_CreateSingleElement()
{
    SortedSequenceOnSequence<int> seq;
    seq.Add(5);

    Histogram<int> histogram;
    DictionaryOnSequence<int, int> dict = histogram.CreateHistogram(seq, 5);

    assert(dict.GetCount() == 1);
    assert(dict.Get(0) == 0);   

}

void Test_Histogram_CreateMultipleRanges() 
{
    SortedSequenceOnSequence<int> seq;
    seq.Add(1);
    seq.Add(2);
    seq.Add(3);
    seq.Add(8);
    seq.Add(9);
    seq.Add(10);

    Histogram<int> histogram;
    DictionaryOnSequence<int, int> dict = histogram.CreateHistogram(seq, 3);

    assert(dict.GetCount() == 2); 
    assert(dict.Get(0) == 0);      
    assert(dict.Get(1) == 3);      
}



void RunAllTests() 
{
    Test_SetOnSequence_InsertAndContains();
    Test_SetOnSequence_Empty();
    Test_SetOnSequence_Get();
    Test_SetOnSequence_Pop();
    Test_SetOnSequence_SubSet();

    Test_SetOnBinaryTree_InsertAndContains();
    Test_SetOnBinaryTree_Empty();
    Test_SetOnBinaryTree_Get();
    Test_SetOnBinaryTree_Pop();
    Test_SetOnBinaryTree_SubSet();

    Test_SortedSequenceOnSequence_Constructor();
    Test_SortedSequenceOnSequence_AddElements();
    Test_SortedSequenceOnSequence_GetFirstAndLast();
    Test_SortedSequenceOnSequence_IndexOf();
    Test_SortedSequenceOnSequence_GetSubsequence();
    Test_SortedSequenceOnSequence_BinarySearch();
    Test_SortedSequenceOnSequence_IsEmpty();

    Test_DictionaryOnSequence_Constructor();
    Test_DictionaryOnSequence_AddAndGet();
    Test_DictionaryOnSequence_ContainsKey();
    Test_DictionaryOnSequence_Remove();

    Test_BinaryTree_DeleteNode();
    Test_BinaryTree_Get();


    Test_Histogram_Create();
    Test_Histogram_CreateSingleElement();
    Test_Histogram_CreateMultipleRanges();
}