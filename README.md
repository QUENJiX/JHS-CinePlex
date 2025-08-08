# JHS-CinePlex Movie Ticketing System

![Language](https://img.shields.io/badge/language-C-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

A simple, command-line interface (CLI) application built in C for managing a small cinema's movie listings and ticket sales. This project demonstrates core C programming concepts, file I/O, and basic application architecture.

## Table of Contents
*   [Features](#-features)
*   [Architecture Overview](#-architecture-overview)
*   [Getting Started](#-getting-started)
    *   [Prerequisites](#prerequisites)
    *   [Compilation](#compilation)
    *   [Running the Application](#running-the-application)
*   [Data Persistence](#-data-persistence)
*   [Roadmap & Future Improvements](#-roadmap--future-improvements)
*   [Contributing](#-contributing)
*   [License](#-license)

## Features

The application supports two distinct user roles with different functionalities.

### **Admin Features**
-   Secure login with hardcoded credentials.
-   **Add New Movies**: Add new films to the catalog with titles, genres, showtimes, prices, and available seats.
-   **Edit Existing Movies**: Update the price and available seat count for any movie.
-   **Remove Movies**: Delete a movie listing from the catalog.
-   **View All Movies**: See a complete list of all available movies and their details.
-   **View All Purchases**: Review a comprehensive history of every ticket purchase made by all users.

### **Customer Features**
-   **User Registration & Login**: Customers can create their own accounts and log in.
-   **View Available Movies**: Browse the current list of movies, including showtimes, pricing, and seat availability.
-   **Purchase Tickets**: A step-by-step process to select a movie and buy one or more tickets.
-   **View Personal Purchase History**: Customers can view a history of their own past ticket purchases and the total amount spent.

## Architecture Overview

This project is implemented as a **monolithic application** within a single `main.c` file. It relies on a set of **global arrays** to manage the application's state (movies, users, tickets) during runtime.

**Data persistence** is achieved through simple text files (`.txt`), allowing the application's state to be saved upon exit and reloaded at the next launch.

## Getting Started

Follow these instructions to get a copy of the project up and running on your local machine.

### Prerequisites

You will need a C compiler installed on your system. The most common is `gcc`.

-   **GCC (GNU Compiler Collection)**: Can be installed on Linux via a package manager (e.g., `sudo apt-get install build-essential`), on macOS via Xcode Command Line Tools, or on Windows via MinGW/Cygwin.

### Compilation

1.  Clone the repository or save the `main.c` file to your local machine.
2.  Open a terminal or command prompt in the directory where you saved the file.
3.  Compile the project using the following command. The `-Wall` and `-Wextra` flags are recommended to enable all compiler warnings.

    ```bash
    gcc -o jhs_cineplex main.c -Wall -Wextra -std=c99
    ```

    This will create an executable file named `jhs_cineplex` (or `jhs_cineplex.exe` on Windows).

### Running the Application

Execute the compiled program from your terminal:

```bash
./jhs_cineplex
```

The application will launch, and you can interact with it through the on-screen menus.

## Data Persistence

The application creates and uses the following files in the same directory as the executable to store data:

-   `movie_list.txt`: Stores the movie catalog. If this file doesn't exist on first run, it will be created with a default set of movies.
-   `users.txt`: Stores user registration details (username and password).
-   `tickets.txt`: Stores a log of all ticket purchase transactions.

> **Security Warning**: User credentials are currently stored in **plaintext**. This is highly insecure and intended for educational purposes only. Do not use this authentication system in a production environment.

## License

This project is distributed under the MIT License. See the `LICENSE` file for more information.

