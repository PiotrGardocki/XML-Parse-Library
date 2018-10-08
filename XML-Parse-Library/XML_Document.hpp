#ifndef XML_DOCUMENT_HPP_
#define XML_DOCUMENT_HPP_

#include <string>
#include "XML_Tag.hpp"

class XML_Document
{
public:
	//XML_Document();

	XML_Tag & getRootElement();
	const XML_Tag & getRootElement() const;

	//void setAttribute(const std::string & attributeName, const std::string & value);
	//bool deleteAttribute(const std::string & attributeName);
	//std::string getAttributeValue(const std::string & attributeName) const;
	//bool hasAttribute(const std::string & attributeName) const;

	void saveToFile(const std::string & fileName) const;

private:
	static std::string getXML_Declaration();

private:
	//std::map<std::string, std::string> mAttributes;  // <attributeName, attributeValue>
	XML_Tag mRootElement;
};

#endif // XML_DOCUMENT_HPP_