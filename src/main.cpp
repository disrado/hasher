#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>
#include <chrono>

#include <cryptopp/integer.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/md5.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/config.h>

#include <ConfigReader.hpp>
#include <ParametersParser.hpp>
#include <Hasher.hpp>

typedef std::chrono::seconds seconds;


#include <cryptopp/integer.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/config.h>



void validateHashes(const StringMap& fileHashPairs, const StringMap& computedHashers)
{
	for (auto& pair : computedHashers) {
		auto itr = fileHashPairs.find(pair.first);
		if (itr != fileHashPairs.end()) {
			std::string hashIsValid = (itr->second == pair.second) ? "Same hash" : "Hash isn't same. Current hash: " + pair.second;
			std::cout << pair.first << " : " << hashIsValid << std::endl;
		}
	}
	std::cout << std::endl;
}


void processOneFile(const std::string& filePath, const std::string& algorithm)
{
	std::string hash = Hasher::getInstance().computeHash(filePath, algorithm);
	std::cout << "Hash of " << filePath << ": " << hash << std::endl;
}


void processMultipleFiles()
{
	auto fileHashPairs = ConfigReader::getInstance().getFileHashPairs();
	std::vector<std::string> fileNames;
	std::for_each(fileHashPairs.begin(), fileHashPairs.end(), [&fileNames](auto& pair) { fileNames.push_back(pair.first); });

	auto timeStep = ConfigReader::getInstance().getTimeStep();

	while (true) {
		auto computedHashers = Hasher::getInstance().computeHashes(fileNames, ConfigReader::getInstance().getAlgorithmType());
		validateHashes(fileHashPairs, computedHashers);

		if (timeStep > seconds(0))
			std::this_thread::sleep_for(timeStep);
		else
			break;
	}
}


int main(int argc, char** argv)
{
    if (argc != 1) {
		ParametersParser::getInstance().parse(argc, argv);
    }

	std::string filePath = ParametersParser::getInstance().getFilePath();
    std::string algorithm = ParametersParser::getInstance().getAlgorithmType();

    if (!filePath.empty() && !algorithm.empty()) {
		processOneFile(filePath, algorithm);
	}
	else {
		if (ConfigReader::getInstance().readJSON("hasher_config.json")) {
			processMultipleFiles();
		}
	}
}

