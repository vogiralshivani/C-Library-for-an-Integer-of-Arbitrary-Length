# C-Library-for-an-Integer-of-Arbitrary-Length
Library "intal", short for integer of arbitray length, a library of nonnegative integers of 
arbitrary length. The given header file "intal.h" declares the functionalities the library is 
expected to provide except that there is no definition of the "intal" itself

Client sees an intal as a "void*". It could be a pointer to char array, int array, long int array, 
double array, or a struct array. There is no theoretical limit to the size of the integer, but memory 
limitations of the process (Operating System). If the OS allows, your library should be able to hold the 
largest prime number known, which is 23,249,425 digits long (as of Feb 2018).

