#ifndef XML_TAG_HPP_
#define XML_TAG_HPP_

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "XML_BaseElement.hpp"

class XML_Tag : public XML_BaseElement
{
public:
	XML_Tag() = default;
	explicit XML_Tag(const std::string & tagName);

	XML_Tag(const XML_Tag & tag);
	XML_Tag(XML_Tag && tag) = default;

	XML_Tag & operator=(const XML_Tag & tag);
	XML_Tag & operator=(XML_Tag && tag) = default;

	~XML_Tag() = default;

	virtual XML_ElementType getElementType() const override;

// modifying tree's structure

	virtual void appendChild(const XML_BaseElement & element) override;
	virtual void appendChild(XML_BaseElement && element) override;
	virtual void appendChild(const std::unique_ptr<XML_BaseElement> & element) override;
	virtual void appendChild(std::unique_ptr<XML_BaseElement> && element) override;

	virtual std::unique_ptr<XML_BaseElement> removeChild(const XML_Tag & element) override;
	virtual std::unique_ptr<XML_BaseElement> removeChild(const XML_Tag * const elementPtr) override;

// getting access to child elements

	virtual unsigned getChildrenCount() const override;
	virtual XML_BaseElement & getChildByPosition(unsigned position) override;
	virtual const XML_BaseElement & getChildByPosition(unsigned position) const override;

	virtual std::vector<XML_BaseElement *> getAllChildren() override;
	virtual std::vector<const XML_BaseElement *> getAllChildren() const override;

	virtual std::vector<XML_BaseElement *> getChildrenByTagName(const std::string & tagName) override;
	virtual std::vector<const XML_BaseElement *> getChildrenByTagName(const std::string & tagName) const override;

	virtual std::vector<XML_BaseElement *> getChildrenWithAttribute(const std::string & attributeName) override;
	virtual std::vector<const XML_BaseElement *> getChildrenWithAttribute(const std::string & attributeName) const override;

	virtual std::vector<XML_BaseElement *> getChildrenByAttributeValue(const std::string & attributeName, const std::string & attributeValue) override;
	virtual std::vector<const XML_BaseElement *> getChildrenByAttributeValue(const std::string & attributeName, const std::string & attributeValue) const override;

// setting attributes

	virtual void setAttribute(const std::string & attributeName, const std::string & value) override;
	virtual bool deleteAttribute(const std::string & attributeName) override;
	virtual std::string getAttributeValue(const std::string & attributeName) const override;
	virtual bool hasAttribute(const std::string & attributeName) const override;
	virtual bool hasAttributeSetWithValue(const std::string & attributeName, const std::string & value) const override;

// other methods

	virtual void setTagName(const std::string & tagName) override;
	virtual std::string getTagName() const override;
	virtual bool hasTagName() const override;

	virtual void setValue(const std::string & value) override;

	virtual std::string getValueInOneLine() const override;
	virtual std::list<std::string> getValueInLines() const override;

	virtual std::string getElementWithValueInOneLine() const override;
	virtual std::list<std::string> getElementWithValueInLines() const override;

protected:
	virtual std::string getClassName() const override;
	virtual std::unique_ptr<XML_BaseElement> makeCopy() const override;
	virtual std::unique_ptr<XML_BaseElement> makeMovedCopy() override;

private:
	std::string getStartTag() const;
	std::string getEndTag() const;
	std::string getTagWithNoElements() const;

	std::string getAttibutesAsString() const;

private:
	std::string mTagName;
	std::map<std::string, std::string> mAttributes;  // <attributeName, attributeValue>

	std::vector<std::unique_ptr<XML_BaseElement> > mChildren;
};

#endif // XML_TAG_HPP_