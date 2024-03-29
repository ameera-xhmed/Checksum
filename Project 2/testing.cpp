#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif

//VARIABLES
unsigned int d{}; //9th digit of checksum value
unsigned int returnedvalue{}; //checksum value that function returns
unsigned int addingsums{}; //variable to save values when caluclating checksum
unsigned int verifychecksum{}; //variable to save values when caluclating checksum
unsigned int storedn{};//variable to save values when caluclating checksum
int counter{}; //counter for how many elements are in inputted array for void add_checksum and void remove_checksum
unsigned int arraychecksum{}; //variable to save values when caluclating checksum

//ARRAYS
unsigned int checksum[8]; //break n into 8 seperate digits and store in this array
unsigned int multipliedchecksum[8]; //new array for when digits are multipled by 2
unsigned int addedchecksum[8]; //new array for when values in multipliedchecksum array are larger than 9
unsigned int finalchecksum[9]; //final array with returned checksum digits seperated

//FUNCTION DECLERATIONS
unsigned int add_checksum(unsigned int n); 
bool verify_checksum(unsigned int n);
unsigned int remove_checksum(unsigned int n);

void add_checksum( unsigned int array[], std::size_t capacity );
void remove_checksum( unsigned int array[], std::size_t capacity );

//FUNCTION DEFINITIONS
//FUNCTION 1
//takes one 8 digit value and calculates checksum value. Returns a 9 digit number or maximum unsigned integer
unsigned int add_checksum(unsigned int n) { 
    if(n > 99999999){ //if n is larger than 8 digits return max unsigned integer
        returnedvalue = UINT_MAX;
    }
    else {
        for(int i = 0; i < 8 ; i++){ //splitting n into 8 seperate digits and storing in an array
            checksum[i] = n % 10;
            n = n / 10;

            if(i % 2 == 0) { //multiply every other digit by 2
                multipliedchecksum[i] = checksum[i] * 2;
            }
            else{
                multipliedchecksum[i] = checksum[i];
            }

            if(multipliedchecksum[i] > 9) {  //adding digits of numbers greater than 9 and replacing new sum in array
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

        finalchecksum[0] = checksum[7]; //rewriting new outputted array
        finalchecksum[1] = checksum[6];
        finalchecksum[2] = checksum[5];
        finalchecksum[3] = checksum[4];
        finalchecksum[4] = checksum[3];
        finalchecksum[5] = checksum[2];
        finalchecksum[6] = checksum[1];
        finalchecksum[7] = checksum[0];
        finalchecksum[8] = d;

        for(int m = 0; m < 9; m++) //connecting all elements of array together are 1 value 
            returnedvalue = returnedvalue*10 + finalchecksum[m];
    }
	return returnedvalue;
}

//FUNCTION 2
//takes a 9 digit value. Checks if 9th digit is correct for checksum value. 
//returns true or false values. returns true if 8 digits without the checksum digit (9th digit) are correct
//returns false if 9th digit is incorrect or there are more than 9 digits in the inputted value
bool verify_checksum(unsigned int n) {
    d = 0;
    if (n < 999999999){//check if there are 9 digits
        //check if d is right
        verifychecksum = n % 10; 
        n = n / 10; 

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
        //std::cout << "value should be is " << d << " value is " << verifychecksum << std::endl;
        if(d == verifychecksum)
            return 1;
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

//FUNCTION 3
//takes a 9 digit value. if number is more than 9 digits or 9th digit is incorrect return max unsigned integer
// if number is 9 digits and 9th digit is correct checksum digit returns 8 digits without the 9th
unsigned int remove_checksum(unsigned int n){ 
    d = 0;
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
        
    //std::cout << "value should be is " << d << " value is " << verifychecksum << std::endl;
    if(d == verifychecksum)
        returnedvalue =  storedn;
    else{
        returnedvalue = UINT_MAX;
    }
    
    return returnedvalue;
}

//FUNCTION 4
//takes an array of 8 digit values, calculates check sum for each element of the array
//returns array, each element of array returned is 9 digits with the corret checksum value calculated
void add_checksum( unsigned int array[], std::size_t capacity ){
	for(int i = 0; i < capacity; i++){ 
        unsigned int placeholder = array[i];
        d = 0;
        arraychecksum = array[i];
        returnedvalue = 0;

        for(int i = 0; i < 8 ; i++){ //splitting n into 8 seperate digits
            checksum[i] = arraychecksum % 10;
            arraychecksum = arraychecksum / 10;

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

            finalchecksum[0] = checksum[7]; //rewriting final array to return
            finalchecksum[1] = checksum[6];
            finalchecksum[2] = checksum[5];
            finalchecksum[3] = checksum[4];
            finalchecksum[4] = checksum[3];
            finalchecksum[5] = checksum[2];
            finalchecksum[6] = checksum[1];
            finalchecksum[7] = checksum[0];
            finalchecksum[8] = d;
            
        for(int m = 0; m < 9; m++){
            returnedvalue = returnedvalue*10 + finalchecksum[m]; //merge elements of array to one value to return
        }
                
        if(placeholder> 99999999){
            returnedvalue = UINT_MAX; 
        }
        array[i] = returnedvalue;
    }
}

//FUNCTION 5
//takes array with 9 digit elements. checks if elements of array are 9 digits and have correct checksum
//returns array of 8 digit elements minus the checksum value or returns max unsigned value if checksum is wrong or elements of array are more than 9 digits
void remove_checksum( unsigned int array[], std::size_t capacity ){
	for(int i = 0; i < capacity; i++){
		storedn = 0;
		if(array[i] > 999999999) {//more than 9 digits
			array[i] = UINT_MAX;
            break;
		}
		d = 0;
        arraychecksum = array[i];
        returnedvalue = 0;

		verifychecksum = arraychecksum % 10;
		arraychecksum = arraychecksum / 10; 
		storedn = arraychecksum;

		for(int i = 0; i < 8; i++){
			checksum[i] = arraychecksum % 10;
			arraychecksum = arraychecksum / 10;

			if(i % 2 == 0) { //multiply every other digit by 2
				multipliedchecksum[i] = checksum[i] * 2;
			}
			else{
				multipliedchecksum[i] = checksum[i];
			}

			if(multipliedchecksum[i] > 9) { //add digits together of number greater than 9
				addingsums = multipliedchecksum[i] % 10;
				unsigned int sum = 1 + addingsums; //1 is always the first digit because 10 <= x <= 19
				addedchecksum[i] = sum; //replace old digit with new sum
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
		
		if(d == verifychecksum)
			returnedvalue =  storedn;
		else{
			returnedvalue = UINT_MAX;
		}
	    array[i] = returnedvalue;
	}
}

#ifndef MARMOSET_TESTING
int main() {
    /*//TESTING FUNCTION 1
    unsigned int value_to_protect{}; //input n
	std::cout << "input n for function 1: ";
	std::cin >> value_to_protect;
	unsigned int protected_value = add_checksum(value_to_protect); //calls function using n
	std::cout << "The value " << value_to_protect << " with the checksum added is " << protected_value << "." << std::endl;
	std::cout << std::endl;

    //TESTING FUNCTION 2
    unsigned int verify{};
    std::cout << "input n for function 2: ";
    std::cin >> verify;

	if (verify_checksum(verify)){
		std::cout << "The checksum is valid." << std::endl;
	}
	else{
		std::cout << "The checksum is invalid." << std::endl;
	} 
    std::cout << std::endl;

    //TESTING FUNCTION 3
    unsigned int value_toprotect{}; //input n
	std::cout << "input n for function 3: ";
	std::cin >> value_toprotect;
	unsigned int protectedvalue = remove_checksum(value_toprotect); //calls function using n
	std::cout << "The value is " << protectedvalue << "." << std::endl;
    std::cout << std::endl;*/
 
    //TESTING FUNCTION 4
    const std::size_t counter {3};
	unsigned int value_series[counter] {123456789, 12345678, 567}; //20201122 7 20209913 1 20224012 3 
	
	add_checksum(value_series, counter);
	
	std::cout << "Series with checksums added for function 4 are: ";

	for (std::size_t series_index {0};
		series_index < counter; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}
    std::cout << std::endl;

   /* //TESTING FUNCTION 5
    const std::size_t QTY_VALUES {4};
	unsigned int valueseries[QTY_VALUES] {202011227, 202099131, 202240123, 123456788};
	
	remove_checksum(valueseries, QTY_VALUES);
	
	std::cout << "The values for function 5 are: ";
	for (std::size_t series_index {0};
		series_index < QTY_VALUES; series_index++)
	{
		std::cout << valueseries[series_index] << " ";
	}*/
    std::cout << std::endl;
    return 0;
}
#endif