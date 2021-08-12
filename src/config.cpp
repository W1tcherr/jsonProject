#include "config.hpp"

void Config::print()
{
	std::cout << j << '\n';
}

void Config::parse(const std::string& str)
{
	j = json::parse(str);
}

void Config::delElemet(const std::string& Keystr)
{
	j.erase(j.find(Keystr));
}
