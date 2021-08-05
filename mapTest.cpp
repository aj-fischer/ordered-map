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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
