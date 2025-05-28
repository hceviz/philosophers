🧠 Philosophers

Philosophers is a project from the 42 curriculum that simulates the classic Dining Philosophers Problem using POSIX threads and mutexes. It explores the challenges of concurrent programming, especially avoiding deadlocks, race conditions, and starvation in a multi-threaded environment.


📌 Project Description

Five (or more) philosophers sit around a table. Each philosopher:
	•	Thinks 🧠
	•	Eats 🍝 (with two forks — one on each side)
	•	Sleeps 😴

Philosophers must take two forks to eat, but only one fork is between each pair. The simulation must avoid deadlocks (e.g., when all philosophers hold one fork and wait forever) and ensure all philosophers eat without starving.

🔧 Compilation

⚠️Ensure you have a POSIX-compliant system (Linux/macOS) and run:

```bash
make
```
This compiles the program and creates an executable named philo.
🚀 Usage

```bash
./philo number_of_philos time_to_die 	time_to_eat time_to_sleep[number_of_times_each_philo_must_eat]
```
Example
```bash
./philo 5 800 200 200
```
Simulates 5 philosophers who die if they don’t eat in 800ms, eat in 200ms, and sleep for 200ms.

🖨 Output Format

Each philosopher’s action is logged to the console in the following format:

	[timestamp] [philosopher_id] action
Example:

	0 2 has taken a fork
	0 2 has taken a fork
	0 2 is eating
	0 4 has taken a fork
	0 4 has taken a fork
	0 4 is eating
	150 4 is sleeping
	150 3 has taken a fork
	150 3 has taken a fork
	150 1 has taken a fork
	150 1 has taken a fork
	150 1 is eating
	150 2 is sleeping
	150 3 is eating
	201 2 died

