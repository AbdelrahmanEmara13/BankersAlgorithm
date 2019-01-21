
As you have studied in the lecture, you need to implement the request
algorithm to allow a process to ask for a new resource to be allocated.
Then you will have to implement the safety algorithm to check if it is
a safe state or not. If it is a safe state then you will allocate the
resource. If not then you will output that the request would cause an
unsafe state. You will have to output the sequence of allocation that
leads to complete unsafe state. If the allocation is not possible as
unsafe sate is inevitable then you will output (allocation is impossible).
Use the examples in the lecture and sheet to test your code. You need
the maximum, needed, and allocated data structures in your code.
The code will get as an input the maximum, needed and available
system resources then it will proceed in the allocating the resources
avoiding the creation of unsafe state.

This code is an implementation of bankers algorithm. It takes the allocation, max, and available values as input.  check if system is in a safe state or not. if yes, it output the sequence of allocation that leads to complete safe state. otherwise, output the system is in an unsafe state.then, it takes the resourse for a process and chech if it can be allocated.
