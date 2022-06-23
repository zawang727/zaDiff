#include <iostream>
#include <fstream>
#include <sstream>
#include "fileReader.h"
#include "programOptions.h"

bool printRead = false;

bool fileReader::read() {
    std::ifstream ifs(filePath.c_str(), std::ios::in);
    if (!ifs.is_open()) {
        return false;
    }
    
    std::stringstream ss;
    ss << ifs.rdbuf();
    contents = ss.str();

    if(programOptions::getInstance().debugMsgLevel && false)
    {
        cout << contents << endl;
    }

    ifs.close();
    return true;
}

bool fileReader::setFilePath(string str){
    filePath = str;
    return true;
}