#include <iostream>
#include <string>
#include <cctype>   // for toupper

using namespace std;

int main() {
    // Arrays for Roman numeral parts
    const string thousands[] = {"", "M", "MM", "MMM"};
    const string hundreds[]  = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    const string tens[]      = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    const string units[]     = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    string input;

    while (cin >> input) {
        // Case 1: Arabic number (starts with digit)
        if (isdigit(input[0])) {
            int number = stoi(input);
            if (number >= 1 && number <= 3999) {
                string roman = thousands[number / 1000] +
                               hundreds[(number % 1000) / 100] +
                               tens[(number % 100) / 10] +
                               units[number % 10];
                cout << roman << endl;
            } else {
                cout << 0 << endl; // Out of range
            }
        }
        // Case 2: Roman number (starts with letter)
        else if (isalpha(input[0])) {
            // Convert input to uppercase
            for (char &c : input) {
                c = toupper(c);
            }

            int value = 0;
            string r = input;
            bool matchedSomething = false;

            // Thousands
            for (int i = 3; i >= 1; i--) { // longest first
                if (r.rfind(thousands[i], 0) == 0) { // prefix match
                    value += i * 1000;
                    r.erase(0, thousands[i].size());
                    matchedSomething = true;
                    break;
                }
            }

            // Hundreds
            for (int i = 9; i >= 1; i--) {
                if (r.rfind(hundreds[i], 0) == 0) {
                    value += i * 100;
                    r.erase(0, hundreds[i].size());
                    matchedSomething = true;
                    break;
                }
            }

            // Tens
            for (int i = 9; i >= 1; i--) {
                if (r.rfind(tens[i], 0) == 0) {
                    value += i * 10;
                    r.erase(0, tens[i].size());
                    matchedSomething = true;
                    break;
                }
            }

            // Units
            for (int i = 9; i >= 1; i--) {
                if (r.rfind(units[i], 0) == 0) {
                    value += i;
                    r.erase(0, units[i].size());
                    matchedSomething = true;
                    break;
                }
            }

            if (!matchedSomething) {
                cout << 0 << endl; // no valid Roman numeral prefix
            } else {
                cout << value << endl; // ignore trailing garbage
            }
        }
        // Case 3: invalid input
        else {
            cout << 0 << endl;
        }
    }

    return 0;
}