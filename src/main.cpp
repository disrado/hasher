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

typedef std::chrono::seconds seconds;

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
	try {
		std::ifstream fileToHashing(filePath);

		if (!fileToHashing.is_open()) {
			std::cout << "Cannot open file " << filePath << std::endl;
			exit(1);
		}

		std::stringstream buffer;
		buffer << fileToHashing.rdbuf();
		return std::make_shared<std::string>(std::move(buffer.str()));
	}
	catch (std::exception& e){
		std::cout << "Cannot read file " << filePath << "\n" << e.what() << std::endl;
	}
}


int main(int argc, char** argv)
{
	ParametersParser paramsParser;
	ConfigReader cfgReader;

	if (argc != 1) {
		if(!paramsParser.parse(argc, argv))
			return 1;
	}

	std::string algorithm = paramsParser.getAlgorithmType();

	if (algorithm.empty()) {
		if (cfgReader.readJSON("config.json"))
			algorithm = cfgReader.getAlgorithmType();
		else
			return 1;

		if (algorithm.empty()) {
			std::cout << "Algorithm not specified";
			return 1;
		}
	}

	std::string filePath = (paramsParser.getFilePath() != "") ? paramsParser.getFilePath() : cfgReader.getFilePath(),
				validHash = (paramsParser.getHash() != "") ? paramsParser.getHash() : cfgReader.getHash(),
				hash;
	
	auto timeStep = (paramsParser.getTimeStep() != seconds(0)) ? paramsParser.getTimeStep() : cfgReader.getTimeStep();

	while(true) {
		auto fileContent = readFileToString(filePath);
			
		if (algorithm == "MD5" || algorithm == "md5") {
			CryptoPP::MD5 algo;
			getHash(*fileContent, hash, algo);
		}
		else if (algorithm == "SHA1" || algorithm == "sha1") {
			CryptoPP::SHA1 algo;
			getHash(*fileContent, hash, algo);
		}
		else if (algorithm == "SHA224" || algorithm == "sha224") {
			CryptoPP::SHA224 algo;
			getHash(*fileContent, hash, algo);
		}
		else if (algorithm == "SHA256" || algorithm == "sha256") {
			CryptoPP::SHA256 algo;
			getHash(*fileContent, hash, algo);
		}
		else if (algorithm == "SHA512" || algorithm == "sha512") {
			CryptoPP::SHA512 algo;
			getHash(*fileContent, hash, algo);
		}
		else {
			std::cout << "Unknown algorithm" << std::endl;
			return 1;
		}

		if (hash == validHash)
			std::cout << "Same hash" << std::endl;
		else
			std::cout << "Hash doesn't same" << std::endl
			<< "Template: " << validHash << std::endl
			<< "Hash    : " << hash << std::endl;


		hash.clear();

		if (timeStep > seconds(0))
			std::this_thread::sleep_for(timeStep);
		else
			break;
	}
}
