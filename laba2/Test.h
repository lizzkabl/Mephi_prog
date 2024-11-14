#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include "BubleSort.h"
#include "ShakerSort.h"
#include "ImprovedSelectionSort.h"
#include "QuickSort.h"
#include "ShrdPtr.h"
#include "ListSequenceMutable.h"
#include <cassert>
#include <string>
#include "Person.h"


void BubbleTestSortingByHeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));
    BubleSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.height < b.height; },
        [](const Person& a, const Person& b) { return a.height == b.height; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "Сортировка по росту выполнена некорректно");
    }
}

void BubbleTestSortingByFirstName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    BubleSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.first_name < b.first_name; },
        [](const Person& a, const Person& b) { return a.first_name == b.first_name; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).first_name <= seq->Get(i).first_name && "Сортировка по имени выполнена некорректно");
    }
}

void BubbleTestSortingByLastName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    BubleSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.last_name < b.last_name; },
        [](const Person& a, const Person& b) { return a.last_name == b.last_name; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).last_name <= seq->Get(i).last_name && "Сортировка по фамилии выполнена некорректно");
    }
}

void BubbleTestSortingByBirthYear()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    BubleSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.birthYear < b.birthYear; },
        [](const Person& a, const Person& b) { return a.birthYear == b.birthYear; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "Сортировка по году рождения выполнена некорректно");
    }
}

void BubbleTestSortingByWeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    BubleSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.weight < b.weight; },
        [](const Person& a, const Person& b) { return a.weight == b.weight; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "Сортировка по весу выполнена некорректно");
    }
}



void ISelectTestSortingByHeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    ImprovedSelectionSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.height < b.height; },
        [](const Person& a, const Person& b) { return a.height == b.height; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "Сортировка по росту выполнена некорректно");
    }
}

void ISelectTestSortingByFirstName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    ImprovedSelectionSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.first_name < b.first_name; },
        [](const Person& a, const Person& b) { return a.first_name == b.first_name; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).first_name <= seq->Get(i).first_name && "Сортировка по имени выполнена некорректно");
    }
}

void ISelectTestSortingByLastName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    ImprovedSelectionSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.last_name < b.last_name; },
        [](const Person& a, const Person& b) { return a.last_name == b.last_name; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).last_name <= seq->Get(i).last_name && "Сортировка по фамилии выполнена некорректно");
    }
}

void ISelectTestSortingByBirthYear()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    ImprovedSelectionSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.birthYear < b.birthYear; },
        [](const Person& a, const Person& b) { return a.birthYear == b.birthYear; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "Сортировка по году рождения выполнена некорректно");
    }
}

void ISelectTestSortingByWeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    ImprovedSelectionSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.weight < b.weight; },
        [](const Person& a, const Person& b) { return a.weight == b.weight; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "Сортировка по весу выполнена некорректно");
    }
}



void QuickTestSortingByHeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    QuickSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.height < b.height; },
        [](const Person& a, const Person& b) { return a.height == b.height; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "Сортировка по росту выполнена некорректно");
    }
}

void QuickTestSortingByFirstName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    QuickSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.first_name < b.first_name; },
        [](const Person& a, const Person& b) { return a.first_name == b.first_name; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).first_name <= seq->Get(i).first_name && "Сортировка по имени выполнена некорректно");
    }
}

void QuickTestSortingByLastName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    QuickSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.last_name < b.last_name; },
        [](const Person& a, const Person& b) { return a.last_name == b.last_name; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).last_name <= seq->Get(i).last_name && "Сортировка по фамилии выполнена некорректно");
    }
}

void QuickTestSortingByBirthYear()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    QuickSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.birthYear < b.birthYear; },
        [](const Person& a, const Person& b) { return a.birthYear == b.birthYear; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "Сортировка по году рождения выполнена некорректно");
    }
}

void QuickTestSortingByWeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    QuickSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.weight < b.weight; },
        [](const Person& a, const Person& b) { return a.weight == b.weight; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "Сортировка по весу выполнена некорректно");
    }
}


void ShakerTestSortingByHeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    ShakerSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.height < b.height; },
        [](const Person& a, const Person& b) { return a.height == b.height; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "Сортировка по росту выполнена некорректно");
    }
}

void ShakerTestSortingByFirstName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    ShakerSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.first_name < b.first_name; },
        [](const Person& a, const Person& b) { return a.first_name == b.first_name; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).first_name <= seq->Get(i).first_name && "Сортировка по имени выполнена некорректно");
    }
}

void ShakerTestSortingByLastName()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    ShakerSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.last_name < b.last_name; },
        [](const Person& a, const Person& b) { return a.last_name == b.last_name; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).last_name <= seq->Get(i).last_name && "Сортировка по фамилии выполнена некорректно");
    }
}

void ShakerTestSortingByBirthYear()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    ShakerSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.birthYear < b.birthYear; },
        [](const Person& a, const Person& b) { return a.birthYear == b.birthYear; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "Сортировка по году рождения выполнена некорректно");
    }
}

void ShakerTestSortingByWeight()
{
    auto persons = ReadPersonsFromFile("data.txt");
    ShrdPtr<MutableSequence<Person>> seq(new ListSequenceMutable<Person>(persons));

    ShakerSort<Person> sorter;
    sorter.Sort(seq, [](const Person& a, const Person& b) { return a.weight < b.weight; },
        [](const Person& a, const Person& b) { return a.weight == b.weight; });

    for (int i = 1; i < seq->GetLength(); ++i)
    {
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "Сортировка по весу выполнена некорректно");
    }
}