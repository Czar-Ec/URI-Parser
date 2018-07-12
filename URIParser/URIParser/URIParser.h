#pragma once
#include <string>
#include <iostream>

#include <algorithm>
#include <regex>

/**
* URIParser
* class that takes in a string input and automatically parses
* the input into components of a URI and also checks if the URI
* is syntactically valid
* 
* created by Czar Ian Echavez (CzarEc)
*/
class URIParser
{
	public:
		URIParser(std::string uriStr);
		~URIParser();

		//getters for each specific part of the URI
		//no setters as each instance of URIParser should be for a specific uriStr input

		/**
		* getStr
		* returns input string
		* @return str
		*/
		std::string getStr() { return str; };

		/**
		* getScheme
		* returns the protocol or scheme of the URI
		* @return scheme
		*/
		std::string getScheme() { return scheme; };

		/**
		* getUser
		* returns the parsed user string
		* @return user
		*/
		std::string getUser() { return user; };

		/**
		* getPassword
		* returns the parsed password string
		* @return password
		*/
		std::string getPassword() { return password; };

		/**
		* getHost
		* returns the parsed host (subdomain and domain) string
		* @return host
		*/
		std::string getHost() { return host; };

		/**
		* getPort
		* returns the port (if there are any found)
		* @return port
		*/
		std::string getPort() { 
			if (port < 0)
				return "NO / DEFAULT PORT";
			else
			return std::to_string(port); };

		/**
		* getPath
		* returns the parsed path string
		* @return path
		*/
		std::string getPath() { return path; };

		/**
		* getQuery
		* returns the parsed query string
		* @return query
		*/
		std::string getQuery() { return query; };

		/**
		* getFragment
		* returns the parsed fragment string
		* @return fragment
		*/
		std::string getFragment() { return fragment; };

		std::string printAll();

		int URITypeCheck(std::string str);

		/**
		* getErrorList
		* returns a vector list of the errors found when parsing the input string
		* @return std::vector<std::string> errorList
		*/
		std::vector<std::string> getErrorList() { return errorList; }

		/**
		* URI Types
		* constant variables used to determine the different type of URI for each string input
		*/
		const int URL_TYPE_URI = 0,
			FILE_TYPE_URI = 1,
			URN_TYPE_URI = 2,
			INVALID_URN = -1;

	private:

		/**
		* errorListAdd
		* adds an error to the error list to be printed out for later
		* @param std::string error
		*/
		void errorListAdd(std::string error) { errorList.push_back(error); }

		bool checkHostDomain(std::string str);

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

		std::vector<std::string> errorList;
};

/**
* URIParser
* class constructor
*
* @param std::string uriStr
*/
URIParser::URIParser(std::string uriStr)
{
	str = uriStr;

	//port initially set to -1
	port = -1;
}

/**
* ~URIParser
* default class destructor
*/
URIParser::~URIParser()
{
}

/**
* printAll
* function that returns a string which holds all information relevant to the URI
*
* @return std::string
*/
std::string URIParser::printAll()
{
	return
		"Scheme: " + getScheme() + "\n" +
		"User: " + getUser() + "\n" +
		"Password: " + getPassword() + "\n" +
		"Host: " + getHost() + "\n" +
		"Port: " + getPort() + "\n" +
		"Path: " + getPath() + "\n" +
		"Query: " + getQuery() + "\n" +
		"Fragment: " + getFragment() + "\n" +
		"_______________________________\n";
}

/**
* URITypeCheck
* function to check which type of URI the input string is
* as well as parsing the string automatically
*
* @param std::string str
* @return 
*/
int URIParser::URITypeCheck(std::string str)
{
	int uriType = INVALID_URN;
	bool validScheme = true, auth_or_path_exists = false;

	std::string tempStr = str;
	//check for schemes
	//"://" is used for web resources
	if (tempStr.find("://") != std::string::npos)
	{
		//URL type URI
		uriType = URL_TYPE_URI;

		scheme = tempStr.substr(0, tempStr.find("://"));
		tempStr = tempStr.substr(tempStr.find("://"));
		tempStr.erase(0, 3);
		//std::cout << tempStr << std::endl;

		//check for the authority if there are any
		if (tempStr.find("/") != std::string::npos)
		{
			authority = tempStr.substr(0, tempStr.find("/"));
			tempStr = tempStr.substr(tempStr.find("/") + 1);

			//checking if there are values for authority
			if (!authority.empty())
			{
				//find if an '@' symbol exists, otherwise the authority is the host
				if (authority.find("@") != std::string::npos)
				{
					//check if password was included
					if (authority.find(":") != std::string::npos)
					{
						user = authority.substr(0, authority.find(":"));
						authority = authority.substr(authority.find(":"));
						//usually not a good idea to include the password unencrypted but this is just to parse the URI
						//I am interested in cybersecurity though
						password = authority.substr(authority.find(":") + 1, authority.find("@") - 1);
						authority = authority.substr(authority.find("@") + 1);

						//check if password and user are not empty
						if (!user.empty() && !password.empty())
						{
							if (checkHostDomain(host))
							{
								auth_or_path_exists = true;
							}
						}
						else
						{
							errorListAdd("User or password is empty\n");
						}
					}
					else
					{
						user = authority.substr(0, authority.find("@"));
						password = "NONE";
						authority = authority.substr(authority.find("@") + 1);
						if (!user.empty())
						{
							if (checkHostDomain(host))
							{
								auth_or_path_exists = true;
							}								
						}
						else
						{
							errorListAdd("URI user not found when '@' is detected");
						}
					}

					//validation of the host is usually "*.*" which means there needs to 
					//be a (sub)domain and a top level domain, as well as for IPv4/6 addresses
					host = authority;

					if (checkHostDomain(host))
					{	}
				}
				else
				{
					user = "NONE";
					password = "NONE";
					host = authority;

					if (checkHostDomain(host))
					{
						auth_or_path_exists = true;
					}
				}
			}
			//empty authority = no user, password and host
			else
			{
				user = "NOT FOUND";
				password = "NOT FOUND";
				host = "NOT FOUND";

				errorListAdd("URI has no scheme or path\n");

				auth_or_path_exists = false;
			}
		}
		//no next '/' symbol means no authority
		else
		{
			host = "NOT FOUND";
			errorListAdd("URI host not found");
		}
	}
	//":\" is for local resources
	else if (tempStr.find(":\\") != std::string::npos)
	{
		//file system URI
		uriType = FILE_TYPE_URI;

		scheme = tempStr.substr(0, tempStr.find(":\\"));
		tempStr = tempStr.substr(tempStr.find(":\\"));
		tempStr.erase(0, 2);
		//std::cout << tempStr << std::endl;

		path = tempStr;
		//so long as there is a scheme, file paths are valid
		if (!scheme.empty())
		{
			auth_or_path_exists = true;
		}
		else
		{
			errorListAdd("URI scheme not found");
		}
	}
	//":"
	else if (tempStr.find(":") != std::string::npos)
	{
		//URN URI
		uriType = URN_TYPE_URI;

		scheme = tempStr.substr(0, tempStr.find(":"));
		tempStr = tempStr.substr(tempStr.find(":"));
		tempStr.erase(0, 1);
		//std::cout << tempStr << std::endl;

		//everything else is a path
		path = tempStr;

		//if scheme or path is empty, it is not valid
		if (!scheme.empty() && !path.empty())
		{
			auth_or_path_exists = true;
		}
		else
		{
			errorListAdd("URI scheme or path not found");
		}
	}
	else
	{
		validScheme = false;
		scheme = "NOT FOUND";
		errorListAdd("URI scheme and path not found");
	}

	if (!validScheme || !auth_or_path_exists)
	{
		uriType = -1;
	}

	return uriType;
}

/**
* checkHostDomain
* function that checks the regex syntax of the host domain for validity
*
* @param std::string str
* @return valid
*/
bool URIParser::checkHostDomain(std::string str)
{
	//regex check for the host
	//regex taken and modified from: https://stackoverflow.com/questions/36903985/email-validation-in-c
	std::regex domain("(\\w+)(\\.|_)?(\\w*)\.(\\w+)(\\.(\\w+))+");
	if (std::regex_match(str, domain))
	{
		//std::cout << "match\n";
		return true;
	}
	else
	{
		//std::cout << "no match\n";
		errorListAdd("URI host domain is not valid");
		return false;
	}
}

