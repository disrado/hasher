#pragma once

#include <nlohmann/json.hpp>

#include <chrono>
#include <map>
#include <iostream>

using json = nlohmann::json;


class ConfigReader {

public:
    bool readJSON(const std::string& filePath) {
        std::ifstream configFile(filePath);

        if(!configFile.is_open()) {
            std::cout << "Cannot open config file" << std::endl;
            return false;
        }

        try {
            json conf;
            configFile >> conf;
            m_fileHashPairs = conf.at("files").get<std::map<std::string, std::string>>();

            m_algorithmType = conf.at("algorithm").get<std::string>();
            m_timestep = std::chrono::seconds(conf.at("timestep").get<uint64_t>());
        }
        catch (std::exception& e) {
            std::cout << "Error while reading config file\n" << e.what() << std::endl;
            return false;
        }

        return true;
    }

    const auto getFileHashPairs() const { return m_fileHashPairs; };
    const std::string& getAlgorithmType() const { return m_algorithmType; }
    std::chrono::seconds getTimeStep() const { return m_timestep; }
    
private:
    std::map<std::string, std::string> m_fileHashPairs;
    std::string m_algorithmType;
    std::chrono::seconds m_timestep;
}; 
