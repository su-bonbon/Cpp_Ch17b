/// @file pa17b.cpp
/// @author Sujin Lee
/// @date 3/30/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief client file to create unique lists
/// @note 40hr
/// 2022-03-30: Sujin created

#include <iostream>
#include <cctype>
#include <string>
#include "List.hpp"
#include <initializer_list>
using namespace std;
/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {
    List<string> list1;  // string type List
    string voca;  // standard input variable
    bool flag;  // LCV for two usages
    List<string>::iterator it1 = nullptr;  // iterator for ascending order
    List<string>::iterator it2 = nullptr;  // iterator for trailcurrent of it1
    List<string>::iterator some = nullptr;  // iterator for travalse and output
    int i;  // LCV of for-loop

    while (cin >> voca) {  // get the input
        for (i = 0; i < static_cast<int>(voca.length()); i++) {
            voca[i] = std::tolower(voca[i]);  // change to lower case
        }
        flag = std::ispunct(voca[voca.length()-1]);
        if (flag) {  // if there is special char at the end
            voca[voca.length()-1] = '\0';  // delete
        }
        flag = std::ispunct(voca[0]);
        if (flag) {  // id there is special char in the beginning
            for(i = 0; i < static_cast<int>(voca.length()); i++) {
                voca[i] = voca[i+1];  // move
            }
        }
        if (list1.size() == 0) {  // if list1 is empty
            it1 = list1.insert(list1.begin(), voca);  // insert in the beginning
        }
        else {  // list1 is not empty
            flag = false;  // initialize LCV to enter travalse
            some = list1.begin();  // comp value to voca
            while (some != list1.end() && !flag) {
                if (*some >= voca) {  // find the pos
                    flag = true;
                }
                else {
                    some++;  // otherwise, increse
                }
            }  // ignore *some == voca case bc
            if (some == list1.end() || *some != voca) {
                if (some == list1.begin()) {
                    it1 = list1.insert(list1.begin(), voca);
                }
                else if (some == list1.end()) {
                    it1 = list1.insert(list1.end(), voca);
                }
                else {
                    it1 = list1.insert(some, voca);
                }
            }
        }
    }  // eof while

    some = list1.begin();
    cout << "FORWARD" << endl;
    cout << "-------" << endl;
    for (i = 0; i < static_cast<int>(list1.size()); i++) {
        cout << *some << endl;
        it2 = some;  // update it2 for reverse printing
        some++;
    }
    cout << "REVERSE" << endl;
    cout << "-------" << endl;

    while (it2 != nullptr) {
        cout << *it2  << endl;
        it2--;
    }

    return EXIT_SUCCESS;
}
