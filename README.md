# To-Do List Application in C using Linked List

## Overview

This project is a simple To-Do List application implemented in C using a linked list data structure. The application allows users to add, display, edit, mark tasks as completed, delete tasks, and save/load tasks from a file.

## Features

- **Add Task:** Insert a new task with a description and priority.
- **Display To-Do List:** View all tasks with their priorities and completion status.
- **Edit Task:** Modify an existing task's description and priority.
- **Mark Task as Completed:** Update a task's status to completion.
- **Delete Task:** Remove a task from the list.
- **Save To-Do List:** Save the current list of tasks to a file.
- **Load To-Do List:** Load tasks from a file into the application.

## System Requirements

- C Compiler (e.g., GCC)
- A standard C library

## Installation

1. **Clone the Repository:**

   ```sh
   git clone https://github.com/DevanshSrajput/TO-DO-List
   cd To-DO-List

## Compile the program

    ```sh
     gcc -o todo_list main.c

## Usage
   Run the Program
    
    ```sh
     ./todo_list

## Code Structure

- **main.c:** Contains the main program logic and menu handling.
- **task.c:** Functions for creating and managing tasks.
- **file_io.c:** Functions for saving to and loading from a file.
- **task.h:** Header file defining task-related structures and functions.

## Future Enhancements
- Implement task prioritization with sorting.
- Add a graphical user interface (GUI).
- Enhance persistent storage (e.g., using a database).
- Introduce task reminders and notifications.

## License
- This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing
- Feel free to submit issues and pull requests. Contributions are welcome!
