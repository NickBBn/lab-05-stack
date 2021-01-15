// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "stack_light.hpp"

TEST(stack_light, push_lvalue) {
  int a = 23;
  stack_light<int> stack1(17);
  EXPECT_EQ(stack1.head(), 17);
  stack1.push(a);
  EXPECT_EQ(stack1.head(), 23);
}

struct example {
  int int_ex;
  char char_ex;
  bool operator==(const example ex) const {
    if ((ex.char_ex == char_ex)&&(ex.int_ex == int_ex)) return true;
    else return false;
  }
  example& operator=(const example& ex){
    char_ex = ex.char_ex;
    int_ex = ex.int_ex;
    return *this;
  }
  example(){}
  example(const int& i, const char& c)
      : int_ex(i)
      , char_ex(c)
  {}
  example(const example& ex) {
    int_ex = ex.int_ex;
    char_ex = ex.char_ex;
  }
  example(example&& ex)  noexcept {
    int_ex = ex.int_ex;
    char_ex = ex.char_ex;
  }
};

TEST(stack_light, push_rvalue) {
  example ex1{3, 'v'};
  example ex2{10, 't'};
  [[maybe_unused]] example ex3 = ex2;
  stack_light<example> stack1(ex1);
  EXPECT_EQ(stack1.head(), ex1);
  stack1.push(std::move(ex2));
  EXPECT_EQ(stack1.head(), ex3);
}

TEST(stack_light, pop) {
  stack_light<char> stack1('a');
  EXPECT_EQ(stack1.head(), 'a');
  stack1.push('u');
  EXPECT_EQ(stack1.head(), 'u');
  stack1.pop();
  EXPECT_EQ(stack1.head(), 'a');
}

TEST(stack_light, head_catch) {
  stack_light<double> stack1(2.89);
  stack1.pop();
  EXPECT_THROW( stack1.head(), std::runtime_error);
}