//Library "intal" - Integer of arbitray length
//intal is a nonnegative integer of arbitrary length.
//The way the integer is stored is specific to the 
//implementation as long as the interface (this header file) is intact.

//DO NOT modify this header file.
//As usual, an implementation file implements all the functionalities decalred here
//and a client file uses the functionalities declared here.

//String (array of chars with a null termination) of decimal digits converted to intal type.
//Input str has most significant digit at the head of the string.
//"void *" abstracts out the format of intal.
//The returned pointer points to the intal "object". Client need not know the format of the intal.
//Even if you happen to use "char*" as the format of the intal, just like the input string, 
//it's expected to a create a new copy because the intal object should be modifiable, but 
//the input could be a constant literal (that's why parameter is "const").
//The intal created here obviosuly needs some memory allocation, which would be freed in intal_destroy().
//The memory allocated by this function is pointed by the pointer it returns. The client has no idea
//what kind of object it is. It could be a pointer to char array, int array, long int array, double array, or
//a struct array. There is no theoretical limit to the size of the integer, but memory limitations of the 
//process (Operating System). If the OS allows, your library should be able to hold the largest prime number
//known, which is 23,249,425 digits long (as of Feb 2018).

//returns "null" if str is not representing a valid nonnegative integer. A "null" pointer
//represents a NaN (not a number).
void* intal_create(const char* str);

//Destroy the created "object".
//It mainly frees the memory allocated by intal_create().
void intal_destroy(void* intal);

//Converts intal to a string of decimal digits for mostly display purpose.
//Returned string has most significant non-zero digit at the head of the string.
char* intal2str(void* intal);

//Increments the integer by one and returns the incremented intal.
//In most cases, it'll return the same object. But in some cases, it may create a
//new object to accommodate the incremented value. In that case, this function
//destroys the older intal and returns the new one.
void* intal_increment(void* intal);

//Decrements the integer by one and returns the decremented intal.
//No change if the intal is zero because it is nonnegative integer.
//In most cases, it'll return the same object. But in some cases, it may create a
//new object to accommodate the decremented value. In that case, this function
//destroys the older intal and returns the new one.
void* intal_decrement(void* intal);

//Adds two intals and returns their sum.
void* intal_add(void* intal1, void* intal2);

//Returns the difference (obviously, nonnegative) of two intals.
void* intal_diff(void* intal1, void* intal2);

//Multiplies two intals and returns the product.
//void* intal_multiply(void* intal1, void* intal2);

//Integer division
//Returns the integer part of the quotient of intal1/intal2.
//Returns "null" if intal2 is zero. A "null" pointer represents a NaN (not a number).
void* intal_divide(void* intal1, void* intal2);

//Returns -1, 0, +1
//Returns 0 when both are equal.
//Returns +1 when intal1 is greater, and -1 when intal2 is greater.
int intal_compare(void* intal1, void* intal2);

//Returns intal1^intal2.
//It could be a really long integer for higher values of intal2.
//0^n = 0. where n is any intal.
void* intal_pow(void* intal1, void* intal2); 
