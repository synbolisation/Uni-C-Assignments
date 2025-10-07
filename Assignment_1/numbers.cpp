#include <iostream>
#include <algorithm>
using namespace std;

//Function to convert string to decimal
string dec_to_binary(int dec) {
    if (dec == 0) return "0";  // Special case: binary of 0 is just "0"

    string binary = "";   // This will hold the binary result as a string
    while (dec > 0) {
        int remainder = dec % 2;  // Modulo gives the remainder when dividing by 2 -> it gives the last binary digit
        binary = to_string(remainder) + binary; // Prepend remainderr (build binary string from right to left)
        dec /= 2;                                   // Divide number by 2 (shift right in binary terms)
    }
    return binary;  // Return the full binary string
}

//Function to reverse number
int reverse_number(int n) {
    string s = to_string(n);   // Convert the integer n to a string ie 1234 -> "1234"
    reverse(s.begin(), s.end()); // Reverse the string in place from beginning to end of string
    return stoi(s);            // Convert the reversed string back to integer
}

//Function to add the two reversed numbers, then return the reversed sum
int reverse_plus(int first, int second) {
    int revFirst = reverse_number(first);   // Reverse the first number
    int revSecond = reverse_number(second); // Reverse the second number
    int sum = revFirst + revSecond;         // Adds the two reversed numbers together
    return reverse_number(sum);             // Reverse the sum and return it
}

// Helper function that multiply a big number (stored as string) by an integer x
string multiply(string num, int x) {
    long long carry = 0;             // carry stores overflow digits during multiplication
    string result = "";        // result string will hold the new number

    // process each digit of the stiring from right to left
    for (int i = num.size() - 1; i >= 0; i--) { // num.size is the size of the string, i-- is the decriment
        int digit = num[i] - '0';         // convert ASCII char -> int digit
        long long prod = digit * x + carry;     // multiply digit by x and add carry
        result.push_back((prod % 10) + '0'); // store the last digit of prod as char
        carry = prod / 10;                // update carry with the remaining part
    }

    // handle any leftover carry (e.g. multiplying 99 * 9 = 891, carry is 8 at the end)
    while (carry) {
        result.push_back((carry % 10) + '0'); // takes last digit out of carry incase left over is more than 1 digit
        carry /= 10;                          // reduce carry by dividing by 10
    }

    // currently result is reversed (lowest digit first), so fix it
    reverse(result.begin(), result.end());
    return result;   // return the product as string
}

// Factorial function using string-based big integer arithmetic
string factorial(int n) {
    string result = "1";     // start with "1" (since 0! = 1 and 1! = 1)
    for (int i = 2; i <= n; i++) {     // loop from 2 up to n
        result = multiply(result, i);  // multiply current result by i
    }
    return result;   // return final factorial value as a string
}

int main(int argc, char const *argv[]) { // Don't modify anything in main!
    char *end;
    long which = 0;
    which=strtol(argv[1], &end, 10);
    switch(which){
        case 1: {
            long dec = strtol(argv[2], &end, 10);
            std::cout << dec << " in binary = " << dec_to_binary(dec) << std::endl;
            break;
        }
        case 2: {
            long first = strtol(argv[2], &end, 10);
            long second = strtol(argv[3], &end, 10);
            std::cout << "reverse_plus(first, second) = " << reverse_plus(first, second) << std::endl;
            break;
        }
        case 3: {
            long limit = strtol(argv[2], &end, 10);
            std::cout << limit << "! = " << factorial(limit) << std::endl;
            break;
        }
        default: {
            std::cout << "invalid option: " << which; break;
        }
    }
    return 0;
}
