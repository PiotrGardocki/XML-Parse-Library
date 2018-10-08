#include <iostream>
#include <exception>
#include <utility>
#include "XML_Tag.hpp"
#include "XML_Value.hpp"
#include "XML_Document.hpp"

int main()
{
	using std::cout;
	using std::cin;

	XML_Document document;
	
	XML_Tag tag1("head");
	tag1.appendChild(XML_Tag("title"));
	tag1.setAttribute("id", "23");

	XML_Tag tag2("body");
	tag2.appendChild(XML_Value("text"));
	tag2.setAttribute("class", "typical");
	tag2.setAttribute("id", "1");

	document.getRootElement().appendChild(std::move(tag1));
	document.getRootElement().appendChild(std::move(tag2));
	document.getRootElement().setTagName("html");

	document.saveToFile("test.xml");

	//cout << tag1.getTagName() << "\n" << tag1.getChildrenCount();
	//cin.get();

	return 0;
}