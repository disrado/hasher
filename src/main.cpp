#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <integer.h>
#include <cryptlib.h>
#include <md5.h>
#include <sha.h>
#include <aes.h>
#include <hex.h>
#include <config.h>

//	CryptoPP::MD5 sha1;
//	CryptoPP::StringSource("nikita", true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hashHolder))));


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
    if(argc < 3) {
        std::cout << "Cannot run program without parameters." << std::endl;
        return 1;
    } 
    
    std::string algorithm;

    if(argv[3]) {
        algorithm = argv[3];
    } else {
        std::ifstream config("config.txt");
        std::string cfgAlgo;
        config >> cfgAlgo;
        algorithm = cfgAlgo.substr(cfgAlgo.find(':') + 1);
    
        if(algorithm.empty()) {
            std::cout << "Algorithm not specified" << std::endl;
            return 1;
        }
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
