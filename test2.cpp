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

//ARRAYS
unsigned int checksum[8]; //break n into 8 seperate digits and store in this array
unsigned int multipliedchecksum[8]; //new array for when digits are multipled by 2
unsigned int addedchecksum[8]; //new array for when values in multipliedchecksum array are larger than 9
unsigned int finalchecksum[9]; //final array with returned checksum digits seperated

//FUNCTION DECLERATIONS
unsigned int add_checksum(unsigned int n); 
bool verify_checksum(unsigned int n);

//FUNCTION DEFINITIONS
unsigned int add_checksum(unsigned int n) { 
    if(n > 99999999){
        returnedvalue = UINT_MAX;
    }
    else {
        for(int i = 0; i < 8 ; i++){ //splitting n into 8 seperate digits
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
        finalchecksum[0] = checksum[7];
        finalchecksum[1] = checksum[6];
        finalchecksum[2] = checksum[5];
        finalchecksum[3] = checksum[4];
        finalchecksum[4] = checksum[3];
        finalchecksum[5] = checksum[2];
        finalchecksum[6] = checksum[1];
        finalchecksum[7] = checksum[0];
        finalchecksum[8] = d;

        for(int m = 0; m < 9; m++)
            returnedvalue = returnedvalue*10 + finalchecksum[m];
    }
	return returnedvalue;
}

bool verify_checksum(unsigned int n) {
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
        std::cout << "value should be is " << d << " value is " << verifychecksum << std::endl;
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

#ifndef MARMOSET_TESTING
int main() {
    unsigned int verify{};
    std::cout << "input n: ";
    std::cin >> verify;

	if (verify_checksum(verify)){
		std::cout << "The checksum is valid." << std::endl;
	}
	else{
		std::cout << "The checksum is invalid." << std::endl;
	} 
    // std::cout << std::endl; 
    //20201122, 20209913, 20224012
    //202011227 235247550 2283134081 
    return 0;
}
#endif