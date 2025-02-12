#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  /*const int width = 3;
  const int height = 5;*/ // never used these variables
  const int value = 42;
  Matrix_init(&mat, 4, 4);
  Matrix_fill(&mat, value);
  Matrix_fill_border(&mat,99);

  ostringstream s;
  Matrix_print(&mat, s);
  ostringstream correct("4 4\n99 99 99 99 \n99 42 42 99 \n99 42 42 99 \n99 99 99 99 \n");

  ASSERT_EQUAL(s.str(), correct.str());
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,3,0,4),0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,1,0,4),1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,3,2,3),2);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat,2,0,4),42);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat,2,0,1),99);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat,3,0,4),99);

  /*for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
  }*/ // this test fails because we change the border and such
}

TEST(test_matrix_max) {
  Matrix mat1;
  Matrix_init(&mat1, 3, 4);
  Matrix_fill(&mat1,0);
  *Matrix_at(&mat1, 0, 0) = 5;

  ASSERT_EQUAL(Matrix_max(&mat1) ,5);
  *Matrix_at(&mat1, 0, 0) = 0;

  *Matrix_at(&mat1, 2,3) = 10;
  ASSERT_EQUAL(Matrix_max(&mat1), 10);
  *Matrix_at(&mat1, 2,3) = 0;

  *Matrix_at(&mat1, 0, 2) = 20;
  ASSERT_EQUAL(Matrix_max(&mat1), 20);
  *Matrix_at(&mat1, 0, 2) = 0;

  *Matrix_at(&mat1, 0, 1) = -20;
  ASSERT_EQUAL(Matrix_max(&mat1), 0);
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
