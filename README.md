# Dining Philosophers Problem

## Introduction
Welcome to the Dining Philosophers Problem implementation! This project tackles a classic concurrency problem in computer science where a number of philosophers sit at a table and engage in thinking and eating. The challenge is to prevent deadlock and starvation while ensuring that each philosopher can eat without causing conflicts with their neighbors.

## Description
The Dining Philosophers Problem is a well-known problem in computer science and concurrent programming. In this scenario, there are a finite number of philosophers sitting at a table with bowls of spaghetti and forks between them. Philosophers alternate between thinking and eating. However, they need forks to eat, and each philosopher needs two forks to eat effectively. The challenge arises when multiple philosophers attempt to pick up forks simultaneously, potentially leading to deadlock or starvation.

## Features
- **Concurrency Management**: The project utilizes threads to represent philosophers and mutex locks to manage access to shared resources (forks).
- **Deadlock Prevention**: A solution is implemented to ensure that no philosopher can deadlock by waiting indefinitely for a fork to become available.
- **Starvation Avoidance**: Techniques are employed to prevent any philosopher from being starved of resources (forks) indefinitely.



### USAGE
   ```bash
   git clone https://github.com/your_username/dining-philosophers.git
   make
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
