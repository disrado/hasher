#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;



class ConfigReader {

public:

    bool readJSON(const std::string& filePath) {
        std::ifstream configFile(filePath);

        if(!configFile.is_open()){
            std::cout << "Cannot open config file" << std::endl;
            return false;
        }

        json conf;
        configFile >> conf;

        algorithm = conf.at("algorithm").get<std::string>();
    
        return true;    
    }

    const std::string& getAlgorithmType() {
        return algorithm;
    }

private:
    std::string algorithm;
};