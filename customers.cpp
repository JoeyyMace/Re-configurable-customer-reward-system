#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <cctype>
#include <iomanip>
#include "customers.h"
#include "globals.h"
#include "utility.h"

/*
****************************************************************************
********************* CUSTOMER ACCOUNT REGISTRATION START ******************
****************************************************************************
*/

/*
Class Name: Customer
Purpose: Represents a customer with attributes such as name, ID, and accumulated rewards points.
Meaning of Attributes:
  - std::string name: The name of the customer.
  - int customerID: A unique identifier for the customer.
  - int rewardsPoints: The rewards points accumulated by the customer.
Description of Methods:
  - Customer(): Default constructor to initialize a customer with default values.
  - Customer(const std::string& name, int id): 
      Parameterized constructor to initialize a customer with a specific name and ID.
  - std::string getName() const: Returns the customer's name.
  - int getCustomerID() const: Returns the unique customer ID.
  - int getRewardsPoints() const: Returns the customer's current rewards points.
  - void addRewardsPoints(int points): Adds the given points to the customer's rewards balance.
  - void printCustomerDetails() const: Prints the details of the customer to the console.
*/
class Account {
public:
    std::string userID;
    std::string username;
    std::string firstName;
    std::string lastName;
    int age;
    std::string creditCard;
    int rewardPoints;

    Account(std::string uname, std::string fname, std::string lname, int age, std::string card)
        : username(uname), firstName(fname), lastName(lname), age(age), creditCard(card), rewardPoints(0) {
        userID = generateUserID();
}

    /*
    Method Name: capitalize
    Purpose: Converts the first character of a string to uppercase and all subsequent characters to lowercase.
    Meaning of Parameters:
    - const std::string& name: The input string to be capitalized.
    Description of Return Values:
    - Returns a new string with the first character capitalized and the rest in lowercase.
    - If the input string is empty, it returns the original empty string.
    */
    static std::string capitalize(const std::string& name) {
        if (name.empty()) {
            return name;
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
        std::string capitalizedName = name;
        capitalizedName[0] = std::toupper(capitalizedName[0]);
        std::transform(capitalizedName.begin() + 1, capitalizedName.end(), capitalizedName.begin() + 1, ::tolower);
        return capitalizedName;
    }

    /*
    Method Name: toString
    Purpose: Converts customer information into a formatted string representation.
    Meaning of Parameters:
    - int customerNumber: The customer number to include in the formatted output.
    Description of Return Values:
    - Returns a formatted string containing customer details, including their ID, username, first and last name (capitalized), age, credit card, and total reward points.
    */
    std::string toString(int customerNumber) const {
        return "Customer " + std::to_string(customerNumber) + "\n" +
               "\tID: " + userID + "\n" +
               "\tUser name: " + username + "\n" +
               "\tFirst Name: " + capitalize(firstName) + "\n" +
               "\tLast Name: " + capitalize(lastName) + "\n" +
               "\tAge: " + std::to_string(age) + "\n" +
               "\tCredit Card: " + creditCard + "\n" +
               "\tTotal Reward Points: " + std::to_string(rewardPoints) + "\n";
    }

    /*
    Method Name: saveAccountToFile
    Purpose: Appends the current customer's information to the "customers.txt" file.
    Meaning of Parameters:
    - int customerNumber: The customer number to include in the saved data.
    Description of Return Values:
    - This method does not return a value. It writes the customer's data to the file or outputs an error message if the file cannot be opened.
    */
    void saveAccountToFile(int customerNumber) const {
        std::ofstream outfile("customers.txt", std::ios::app);
        if (outfile.is_open()) {
            outfile << toString(customerNumber); // Save this specific account's data
            outfile.close();
            std::cout << "Account saved successfully.\n";
        } else {
            std::cerr << "Error: Could not open customers.txt file.\n";
        }
    }
    /*
    Method Name: readCustomerCount
    Purpose: Reads the current customer count from the "customer_count.txt" file.
    Meaning of Parameters:
    - None.
    Description of Return Values:
    - Returns the customer count as an integer if the file is successfully read.
    - Returns 1 if the file cannot be opened or the count is unavailable.
    */
    static int readCustomerCount() {
        std::ifstream infile("customer_count.txt");
        int count = 1;
        if (infile.is_open()) {
            infile >> count;
            infile.close();
        }
        else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
        return count;
    }

    /*
    Method Name: updateCustomerCount
    Purpose: Updates the customer count in the "customer_count.txt" file with the provided value.
    Meaning of Parameters:
    - int count: The new customer count to be written to the file.
    Description of Return Values:
    - This function does not return a value. It writes the updated count to the file if it is successfully opened.
    */
    static void updateCustomerCount(int count) {
        std::ofstream outfile("customer_count.txt");
        if (outfile.is_open()) {
            outfile << count;
            outfile.close();
        }
        else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
    }
};

/*
Function Name: generateUserID
Purpose: Generates a unique customer ID by appending "CustID" to a random 10-digit number.
Meaning of Parameters:
  - None.
Description of Return Values:
  - Returns a string containing the newly generated unique customer ID.
  - Ensures the ID does not already exist in the `customerIDs` set.
*/
std::string generateUserID() {
    std::srand(std::time(nullptr));
    std::string newID;
    do {
        newID = "CustID" + std::to_string(1000000000 + std::rand() % 9000000000);
    } while (customerIDs.find(newID) != customerIDs.end());
    customerIDs.insert(newID);
    return newID;
}

// Customer Validation Start

/*
Function Name: validateAge
Purpose: Checks if the given age is within a valid range.
Meaning of Parameters:
  - int age: The age to validate, expected to be a non-negative integer.
Description of Return Values:
  - Returns `true` if the age is between 0 and 100 (inclusive).
  - Returns `false` if the age is less than 0 or greater than 100.
*/
bool validateAge(int age) {
    return (age >= 0 && age <= 100);
}

/*
Function Name: validateCreditCard
Purpose: Validates the format and uniqueness of a credit card number.
Meaning of Parameters:
  - std::string& cardNumber: The credit card number to validate, provided as a string (expected in the format XXXX-XXXX-XXXX).
  - std::unordered_set<std::string>& existingCards: A set of strings containing existing credit card numbers to check for duplicates.
Description of Return Values:
  - Returns `true` if the credit card number is valid in format and does not already exist in the provided set.
  - Returns `false` if the format is incorrect or if the card number already exists.
*/
bool validateCreditCard(const std::string& cardNumber, const std::unordered_set<std::string>& existingCards) {
    if (existingCards.find(cardNumber) != existingCards.end()) {
        std::cerr << "Invalid credit card format or card already exists.\n";
        return false;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    if (cardNumber.size() != 14 || cardNumber[4] != '-' || cardNumber[9] != '-') {
        std::cerr << "Invalid credit card format.\n";
        return false;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    // Validates that all characters in the credit card number are digits except for hyphens at positions 4 and 9.
    for (int i = 0; i < 14; ++i) {
        if (i == 4 || i == 9) {
            continue;
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
        if (!std::isdigit(cardNumber[i])) {
            std::cerr << "Invalid credit card format.\n";
            return false;
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
    }

    if (cardNumber[0] == '0') {
        std::cerr << "Invalid credit card format: Card number cannot start with 0.\n";
        return false;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    return true;
}

/*
Function Name: validateUsername
Purpose: Validates the format and uniqueness of a username.
Meaning of Parameters:
  - const std::string& username: The username to validate, provided as a string.
  - const std::unordered_set<std::string>& existingUsernames: A set containing existing usernames to check for duplicates.
Description of Return Values:
  - Returns `true` if the username is valid in format and does not already exist in the provided set.
  - Returns `false` if the format is incorrect or if the username already exists.
*/
bool validateUsername(const std::string& username, const std::unordered_set<std::string>& existingUsernames) {
    if (existingUsernames.find(username) != existingUsernames.end()) {
        std::cerr << "Invalid username or username already exists.\n";
        return false;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    if (username.size() != 10 || username.substr(0, 2) != "U_") {
        std::cerr << "Invalid format: Username must start with 'U_' and be exactly 10 characters long.\n";
        return false;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    int letterCount = 0;
    int digitCount = 0;
    // Counts the number of letters and digits in the username (after 'U_') while ensuring it contains only alphanumeric characters.
    for (size_t i = 2; i < username.size(); ++i) {
        if (std::isalpha(username[i])) {
            letterCount++;
        } else if (std::isdigit(username[i])) {
            digitCount++;
        } else {
            std::cerr << "Invalid format: Username can only contain letters and numbers after 'U_'.\n";
            return false;
        }
    }

    // Validates that the username (after 'U_') follows one of the allowed letter-to-digit combinations: 
    // 5 letters and 3 digits, 6 letters and 2 digits, 7 letters and 1 digit, or 8 letters and 0 digits.
    if ((letterCount == 5 && digitCount == 3) ||
        (letterCount == 6 && digitCount == 2) ||
        (letterCount == 7 && digitCount == 1) ||
        (letterCount == 8 && digitCount == 0)) {
        return true;
    } else {
        std::cerr << "Invalid format: Username must follow one of the required letter-number combinations after 'U_'.\n";
        return false;
    }
}

/*
Function Name: validateName
Purpose: Validates if a name contains only alphabetic characters and is at most 12 characters long.
Meaning of Parameters:
  - const std::string& name: The name to validate, provided as a string.
Description of Return Values:
  - Returns `true` if the name is at most 12 characters long and contains only alphabetic characters.
  - Returns `false` if the name exceeds 12 characters or contains non-alphabetic characters.
*/
bool validateName(const std::string& name) {
    return (name.size() <= 12 && std::all_of(name.begin(), name.end(), ::isalpha));
}
//Customer validation end

//Creates an account instance start
/*
Function Name: addAccount
Purpose: Collects user input to create a new customer account, validates the input, and saves the account information to a file.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function does not return a value. It performs operations such as input validation, file updates, and updating in-memory sets of existing usernames and credit cards.
*/
void addAccount() {
    std::string username, firstName, lastName, creditCard;
    int age;

    username = userNameCreation();

    firstName = firstNameCreation();

    lastName = lastNameCreation();

    age = ageCreation();

    creditCard = creditCardCreation();

    int customerNumber = Account::readCustomerCount();
    Account account(username, firstName, lastName, age, creditCard);
    account.saveAccountToFile(customerNumber);

    //Updates the count in the customer_count.txt and stores the value dynamically
    int newCount = customerNumber + 1;
    Account::updateCustomerCount(newCount);

    existingUsernames.insert(username);
    existingCreditCards.insert(creditCard);
}

/*
Function Name: userNameCreation
Purpose: Creates a username for a customer and validates to make sure it is following proper guidelines.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function returns the validated username.
*/
std::string userNameCreation()
{
    std::string username;

    std::cout << "Enter a username that starts with 'U_' and is a maximum of 10 characters (including 'U_'): ";
    std::cin >> username;
    if (!validateUsername(username, existingUsernames)) {
        return userNameCreation();
    } else {
        return username;
    }
}

/*
Function Name: firstNameCreation
Purpose: Creates a first name for a customer and validates to make sure it is following proper guidelines.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function returns the validated first name.
*/
std::string firstNameCreation()
{
    std::string firstName;

    std::cout << "Enter first name: ";
    std::cin >> firstName;
    if (!validateName(firstName)) {
        std::cerr << "Invalid first name. Only alphabetic characters allowed.\n";
        return firstNameCreation();
    } else {
        return firstName;
    }
}

/*
Function Name: lastNameCreation
Purpose: Creates a last name for a customer and validates to make sure it is following proper guidelines.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function returns the validated last name.
*/
std::string lastNameCreation()
{
    std::string lastName;

    std::cout << "Enter last name: ";
    std::cin >> lastName;
    if (!validateName(lastName)) {
        std::cerr << "Invalid first name. Only alphabetic characters allowed.\n";
        return lastNameCreation();
    } else {
        return lastName;
    }
}

/*
Function Name: ageCreation
Purpose: Lets the user input their age and validates to make sure it is following proper guidelines.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function returns the validated age info.
*/
int ageCreation()
{
    int age;

    std::cout << "Enter age: ";
    std::cin >> age;
    if (!validateAge(age)) {
        std::cerr << "Invalid age. Must be between 0 and 100.\n";
        return ageCreation();
    } else {
        return age;
    }
}

/*
Function Name: creditCardCreation
Purpose: Creates a credit card for a customer and validates to make sure it is following proper guidelines.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function returns the validated credit card info.
*/
std::string creditCardCreation()
{
    std::string creditCard;

    std::cout << "Enter credit card (xxxx-xxxx-xxxx format): ";
    std::cin >> creditCard;
    if (!validateCreditCard(creditCard, existingCreditCards)) {
        std::cerr << "Invalid credit card format or card already exists.\n";
        return creditCardCreation();
    } else {
        return creditCard;
    }
}

/*
Function Name: displayCustomerInfo
Purpose: Displays detailed information about a specific customer using their customer ID.
Meaning of Parameters:
  - const std::string& customerID: The customer ID for which information is to be displayed.
Description of Return Values:
  - This function does not return a value. It outputs the customer's details to the console if found or an error message if the customer does not exist.
*/
void displayCustomerInfo(const std::string& customerID) {
    customersTxtChecker();

    std::ifstream infile("customers.txt");

    std::string line;
    std::string fullCustomerID = "ID: CustID" + customerID; // Add "CustID" prefix to the input number
    bool found = false;
    int lineCounter = 0;

    // The while loop reads each line of the "customers.txt" file, trims it, and checks if it matches the fullCustomerID;
    // if a match is found, it prints the customer's details (the matching line and the next 6 lines) and stops further reading.
    while (std::getline(infile, line)) {
        
        line = trim(line);
        // Check for the matching customer ID line
        if (line == fullCustomerID) {
            found = true;
            std::cout << "Customer Details:\n";
            std::cout << "\t"<< line << "\n"; // Print the customer ID line

            // Print the following 6 lines to display all details
            for (int i = 0; i < 6; ++i) {
                if (std::getline(infile, line)) {
                    std::cout << line << "\n";
                }
            }
            break;
        }
        else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
    }

    infile.close();

    if (!found) {
        std::cerr << "Customer with " << fullCustomerID << " not found.\n";
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }
}

/*
Function Name: removeAccount
Purpose: Removes a customer account from the "customers.txt" file based on the provided account ID and updates the customer count.
Meaning of Parameters:
  - const std::string& accountID: The ID of the account to be removed from the file.
Description of Return Values:
  - This function does not return a value. It updates the "customers.txt" file by removing the specified account and rewrites the file, or outputs error messages if issues occur.
*/
void removeAccount(const std::string& accountID) {
    std::ifstream inFile("customers.txt");
    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
        return;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    std::vector<std::string> fileContents;
    std::string line;
    bool accountFound = false;
    bool skip = false;

    // Read each line and decide whether to keep or skip it
    while (getline(inFile, line)) {
        if (!skip && line.find("ID: " + accountID) != std::string::npos) {
            // Start skipping lines for the account to remove
            accountFound = true;
            skip = true;
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
        if (skip) {
            // Keep skipping until we reach a new customer or end of account data
            if (line.empty() || line.find("Customer") != std::string::npos) {
                skip = false;  // Stop skipping at the end of the account
            }
        } else {
            fileContents.push_back(line); // Add the line if not skipping
        }
    }
    inFile.close();

    if (!accountFound) {
        std::cout << "Account ID not found.\n";
        return;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    // Rewrite the file with remaining accounts
    std::ofstream outFile("customers.txt", std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    for (size_t i = 0; i < fileContents.size(); ++i) {
        const std::string& contentLine = fileContents[i];
        outFile << contentLine << "\n";
    }

    outFile.close();
    deincrement_count("customer_count.txt");
    std::cout << "Account removed successfully.\n";
}

/*
Function Name: validateCustomerID
Purpose: Checks if a specific customer ID exists in the "customers.txt" file.
Meaning of Parameters:
  - const std::string& customerID: The customer ID to validate, provided as a string.
Description of Return Values:
  - Returns `true` if the customer ID exists in the "customers.txt" file.
  - Returns `false` if the customer ID does not exist or if the file cannot be opened.
*/
bool validateCustomerID(const std::string& customerID) {
    customersTxtChecker();
    std::ifstream infile("customers.txt");
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open customers.txt file.\n";
        return false;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    std::string line;
    std::string fullCustomerID = "ID: CustID" + customerID;
    fullCustomerID = trim(fullCustomerID);  // Trim any extra spaces from the fullCustomerID if needed

    // The while loop reads each line from the "customers.txt" file, trims it, and checks if it matches the fullCustomerID;
    // if a match is found, it outputs a success message and returns true, otherwise, it continues searching until the end of the file.
    while (std::getline(infile, line)) {
        line = trim(line);  // Trim each line before checking
        if (line == fullCustomerID) { // Exact match comparison
            std::cout << "\nCustomer ID '" << customerID << "' found.\n";
            return true;
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
    }

    std::cout << "\nCustomer ID '" << customerID << "' not found.\n";
    return false;
}

/*
Function Name: calculateRewardPoints
Purpose: Calculates reward points based on the total transaction amount.
Meaning of Parameters:
  - double totalAmount: The total amount of the transaction, used to compute reward points.
Description of Return Values:
  - Returns an integer representing the total reward points earned based on the transaction amount.
*/
int calculateRewardPoints(double totalAmount){
    int fullChunks = static_cast<int>(totalAmount / 5);
    double remainder = totalAmount - (fullChunks*5);
    int rewardPoints = (fullChunks*10) + static_cast<int>((remainder/5) * 10); 

    return rewardPoints;
}

/*
Function Name: readAndModifyCustomerRewards
Purpose: Reads customer data from the "customers.txt" file, updates reward points for a specified customer, and returns the updated lines.
Meaning of Parameters:
  - const std::string& customerID: The ID of the customer whose reward points are to be modified.
  - int newRewardPoints: The reward points to be added or subtracted from the customer's total.
  - bool& customerFound: A reference variable indicating whether the specified customer ID was found.
  - int menuFlag: Determines the operation. If `menuFlag` is 5, reward points are added; otherwise, they are subtracted.
Description of Return Values:
  - Returns a `std::vector<std::string>` containing the updated lines of the "customers.txt" file.
  - If the customer is not found, the lines remain unchanged, and `customerFound` is set to false.
*/
std::vector<std::string> readAndModifyCustomerRewards(const std::string& customerID, int newRewardPoints, bool& customerFound, int menuFlag) {
    std::ifstream infile("customers.txt");
    std::vector<std::string> lines;
    customerFound = false;

    customersTxtChecker();

    std::string line;
    // The while loop reads each line from the "customers.txt" file, searches for a customer matching the given ID, and updates the reward points if found; it stores all lines in a vector, modifying only the relevant customer's details.
    while (getline(infile, line)) {
        if (line.find("ID: CustID" + customerID) != std::string::npos) {
            lines.push_back(line); // Customer ID line
            getline(infile, line); // Username line
            lines.push_back(line);
            getline(infile, line); // First Name line
            lines.push_back(line);
            getline(infile, line); // Last Name line
            lines.push_back(line);
            getline(infile, line); // Age line
            lines.push_back(line);
            getline(infile, line); // Credit Card line
            lines.push_back(line);

            // Modify the Total Reward Points line
            getline(infile, line);
            int currentRewardPoints = 0;

            size_t pos = line.find(":");
            if (pos != std::string::npos){
                std::string currentPointsStr = line.substr(pos+1);
                currentRewardPoints = std::stoi(currentPointsStr);
            } else {
                ; // Null Statement: to satisify requirement that every if block has a corresponding else.
            }

            int updatedRewardPoints = customerRewardUpdatePath(menuFlag, currentRewardPoints, newRewardPoints);
            std::stringstream ss;
            ss << "\tTotal Reward Points: " << updatedRewardPoints;
            lines.push_back(ss.str());

            customerFound = true;
        } else {
            lines.push_back(line);
        }
    }

    infile.close();
    return lines;
}

/*
Function Name: writeUpdatedCustomerData
Purpose: Writes updated customer data back to the "customers.txt" file.
Meaning of Parameters:
  - const std::vector<std::string>& lines: A vector containing the updated lines to be written to the file.
Description of Return Values:
  - This function does not return a value. It writes the updated customer data to the file and confirms success with a console message.
*/
void writeUpdatedCustomerData(const std::vector<std::string>& lines) {
    std::ofstream outfile("customers.txt");

    customersTxtChecker();

    // Expanded loop for writing each line to the file
    for (std::size_t i = 0; i < lines.size(); ++i) {
        outfile << lines[i] << "\n";
    }

    outfile.close();
    std::cout << "\nCustomer data updated successfully.\n";
}

/*
Function Name: updateCustomerRewards
Purpose: Updates the reward points for a specified customer and writes the changes back to the "customers.txt" file.
Meaning of Parameters:
  - const std::string& customerID: The ID of the customer whose reward points are to be updated.
  - int newRewardPoints: The reward points to be added or subtracted.
  - int menuFlag: Determines the operation. If `menuFlag` is 5, reward points are added; otherwise, they are subtracted.
Description of Return Values:
  - This function does not return a value. It updates the customer's reward points if the customer is found or outputs an error message if the customer does not exist.
*/
void updateCustomerRewards(const std::string& customerID, int newRewardPoints, int menuFlag) {
    bool customerFound;
    std::vector<std::string> lines = readAndModifyCustomerRewards(customerID, newRewardPoints, customerFound, menuFlag);

    if (customerFound) {
        writeUpdatedCustomerData(lines);
        std::cout << "\n" << newRewardPoints << " Reward points updated successfully for customer ID: " << customerID << "\n";
    } else {
        std::cerr << "\nCustomer with ID " << customerID << " not found.\n";
    }
}

/*
Function Name: customerRewardUpdatePath
Purpose: Updates the customer's reward points based on the menu option.
Meaning of Parameters:
  - int menuFlag: Determines the operation. If `menuFlag` is 5, reward points are added; otherwise, they are subtracted.
  - int currentRewardPoints: The customer's current reward points.
  - int newRewardPoints: The reward points to be added or subtracted.
Description of Return Values:
  - Returns the updated reward points as an integer after applying the specified operation.
*/
int customerRewardUpdatePath(int menuFlag, int currentRewardPoints, int newRewardPoints) {
    if(menuFlag == 5) {
        return currentRewardPoints + newRewardPoints;
    }
    else{
        return currentRewardPoints - newRewardPoints;
    }
}
//Creates an account instance end

/*
****************************************************************************
********************* CUSTOMER ACCOUNT REGISTRATION END ********************
****************************************************************************
*/