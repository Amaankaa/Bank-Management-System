# Bank Management System

## Overview
This is a simple **Bank Management System** implemented in C++. It allows users to create, manage, and delete bank accounts, as well as deposit and withdraw money. The program uses file handling to store account details persistently.

## Features
- Create an account
- Deposit money
- Withdraw money
- Balance enquiry
- Display existing accounts
- Delete an account

## Technologies Used
- **C++** for implementation
- **File Handling** for storing account data persistently
- **Command Line Interface (CLI)** for user interaction

## Installation and Usage
### Prerequisites
Ensure you have a C++ compiler installed. You can use **g++ (MinGW)** for Windows or **g++ (GCC)** for Linux/Mac.

### Steps to Compile and Run
1. Clone this repository or download the source code.
2. Open a terminal and navigate to the project folder.
3. Compile the code using the following command:
   ```sh
   g++ bank_management.cpp -o bank_management
   ```
4. Run the executable:
   ```sh
   ./bank_management   # On Linux/Mac
   bank_management.exe  # On Windows
   ```

## File Handling
- The system stores account details in a file named **account.dat**.
- The file is updated with every transaction or account modification.
- Deleted accounts are removed by rewriting the data into a temporary file and renaming it.

## Program Structure
The project consists of the following key functions:
- `write_account()`: Creates a new account and saves it to a file.
- `deposit_withdraw(int, int)`: Deposits or withdraws money from an account.
- `display_sp(int)`: Displays details of a specific account.
- `display_all()`: Displays all existing accounts.
- `delete_account(int)`: Deletes an account from the file.
- `intro()`: Displays an introduction screen.

## Contributors
- **Amanuel Merara** (UGR/30138/15)
- **Abenezer Gdilew** (UGR/30076/15)
- **Yosef Solomon** (UGR/31454/15)
- **Mikiyas Abebe** (UGR/26684/15)
- **Lemi Abduljebar** (UGR/30821/15)

## License
This project is open-source and available under the MIT License.

---
**Thank you for using our Bank Management System!**
