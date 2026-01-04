#include "data-reader.h"

std::vector<float> extractData(std::string dataline) {
    std::stringstream data(dataline) ;
    std::string item ;
    std::vector<float> result ;

    while(std::getline(data , item , ',')) {
        float val = std::stof(item) ;
        result.push_back(val) ;
    }
    return result ;
}

std::string stripComments(const std::string& dataline) {
    size_t pos = dataline.find('#') ;
    if(pos == std::string::npos) return dataline ;
    return dataline.substr(0 , pos) ;
}

bool DataReader::readFile(std::vector<Ball>& balls , const glm::vec2& gravity , const float initdt) {
    std::ifstream dataFile(filePath) ;
    std::string dataline ;
    std::vector<float> tempVec ;

    Ball tempball ;
    if(dataFile.is_open()) {
        while(std::getline(dataFile , dataline)) {
            if (dataline.empty()) continue ;
            dataline = stripComments(dataline) ;
            if (dataline.find_first_not_of(" \t\r\n") == std::string::npos) continue ;
            tempVec = extractData(dataline) ;
            //if(tempVec.size() != DATALINE_SIZE) return false ;
            tempball.prev_pos = {tempVec[0] , tempVec[1]} ;
            glm::vec2 vel = {tempVec[2] , tempVec[3]} ;
            tempball.cur_pos = tempball.prev_pos + initdt * (vel + 0.5f * gravity * initdt) ;
            tempball.radius = tempVec[4] ;
            tempball.color = {tempVec[5] , tempVec[6] , tempVec[7] , tempVec[8]} ;

            balls.push_back(tempball) ;
        }
        return true ;
    }
    else return false ;
}

std::string DataReader::getExecutableDir() {
    char buffer[PATH_MAX] ;
    ssize_t len = readlink("/proc/self/exe" , buffer , sizeof(buffer) - 1) ;
    if(len == -1) return "" ;
    buffer[len] = '\0' ;

    std::string path(buffer) ;
    return path.substr(0 , path.find_last_of('/')) ;
}