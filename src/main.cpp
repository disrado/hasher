#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

#include <nlohmann/json.hpp>

#include <cryptopp/integer.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/md5.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/config.h>

#include "ConfigReader.hpp"

//	CryptoPP::MD5 sha1;
//	CryptoPP::StringSource("nikita", true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hashHolder))));


std::set<std::string> validAlgorithms {
    "MD5",
    "md5",
    "SHA1",
    "sha1",
    "SHA224",
    "sha224",
    "SHA256",
    "sha256",
    "SHA512",
    "sha512"
};


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


bool checkParameters(int argc, char** argv)
{
    if(argc < 3) {
        std::cout << "Cannot run program without some parameters" << std::endl;
        return false;
    } 

    std::ifstream cfg;

    cfg.open(argv[1]);

    // if(!) {
        // std::cout << "Cannot open file " << argv[1] << std::endl;
        // retutn false;
    // }

    if(!argv[2]) {
        std::cout << "Hash for compare not specified" << std::endl;
        return false;
    }

    if(argv[3]) {
        if(validAlgorithms.find(argv[3]) == validAlgorithms.end()) {
            std::cout << "Invalid algorithm type";
            return false;
        }
    }   

    return true;
}

int main(int argc, char** argv)
{
    std::string algorithm;

    if(argv[3]) {
        algorithm = argv[3];
    } else {
        ConfigReader cfgReader;

        cfgReader.readJSON("config.json");

        algorithm =  cfgReader.getAlgorithmType();

        if(algorithm.empty())
            std::cout << "Algorithm not specified" << std::endl;
    }

    std::ifstream file(argv[1]);


    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string hash = "";

    if(algorithm == "MD5" || algorithm == "md5") {
        CryptoPP::MD5 algo;
        getHash(buffer.str(), hash, algo);
    } else if(algorithm == "SHA1" || algorithm == "sha1") {
        CryptoPP::SHA1 algo;
        getHash(buffer.str(), hash, algo);
    } else if(algorithm == "SHA224" || algorithm == "sha224") {
        CryptoPP::SHA224 algo;
        getHash(buffer.str(), hash, algo);
    } else if(algorithm == "SHA256" || algorithm == "sha256") {
        CryptoPP::SHA256 algo;
        getHash(buffer.str(), hash, algo);
    } else if(algorithm == "SHA512" || algorithm == "sha512") {
        CryptoPP::SHA512 algo;
        getHash(buffer.str(), hash, algo);
    } else {
        std::cout << "Unknown algorithm" << std::endl;
        return 1;
    }

    if(hash == argv[2]) {
        std::cout << "Same hash" << std::endl;
    } else {
        std::cout << "Hash doesnt same" << std::endl;
        std::cout << "hash: " << hash << std::endl;
    }
}
