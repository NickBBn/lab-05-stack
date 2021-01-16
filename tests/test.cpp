// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "stack_light.hpp"

TEST(stack_light, push_lvalue) {
  int a = 23;
  int b = 17;
  stack_light<int> stack1;
  stack1.push(b);
  EXPECT_EQ(stack1.head(), b);
  stack1.push(a);
  EXPECT_EQ(stack1.head(), a);
}

struct example {
  int int_ex;
  char char_ex;
  bool operator==(const example& ex) const { // needed for EXPECT_EQ
    if ((ex.char_ex == char_ex)&&(ex.int_ex == int_ex)) return true;
    else return false;
  }
  example(const int& i, const char& c)
      : int_ex(i)
      , char_ex(c)
  {}/*
  example(const example& ex)
      : int_ex(ex.int_ex)
      , char_ex(ex.char_ex)
  { std::cout << "const example& ex" << std::endl; }
  example(example&& ex) noexcept
      : int_ex(ex.int_ex)
      , char_ex(ex.char_ex)
  { std::cout << "example&& ex" << std::endl; }*/
};

TEST(stack_light, push_rvalue) {
  example ex1{3, 'v'};
  example ex2{10, 't'};
  [[maybe_unused]] example ex3 = ex2;
  stack_light<example> stack1;
  stack1.push(ex1);
  EXPECT_EQ(stack1.head(), ex1);
  stack1.push(std::move(ex2));
  //stack1.push(std::forward<example&&>(ex2));
  EXPECT_EQ(stack1.head(), ex3);
}

TEST(stack_light, pop) {
  char a = 'a';
  stack_light<char> stack1;
  stack1.push(a);
  EXPECT_EQ(stack1.head(), 'a');
  stack1.push('u');
  EXPECT_EQ(stack1.head(), 'u');
  stack1.pop();
  EXPECT_EQ(stack1.head(), 'a');
}

TEST(stack_light, head_catch) {
  double e = 2.89;
  stack_light<double> stack1;
  EXPECT_THROW( stack1.head(), std::runtime_error);
  stack1.push(e);
  stack1.pop();
  EXPECT_THROW( stack1.head(), std::runtime_error);
}

TEST(stack_light, move_constructible) {
  int i = 293;
  stack_light<int> stack1;
  stack1.push(i);
  stack_light<int> stack2(std::move(stack1));
  EXPECT_EQ(stack2.head(), i);
  EXPECT_EQ(std::is_move_constructible<stack_light<int>>::value,true);
}

TEST(stack_light, move_assignable) {
  char i = 'q';
  stack_light<char> stack1;
  stack1.push(i);
  stack_light<char> stack2;
  stack2 = std::move(stack1);
  EXPECT_EQ(stack2.head(), i);
  EXPECT_EQ(std::is_move_assignable<stack_light<char>>::value,true);
}

TEST(stack_light, copy_prohibited) {
  EXPECT_EQ(std::is_copy_assignable<stack_light<char>>::value, false);
  EXPECT_EQ(std::is_copy_constructible<stack_light<char>>::value,false);
}

