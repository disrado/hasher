#include <iostream>
#include <fstream>
#include <sstream>

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
    std::cout << "Enter file name: ";

    std::string fileName;
    std::cin >> fileName;

    std::ifstream file(fileName.c_str());

    std::stringstream buffer;
    buffer << file.rdbuf();
    
    std::string hash = "";

    CryptoPP::MD5 algo;

    getHash(buffer.str(), hash, algo);

    std::cout << "hash: " << hash << std::endl;
}
