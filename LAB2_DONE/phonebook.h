#pragma once
#include "hashtable.h"
#include <typeindex>
struct Person
{
	std::vector<std::string> numbers;
	std::string surname;
	std::string name;
	std::string patronymic;
	std::string email;
	std::string company;
	std::string post;
};

template <typename KEY>
class hash
{
public:
	size_t operator() (KEY key)
	{
		int hash = 0;
		if (typeid(key) == typeid(std::string)) {
			for (int i = 0; i < key.length(); i++)
			{
				hash = (hash * 17 + key[i]) % SIZE;
			}
			return hash;
		}
	}
	/*size_t operator() (KEY key) const
	{
	char* tmp = reinterpret_cast<char*>(&key);
	const size_t size = sizeof(key);
	int hash = 0;
	for (size_t i = 0; i < size; i++)
	{
	hash += tmp[i] * pow(2, i);
	}
	return hash;
	}
	*/
};

struct edited
{
	std::string action;
	Person last;
	Person current;
};
class phonebook
{
	std::vector < edited> log;
	hashtable<Person, std::string, hash<std::string>> book;
	Person StrToPerson(const std::string&);
	Person VecToPerson(std::vector<std::string>);

public:
	void WriteToFile(const Person&);
	void ReadFromFile(const std::string&);
	void print(const std::string&);
	void add(const Person&, const size_t&);
	void del(const std::string&);
	void PrintLogs();
	void EditFromSearch(const std::string&, const size_t&);
	void PrintAll();
	void SaveToFile();
	void reset(size_t);
	void addALLL(size_t);
	std::string PersonToStr(const Person&);
	std::vector<std::string> find(const std::string&);
	std::vector<std::string> FindByIterator(const std::string&);
	Person operator[](const std::string&);
	Person AddNewPerson(const size_t&);
};


