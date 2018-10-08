#include "XML_Exception.hpp"

XML_Exception::XML_Exception(const std::string & message)
	: mMessage(message)
{
}

const char * XML_Exception::what() const
{
	return mMessage.c_str();
}
