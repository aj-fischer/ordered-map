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

TEST(MapTest, indexOperatorOfInvalidKeyReturnsEmptyStringAndIncreasesSize) {
    Map m;
    m.insert("g", "z");
    EXPECT_EQ(m["b"], "");
    EXPECT_EQ(m.size(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
