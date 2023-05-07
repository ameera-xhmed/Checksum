#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif
unsigned int d{}; //last checksum digit calculated (will be added to end of n as the ninth digit)
unsigned int returnedvalue{}; //returned checksum
unsigned int addingsums{}; 
unsigned int verifychecksum{};
int counter{};
unsigned int arraychecksum{};

//ARRAYS
unsigned int checksum[8]; //break n into 8 seperate digits and store in this array
unsigned int multipliedchecksum[8]; //new array for when digits are multipled by 2
unsigned int addedchecksum[8]; //new array for when values in multipliedchecksum array are larger than 9
unsigned int finalchecksum[9]; //final array with returned checksum digits seperated

void add_checksum( unsigned int array[], std::size_t capacity ); 

void add_checksum( unsigned int array[], std::size_t capacity ){ //overwrite array with new values?

	for(int i = 0; i < capacity; i++){
        if(array[i] > 99999999){
            array[i] = UINT_MAX; //fix return value
        }
        else {
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
            finalchecksum[0] = checksum[7];
            finalchecksum[1] = checksum[6];
            finalchecksum[2] = checksum[5];
            finalchecksum[3] = checksum[4];
            finalchecksum[4] = checksum[3];
            finalchecksum[5] = checksum[2];
            finalchecksum[6] = checksum[1];
            finalchecksum[7] = checksum[0];
            finalchecksum[8] = d;
            
            for(int m = 0; m < 9; m++){
                returnedvalue = returnedvalue*10 + finalchecksum[m];
            }
                
        }
        array[i] = returnedvalue;
        }
}

#ifndef MARMOSET_TESTING
int main() {
	
	/*const std::size_t counter {0};
    unsigned int value_series[counter]{};
    std::cin >> counter; 
    std::cin >> value_series[counter];*/
	const std::size_t counter {3};
	unsigned int value_series[counter] {20201122, 20209913, 20224012}; //20201122 7 20209913 1 20224012 3 
	
	add_checksum(value_series, counter);
	
	std::cout << "Series with checksums added: ";

	for (std::size_t series_index {0};
		series_index < counter; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}

    std::cout << std::endl;
    return 0;
}
#endif
//g++ staircase.cpp -std=c++11 -o staircase