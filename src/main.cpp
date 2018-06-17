#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

#include <cryptopp/integer.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/md5.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/config.h>

#include <ConfigReader.hpp>
#include <ParametersParser.hpp>


template<typename T>
void getHash(const std::string& sourceString, std::string& hashHolder, T& algorithm)
{
    CryptoPP::byte digest[T::DIGESTSIZE];
    algorithm.CalculateDigest(digest, (CryptoPP::byte*)sourceString.c_str(), sourceString.length());

    CryptoPP::HexEncoder encoder;
    encoder.Attach(new CryptoPP::StringSink(hashHolder));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
}


std::shared_ptr<std::string> readFileToString(const std::string filePath) {
    std::ifstream fileToHashing(filePath);
    std::stringstream buffer;
    buffer << fileToHashing.rdbuf();
    return std::make_shared<std::string>(std::move(buffer.str()));
}


int main(int argc, char** argv)
{
    ParametersParser paramsParser;
    ConfigReader cfgReader;

    if(!paramsParser.parse(argc, argv)) {
        return 1;
    }

    std::string algorithm = paramsParser.getAlgorithmType();

    if(algorithm.empty()) {
        cfgReader.readJSON("config.json");
        algorithm = cfgReader.getAlgorithmType();

        if(algorithm.empty())
            throw std::runtime_error("Algorithm not specified");
    }

    std::string filePath = (paramsParser.getFilePath() != "") ? paramsParser.getFilePath()
                                                              : cfgReader.getFilePath(),
                fileContentHolder, 
                hash;

    auto fileContent = readFileToString(filePath);
    
    if(algorithm == "MD5" || algorithm == "md5") {
        CryptoPP::MD5 algo;
        getHash(*fileContent, hash, algo);
    } else if(algorithm == "SHA1" || algorithm == "sha1") {
        CryptoPP::SHA1 algo;
        getHash(*fileContent, hash, algo);
    } else if(algorithm == "SHA224" || algorithm == "sha224") {
        CryptoPP::SHA224 algo;
        getHash(*fileContent, hash, algo);
    } else if(algorithm == "SHA256" || algorithm == "sha256") {
        CryptoPP::SHA256 algo;
        getHash(*fileContent, hash, algo);
    } else if(algorithm == "SHA512" || algorithm == "sha512") {
        CryptoPP::SHA512 algo;
        getHash(fileContentHolder, hash, algo);
    } else {
        std::cout << "Unknown algorithm" << std::endl;
        return 1;
    }

    std::string validHash = (paramsParser.getHash() != "") ? paramsParser.getHash() 
                                                           : cfgReader.getHash();

    if(hash == validHash)
        std::cout << "Same hash" << std::endl;
    else
        std::cout << "Hash doesn't same" << std::endl
                  << "Template: " << paramsParser.getHash() << std::endl
                  << "Hash    : " << hash << std::endl;
}
