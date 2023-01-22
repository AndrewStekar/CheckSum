// Andrew Stekar
// October 7, 2022

#include <iostream>
#include <climits>

// function declarations
int main();
unsigned int add_checksum( unsigned int n );
void add_checksum( unsigned int array[], std::size_t capacity );
bool verify_checksum( unsigned int n );
unsigned int remove_checksum( unsigned int n );
void remove_checksum( unsigned int array[], std::size_t capacity );

// function definitions
int main() {
    unsigned int value_to_protect{21352411};
    unsigned int protected_value = add_checksum(value_to_protect);
    std::cout << "The value " << value_to_protect
              << " with the checksum added is " << protected_value
              << "." << std::endl;

    if (verify_checksum(protected_value)) {
        std::cout << "The checksum is valid." << std::endl;
    } else {
        std::cout << "The checksum is invalid." << std::endl;
    }

    const std::size_t QTY_VALUES{3};
    unsigned int value_series[QTY_VALUES]{20201122, 20209913, 20224012};
    add_checksum(value_series, QTY_VALUES);
    std::cout << "Series with checksums added: ";

    for (std::size_t series_index{0}; series_index < QTY_VALUES; series_index++) {
        std::cout << value_series[series_index] << " ";
    }

    std::cout << std::endl;
    return 0;
}

// adds checksum digit to a 8-digit number
unsigned int add_checksum( unsigned int n ) {
    if (n > 99999999) {
        return UINT_MAX;
    } else {
        // declaring local variables
        unsigned int num{n};
        unsigned int current_num{};
        unsigned int tally{0};
        
        // this loop completes steps 1 and 2 in the assignment description.
        // "tally" collects the final number, "current_num" is used to individualy add digits to tally.
        for (std::size_t i{0}; i < 4; ++i) {
            //dealing digits multiplied by 2
            current_num = num%10;
            num = (num - current_num)/10;
            current_num *= 2;
            if (current_num > 9) {
                current_num -= 9;
            }
            tally += current_num;

            //dealing with digits not multiplied by 2
            current_num = num%10;
            num = (num - current_num)/10;
            tally += current_num;
        }
        // returning the number with the checksum included
        return ((n*10) + (tally*9)%10);
    }
}

// this function loops through the numbers in the array and adds the checksum to them.
void add_checksum( unsigned int array[], std::size_t capacity ) {
    for (std::size_t i{0}; i < capacity; ++i) {
        array[i] = add_checksum(array[i]);
    }
}

// checks if the checksum is valid
bool verify_checksum( unsigned int n ) {
    if (n <= 999999999) {
        unsigned int num_to_check{(n - (n%10))/10};
        if (add_checksum(num_to_check) == n) {
            return true;
        }
    } 
    return false;
}

// returns the original 8-digit number if valid
unsigned int remove_checksum( unsigned int n ) {
    if (verify_checksum(n)) {
        return ((n - (n%10))/10);
    } else {
        return UINT_MAX;
    }
}

// removes the checksum digit from the number
void remove_checksum( unsigned int array[], std::size_t capacity ) {
    // looping through the array to modify its elements
    for (std::size_t i{0}; i < capacity; ++i) {
        array[i] = remove_checksum(array[i]);
    }
}