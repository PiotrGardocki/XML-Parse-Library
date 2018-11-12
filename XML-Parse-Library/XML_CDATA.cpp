#include "XML_CDATA.hpp"
#include "XML_Exception.hpp"

XML_CDATA::XML_CDATA(const std::string & value)
{
	setValue(value);
}

XML_ElementType XML_CDATA::getElementType() const
{
	return XML_ElementType::CDATA;
}

void XML_CDATA::setValue(const std::string & value)
{
	if (value.find("]]>") != std::string::npos)
		throw XML_Exception("XML_CDATA cannot contain substring ']]>'");

	mValue = value;
}

std::string XML_CDATA::getValueInOneLine() const
{
	return mValue;
}

std::list<std::string> XML_CDATA::getValueInLines() const
{
	std::list<std::string> line;
	line.push_back(mValue);
	return line;
}

std::string XML_CDATA::getElementWithValueInOneLine() const
{
	return std::string("<![CDATA[") + mValue + "]]>";
}

std::list<std::string> XML_CDATA::getElementWithValueInLines() const
{
	std::list<std::string> line;
	line.push_back(getElementWithValueInOneLine());
	return line;
}

std::string XML_CDATA::getClassName() const
{
	return std::string("XML_CDATA");
}

std::unique_ptr<XML_BaseElement> XML_CDATA::makeCopy() const
{
	std::unique_ptr<XML_BaseElement> copy(new XML_CDATA(*this));
	return copy;
}

std::unique_ptr<XML_BaseElement> XML_CDATA::makeMovedCopy()
{
	std::unique_ptr<XML_BaseElement> moved(new XML_CDATA(std::move(*this)));
	return moved;
}
