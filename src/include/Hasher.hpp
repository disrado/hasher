#pragma once

#include <vector>
#include <map>
#include <algorithm>

#include <cryptopp/integer.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/md5.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/config.h>


typedef std::map<std::string, std::string> StringMap;


std::string readFileToString(const std::string&);


class Hasher {

public:
    StringMap computeHashes(const std::vector<std::string>& files, const std::string& algorithm) {
        StringMap fileHashPairs;

        for(auto& filePath : files) {
            std::string fileContent;

            try {
                fileContent = readFileToString(filePath); 
            } catch(std::exception& e) {
                fileHashPairs.emplace(filePath, "Cannot read file");
            }

            std::string algorithmName = algorithm;
            std::transform(algorithmName.begin(), algorithmName.end(), algorithmName.begin(), ::tolower);

            if (algorithmName == "md5") {
                CryptoPP::MD5 algo;
                
                fileHashPairs.emplace(filePath, getHash(fileContent, algo));
            }
            else if (algorithmName == "sha1") {
                CryptoPP::SHA1 algo;
                fileHashPairs.emplace(filePath, getHash(fileContent, algo));
            }
            else if (algorithmName == "sha224") {
                CryptoPP::SHA224 algo;
                fileHashPairs.emplace(filePath, getHash(fileContent, algo));
            }
            else if (algorithmName == "sha256") {
                CryptoPP::SHA256 algo;
                fileHashPairs.emplace(filePath, getHash(fileContent, algo));
            }
            else if (algorithmName == "sha512") {
                CryptoPP::SHA512 algo;
                fileHashPairs.emplace(filePath, getHash(fileContent, algo));
            }
            else {
                std::cout << "Unknown algorithm" << std::endl;
            }
        }

        return fileHashPairs;
    }

    template<typename T>
    std::string getHash(const std::string& sourceString, T& algorithm)
    {
        CryptoPP::byte digest[T::DIGESTSIZE];
        algorithm.CalculateDigest(digest, (CryptoPP::byte*)sourceString.c_str(), sourceString.length());
        std::string hash;

        CryptoPP::HexEncoder encoder;
        encoder.Attach(new CryptoPP::StringSink(hash));
        encoder.Put(digest, sizeof(digest));
        encoder.MessageEnd();

        return hash;
    }
};

std::string readFileToString(const std::string& filePath) {
    try {
        std::ifstream fileToHashing(filePath);

        if (!fileToHashing.is_open()) {
            std::cout << "Cannot open file " << filePath << std::endl;
            throw std::runtime_error("Cannot open file");
        }

        std::stringstream buffer;
        buffer << fileToHashing.rdbuf();
        return buffer.str();
    }
    catch (std::exception& e){
        std::cout << "Cannot read file " << filePath << "\nException: " << e.what() << std::endl;
        throw;
    }
}
