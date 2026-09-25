*This project has been created as part of the 42 curriculum by nildruon.*

# 42 Philosophers

A multithreaded implementation of the classic **Dining Philosophers Problem** in C using POSIX threads and mutexes.

## Description

Philosophers sit at a round table alternating between **eating**, **sleeping**, and **thinking**. There are as many forks on the table as philosophers, and each philosopher needs both their left and right forks to eat.

If a philosopher does not start eating within `time_to_die` milliseconds after their last meal, they starve. The challenge is to manage shared resources (forks) concurrently to prevent data races, starvation, and deadlocks. The simulation stops if a philosopher dies or once all philosophers have eaten a required number of times.

## Instructions

### Compilation

Compile the binary using `make` inside the `philo` directory:

```bash
cd philo && make
```

Available rules: `make`, `make clean`, `make fclean`, `make re`.

### Execution

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Number of philosophers and forks.
- `time_to_die` (ms): Time a philosopher can live without eating.
- `time_to_eat` (ms): Time spent eating (holding two forks).
- `time_to_sleep` (ms): Time spent sleeping.
- `[number_of_times_each_philosopher_must_eat]` (optional): Simulation stops once each philosopher eats this many times.

### Example

```bash
# 5 philosophers surviving indefinitely
./philo 5 800 200 200

# 5 philosophers stopping after eating 7 times each
./philo 5 800 200 200 7
```

## Resources

- **References**:
  - Edsger Dijkstra's *Dining Philosophers Problem* (1965).
  - Linux `man` pages: `pthread_create(3)`, `pthread_mutex_init(3)`, `gettimeofday(2)`, `usleep(3)`.
- **Peer Discussions**: Kian N., Stefan A., and Barbara S.
- **AI Usage**: Used to clarify concurrency concepts, assist in troubleshooting race conditions and edge cases (such as single-philosopher timing), and help structure the project documentation.
Ai was used for understanding of the Philosopher Problem and sometimes find small bugs i had a hard time finding