#include <fstream>
#include <list>
#include <string>
#include "XML_Document.hpp"

XML_Tag & XML_Document::getRootElement()
{
	return mRootElement;
}

const XML_Tag & XML_Document::getRootElement() const
{
	return mRootElement;
}

/*void XML_Document::setAttribute(const std::string & attributeName, const std::string & value)
{
	mAttributes[attributeName] = value;
}

bool XML_Document::deleteAttribute(const std::string & attributeName)
{
	auto deletedAttributesCount = mAttributes.erase(attributeName);

	return static_cast<bool>(deletedAttributesCount);
}

std::string XML_Document::getAttributeValue(const std::string & attributeName) const
{
	auto iterator = mAttributes.find(attributeName);

	if (iterator == mAttributes.end())
		return "";
	return iterator->second;
}

bool XML_Document::hasAttribute(const std::string & attributeName) const
{
	return (mAttributes.find(attributeName) != mAttributes.end());
}*/

void XML_Document::saveToFile(const std::string & fileName) const
{
	std::ofstream file(fileName);
	file << getXML_Declaration();

	std::list<std::string> lines = mRootElement.getElementWithValueInLines();

	for (auto & line : lines)
	{
		file << line << std::endl;
	}
}

std::string XML_Document::getXML_Declaration()
{
	return std::string("<?xml version=\"1.1\" ?>\n");
}
