#include <iostream>
#include <string>
#include <fstream>
#include "config.hpp"

int main()
{
	std::ifstream myfile("../test_json.json");
	std::string loadStr = {};
	std::string str = {};
	Config json;

	if (myfile.is_open())
  	{
    	while (std::getline (myfile, str))
    	{
      		loadStr += str;
    	}
    	myfile.close();
  	}

	std::cout << "File contents: \n" << loadStr << std::endl;
	json.parse(loadStr);
	std::cout << "Json contents: \n";
	json.print();

	/////test Config/////
	std::cout << "\n\nTest Config \n\n";
	int a;
	bool b;
	float c;
	float t;
	std::string test = "param1";

	str = json.getObjValue(str, "param8", "param0");
	std::cout << str << std::endl;

	t = json.getObjValue(t, "param8", "param");
	std::cout << t << std::endl;

	test = json.getValue(test, test);
	std::cout << "String test: " << test << std::endl;

	b = json.getValue(b, "param2");
	std::cout << "Bool test: " << b << std::endl;

	c = json.getValue(c, "param3");
	std::cout << "Float test: " << c << std::endl;

	a = json.getValue(a, "param4");
	std::cout << "Int test: " << a << std::endl;

	json.getValue(a, "param12");
	std::cout << "Non-existent key test: " << a << std::endl;

	json.getValue(test, "param5");
	std::cout << "Exception test: " << test << std::endl;

	json.getValue(c, "param8");
	std::cout << "Float test: " << c << std::endl;	

	json.print();
	json.addElement("param4", 15);
	json.addElement("param10", 15);
	json.delElemet("param");
	json.print();

	return 0;
}