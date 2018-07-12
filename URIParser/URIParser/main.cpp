//standard libs
#include <iostream>
#include <conio.h>
#include <Windows.h>

//the URI Parser class
#include "URIParser.h"

void parse();

int main()
{
	try
	{
		//while loop acts as a menu
		int menuOpt = -1;

		while (menuOpt != 2)
		{
			std::cout << "\nURI Parser Menu:\n" <<
				"1 - Parse URI\n2 - Exit Program\n";

			std::cin >> menuOpt;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
			else
			{
				if (menuOpt == 1)
				{
					std::cout << std::endl << std::endl;
					parse();
					menuOpt = -1;
				}
				//ignore menu 2
				if (menuOpt == 2 || menuOpt == -1)
				{
				}
				else
				{
					std::cout << "Invalid Input\n";
				}
			}
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl
			<< "Exiting program...";
		Sleep(3000);
		return 0;
	}

	//pause before ending the program
	system("PAUSE");
	return 0;
}

void parse()
{
	//variable that stores URI string to be parsed
	std::string uriStr;

	//message prompt
	std::cout << "Enter string to parse: \n";

	std::cin >> uriStr;

	URIParser testURI = URIParser(uriStr);

	//Print individual components
	/*std::cout <<
		"Scheme: " << testURI.getScheme() << std::endl <<
		"User: " << testURI.getUser() << std::endl <<
		"Password: " << testURI.getPassword() << std::endl <<
		"Host: " << testURI.getHost() << std::endl <<
		"Port: " << testURI.getPort() << std::endl <<
		"Path: " << testURI.getPath() << std::endl <<
		"Query: " << testURI.getQuery() << std::endl <<
		"Fragment: " << testURI.getFragment() << std::endl << std::endl;*/

	//or print everything
	std::cout << testURI.printAll() << std::endl;
}