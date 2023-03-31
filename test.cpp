/// @file List-test.cxx
/// @author Kevin Mess <kevin.mess@csn.edu>
/// @date 2022-04-16
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Catch2 Unit tests for the dynamic List class

#define CATCH_CONFIG_MAIN
#if defined __linux__
#include <catch.hpp>
#elif defined __MACH__
#include </opt/local/include/catch2/catch.hpp>
#else
#include "catch.hpp"
#endif

#include <algorithm>
#include <initializer_list>
#include <iomanip>
#include <sstream>
#include <string>

#include "List.hpp"
#include "List.hpp"  // check include guard

TEMPLATE_TEST_CASE("List()", "", char, int, double) {
    List<TestType> list1{};

    REQUIRE(list1.size() == 0);
    REQUIRE(list1.empty() == true);
    REQUIRE(list1.begin() == list1.end());
}

TEMPLATE_TEST_CASE("List(const List&)", "", char, int, double) {
    const List<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };
    const List<TestType> list1(REF);

    CHECK(list1.size() == REF.size());
    CHECK(std::equal(list1.begin(), list1.end(), REF.begin(), REF.end()) == true);
}


TEMPLATE_TEST_CASE("List(List&&)", "", char, int, double) {
    const List<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };
    List<TestType> list1(std::move(List<TestType>{ 65, 66, 67, 68, 69, 70, 71, 72 }));

    CHECK(list1.size() == REF.size());
    CHECK(std::equal(list1.begin(), list1.end(), REF.begin(), REF.end()) == true);
}

TEMPLATE_TEST_CASE("List(initializer_list)", "", char, int, double) {
    const std::initializer_list<TestType> INIT {
        65, 66, 67, 68, 69, 70, 71, 72
    };

    const List<TestType> list1 { INIT };

    REQUIRE(list1.size() == INIT.size());
    REQUIRE(std::equal(list1.begin(), list1.end(), INIT.begin(), INIT.end()) == true);
}

TEST_CASE("~List()") {}

TEMPLATE_TEST_CASE("List& operator=(const List&)", "", char, int, double) {
    const List<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    List<TestType> list1{};
    list1 = REF;

    CHECK(list1.size() == REF.size());
    CHECK(list1.begin() != REF.begin());
    CHECK(std::equal(list1.begin(), list1.end(), REF.begin(), REF.end()) == true);

    // check self-assignment
    list1 = list1;

    CHECK(list1.size() == REF.size());
    CHECK(list1.begin() != REF.begin());
    CHECK(std::equal(list1.begin(), list1.end(), REF.begin(), REF.end()) == true);
}

TEMPLATE_TEST_CASE("List& operator=(List&&)", "", char, int, double) {
    const List<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    List<TestType> list1{};
    list1 = std::move(List<TestType>(REF));

    CHECK(list1.size() == REF.size());
    CHECK(list1.begin() != REF.begin());
    CHECK(std::equal(list1.begin(), list1.end(), REF.begin(), REF.end()) == true);

    // check self-assignment
    list1 = std::move(list1);

    CHECK(list1.size() == REF.size());
    CHECK(list1.begin() != REF.begin());
    CHECK(std::equal(list1.begin(), list1.end(), REF.begin(), REF.end()) == true);
}

TEMPLATE_TEST_CASE("front()", "", char, int, double) {
    List<TestType> list1{ 65, 66, 67 };

    CHECK(list1.front() == 65);

    list1.front() = 65 + 32;

    CHECK(list1.front() == 97);

    List<TestType> list2{};

    CHECK_THROWS(list2.front());
}

TEMPLATE_TEST_CASE("back()", "", char, int, double) {
    List<TestType> list1{ 65, 66, 67 };

    CHECK(list1.back() == 67);

    list1.back() = 67 + 32;

    CHECK(list1.back() == 99);

    List<TestType> list2{};

    CHECK_THROWS(list2.back());
}

TEMPLATE_TEST_CASE("empty()", "", char, int, double) {
    List<TestType> list1{};

    CHECK(list1.empty() == true);

    list1.insert(list1.begin(), 42);
    CHECK(list1.empty() == false);
}

TEMPLATE_TEST_CASE("size()", "", char, int, double) {
    const List<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    List<TestType> list1{};
    List<TestType> list2{ REF };

    CHECK(list1.size() == 0);
    CHECK(list2.size() == REF.size());

    list2.clear();
    CHECK(list2.size() == 0);
}

//TEST_CASE("begin()") {}
//TEST_CASE("begin() const") {}
//TEST_CASE("end()") {}
//TEST_CASE("end() const") {}

TEST_CASE("insert()") {
    List<int> list1{};

    REQUIRE(list1.begin() == list1.end());

    // insert into an empty list
    list1.insert(list1.begin(), 66);
    REQUIRE(list1.size() == 1);

    // insert into front of a list
    list1.insert(list1.begin(), 65);
    REQUIRE(list1.size() == 2);

    // insert into back of a list
    list1.insert(list1.end(), 68);
    REQUIRE(list1.size() == 3);

    // insert into middle of a list
    list1.insert(list1.begin()->next->next, 67);
    REQUIRE(list1.size() == 4);

    // check forward linkage
    REQUIRE(list1.begin()->prev == nullptr);
    REQUIRE(list1.begin()->data == 65);
    REQUIRE(list1.begin()->next != nullptr);
    REQUIRE(list1.begin()->next->data == 66);
    REQUIRE(list1.begin()->next->next != nullptr);
    REQUIRE(list1.begin()->next->next->data == 67);
    REQUIRE(list1.begin()->next->next->next != nullptr);
    REQUIRE(list1.begin()->next->next->next->data == 68);
    REQUIRE(list1.begin()->next->next->next->next == list1.end());

    // check backward linkage
    auto tail = list1.begin()->next->next->next;
    REQUIRE(tail->next == list1.end());
    REQUIRE(tail->data == 68);
    REQUIRE(tail->prev != nullptr);
    REQUIRE(tail->prev->data == 67);
    REQUIRE(tail->prev->prev != nullptr);
    REQUIRE(tail->prev->prev->data == 66);
    REQUIRE(tail->prev->prev->prev != nullptr);
    REQUIRE(tail->prev->prev->prev->data == 65);
    REQUIRE(tail->prev->prev->prev->prev == nullptr);
}

TEST_CASE("erase()") {
    List<int> list1 { 65, 66, 67, 68 };

    REQUIRE(list1.begin()->prev == nullptr);
    REQUIRE(list1.begin()->next->next->next->next == list1.end());

    // delete last element
    list1.erase(list1.begin()->next->next->next);
    REQUIRE(list1.begin()->next->next->next == list1.end());
    REQUIRE(list1.begin()->next->next->data == 67);
    REQUIRE(list1.begin()->next->next->prev->data == 66);
    REQUIRE(list1.size() == 3);

    // delete middle element
    list1.erase(list1.begin()->next);
    REQUIRE(list1.size() == 2);
    REQUIRE(list1.begin()->next->next == list1.end());
    REQUIRE(list1.begin()->next->data == 67);
    REQUIRE(list1.begin()->next->prev->data == 65);

    // delete front element
    list1.erase(list1.begin());
    REQUIRE(list1.size() == 1);
    REQUIRE(list1.begin()->data == 67);
    REQUIRE(list1.begin()->next == list1.end());
    REQUIRE(list1.begin()->prev == nullptr);

    // delete final element, leaving empty container
    list1.erase(list1.begin());
    REQUIRE(list1.empty() == true);
    REQUIRE(list1.size() == 0);
}

TEMPLATE_TEST_CASE("clear()", "", char, int, double) {
    const List<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    List<TestType> list1 { REF };
    CHECK(list1.size() == REF.size());
    list1.clear();
    CHECK(list1.size() == 0);
}

TEMPLATE_TEST_CASE("swap(List&)", "", char, int, double) {
    const List<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    List<TestType> list1 { REF };
    List<TestType> list2;

    list1.swap(list2);

    CHECK(list1.empty() == true);
    REQUIRE(list2.size() == REF.size());

    CHECK(std::equal(list1.begin(), list1.end(), REF.begin(), REF.end()) == false);
    CHECK(std::equal(list2.begin(), list2.end(), REF.begin(), REF.end()) == true);
}

TEMPLATE_TEST_CASE("bool operator==(const List&, const List&)", "", char, int, double) {
    const List<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    List<TestType> list1{ REF };
    List<TestType> list2{ REF };
    List<TestType> list3{ REF };

    CHECK((list1 == list2) == true);

    list2.begin()->next->next->next->next->next->next->data = 42;
    CHECK((list1 == list2) == false);

    list3.insert(list3.end(), 42);
    CHECK((list1 == list2) == false);
}

TEMPLATE_TEST_CASE("bool operator!=(const List&, const List&)", "", char, int, double) {
    const List<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    List<TestType> list1 { REF };
    List<TestType> list2 { REF };
    List<TestType> list3 { REF };

    CHECK((list1 != list2) == false);

    list2.begin()->next->next->next->data = 42;
    CHECK((list1 != list2) == true);

    list3.insert(list3.end(), 42);
    CHECK((list1 != list2) == true);
}

TEST_CASE("std::ostream& operator<<(std::ostream&, const List<char>&)") {
    const List<char> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    std::ostringstream output{};
    List<char> list1{};
    List<char> list2 { REF };

    output << list1;

    CHECK(output.str() == "{}");

    output.str("");

    output << list2;

    CHECK(output.str() == "{A,B,C,D,E,F,G,H}");
}

TEST_CASE("std::ostream& operator<<(std::ostream&, const List<int>&)") {
    const List<int> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    std::ostringstream output{};
    List<int> list1{};
    List<int> list2 { REF };

    output << list1;

    CHECK(output.str() == "{}");

    output.str("");

    output << list2;

    CHECK(output.str() == "{65,66,67,68,69,70,71,72}");
}

TEST_CASE("std::ostream& operator<<(std::ostream&, const List<double>&)") {
    const List<double> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    std::ostringstream output{};
    output << std::fixed << std::showpoint << std::setprecision(1);

    List<double> list1{};
    List<double> list2 { REF };

    output << list1;

    CHECK(output.str() == "{}");

    output.str("");

    output << list2;

    CHECK(output.str() == "{65.0,66.0,67.0,68.0,69.0,70.0,71.0,72.0}");
}

TEST_CASE("std::ostream& operator<<(std::ostream&, const List<std::string>&)") {
    const List<std::string> REF {
        "Alpha", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf"
    };

    std::ostringstream output{};

    List<std::string> list1{};
    List<std::string> list2{ REF };

    output << list1;

    CHECK(output.str() == "{}");

    output.str("");

    output << list2;

    CHECK(output.str() == "{Alpha,Bravo,Charlie,Delta,Echo,Foxtrot,Golf}");
}

/* EOF */

