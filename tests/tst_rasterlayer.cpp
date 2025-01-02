#include <QtCore/qdebug.h>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <rasterlayer.h>

using namespace testing;

// Constructor destructor tests ---------------------------

TEST(ConstructorDestructor, DefaultConstructor) {
    RasterLayer layer;
    EXPECT_EQ(layer.size(), 0);
    EXPECT_FALSE(layer.contains(QPoint(0, 0)));
}

TEST(ConstructorDestructor, CopyConstructorEmpty) {
    RasterLayer original;
    RasterLayer copy(original);

    // both should be empty
    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(copy.size(), 0);
}

TEST(ConstructorDestructor, CopyConstructorNonEmpty) {
    RasterLayer original;
    original.upsert({10, 10}, QColor(255, 0, 0, 255));
    original.upsert({20, 20}, QColor(0, 255, 0, 255));

    RasterLayer copy(original);

    // test keys
    EXPECT_EQ(copy.size(), 2);
    EXPECT_TRUE(copy.contains(QPoint(10, 10)));
    EXPECT_TRUE(copy.contains(QPoint(20, 20)));

    // modifying one shouldnt affect the other
    original.clear();
    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(copy.size(), 2);
    EXPECT_TRUE(copy.contains(QPoint(10, 10)));
}

TEST(ConstructorDestructor, DestructorBasicCheck) {
    {
        RasterLayer layer;
        layer.upsert(QPoint(10, 10), QColor(128, 128, 128));
    }
    // if no crash or external memory leak detection flags show up, we pass.
    SUCCEED();
}

// Accessors tests: SIZE ---------------------------

TEST(size, EmptyLayer) {
    RasterLayer layer;
    EXPECT_EQ(layer.size(), 0);
}

TEST(size, AfterSingleUpsert) {
    RasterLayer layer;
    layer.upsert(QPoint(0, 0), QColor(255, 255, 255));
    EXPECT_EQ(layer.size(), 1);
}

TEST(size, AfterMultipleUpserts) {
    RasterLayer layer;
    layer.upsert(QPoint(0, 0), QColor(255, 255, 255));
    layer.upsert(QPoint(1, 1), QColor(0, 0, 0));
    EXPECT_EQ(layer.size(), 2);

    // upsert an existing pixel => does not increase size
    layer.upsert(QPoint(1, 1), QColor(100, 100, 100));
    EXPECT_EQ(layer.size(), 2);
}

// Accessors tests: CONTAINS ---------------------------

TEST(contains, EmptyLayer) {
    RasterLayer layer;
    EXPECT_FALSE(layer.contains(QPoint(10, 10)));
}

TEST(contains, SinglePixelExists) {
    RasterLayer layer;
    layer.upsert(QPoint(1, 2), QColor(200, 100, 50));
    EXPECT_TRUE(layer.contains(QPoint(1, 2)));
}

TEST(contains, SinglePixelDoesNotExist) {
    RasterLayer layer;
    layer.upsert(QPoint(0, 0), QColor(10, 10, 10));
    EXPECT_FALSE(layer.contains(QPoint(99, 99)));
}

// Accessors tests: GET ---------------------------

TEST(getSingle, GetOnEmptyLayer) {
    RasterLayer layer;
    auto pixelOpt = layer.get(QPoint(5, 5));
    EXPECT_FALSE(pixelOpt.has_value());
}

TEST(getSingle, GetExistingPixel) {
    RasterLayer layer;
    layer.upsert(QPoint(0, 0), QColor(0, 255, 0));
    auto pixelOpt = layer.get(QPoint(0, 0));
    ASSERT_TRUE(pixelOpt.has_value());
    EXPECT_EQ(pixelOpt->location, QPoint(0, 0));
    EXPECT_EQ(pixelOpt->value.get(), QColor(0, 255, 0));
}

TEST(getSingle, GetNonExistingPixel) {
    RasterLayer layer;
    layer.upsert(QPoint(1, 1), QColor(255, 0, 255));
    auto pixelOpt = layer.get(QPoint(2, 2));
    EXPECT_FALSE(pixelOpt.has_value());
}

TEST(getSingle, getReferenceTest) {
    RasterLayer layer;
    layer.upsert(QPoint(10, 10), QColor(255, 0, 0));
    auto pixelOpt = layer.get(QPoint(10, 10));
    ASSERT_TRUE(pixelOpt.has_value());
    // modify (should not change)
    pixelOpt->value.get() = QColor(0, 255, 0);
    EXPECT_EQ(layer.get(QPoint(10, 10))->value.get(), QColor(0, 255, 0));
}

// Accessory test: GETREGION ---------------------------

TEST(getRegion, NoPixelsInRegion) {
    RasterLayer layer;
    // No insertion => empty
    auto results = layer.get(0, 10, 0, 10);
    EXPECT_TRUE(results.isEmpty());
}

TEST(getRegion, SomePixelsInRegion) {
    RasterLayer layer;
    layer.upsert(QPoint(0, 0), QColor(10, 10, 10));
    layer.upsert(QPoint(5, 5), QColor(20, 20, 20));
    layer.upsert(QPoint(10, 10), QColor(30, 30, 30));
    layer.upsert(QPoint(20, 20), QColor(40, 40, 40));

    auto results = layer.get(0, 10, 0, 10);
    // expect (0,0), (5,5), (10,10)
    EXPECT_EQ(results.size(), 3);

    std::vector<QPoint> foundLocations;
    for (const auto &pix : results) {
        foundLocations.push_back(pix.location);
    }

    // Check that the points exist in the results
    EXPECT_NE(std::find(foundLocations.begin(), foundLocations.end(), QPoint(0, 0)), foundLocations.end());
    EXPECT_NE(std::find(foundLocations.begin(), foundLocations.end(), QPoint(5, 5)), foundLocations.end());
    EXPECT_NE(std::find(foundLocations.begin(), foundLocations.end(), QPoint(10, 10)), foundLocations.end());
}

TEST(getRegion, QRectNoPixels) {
    RasterLayer layer;
    QRect box(0, 0, 10, 10);
    auto results = layer.get(box);
    EXPECT_TRUE(results.isEmpty());
}

TEST(getRegion, QRectSomePixels) {
    RasterLayer layer;
    layer.upsert(QPoint(1, 1), QColor(111, 111, 111));
    layer.upsert(QPoint(9, 9), QColor(222, 222, 222));
    layer.upsert(QPoint(15, 15), QColor(100, 100, 100));

    QRect box(0, 0, 10, 10);
    auto results = layer.get(box);
    // We expect only (1,1) and (9,9) to be inside
    EXPECT_EQ(results.size(), 2);
}

// Mutators tests: CLEAR ---------------------------

TEST(clear, ClearEmptyLayer) {
    RasterLayer layer;
    layer.clear();  // Should not crash, remain empty
    EXPECT_EQ(layer.size(), 0);
    EXPECT_FALSE(layer.contains(QPoint(0, 0)));
}

TEST(clear, ClearNonEmptyLayer) {
    RasterLayer layer;
    layer.upsert(QPoint(-10, 5), QColor(128, 128, 128));
    layer.upsert(QPoint(0, 0), QColor(255, 255, 255));
    EXPECT_EQ(layer.size(), 2);

    layer.clear();
    EXPECT_EQ(layer.size(), 0);
    EXPECT_FALSE(layer.contains(QPoint(-10, 5)));
    EXPECT_FALSE(layer.contains(QPoint(0, 0)));
}

// Mutators tests: UPDATE ---------------------------

TEST(update, UpdateNonExistentPixel) {
    RasterLayer layer;
    layer.update(QPoint(10, 10), QColor(77, 77, 77));
    // No new insertion, size remains 0
    EXPECT_EQ(layer.size(), 0);
}

TEST(update, UpdateExistingPixel) {
    RasterLayer layer;
    layer.upsert(QPoint(5, 5), QColor(0, 0, 0));
    EXPECT_EQ(layer.size(), 1);

    layer.update(QPoint(5, 5), QColor(255, 0, 0));
    auto pixOpt = layer.get(QPoint(5, 5));
    ASSERT_TRUE(pixOpt.has_value());
    EXPECT_EQ(pixOpt->value.get(), QColor(255, 0, 0));

    // Size unchanged
    EXPECT_EQ(layer.size(), 1);
}

// Mutators tests: UPSERT ---------------------------

TEST(upsert, InsertNewPixel) {
    RasterLayer layer;
    layer.upsert(QPoint(0, 0), QColor(100, 50, 75));
    EXPECT_EQ(layer.size(), 1);
    EXPECT_TRUE(layer.contains(QPoint(0, 0)));
}

TEST(upsert, UpdateExistingPixel) {
    RasterLayer layer;
    layer.upsert(QPoint(1, 2), QColor(10, 10, 10));
    EXPECT_EQ(layer.size(), 1);

    // upsert again => should update color, not size
    layer.upsert(QPoint(1, 2), QColor(20, 20, 20));
    EXPECT_EQ(layer.size(), 1);

    auto pixOpt = layer.get(QPoint(1, 2));
    ASSERT_TRUE(pixOpt.has_value());
    EXPECT_EQ(pixOpt->value.get(), QColor(20, 20, 20));
}

// Mutators tests: REMOVE ---------------------------

TEST(remove, RemoveNonExistentPixel) {
    RasterLayer layer;
    layer.upsert(QPoint(1, 2), QColor(10, 10, 10));
    EXPECT_EQ(layer.size(), 1);

    layer.remove(QPoint(99, 99));
    // size unchanged
    EXPECT_EQ(layer.size(), 1);
}

TEST(remove, RemoveExistentPixel) {
    RasterLayer layer;
    layer.upsert(QPoint(-5, 0), QColor(100, 100, 100));
    EXPECT_TRUE(layer.contains(QPoint(-5, 0)));
    EXPECT_EQ(layer.size(), 1);

    layer.remove(QPoint(-5, 0));
    EXPECT_EQ(layer.size(), 0);
    EXPECT_FALSE(layer.contains(QPoint(-5, 0)));
}

// MEMORY LEAK TESTS ---------------------------
// NOTE: run these under a memory profiler.

TEST(MemoryLeak, InsertAndClearRepeatedly) {
    RasterLayer layer;
    for (int iteration = 0; iteration < 10; ++iteration) {
        for (int i = 0; i < 1000; ++i) {
            layer.upsert(QPoint(i, i), QColor(50, 50, 50));
        }
        layer.clear();
        EXPECT_EQ(layer.size(), 0);
    }
    SUCCEED();
}

