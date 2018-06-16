#include <iostream>
#include <sstream>
#include <fstream>

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


int main(int argc, char** argv)
{
    ParametersParser paramsParser;
    
    if(!paramsParser.parse(argc, argv))
        return 1;

    std::string algorithm;

    if(!paramsParser.getAlgorithmType().empty()) {
        algorithm = paramsParser.getAlgorithmType();
    } else {
        ConfigReader cfgReader;
        cfgReader.readJSON("config.json");
        algorithm = cfgReader.getAlgorithmType();

        if(algorithm.empty())
            std::cout << "Algorithm not specified" << std::endl;
    }

    std::string hash, fileContent;

    std::ifstream fileToHashing(paramsParser.getFilePath());
    std::stringstream buffer;
    buffer << fileToHashing.rdbuf();
    fileContent = buffer.str();
    
    if(algorithm == "MD5" || algorithm == "md5") {
        CryptoPP::MD5 algo;
        getHash(fileContent, hash, algo);
    } else if(algorithm == "SHA1" || algorithm == "sha1") {
        CryptoPP::SHA1 algo;
        getHash(fileContent, hash, algo);
    } else if(algorithm == "SHA224" || algorithm == "sha224") {
        CryptoPP::SHA224 algo;
        getHash(fileContent, hash, algo);
    } else if(algorithm == "SHA256" || algorithm == "sha256") {
        CryptoPP::SHA256 algo;
        getHash(fileContent, hash, algo);
    } else if(algorithm == "SHA512" || algorithm == "sha512") {
        CryptoPP::SHA512 algo;
        getHash(fileContent, hash, algo);
    } else {
        std::cout << "Unknown algorithm" << std::endl;
        return 1;
    }

    if(hash == paramsParser.getHash())
        std::cout << "Same hash" << std::endl;
    else
        std::cout << "Hash doesn't same" << std::endl
                  << "Template: " << paramsParser.getHash() << std::endl
                  << "Hash    : " << hash << std::endl;
}
