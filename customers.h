#ifndef CUSTOMERS_H
#define CUSTOMERS_H

/* Declarations for customer-related classes and functions */

void customersTxtChecker();
bool validateCustomerID(const std::string& customerID);
void deincrement_count(const std::string& fileName);
void addAccount();
void removeAccount(const std::string& accountID);
void displayCustomerInfo(const std::string& customerID);
std::string generateUserID();
bool validateCustomerID(const std::string& customerID);
int calculateRewardPoints(double totalAmount);
std::vector<std::string> readAndModifyCustomerRewards(const std::string& customerID, int newRewardPoints, bool& customerFound, int menuFlag);
void writeUpdatedCustomerData(const std::vector<std::string>& lines);
void updateCustomerRewards(const std::string& customerID, int newRewardPoints, int menuFlag);
int customerRewardUpdatePath(int menuFlag, int currentRewardPoints, int newRewardPoints);
std::string userNameCreation();
std::string firstNameCreation();
std::string lastNameCreation();
int ageCreation();
std::string creditCardCreation();

#endif // CUSTOMERS_H
