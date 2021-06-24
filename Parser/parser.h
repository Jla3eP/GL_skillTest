#ifndef GL_SKILLTEST_PARSER_H
#define GL_SKILLTEST_PARSER_H
#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
using json = nlohmann::json;
using value_t = nlohmann::detail::value_t;

class Parser {
private:
	//bool isServiceSybmolsCounterCorrect(const std::string& pathToInputFile);
	std::string parseArrayToString(json& _json, const json::iterator& iter, const std::string& path = "");
	std::string parseObjectToString(json& _json, const json::iterator& iter, const std::string& path = "");
public:
	bool parse(const std::string& pathToInputFile, const std::string& pathToOutputFile);
};


#endif //GL_SKILLTEST_PARSER_H
