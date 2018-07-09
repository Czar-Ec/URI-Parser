#pragma once
#include <string>
#include <iostream>


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

		//regex check, to validate each part of the URI as valid or not
		bool regexCheck(std::string str, int checkType);

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
}

//default destructor
URIParser::~URIParser()
{
}

bool URIParser::regexCheck(std::string str, int checkType)
{
	return false;
}

