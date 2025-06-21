Table of Contents
-Introduction
-Prerequisites
-Steps for File Transfer and Execution
-Usage Notes

Introduction
-This guide demonstrates how to transfer files to the Lovelace server at Missouri State University and run a program using make and make run. This process uses tools like WinSCP for file transfer and PuTTY for terminal access.

Prerequisites
-Ensure you have the following tools installed and configured:
	-WinSCP: For secure file transfer.
	-PuTTY: For SSH access to Lovelace.
	-Missouri State University credentials.
	-Use Missouri State University server

Steps for File Transfer and Execution
1) Open WinSCP and Log Into Lovelace
	-Hostname: lovelace.missouristate.edu
	-Username: Your Missouri State credentials.
	-Password: Your Missouri State password.
2) Transfer the File
	-Locate the file labeled CSC455FinalProject on your local machine.
	-Drag and drop the file into the Lovelace portion of WinSCP.
	-Note the file path/directory where the file is uploaded.
	-Open PuTTY and Connect to Lovelace
	-Hostname: lovelace.missouristate.edu
	-Login using your Missouri State credentials.
	-Navigate to the File
		-Use appropriate cd commands to move to the directory where the file was uploaded:
			-cd /path/to/directory
	-Compile the Code
	-Run the following command to compile the code:
		-make
	-You should see outputs confirming a successful compilation.
	-Execute the program using:
		-make run

Usage Notes
-Menu Inputs:
	-When you select menu option 5 (Add Transaction/Shopping) or menu option 6 (View customer 
	 using customer ID) and you are told to input the customer ID, you have to enter	
 	 the 10 digit number that follows "CustID", but not "CustID" itself.
	-When you select menu option 2 (customer removal), you have to input "CustID" and the 10
	  numbers that follow the string "CustID". So it requires both.
	-When you select menu option 5 (Add Transaction/Shopping), and you have already inputted
	 a customer id, it will ask how many different products you wish to buy
		-If buying 1 product, type 1.
		-If buying multiple products (e.g., Product A and Product B), type the number 
		 of products (e.g., 2).
	-Then the code asks you to input a product id number
		-You just have to input the 5 digits after "Prod"
	-When you select menu option 4 (product removal), you have to input "Prod" and the 5
	 	numbers that follow the string "Prod". So it requires both.

-Where to find a customers id
	-After creating a customer account, open customers.txt to find the specific customer ID # 

-Notes:
	-When buying products, you won't be stuck in an infinite loop.
	 If you say you want to buy 3 products, but only 2 products are available,
	 one of the existing items you will have to purchase multiple times (just put quantity 0
	 for one of them)
	-All sales are final! Once you add transaction using its product id #, you can't remove it
	 from the "shopping cart". You can avoid charges by entering 0 for the quantity during
	 purchase.

-Side notes:
	-The code is designed to work properly as long as it is used as intended. 
	 Avoid attempts to break or misuse it.

