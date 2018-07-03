#pragma once

#include <iostream>
#include <set>

#include <functions.hpp>

std::set<std::string> supportedAlgorithms {
    "md5",
    "sha1",
    "sha224",
    "sha256",
    "sha512"
};


class ParametersParser {

private:
	ParametersParser() {};

public:
	static ParametersParser& getInstance()
	{
		static ParametersParser instance;
		return instance;
	}

    void parse(int paramsCount, char** params = nullptr) {

		std::string key(params[1]);

		if (key == "-h" || key == "--help") {
			printMan();
			exit(0);
		}
		else if (key == "-f") {

			if (paramsCount != 4) {
				std::cout << "Some parameters are not specified. Try use -h or --help for more info";
				exit(1);
			}

			m_filePath = params[2];
			std::string algorithm(params[3]);

			if (m_filePath.empty()) {
				std::cout << "File path not specified. Try use -h or --help for more info" << std::endl;
				exit(1);
			}

			if (algorithm.empty()) {
				std::cout << "Algorithm name not specified. Try use -h or --help for more info" << std::endl;
				exit(1);
			}

			std::transform(algorithm.begin(), algorithm.end(), algorithm.begin(), ::tolower);

			if (supportedAlgorithms.find(algorithm) != supportedAlgorithms.end()) {
				m_algorithmType = algorithm;
			}
			else {
				std::cout << "Invalid algorithm name. Try use -h or --help for more info" << std::endl;
				exit(1);
			}
		}
		else {
			std::cout << "Unknown parameter. Try use -h or --help for more info";
			exit(1);
		}
    }

	const std::string& getFilePath() const { return m_filePath; }
	const std::string& getAlgorithmType() const { return m_algorithmType; }

private:
	std::string m_filePath = "";
    std::string m_algorithmType = "";
};