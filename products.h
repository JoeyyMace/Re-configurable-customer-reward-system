#ifndef PRODUCTS_H
#define PRODUCTS_H

/* Declarations for product-related classes and functions */
void productsTxtChecker();
void addProduct();
void removeProduct(const std::string& productID);
bool validateProductName(const std::string& name);
bool validateProductPrice(const std::string& priceStr);
bool validateInventoryCount(const std::string& countStr);
std::string generateProductID();
std::unordered_set<std::string> loadAndDisplayProducts(int menuFlag);
bool validateProductsID(const std::string& productsID, int menuFlag);
void processProducts(std::vector<std::string> &productList, double &totalAmount);
double getProductPrice(const std::string& productID);
std::vector<std::string> readAndUpdateProductInventory(const std::string& productID, int quantity, bool& productFound, int menuFlag);
void writeUpdatedProductInventory(const std::vector<std::string>& lines, int menuFlag);
void processInventoryAdjustment(const std::string& productID, int quantity, int menuFlag);
std::string productNameCreation();
std::string priceCreation();
std::string inventoryCreation();

#endif // PRODUCTS_H
