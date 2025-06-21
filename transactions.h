#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>

/* Declarations for transaction-related classes and functions */
void addTransaction();
std::string generateTransactionID();
void updateTransactionCount(int count);
int readTransactionCount();

#endif // TRANSACTIONS_H
