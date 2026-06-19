# Student Record Management System

A console-based C application for managing student records, with persistent storage in a text file.

## Features

- Add, search, update, and delete student records
- Load records from file automatically on startup
- Save records to file (manually or automatically on exit)
- Input validation (ID format, GPA range, duplicate ID checks)
- Simple menu-driven interface

## Tech Stack

- C
- File I/O (fopen, fscanf, fprintf)
- Structs and pointers

## How to Run

1. Compile the program:

   gcc main.c -o student_manager

2. Run it:

   ./student_manager

3. Use the menu to load, add, search, update, delete, or save student records.

## Data Format

Each line in students.txt represents one student record in the format:

id name department gpa

Example:

1001 John_Smith CE 3.51