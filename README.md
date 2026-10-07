# Course Management System

## Overview

The Course Management System is a C++ application designed to manage university course information for an academic advising program.

The application reads course data from a file, stores course information in a hash table, and provides a menu-driven interface for viewing the complete course list or searching for an individual course and its prerequisites.

Before implementing the final application, multiple data structures—including vectors, hash tables, and binary search trees—were evaluated to determine their advantages, disadvantages, and runtime characteristics.

## Features

- Load course information from a data file
- Parse course numbers, titles, and prerequisites
- Store course records using a hash table
- Search for courses by course number
- Display all courses in alphanumeric order
- Display individual course information
- Display prerequisite course numbers and titles
- Handle invalid files, missing courses, and invalid menu selections
- Normalize course numbers for consistent searching

## Technologies

- C++
- Visual Studio
- Standard Template Library (STL)
- `unordered_map`
- `vector`
- File I/O
- Sorting and searching algorithms

## Data Structure Design

During the design phase, three data structures were evaluated for managing course information:

- **Vector** – Simple and memory efficient, but searching requires linear traversal and the data must be sorted before displaying courses in order.
- **Hash Table** – Provides efficient average-case lookup by course number but does not naturally maintain sorted order.
- **Binary Search Tree** – Naturally supports ordered traversal and efficient average-case searching, although performance can decrease if the tree becomes unbalanced.

The final application uses an `unordered_map` to store courses using the course number as the key. This provides efficient lookup when searching for an individual course.

A vector of course IDs is generated and sorted when the complete course list needs to be displayed in alphanumeric order.

## Application Design

Each course is represented by a `Course` structure containing:

- Course ID
- Course title
- List of prerequisite course IDs

The application provides a menu with options to:

1. Load the course data
2. Print the complete course list
3. Search for and display an individual course
9. Exit the application

When an individual course is selected, the application also looks up and displays information about its prerequisites when those courses are available in the loaded data.

## File Processing

Course information is read from a comma-separated data file.

During file processing, the application:

- Splits each line into individual values
- Removes unnecessary whitespace
- Converts course IDs to uppercase for consistent searching
- Creates a `Course` object for each valid record
- Stores prerequisite IDs with the corresponding course
- Adds each course to the hash table

## Technical Decisions

The hash table implementation was selected because searching for an individual course is a primary operation of the advising application. Using the course number as the hash key allows courses to be retrieved efficiently without traversing the entire collection.

Because hash tables do not maintain their elements in sorted order, course IDs are also collected into a vector and sorted before the complete course list is displayed.

This design combines efficient course lookup with the ability to present course information in an organized alphanumeric format.

## Skills Demonstrated

- C++ programming
- Data structure selection
- Algorithm analysis
- Big-O runtime analysis
- Hash tables
- Vectors
- Sorting and searching
- File parsing
- Input validation
- Error handling
- Software design
- Debugging

## Project Structure

- `CourseManagementSystem.cpp` – C++ implementation of the Course Management System

## What I Learned

This project strengthened my understanding of selecting data structures based on the requirements of an application rather than simply choosing a structure that can store the necessary data.

By comparing vectors, hash tables, and binary search trees, I gained experience evaluating trade-offs involving searching, ordering, runtime performance, and implementation complexity.

Implementing the final application also strengthened my experience with C++ file processing, data structures, input validation, searching, sorting, and designing a menu-driven application.

## Potential Enhancements

Future improvements could include:

- Add a graphical user interface
- Store course information in a database
- Add advanced course search and filtering
- Support additional import file formats
- Add automated tests
- Benchmark data structure performance using larger datasets
