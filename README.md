uftp
====

USC558L => Lab5 FTP

Contributors
===========
Ramitha

Love

Danish

Project
=======
http://www.isi.edu/~youngcho/csci558l-f14/lab5-f14.pdf

Due
====
Report : September 13

Demo   : September 15

Summary
======
This project will build on the last assignment. In it you will explore
the real-world implications
of how TCP performs under less than perfect conditions. Your goal is to
develop a file transfer
program that uses your custom protocol that performs better than any
other program available.
This is your first competitive laboratory that will go head to head
against one other randomly
selected team’s result. We suggest doing the following experiments using
the Ubuntu operating
system.

While TCP is effective, reliable, and relatively robust on the Internet,
it doesn't always give us
the best throughput under every circumstance. In this section you'll
design an IP based file-
transfer utility. The design and implementation of the utility is up to
your group, however it must
full-fill only three requirements: it must use IP (so it can be routed),
it must transfer the file
reliably (with no errors) and it must be implemented with a command-line
interface similar to
scp.

The link speed between the sender and receiver must be 100Mbps and the
test file size must be at
least 1GBytes. You should emulate the delay and the loss rate of the
link using the delay node.
You should test your system under various different conditions. However
two settings that you
must expose your system for the assignment are:

* The Delay (RTT) of 10ms with the Loss rate of 1%
* The Delay (RTT) of 200ms with the Loss rate of 20%

For your demo and competition, you will need to create an experiment
with two nodes connected
by the second link (delay of 200ms and the loss rate of 20%) in both
direction defined in your .ns
file.

You will also need to create a 1GB file in your local /tmp directory of
the sender computer.
Your program will need to reliably transfer the entire file from the
sender to the receiver then
back to the sender at the highest performance possible; all through this
bad network link.

You must also create a script that will timestamp right before the
execution of the program and
timestamp at the end of the successful transference of the file. The
total time for the file to make
the round trip will be used to compare your program’s performance
against other team’s program
performance. You also will need to prove the reliability of your system
by running MD5 on both
the original file and the received file.

The execution of the system should be straight forward and any notion of
cheating will result in
automatic defeat in the competition and possibly zero on the lab score.
The goal of this task is to
encourage a healthy competitive development environment for everyone.
You are encouraged to
help each other to get the best result. However, at the end, the faster
team will win.


Daily activities
================

* As a part of the assignment, each group must post the progress and
the result of your system
on the Laboratory 5 Results and Discussion forum EVERY SINGLE DAY.
* The minimum transfer rate for your final FTP is 20 Mbps to compete
against the other team.
* Describe, in detail, the concept(s) behind your file transfer
utility, results, and the analysis in
the document that must be submitted on September 13 th by 11:55pm. You
also must
demonstrate your system to your T.A. during his office hour on Sept
15th.
* The scoring will be based on the submitted document and T.A.s
verification of the system.
