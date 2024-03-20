#include <gtest/gtest.h>

#include <cppfetch/core.hpp>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(CoreTest, Getters) {
    cppfetch::cppfetch downloader;
    ASSERT_TRUE(downloader.get_files_list().size() == 0);

    downloader.add_file("test");
    ASSERT_TRUE(downloader.get_files_list().size() == 1);
    EXPECT_EQ("test", downloader.get_files_list()[0]);
}

TEST(CoreTest, Setters) {

}

TEST(CoreTest, Methods) {
    
}