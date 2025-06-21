#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <cctype>
#include <fstream>

std::string trim(const std::string &s);
void deincrement_count(const std::string& fileName);
void productsTxtChecker();
void customersTxtChecker();

#endif // UTILITY_H
