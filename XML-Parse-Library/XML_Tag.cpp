#include <utility>
#include <cctype>
#include "XML_Tag.hpp"
#include "XML_Value.hpp"
#include "XML_Exception.hpp"
#include "Utilities.hpp"

XML_Tag::XML_Tag(const std::string & tagName)
{
	setTagName(tagName);
}

XML_Tag::XML_Tag(const XML_Tag & tag)
{
	mTagName = tag.mTagName;
	mAttributes = tag.mAttributes;

	auto childrenCount = tag.getChildrenCount();
	mChildren.resize(childrenCount);

	for (auto iter = 0; iter < childrenCount; ++iter)
	{
		mChildren.at(iter) = std::move(tag.mChildren.at(iter)->makeCopy());
	}
}

XML_Tag & XML_Tag::operator=(const XML_Tag & tag)
{
	mTagName = tag.mTagName;
	mAttributes = tag.mAttributes;

	mChildren.resize(0);

	auto childrenCount = tag.getChildrenCount();
	mChildren.resize(childrenCount);

	for (auto iter = 0; iter < childrenCount; ++iter)
	{
		mChildren.at(iter) = std::move(tag.mChildren.at(iter)->makeCopy());
	}

	return *this;
}

XML_ElementType XML_Tag::getElementType() const
{
	return XML_ElementType::TAG;
}

void XML_Tag::appendChild(const XML_BaseElement & element)
{
	mChildren.push_back(element.makeCopy());
	mChildren.back()->setParent(this);
}

void XML_Tag::appendChild(XML_BaseElement && element)
{
	std::unique_ptr<XML_BaseElement> moved = element.makeMovedCopy();
	appendChild(std::move(moved));
}

void XML_Tag::appendChild(const std::unique_ptr<XML_BaseElement> & element)
{
	mChildren.push_back(element->makeCopy());
	mChildren.back()->setParent(this);
}

void XML_Tag::appendChild(std::unique_ptr<XML_BaseElement> && element)
{
	mChildren.push_back(std::unique_ptr<XML_BaseElement>());
	mChildren.back() = std::move(element);
	mChildren.back()->setParent(this);
}

std::unique_ptr<XML_BaseElement> XML_Tag::removeChild(const XML_Tag & element)
{
	for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
	{
		if (iter->get() == &element)
		{
			std::unique_ptr<XML_BaseElement> foundElement(std::move(*iter));
			mChildren.erase(iter);
			return foundElement;
		}
	}

	return std::unique_ptr<XML_BaseElement>{};
}

std::unique_ptr<XML_BaseElement> XML_Tag::removeChild(const XML_Tag * const elementPtr)
{
	for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
	{
		if (iter->get() == elementPtr)
		{
			std::unique_ptr<XML_BaseElement> foundElement(std::move(*iter));
			mChildren.erase(iter);
			return foundElement;
		}
	}

	return std::unique_ptr<XML_BaseElement>{};
}

unsigned XML_Tag::getChildrenCount() const
{
	return mChildren.size();
}

XML_BaseElement & XML_Tag::getChildByPosition(unsigned position)
{
	if (position < getChildrenCount())
		return *mChildren.at(position);
	throw XML_Exception("Attempt to access to child out of range");
}

const XML_BaseElement & XML_Tag::getChildByPosition(unsigned position) const
{
	return getChildByPosition(position);
}

std::vector<XML_BaseElement*> XML_Tag::getAllChildren()
{
	std::vector<XML_BaseElement *> children;
	children.reserve(mChildren.size());

	for (auto & child : mChildren)
		children.emplace_back(child.get());

	return children;
}

std::vector<const XML_BaseElement*> XML_Tag::getAllChildren() const
{
	std::vector<const XML_BaseElement *> children;
	children.reserve(mChildren.size());

	for (auto & child : mChildren)
		children.emplace_back(child.get());

	return children;
}

std::vector<XML_BaseElement*> XML_Tag::getChildrenByTagName(const std::string & tagName)
{
	std::vector<XML_BaseElement *> children;

	for (auto & child : mChildren)
		if (child->getElementType() == XML_ElementType::TAG && child->getTagName() == tagName)
			children.emplace_back(child.get());

	return children;
}

std::vector<const XML_BaseElement*> XML_Tag::getChildrenByTagName(const std::string & tagName) const
{
	std::vector<const XML_BaseElement *> children;

	for (auto & child : mChildren)
		if (child->getElementType() == XML_ElementType::TAG && child->getTagName() == tagName)
			children.emplace_back(child.get());

	return children;
}

std::vector<XML_BaseElement*> XML_Tag::getChildrenWithAttribute(const std::string & attributeName)
{
	std::vector<XML_BaseElement *> children;

	for (auto & child : mChildren)
		if (child->getElementType() == XML_ElementType::TAG && child->hasAttribute(attributeName))
			children.emplace_back(child.get());

	return children;
}

std::vector<const XML_BaseElement*> XML_Tag::getChildrenWithAttribute(const std::string & attributeName) const
{
	std::vector<const XML_BaseElement *> children;

	for (auto & child : mChildren)
		if (child->getElementType() == XML_ElementType::TAG && child->hasAttribute(attributeName))
			children.emplace_back(child.get());

	return children;
}

std::vector<XML_BaseElement*> XML_Tag::getChildrenByAttributeValue(const std::string & attributeName, const std::string & attributeValue)
{
	std::vector<XML_BaseElement *> children;

	for (auto & child : mChildren)
		if (child->getElementType() == XML_ElementType::TAG && child->hasAttributeSetWithValue(attributeName, attributeValue))
			children.emplace_back(child.get());

	return children;
}

std::vector<const XML_BaseElement*> XML_Tag::getChildrenByAttributeValue(const std::string & attributeName, const std::string & attributeValue) const
{
	std::vector<const XML_BaseElement *> children;

	for (auto & child : mChildren)
		if (child->getElementType() == XML_ElementType::TAG && child->hasAttributeSetWithValue(attributeName, attributeValue))
			children.emplace_back(child.get());

	return children;
}

void XML_Tag::setAttribute(const std::string & attributeName, const std::string & value)
{
	mAttributes[correctString(attributeName)] = correctString(value);
}

bool XML_Tag::deleteAttribute(const std::string & attributeName)
{
	auto deletedAttributesCount = mAttributes.erase(correctString(attributeName));

	return static_cast<bool>(deletedAttributesCount);
}

std::string XML_Tag::getAttributeValue(const std::string & attributeName) const
{
	auto iterator = mAttributes.find(correctString(attributeName));

	if (iterator == mAttributes.end())
		return "";
	return iterator->second;
}

bool XML_Tag::hasAttribute(const std::string & attributeName) const
{
	return (mAttributes.find(correctString(attributeName)) != mAttributes.end());
}

bool XML_Tag::hasAttributeSetWithValue(const std::string & attributeName, const std::string & value) const
{
	auto iterator = mAttributes.find(correctString(attributeName));

	if (iterator == mAttributes.end() || iterator->second != correctString(value))
		return false;
	return true;
}

bool isTagNameCorrect(const std::string & tagName)
{
	char firstChar = tagName.at(0);

	if (firstChar == '-' || firstChar == '.' || std::isdigit(firstChar))
		return false;

	std::string badCharacters("!\"#$%&'()*+,/;<=>?@[\\]^`{|}~");

	for (auto & ch : badCharacters)
		if (tagName.find(ch) != std::string::npos)
			return false;

	return true;
}

void XML_Tag::setTagName(const std::string & tagName)
{
	if (tagName.size() > 0 && !isTagNameCorrect(tagName))
		throw XML_Exception("Tag's name can't contain any of the characters: ' !\"#$%&'()*+,/;<=>?@[\\]^`{|}~ ', space and cannot begin with '-' '.' or a digit");

	mTagName = tagName;
}

std::string XML_Tag::getTagName() const
{
	return mTagName;
}

bool XML_Tag::hasTagName() const
{
	return (mTagName != "");
}

void XML_Tag::setValue(const std::string & value)
{
	mChildren.clear();
	mChildren.push_back(std::make_unique<XML_Value>(value));
}

std::string XML_Tag::getValueInOneLine() const
{
	std::string value;

	for (auto & iter : mChildren)
	{
		value += iter->getElementWithValueInOneLine();
	}

	return value;
}

std::list<std::string> XML_Tag::getValueInLines() const
{
	std::list<std::string> lines;

	for (auto & iter : mChildren)
	{
		std::list<std::string> childLines = iter->getElementWithValueInLines();
		lines.splice(lines.end(), childLines);
	}

	return lines;
}

std::string XML_Tag::getElementWithValueInOneLine() const
{
	if (mChildren.size() == 0)
		return getTagWithNoElements();

	return getStartTag() + getValueInOneLine() + getEndTag();
}

void addTab(std::string & str)
{
	str = std::string("\t") + str;
}

std::list<std::string> XML_Tag::getElementWithValueInLines() const
{
	auto lines = getValueInLines();
	
	if (lines.size() == 0)
	{
		lines.push_back(getTagWithNoElements());
		return lines;
	}

	for (auto & line : lines)
		addTab(line);

	lines.push_front(getStartTag());
	lines.push_back(getEndTag());

	return lines;
}

std::string XML_Tag::getClassName() const
{
	return "XML_Tag";
}

std::unique_ptr<XML_BaseElement> XML_Tag::makeCopy() const
{
	std::unique_ptr<XML_BaseElement> copy(new XML_Tag(*this));
	return copy;
}

std::unique_ptr<XML_BaseElement> XML_Tag::makeMovedCopy()
{
	std::unique_ptr<XML_BaseElement> moved(new XML_Tag(std::move(*this)));
	return moved;
}

std::string XML_Tag::getStartTag() const
{
	return std::string("<") + mTagName + getAttibutesAsString() + ">";
}

std::string XML_Tag::getEndTag() const
{
	return std::string("</") + mTagName + ">";
}

std::string XML_Tag::getTagWithNoElements() const
{
	return std::string("<") + mTagName + getAttibutesAsString() + "/>";
}

std::string XML_Tag::getAttibutesAsString() const
{
	std::string attributes;

	for (auto & iter : mAttributes)
	{
		attributes += " " + iter.first + "=\"" + iter.second + "\"";
	}

	return attributes;
}
