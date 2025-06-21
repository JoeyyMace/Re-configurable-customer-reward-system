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
#include <limits>
#include <iomanip>
#include "customers.h"
#include "products.h"
#include "transactions.h"
#include "globals.h"
#include "utility.h"

/*
Function Name: getRewardAmount
Purpose: Retrieves the total reward points for a specified customer from the "customers.txt" file.
Meaning of Parameters:
  - const std::string& customerID: The ID of the customer whose reward points are being retrieved.
Description of Return Values:
  - Returns the total reward points as an integer if the customer ID is found.
  - Returns -1 if the customer ID or reward points are not found in the file.
*/
int getRewardAmount(const std::string& customerID) {
    std::ifstream infile("customers.txt");
    std::string line;
    std::string fullCustomerID = "ID: CustID" + customerID; // Full customer ID format
    fullCustomerID = trim(fullCustomerID); // Trim any extra spaces

    bool customerFound = false;
    int rewardPoints = -1; // Default to -1 to indicate not found
    
    // The while loop reads each line from the "customers.txt" file, searches for the specified customer ID, and extracts the reward points from the 
    // corresponding "Total Reward Points:" line if the customer is found.
    while (std::getline(infile, line)) {
        line = trim(line); // Trim whitespace from each line

        // Check if this line contains the customer ID
        if (line == fullCustomerID) {
            customerFound = true;
        }

        // If the customer ID was found, look for the reward points on the next relevant line
        if (customerFound && line.find("Total Reward Points:") != std::string::npos) {
            // Extract the reward points value after "Total Reward Points:"
            size_t pos = line.find(":");
            if (pos != std::string::npos) {
                std::string rewardStr = line.substr(pos + 1);
                rewardPoints = std::stoi(trim(rewardStr)); // Convert reward points to an integer
            }
            break;
        }
    }

    infile.close();

    return rewardPoints;
}

/*
Function Name: getRewardPointValue
Purpose: Retrieves the point value of a reward product based on its product ID from the "rewardsList.txt" file.
Meaning of Parameters:
  - const std::string& productID: The ID of the reward product for which the point value is being retrieved.
Description of Return Values:
  - Returns the point value as an integer if the product ID is found in the file.
  - Returns -1 if the product ID or point value is not found.
*/
int getRewardPointValue(const std::string& productID) {
    std::ifstream infile("rewardsList.txt");
    std::string line;
    std::string fullRewardID = "ID: Prod" + productID;  // Full reward ID format
    int pointValue = -1; // Default to -1 to indicate not found

    // Trim any extra spaces from the fullRewardID
    fullRewardID = trim(fullRewardID);

    bool rewardFound = false;

    // The while loop reads each line from the "rewardsList.txt" file, searches for the specified product ID, and extracts the "Point Value" from the 
    // subsequent relevant line if the product is found.
    while (std::getline(infile, line)) {
        line = trim(line);  // Trim whitespace from each line

        // Check for the product ID in the current line
        if (line == fullRewardID) {
            rewardFound = true;
            continue; // Move to next line to find relevant details
        }

        // If the reward ID was found, look for the "Point Value" line
        if (rewardFound && line.find("Point Value:") != std::string::npos) {
            // Extract the point value after "Point Value:"
            size_t pos = line.find(":");
            if (pos != std::string::npos) {
                std::string pointValueStr = line.substr(pos + 1);
                pointValueStr = trim(pointValueStr); // Remove any extra whitespace
                pointValue = std::stoi(pointValueStr); // Convert point value to integer
                break; // Exit once the value is found
            }
        }
    }

    infile.close();
    return pointValue;
}

/*
Function Name: redeemRewards
Purpose: Allows a customer to redeem rewards by validating their customer ID, checking available reward points, and deducting points if they redeem a product.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function does not return a value. It validates customer and product IDs, checks reward points, processes inventory adjustments, and updates the customer's reward points.
*/
void redeemRewards() {
    std::string customerID;
    std::string productID;
    int customerRewardsAmount;
    int redeemRewardAmount;

    std::cout << "\nEnter the 10 digit Customer ID: ";
    std::cin >> customerID;

    if (!validateCustomerID(customerID)) {
        std::cerr << "Customer with ID " << customerID << " does not exist.\n";
        return;
    }
    else {
        customerRewardsAmount = getRewardAmount(customerID);
        std::cerr << "Welcome to the reward section customer: " << customerID << "\n"
                    << "You have " << customerRewardsAmount << " points available\n";
    }
    std::cout << "\nHere are the all rewards that can be redeemed: \n";
    loadAndDisplayProducts(7);

    std::cout << "Enter the 5 digit Product ID to Redeem: ";
    std::cin >> productID;

    if (validateProductsID(productID, 7)){
        redeemRewardAmount = getRewardPointValue(productID);
        std::cout << "The customer " << customerID << " has: " << customerRewardsAmount << " points.";
        std::cout << "The reward you are trying to redeem costs: " << redeemRewardAmount << " points.";
        if(customerRewardsAmount >= redeemRewardAmount) {
            std::cout << "You redeemed Product ID: " << productID;
            processInventoryAdjustment(productID, 1, 7);   
            updateCustomerRewards(customerID, redeemRewardAmount, 7);
        }
        else {
            std::cout << "You don't have enough points to redeem";
        } 
    }
}

/*
****************************************************************************
************************ MAIN CODE / MAIN MENU START ***********************
****************************************************************************
*/

/*
Function Name: showMenu
Purpose: Displays the main menu options to the user.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function does not return a value. It outputs the menu options to the console for user selection.
*/
void showMenu() {
    std::cout << "\n1. Register Customer\n";
    std::cout << "2. Remove Customer\n";
    std::cout << "3. Add Product\n";
    std::cout << "4. Remove Product\n";
    std::cout << "5. Add Transaction/Shopping\n";
    std::cout << "6. View customer using customer ID\n";
    std::cout << "7. Redeem Rewards\n";
    std::cout << "8. Exit\n";
    std::cout << "Type a number 1 through 8: ";
}

/*
Function Name: main
Purpose: Serves as the entry point of the program, displaying the main menu and handling user input to navigate various functionalities.
Meaning of Parameters:
  - None.
Description of Return Values:
  - Returns 0 upon successful program termination.
  - Continuously executes a menu loop, invoking appropriate functions based on user input.
*/
int main() {
    int choice;
    int menuFlag = 0;
    
    // The while loop repeatedly displays the main menu, takes user input, 
    // and performs the appropriate action based on the selected choice, continuing until the user chooses to exit.
    while (true) {
        showMenu();
        std::cin >> choice;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string IDNumber = "";

        switch (choice) {
            case 1: addAccount(); 
                break;
            case 2: {
                    std::string accountID;

                    std::cout << "Enter the account ID, in this format: CustID########## to remove: ";
                    std::cin >> accountID;
                    removeAccount(accountID); 
                    break;
            }
            case 3: addProduct(); 
                break;
            case 4: {
                    std::string productID;
                    std::cout << "Enter the product ID, in this format:  Prod##### to remove: ";
                    std::cin >> productID;
                    removeProduct(productID);
                    break;
            }
            case 5: addTransaction(); 
                break;
            case 6:
                std::cout << "Enter the 10-digit customer ID number: ";
                std::cin >> IDNumber;
                displayCustomerInfo(IDNumber);
                break;
            case 7: redeemRewards(); 
                break;
            case 8: std::cout << "Exiting...\n"; 
                return 0;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    }
}

/*
****************************************************************************
************************ MAIN CODE / MAIN MENU END *************************
****************************************************************************
*/