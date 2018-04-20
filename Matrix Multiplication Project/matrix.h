// matrix.h
// Zach Yuzon
// A simple basic implementation of a Matrix class
// February 8, 2018

#ifndef TEACH_CSCI335_MATRIX_H_
#define TEACH_CSCI335_MATRIX_H_

#include <iostream>
#include <vector>



// Make it a habit to use namespaces for your code.
namespace linear_algebra_project {

// Templated implementation of Matrix
// Sample usage:
//   Matrix<int> a;
//   a.ReadMatrix();
//   std::cout << a_matrix.NumRows() << std::endl;
//   std::cout << a_matrix.NumCols() << std::endl;
//   std::cout << a;
//   Matrix<int> b;
//   b.ReadMatrix();
//   std::cout << a + b;
template <typename Object>
class Matrix {
 public:
    
    // Matrix Constructor. Empty Constructor that assigns default values to private variables.
    Matrix() {
        num_rows_ = 0;
        num_columns_ = 0;
    };
    
    // Copy Constructor. Creates a Matrix as a copy of an exisiting Matrix.
    // @rhs: an existing Matrix.
    Matrix(const Matrix &rhs) {
        
        num_rows_ = rhs.NumRows();
        num_columns_ = rhs.NumCols();
        array_ = new Object*[num_rows_];            //allocates new memory for the rows of the new Matrix
        for(int i = 0; i < num_rows_; i++){         //allocates new memory for the columns of the new Matrix
            array_[i] = new Object[num_columns_];
        }
    
        for(int i = 0; i < num_rows_; i++){
            for(int j = 0; j < num_columns_; j++){
                array_[i][j] = rhs.array_[i][j];
            }
        }
    };
    
    // Copy assignment operator. Copies elements from the Matrix on the right-hand side to the Matrix on the left-hand side.
    // @rhs: an existing Matrix.
    // @returns this Matrix as a copy of rhs Matrix.
    Matrix& operator=(const Matrix &rhs) {
        num_rows_ = rhs.NumRows();
        num_columns_ = rhs.NumCols();
        
        //Avoid memory leak by deleting old elements
        for(int i = 0; i < num_rows_; i++){
            delete []array_[i];
        }
        delete []array_;
        
        array_ = new Object*[num_rows_];            //allocates new memory for the rows of the new Matrix
        for(int i = 0; i < num_rows_; i++){         //allocates new memory for the columns of the new Matrix
            array_[i] = new Object[num_columns_];
        }
        
        for(int i = 0; i < num_rows_; i++){
            for(int j = 0; j < num_columns_; j++){
                array_[i][j] = rhs.array_[i][j];
            }
        }
        
        return *this;
    };
    
    // Move Constructor. Transfers data from the r-value style Matrix rhs to this Matrix.
    // @rhs: an existing Matrix.
    Matrix(Matrix &&rhs) {
        num_rows_ = rhs.num_rows_;
        num_columns_ = rhs.num_columns_;
        
        array_ = new Object*[num_rows_];            //allocates new memory for the rows of the new Matrix object
        for(int i = 0; i < num_rows_; i++){         //allocates new memory for the columns of the new Matrix object
            array_[i] = new Object[num_columns_];
        }
        
        //copy data from rhs matrix to this matrix
        for(int i = 0; i < num_rows_; i++){
            for(int j = 0; j < num_columns_; j++){
                array_[i][j] = rhs.array_[i][j];
            }
        }
        for(int i = 0; i < rhs.num_rows_; i++){
            rhs.array_[i] = nullptr;
        }
        rhs.num_columns_ = 0;
        rhs. num_rows_ = 0;
        rhs.array_ = nullptr;
        
    };
    
    // Move Assignment Operator. Transfers a temporary Matrix object to this Matrix object.
    // @rhs: an existing Matrix.
    // @returns this Matrix after transferring data from rhs Matrix.
    Matrix& operator=(Matrix &&rhs) {
        
        if(this == &rhs){
            return *this;
        }
        std::swap(num_rows_,rhs.num_rows_);
        std::swap(num_columns_,rhs.num_columns_);
        std::swap(array_,rhs.array_);
        return *this;
    };
    
    
    //Destructor. Deletes all data from Matrix.
    ~Matrix(){
        for(int i = 0; i < num_rows_; i++){
            delete []array_[i];
        }
        delete []array_;
    };

    
  
    // ReadMatrix() gets input from the user and stores that data into this Matrix object.
    void ReadMatrix() {
        
        // deletes data in array_ if there is data that exists.
        if(num_rows_ != 0 && num_columns_ != 0){
            for(int i = 0; i < num_rows_; i++){
                for(int j = 0; j < num_columns_; j++){
                    delete []array_[i];
                }
            }
        
        delete []array_;
        }
        
        // gets input from user
        int rows, columns;
        Object value;
        std::cin >> rows >> columns;
        num_rows_ = rows;
        num_columns_ = columns;
        
        // allocates new memory for the rows of the new Matrix
        array_ = new Object*[num_rows_];
        for(int i = 0; i < num_rows_; i++){
            array_[i] = new Object[num_columns_];
        }
        
        // places values in array_
        for(int i = 0; i < num_rows_; i++){
            for(int j = 0; j < num_columns_; j++){
                std::cin >> value;
                array_[i][j] = value;
            }
        }
    }
    
    // @row: an index to a row of the matrix.
    // @returns the row as a vector of items. No error checking.
    // const version.
    std::vector<Object> operator[](int row) const{
        std::vector<Object> vec;
        for(int j = 0; j < num_columns_; j++){
            vec.push_back(array_[row-1][j]);
        }
        return vec;

    }

    // Adds two Matrices together.
    // @b_matrix: an existing Matrix.
    // @returns a Matrix containing values of the sum of the elements from b_matrix Matrix and the elements from this Matrix.
    Matrix operator+(const Matrix &b_matrix) {
        
        // check if Matrices can be added.
        if(num_rows_ != b_matrix.NumRows() || num_columns_ != b_matrix.NumCols()){
            std::cout << "Sizes do not match. Addition cannot be done." << std::endl;
            return *this;
        }
        
        
        // allocate memory for new Matrix
        Matrix new_matrix{b_matrix};
        new_matrix.num_rows_ = b_matrix.num_rows_;
        new_matrix.num_columns_ = b_matrix.num_columns_;
        new_matrix.array_ = new Object*[num_rows_];
        for(int i = 0; i < num_rows_; i++){         //allocates new memory for the columns of the new Matrix
            new_matrix.array_[i] = new Object[num_columns_];
        }
        
    
        //stores the values from b_matrix
        for(int i = 0; i < num_rows_; i++){
            for(int j = 0; j < num_columns_; j++){
                new_matrix.array_[i][j] = array_[i][j] + b_matrix.array_[i][j];
            }
        }
            return new_matrix;
    }
   
    //Adds Object to all elements of a Matrix
    // @an_object: an existing Object.
    // @returns a Matrix containing the values of the sum of an_Object and the elements of this Matrix
    Matrix operator+(const Object &an_object) {
        
        //Create a new matrix and Allocate memory to it.
        Matrix new_matrix;
        new_matrix.num_columns_ = num_columns_;
        new_matrix.num_rows_ = num_rows_;
        new_matrix.array_ = array_;
        new_matrix.array_ = new Object*[num_rows_];
        for(int i = 0; i < num_rows_; i++){         //allocates new memory for the columns of the new Matrix
            new_matrix.array_[i] = new Object[num_columns_];
        }
        
        //Perform the addition in the new matrix
        for(int i = 0; i < num_rows_; i++){
            for(int j = 0; j < num_columns_; j++){
                new_matrix.array_[i][j] = array_[i][j] + an_object;
            }
        }
        return new_matrix;
    }

    // @returns number of rows.
    size_t NumRows() const {
      return num_rows_;
    }
    // @returns number of columns.
    size_t NumCols() const {
      return num_columns_;
    }

    // Overloading the << operator.
    // @out: passed in the ostream in order to take in the input.
    // @a_matrix: an existing Matrix
    // @returns
    friend std::ostream &operator<<(std::ostream &out, const Matrix &a_matrix) {
        out << "[";
        for(int i = 0; i < a_matrix.NumRows(); i++){
            for(int j = 0; j < a_matrix.NumCols(); j++){
                out <<  a_matrix.array_[i][j];
                if(j != a_matrix.NumCols() - 1)
                    out << " ";
            }
            if(i == a_matrix.NumRows() - 1){
                out << "]" << std::endl;
            }
            out << std::endl;
        }
        return out;
    }

 private:
    size_t num_columns_;
    size_t num_rows_;
    Object **array_;
};

}  // namespace linear_algebra_project

#endif  // TEACH_CSCI335_MATRIX_H


