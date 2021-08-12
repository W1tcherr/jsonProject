#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

class Config
{
public:
	void print();
	void parse(const std::string& str);
	void delElemet(const std::string& Keystr);

	template<class T>
	T getObjValue(T& base, const std::string& Keystr);

	template<class T>
	T getObjValue(T& base, const std::string& Keystr, const std::string& nameObject);

	template<class T>
	void addElement(const std::string& Keystr,const T& value);
	
	template<class T>
	T getValue(T& base, const std::string& Keystr);
private:
	json j;

	template<class T>
	T iterate(json obj, const std::string& Keystr);

	template<class T>
	T iterate(json obj, const std::string& Keystr, const std::string& nameObject);
};

template<class T>
inline T Config::iterate(json obj, const std::string& Keystr)
{
	for (auto& el : obj.items())
	{
		if (el.value().is_object())
		{
			json inObject = el.value();
			return iterate<T>(inObject, Keystr);
		}
		if (el.key() == Keystr)
		{
			try 
			{
				return el.value();
			}
			catch (json::exception& e)
			{
				std::cout << "Error: " << e.what() << '\n';
				return T();
			}
		}
	}
	return T();
}

template<class T>
inline T Config::iterate(json obj, const std::string& Keystr, const std::string& nameObject)
{
	for (auto& el : obj.items())
	{
		if (el.key() == nameObject)
		{
			try
			{
				return el.value().value(Keystr, T());
			}
			catch (json::exception& e)
			{
				std::cout << "Error: " << e.what() << '\n';
				return T();
			}
		}
		if (el.value().is_object())
		{
			json inObject = el.value();
			iterate<T>(inObject, Keystr, nameObject);
		}
	}
	return T();
}

template<class T>
inline T Config::getObjValue(T& base, const std::string& Keystr)
{
	base = iterate<T>(j, Keystr);
	return base;
}

template<class T>
inline T Config::getObjValue(T& base, const std::string& Keystr, const std::string& nameObject)
{
	base = iterate<T>(j, Keystr, nameObject);
	return base;
}

template<class T>
inline void Config::addElement(const std::string& Keystr, const T& value)
{
	if (j.contains(Keystr))
	{
		std::cout << "This key already exists.\n";
	}
	else
	{
		auto it = j.emplace(Keystr, value);
	}
}

template<class T>
inline T Config::getValue(T& base, const std::string& Keystr)
{
	if (!j.contains(Keystr))
	{
		std::cout << "Key is not found.\n";
		base = T();
		return base;
	}
	try{
		base = j.value(Keystr, base);
		return base;
	}
	catch(json::exception& e)
	{
		std::cout << "Error: " << e.what() << '\n';
		base = T();
		return base;
	}
}