//standard libs
#include <iostream>

//the URI Parser class
#include "URIParser.h"

int main()
{
	//error handling
	try {
		//variable that stores URI string to be parsed
		std::string uriStr;

		//message prompt
		std::cout << "Enter string to parse: " << std::endl;

		std::cout << "\n\n";

		std::cin >> uriStr;



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
	}
	catch(const std::exception &e)
	{
		std::cout << "\nPlease stop trying to break this thing\n\n";
	}
	

	//pause before ending the program
	system("PAUSE");
	return 0;
}