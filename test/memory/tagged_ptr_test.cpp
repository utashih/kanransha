#include "memory/tagged_ptr.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

GTEST_TEST(tagged_ptr_test, sanity_test) {
  kanransha::tagged_ptr<int> ptr0;

  ASSERT_EQ(ptr0.address(), nullptr);
  ASSERT_EQ(ptr0.tag(), 0);

  int local = 0;
  kanransha::tagged_ptr<int> ptr1(&local);

  ASSERT_EQ(ptr1.address(), &local);
  ASSERT_EQ(ptr1.tag(), 0);

  kanransha::tagged_ptr<int> ptr2(&local, 1);

  ASSERT_EQ(ptr2.address(), &local);
  ASSERT_EQ(ptr2.tag(), 1);
}

int main(int argc, char *argv[]) {
  ::google::InitGoogleLogging(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}