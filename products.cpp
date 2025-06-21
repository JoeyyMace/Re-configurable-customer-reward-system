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
#include "products.h"
#include "globals.h"
#include "utility.h"

/*
****************************************************************************
************************ PRODUCT REGISTRATION START ************************
****************************************************************************
*/

/*
Class Name: Product
Purpose: Represents a product with attributes such as ID, name, price, and inventory, and provides methods to manage and persist product data.
Meaning of Attributes:
  - std::string productID: A unique identifier for the product, generated when the product is created.
  - std::string name: The name of the product.
  - double price: The price of the product in dollars, stored as a double with two decimal places.
  - int inventory: The quantity of the product available in stock.
Description of Methods:
  - Product(std::string pname, double pprice, int pinventory): 
      Constructor to initialize a product with a name, price, and inventory, and generate a unique product ID.
  - std::string toString(int productNumber) const: 
      Converts product information into a formatted string representation, including the product number, ID, name, price (with two decimal places), and inventory count.
  - static void saveProductToFile(const Product& product): 
      Appends the product's details to the file "products.txt". If the file cannot be opened, it outputs an error message.
  - static int readProductCount(): 
      Reads and returns the current product count from the file "product_count.txt". If the file is unavailable or unreadable, defaults to 1.
  - static void updateProductCount(int count): 
      Updates the product count in the file "product_count.txt" with the provided value. If the file cannot be opened or written to, outputs an error message.
*/
class Product {
public:
    std::string productID;
    std::string name;
    double price;
    int inventory;

    Product(std::string pname, double pprice, int pinventory)
        : name(pname), price(pprice), inventory(pinventory) {
        productID = generateProductID();
    }

    /*
    Method Name: toString
    Purpose: Converts product information into a formatted string representation.
    Meaning of Parameters:
    - int productNumber: The product number to include in the formatted output.
    Description of Return Values:
    - Returns a formatted string containing product details, including the product ID, name, price (with two decimal places), and inventory count.
    */
    std::string toString(int productNumber) const {
        std::ostringstream oss;
        oss << "Product " << productNumber << "\n"  // Add the product number
            << "\tID: " << productID << "\n"
            << "\tName: " << name << "\n"
            << "\tPrice: $" << std::fixed << std::setprecision(2) << price << "\n"
            << "\tInventory Count: " << inventory << "\n";
        return oss.str();
    }

    /*
    Method Name: saveProductToFile
    Purpose: Appends a product's information to the "products.txt" file.
    Meaning of Parameters:
    - const Product& product: The product object containing the details to be saved.
    Description of Return Values:
    - This method does not return a value. It writes the product's data to the file or outputs an error message if the file cannot be opened.
    */
    static void saveProductToFile(const Product& product) {
        std::ofstream outfile("products.txt", std::ios::app);

        if (outfile.is_open()) {
            int productNumber = Product::readProductCount(); // Get current product count
            outfile << product.toString(productNumber);      // Pass productNumber to toString
            outfile.close();

            std::cout << "Product saved successfully.\n";
        } else {
            std::cerr << "Error: Could not open products.txt file.\n";
        }
    }

    /*
    Method Name: readProductCount
    Purpose: Reads the current product count from the "product_count.txt" file.
    Meaning of Parameters:
    - None.
    Description of Return Values:
    - Returns the product count as an integer if the file is successfully read.
    - Returns 1 if the file cannot be opened or the count is unavailable.
    */
    static int readProductCount() {
        std::ifstream infile("product_count.txt");
        int count = 1; // Default to 1 if the file is missing or empty
        if (infile.is_open()) {
            infile >> count;
            infile.close();
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
        return count;
    }

    /*
    Method Name: updateProductCount
    Purpose: Updates the product count in the "product_count.txt" file with the provided value.
    Meaning of Parameters:
    - int count: The new product count to be written to the file.
    Description of Return Values:
    - This method does not return a value. It writes the updated count to the file if it is successfully opened. Outputs an error message if the file cannot be written.
    */
    static void updateProductCount(int count) {
        std::ofstream outfile("product_count.txt");
        if (outfile.is_open()) {
            outfile << count;
            outfile.close();
        } else {
            std::cerr << "Error: Unable to write to product_count.txt\n";
        }
    }
};

/*
Function Name: generateProductID
Purpose: Generates a unique product ID by appending "Prod" to a random 5-digit number.
Meaning of Parameters:
  - None.
Description of Return Values:
  - Returns a string containing the newly generated unique product ID.
  - Ensures the ID does not already exist in the `productIDs` set.
*/
std::string generateProductID() {
    std::srand(std::time(nullptr));
    std::string newID;
    // Generates a unique product ID in the format "ProdXXXXX" (with a random 5-digit number) and ensures uniqueness by checking against existing IDs.
    do {
        newID = "Prod" + std::to_string(10000 + std::rand() % 90000);
    } while (productIDs.find(newID) != productIDs.end());
    productIDs.insert(newID);
    return newID;
}

//Product validation start

/*
Function Name: isAlphaOrUnderscore
Purpose: Checks if a single character is either an alphabetic character or an underscore.
Meaning of Parameters:
  - char c: The character to validate.
Description of Return Values:
  - Returns `true` if the character is an alphabetic character (A-Z or a-z) or an underscore ('_').
  - Returns `false` if the character is neither alphabetic nor an underscore.
*/
bool isAlphaOrUnderscore(char c) {
    // Check if the character is alphabetic or an underscore
    return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
}

/*
Function Name: validateProductName
Purpose: Validates that a product name contains only alphabetic characters and is not empty.
Meaning of Parameters:
  - const std::string& name: The product name to validate, provided as a string.
Description of Return Values:
  - Returns `true` if the product name is non-empty and contains only alphabetic characters.
  - Returns `false` if the product name is empty or contains non-alphabetic characters.
*/
bool validateProductName(const std::string& name) {
    // Ensure the name is not empty
    if (name.empty()) {
        return false;
    }

    // Iterate through each character in the string
    for (std::string::const_iterator it = name.begin(); it != name.end(); ++it) {
        if (!isAlphaOrUnderscore(*it)) {
            return false; // Return false if any character is invalid
        }
    }

    return true; // Return true if all characters are valid
}

/*
Function Name: validateProductPrice
Purpose: Validates that the product price is a positive number with at most two decimal places.
Meaning of Parameters:
  - const std::string& priceStr: The product price to validate, provided as a string.
Description of Return Values:
  - Returns `true` if the product price is valid (positive, numeric, with at most two decimal places).
  - Returns `false` if the product price is invalid (non-numeric, negative, or has more than two decimal places).
*/
bool validateProductPrice(const std::string& priceStr) {
    int decimalCount = 0;
    bool decimalPointFound = false;

    // Check that each character is either a digit or a single decimal point
    for (size_t i = 0; i < priceStr.size(); ++i) {
        char ch = priceStr[i];
        if (ch == '.') {
            decimalCount++;
            decimalPointFound = true;
        } else if (!std::isdigit(ch)) {
            std::cerr << "Invalid input: Product price must be a numeric value.\n";
            return false;
        }
        
        if (decimalCount > 1) {
            std::cerr << "Invalid input: Product price must contain at most one decimal point.\n";
            return false;
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
    }

    // Convert the valid numeric string to double and check if it's positive
    double price = std::stod(priceStr);
    if (price <= 0.0) {
        std::cerr << "Invalid product price. Price must be a positive number.\n";
        return false;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    // Check for two decimal places
    if (decimalPointFound) {
        std::size_t decimalPos = priceStr.find('.');
        if (priceStr.size() - decimalPos - 1 > 2) {
            std::cerr << "Invalid input: Product price must have at most two decimal places.\n";
            return false;
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    return true;
}

/*
Function Name: validateInventoryCount
Purpose: Validates that the inventory count is a positive integer with no letters or special characters.
Meaning of Parameters:
  - const std::string& countStr: The inventory count to validate, provided as a string.
Description of Return Values:
  - Returns `true` if the inventory count is a positive integer.
  - Returns `false` if the inventory count contains non-numeric characters or is not positive.
*/
bool validateInventoryCount(const std::string& countStr) {
    // Check that every character in countStr is a digit
    if (!std::all_of(countStr.begin(), countStr.end(), ::isdigit)) {
        std::cerr << "Invalid input: Inventory count must be a positive integer.\n";
        return false;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    // Convert the valid numeric string to an integer and check if it's positive
    int count = std::stoi(countStr);
    if (count <= 0) {
        return false;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    return true;
}
//Product validation end

/*
Function Name: addProduct
Purpose: Creates an instance of the Product class by collecting user input, validating it, and saving the product to a file.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function does not return a value. It performs input validation, creates a product instance, and updates the product count and ID list.
*/
void addProduct() {
    std::string name;
    std::string priceStr;       // Use a string for price validation
    std::string inventoryStr;    // Use a string for inventory validation

    name = productNameCreation();

    priceStr = priceCreation();

    double price = std::stod(priceStr); // Convert to double after validation

    std::ostringstream formattedPrice;
    formattedPrice << std::fixed << std::setprecision(2);

    inventoryStr = inventoryCreation();

    int inventory = std::stoi(inventoryStr); // Convert to int after validation

    // If all validations pass, create and save the product
    
    int productNumber = Product::readProductCount();
    Product product(name, price, inventory);
    Product::saveProductToFile(product);

    int newCount = productNumber + 1; 
    Product::updateProductCount(newCount);
    
    productIDs.insert(product.productID);
}

/*
Function Name: productNameCreation
Purpose: Creates a product name and validates to make sure it is following proper guidelines.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function returns the validated product name.
*/
std::string productNameCreation()
{
    std::string name;

    std::cout << "Enter product name (if multiple words separate the words with _ not a space): ";
    std::cin >> name;
    if (!validateProductName(name)) {
        std::cerr << "Invalid product name. Only alphabetic characters allowed.\n";
        return productNameCreation(); 
    } else {
        return name;
    }
}

/*
Function Name: priceCreation
Purpose: Creates a price for a product and validates to make sure it is following proper guidelines.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function returns the validated product price.
*/
std::string priceCreation()
{
    std::string priceStr;

    std::cout << "Enter product price: ";
    std::cin >> priceStr;
    if (!validateProductPrice(priceStr)) {
        return productNameCreation(); 
    } else {
        return priceStr;
    }

}

/*
Function Name: inventoryCreation
Purpose: Creates an inventory count for a product and validates to make sure it is following proper guidelines.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function returns the validated inventory count.
*/
std::string inventoryCreation()
{
    std::string inventoryStr;

    std::cout << "Enter inventory count: ";
    std::cin >> inventoryStr;
    if (!validateInventoryCount(inventoryStr)) {
        return inventoryCreation(); 
    } else {
        return inventoryStr;
    }
}
/*
Function Name: removeProduct
Purpose: Removes a product from the "products.txt" file based on the provided product ID and updates the product count.
Meaning of Parameters:
  - const std::string& productID: The ID of the product to be removed from the file.
Description of Return Values:
  - This function does not return a value. It updates the "products.txt" file by removing the specified product and rewrites the file, or outputs error messages if issues occur.
*/
void removeProduct(const std::string& productID) {
    std::ifstream inFile("products.txt");
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
        if (!skip && line.find("ID: " + productID) != std::string::npos) {
            // Start skipping lines for the account to remove
            accountFound = true;
            skip = true;
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
        if (skip) {
            // Keep skipping until we reach a new customer or end of account data
            if (line.empty() || line.find("Product") != std::string::npos) {
                 skip = false;  // Stop skipping at the end of the account
            } else {
                ; // Null Statement: to satisify requirement that every if block has a corresponding else.
            }
        } else {
            fileContents.push_back(line); // Add the line if not skipping
        }
    }
    inFile.close();

    if (!accountFound) {
        std::cout << "Product ID not found.\n";
        return;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    // Rewrite the file with remaining accounts
    std::ofstream outFile("products.txt", std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    // The for loop iterates through the lines stored in the vector `fileContents` and writes each line back to the "products.txt" file to 
    // reconstruct the file without the removed product.
    for (std::vector<std::string>::const_iterator it = fileContents.begin(); it != fileContents.end(); ++it) {
        const std::string& contentLine = *it;
        outFile << contentLine << "\n";
    }


    outFile.close();
    deincrement_count("product_count.txt");
    std::cout << "Product removed successfully.\n";
}

/*
Function Name: loadAndDisplayProducts
Purpose: Displays products from a file and loads their IDs into a set for further processing.
Meaning of Parameters:
  - int menuFlag: Determines the file to read from. If `menuFlag` is 5, the function reads from "products.txt"; otherwise, it reads from "rewardsList.txt".
Description of Return Values:
  - Returns an `std::unordered_set<std::string>` containing the product IDs found in the file.
  - Outputs the product details to the console and provides a message if no products are available.
*/
std::unordered_set<std::string> loadAndDisplayProducts(int menuFlag) {
    std::unordered_set<std::string> productIDs;
    std::ifstream infile;
    std::string message;

    if(menuFlag == 5) {
        infile.open("products.txt");
        productsTxtChecker();
        message = "Available Products:\n";
    }
    else {
        infile.open("rewardsList.txt");
    }

    std::string line;
    bool productFound = false;
    int productCount = 0;

    std::cout << message;
    // The while loop reads each line from either "products.txt" or "rewardsList.txt," identifies product-related details, displays them, 
    // and collects product IDs into an unordered set.
    while (std::getline(infile, line)) {
        if (line.find("Product") != std::string::npos) {
            ++productCount;
            std::cout << "Product " << productCount << "\n";
        } else if (line.find("ID:") != std::string::npos) {
            std::string productID = line.substr(line.find(":") + 2);
            productIDs.insert(productID);
            productFound = true;
            std::cout << "\tID: " << productID << "\n";
        } else {
            std::cout << "  " << line << "\n";
        }
    }

    infile.close();

    if (!productFound) {
        std::cerr << "No products available in products.txt. Returning to main menu.\n";
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    return productIDs;
}

/*
Function Name: validateProductsID
Purpose: Validates if a given product ID exists in the file of available products or rewards.
Meaning of Parameters:
  - const std::string& productsID: The product ID to validate, provided as a string.
  - int menuFlag: Determines the file to validate against. If `menuFlag` is 5, the function checks "products.txt"; otherwise, it checks "rewardsList.txt".
Description of Return Values:
  - Returns `true` if the product ID is found in the specified file.
  - Returns `false` if the product ID is not found or the file does not exist.
*/
bool validateProductsID(const std::string& productsID, int menuFlag) {
    std::ifstream infile;
    if(menuFlag == 5) {
        infile.open("products.txt");
        productsTxtChecker(); // Check if products.txt exists
    }
    else {
        infile.open("rewardsList.txt");
    }
    std::string line;
    std::string fullProductID = "ID: Prod" + productsID;

    // Trim any extra spaces from the fullProductID
    fullProductID = trim(fullProductID);

    // The while loop reads each line from the specified file, trims it, and checks if it matches the given full product ID; if found, 
    // it returns true, otherwise continues searching.
    while (std::getline(infile, line)) {
        // Trim each line before checking
        line = trim(line);

        // Check if the line matches exactly with fullProductID
        if (line == fullProductID) {
            std::cout << "\nProduct ID '" << productsID << "' found.\n"; // Debug message
            return true; // Exact Product ID found
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
    }

    std::cerr << "\nProduct ID '" << productsID << "' not found.\n"; // Debug message
    return false; // Product ID not found
}

/*
Function Name: processProducts
Purpose: Handles the product selection process for a transaction, including validating product IDs, adjusting inventory, and calculating the total amount.
Meaning of Parameters:
  - std::vector<std::string>& productList: A reference to a vector where selected product IDs will be stored.
  - double& totalAmount: A reference to a double where the total amount of the transaction will be accumulated.
Description of Return Values:
  - This function does not return a value. It updates the provided product list and total amount based on user input and validation.
*/
void processProducts(std::vector<std::string> &productList, double &totalAmount) {
    int productCount;
    std::cout << "Enter the number of different products you wish to buy: ";
    std::cin >> productCount;
    if (productCount == 0) {
        return;
    } else {
        ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    char choice;
    int count = 0;
    int quantity = 0;
    std::string productID;
    double productPrice;

    // The do-while loop prompts the user to enter product IDs and quantities, validates the product ID, updates the inventory, 
    // calculates the total price, and repeats until the specified number of products has been
    do {
        std::cout << "\nEnter 5 digit Product ID #" << (++count) << ": ";
        std::cin >> productID;

        if (validateProductsID(productID, 5)) { // Only proceed if product ID is valid
            std::cout << "Enter the quantity of " << productID << " that you wish to purchase: ";
            std::cin >> quantity;

            bool productFound = false;
            std::vector<std::string> updatedInventory = readAndUpdateProductInventory(productID, quantity, productFound,5);

            if (productFound && !updatedInventory.empty()) {
                productList.push_back(productID);
                std::cout << "Added " << quantity << " of Product ID " << productID << " to the list.\n";
                processInventoryAdjustment(productID, quantity, 5);
                productCount -= 1;
                productPrice = getProductPrice(productID);
                totalAmount = totalAmount + (productPrice * quantity);
                std::cout << "The current total price is: $" << totalAmount << "\n";
            } else {
                std::cerr << "Transaction canceled for this item.\n";
            }
        } else {
            std::cerr << "Product with ID " << productID << " does not exist. Please enter a valid product ID.\n";
        }

    } while (productCount != 0);
}

/*
Function Name: getProductPrice
Purpose: Retrieves the price of a product based on its product ID from the "products.txt" file.
Meaning of Parameters:
  - const std::string& productID: The ID of the product for which the price is being retrieved.
Description of Return Values:
  - Returns the price of the product as a double if found in the file.
  - Returns -1.0 if the product ID or price is not found.
*/
double getProductPrice(const std::string& productID) {
    std::ifstream infile("products.txt");
    std::string line;
    std::string fullProductID = "ID: Prod" + productID;  // Full product ID format
    double price = -1.0; // Default to -1.0 to indicate not found

    // Trim any extra spaces from the fullProductID
    fullProductID = trim(fullProductID);

    bool productFound = false;

    // The while loop reads each line from "products.txt," checks for the specified product ID, and retrieves the price from the 
    // subsequent "Price: $" line if the product ID is found.
    while (std::getline(infile, line)) {
        line = trim(line);  // Trim whitespace from each line

        // Check for the product ID in the current line
        if (line == fullProductID) {
            productFound = true;
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }

        // If the product ID was found, look for the price on the next relevant line
        if (productFound && line.find("Price: $") != std::string::npos) {
            // Extract the price value after "Price: $"
            std::string priceStr = line.substr(line.find("$") + 1);
            price = std::stod(priceStr); // Convert price to double
            break;
        } else {
            ; // Null Statement: to satisify requirement that every if block has a corresponding else.
        }
    }

    return price;
}

/*
Function Name: readAndUpdateProductInventory
Purpose: Reads product inventory from a file, updates the inventory for a specified product ID, and returns the updated lines.
Meaning of Parameters:
  - const std::string& productID: The ID of the product whose inventory is being updated.
  - int quantity: The quantity to deduct from the current inventory.
  - bool& productFound: A reference variable to indicate whether the specified product ID was found.
  - int menuFlag: Determines the file to process. If `menuFlag` is 5, the function reads from "products.txt"; otherwise, it reads from "rewardsList.txt".
Description of Return Values:
  - Returns a `std::vector<std::string>` containing the updated lines of the file, including inventory adjustments if applicable.
  - If there is insufficient inventory, the function outputs an error message and returns the lines without changes.
*/
std::vector<std::string> readAndUpdateProductInventory(const std::string& productID, int quantity, bool& productFound, int menuFlag) {
    std::ifstream infile;
    if(menuFlag == 5) {
        infile.open("products.txt");
        productsTxtChecker();
    }
    else {
        infile.open("rewardsList.txt");
    }
    std::vector<std::string> lines;
    productFound = false;

    std::string line;
    // The while loop reads each line from the file, identifies the specified product ID, validates and updates its inventory if sufficient stock is available, 
    // and stores all lines in a vector for potential file updates.
    while (getline(infile, line)) {
        if (line.find("ID: Prod" + productID) != std::string::npos) {
            lines.push_back(line); // Product ID line
            getline(infile, line); // Name line
            lines.push_back(line);
            getline(infile, line); // Price line
            lines.push_back(line);

            // Process the Inventory Count line
            getline(infile, line);
            int currentInventory = 0;

            // Extract current inventory from the line
            size_t pos = line.find(":");
            if (pos != std::string::npos) {
                std::string currentInventoryStr = line.substr(pos + 1);
                currentInventory = std::stoi(currentInventoryStr);
            } else {
                ; // Null Statement: to satisify requirement that every if block has a corresponding else.
            }

            // Check if there's enough inventory
            if (currentInventory >= quantity) {
                int updatedInventory = currentInventory - quantity;

                // Update the line with the new inventory count, including the tab
                std::stringstream ss;
                ss << "\tInventory Count: " << updatedInventory;
                lines.push_back(ss.str());
            } else {
                std::cerr << "Error: Not enough inventory for product ID " << productID << ".\n";
                return lines;
                break;

            }

            productFound = true;
        } else {
            lines.push_back(line);
        }
    }

    infile.close();
    return lines;
}

/*
Function Name: writeUpdatedProductInventory
Purpose: Writes updated product inventory data back to the appropriate file.
Meaning of Parameters:
  - const std::vector<std::string>& lines: A vector containing the updated lines to be written to the file.
  - int menuFlag: Determines the file to write to. If `menuFlag` is 5, the function writes to "products.txt"; otherwise, it writes to "rewardsList.txt".
Description of Return Values:
  - This function does not return a value. It writes the updated lines to the specified file.
*/
void writeUpdatedProductInventory(const std::vector<std::string>& lines, int menuFlag) {
    std::ofstream outfile;
    if(menuFlag == 5) {
        outfile.open("products.txt");
        productsTxtChecker();
    }
    else {
        outfile.open("rewardsList.txt");
    }

    // The for loop iterates through the vector of lines and writes each line back to the appropriate file, ensuring the product inventory is updated.
    for (size_t i = 0; i < lines.size(); ++i) {
        outfile << lines[i] << "\n";
    }

    outfile.close();
}

/*
Function Name: processInventoryAdjustment
Purpose: Adjusts the inventory of a specified product by updating the product data in the appropriate file.
Meaning of Parameters:
  - const std::string& productID: The ID of the product whose inventory needs to be adjusted.
  - int quantity: The quantity to deduct from the product's inventory.
  - int menuFlag: Determines the file to process. If `menuFlag` is 5, the function adjusts inventory in "products.txt"; otherwise, it adjusts inventory in "rewardsList.txt".
Description of Return Values:
  - This function does not return a value. It updates the inventory if the product is found, or outputs an error message if the product is not found.
*/
void processInventoryAdjustment(const std::string& productID, int quantity, int menuFlag) {
    bool productFound = false;
    std::vector<std::string> updatedData;
    if(menuFlag == 5) {
        updatedData = readAndUpdateProductInventory(productID, quantity, productFound, menuFlag);
    }
    else {
        updatedData = readAndUpdateProductInventory(productID, quantity, productFound, menuFlag);
    }

    if (productFound) {
        writeUpdatedProductInventory(updatedData, menuFlag);
        std::cout << "\nInventory updated successfully for Product ID: " << productID << "\n";
    } 
    else {
        std::cerr << "Product with ID " << productID << " not found.\n";
    }
}
/*
****************************************************************************
************************ PRODUCT REGISTRATION END **************************
****************************************************************************
*/
