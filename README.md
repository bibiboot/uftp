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

