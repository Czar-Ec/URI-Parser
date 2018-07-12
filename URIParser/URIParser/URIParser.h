#pragma once
#include <string>
#include <iostream>

#include <algorithm>
#include <regex>


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
		std::string getPort() { 
			if (port < 0)
				return "NO / DEFAULT PORT";
			else
			return std::to_string(port); };
		std::string getPath() { return path; };
		std::string getQuery() { return query; };
		std::string getFragment() { return fragment; };

		std::string printAll();

		//regex check, to validate each part of the URI as valid or not
		bool URITypeCheck(std::string str);

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
	if ((str.length() > 0))
	{
		//check if the URI is valid
		if (URITypeCheck(str))
		{
			std::cout << "----------------------------------------------------\n";
			std::cout << "URI is complete and valid\n";
			std::cout << "----------------------------------------------------\n";
		}
		else
		{
			std::cout << "----------------------------------------------------\n";
			std::cout << "The URI is missing a scheme and path/authority\n";
			std::cout << "----------------------------------------------------\n";
		}
	}
	else
	{
		std::cout << "Empty Input\n\n";
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
		"Port: " + getPort() + "\n" +
		"Path: " + getPath() + "\n" +
		"Query: " + getQuery() + "\n" +
		"Fragment: " + getFragment() + "\n" +
		"_______________________________\n";
}

bool URIParser::URITypeCheck(std::string str)
{
	bool validScheme = true, auth_or_path_exists = false;

	std::string tempStr = str;
	//check for schemes
	//"://" is used for web resources
	if (tempStr.find("://") != std::string::npos)
	{
		scheme = tempStr.substr(0, tempStr.find("://"));
		tempStr = tempStr.substr(tempStr.find("://"));
		tempStr.erase(0, 3);
		//std::cout << tempStr << std::endl;

		//check for the authority if there is any
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

						auth_or_path_exists = true;
					}
					else
					{
						user = authority.substr(0, authority.find("@"));
						password = "NONE";
						authority = authority.substr(authority.find("@") + 1);
						if (!user.empty())
						{
							auth_or_path_exists = true;
						}
					}

					//validation of the host is usually "*.*" which means there needs to 
					//be a (sub)domain and a top level domain, as well as for IPv4/6 addresses
					host = authority;

					//regexes
					std::regex domain("[\w].[A-Za-z]");

					if (std::regex_match(host, domain))
					{
						std::cout << "valid\n";
					}
					else
					{
						std::cout << "invalid\n";
					}
				}
				else
				{
					user = "NONE";
					password = "NONE";
					host = authority;
					auth_or_path_exists = true;
				}
			}
			//empty authority = no user, password and host
			else
			{
				user = "NOT FOUND";
				password = "NOT FOUND";
				host = "NOT FOUND";
				auth_or_path_exists = false;
			}
		}
		//no next '/' symbol means no authority
		else
		{
			host = "NOT FOUND";
		}
	}
	//":\" is for local resources
	else if (tempStr.find(":\\") != std::string::npos)
	{
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
	}
	//":"
	else if (tempStr.find(":") != std::string::npos)
	{
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
	}
	else
	{
		validScheme = false;
		scheme = "NOT FOUND";
	}

	

	return validScheme && auth_or_path_exists;
}

