#include "parser.h"

bool Parser::parse (const std::string &pathToInputFile, const std::string &pathToOutputFile){
	std::stringstream i;
	std::ifstream inputFile;
	std::ofstream outputFile;
	json j;
	try {
		inputFile.open(pathToInputFile);
		outputFile.open(pathToOutputFile);
		if (!inputFile.is_open() || !outputFile.is_open()) {
			throw std::exception();
		}
		i << inputFile.rdbuf();
		inputFile.close();
		j = json::parse(i);
	}
	catch (std::exception) {
		std::cout << "Error\n";
		return false;
	}
	std::string result;
	for (auto it = j.begin(); it != j.end(); ++it) {
		if (it->type() != value_t::array && it->type() != value_t::object) {
			result += '\"' + it.key() + '\"' + '\t' + to_string(j[it.key()]) + '\n';
		}
		else if (it->type() == value_t::array) {
			result += this->parseArrayToString(j, it, it.key());
		}
		else if (it->type() == value_t::object) {
			result += this->parseObjectToString(j, it, it.key());
		}
	}
	outputFile << result;
	outputFile.close();
	return true;
}

std::string Parser::parseArrayToString (json &_json, const json::iterator &iter, const std::string &path){
	std::string result;
	for (int i = 0; i < iter->size(); i++) {
		if (_json[iter.key()][i].type() != value_t::array && _json[iter.key()][i].type() != value_t::object) {
			result += path + '[' + std::to_string(i) + "]\t" + to_string(_json[iter.key()][i]) + '\n';
		}
		else if (_json[iter.key()][i].type() == value_t::array) {
			std::string buffer = "{\"q\": " + to_string(_json[iter.key()][i]) + '}';
			json j;
			j = json::parse(buffer);
			result += parseArrayToString(j, j.begin(), path + '[' + std::to_string(i) + ']');
		}
		else if (_json[iter.key()][i].type() == value_t::object) {
			std::string buffer = "{\"q\": " + to_string(_json[iter.key()][i]) + '}';
			json j;
			j = json::parse(buffer);
			result += parseObjectToString(j, j.begin(), path + '[' + std::to_string(i) + ']');
		}
	}
	return result;
}


std::string Parser::parseObjectToString (json &_json, const json::iterator &iter, const std::string &path){
	std::string result;
	for (auto itt = iter->begin(); itt != iter->end(); ++itt) {
		if (itt->type() != value_t::array && itt->type() != value_t::object) {
			result += (path + '.' + itt.key() + '\t' + to_string(_json[iter.key()][itt.key()]) + '\n');
		}
		else if (itt->type() == value_t::array) {
			std::string buffer = "{\"q\": " + to_string(_json[iter.key()][itt.key()]) + '}';
			json j;
			j = json::parse(buffer);
			result += parseArrayToString(j, j.begin(), path + '.' + itt.key());
		}
		else if (itt->type() == value_t::object) {
			std::string buffer = "{\"q\": " + to_string(_json[iter.key()][itt.key()]) + '}';
			json j;
			j = json::parse(buffer);
			result += parseObjectToString(j, j.begin(), path + '.' + itt.key());
		}
	}
	return result;
}