Contribution-
Github Repo-Sanchay117/OS-Simple-Multithreader: Assignment 5 Of Operating Systems Course
Features
Parallel Loop Execution
Single-dimensional loop parallelization using parallel_for.
Two-dimensional loop parallelization using parallel_for.
Lightweight Design
No task/thread pool is used; threads are created and destroyed dynamically with each API call.
Execution Time Measurement
The runtime of each parallel execution is measured and displayed.
Error Checking
Comprehensive checks are implemented for robust and predictable behavior.
Methods
Single-Dimensional Parallel For Loop
Parameters:
low: Starting index of the loop.
high: Ending index of the loop.
lambda: Lambda function containing the loop logic.
numThreads: Number of threads to spawn.
Behavior:
Spawns numThreads threads to execute the lambda logic across the range [low, high).


Two-Dimensional Parallel For Loop
Parameters:
low1, high1: Range for the outer loop.
low2, high2: Range for the inner loop.
lambda: Lambda function containing nested loop logic.
numThreads: Number of threads to spawn.
         Behavior:
         Splits the outer loop across threads, while the inner loop is processed
         sequentially for each range of the outer loop.
                    


