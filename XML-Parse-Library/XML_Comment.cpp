#include "XML_Comment.hpp"
#include "XML_Exception.hpp"

XML_Comment::XML_Comment(const std::string & value)
{
	setValue(value);
}

XML_ElementType XML_Comment::getElementType() const
{
	return XML_ElementType::COMMENT;
}

void XML_Comment::setValue(const std::string & value)
{
	auto pos = value.find("-->");
	if (pos != std::string::npos)
		throw XML_Exception("XML_Comment can't contain substring '-->'");

	mValue = value;
}

std::string XML_Comment::getValueInOneLine() const
{
	return mValue;
}

std::list<std::string> XML_Comment::getValueInLines() const
{
	std::list<std::string> line;
	line.push_back(mValue);
	return line;
}

std::string XML_Comment::getElementWithValueInOneLine() const
{
	return std::string("<!--") + mValue + "-->";
}

std::list<std::string> XML_Comment::getElementWithValueInLines() const
{
	std::list<std::string> line;
	line.push_back(getElementWithValueInOneLine());
	return line;
}

std::string XML_Comment::getClassName() const
{
	return "XML_Comment";
}

std::unique_ptr<XML_BaseElement> XML_Comment::makeCopy() const
{
	std::unique_ptr<XML_BaseElement> copy(new XML_Comment(*this));
	return copy;
}

std::unique_ptr<XML_BaseElement> XML_Comment::makeMovedCopy()
{
	std::unique_ptr<XML_BaseElement> moved(new XML_Comment(std::move(*this)));
	return moved;
}
