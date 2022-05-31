#include <iostream>
#include <fstream>
#include <sstream>
#include "fileReader.h"
#include "programOptions.h"

bool fileReader::read() {
    std::ifstream ifs("input.txt", std::ios::in);
    if (!ifs.is_open()) {
        return false;
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    contents = ss.str();

    if(programOptions::getInstance().debugMsgLevel)
    {
        cout << contents << endl;
    }

    ifs.close();
    return true;
}

bool fileReader::setFilePath(string str){
    filePath = str;
}