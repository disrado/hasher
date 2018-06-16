#pragma once

#include <iostream>
#include <fstream>
#include <set>


std::set<std::string> supportedAlgorithms {
    "MD5", "md5",
    "SHA1", "sha1",
    "SHA224", "sha224",
    "SHA256", "sha256",
    "SHA512", "sha512"
};


class ParametersParser {

public:  
    bool parse(int paramsCount, char** params) {
        if(paramsCount < 3) {
            std::cout << "Some parameters does't specified" << std::endl;
            return false;
        } 

        std::ifstream fileToHashing(params[1]);
        if(fileToHashing.is_open()) {
            filePath = params[1];
        } else {
            std::cout << "Cannot open file " << params[1] << std::endl;
            return false;
        }

        if(params[2]) {
            hash = params[2];
        } else {
            std::cout << "Hash for compare not specified" << std::endl;
            return false;
        }

        if(params[3]) {
            if(supportedAlgorithms.find(params[3]) != supportedAlgorithms.end()) {
                algorithmType = params[3];
            } else {
                std::cout << "Invalid algorithm type";
                return false;
            }
        }   

        return true;
    }

    const std::string& getFilePath() const { return filePath; }
    const std::string& getHash() const { return hash; }
    const std::string& getAlgorithmType() const { return algorithmType; }

private:
    std::string filePath = "";
    std::string hash = "";
    std::string algorithmType;

};