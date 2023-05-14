#include <gtest/gtest.h>
#include <string>
#include "ORM.hpp"
#include "DatabaseMOCK.hpp"

const std::string SUCCECTION_MESSAGE = "The request is correct!";

TEST(ORMTest, SelectCase_table)
{
    std::string DB_work_result = DatabaseMOCK::execute("SELECT *\nFROM table;");
    ORM::Select("table");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, SelectCase_another_table)
{
    std::string DB_work_result = DatabaseMOCK::execute("SELECT *\nFROM table;");
    ORM::Select("another_table");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, FilterCase_table_predicate)
{
    std::string DB_work_result = DatabaseMOCK::execute("SELECT *\nFROM table WHERE predicate;");
    ORM::Filter("table", "predicate");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, FilterCase_another_table_and_predicate)
{
    std::string DB_work_result = DatabaseMOCK::execute("SELECT *\nFROM table WHERE predicate;");
    ORM::Filter("another_table", "predicate");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, FilterCase_table_and_another_predicate)
{
    std::string DB_work_result = DatabaseMOCK::execute("SELECT *\nFROM table WHERE predicate;");
    ORM::Filter("table", "another_predicate");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, FilterCase_another_table_and_another_predicate)
{
    std::string DB_work_result = DatabaseMOCK::execute("SELECT *\nFROM table WHERE predicate;");
    ORM::Filter("another_table", "another_predicate");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, FindCase_table_and_object_id1)
{
    std::string DB_work_result = DatabaseMOCK::execute("SELECT *\nFROM table WHERE object_id = 1;");
    ORM::Find("table", "1");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, FindCase_another_table_and_object_id1)
{
    std::string DB_work_result = DatabaseMOCK::execute("SELECT *\nFROM table WHERE object_id = 1;");
    ORM::Find("another_table", "1");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, FindCase_table_and_object_id2)
{
    std::string DB_work_result = DatabaseMOCK::execute("SELECT *\nFROM table WHERE object_id = 1;");
    ORM::Find("table", "2");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, FindCase_another_table_and_object_id2)
{
    std::string DB_work_result = DatabaseMOCK::execute("SELECT *\nFROM table WHERE object_id = 1;");
    ORM::Find("another_table", "2");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, DeleteCase_table_and_object_id1)
{
    std::string DB_work_result = DatabaseMOCK::execute("DELETE *\nFROM table WHERE object_id = 1;");
    ORM::Delete("table", "1");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, DeleteCase_another_table_and_object_id1)
{
    std::string DB_work_result = DatabaseMOCK::execute("DELETE *\nFROM table WHERE object_id = 1;");
    ORM::Delete("another_table", "1");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, DeleteCase_table_and_object_id2)
{
    std::string DB_work_result = DatabaseMOCK::execute("DELETE *\nFROM table WHERE object_id = 1;");
    ORM::Delete("table", "2");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, DeleteCase_another_table_and_object_id2)
{
    std::string DB_work_result = DatabaseMOCK::execute("DELETE *\nFROM table WHERE object_id = 1;");
    ORM::Delete("another_table", "2");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, InsertCase_table_and_object)
{
    std::string DB_work_result = DatabaseMOCK::execute("INSERT INTO table\nVALUES object;");
    ORM::Insert("table", "object");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, InsertCase_another_table_and_object)
{
    std::string DB_work_result = DatabaseMOCK::execute("INSERT INTO table\nVALUES object;");
    ORM::Insert("another_table", "object");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, InsertCase_table_and_another_object)
{
    std::string DB_work_result = DatabaseMOCK::execute("INSERT INTO table\nVALUES object;");
    ORM::Insert("table", "another_object");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, InsertCase_another_table_and_another_object)
{
    std::string DB_work_result = DatabaseMOCK::execute("INSERT INTO table\nVALUES object;");
    ORM::Insert("another_table", "another_object");
    EXPECT_EQ(DB_work_result, SUCCECTION_MESSAGE);
}

TEST(ORMTest, UpdateCase_table_and_object)
{
    std::string DB_work_result = DatabaseMOCK::execute("UPDATE table\nSET object;");
    ORM::Update("table", "object");
    EXPECT_EQ(DatabaseMOCK::execute("UPDATE table\nSET object;"), SUCCECTION_MESSAGE);
}

TEST(ORMTest, UpdateCase_another_table_and_object)
{
    std::string DB_work_result = DatabaseMOCK::execute("UPDATE table\nSET object;");
    ORM::Update("another_table", "object");
    EXPECT_EQ(DatabaseMOCK::execute("UPDATE table\nSET object;"), SUCCECTION_MESSAGE);
}

TEST(ORMTest, UpdateCase_table_and_another_object)
{
    std::string DB_work_result = DatabaseMOCK::execute("UPDATE table\nSET object;");
    ORM::Update("table", "another_object");
    EXPECT_EQ(DatabaseMOCK::execute("UPDATE table\nSET object;"), SUCCECTION_MESSAGE);
}

TEST(ORMTest, UpdateCase_another_table_and_another_object)
{
    std::string DB_work_result = DatabaseMOCK::execute("UPDATE table\nSET object;");
    ORM::Update("another_table", "annother_object");
    EXPECT_EQ(DatabaseMOCK::execute("UPDATE table\nSET object;"), SUCCECTION_MESSAGE);
}
