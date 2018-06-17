#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;


class ConfigReader {

public:
    bool readJSON(const std::string& filePath) {
        std::ifstream configFile(filePath);

        if(!configFile.is_open()) {
            std::cout << "Cannot open config file" << std::endl;
            return false;
        }

        json conf;
        configFile >> conf;

        m_filePath = conf.at("filepath").get<std::string>();
        m_hash = conf.at("hash").get<std::string>();
        m_algorithmType = conf.at("algorithm").get<std::string>();
        
        return true;
    }

    const std::string& getFilePath() const { return m_filePath; }
    const std::string& getHash() const { return m_hash; }
    const std::string& getAlgorithmType() const { return m_algorithmType; }
    
private:
    std::string m_filePath;
    std::string m_hash;
    std::string m_algorithmType;
};