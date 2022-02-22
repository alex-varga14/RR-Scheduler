# RR-Scheduler
 C++ function implementing a Round Robin CPU Scheduling Simulation
 
 ## Compile with:
 ```
 make
 ```
 
 ## Run with:
 ```
 ./scheduler <quantum #> <max_seq_length> < ./tests/<testfile.txt>
 ```
 
 ## Example with Output:
 ```
 ./scheduler 3 20 < ./tests/test1.txt
 ```
 Where the simulator would run with quantum = 3 and max sequence length = 20
 
 ```
 Reading in lines from stdin...
 Running simulate_rr(q=3,maxs=20,procs=[3])
 Elapsed time  : 0.0000s

 seq = [-1,0,1,0,2,1,0]
 +---------------------------+----------------------+----------------------+----------------------+
 | Id |              Arrival |                Burst |                Start |               Finish |
 +---------------------------+----------------------+----------------------+----------------------+
 |  0 |                    1 |                   10 |                    1 |                   19 |
 |  1 |                    3 |                    5 |                    4 |                   15 |
 |  2 |                    5 |                    3 |                   10 |                   13 |
 +---------------------------+----------------------+----------------------+----------------------+
 ```
 