#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& listType);

std::vector<std::string> split(std::string str, const std::string& token);


std::string ltrim(const std::string& s);

std::string rtrim(const std::string& s);

std::string trim(const std::string& s);

void overwriteFile(const std::string& path, const std::string& text);

std::string readFile(const std::string& path);

std::string deleteUtil(const std::string& str, const std::string& token);

std::string exec(const char* cmd);
