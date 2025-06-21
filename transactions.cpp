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
#include "transactions.h"
#include "globals.h"
#include "utility.h"
#include "customers.h"
#include "products.h"

/*
****************************************************************************
********************** TRANSACTIONS/SHOPPING START *************************
****************************************************************************
*/

/*
Class Name: Transaction
Purpose: Represents a financial transaction involving a customer and multiple products, tracking details such as transaction ID, customer ID, product IDs, total amount, and rewards earned.
Meaning of Attributes:
  - std::string transactionID: A unique identifier for the transaction, generated when the transaction is created.
  - std::string customerID: The unique identifier of the customer associated with the transaction.
  - std::vector<std::string> productIDs: A list of product IDs included in the transaction.
  - double totalAmount: The total amount of the transaction, stored as a double.
  - int rewardPoints: The total reward points earned in the transaction.
Description of Methods:
  - Transaction(std::string custID, std::vector<std::string> prodIDs, double totalAmt, int rewards): 
      Constructor to initialize a transaction with customer ID, product IDs, total amount, and rewards, and generate a unique transaction ID.
  - std::string toString(int transactionNumber) const: 
      Converts transaction details into a formatted string representation, including transaction number, transaction ID, customer ID, product IDs, total amount, and rewards.
  - static void saveTransactionToFile(const Transaction& transaction): 
      Appends the transaction's details to the "transactions.txt" file. If the file cannot be opened, outputs an error message.
*/
class Transaction {
public:
    std::string transactionID;
    std::string customerID;
    std::vector<std::string> productIDs;
    double totalAmount;
    int rewardPoints;

    Transaction(std::string custID, std::vector<std::string> prodIDs, double totalAmt, int rewards)
        : customerID(custID), productIDs(prodIDs), totalAmount(totalAmt), rewardPoints(rewards) {
            transactionID = generateTransactionID();
        }

    /*
    Method Name: toString
    Purpose: Converts transaction information into a formatted string representation.
    Meaning of Parameters:
    - int transactionNumber: The transaction number to include in the formatted output.
    Description of Return Values:
    - Returns a formatted string containing transaction details, including transaction ID, user ID, product IDs, total amount, and total reward points.
    */
    std::string toString(int transactionNumber) const {
        std::ostringstream oss;
        oss << "Transaction " << transactionNumber << "\n"
            << "\tTransaction ID: " << transactionID << "\n"
            << "\tUser ID: " << customerID << "\n"
            << "\tProducts: ";
        for (size_t i = 0; i < productIDs.size(); ++i) {
            oss << "Product " << i+1 << " " <<  productIDs[i];
            if (i < productIDs.size() - 1) oss << ", ";
        }
        oss << "\n\tTotal Amount: $" << totalAmount << "\n"
            << "\tTotal Reward Points: " << rewardPoints << "\n";
        return oss.str();
    }

    /*
    Method Name: saveTransactionToFile
    Purpose: Appends a transaction's information to the "transactions.txt" file.
    Meaning of Parameters:
    - const Transaction& transaction: The transaction object containing the details to be saved.
    Description of Return Values:
    - This method does not return a value. It writes the transaction's data to the file or outputs an error message if the file cannot be opened.
    */
    static void saveTransactionToFile(const Transaction& transaction) {
        std::ofstream outfile("transactions.txt", std::ios::app);
        if (outfile.is_open()) {
            int transactionNumber = readTransactionCount();
            outfile << transaction.toString(transactionNumber);
            outfile.close();
            std::cout << "\nTransaction saved successfully.\n";
        } else {
            std::cerr << "Error: Could not open transactions.txt file.\n";
        }
    }

};

/*
Function Name: readTransactionCount
Purpose: Reads the transaction count from the "transaction_count.txt" file.
Meaning of Parameters:
  - None.
Description of Return Values:
  - Returns the transaction count as an integer if successfully read from the file.
  - Returns 1 if the file cannot be read or the count is unavailable.
*/
int readTransactionCount() {
    std::ifstream infile("transaction_count.txt");
    int count = 1;
    if (infile >> count) {
        return count;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }
    return 1;
}

/*
Function Name: updateTransactionCount
Purpose: Updates the "transaction_count.txt" file with the given transaction count.
Meaning of Parameters:
  - int count: The new transaction count to be written to the file.
Description of Return Values:
  - This function does not return a value. It writes the provided count to the "transaction_count.txt" file.
*/
void updateTransactionCount(int count) {
    std::ofstream outfile("transaction_count.txt");
    outfile << count;
}

/*
Function Name: addTransaction
Purpose: Creates and records a new transaction by validating customer and product details, calculating rewards, and updating transaction records.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function does not return a value. It validates customer and product IDs, calculates total amounts and reward points, and updates the transaction count and customer rewards.
*/
void addTransaction() {
    std::string customerID;
    std::unordered_set<std::string> validProductIDs = loadAndDisplayProducts(5);
    
    if (validProductIDs.empty()) {
        return;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    // Step 1: Validate Customer ID
    customersTxtChecker();
    std::cout << "\nEnter 10 digit Customer ID number: ";
    std::cin >> customerID;
    if (!validateCustomerID(customerID)) {
        std::cerr << "Customer with ID " << customerID << " does not exist.\n";
        return;
    }
    else {
        std::cerr << "Welcome back customer: " << customerID << "\n\n";
    }

    // Step 2: Get Product IDs and validate each
    std::vector<std::string> productList; // Store the list of products for transaction record
    double totalAmount = 0.0;
    processProducts(productList, totalAmount);

    // Step 3: Calculate Rewards (e.g., 10% of totalAmount as reward points)
    int rewardPoints = calculateRewardPoints(totalAmount);

    int transactionCount = readTransactionCount();

    Transaction transaction(customerID, productList, totalAmount, rewardPoints);

    Transaction::saveTransactionToFile(transaction);

    // Update transaction count for the next transaction
    updateTransactionCount(transactionCount + 1);

    updateCustomerRewards(customerID, rewardPoints, 5);
}

/*
Function Name: generateTransactionID
Purpose: Generates a unique transaction ID by appending "Transaction" to a random 7-digit number.
Meaning of Parameters:
  - None.
Description of Return Values:
  - Returns a string containing the newly generated unique transaction ID.
  - Ensures the ID does not already exist in the `transactionIDs` set.
*/
std::string generateTransactionID() {
    std::srand(std::time(nullptr));
    std::string newID;
    // The do-while loop generates a unique transaction ID by repeatedly creating a random ID and checking it against existing IDs to ensure uniqueness before 
    // inserting it into the set.
    do {
        newID = "Transaction" + std::to_string(1000000 + std::rand() % 9000000);
    } while (transactionIDs.find(newID) != transactionIDs.end());
    transactionIDs.insert(newID);
    return newID;
}

/*
****************************************************************************
********************** TRANSACTIONS/SHOPPING END ***************************
****************************************************************************
*/
