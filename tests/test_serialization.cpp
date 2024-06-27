#include <gtest/gtest.h>

#include "../utils/serialization.h"


class CustomObj {
private:
    int id;
    std::string name;

public:
    CustomObj() : id(0), name("") {}
    CustomObj(int id, std::string name) : id(id), name(name) {}

    // Getters for testing
    int getId() const { return id; }
    std::string getName() const { return name; }

};

TEST(TestSerialization, CustomObjectSerilization){
    CustomObj value(491981, "TestObjectString");

    std::string serialized_str = Serializer::serialize<CustomObj>(
        value, std::is_arithmetic<CustomObj>{}
    );
    CustomObj deserialized_obj = Serializer::deserialize<CustomObj>(
        serialized_str, std::is_arithmetic<CustomObj>{}
    );

    EXPECT_EQ(deserialized_obj.getId(), 491981);
    EXPECT_EQ(deserialized_obj.getName(), "TestObjectString");
}

TEST(TestSnapshot, RegularDataTypeSerialization){
    
}

int serialization_main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}