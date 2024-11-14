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
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "Сортировка по росту выполнена некорректно");
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
        assert(seq->Get(i - 1).firstName <= seq->Get(i).firstName && "Сортировка по имени выполнена некорректно");
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
        assert(seq->Get(i - 1).lastName <= seq->Get(i).lastName && "Сортировка по фамилии выполнена некорректно");
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
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "Сортировка по году рождения выполнена некорректно");
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
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "Сортировка по весу выполнена некорректно");
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
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "Сортировка по росту выполнена некорректно");
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
        assert(seq->Get(i - 1).firstName <= seq->Get(i).firstName && "Сортировка по имени выполнена некорректно");
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
        assert(seq->Get(i - 1).lastName <= seq->Get(i).lastName && "Сортировка по фамилии выполнена некорректно");
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
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "Сортировка по году рождения выполнена некорректно");
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
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "Сортировка по весу выполнена некорректно");
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
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "Сортировка по росту выполнена некорректно");
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
        assert(seq->Get(i - 1).firstName <= seq->Get(i).firstName && "Сортировка по имени выполнена некорректно");
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
        assert(seq->Get(i - 1).lastName <= seq->Get(i).lastName && "Сортировка по фамилии выполнена некорректно");
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
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "Сортировка по году рождения выполнена некорректно");
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
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "Сортировка по весу выполнена некорректно");
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
        assert(seq->Get(i - 1).height <= seq->Get(i).height && "Сортировка по росту выполнена некорректно");
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
        assert(seq->Get(i - 1).firstName <= seq->Get(i).firstName && "Сортировка по имени выполнена некорректно");
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
        assert(seq->Get(i - 1).lastName <= seq->Get(i).lastName && "Сортировка по фамилии выполнена некорректно");
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
        assert(seq->Get(i - 1).birthYear <= seq->Get(i).birthYear && "Сортировка по году рождения выполнена некорректно");
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
        assert(seq->Get(i - 1).weight <= seq->Get(i).weight && "Сортировка по весу выполнена некорректно");
    }
}