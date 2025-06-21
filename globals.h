#ifndef GLOBALS_H
#define GLOBALS_H

#include <unordered_set>
#include <string>

// Global data for consistency checks and tracking

extern std::unordered_set<std::string> customerIDs;
extern std::unordered_set<std::string> existingUsernames;
extern std::unordered_set<std::string> existingCreditCards;
extern std::unordered_set<std::string> productIDs;
extern std::unordered_set<std::string> transactionIDs;

#endif // GLOBALS_H