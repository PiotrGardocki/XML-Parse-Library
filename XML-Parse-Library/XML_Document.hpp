#ifndef XML_DOCUMENT_HPP_
#define XML_DOCUMENT_HPP_

#include <string>
#include <ostream>
#include "XML_Tag.hpp"

class XML_Document
{
public:
	XML_Tag & getRootElement();
	const XML_Tag & getRootElement() const;

	void saveToFile(const std::string & fileName) const;
	void writeIntoStream(std::ostream & stream) const;

private:
	static std::string getXML_Declaration();

private:
	XML_Tag mRootElement;
};

#endif // XML_DOCUMENT_HPP_