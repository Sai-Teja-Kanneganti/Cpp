/*The exception class, which constructs the exception object with a given message. */
#include<iostream>
using namespace std;
class GraphException
{
private:
	char * m_strError;

	GraphException() {}; //not meant to be called
public:
	GraphException(char *strError)
		: m_strError(strError)
	{
	}

	char* getError()
	{
		return m_strError;
	}
};