//Operating Systems - CS444;
//Spring 2023;
//Christian Soucy;
//Assignment Info: Matrix Multiplication (Threading), Due 02/19/2023;
//Program Description: Using the pthreads library to perform matrix multiplication;
//Last modified: 02/19/2023, 9:18 pm;
//Youtube Code Review & Demo Link: https://youtu.be/GV91zWLiR_M

//Includes/Namespace://
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <vector>
using namespace std;

//This struct holds the data for each element in the resulting matrix;
typedef struct param_struct {
  int i; //represents the row of the resulting matrix;
  int j; //represents the column of the resulting matrix;
} param_t;


//Global Variables://
int m1_row, m2_row; //row variables for the two randomly generated arrays;
int m1_col, m2_col; //col variables for the two randomly generated arrays;
int **mm1, **mm2, **result; //variables to generate the two arrays, as well as the resulting array;


//Functions://
//this function takes the rows/columns of the matrix to generate the array, so it is able to be printed to the terminal;
int **create_matrix(int rows, int cols) {
  int **ptr = new int *[rows]; //creating a pointer that points to a pointer of the rows in the matrix;

  for (int i = 0; i < rows; i++) { //increments through the # of rows in the matrix;
    ptr[i] = new int[cols]; //assigns the row value of the pointer to a column value;
  }

  return ptr; //returns the pointer;
}


//this function takes the ptr returned from the create_matrix function and multiplies the two matricies together;
//then, the resulting dot product matrix produced is printed to the terminal;
void* threading_func (void *ptr) {
  param_t *param = (param_t *) ptr; //setting the variable param equal to the value of the pointer;

  for (int k = 0; k < m1_col; k++) { //increments through the # of columns of the first matrix;
    result[param -> i][param -> j] += mm1[param -> i][k] * mm2[k][param -> j]; //calculates the dot product, and sets that value equal to the resulting matrix, so it can be printed out later;
  }

  pthread_exit(0); //exits the threads after they're done being used, cleanup and destructor runs;
}


//Main Function://
int main() {
//Variables needed for main:
  bool again = true; //variable incase the user inputs the matricies incorrectly;
  int num_threads; //used to determine how many threads are needed to generate resulting matrix;

//1) prompt user to input the sizes of two matricies:
  while (again) { //while loop incase user incorrectly inputs matrix sizes:
    cout << "Enter how many rows matrix one will contain: ";
    cin >> m1_row; //user inputs how many rows they want the first matrix to have;
    cout << "Enter how many columns matrix one will contain: ";
    cin >> m1_col; //user inputs how many columns they want the first matrix to have;
    cout << "Enter how many rows matrix two will contain: ";
    cin >> m2_row; //user inputs how many rows they want the second matrix to have;
    cout << "Enter how many columns matrix two will contain: ";
    cin >> m2_col; //user inputs how many columns they want the second matrix to have;

    num_threads = (m1_row * m2_col); //calculates how many threads are needed;


//---------------------------------------------------------------------------------
//2) program verifies that it can actually multiple the two matricies (# of rows in matrix 1 matches # of columns in matrix 2);

    if (m1_row != m2_col) { //checks if user incorrectly inputs matrix sizes;
      cout << "Try again. The number of rows in the first matrix needs to match the number of columns in the second matrix.";
      cout << " " << endl;
    }

    else {
      again = false; //if matrix sizes were incorrect, this makes the while run again until they input the correct sizes
      cout << endl;
    }
  }
  cout << endl;


//---------------------------------------------------------------------------------
//3) The program fills both matricies with random numbers and prints them to the screen;

  srand(time(0)); //checks the current time to produce psuedo-random numbers for the STL rand() function;
  
  mm1 = create_matrix(m1_row, m1_col); //generates the structure for the first matrix;
  mm2 = create_matrix(m2_row, m2_col); //generates the structure for the second matrix;
  result = create_matrix(m1_row, m2_col); //generates the structure for the resulting matrix;

  cout << "Matrix One: " << endl;
  for (int i = 0; i < m1_row; i++) { //increments through the number of rows of the first matrix;
    for (int j = 0; j < m1_col; j++) { //increments through the number of columns of the first matrix;
      mm1[i][j] = (rand() % 10); //generates numbers using the rand() function to fill the first matrix;
      cout << mm1[i][j] << " "; //outputs the resulting matrix to the terminal;
    }
    cout << endl; //after every row is printed, the next line is printed, thus generating the columns;
  }
  cout << endl;

  cout << "Matrix Two: " << endl;
  for (int i = 0; i < m2_row; i++) { //increments through the number of rows of the second matrix;
    for (int j = 0; j < m2_col; j++) { //increments through the number of columns of the second matrix;
      mm2[i][j] = (rand() % 10); //generates numbers using the rand() function to fill the second matrix;
      cout << mm2[i][j] << " "; //outputs the resulting matrix to the terminal;
    }
    cout << endl; //after every row is printed, the next line is printed, thus generating the columns;
  }
  cout << endl;

//---------------------------------------------------------------------------------
//4)The program uses pthreads to parallelize the matrix multiplication/dot product result matrix generation:

   pthread_t resulting_thread[m1_row][m2_col]; //thread that multiplies the two matricies together to create the resulting matrix;

  for (int i = 0; i < m1_row; i++) { //increments through the number of rows of the first matrix;
    for (int j = 0; j < m2_col; j++) { //increments through the number of columns of the second matrix;
      param_t *param = (param_t *)malloc(sizeof(param_t)); //allocates memory  to the resulting matrix using malloc()
      param -> i = i; //dereferencing the pointer from the struct to i;
      param -> j = j; //dereferencing the pointer from the struct to j;

      //creates a thread for each dot product of the two given matricies:
      pthread_create(&resulting_thread[i][j], NULL, threading_func, (void *) param);
    }
  }

  for (int i = 0; i < m1_row; i++) { //increments through the number of rows of the first matrix;
    for (int j = 0; j < m2_col; j++) { //increments through the number of columns of the second matrix;
      pthread_join(resulting_thread[i][j], NULL); //joins the thread, prints any errors that occurs within thread generation;
    }
  }

  cout << "Resulting matrix: " << endl;
  for (int i = 0; i < m1_row; i++) { //increments through the # of rows in the first matrix;
    for (int j = 0; j < m2_col; j++) { //increments through the # of columns in the second matrix;
      cout << result[i][j] << " "; //outputs the resulting matrix to the terminal;
    }
    cout << endl; //after every row is printed, the next line is printed, thus generating the columns;
  }
  cout << endl;
  
//Return://
  return 0;
}

