#ifndef XML_BASEELEMENT_HPP_
#define XML_BASEELEMENT_HPP_

#include <string>
#include <memory>
#include <list>
#include <vector>
#include "XML_ElementType.hpp"

class XML_Tag;

class XML_BaseElement
{
	friend XML_Tag;
public:
	XML_BaseElement();
	virtual ~XML_BaseElement() = default;
	virtual XML_ElementType getElementType() const = 0;

// modifying tree's structure

	virtual void appendChild(const XML_BaseElement & element);
	virtual void appendChild(XML_BaseElement && element);
	virtual void appendChild(const std::unique_ptr<XML_BaseElement> & element);
	virtual void appendChild(std::unique_ptr<XML_BaseElement> && element);

	//bool removeChild(const XML_Tag & element);
	//bool removeChild(const XML_Tag * const elementPtr);

// getting access to child elements

	virtual unsigned getChildrenCount() const;
	virtual XML_BaseElement & getChildByPosition(unsigned position);
	virtual const XML_BaseElement & getChildByPosition(unsigned position) const;

	virtual std::vector<XML_BaseElement *> getAllChildren();
	virtual std::vector<const XML_BaseElement *> getAllChildren() const;

	virtual std::vector<XML_BaseElement *> getChildrenByTagName(const std::string & tagName);
	virtual std::vector<const XML_BaseElement *> getChildrenByTagName(const std::string & tagName) const;

	virtual std::vector<XML_BaseElement *> getChildrenWithAttribute(const std::string & attributeName);
	virtual std::vector<const XML_BaseElement *> getChildrenWithAttribute(const std::string & attributeName) const;

	virtual std::vector<XML_BaseElement *> getChildrenByAttributeValue(const std::string & attributeName, const std::string & attributeValue);
	virtual std::vector<const XML_BaseElement *> getChildrenByAttributeValue(const std::string & attributeName, const std::string & attributeValue) const;

// setting attributes

	virtual void setAttribute(const std::string & attributeName, const std::string & value);
	virtual bool deleteAttribute(const std::string & attributeName);
	virtual std::string getAttributeValue(const std::string & attributeName) const;
	virtual bool hasAttribute(const std::string & attributeName) const;
	virtual bool hasAttributeSetWithValue(const std::string & attributeName, const std::string & value) const;

	virtual void setTagName(const std::string & tagName);
	virtual std::string getTagName() const;
	virtual bool hasTagName() const;

	virtual void setValue(const std::string & value) = 0;
	
	virtual std::string getValueInOneLine() const = 0;
	virtual std::list<std::string> getValueInLines() const = 0;
	
	virtual std::string getElementWithValueInOneLine() const = 0;
	virtual std::list<std::string> getElementWithValueInLines() const = 0;

	XML_Tag & getParent();
	const XML_Tag & getParent() const;
	bool hasParent() const;

protected:
	virtual std::string getClassName() const = 0;
	virtual std::unique_ptr<XML_BaseElement> makeCopy() const = 0;
	virtual std::unique_ptr<XML_BaseElement> makeMovedCopy() = 0;

private:
	void setParent(XML_Tag * parent);

private:
	XML_Tag * mParent;
};

#endif // XML_BASEELEMENT_HPP_