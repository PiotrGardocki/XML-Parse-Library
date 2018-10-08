#include "XML_BaseElement.hpp"
#include "XML_Exception.hpp"

XML_BaseElement::XML_BaseElement()
	: mParent(nullptr)
{
}

void XML_BaseElement::appendChild(const XML_BaseElement & element)
{
	throw XML_Exception(getClassName() + " class cannot have child elements");
}

void XML_BaseElement::appendChild(XML_BaseElement && element)
{
	throw XML_Exception(getClassName() + " class cannot have child elements");
}

void XML_BaseElement::appendChild(const std::unique_ptr<XML_BaseElement>& element)
{
	throw XML_Exception(getClassName() + " class cannot have child elements");
}

void XML_BaseElement::appendChild(std::unique_ptr<XML_BaseElement>&& element)
{
	throw XML_Exception(getClassName() + " class cannot have child elements");
}

unsigned XML_BaseElement::getChildrenCount() const
{
	return 0;
}

void XML_BaseElement::setAttribute(const std::string & attributeName, const std::string & value)
{
	throw XML_Exception(getClassName() + " class cannot have attributes");
}

bool XML_BaseElement::deleteAttribute(const std::string & attributeName)
{
	throw XML_Exception(getClassName() + " class cannot have attributes");
}

std::string XML_BaseElement::getAttributeValue(const std::string & attributeName) const
{
	return "";
}

bool XML_BaseElement::hasAttribute(const std::string & attributeName) const
{
	return false;
}

void XML_BaseElement::setTagName(const std::string & tagName)
{
	throw XML_Exception(getClassName() + " class cannot have tag name");
}

std::string XML_BaseElement::getTagName() const
{
	throw XML_Exception(getClassName() + " class cannot have tag name");
}

bool XML_BaseElement::hasTagName() const
{
	throw XML_Exception(getClassName() + " class cannot have tag name");
}

XML_Tag * XML_BaseElement::getParent()
{
	if (hasParent())
		return mParent;
	throw XML_Exception("XML Element object has not a parent oobject");
}

const XML_Tag * XML_BaseElement::getParent() const
{
	if (hasParent())
		return mParent;
	throw XML_Exception("XML Element object has not a parent oobject");
}

bool XML_BaseElement::hasParent() const
{
	return (mParent != nullptr);
}

void XML_BaseElement::setParent(XML_Tag * parent)
{
	mParent = parent;
}
