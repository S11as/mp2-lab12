
#include <gtest.h>
#include <TTextFactory.h>

TEST(Text, can_build_and_run_sample_test)
{
    char *s = "hello world\nit is rainy today\\pabye world";
    ASSERT_NO_THROW(TTextFactory::create(s));
}

TEST(TextIterator, go_next_char)
{
    char *s = "hello world\nit is rainy today\\pabye world";
    char *test = "hello";
    TText* text = TTextFactory::create(s);
    TTextIterator i = text->begin();
    for (int j = 0; j < 5; ++j) {
        i.go_next_char();
        EXPECT_EQ(i.get()->get_c(), test[j]);
    }
}

TEST(TextIterator, go_next_level)
{
    char *s = "hello world\nit is rainy today\\pabye world";
    TText* text = TTextFactory::create(s);
    TTextIterator i = text->begin();
    for (int j = 0; j < 5; ++j) {
        EXPECT_EQ(i.get()->get_level(), static_cast<NodeLevel>(4-j));
        i.go_next();
    }
}

TEST(TextIterator, reset_to)
{
    char *s = "hello world\nit is rainy today\\pabye world";
    TText* text = TTextFactory::create(s);
    TTextIterator i = text->find(NodeLevel::WORD, "it");
    for (int j = 0; j < 5; ++j) {
        i.reset_to(static_cast<NodeLevel>(j));
        EXPECT_EQ(i.get()->get_level(), static_cast<NodeLevel>(j));
    }
}

TEST(Text, find_char){
    char *s = "hello world\nit is rainy today\\pabye world";
    TText* text = TTextFactory::create(s);
    TTextIterator i = text->find('i');
    EXPECT_EQ(i.get()->get_c(), 'i');
}

TEST(Text, find_sequence){
    char *s = "hello world\nit is rainy today\\pabye world";
    TText* text = TTextFactory::create(s);
    char *sequence = "itis";
    int len = strlen(sequence);
    TTextIterator i = text->find(sequence);
    for (int j = 0; j < len; ++j) {
        EXPECT_EQ(i.get()->get_c(), sequence[j]);
        i.go_next_char();
    }
}

TEST(Text, find_word){
    char *s = "hello world\nit is rainy today\\pabye world";
    TText* text = TTextFactory::create(s);
    char *sequence = "rainy";
    int len = strlen(sequence);
    TTextIterator i = text->find(NodeLevel::WORD, sequence);
    i.go_next_char();
    for (int j = 0; j < len; ++j) {
        EXPECT_EQ(i.get()->get_c(), sequence[j]);
        i.go_next_char();
    }
}

TEST(Text, insert_word){
    char *s = "hello world\nit is rainy today\\pabye world";
    TText* text = TTextFactory::create(s);
    char *sequence = "rainydaytoday";
    int len = strlen(sequence);
    TTextIterator i = text->find(NodeLevel::WORD, "rainy");
    text->insert("day", i);
    TTextIterator j = text->find(NodeLevel::WORD, "day");
    i.go_next_char();
    for (int j = 0; j < len; ++j) {
        EXPECT_EQ(i.get()->get_c(), sequence[j]);
        i.go_next_char();
    }
}

TEST(Text, delete_word){
    char *s = "hello world\nit is rainy today\\pabye world";
    TText* text = TTextFactory::create(s);
    char *sequence = "world";
    int len = strlen(sequence);
    TTextIterator i = text->begin();
    text->_delete(28,i);
    i.go_next_char();
    for (int j = 0; j < len; ++j) {
        EXPECT_EQ(i.get()->get_c(), sequence[j]);
        i.go_next_char();
    }
}

TEST(Text, copy_word){
    char *s = "hello world\nit is rainy today\\pabye world";
    TText* text = TTextFactory::create(s);
    TTextIterator i = text->begin();
    char *g = text->copy(10, i);
    char *sequence = "hello world\n";
    int len = strlen(sequence);
    for (int j = 0; j < len; ++j) {
        EXPECT_EQ(g[j], sequence[j]);
    }
}