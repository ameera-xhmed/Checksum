#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif

//VARIABLES
unsigned int d{}; //last checksum digit calculated (will be added to end of n as the ninth digit)
unsigned int returnedvalue{}; //returned checksum
unsigned int addingsums{}; 
unsigned int verifychecksum{};
unsigned int storedn{};

//ARRAYS
unsigned int checksum[8]; //break n into 8 seperate digits and store in this array
unsigned int multipliedchecksum[8]; //new array for when digits are multipled by 2
unsigned int addedchecksum[8]; //new array for when values in multipliedchecksum array are larger than 9
unsigned int finalchecksum[9]; //final array with returned checksum digits seperated

//FUNCTION DECLERATIONS
unsigned int add_checksum(unsigned int n); 
bool verify_checksum(unsigned int n);
unsigned int remove_checksum(unsigned int n);

//FUNCTION DEFINITIONS

//takes 9 digit #, if checksum is wrong or more than 9 #s return max unsigned int
//otherwise just return 8 digit number without checksum digit (d)
unsigned int remove_checksum(unsigned int n){ 
    if(n > 999999999) {//more than 9 digits
        returnedvalue = UINT_MAX;
    }
    verifychecksum = n % 10;
    n = n / 10; 
    storedn = n;

    for(int i = 0; i < 8; i++){
        checksum[i] = n % 10;
        n = n / 10;
        if(i % 2 == 0) { //multiply every other digit by 2
            multipliedchecksum[i] = checksum[i] * 2;
        }
        else{
            multipliedchecksum[i] = checksum[i];
        }

        if(multipliedchecksum[i] > 9) { 
            addingsums = multipliedchecksum[i] % 10;
            unsigned int sum = 1 + addingsums; //1 is always the first digit because 10 <= x <= 19
            addedchecksum[i] = sum;
        }
        else{
            addedchecksum[i] = multipliedchecksum[i];
        }
    }

    for(int k = 7; k >=0; k--){ //step 2 and 3 
        d = d + addedchecksum[k];

        if(k == 0) {
            d = d * 9;
            d = d % 10;
        }	
    }
    
    std::cout << "value should be is " << d << " value is " << verifychecksum << std::endl;
    if(d == verifychecksum)
        returnedvalue =  storedn;
        else{
            returnedvalue = UINT_MAX;
        }
    return returnedvalue;
}

#ifndef MARMOSET_TESTING
int main() {
    	unsigned int value_to_protect{}; //input n
	std::cout << "input n: ";
	std::cin >> value_to_protect;
	unsigned int protected_value = remove_checksum(value_to_protect); //calls function using n
	std::cout << "The value is " << protected_value << "." << std::endl;
	
    std::cout << std::endl;
    
    return 0;
}
#endif