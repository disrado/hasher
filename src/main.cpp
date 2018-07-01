#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>

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


// void validateHashes(const StringMap& fileHashPairs) {
//     if(auto hashPair : fileHashPairs) {
//         if(hashPair.first == hashPair.second)
//             std::cout << "Same hash" << std::endl;
//     }
// }

#include <cryptopp/integer.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/config.h>



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

    Hasher hasher;

    std::vector<std::string> fileNames;

    auto fileHashPairs = cfgReader.getFileHashPairs();

    std::for_each(fileHashPairs.begin(), fileHashPairs.end(), [&fileNames](auto& pair){ fileNames.push_back(pair.first); });

    auto computedHashers = hasher.computeHashes(fileNames, cfgReader.getAlgorithmType());

    for(auto& pair : computedHashers) {
        if(fileHashPairs.find(pair.first) != fileHashPairs.end()) {
            std::string hashIsValid = (fileHashPairs[pair.first] == pair.second) ? "Same hash" : "Hash in't same";
            std::cout << pair.first << " : " << hashIsValid << std::endl;
        }
    }

    // auto hashes = computeHashes(ConfigReader.getFileHashPairs());    

    // validateHashes(hashes);

    // auto timeStep = (paramsParser.getTimeStep() != seconds(0)) ? paramsParser.getTimeStep() : cfgReader.getTimeStep();

    // while(true) {
    //     auto fileContent = readFileToString(filePath);
            

    //     if (fileHash == validHash)
    //         std::cout << "Same fileHash" << std::endl;
    //     else
    //         std::cout << "Hash doesn't same" << std::endl
    //         << "Template: " << validHash << std::endl
    //         << "Hash    : " << fileHash << std::endl;


    //     fileHash.clear();
        // if (timeStep > seconds(0))
        // 	std::sleep_fore(timeStep);
        // else
        // 	break;
    // }
}
