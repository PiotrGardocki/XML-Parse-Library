#ifndef XML_EXCEPTION_HPP_
#define XML_EXCEPTION_HPP_

#include <exception>
#include <string>

class XML_Exception : public std::exception
{
public:
	XML_Exception(const std::string & message);

	virtual const char * what() const override;

private:
	std::string mMessage;
};

#endif // XML_EXCEPTION_HPP_