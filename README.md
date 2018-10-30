# URI Parser

Hilariously, the guy who sent me this task to do failed to fix his copy paste, but I thought this was an interesting thing to try anyway. May fix this later on but for now I'm updating it to get that sweet Hacktober T-Shirt.

## The task:

The team is very interested in getting to know you and your background. I was wondering if you might be open to performing a small programming task to better understand your approach to SW development.

The purpose:
This test is intended to provide some reflection on the following:
* How you go about design and development of a relatively small, isolated component;
* How you address aspects of SW quality such as Discoverability, Modularity, Efficiency, and Testability;

Our expectation is that this task should take between two and ten hours work. Do not over-engineer.

Specification:
Create a component, written in a language of your choice of C++, C#, Go, Java, Python, Ruby, Scala, that performs URI parsing. 

Ideally recording its evolution in a Git repository that you will create. Email back (in archive form) your work.

The parser component should be able to identify all of the recognised components of a well-formed URI – scheme, user, password, host, port, path, query, fragment – and provide them to the caller in the form of a suitable abstraction. The parser component should communicate adequately to the caller upon receipt of malformed input.

Performance is not to be considered a critical requirement in this design. However, if you wish to comment on how your implementation and design might be adjusted to have higher runtime performance, that would be of interest to us.

A Test Driven Development (TDD) approach is recommended, but not required. If you follow a TDD-approach, the suite of tests may be deemed to be the component’s documentation.

# Using the URI Parser
The URI Parser is a header file that can be attached to any program which takes in a string input. The class automatically parses the string, however the outputs are determined by the programmer using the class. The main.cpp file of this project is just a console program to demonstrate how to use the class in a project so that it can be integrated into other projects.

The URI Parser has been quite heavily tested, however, should there happen to be a bug / issue that is found, please do notify me by pushing an issue on the "Issues" tab above.

### Known bugs:
* The regex parser for the domain name may not be correct for every input
* Sometimes inputting multiline inputs break the program but not the class itself
* may not work for every single URI scheme
* Needs to be updated to use regex checks instead of how I implemented the "regex check"