# Address Book

## Project Overview
A simple C-based Address Book application to add, search, display, and save contacts with email validation and file handling.

## Features
- Add new contacts
- Display all contacts
- Search contacts by name or email
- Save and load contacts from a file
- Prevent duplicate emails

## How to Run
1. Clone the repository:
   ```bash
   git clone <repository-url>
   ```
2. Navigate to the project folder:
   ```bash
   cd AddressBook
   ```
3. Compile the project:
   ```bash
   gcc main.c contact.c file.c -o AddressBook
   ```
4. Run the program:
   ```bash
   ./AddressBook
   ```

## File Structure
```
AddressBook/
├── main.c          # Main program
├── contact.h       # Contact structure and function declarations
├── contact.c       # Contact management functions
├── file.h          # File handling declarations
├── file.c          # File handling implementations
└── README.md       # Project documentation
```

## Author
**Nakul Anil Vadar**  
Electronic and Telecommunications Enthusiast
