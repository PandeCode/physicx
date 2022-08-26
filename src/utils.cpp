#include "utils.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

static constexpr auto WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s) {
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}
std::string rtrim(const std::string& s) {
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
std::string trim(const std::string& s) {
	return rtrim(ltrim(s));
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& listType) {
	stream << "{ ";
	for(auto it = listType.begin(); it != listType.end(); it++)
		stream << *it << (std::next(it) != listType.end() ? ", " : " }");
	return stream;
}

std::vector<std::string> split(std::string str, const std::string& token) {
	std::vector<std::string> result;
	while(str.size()) {
		std::size_t index = str.find(token);
		if(index != std::string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
			if(str.size() == 0) result.push_back(str);
		} else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}

void overwriteFile(const std::string& path, const std::string& text) {
	std::ofstream file(path, std::ofstream::trunc);
	if(file.bad()) { throw std::runtime_error("Bad file."); }
	file << text;
	file.close();
}

std::string readFile(const std::string& path) {
	std::ifstream file(path);
	if(file.bad()) { throw std::runtime_error("Bad file."); }

	std::stringstream ret = std::stringstream();
	std::string       tmp;
	while(std::getline(file, tmp))
		ret << tmp << "\n";
	file.close();
	return ret.str();
}

std::string deleteUtil(const std::string& str, const std::string& token) {
	return str.substr(str.find(token), str.size());
}

std::string exec(const char* cmd) {
	char        buffer[128];
	std::string result = "";
	FILE*       pipe   = popen(cmd, "r");
	if(!pipe) throw std::runtime_error("popen() failed!");
	try {
		while(fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	} catch(...) {
		pclose(pipe);
		throw;
	}
	pclose(pipe);
	return result;
}
