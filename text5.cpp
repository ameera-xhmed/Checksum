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
int counter{};
unsigned int arraychecksum{};
unsigned int storedn{};

//ARRAYS
unsigned int checksum[8]; //break n into 8 seperate digits and store in this array
unsigned int multipliedchecksum[8]; //new array for when digits are multipled by 2
unsigned int addedchecksum[8]; //new array for when values in multipliedchecksum array are larger than 9
unsigned int finalchecksum[9]; //final array with returned checksum digits seperated


void remove_checksum( unsigned int array[], std::size_t capacity );


void remove_checksum( unsigned int array[], std::size_t capacity ){
	for(int i = 0; i < capacity; i++){
		storedn = 0;
		if(array[i] > 999999999) {//more than 9 digits
			array[i] = UINT_MAX;
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
	array[i] = returnedvalue;
	}
	
}
#ifndef MARMOSET_TESTING
int main() {


	const std::size_t QTY_VALUES {3};
	unsigned int value_series[QTY_VALUES] {202011227, 202099131, 202240123};
	
	remove_checksum(value_series, QTY_VALUES);
	
	std::cout << "The values are: ";
	for (std::size_t series_index {0};
		series_index < QTY_VALUES; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}

    std::cout << std::endl;
    return 0;
}
#endif
//g++ staircase.cpp -std=c++11 -o staircase