# Dining Philosophers Problem

![Local GIF](dining.gif)

## Introduction
Welcome to the Dining Philosophers Problem implementation! This project tackles a classic concurrency problem in computer science where a number of philosophers sit at a table and engage in thinking and eating. The challenge is to prevent deadlock and starvation while ensuring that each philosopher can eat without causing conflicts with their neighbors.

## Description
The Dining Philosophers Problem is a well-known problem in computer science and concurrent programming. In this scenario, there are a finite number of philosophers sitting at a table with bowls of spaghetti and forks between them. Philosophers alternate between thinking and eating. However, they need forks to eat, and each philosopher needs two forks to eat effectively. The challenge arises when multiple philosophers attempt to pick up forks simultaneously, potentially leading to deadlock or starvation.

## Objective
The main objective of the Philosopher Dining Problem project is to implement a `multi-threaded` application where each thread represents a philosopher seated around a circular table. Each philosopher alternates between periods of eating and thinking. However, they require both forks adjacent to them to eat, leading to potential `deadlock` situations if not managed properly.

## Features
- **Concurrency Management**: The project utilizes threads to represent philosophers and mutex locks to manage access to shared resources (forks).
- **Deadlock Prevention**: A solution is implemented to ensure that no philosopher can deadlock by waiting indefinitely for a fork to become available.
- **Starvation Avoidance**: Techniques are employed to prevent any philosopher from being starved of resources (forks) indefinitely.

## Definitions

### Threads

A **thread** is the smallest unit of a process that can be scheduled and executed by the operating system. Each thread in a process shares the same data space, code, and resources, but operates independently. This allows multiple tasks to be performed simultaneously within the same application.

### Multi-threading

**Multi-threading** is the ability of a CPU, or a single core in a multi-core processor, to provide multiple threads of execution concurrently. This is useful in applications that perform many independent tasks that can run simultaneously. Multi-threading can improve the performance of applications by making better use of system resources.

### Deadlocks

A **deadlock** is a situation in multi-threading where two or more threads are unable to proceed because each is waiting for the other to release a resource. This results in the program becoming unresponsive and unable to continue executing. Deadlocks usually occur due to poor resource management and can be avoided by careful programming and resource allocation.

### Mutexes

A **mutex** (short for mutual exclusion) is a synchronization primitive used to prevent multiple threads from simultaneously accessing shared resources. When a thread locks a mutex, other threads attempting to lock it will be blocked until the mutex is unlocked. This ensures that only one thread can access the critical section of code at a time, preventing race conditions and ensuring data integrity.

### Race Conditions
A race condition occurs when two or more threads access shared data and try to change it at the same time. Because the thread scheduling algorithm can swap between threads at any time, you don't know the order in which the threads will attempt to access the shared data. This can lead to unexpected results and bugs. Proper synchronization mechanisms, like mutexes, are used to avoid race conditions.
---


### USAGE
   ```bash
   git clone git@github.com:oumaima-aarabe/philosophers.git
   make
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
