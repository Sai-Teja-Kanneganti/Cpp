/*The exception class, which constructs the exception object with a given message */
#include<iostream>
using namespace std;
class LSAException
{
private:
	char * m_strError;

	LSAException() {}; // not meant to be called
public:
	LSAException(char *strError)
		: m_strError(strError)
	{
	}

	char* getError()
	{
		return m_strError;
	}
};