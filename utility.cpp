#include <iostream>
#include "utility.h"

/*
Function Name: trim
Purpose: Removes leading and trailing whitespace from a given string.
Meaning of Parameters:
  - const std::string& s: The string to be trimmed.
Description of Return Values:
  - Returns a new string with leading and trailing whitespace removed.
  - If the input string is empty or contains only whitespace, an empty string is returned.
*/
std::string trim(const std::string &s) {
    // Find the start of the non-whitespace characters
    std::string::const_iterator start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        ++start;
    }

    // Find the end of the non-whitespace characters
    std::string::const_iterator end = s.end();
    if (start != end) {  // Check to avoid decrementing if the string is empty or only whitespace
        do {
            --end;
        } while (end != start && std::isspace(*end));
    } else {
      ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }

    // Return the trimmed string
    return std::string(start, end + 1);
}

/*
Function Name: deincrement_count
Purpose: Decreases the count stored in a specified file by 1, typically used when removing an item.
Meaning of Parameters:
  - std::string fileName: The name of the file containing the count to be decreased.
Description of Return Values:
  - This function does not return a value. It updates the count in the specified file or outputs an error message if the file cannot be opened.
*/
void deincrement_count(const std::string& fileName) {
    std::ifstream inFile(fileName);
    int num;

    if (inFile.is_open()) {
        inFile >> num;
        inFile.close();
    } else {
        std::cerr << "Error: Could not open file." << std::endl;
        return;
    }

    num--;

    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        outFile << num;
        outFile.close();
    } else {
        std::cerr << "Error: Could not open file." << std::endl;
    }
}

/*
Function Name: productsTxtChecker
Purpose: Checks if the "products.txt" file exists and provides an error message if it does not.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function does not return a value. It outputs an error message if the file is missing and suggests a solution.
*/
void productsTxtChecker()
{
    std::ifstream infile("products.txt");
    if (!infile.is_open()) {
        std::cerr << "Error: products.txt file does not exist.\n";
        std::cerr << "Please go to menu option 1 and input some customer information.\n";
        return;
    } else {
      ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }
}


/*
Function Name: customersTxtChecker
Purpose: Checks if the "customers.txt" file exists and provides an error message if it does not.
Meaning of Parameters:
  - None.
Description of Return Values:
  - This function does not return a value. It outputs an error message if the file is missing and suggests a solution.
*/
void customersTxtChecker()
{
    std::ifstream infile("customers.txt");
    if (!infile.is_open()) {
        std::cerr << "Error: customers.txt file does not exist.\n";
        std::cerr << "Please go to menu option 1 and input some customer information.\n";
        return;
    } else {
      ; // Null Statement: to satisify requirement that every if block has a corresponding else.
    }
}