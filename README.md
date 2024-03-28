# ELEC4075_Lab7_Scheduling
Create a simulator in C that simulates First-Come-First Serve (FCFC), Shortest Process Next (SPN), and Shortest-
Remaining Time (SRT).
• The simulator will need to accept the following inputs for each process: Process Name, Arrival Time, and
Service Time – you can create input files or have the user input each time.
• The simulator would need to calculate and display the following outputs (in a table) for each process: Process
Name, Arrival Time, Service Time, Start Time, Finish Time, Wait Time, Turnaround Time.
• Similar to the examples we did in the lecture, you can ignore I/O i.e., in non-preemptive algorithms, the
processes run straight through to the end once started, and in preemptive algorithms, only the OS can preempt a process.

Create a visual representation (Gantt chart) in C. For example, SPN for Part 1 will produce the following Gantt Chart:
A A A
     B B B B B B
                   C C C C
                          D D D D D
                E E 