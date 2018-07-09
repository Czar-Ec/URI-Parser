//standard libs
#include <iostream>

//the URI Parser class
#include "URIParser.h"

int main()
{
	//variable that stores URI string to be parsed
	std::string uriStr;

	//message prompt
	std::cout << "Enter string to parse: " << std::endl;

	//input  to URI string variable
	std::cin >> uriStr;

	//debug if input is the same as output
	//std::cout << uriStr << std::endl;

	//instantiate a URIParser
	URIParser testURI = URIParser(uriStr);
	std::cout << testURI.getStr() << std::endl;

	//pause before ending the program
	system("PAUSE");
	return 0;
}