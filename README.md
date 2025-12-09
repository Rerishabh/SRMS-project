# SRMS-project
Student Record Management System


A menu driven Student Management System built using C language with file handling, multi-role login, and structured data management.
This project was developed as part of an academic assignment to demonstrate practical implementation of structures, file operations, modular programming, and user authentication.

 Key Features

 Admin

* Add Student
* Display All Students
* Search Student (by Roll / Name)
* Update Student (Rename / Marks)
* Delete Student
* Logout

Staff

* Rename Student
* Update Marks
* Display Students
* Search Students

User

* Display Students Only

Guest

* Display Students
* Search Students

 File Handling

All student data is stored persistently using:

* `students.dat` (binary file)
* `fwrite()`, `fread()`, `fopen()`, `fseek()`

Ensures safe, fast, and structured storage.

Technologies Used

* C Programming
* File Handling (Binary)
* Structures
* Switch-case
* Modular Functions


How to Compile & Run

```bash
gcc main.c -o managementapp
./managementapp
```


 Project Objective

To build a complete management system demonstrating:

* Multi-level user login
* Real-world student database handling
* Menu-driven program structure
* Hands-on use of file operations in C



 

