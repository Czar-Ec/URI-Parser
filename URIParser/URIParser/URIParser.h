#pragma once
#include <string>
#include <iostream>

#include <algorithm>


class URIParser
{
	public:
		URIParser(std::string uriStr);
		~URIParser();

		//getters for each specific part of the URI
		//no setters as each instance of URIParser should be for a specific uriStr input


		std::string getStr() { return str; };
		std::string getProtocol() { return protocol; };
		std::string getScheme() { return scheme; };
		std::string getUser() { return user; };
		std::string getPassword() { return password; };
		std::string getHost() { return host; };
		int getPort() { return port; };
		std::string getPath() { return path; };
		std::string getQuery() { return query; };
		std::string getFragment() { return fragment; };

		std::string printAll();

		//regex check, to validate each part of the URI as valid or not
		bool regexCheck(std::string str);

	private:
		//string variables to store the specific parts of the URI
		std::string
			str, // save the string used to instantiate the parser
			protocol, //protocol type
			scheme, //identifies unique schemes

			//user information
			user,
			password,

			//ipv4/6 target address
			host,

			//path to the unique resource
			path,

			//query for the specific resource
			query,

			//allows identification of another resource
			fragment;
		
		//access port
		int	port;
};

//constructor
URIParser::URIParser(std::string uriStr)
{
	str = uriStr;

	//check if the URI is not empty
	if ((str.length() != 0))
	{
		//check if the URI is valid
		if (regexCheck(str))
		{
			std::cout << "URI is complete and valid\n\n";
		}
		else
		{
			std::cout << "The URI is missing a protocol or scheme\n\n";
		}
	}
}

//default destructor
URIParser::~URIParser()
{
}

inline std::string URIParser::printAll()
{
	return
		"Protocol: " + getProtocol() + "\n" +
		"Scheme: " + getScheme() + "\n" +
		"User: " + getUser() + "\n" +
		"Password: " + getPassword() + "\n" +
		"Host: " + getHost() + "\n" +
		"Port: " + std::to_string(getPort()) + "\n" +
		"Path: " + getPath() + "\n" +
		"Query: " + getQuery() + "\n" +
		"Fragment: " + getFragment() + "\n";
}

bool URIParser::regexCheck(std::string str)
{
	bool valid = true;

	std::string tempStr = str;

	//check for protocol
	if (tempStr.find("://") != std::string::npos)
	{
		protocol = tempStr.substr(0, tempStr.find("://"));
		tempStr = tempStr.substr(tempStr.find("://"));
	}
	else if (tempStr.find(":\\") != std::string::npos)
	{
		protocol = tempStr.substr(0, tempStr.find(":\\"));
		tempStr = tempStr.substr(tempStr.find(":\\"));
	}
	else
	{
		valid = false;
		protocol = "NOT FOUND";
	}

	std::cout << tempStr << std::endl;


	return valid;
}

