#include <avltree.h>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

// Constructor destructor tests ---------------------------

TEST(ConstructorDestructor, DefaultConstructor) {
    AVLTree<int, std::string> tree;
    ASSERT_EQ(tree.size(), 0);
    ASSERT_FALSE(tree.contains(100)); // shouldn't contain some random keys
}

TEST(ConstructorDestructor, CopyConstructorEmpty) {
    AVLTree<int, std::string> original;
    AVLTree<int, std::string> copy(original);

    ASSERT_EQ(copy.size(), 0);
    ASSERT_FALSE(copy.contains(0));
}

TEST(ConstructorDestructor, CopyConstructorNonEmpty) {
    AVLTree<int, std::string> original;
    original.upsert(10, "ten");
    original.upsert(20, "twenty");

    AVLTree<int, std::string> copy(original);

    // test keys
    ASSERT_EQ(copy.size(), 2);
    ASSERT_TRUE(copy.contains(10));
    ASSERT_TRUE(copy.contains(20));

    // modifying one shouldnt affect the other
    original.remove(10);
    ASSERT_EQ(original.size(), 1);
    ASSERT_EQ(copy.size(), 2);
    ASSERT_TRUE(copy.contains(10));
}

TEST(ConstructorDestructor, DestructorBasicCheck) {
    // we cannot directly test the destructor from user code,
    // but we can put an instance in a scope to ensure no crashes, etc.
    {
        AVLTree<int, std::string> tree;
        tree.upsert(1, "test");
        // exit scope => destructor called
    }
    SUCCEED();
}

// Accessory test: SIZE ---------------------------

TEST(size, EmptyTree) { // trivial
    AVLTree<int, std::string> tree;
    ASSERT_EQ(tree.size(), 0);
}

TEST(size, InsertOne) {
    AVLTree<int, std::string> tree;
    tree.upsert(1, "test");
    ASSERT_EQ(tree.size(), 1);
}

TEST(size, AfterMultipleUpserts) {
    AVLTree<int, std::string> tree;
    tree.upsert(1, "one");
    tree.upsert(2, "two");
    tree.upsert(3, "three");
    ASSERT_EQ(tree.size(), 3);

    // upserting a duplicate key should not increase size
    tree.upsert(2, "two updated");
    ASSERT_EQ(tree.size(), 3);
}

// Accessory test: CONTAINS ---------------------------

TEST(contains, EmptyTree) {
    AVLTree<int, std::string> tree;
    ASSERT_FALSE(tree.contains(9999));
}

TEST(contains, NonEmptyTreeKeyExists) {
    AVLTree<int, std::string> tree;
    tree.upsert(42, "weed");
    ASSERT_TRUE(tree.contains(42));
}

TEST(contains, NonEmptyTreeKeyDoesNotExist) {
    AVLTree<int, std::string> tree;
    tree.upsert(10, "ten");
    ASSERT_FALSE(tree.contains(9999));
}

// Accessory test: GET ---------------------------

TEST(get, GetOnEmptyTree) {
    AVLTree<int, std::string> tree;
    auto value = tree.get(5);
    ASSERT_FALSE(value.has_value());
}

TEST(get, GetKeyExists) {
    AVLTree<int, std::string> tree;
    tree.upsert(100, "hundred");

    auto value = tree.get(100);
    ASSERT_TRUE(value.has_value());
    ASSERT_EQ(value->get(), "hundred"); // reference_wrapper’s .get() returns the underlying object
}

TEST(get, GetKeyNotExists) {
    AVLTree<int, std::string> tree;
    tree.upsert(10, "ten");
    auto value = tree.get(20);
    ASSERT_FALSE(value.has_value());
}

TEST(get, GetReferenceTest) {
    AVLTree<int, std::string> tree;
    tree.upsert(10, "apple");

    auto value = tree.get(10);
    ASSERT_TRUE(value.has_value());
    // modify
    value->get() = "banana";
    ASSERT_EQ(tree.get(10)->get(), "banana");
}

TEST(get, GetCrossReferenceTest) {
    AVLTree<int, std::string> tree;
    tree.upsert(10, "apple");
    tree.upsert(20, "pears");

    auto value = tree.get(10);
    auto value2 = tree.get(20);
    ASSERT_TRUE(value.has_value());
    ASSERT_TRUE(value2.has_value());
    // swap both references with a common value
    value->get().swap(value2->get());
    ASSERT_EQ(tree.get(10)->get(), "pears");
    ASSERT_EQ(tree.get(20)->get(), "apple");
    // modify
    value->get() = "banana";
    ASSERT_EQ(tree.get(10)->get(), "banana");
    ASSERT_EQ(tree.get(20)->get(), "apple");
}

// Accessory test: GETRANGE ---------------------------

TEST(getRange, EmptyTree) {
    AVLTree<int, std::string> tree;
    auto result = tree.getRange(0, 100);
    ASSERT_TRUE(result.isEmpty());
}

TEST(getRange, SingleElementInRange) {
    AVLTree<int, std::string> tree;
    tree.upsert(50, "fifty");

    auto result = tree.getRange(0, 100);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].first, 50);
    EXPECT_EQ(result[0].second.get(), "fifty");
}

TEST(getRange, MultipleInRange) {
    AVLTree<int, std::string> tree;
    tree.upsert(10, "ten");
    tree.upsert(20, "twenty");
    tree.upsert(30, "thirty");
    tree.upsert(40, "forty");

    // Should capture 20, 30, 40
    auto result = tree.getRange(15, 40);
    ASSERT_EQ(result.size(), 3);

    // Because we do not assume internal order, just verify correctness of contents
    std::set<int> keysInRange;
    for (auto &pair : result) {
        keysInRange.insert(pair.first);
    }
    ASSERT_TRUE(keysInRange.find(20) != keysInRange.end());
    ASSERT_TRUE(keysInRange.find(30) != keysInRange.end());
    ASSERT_TRUE(keysInRange.find(40) != keysInRange.end());
}

TEST(getRange, NoElementsInRange) {
    AVLTree<int, std::string> tree;
    tree.upsert(1, "one");
    tree.upsert(2, "two");
    tree.upsert(3, "three");

    auto result = tree.getRange(10, 20);
    ASSERT_TRUE(result.isEmpty());
}

TEST(getRange, InvalidRange) {
    AVLTree<int, std::string> tree;
    tree.upsert(1, "one");
    tree.upsert(2, "two");
    tree.upsert(3, "three");

    auto result = tree.getRange(20, 10);
    ASSERT_TRUE(result.isEmpty());
}

// Accessory test: CLEAR ---------------------------

TEST(clear, ClearEmptyTree) {
    AVLTree<int, std::string> tree;
    tree.clear(); // should not crash or do anything unexpected
    ASSERT_EQ(tree.size(), 0);
    ASSERT_FALSE(tree.contains(10));
}

TEST(clear, ClearNonEmptyTree) {
    AVLTree<int, std::string> tree;
    tree.upsert(1, "one");
    tree.upsert(2, "two");
    tree.upsert(3, "three");
    ASSERT_EQ(tree.size(), 3);

    tree.clear();
    ASSERT_EQ(tree.size(), 0);
    ASSERT_FALSE(tree.contains(1));
    ASSERT_FALSE(tree.contains(2));
    ASSERT_FALSE(tree.contains(3));
}

// Accessory test: UPDATE ---------------------------

TEST(update, UpdateNonExistentKeyDoesNothing) {
    AVLTree<int, std::string> tree;
    tree.update(10, "ten updated");
    // no crash, size should remain 0
    ASSERT_EQ(tree.size(), 0);
    ASSERT_FALSE(tree.contains(10));
}

TEST(update, UpdateExistentKey) {
    AVLTree<int, std::string> tree;
    tree.upsert(10, "old value");
    ASSERT_EQ(tree.size(), 1);

    tree.update(10, "new value");
    auto val = tree.get(10);
    ASSERT_TRUE(val.has_value());
    ASSERT_EQ(val->get(), "new value");
    ASSERT_EQ(tree.size(), 1); // size should remain the same
}

// Accessory test: UPSERT ---------------------------

TEST(upsert, InsertNewKey) {
    AVLTree<int, std::string> tree;
    tree.upsert(10, "ten");
    ASSERT_TRUE(tree.contains(10));
    ASSERT_EQ(tree.size(), 1);
}

TEST(upsert, UpdateExistingKey) {
    AVLTree<int, std::string> tree;
    tree.upsert(5, "five");
    ASSERT_EQ(tree.size(), 1);

    tree.upsert(5, "five updated");
    ASSERT_EQ(tree.size(), 1);
    auto val = tree.get(5);
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val->get(), "five updated");
}

// Accessory test: REMOVE ---------------------------

TEST(remove, RemoveNonExistentKey) {
    AVLTree<int, std::string> tree;
    tree.upsert(1, "one");
    ASSERT_EQ(tree.size(), 1);

    tree.remove(9999);
    ASSERT_EQ(tree.size(), 1); // size unchanged
    ASSERT_TRUE(tree.contains(1));
}

TEST(remove, RemoveExistentKey) {
    AVLTree<int, std::string> tree;
    tree.upsert(42, "test");
    ASSERT_TRUE(tree.contains(42));
    ASSERT_EQ(tree.size(), 1);

    tree.remove(42);
    ASSERT_EQ(tree.size(), 0);
    ASSERT_FALSE(tree.contains(42));
}

// MEMORY LEAK TESTS ---------------------------
// NOTE: run these under a memory profiler.

TEST(MemoryLeak, InsertAndClearRepeatedly) {
    AVLTree<int, std::string> tree;

    // test stability
    for (int iteration = 0; iteration < 10; ++iteration) {
        for (int i = 0; i < 1000; ++i) {
            tree.upsert(i, "value");
        }
        tree.clear();
        ASSERT_EQ(tree.size(), 0);
    }

    SUCCEED();
}
