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
		std::cout <<
			"++++++++++++++++++++++++\n" <<
			e.what() << std::endl <<
			"++++++++++++++++++++++++\n\n"
			<< "Exiting program in 10 seconds...";
		Sleep(10000);
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

	//check if the URI is not empty
	if ((testURI.getStr().length() > 0))
	{
		//check if the URI is valid
		if (testURI.URITypeCheck(testURI.getStr()) >= 0)
		{
			std::cout << "----------------------------------------------------\n";
			std::cout << "URI is complete and valid\n";
			std::cout << "----------------------------------------------------\n";
		}
		else
		{
			std::cout << "----------------------------------------------------\n";
			std::cout << "The URI has errors/warnings:\n\n";
			for (auto list : testURI.getErrorList())
			{
				std::cout << list << std::endl;
			}
			std::cout << "----------------------------------------------------\n";
		}
	}
	else
	{
		std::cout << "Empty Input\n\n";
	}

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