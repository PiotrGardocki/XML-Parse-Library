#include "XML_Value.hpp"

XML_Value::XML_Value(const std::string & value)
	: mValue(value)
{
}

XML_ElementType XML_Value::getElementType() const
{
	return XML_ElementType::VALUE;
}

void XML_Value::setValue(const std::string & value)
{
	// TO DO: add parser checking
	mValue = value;
}

std::string XML_Value::getValueInOneLine() const
{
	return mValue;
}

std::list<std::string> XML_Value::getValueInLines() const
{
	std::list<std::string> line;
	line.push_back(mValue);
	return line;
}

std::string XML_Value::getElementWithValueInOneLine() const
{
	return mValue;
}

std::list<std::string> XML_Value::getElementWithValueInLines() const
{
	return getValueInLines();
}

std::string XML_Value::getClassName() const
{
	return "XML_Value";
}

std::unique_ptr<XML_BaseElement> XML_Value::makeCopy() const
{
	std::unique_ptr<XML_BaseElement> copy(new XML_Value(*this));
	return copy;
}

std::unique_ptr<XML_BaseElement> XML_Value::makeMovedCopy()
{
	std::unique_ptr<XML_BaseElement> moved(new XML_Value(std::move(*this)));
	return moved;
}
