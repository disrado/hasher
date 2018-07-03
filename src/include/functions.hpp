#pragma once

#include <iostream>


std::string readFileToString(const std::string& filePath) {
	try {
		std::ifstream fileToHashing(filePath);

		if (!fileToHashing.is_open()) {
			throw std::runtime_error("Cannot open file " + filePath);
		}

		std::stringstream buffer;
		buffer << fileToHashing.rdbuf();
		return buffer.str();
	}
	catch (std::exception& e) {
		std::cout << "\nException: " << e.what() << std::endl;
		throw;
	}
}


void printMan()
{
	std::cout << " - Supported algorithms: md5, sha1, sha224, sha256, sha512                                   \n\n"
			  << "   Register of algorithm type is not important                                               \n\n"
			  << " - Calculate hash of file                                                                    \n\n"
			  << "   -f {path to file} {algorithm type}                                                        \n\n"
		      << " - Compare hashes of files                                                                   \n\n"
			  << "   For campare one or multiple files, you should add config file with name config.json         \n"
			  << "   and put it next to the executable file or directory from you launch executable file.        \n"
			  << "   Next you should edit config file. Example:                                                \n\n"
			  << "   {                                                                                           \n"
			  << "       \"files\": {                                                                            \n"
			  << "           \"C:/Users/user/Desktop/t1.txt\": \"26682ED0BAF2E1D38208BB1C513C7D5D0FEA65CF\",     \n"
			  << "           \"C:/Users/user/Desktop/t2.txt\" : \"4EE6B80FEF0DD234E383946A4CFF147F1EFF6D0D\"     \n"
	          << "       },                                                                                      \n"
		      << "       \"algorithm\" : \"SHA1\",                                                               \n"
			  << "       \"timestep\" : 2                                                                        \n"
              << "   }                                                                                         \n\n"
		      << "   Path to the file must not contain \"\\\"                                                    \n"
		      << "   Timestep - hash comparison period in seconds. Set to 0 if need only one check               \n";
}