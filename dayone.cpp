#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "solutions.h"

int fromString(std::string test) {

    if (test == "one"){
        return 1;
    } else if (test == "two") {
        return 2;
    } else if (test == "three") {
        return 3;
    } else if (test == "four") {
        return 4;
    } else if (test == "five") {
        return 5;
    } else if (test == "six") {
        return 6;
    } else if (test == "seven") {
        return 7;
    } else if (test == "eight") {
        return 8;
    } else if (test == "nine") {
        return 9;
    } else {
        return 0;
    }
}

int dayone() {
    std::ifstream file("./puzzle_inputs/dayone.txt"); // Open file

    if (file.is_open()) {
        std::string line;

        // First, we read the file line-by line so that we
        // know how much memory we need to allocate
        int lineCounter = 0;
        while (std::getline(file, line)) {
            ++lineCounter;
        }

        // This array will contain the resulting values for each line
        // We could also use a vector instead and resize at each line
        // but I chose the default array here.
        int resultArray[lineCounter] = {};
        int arrayIdx = 0; //keep track of array index

        // Reset file pointer to the beginning of the file so we can re-read it
        file.clear();
        file.seekg(0, std::ios::beg);

        // Read file line by line again
        while (std::getline(file, line)) {
            // Get length of line
            size_t length = line.length();

            // Create two indices, one at the beginning of the line and one at the end
            int upperDigit = -1;
            int lowerDigit = -1;
            int currentDigit = -1;

            // The idea is to keep track of strings with three, four and five chars,
            // since these are the unique numbers of chars in the written-out digits
            // from one to nine
            std::string threeSubstr = "";
            std::string fourSubstr = "";
            std::string fiveSubstr = ""; 
            int testVal;

            // Loop through each line, look for first and last element
            for (int i = 0; i < length; ++i) {
                // Case when the current char is a digit
                if (std::isdigit(line[i])) {
                    currentDigit = line[i] - '0';
                }

                // Check for substring with three characters:
                // if the current line is traversed below two chars,
                // just add the current char. Otherwise, add the current
                // char and check whether a written-out digit is present.
                // If not, the fromString function will return 0, and the
                // value of currentDigit will be used, which is also either 0
                // or larger than zero if a digit was found in the previous step.
                // Then, erase the first element of the string and repeat this
                // in the following loop iteration
                if (threeSubstr.size() < 2) {
                    threeSubstr += line[i];
                } else {
                    threeSubstr += line[i];
                    testVal = fromString(threeSubstr);
                    currentDigit = std::max(currentDigit, testVal);
                    threeSubstr.erase(0,1);
                }

                // Same procedure as for threeSubstr described above.
                if (fourSubstr.size() < 3) {
                    fourSubstr += line[i];
                } else {
                    fourSubstr += line[i];
                    testVal = fromString(fourSubstr);
                    currentDigit = std::max(currentDigit, testVal);
                    fourSubstr.erase(0,1);
                }

                // Same procedure as for threeSubstr described above.
                if (fiveSubstr.size() < 4) {
                    fiveSubstr += line[i];
                } else {
                    fiveSubstr += line[i];
                    testVal = fromString(fiveSubstr);
                    currentDigit = std::max(currentDigit, testVal);
                    fiveSubstr.erase(0,1);
                }

                // If a char digit or written-out digit was found, assign it
                // to left-most digit (lowerDigit) first. If that already has a
                // larger-than-zero value, assign it to upperDigit and keep overwriting it.
                // When finishing the loop, upperDigit will contain the value
                // of the right-most digit.
                if (currentDigit > 0) {
                    if (lowerDigit < 0) {
                        lowerDigit = currentDigit;
                    } else {
                        upperDigit = currentDigit;
                    }

                    currentDigit = 0;
                }
            }

            // Compute calibration and add to resulting array
            if (lowerDigit < 0 && upperDigit < 0) {
                // in case there are also strings without any digits present
                resultArray[arrayIdx] = 0;
            } else if (upperDigit < 0) {
                // Case where only one digit is found in the current line
                resultArray[arrayIdx] = (lowerDigit*10)+lowerDigit;
            } else {
                resultArray[arrayIdx] = (lowerDigit*10)+upperDigit;
            }

            ++arrayIdx;
        }

        file.close(); // Close the file

        // Compute array sum and return fineal result
        int calibrationResult = 0;
        for (int j = 0; j < lineCounter; ++j) {
            calibrationResult += resultArray[j];
        }

        return calibrationResult;
    } else {
        std::cout << "Unable to open file!" << std::endl;
        return 0;
    }
}