#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <physics/ball.h>
#include <limits.h>
#include <unistd.h>

class DataReader {
public:
    std::string filePath = "" ;

    bool readFile(std::vector<Ball>& balls , const glm::vec2& gravity , const float initdt) ;
    std::string getExecutableDir() ;
} ;