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

#include <functions.hpp>


typedef std::map<std::string, std::string> StringMap;


class Hasher {

private:
	Hasher() {};

public:

	static Hasher& getInstance()
	{
		static Hasher instance;
		return instance;
	}

    StringMap computeHashes(std::vector<std::string>& filePaths, std::string algorithmName) {
		m_fileHashPairs.clear();

        for(auto& filePath : filePaths)
			m_fileHashPairs.emplace(filePath, computeHash(filePath, algorithmName));

        return m_fileHashPairs;
    }

	std::string computeHash(const std::string& filePath, std::string algorithmName) {

		std::string fileContent;

		try {
			fileContent = readFileToString(filePath);
		}
		catch (std::exception& e) {
			return "Cannot read file";
		}

		std::transform(algorithmName.begin(), algorithmName.end(), algorithmName.begin(), ::tolower);

		if (algorithmName == "md5") {
			CryptoPP::MD5 algo;
			m_hash = getHashFromString(fileContent, algo);
		}
		else if (algorithmName == "sha1") {
			CryptoPP::SHA1 algo;
			m_hash = getHashFromString(fileContent, algo);
		}
		else if (algorithmName == "sha224") {
			CryptoPP::SHA224 algo;
			m_hash = getHashFromString(fileContent, algo);
		}
		else if (algorithmName == "sha256") {
			CryptoPP::SHA256 algo;
			m_hash = getHashFromString(fileContent, algo);
		}
		else if (algorithmName == "sha512") {
			CryptoPP::SHA512 algo;
			m_hash = getHashFromString(fileContent, algo);
		}
		else {
			std::cout << "Unknown algorithm" << std::endl;
			exit(1);
		}

		return m_hash;
	}

	const StringMap& getComputedHashes() const { return m_fileHashPairs; }
	const std::string& getComputedHash() const { return m_hash; };

private:
    template<typename T>
    std::string getHashFromString(const std::string& sourceString, T& algorithm) const
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

private:
	StringMap m_fileHashPairs;
	std::string m_hash;
};
