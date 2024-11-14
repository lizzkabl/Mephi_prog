#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include "BubleSort.h"
#include "ShakerSort.h"
#include "ImprovedSelectionSort.h"
#include "QuickSort.h"
#include "C:\Users\user\source\repos\WindowsProject1_help\ShrdPtr.h"
#include "C:\Users\user\source\repos\WindowsProject1_help\ListSequenceMutable.h"
#include <cassert>
#include <string>
#include "Person.h"


void BubbleTestSortingByHeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    BubleSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.height < b.height; },
        [](const Person& a, const Person& b) { return a.height == b.height; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "���������� �� ����� ��������� �����������");
    }
}

void BubbleTestSortingByFirstName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    BubleSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.firstName < b.firstName; },
        [](const Person& a, const Person& b) { return a.firstName == b.firstName; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).firstName <= seq->Get(i).firstName && "���������� �� ����� ��������� �����������");
    }
}

void BubbleTestSortingByLastName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    BubleSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.lastName < b.lastName; },
        [](const Person& a, const Person& b) { return a.lastName == b.lastName; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).lastName <= seq->Get(i).lastName && "���������� �� ������� ��������� �����������");
    }
}

void BubbleTestSortingByBirthYear()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    BubleSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.birthYear < b.birthYear; },
        [](const Person& a, const Person& b) { return a.birthYear == b.birthYear; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "���������� �� ���� �������� ��������� �����������");
    }
}

void BubbleTestSortingByWeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    BubleSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.weight < b.weight; },
        [](const Person& a, const Person& b) { return a.weight == b.weight; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "���������� �� ���� ��������� �����������");
    }
}



void ISelectTestSortingByHeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    ImprovedSelectionSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.height < b.height; },
        [](const Person& a, const Person& b) { return a.height == b.height; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "���������� �� ����� ��������� �����������");
    }
}

void ISelectTestSortingByFirstName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    ImprovedSelectionSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.firstName < b.firstName; },
        [](const Person& a, const Person& b) { return a.firstName == b.firstName; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).firstName <= seq->Get(i).firstName && "���������� �� ����� ��������� �����������");
    }
}

void ISelectTestSortingByLastName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    ImprovedSelectionSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.lastName < b.lastName; },
        [](const Person& a, const Person& b) { return a.lastName == b.lastName; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).lastName <= seq->Get(i).lastName && "���������� �� ������� ��������� �����������");
    }
}

void ISelectTestSortingByBirthYear()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    ImprovedSelectionSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.birthYear < b.birthYear; },
        [](const Person& a, const Person& b) { return a.birthYear == b.birthYear; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "���������� �� ���� �������� ��������� �����������");
    }
}

void ISelectTestSortingByWeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    ImprovedSelectionSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.weight < b.weight; },
        [](const Person& a, const Person& b) { return a.weight == b.weight; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "���������� �� ���� ��������� �����������");
    }
}



void QuickTestSortingByHeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    QuickSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.height < b.height; },
        [](const Person& a, const Person& b) { return a.height == b.height; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "���������� �� ����� ��������� �����������");
    }
}

void QuickTestSortingByFirstName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    QuickSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.firstName < b.firstName; },
        [](const Person& a, const Person& b) { return a.firstName == b.firstName; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).firstName <= seq->Get(i).firstName && "���������� �� ����� ��������� �����������");
    }
}

void QuickTestSortingByLastName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    QuickSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.lastName < b.lastName; },
        [](const Person& a, const Person& b) { return a.lastName == b.lastName; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).lastName <= seq->Get(i).lastName && "���������� �� ������� ��������� �����������");
    }
}

void QuickTestSortingByBirthYear()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    QuickSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.birthYear < b.birthYear; },
        [](const Person& a, const Person& b) { return a.birthYear == b.birthYear; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "���������� �� ���� �������� ��������� �����������");
    }
}

void QuickTestSortingByWeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    QuickSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.weight < b.weight; },
        [](const Person& a, const Person& b) { return a.weight == b.weight; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "���������� �� ���� ��������� �����������");
    }
}


void ShakerTestSortingByHeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    ShakerSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.height < b.height; },
        [](const Person& a, const Person& b) { return a.height == b.height; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "���������� �� ����� ��������� �����������");
    }
}

void ShakerTestSortingByFirstName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    ShakerSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.firstName < b.firstName; },
        [](const Person& a, const Person& b) { return a.firstName == b.firstName; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).firstName <= seq->Get(i).firstName && "���������� �� ����� ��������� �����������");
    }
}

void ShakerTestSortingByLastName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    ShakerSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.lastName < b.lastName; },
        [](const Person& a, const Person& b) { return a.lastName == b.lastName; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).lastName <= seq->Get(i).lastName && "���������� �� ������� ��������� �����������");
    }
}

void ShakerTestSortingByBirthYear()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    ShakerSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.birthYear < b.birthYear; },
        [](const Person& a, const Person& b) { return a.birthYear == b.birthYear; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "���������� �� ���� �������� ��������� �����������");
    }
}

void ShakerTestSortingByWeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<ListSequenceMutable<Person>> seq(new ListSequenceMutable<Person>(persons));

    ShakerSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.weight < b.weight; },
        [](const Person& a, const Person& b) { return a.weight == b.weight; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "���������� �� ���� ��������� �����������");
    }
}