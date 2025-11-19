# Conceptual Guide on Forking Processes, Threads, and IPC in C

## Overview
In this project, we explore important **concepts** in system programming: **forking processes**, **threads**, and **Inter-Process Communication (IPC)** using C. The video explains these concepts and demonstrates how to use **fork()**, **execvp()**, **waitpid()**, and **pthread_create()** to manage processes and threads, along with the concept of **context switching** and measuring performance differences between threads and processes.

## Features
- **Forking Processes**: Creating new processes with `fork()` and isolating them.
- **IPC with Pipes**: Using pipes (`pipe()`, `dup()`) to facilitate communication between processes.
- **Threading**: Using `pthread_create()` to create threads, which share memory space.
- **Performance Comparison**: Measuring time differences between using processes and threads in task creation using `gettimeofday()`.
- **Context Switch**: Analyzing the performance of context switching when using processes vs. threads.

## Setup

### Prerequisites
- **C compiler**: `gcc` or any POSIX-compliant C compiler.
- **POSIX Threads** library.
- **Linux** or **macOS** is required for pthreads support.

### Installation
1. Clone this repository or download the project files.
2. Navigate to the project directory:
 ```bash
cd <project-directory>
 ```
3. Compile the C code:
 ```bash
gcc -o program main.c -lpthread
 ```
4. Run the program with either data from a CSV file or user input.

### Files

- **`main.c`**: Contains the main program for managing processes and threads, including the logic for creating child processes, executing commands, and measuring performance.
- **`sort_utils.c`**: Implements the sequential merge and parallel merge sort logic.
- **`README.md`**: Documentation about the project.

## Concepts Covered

1. **Forking Processes**:
 - Processes are created using the `fork()` system call, which duplicates the current process.
 - A child process is created and executes a command using `execvp()`. The parent process waits for the child process to finish using `waitpid()`.

 **Diagram**: The parent process creates a child process, and the two cannot communicate directly without an IPC mechanism.

 - **IPC (Inter-Process Communication)**:
   - **Pipes**: Used to allow data flow between processes. The `pipe()` function creates a pipe that connects the `stdout` of the child process to the `stdin` of the parent process.
   - **Duplication (`dup()`)**: Redirects input/output streams to pipes.

2. **Threads**:
 - Threads are created using `pthread_create()` and share the same memory space. Unlike processes, threads do not need an IPC mechanism as they can access shared data directly.
 - Threads are more efficient in terms of performance compared to processes, but they come with the challenge of managing shared memory space.

3. **Performance Comparison**:
 - The project compares the **context switch time** between threads and processes using `gettimeofday()` to measure microseconds.
 - **Fork**: Creates isolated memory spaces, which can cause performance overhead.
 - **Threads**: Share memory and can be more efficient in terms of task creation.

4. **Context Switching**:
 - The video and code compare how a CPU switches between processes and threads. It measures the context switch time and compares the overhead of using threads vs. processes for task creation.

## Example

1. **Fork Example**: A simple shell that asks the user for a command, forks a new process, and executes the command.
2. **Thread Example**: Comparing task creation and memory usage between processes and threads. Threads outperform processes in certain scenarios, particularly when tasks are lightweight and memory sharing is required.

## Results and Analysis
| Scenario        | Source    | Data Size (N) | Expected Acceleration | Main Limiting Factor          |
|-----------------|-----------|---------------|-----------------------|-------------------------------|
| 1               | CSV Large | 1,000,000     | Very High             | I/O Time and Final Merge      |
| 2               | CSV Small | 10,000        | Moderate to High      | Thread Management and Merging |
| 3               | Console   | Small         | None or Deceleration  | Thread Creation Overhead      |

- **Large CSV (1,000,000 entries)**: Very high acceleration due to parallelism.
- **Small CSV (10,000 entries)**: Moderate acceleration, some overhead from thread management.
- **Console input**: Little to no acceleration due to high overhead of thread creation.

## Video
- **Watch the full video**: @#@!$#!@$#!@

---

This README summarizes the concepts explained in the video, installation steps, and details about performance comparison using processes and threads in C.
