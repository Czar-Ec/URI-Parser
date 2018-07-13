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
			if (port == -1)
				return "NO / DEFAULT PORT";
			if (port < -1)
				return "ERROR PARSING PORT";
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

		bool parseURN(std::string tempStr);
		bool parseFileURI(std::string tempStr);
		bool parseURL(std::string tempStr);

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

		auth_or_path_exists = parseURL(tempStr);
	}
	//":\" is for local resources
	else if (tempStr.find(":\\") != std::string::npos)
	{
		//file system URI
		uriType = FILE_TYPE_URI;

		auth_or_path_exists = parseFileURI(tempStr);
	}
	//":"
	else if (tempStr.find(":") != std::string::npos)
	{
		//URN URI
		uriType = URN_TYPE_URI;

		auth_or_path_exists = parseURN(tempStr);
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
	std::regex ldapHost("\[(\w)\]");
	if (str == "localhost")
	{
		return true;
	}
	else
	{
		if (std::regex_match(str, domain) || std::regex_match(str, ldapHost))
		{
			//std::cout << "match\n";
			return true;
		}
		else
		{
			//std::cout << "no match\n";
			errorListAdd("URI host domain is MAY NOT be valid");
			return false;
		}
	}
}

/**
* parseURN
* function that parses URN type URIs
*
* @param std::string tempStr
* @return valid
*/
bool URIParser::parseURN(std::string tempStr)
{
	bool valid = false;

	scheme = tempStr.substr(0, tempStr.find(":"));
	tempStr = tempStr.substr(tempStr.find(":"));
	tempStr.erase(0, 1);
	//std::cout << tempStr << std::endl;

	//everything else is a path
	path = tempStr;

	//if scheme or path is empty, it is not valid
	if (!scheme.empty() && !path.empty())
	{
		valid = true;
	}
	else
	{
		errorListAdd("URI scheme or path not found");
	}

	return valid;
}

/**
* parseFileURI
* function that parses file system URIs
*
* @param std::string tempStr
* @return valid
*/
bool URIParser::parseFileURI(std::string tempStr)
{
	bool valid = false;

	scheme = tempStr.substr(0, tempStr.find(":\\"));
	tempStr = tempStr.substr(tempStr.find(":\\"));
	tempStr.erase(0, 2);
	//std::cout << tempStr << std::endl;

	path = tempStr;
	//so long as there is a scheme, file paths are valid
	if (!scheme.empty())
	{
		valid = true;
	}
	else
	{
		errorListAdd("URI scheme not found");
	}

	return valid;
}

/**
* parseURL
* function that parses URL type URIs
*
* @param std::string tempStr
* @return valid
*/
bool URIParser::parseURL(std::string tempStr)
{
	bool valid = false;

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
				//separate user and password from authority
				std::string uspwd = authority.substr(0, authority.find("@"));
				authority = authority.substr(authority.find("@"));

				//check if password was included
				if (uspwd.find(":") != std::string::npos)
				{
					user = uspwd.substr(0, uspwd.find(":"));
					uspwd = uspwd.substr(uspwd.find(":"));
					//usually not a good idea to include the password unencrypted but this is just to parse the URI
					//I am interested in cybersecurity though
					password = uspwd.substr(uspwd.find(":") + 1, uspwd.find("@") - 1);
					uspwd = uspwd.substr(uspwd.find("@") + 1);

					//check if password and user are not empty
					if (!user.empty() && !password.empty())
					{
						valid = checkHostDomain(host);
					}
					else
					{
						errorListAdd("User or password is empty when ':' is detected\n");
					}
				}
				else
				{
					user = uspwd.substr(0, uspwd.find("@"));
					password = "NONE";
					uspwd = uspwd.substr(uspwd.find("@") + 1);
					if (!user.empty())
					{
						valid = checkHostDomain(host);
					}
					else
					{
						errorListAdd("URI user not found when '@' is detected");
					}
				}
			}
			else
			{
				user = "NONE";
				password = "NONE";
				host = authority;

				valid = checkHostDomain(host);
			}
		}
		//empty authority = no user, password and host
		else
		{
			user = "NOT FOUND";
			password = "NOT FOUND";
			host = "NOT FOUND";

			errorListAdd("URI has no scheme or path\n");

			valid = false;
		}

		//check if there are ports
		if (authority.find(":") != std::string::npos)
		{
			bool validPort = false;

			if (authority.find("@") != std::string::npos)
			{
				host = authority.substr(authority.find("@") + 1, authority.find(":") - 1);
			}
			else
			{
				host = authority.substr(authority.find("@") + 1, authority.find(":"));
			}

			//convert port string to int and check if not empty
			if (!authority.substr(authority.find(":") + 1).empty())
			{
				port = std::stoi(authority.substr(authority.find(":") + 1));
			}
			else
			{
				errorListAdd("URI port is empty when ':' is detected");
				port = -2;
				valid = false;
			}

			//validate host and port
			valid = checkHostDomain(host) && validPort;
		}
		//no ports means the leftover authority is the host domain
		else
		{
			host = authority;
			valid = checkHostDomain(host);
		}

		//check for paths
		//paths can be empty
		//check if there is a query, otherwise leftover is the path
		if (tempStr.find("?") != std::string::npos)
		{
			path = tempStr.substr(0, tempStr.find("?"));
			tempStr = tempStr.substr(tempStr.find("?") + 1);

			//check for queries
			//queries CANNOT be empty
			//check if there is a fragment, otherwise, leftover is a query
			if (tempStr.find("#") != std::string::npos)
			{
				query = tempStr.substr(0, tempStr.find("#"));
				tempStr = tempStr.substr(tempStr.find("#") + 1);

				if (query.empty())
				{
					errorListAdd("URI query is empty when '#' is detected");
					valid = false;
				}

				fragment = tempStr;

				if (fragment.empty())
				{
					errorListAdd("URI fragment is empty when '#' is detected");
					valid = false;
				}
			}
			else
			{
				query = tempStr;
			}
		}
		else if(tempStr.find("#") != std::string::npos)
		{
			path = tempStr.substr(0, tempStr.find("#"));
			tempStr = tempStr = tempStr.substr(tempStr.find("#") + 1);

			fragment = tempStr.substr(tempStr.find("#") + 1);

			if (fragment.empty())
			{
				errorListAdd("URI fragment is empty when '#' is detected");
				valid = false;
			}
		}
		else
		{
			path = tempStr;
		}
	}
	//no next '/' symbol means no authority
	else
	{
		host = "NOT FOUND";
		errorListAdd("URI host not found");
	}
	
	return valid;
}

