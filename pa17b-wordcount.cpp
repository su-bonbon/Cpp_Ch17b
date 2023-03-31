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
struct freq {
    int count;
    string  word;
};
int main() {
    List<freq> list1;
    List<freq> list2;
    string voca;
    bool flag;
    List<freq>::iterator it1 = nullptr;
    List<freq>::iterator it2 = nullptr;
    List<freq>::iterator some = nullptr;
    int i;
    freq item;

    while (cin >> voca) {
        for (i = 0; i < static_cast<int>(voca.length()); i++) {
            voca[i] = std::tolower(voca[i]);
        }
        flag = std::ispunct(voca[voca.length()-1]);
        if (flag) {
            voca[voca.length()-1] = '\0';
        }
        flag = std::ispunct(voca[0]);
        if (flag) {
            for(i = 0; i < static_cast<int>(voca.length()); i++) {
                voca[i] = voca[i+1];
            }
        }
        if (list1.size() == 0) {
            item = { 1, voca };
            it1 = list1.insert(list1.begin(), item);
        }
        else {
            flag = false;
            some = list1.begin();
            while (some != list1.end() && !flag) {
                if ((*some).word >= voca) {
                    flag = true;
                }
                else {
                    some++;
                }
            }
            if (some == list1.end() || (*some).word != voca) {
                item = { 1, voca };
                if (some == list1.begin()) {
                    it1 = list1.insert(list1.begin(), item);
                }
                else if (some == list1.end()) {
                    it1 = list1.insert(list1.end(), item);
                }
                else {
                    it1 = list1.insert(some, item);
                }
                it1 = list1.begin();  // traverse for frequency count
            }
            else if ((*some).word == voca) {
                (*some).count++;
            }
        }
    }  // eof while
    it2 = list2.begin();
    it1 = list1.begin();
    while (it1 != list1.end()) {
        if (list2.empty()) {  // if list2 is empty
            it2 = list2.insert(it2, *it1);
            it1++;
        }
        else {  // if list2 is not empty put in the middle of end
            it2 = list2.begin();
            some = list2.begin();
            flag = false;
            while (it2 != nullptr && !flag) {
                if ((*it2).count < (*it1).count){
                    flag = true;
                }
                else {
                    it2++;
                }
            }  // eof while
            if (it2 == list2.begin()) {
                it2 = list2.insert(list2.begin(), *it1);
            }
            else if (it2 == list2.end()) {
                it2 = list2.insert(list2.end(), *it1);
            }
            else {
                it2 = list2.insert(it2, *it1);
            }
            it1++;
        }
    }
    some = list1.begin();
    cout << "ALPHABETIC" << endl;
    cout << "----------" << endl;
    for (i = 0; i < static_cast<int>(list1.size()); i++) {
        cout << '\t' << (*some).count << ' ' << (*some).word << endl;
        some++;
    }
    cout << "FREQUENCY" << endl;
    cout << "---------" << endl;
    some = list2.begin();
    for (i = 0; i < static_cast<int>(list1.size()); i++) {
        cout << '\t' << (*some).count << ' ' << (*some).word << endl;
        some++;
    }

    return EXIT_SUCCESS;
}
