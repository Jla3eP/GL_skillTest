#include "ParserMenu.h"

void ParserMenu::menu (){
	bool breakFlag = false;
	while(true) {
		enum {
			ENTER_INPUT = 1, ENTER_OUTPUT = 2, PARSE = 3, EXIT = 0
		};
		bool pathsToFilesAreNotEmpty = false;
		std::cout << "1 - enter path to input file\n2 - enter path to output file\n";
		if (!inputFilePath.empty() && !outputFilePath.empty()) {
			pathsToFilesAreNotEmpty = true;
			std::cout << "3 - parse file\n";
		}
		std::cout << "0 - exit\n";
		unsigned int operationNum;
		while ( true ) {
			std::cin >> operationNum;
			if (operationNum == ENTER_INPUT || operationNum == ENTER_OUTPUT ||
				(pathsToFilesAreNotEmpty && operationNum == PARSE) || operationNum == EXIT || breakFlag) {
				break;
			}
			std::cout << "Try again)))\n";
		}
		switch (operationNum) {
			case EXIT:{
				breakFlag = true;
				break;
			}
			case ENTER_INPUT:{
				std::cin>>inputFilePath;
				break;
			}
			case ENTER_OUTPUT:{
				std::cin>>outputFilePath;
				break;
			}
			case PARSE:{
				Parser parser;
				parser.parse(inputFilePath, outputFilePath);
				breakFlag = true;
				break;
			}
		}
		if(breakFlag){
			break;
		}
		
	}
}
