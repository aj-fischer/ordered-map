#include "map.h"
#include <gtest/gtest.h>
#include <iostream>
using namespace std;


// Checks if constructor creates a map with zero size.
TEST(MapTest, constructorCreatesCorrectSize) {
    Map m;
    EXPECT_EQ(0, m.size());
}

// Checks if inserting into an empty map is successful and
// insert() increments size.
TEST(MapTest, insertWhileEmptyReturnsTrueAndMapSizeIsOne) { 
    Map m;
    EXPECT_TRUE(m.insert("a", "a"));
    EXPECT_EQ(1, m.size());
}

// Checks if you can't insert a key that already exists and that
// size doesn't increase despite a failed insertion.
TEST(MapTest, insertingExistingKeyReturnsFalseAndMapSizeStaysSame) {
    Map m;
    m.insert("a", "a");
    EXPECT_FALSE(m.insert("a", "a"));
    EXPECT_EQ(1, m.size());
}

// Tests if erase deletes valid key and that size properly decrements.
TEST(MapTest, erasingExistingKeyReturnsTrueAndMapSizeDecreases) {
    Map m;
    m.insert("a", "a");
    EXPECT_TRUE(m.erase("a"));
    EXPECT_EQ(0, m.size());
}

TEST(MapTest, erasingNodeWithTwoChildrenProperlyLinksChildren) {
    Map m;
    m.insert("50", "a");
    m.insert("40", "b");
    m.insert("60", "c");
    m.insert("57", "d");
    m.insert("55", "e");
    m.insert("56", "f");
    cout << m;
    EXPECT_TRUE(m.erase("50"));
    cout << m;
    EXPECT_TRUE(m.erase("55"));
    cout << m;
    EXPECT_TRUE(m.erase("56"));
    cout << m;
    EXPECT_TRUE(m.erase("57"));
    cout << m;
    EXPECT_TRUE(m.erase("60"));
    cout << m;
    EXPECT_TRUE(m.erase("40"));
}

// Tests if erase() won't erase a key that doesn't exist, and that size
// is not decremented despite failing to erase.
TEST(MapTest, erasingInvalidKeyReturnsFalseAndMapSizeStaysSame) {
    Map m;
    m.insert("a", "a");
    EXPECT_FALSE(m.erase("b"));
    EXPECT_EQ(1, m.size());
}

// Accessing a key in the BST will properly return the elements data
// and not change the size of the map.
TEST(MapTest, indexOperatorOfExistingKeyReturnsProperValueAndSizeIsSame) {
    Map m;
    m.insert("g", "z");
    EXPECT_EQ(m["g"], "z");
    EXPECT_EQ(m.size(), 1);
}

// Index operator should insert an element if it's not in the tree and size should increase by one.
TEST(MapTest, indexOperatorOfInvalidKeyReturnsEmptyStringAndIncreasesSize) {
    Map m;
    m.insert("g", "z");
    EXPECT_EQ(m["b"], "");
    EXPECT_EQ(m.size(), 2);
}

// Two maps of the same size should be created from the copy constructor
TEST(MapTest, copyConstructorMakesCorrectSize) {
    Map m;
    m.insert("a", "a");
    Map n = m;
    EXPECT_EQ(m.size(), 1);
    EXPECT_EQ(n.size(), 1);
}

TEST(MapTest, copyConstructorMakesSeparateCopy) {
    Map m;
    m.insert("a", "a");
    Map n = m;
    n.insert("b", "z");
    EXPECT_FALSE(m.size() == n.size());
    m.insert("g", "f");
    EXPECT_TRUE(m.size() == n.size());
    m.insert("r", "j");
    n.insert("r", "h");
    cout << m;
    cout << n;
    EXPECT_NE(m["r"], n["r"]);
    EXPECT_TRUE(m.erase("r"));
    cout << m;
    cout << n;
    EXPECT_NE(m.size(), n.size());
    EXPECT_TRUE(n.erase("r"));
    cout << m;
    cout << n;
    EXPECT_EQ(m.size(), n.size());
}

// Using the assignment operator results in two maps of the same, correct size.
TEST(MapTest, assignmentOperatorMakesCorrectSize)
{
    Map m;
    EXPECT_EQ(0, m.size());
    m.insert("a", "a");
    m.insert("b", "b");
    EXPECT_EQ(2, m.size());
    Map n = m;
    EXPECT_EQ(2, n.size());
    EXPECT_EQ(m.size(), n.size());
}

// Using the assignment operator with an existing map makes its own
// copy, such that if the value associated with a key is changed
// in the copy it does not change the associated value in the
// original, and inserts/erases on either won't affect the other.
TEST(MapTest, assignmentMakesSeparateCopy)
{
    Map m;
    m.insert("a", "a");
    Map n;
    n = m;
    EXPECT_EQ(n.size(), m.size());
    n["a"] = "b";
    EXPECT_NE(m["a"], n["a"]);
    m.insert("b", "a");
    EXPECT_EQ(1, n.size());
    EXPECT_NE(m["b"], n["b"]);
    n.insert("b", "b");
    EXPECT_EQ(2, n.size());
    EXPECT_NE(m["b"], n["b"]);
    m.erase("a");
    EXPECT_EQ(2, n.size());
    EXPECT_NE(m["a"], n["a"]);
    n.erase("b");
    EXPECT_EQ(1, n.size());
    EXPECT_NE(m["b"], n["b"]);
}

// Using the assignment operator with an existing map with over 1000 items
// makes a copy that has correct keys/values at a couple of places deep within
// the map (values that aren't at either end of the range of keys used).
TEST(MapTest, assignmentWithManyItemsHasCorrectValues)
{
    Map m;
    string key;
    string val;

    // Add 1000 items to first map
    for (int i = 1; i <= 1000; i++) {
        key = to_string(i);
        val = to_string(i);
        m.insert(key, val);
    }

    EXPECT_EQ(1000, m.size());

    Map n;
    n = m;

    EXPECT_EQ(1000, m.size());
    EXPECT_EQ(m.size(), n.size());

    // Test 10 items deep into each list
    EXPECT_EQ(m["600"], n["600"]);
    EXPECT_EQ(m["655"], n["655"]);
    EXPECT_EQ(m["704"], n["704"]);
    EXPECT_EQ(m["789"], n["789"]);
    EXPECT_EQ(m["821"], n["821"]);
    EXPECT_EQ(m["856"], n["856"]);
    EXPECT_EQ(m["889"], n["889"]);
    EXPECT_EQ(m["907"], n["907"]);
    EXPECT_EQ(m["934"], n["934"]);
    EXPECT_EQ(m["977"], n["977"]);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
