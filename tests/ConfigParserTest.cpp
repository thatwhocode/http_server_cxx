#include <gtest/gtest.h>
#include "ConfigParser.h"
#include <fstream>
#include <cstdio>

class ConfigParserTest : public ::testing::Test {
protected:
    const std::string testFile = "test_config.conf";

    void SetUp() override {
        std::ofstream out(testFile);
        out << "port = 9090\n";
        out << "ip_address = 192.168.1.1\n";
        out << "# comment line\n";
        out << "   dirty_key  =  dirty_value   \n";
        out.close();
    }

    void TearDown() override {
        std::remove(testFile.c_str());
    }
};

TEST_F(ConfigParserTest, LoadAndReadValues) {
    ConfigParser config;
    bool loaded = config.load(testFile);
    
    ASSERT_TRUE(loaded);
    EXPECT_EQ(config.getInt("port"), 9090);
    EXPECT_EQ(config.getString("ip_address"), "192.168.1.1");
}

TEST_F(ConfigParserTest, HandleTrimAndComments) {
    ConfigParser config;
    config.load(testFile);
    
    EXPECT_EQ(config.getString("dirty_key"), "dirty_value");
}

TEST_F(ConfigParserTest, DefaultValues) {
    ConfigParser config; // Файл не завантажуємо
    
    EXPECT_EQ(config.getInt("port", 80), 80);
    EXPECT_EQ(config.getString("host", "localhost"), "localhost");
}