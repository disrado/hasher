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

void md5(const std::string& sourceString, std::string& hashHolder)
{
//	CryptoPP::MD5 sha1;
//	CryptoPP::StringSource("nikita", true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hashHolder))));

    CryptoPP::MD5 md5;
    CryptoPP::byte digest[CryptoPP::MD5::DIGESTSIZE];

    md5.CalculateDigest(digest, (CryptoPP::byte*)sourceString.c_str(), sourceString.length());

    CryptoPP::HexEncoder encoder;

    encoder.Attach(new CryptoPP::StringSink(hashHolder));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

}

void sha1(const std::string& sourceString, std::string& hashHolder)
{
//	CryptoPP::SHA1 sha1;
//	CryptoPP::StringSource(sourceString, true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hashHolder))));

    CryptoPP::SHA1 md5;
    CryptoPP::byte digest[CryptoPP::SHA1::DIGESTSIZE];

    md5.CalculateDigest(digest, (CryptoPP::byte*)sourceString.c_str(), sourceString.length());

    CryptoPP::HexEncoder encoder;

    encoder.Attach(new CryptoPP::StringSink(hashHolder));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
}

void sha256(const std::string& sourceString, std::string& hashHolder)
{
    CryptoPP::SHA256 md5;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

    md5.CalculateDigest(digest, (CryptoPP::byte*)sourceString.c_str(), sourceString.length());

    CryptoPP::HexEncoder encoder;

    encoder.Attach(new CryptoPP::StringSink(hashHolder));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
}

void sha224(const std::string& sourceString, std::string& hashHolder)
{
    CryptoPP::SHA224 md5;
    CryptoPP::byte digest[CryptoPP::SHA224::DIGESTSIZE];

    md5.CalculateDigest(digest, (CryptoPP::byte*)sourceString.c_str(), sourceString.length());

    CryptoPP::HexEncoder encoder;

    encoder.Attach(new CryptoPP::StringSink(hashHolder));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
}


int main()
{
    std::cout << "Enter file name: ";

    std::string fileName;
    std::cin >> fileName;
        
    std::ifstream file(fileName.c_str());

    std::stringstream buffer;
    buffer << file.rdbuf();
    
    std::string hash = "";

    md5(buffer.str(), hash);

    std::cout << "MD5: " << hash << std::endl;

    hash = "";

    sha1(buffer.str(), hash);

    std::cout << "SHA1: " << hash << std::endl;
    
    hash = "";

    sha256(buffer.str(), hash);

    std::cout << "SHA256: " << hash << std::endl;

    hash = "";

    sha224(buffer.str(), hash);

    std::cout << "SHA224: " << hash << std::endl;
}
