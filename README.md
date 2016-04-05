# OperatingSystems
C language implementations of system mechanisms used from user level


cw01 - Memory management , libraries and time measurement:

1) List implementation with basic functionalities as an addres book.

2) Using implemented list as a ready library - 3 different solutions : static , dynamic , shared.


cw02 - IO operations

1) Implementing insertion sort on files to compare library and system functions efficiency.

2) Directory structure operations. Walking through the file tree ( comparison of 2 methods).

3) File locking ( read/ write , mandatory/advisory).


cw03 - Process operations

1) Creating and testing behavior of processes ( fork / vfork / clone with different arguments).

2) Creating some kind of child processes tree ( while file tree walk ).


cw04 - Signals

1) Printer reacting on ctrl-Z signals to change it's behaviour ( forward, backward, with repetitions to max number ) and ctrl-C to stop.

2) Sending signals ( SIGUSR1 and SIGUSR2 ) from one program to another and counting them, also resending back. Implemented in three ways : naive ( loosing part of signals), with confirmation after receiving a signal and using real time signals.

