# Custom Shell - A Simple Linux Shell Implementation in C

## Introduction

This project implements a simple Linux shell using the C programming language. The shell provides basic functionality to navigate the file system, perform echo, pwd and maintain command history.

## Run the shell

1. Clone this repository and `cd` into it.
2. Run the command `make` to compile the program.
3. Execute the shell with `./shell` to get a prompt of the form `username@system_name:path`.
4. To exit the shell, simply type `exit`.

## Features

### Built-in commands

The following commands are implemented as part of the shell:

1. `pwd`
    
    - Displays the current working directory.
    - Implemented in [pwd.c](pwd.c)

2. `cd`
    
    - Changes the current directory to the specified directory.
    - Handles the following cases:
        - `cd` or `cd ~`: Changes to the home directory.
        - `cd ..`: Moves one level up.
        - `cd -`: Returns to the previous directory.
    - Throws an error if the directory does not exist.
    - Implemented in [cd.c](cd.c)

3. `echo`
    
    - Prints the specified arguments to the console.
    - Supports trimming of leading and trailing whitespace and accounts for arguments enclosed in double quotes.
    - Implemented in [echo.c](echo.c)

4. `history`
    
    - Displays the last 10 commands entered in the shell.
    - Implemented in [history.c](history.c)

5. `clear_history`
    
    - Clears the command history both in memory and from the history file.
    - Implemented in [history.c](history.c)

6. `exit`
    
    - Exits the shell gracefully, saving the current command history to a file.
    - Implemented in [main.c](main.c)

## Steps to Compile
1. Open a terminal and navigate to the project directory.
2. Run the following command to compile the code:

   ```bash
   make
3. Once compiled, run the program by executing:

    ```bash
    ./shell
4. To remove the compiled executable, use:

    ```bash
    make clean

## Dependencies

- `gcc` for compiling the C code.
- Standard C libraries.