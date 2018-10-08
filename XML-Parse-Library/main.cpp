#include <iostream>
#include <exception>
#include "XML_Tag.hpp"
#include "XML_Value.hpp"
#include "XML_Document.hpp"

struct MyStruct
{
	MyStruct() : number(nullptr) {}
	int & getNumber() const
	{
		return *number;
	}
	int * number;
};

int main()
{
	XML_Document document;
	
	XML_Tag tag1("head");
	tag1.appendChild(XML_Tag("title"));
	tag1.setAttribute("id", "23");

	XML_Tag tag2("body");
	tag2.appendChild(XML_Value("text"));
	tag2.setAttribute("class", "typical");
	tag2.setAttribute("id", "1");

	document.getRootElement().appendChild(tag1);
	document.getRootElement().appendChild(tag2);
	document.getRootElement().setTagName("html");

	document.saveToFile("test.xml");

	//std::cin.get();

	/*MyStruct temp;
	int x = 5;
	//temp.number = &x;

	std::cout << temp.getNumber();
	std::cin.get();*/

	/*XML_Tag tag;
	try
	{
		auto y = tag.getParent();
		y.hasParent();
	}
	catch (const std::exception & except)
	{
		std::cout << except.what();
	}

	std::cin.get();*/

	return 0;
}