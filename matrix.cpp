#include <iostream>
//#include <random>
//#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <vector>
using namespace std;

//Constants/Defines:
//#define NUM_THREADS 5;

typedef struct param_struct {
  int i;
  int j;

} param_t;

//Global Variables:
int m1_row, m2_row;
int m1_col, m2_col;
int* mm1;
//int **mm1 = malloc(sizeof(m1_row * m2_col));
param_t* param = (param_t*)malloc(sizeof(param_t));

//Functions:
//func1 does...
//void func1() {

//}

//param_t* param = (param_t*)malloc(sizeof(param_t));

int** create_matrix(int i, int j) {
  //  int (*arr)[mm1] = malloc(sizeof(int[i][j]));
  // int ** ptr = static_cast<int*>(malloc(i*j*sizeof(int)));

  int ** ptr = new int*[m1_row];

  for (int i = 0; i < m1_row; i++) {
    ptr[i] = new int[m2_col];
  }
  
    //  for (int i = 0; i < param; i++) {
  //mm1[i] = malloc(param * sizeof(int));
  //  }
}

void* print_message_function (void *ptr) {
  cout << "in print function" << endl;

  for (int i = 0; i < m1_col; i++){
    //    mm1[param -> i][i];
    cout << "here5" << endl;
    //    cout << mm1[ptr -> i] << endl;       //*******void is not a pointer to object type error;

    //   cout << mm1[param -> i] << endl;
  }
    //  } param_t;
  //  int* mm1;


  //mm1[i]
  param = (param_t*) ptr;

  printf("i=%d,j=%d\n",param->i,param->j);
  // return 0;
}

//Main:
int main() {

//Variables needed for main:
//  int m1_row, m2_row, m1_col, m2_col = 0;
  bool again = true;
  pthread_t thread1, thread2;
  char *message1 = "Thread 1";
  char *message2 = "Thread 2";
  int num_threads;


//1) prompt user to input the sizes of two matricies:

  while (again) {
    cout << "Enter how many rows matrix one will contain: ";
    cin >> m1_row;
    cout << "Enter how many columns matrix one will contain: ";
    cin >> m1_col;
    cout << "Enter how many rows matrix two will contain: ";
    cin >> m2_row;
    cout << "Enter how many columns matrix two will contain: ";
    cin >> m2_col;

    num_threads = (m1_row * m2_col);

  //2) program verifies that it can actually multiple the two matricies (# of rows in matrix 1 matches # of columns in\
 matrix 2);

    if (m1_row != m2_col) {
      cout << "Try again. The number of rows in the first matrix needs to match the number of columns in the second \
matrix.";
      cout << " " << endl;
    }

    else {
      again = false;
      cout << endl;
    }
  }

  cout << endl;

//3) The program fills both matricies with random numbers and prints them to the screen;

  srand(time(0));

  int m1[m1_row][m1_col];
  int m2[m2_row][m2_col];
  int result[m1_row][m2_col];

  // int* mm1 = malloc();

  cout << "Matrix One: " << endl;
  for (int i = 0; i < m1_row; i++) {
    for (int j = 0; j < m1_col; j++) {
      m1[i][j] = (rand() % 10);
      cout << m1[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  cout << "Matrix Two: " << endl;
  for (int i = 0; i < m2_row; i++) {
    for (int j = 0; j < m2_col; j++) {
      m2[i][j] = (rand() % 10);
      cout << m2[i][j] << " ";
      //      result += (m1[i]) + m2[j]; //* m2[j]);
    }
    cout << endl;
  }
  cout << endl;

  //  cout << "total result: " << result << endl;

//4)Use pthreads to parallelize the matrix multiplication and dot product result matrix generation:
    //-Each row and column dot product process should be handled by an individual thread, in parallel;
    //-Once all threads have finished, the final result matrix can be printed to the screen;

  //a new thread should be generated for each resulting matrix square;
  //so if matrix 1 is 2x3, and matrix 2 is 3x2, resulting matrix is 2x2;
  //meaning 4 threads should be created and multiplying the rows by columns to get the solution;

  //  int *message;
  //  pthread_t thread;
  //  int iret;

  pthread_t thread[m1_row][m2_col];

  for (int i = 0; i < m1_row; i++) {
    for (int j = 0; j < m2_col; j++) {
    //  pthread_t thread[i];
    // int iret[i];

      cout << "here2" << endl;

      param_t* param = (param_t*)malloc(sizeof(param_t));
      param -> i = i;
      param -> j = j;

      //      pthread_create(&thread[i][j], NULL, print_message_function, (void*) param);
      //pthread_join(thread[i], NULL);
      cout << "here3" << endl;
    }
  }

  /*  for (int i = 0; i < m1_row; i++) {
    for (int j = 0; j < m2_col; j++) {
            cout << "here4" << endl;
            //pthread_join(thread[i], NULL);
      pthread_join(thread[i][j], NULL);
      //cout << i << endl;
    }
  }
  */

  int** mm1 = create_matrix(m1_row, m2_col);
  //  cout << print_message_function(param) << endl;
  cout << print_message_function(mm1) << endl;

  cout << "program ending" << endl;

//return:
  return 0;
}

