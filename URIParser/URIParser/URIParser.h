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
			scheme, //identifies unique schemes

			//user information
			authority,
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
			std::cout << "The URI is missing a scheme and path/authority\n\n";
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
	bool validScheme = true, auth_or_path_exists = false;

	std::string tempStr = str;
	//check for scheme
	if (tempStr.find("://") != std::string::npos)
	{
		scheme = tempStr.substr(0, tempStr.find(":/"));
		tempStr = tempStr.substr(tempStr.find(":/"));
		tempStr.erase(0, 3);
		//std::cout << tempStr << std::endl;
	}
	else if (tempStr.find(":\\") != std::string::npos)
	{
		scheme = tempStr.substr(0, tempStr.find(":\\"));
		tempStr = tempStr.substr(tempStr.find(":\\"));
		tempStr.erase(0, 2);
		//std::cout << tempStr << std::endl;
	}
	else if (tempStr.find(":"))
	{
		scheme = tempStr.substr(0, tempStr.find(":"));
		tempStr = tempStr.substr(tempStr.find(":"));
		tempStr.erase(0, 1);
		//std::cout << tempStr << std::endl;
	}
	else
	{
		validScheme = false;
		scheme = "NOT FOUND";
	}

	//check for the authority if there is any
	if (tempStr.find("@"))
	{
		authority = tempStr.substr(0, tempStr.find("@"));
		tempStr = tempStr.substr(tempStr.find("@") + 1);

		user = authority.substr(0, authority.find(":"));
		//usually not a good idea to include the password unencrypted but this is just to parse the URI
		//I am interested in cybersecurity though
		password = authority.substr(authority.find(":") + 1);
	}


	return validScheme && auth_or_path_exists;
}

