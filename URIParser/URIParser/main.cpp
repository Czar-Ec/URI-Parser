//standard libs
#include <iostream>

//the URI Parser class
#include "URIParser.h"

int main()
{
	//variable that stores URI string to be parsed
	std::string uriStr;

	//message prompt
	std::cout << "Enter string to parse: \n";

	std::cin >> uriStr;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Not a valid number. Please reenter: ";
		std::cin >> uriStr;
	}

	URIParser testURI = URIParser(uriStr);

	//Print individual components
	std::cout <<
		"Scheme: " << testURI.getScheme() << std::endl <<
		"User: " << testURI.getUser() << std::endl <<
		"Password: " << testURI.getPassword() << std::endl <<
		"Host: " << testURI.getHost() << std::endl <<
		"Port: " << testURI.getPort() << std::endl <<
		"Path: " << testURI.getPath() << std::endl <<
		"Query: " << testURI.getQuery() << std::endl <<
		"Fragment: " << testURI.getFragment() << std::endl << std::endl;

	//or print everything
	//std::cout << testURI.printAll() << std::endl;
	

	//pause before ending the program
	system("PAUSE");
	return 0;
}