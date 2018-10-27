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

void XML_Document::saveToFile(const std::string & fileName) const
{
	std::ofstream file(fileName);
	writeIntoStream(file);
}

void XML_Document::writeIntoStream(std::ostream & stream) const
{
	stream << getXML_Declaration();

	std::list<std::string> lines = mRootElement.getElementWithValueInLines();

	for (auto & line : lines)
	{
		stream << line << std::endl;
	}
}

std::string XML_Document::getXML_Declaration()
{
	return std::string("<?xml version=\"1.1\" ?>\n");
}
