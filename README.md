# Banker's Algorithm (C)

Deadlock avoidance with the Banker's algorithm: the safety check plus resource
requests that are granted only if the system stays in a safe state.

## Build and run

```sh
make
./bankers
```

## Output

```
Banker's algorithm: 5 processes, resources A B C

       Alloc     Max      Need
       A B C    A B C    A B C
  P0   0 1 0    7 5 3    7 4 3
  P1   2 0 0    3 2 2    1 2 2
  P2   3 0 2    9 0 2    6 0 0
  P3   2 1 1    2 2 2    0 1 1
  P4   0 0 2    4 3 3    4 3 1
  Available: 3 3 2

Safety check:
  P1 can finish -> work = (5 3 2)
  P3 can finish -> work = (7 4 3)
  P4 can finish -> work = (7 4 5)
  P0 can finish -> work = (7 5 5)
  P2 can finish -> work = (10 5 7)
  SAFE. Sequence: P1 -> P3 -> P4 -> P0 -> P2

Request P1 (1 0 2): GRANTED, system stays safe
  P1 can finish -> work = (5 3 2)
  P3 can finish -> work = (7 4 3)
  P4 can finish -> work = (7 4 5)
  P0 can finish -> work = (7 5 5)
  P2 can finish -> work = (10 5 7)
  SAFE. Sequence: P1 -> P3 -> P4 -> P0 -> P2

Request P4 (3 3 0): WAIT, not enough available

Request P0 (0 2 0): DENIED, would lead to an unsafe state (rolled back)
```

## How a request is decided

1. Reject it if it is more than the process's remaining need.
2. Wait if there aren't enough resources available right now.
3. Otherwise pretend to grant it and run the safety check. If no safe sequence exists, roll back and deny.

## About

Written by Ahsan (Code Projects on YouTube).
I build and debug operating-systems, graphics and desktop projects. Issues and pull requests are welcome.

Licensed under the MIT License.
