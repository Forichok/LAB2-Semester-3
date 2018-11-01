#include "stdafx.h"
#include "phonebook.h"
#include <iostream>
#include <string>

int main()
{
	std::vector < std::string > found;
	std::string tmp;
	size_t n = 0, k = 0;
	phonebook a;
	a.ReadFromFile("base.txt");
	size_t swtch = 0;
	while (7)
	{
		system("cls");
		std::cout << "Input:" << std::endl
			<< "1 to add new Person" << std::endl
			<< "2 to find" << std::endl
			<< "3 to show all" << std::endl
			<< "4 to search by phone number" << std::endl
			<< "5 to show last operations" << std::endl
			<< "6 to reset last operations" << std::endl
			<< "0 to exit" << std::endl;
		std::string tmp;
		std::cin >> swtch;
		switch (swtch)
		{
		case 1:
			a.AddNewPerson(1);
			break;
		case 2:
			std::cout << "searching for: " ;
			std::getline(std::cin, tmp, ';');
			tmp[0] = ' ';
			found = a.FindByIterator(tmp);
			if (found.size() == 0) std::cout << "no results" << std::endl; else
				for (size_t i = 0; i < found.size(); i++) a.print(found[i]);
			std::cout << std::endl << "Do u wanna edit something? input number of Person in list u wanna edit OR input 0 to skip: ";
			std::cin >> k;
			if (k != 0)
			{
				std::cout << "1 to delete " << std::endl << "2 to edit" << std::endl;
				std::cin >> n;
				if (k<=found.size())
				a.EditFromSearch(found[k - 1], n);
			}
			break;
		case 3:
			a.PrintAll();
			break;
		case 4:
			std::cout << "search:" << std::endl;
			std::cin >> tmp;
			std::cout << a.PersonToStr(a[tmp]) << std::endl;
			break;
		case 5:
			a.PrintLogs();
			break;
		case 6:
			std::cout << "input number of operations u wanna reset" << std::endl;
			std::cin >> k;
			a.reset(k);
			break;
		case 7:
			a.SaveToFile();
			break;
		case 8:
			a.addALLL(100);
			break;
		case 0:
			a.SaveToFile();
			exit(0);
		}
		system("pause");
	}
	return 0;
}
