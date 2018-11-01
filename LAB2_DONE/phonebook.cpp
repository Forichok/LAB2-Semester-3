#include "stdafx.h"
#include "phonebook.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

const std::array<char, 27> ar = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

std::string getrndstr() {
	int n;
	std::string  s;
	n = rand() % 8 + 3;
	for (int i = 0; i < n; i++) s += ar[rand() % 27];
	return s;
}

void phonebook::addALLL(size_t n)
{
	for (size_t i = 0; i < n; i++) {
		Person man;
		man.numbers.push_back(getrndstr());
		man.company = getrndstr();
		man.email = getrndstr();
		man.name = getrndstr();
		man.patronymic = getrndstr();
		man.post = getrndstr();
		man.surname = getrndstr();
		add(man, 0);
	}
}

std::vector<std::string>split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}


void phonebook::WriteToFile(const Person& man)
{
	std::ofstream fout("base.txt", std::ios_base::app);
	if (!fout)
	{
		std::cerr << "cannot open file" << std::endl;
		exit(1);
	}
	for (int i = 0; i < man.numbers.size(); i++)
		fout << man.numbers[i] << ' ';
	fout << man.name << ' ' << man.surname << ' ' << man.patronymic << ' ' << man.email << ' ' << man.company << ' ' << man.post << std::endl;
	fout.close();
}

void phonebook::ReadFromFile(const std::string& FileName)
{
	Person man;
	std::string str;
	std::ifstream fin(FileName, std::ios_base::in);
	if (!fin)
	{
		std::cerr << "cannot open file" << std::endl;
		exit(1);
	}
	while (getline(fin, str))
	{
		std::vector<std::string> sWords = split(str, ' ');
		Person man = VecToPerson(sWords);
		add(man, 0);
	}
}

void phonebook::print(const std::string& key)
{
	Person man = book[key];
	for (int i = 0; i < man.numbers.size(); i++)
		std::cout << man.numbers[i] << ' ';
	std::cout << man.name << ' ' << man.surname << ' ' << man.patronymic << ' ' << man.email << ' ' << man.company << ' ' << man.post << std::endl;
}

void phonebook::add(const Person& man, const size_t& writelogs)
{
	if (!man.numbers.empty()) {
		if (writelogs == 1)
		{
			edited edit;
			edit.action = "added";
			edit.current = man;
			log.push_back(edit);
		}
		book.add(man, man.numbers[0]);
	}
}

void phonebook::del(const std::string& num)
{
	book.erase(num);
}

void phonebook::EditFromSearch(const std::string& num, const size_t& delORedit)
{
	edited edit;
	edit.last = book[num];
	if (delORedit == 1)
		edit.action = "deleted";
	if (delORedit == 2)
	{
		edit.action = "edited";
		edit.current = AddNewPerson(0);
	}
	del(num);
	log.push_back(edit);
}

void phonebook::PrintAll()
{
	for (auto it = book.begin(); it != book.end(); it++)
	{
		for (auto it_map = it->begin(); it_map != it->end(); it_map++)
		{
			for (int i = 0; i <it_map->second.numbers.size(); i++)
				std::cout << it_map->second.numbers[i] << ' ';
			std::cout << it_map->second.name << ' ' << it_map->second.surname << ' ' << it_map->second.patronymic << ' ' << it_map->second.email << ' ' << it_map->second.company << ' ' << it_map->second.post << std::endl;
		}
	}
}

void phonebook::SaveToFile()
{
	std::ofstream fout("base.txt", std::ios_base::trunc);
	if (!fout)
	{
		std::cerr << "cannot open file" << std::endl;
		exit(1);
	}
	for (auto it = book.begin(); it != book.end(); it++)
	{
		for (auto it_map = it->begin(); it_map != it->end(); it_map++) {
			for (int i = 0; i < it_map->second.numbers.size(); i++)
				fout << it_map->second.numbers[i] << ' ';
			fout << it_map->second.name << ' ' << it_map->second.surname << ' ' << it_map->second.patronymic << ' ' << it_map->second.email << ' ' << it_map->second.company << ' ' << it_map->second.post << std::endl;
		}
	}
	fout.close();
}

void phonebook::reset(size_t num)
{
	if (num > log.size()) num = log.size();
	if (num <= log.size()) {
		std::vector<edited>::reverse_iterator it = log.rbegin();
		for (size_t i = 0; i<num; i++)
		{
			if (it->action == "added")
				del(it->current.numbers[0]);
			if (it->action == "deleted")
				add(it->last, 0);
			if (it->action == "edited")
			{
				del(it->current.numbers[0]);
				add(it->last, 0);
			}
			it++;
			log.pop_back();
		}
	}
}

void phonebook::PrintLogs()
{
	if (log.size() == 0)std::cout << "there are no last operations" << std::endl;
	for (std::vector<edited>::iterator it = log.begin(); it != log.end(); it++)
	{
		if (it->action == "added")	std::cout << PersonToStr(it->current) << "  HAS BEEN ADDED" << std::endl;
		if (it->action == "deleted") std::cout << PersonToStr(it->last) << "  HAS BEEN DELETED" << std::endl;
		if (it->action == "edited") std::cout << PersonToStr(it->last) << "  HAS BEEN CHANGED TO " << PersonToStr(it->current) << std::endl;
	}
}

std::vector<std::string> phonebook::FindByIterator(const std::string& req)
{
	std::vector<std::string> sWords = split(req, ' ');
	sWords.erase(sWords.begin());
	std::string data;
	std::vector<std::string> found;
	for (auto it = book.begin(); it != book.end(); it++)
	{
		for (auto it_map = it->begin(); it_map != it->end(); it_map++)
		{
			int count = 0;
			for (int n = 0; n < sWords.size(); n++)
			{
				for (int i = 0; i <it_map->second.numbers.size(); i++)
				if (it_map->second.numbers[i].find(sWords[n], 0) != -1) count++;
				if (it_map->second.name.find(sWords[n], 0) != -1) count++;
				if (it_map->second.surname.find(sWords[n], 0) != -1) count++;
				if (it_map->second.patronymic.find(sWords[n], 0) != -1) count++;
				if (it_map->second.post.find(sWords[n], 0) != -1) count++;
				if (it_map->second.company.find(sWords[n], 0) != -1) count++;
				if (it_map->second.email.find(sWords[n], 0) != -1) count++;
			}
			if (count == sWords.size())
				found.push_back(it_map->second.numbers[0]);
		}
	}
	return found;
}

std::string phonebook::PersonToStr(const Person& man)
{
	std::string data;
	for (int i = 0; i < man.numbers.size(); i++)
		data += man.numbers[i];
	data = ' ' + man.name + ' ' + man.surname + ' ' + man.patronymic + ' ' + man.email + ' ' + man.company + ' ' + man.post;
	return data;
}

Person phonebook::VecToPerson(std::vector<std::string> sWords)
{
	auto size = sWords.size();
	if (size >= 7)
	{
		Person man;
		for (size_t i = 0; i < size - 6; i++)
			man.numbers.push_back(sWords[i]);
		man.name = sWords[size - 6];
		man.surname = sWords[size - 5];
		man.patronymic = sWords[size - 4];
		man.email = sWords[size - 3];
		man.company = sWords[size - 2];
		man.post = sWords[size - 1];
		return man;
	}
}

Person phonebook::AddNewPerson(const size_t& writelogs)
{
	Person man;
	std::string tmp = "";
	std::cout << "input numbers (0 to stop)" << std::endl;
	while (7)
	{
		std::cin >> tmp;
		if (tmp == "0"&&man.numbers.size() == 0)
		{
			std::cout << "input fckng number morron" << std::endl;
			continue;
		}
		if (tmp == "0")break;
		man.numbers.push_back(tmp);
	}
	std::cout << "input name: ";
	std::cin >> man.name;
	std::cout << "input surname: ";
	std::cin >> man.surname;
	std::cout << "input patronymic: ";
	std::cin >> man.patronymic;
	std::cout << "input email: ";
	std::cin >> man.email;
	std::cout << "input company: ";
	std::cin >> man.company;
	std::cout << "input post: ";
	std::cin >> man.post;
	add(man, writelogs);
	WriteToFile(man);
	return man;
}

Person phonebook::operator[](const std::string& key)
{
	return book[key];
}

Person phonebook::StrToPerson(const std::string& str)
{
	Person man;
	std::vector<std::string> sWords = split(str, ' ');
	return VecToPerson(sWords);
}