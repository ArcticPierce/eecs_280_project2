#include <cassert>
#include <fstream>
#include "Matrix.hpp"

// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {
  int matrix_height = height;
  int matrix_width = width;
  assert(matrix_height >= 0 || matrix_width >= 0);
  std::vector<int> matrix(height * width, 0);
  mat -> data = matrix;
};




// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  os << "WIDTH "<< mat -> width << "HEIGHT " << mat -> height;
  int total_length = 0;
  for (int i = 0; i < mat -> height; i++){
    os << endl;
    for(int j = 0; j < mat -> width; j++){
      os << mat ->data[total_length] << " ";
      total_length++;
    }
  }

}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return mat -> width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat -> height;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(0 <= row && row < mat->height);
  assert(0 <= column && column < mat->width);
  int x = (row * mat->width) + column;
  return &(mat->data[x]);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(0 <= row && row < mat->height);
  assert(0 <= column && column < mat->width);
  int x = (row * mat->width) + column;
  const int* val = &(mat->data[x]);
  return val;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  for(int i = 0; i < mat->width;i++) {
    for(int j = 0; i < mat->height;j++){
      *Matrix_at(mat,i,j) = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  for(int i = 0; i < mat->width;i++) {
    if(i = 0) {
      *Matrix_at(mat,i,0) = value;
    }
    else if(i = mat->width - 1) {
      *Matrix_at(mat,i,mat->width - 1) = value;
    }
    for(int j = 0; i < mat->height;j++){
      if(j = 0) {
        *Matrix_at(mat,0,j) = value;
      }
      else if(j = mat->height - 1) {
        *Matrix_at(mat,i,j) = value;
      }
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int max = mat->data[0];
  for (int i = 0; i < mat->data.size(); i++) {
    if (max < mat->data[i]) {
      max = mat->data[i];
    }
  }
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row, int column_start, int column_end) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);
  int min = *Matrix_at(mat,row,column_start);
  int min_column;
  for (int i = 0; i < column_end - column_start; i++) {
    if(min > *Matrix_at(mat,row,column_start + i)){
      min = *Matrix_at(mat,row,column_start + i);
      min_column = column_start + i;
    }
  }
  return min_column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row, int column_start, int column_end) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);
  int min = *Matrix_at(mat,row,column_start);
  for (int i = 0; i < column_end - column_start; i++) {
    if(min > *Matrix_at(mat,row,column_start + i)){
      min = *Matrix_at(mat,row,column_start + i);
    }
  }
  return min;
}
