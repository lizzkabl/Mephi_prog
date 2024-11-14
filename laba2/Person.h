#pragma once
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>

struct Person 
{
    std::string first_name;
    std::string last_name;
    int birthYear;
    double height;
    float weight;


    friend std::wostream& operator<<(std::wostream& wos, const Person& person) 
    {
        wos << L"Имя: " << std::wstring(person.first_name.begin(), person.first_name.end())
            << L", Фамилия: " << std::wstring(person.last_name.begin(), person.last_name.end())
            << L", Год рождения: " << person.birthYear << L", Рост: " << person.height
            << L", Вес: " << person.weight;
        return wos;
    }

};

ListSequenceMutable<Person> ReadPersonsFromFile(const std::string& filename)
{
    ListSequenceMutable<Person> persons;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) 
    {
        std::stringstream ss(line);
        std::string first_name, last_name;
        int birthYear;
        double height;
        float weight;

        std::getline(ss, first_name, ',');
        std::getline(ss, last_name, ',');
        ss >> birthYear >> height >> weight;

        persons.Append({ first_name, last_name, birthYear, height, weight });
    }

    return persons;
}