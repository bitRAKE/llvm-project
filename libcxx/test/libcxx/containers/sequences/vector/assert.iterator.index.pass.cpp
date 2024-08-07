//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <vector>

// Index iterator out of bounds.

// REQUIRES: has-unix-headers, libcpp-has-abi-bounded-iterators-in-vector
// UNSUPPORTED: libcpp-hardening-mode=none, c++03

#include <vector>
#include <cassert>

#include "check_assertion.h"
#include "fill_to_capacity.h"
#include "min_allocator.h"

int main(int, char**) {
  {
    typedef int T;
    typedef std::vector<T> C;
    C c(1);
    fill_to_capacity(c);
    C::iterator i = c.begin();
    assert(i[0] == 0);
    TEST_LIBCPP_ASSERT_FAILURE(
        i[c.size()], "__bounded_iter::operator[]: Attempt to index an iterator at or past the end");
    TEST_LIBCPP_ASSERT_FAILURE(
        i[c.size() + 1], "__bounded_iter::operator[]: Attempt to index an iterator at or past the end");
  }

  {
    typedef int T;
    typedef std::vector<T, min_allocator<T> > C;
    C c(1);
    fill_to_capacity(c);
    C::iterator i = c.begin();
    assert(i[0] == 0);
    TEST_LIBCPP_ASSERT_FAILURE(
        i[c.size()], "__bounded_iter::operator[]: Attempt to index an iterator at or past the end");
    TEST_LIBCPP_ASSERT_FAILURE(
        i[c.size() + 1], "__bounded_iter::operator[]: Attempt to index an iterator at or past the end");
  }

  return 0;
}
