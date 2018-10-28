#include <iostream>
#include <exception>
#include <utility>
#include <functional>
#include <memory>
#include "XML-Parse-Library.hpp"

int main()
{	
	using std::cout;
	using std::cin;
	using std::endl;
	
	/*std::unique_ptr<XML_Tag> pointer(new XML_Tag{});
	XML_Tag tag;
	
	const XML_Tag * ptr = pointer.get();

	cout << ptr->hasParent() << endl;

	tag.appendChild(std::move(pointer));

	cout << ptr->hasParent() << endl;

	auto & x = ptr->getParent();
	XML_BaseElement & y = tag.getChildByPosition(0);

	cout << ptr << endl;
	cout << &y << endl;*/

	//cout << &tag << endl;

	/*XML_Document doc;
	doc.getRootElement() = tag;

	doc.saveToFile("test2.xml");*/

	/*std::string str("<&div>");

	replaceOccurencies(str, "&", "&amp;");
	replaceOccurencies(str, "<", "&lt;");
	replaceOccurencies(str, ">", "&gt;");
	replaceOccurencies(str, "\"", "&quot;");
	replaceOccurencies(str, "'", "&apos;");

	cout << str << endl;*/

	XML_Document document;
	
	XML_Tag tag1("head");
	tag1.appendChild(XML_Tag("title"));
	tag1.setAttribute("id", "23");

	{
		XML_Tag css("link");
		css.setAttribute("rel", "stylesheet");
		css.setAttribute("href", "style.css");
		tag1.appendChild(std::move(css));
	}

	XML_Tag tag2("body");
	tag2.appendChild(XML_Value("text"));
	tag2.setAttribute("class", "typical");
	tag2.setAttribute("id", "1");

	{
		XML_CDATA someData;
		someData.setValue("Content not to be parsed");
		tag2.appendChild(std::move(someData));

		XML_Tag divTag("div");
		divTag.appendChild(XML_Comment("just a comment"));
		tag2.appendChild(std::move(divTag));
	}

	document.getRootElement().appendChild(std::move(tag1));
	document.getRootElement().appendChild(std::move(tag2));
	document.getRootElement().setTagName("html");

	auto & root = document.getRootElement();

	auto vec = root.getChildrenByTagName("html");
	cout << vec.size() << endl;
	//cout << vec[0] << endl;
	//cout << &root.getChildByPosition(1) << endl;

	/*auto vec = root.getAllChildren();
	cout << vec.size() << " " << root.getChildrenCount() << endl;
	for (int i = 0; i < root.getChildrenCount(); ++i)
	{
		cout << i << ":" << vec.at(i) << " " << &root.getChildByPosition(i) << endl;
	}*/

	//document.saveToFile("test.xml");

	//cout << tag1.getTagName() << "\n" << tag1.getChildrenCount();
	cin.get();

	return 0;
}