*This project has been created as part of the 42 curriculum by flhensel.*

# Philosophers

## Description

Philosophers is a simulation of the classic **Dining Philosophers Problem**, a concurrency exercise originally formulated by Edsger Dijkstra. The goal is to coordinate several philosophers who share a table, alternating between eating, sleeping, and thinking, without ever falling into a deadlock or starving.

The setup: philosophers sit around a circular table with one fork placed between each neighbouring pair. A philosopher needs **both** adjacent forks to eat. After eating, they put both forks down, sleep, then think, and the cycle repeats. If a philosopher goes too long without eating, they die — and the simulation ends.

The challenge of the project is managing shared resources (the forks) across many concurrent threads while avoiding the three classic concurrency pitfalls:

- **Deadlock** — every philosopher grabbing one fork and waiting forever for the second.
- **Race conditions** — multiple threads reading and writing the same data without synchronisation.
- **Starvation** — a philosopher being denied access to forks for too long.

In this implementation, **each philosopher is a thread** and **each fork is a mutex**. A dedicated monitor thread watches every philosopher and ends the simulation the instant one starves or, optionally, once every philosopher has eaten a required number of times.

## Instructions

### Requirements

- A C compiler (`cc` / `gcc`)
- `make`
- The POSIX threads library (`pthread`), available by default on Linux and macOS

### Compilation

From the root of the repository:

```bash
make
```

This produces an executable named `philo`. Other available rules:

```bash
make clean    # remove object files
make fclean   # remove object files and the executable
make re       # rebuild from scratch
```

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning |
|----------|---------|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` | Time in milliseconds a philosopher can go without eating before dying |
| `time_to_eat` | Time in milliseconds it takes a philosopher to eat |
| `time_to_sleep` | Time in milliseconds a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(optional)* Once every philosopher has eaten this many times, the simulation stops. If omitted, it runs until a philosopher dies. |

All times are expressed in **milliseconds**.

### Output

Each status change is logged on its own line in the format:

```
timestamp_in_ms philosopher_id status
```

For example:

```
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 3 is thinking
...
807 4 died
```

### Examples

```bash
./philo 1 800 200 200       # single philosopher: takes one fork and dies (~800ms)
./philo 5 800 200 200       # runs indefinitely, nobody should die
./philo 5 800 200 200 7     # stops once every philosopher has eaten 7 times
./philo 4 410 200 200       # tight timing, nobody should die
```

## Technical Choices

- **Threads and mutexes** — one thread per philosopher, one mutex per fork. Acquiring a fork's mutex represents picking up that fork.
- **Deadlock avoidance** — philosophers pick up their forks in different orders based on the parity of their id (even ids take the left fork first, odd ids take the right fork first). This breaks the circular-wait condition. Even-id philosophers also wait briefly before starting, desynchronising fork access and reducing contention.
- **A dedicated monitor thread** sweeps all philosophers every 0.5 ms, checking whether any has exceeded `time_to_die` since their last meal, or whether all philosophers have eaten enough.
- **Per-philosopher data locks** — each philosopher has its own mutex guarding its `last_meal` timestamp and meal count, so philosophers updating their own data never block one another; the monitor only briefly contends with the single philosopher it is checking.
- **Precise custom sleep** — instead of one long `usleep`, a polling sleep checks the elapsed time in small steps. This keeps timing tight (oversleeping a single `usleep` could make a death report arrive late) and lets threads exit early when the simulation ends.
- **Synchronised output** — a single print mutex ensures status lines never interleave, and the death state is checked while that lock is held so no message can slip in after a philosopher has died.

## Resources

Classic references on the Dining Philosophers Problem and POSIX threads:

- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- `man pthread_create`, `man pthread_mutex_init`, `man pthread_mutex_lock`, `man pthread_join` — POSIX threads manual pages
- `man gettimeofday`, `man usleep` — timing functions

### Use of AI

AI was used in this project for:

    Understanding the Topic:
        Understanding mutexes, data races, and thread synchronisation
        Researching deadlock conditions and prevention strategies
        Understanding the dining philosophers problem and its edge cases

    Code Organization:
        Adding comments to explain non-obvious design decisions
        Restructuring comments to comply with 42 Norm requirements

    Testing & Validation:
        Creating test commands to verify death timing accuracy
        Verifying no fork stealing occurs across concurrent eating pairs

All code was written and verified for correctness and understanding by me. AI was used as a learning tool and for explanation of concurrency concepts
