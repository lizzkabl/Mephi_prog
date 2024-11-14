#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <string>

struct Person 
{
    std::string firstName;
    std::string lastName;
    int birthYear;
    double height;
    float weight;


    friend std::wostream& operator<<(std::wostream& wos, const Person& person) 
    {
        wos << L"Имя: " << std::wstring(person.firstName.begin(), person.firstName.end())
            << L", Фамилия: " << std::wstring(person.lastName.begin(), person.lastName.end())
            << L", Год рождения: " << person.birthYear << L", Рост: " << person.height
            << L", Вес: " << person.weight;
        return wos;
    }

};

std::vector<Person> ReadPersonsFromFile(const std::string& filename)
{
    std::vector<Person> persons;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) 
    {
        std::stringstream ss(line);
        std::string firstName, lastName;
        int birthYear;
        double height;
        float weight;

        std::getline(ss, firstName, ',');
        std::getline(ss, lastName, ',');
        ss >> birthYear >> height >> weight;

        persons.push_back({ firstName, lastName, birthYear, height, weight });
    }

    return persons;
}