#include<stdio.h>
#include<string.h>

// add error code declarations here
int MAX_DIMENSION_LIMIT_EXCEEDED = 0;
int DIMENSION_ZERO_ERROR = 0;
int NO_PRODUCT_POSSIBLE = 0;

// end of error code declaration

#define MAX 5

typedef struct Matrix
{
	int rows;
	int cols;
	// The type of current Matrix: Can be 'Horizontal', 'Vertical', 'Square'
	// 'Row', or 'Column'
	char type[10];
	int mat[MAX][MAX];
} Matrix;

int ExceptionalOccurances(){
	/*
		If any exception is to be handeled, we can use this function as follows: the main() function must be alerted
		about any error that has occured while running a particular function. It knows about any such error
		through the value returned by this function: which is 0 if there is no error and >0 otherwise.
		
		To handle errors of your own:
		-> create a global 'int' and give it a sensible name; initialize it to 0;
		-> within the scope demanding the corresponding exception handeling, update that global variable to 1; and finally,
		-> add another if-statement in this function to update the value of 'except' to 1 for that error
	*/	
	int except=0;
	
	if(MAX_DIMENSION_LIMIT_EXCEEDED)
		except = 1;
	if(DIMENSION_ZERO_ERROR)
		except = 1;
	if(NO_PRODUCT_POSSIBLE)
		except = 1;
		
	return except;
}

void resetAllErrors(){
	/*
		For continued operation of the program until the user queries an exit code,
		the error codes must be reset whenever main() function calls for it
	*/

	MAX_DIMENSION_LIMIT_EXCEEDED = 0;
	DIMENSION_ZERO_ERROR = 0;
	NO_PRODUCT_POSSIBLE = 0;
}

void initializeMatrix(Matrix *matrix,int rows,int cols){
	matrix->rows = rows;
	matrix->cols = cols;
}

int newMatrix(Matrix *matrix, int m, int n){
	//For easy Matrix entry error handling, this function returns 1 if any entry level error occurs, and 0 otherwise
	
	int i, j;

	// Error is reset on a new function call
	resetAllErrors();

	matrix->rows = m;
	matrix->cols = n;
	
	if(matrix->rows>MAX || matrix->cols>MAX){
		MAX_DIMENSION_LIMIT_EXCEEDED = 1;
		printf("Maximum dimension limit exceeded!");
		return 1;
	}

	if(matrix->rows==0 || matrix->cols==0){
		DIMENSION_ZERO_ERROR = 1;
		printf("Dimensions must be such that 'm' and 'n' are Natural Numbers\n");
		return 1;
	}
	
	printf("Enter the Matrix:\n");
	for(i=0; i<matrix->rows; ++i){
		for(j=0; j<matrix->cols; ++j){
			scanf("%d", &matrix->mat[i][j]);
		}
	}
	
	return 0;
}

void showMatrix(Matrix *matrix){
	int i, j;
	
	if(matrix->rows>1 && matrix->cols>1){
		for(i=0; i<matrix->rows; ++i){
			for(j=0; j<matrix->cols; ++j){
				if(j==0){
					if(i==0)
						printf("\t%c%-7d", 218, matrix->mat[i][j]);
					else if(i==matrix->rows-1)
						printf("\t%c%-7d", 192, matrix->mat[i][j]);
					else
						printf("\t%c%-7d", 179, matrix->mat[i][j]);
				}
						
				else if(j==matrix->cols-1){
					if(i==0)
						printf("\t%7d%c", matrix->mat[i][j], 191);
					else if(i==matrix->rows-1)
						printf("\t%7d%c", matrix->mat[i][j], 217);
					else
						printf("\t%7d%c", matrix->mat[i][j], 179);
				}
					
				else
					printf("\t%d", matrix->mat[i][j]);
			}
			
			printf("\n");
		}
	}
	
	else if(matrix->rows==1 && matrix->cols>1){
		printf("\t[");
		for(i=0; i<matrix->cols; ++i){
			if(i!=matrix->cols-1)
				printf("%d\t", matrix->mat[0][i]);
			else
				printf("%d", matrix->mat[0][i]);
		}
		printf("]\n");
	}
	
	else{
		for(i=0; i<matrix->rows; ++i){
			if(i==0)
				printf("\t%c\t%d\t%c\n", 218, matrix->mat[i][0], 191);
			else if(i==matrix->rows-1)
				printf("\t%c\t%d\t%c\n", 192, matrix->mat[i][0], 217);
			else
				printf("\t%c\t%d\t%c\n", 179, matrix->mat[i][0], 179);
		}
	}
}

void classify(Matrix *A){
	if(A->cols == 1)
		strcpy(A->type, "Column");
	else if(A->rows == 1)
		strcpy(A->type, "Row");
	else if(A->rows > A->cols)
		strcpy(A->type, "Vertical");
	else if(A->rows < A->cols)
		strcpy(A->type, "Horizontal");
	else
		strcpy(A->type, "Square");
}

void addition(Matrix* matrix1Ptr){
	
	int m = matrix1Ptr->rows;
	int n = matrix1Ptr->cols;
	int i,j;
	
	Matrix sum;
	Matrix* sumPtr = &sum;
	initializeMatrix(sumPtr,m,n);
	
	printf("\nPlease enter the Matrix(B) to be added to Matrix(A):\n");
	Matrix matrix2;
	Matrix* matrix2Ptr = &matrix2;
	newMatrix(matrix2Ptr,m,n);
	
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			sumPtr->mat[i][j] = (matrix1Ptr->mat[i][j] + matrix2Ptr->mat[i][j]);
		}
	}
	printf("\nMatrix(C) such that Matrix(A) + Matrix(B) = Matrix(C) is:\n");
	showMatrix(sumPtr);	
}

void subtraction(Matrix* matrix1Ptr){
	
	int m = matrix1Ptr->rows;
	int n = matrix1Ptr->cols;
	int i,j;
	
	Matrix sub;
	Matrix* subPtr = &sub;
	initializeMatrix(subPtr,m,n);
	
	printf("\nPlease enter the Matrix(B) to be subtracted from Matrix(A):\n");
	Matrix matrix2;
	Matrix* matrix2Ptr = &matrix2;
	newMatrix(matrix2Ptr,m,n);
	
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			subPtr->mat[i][j] = (matrix1Ptr->mat[i][j] - matrix2Ptr->mat[i][j]);
		}
	}
	printf("\nMatrix(C) such that Matrix(A) - Matrix(B) = Matrix(C) is:\n");
	showMatrix(subPtr);	
}

void multiplication(Matrix* matrix1Ptr){
	int m = matrix1Ptr->rows;
	int n = matrix1Ptr->cols;
	int i,j,k,p,q,sum = 0;

	// Error is reset on a new function call
	resetAllErrors();
	
	Matrix multi;
	Matrix* multiPtr = &multi;
	initializeMatrix(multiPtr,m,n);
	
	printf("Please enter dimensions 'p x q' (p and q must be less than or equal to %d) of 'Matrix(B)' to be mulplied\nEnter p: ", MAX);
	scanf("%d", &p);	
	printf("Enter q: ");
	scanf("%d", &q);
	
	if(n != p){
		NO_PRODUCT_POSSIBLE = 1;
		printf("\nMath Error: Number of Rows in Matrix(A) should be equal to number of Columns in Matrix(B)");
		return;
	}
		
	printf("\nPlease enter the Matrix(B) to be pre-multiplied by Matrix(A):\n");
	Matrix matrix2;
	Matrix* matrix2Ptr = &matrix2;
	newMatrix(matrix2Ptr,p,q);
		
	for(i=0;i<m;i++){
		for(j=0;j<q;j++){
			for(k=0;k<p;k++){
				sum = sum + (matrix1Ptr->mat[i][k] * matrix2Ptr->mat[k][j]);
			}
			multiPtr->mat[i][j] = sum;
			sum = 0;
		}
	}
	printf("\nMatrix(C) such that Matrix(A) * Matrix(B) = Matrix(C) is:\n");
	showMatrix(multiPtr);	
}

void transpose(Matrix * matrixPtr){
	int m = matrixPtr->rows;
	int n = matrixPtr->cols;
	int i,j;
	
	Matrix transpose;
	Matrix* transposePtr = &transpose;
	initializeMatrix(transposePtr,n,m);
	
	if(m == n){
		for(i=0;i<m;i++){
			for(j=0;j<n;j++){
				transposePtr->mat[j][i] = matrixPtr->mat[i][j];
			}
	    }
	}else{
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				transposePtr->mat[i][j] = matrixPtr->mat[j][i];
			}
		}
	}
	
	printf("\nThe Matrix(A') is:\n");
	showMatrix(transposePtr);	
}


int determinant(Matrix *A){
	
	// Since you'll need the value of det(A) to calculate the inverse(A), returning its value will be the better choice
}

Matrix *adjoint(Matrix *A){
	
	// Since you'll need adj(A) to calculate the inverse(A), returning a pointer to that matrix will be the better choice
}

void invert(Matrix *A){
	
	// Calculate and show the result here itself. No need to return anything
}

void main(){
	Matrix A;
	int m, n, ch=-1, err=1;
	
	// If erronuous dimensions are entered, this loop will enable the user to re-enter the correct ones
	while(err){
		printf("For Matrix A:\n");
		printf("Enter m: ");
		scanf("%d", &m);
		printf("Enter n: ");
		scanf("%d", &n);
		
		err=newMatrix(&A, m, n);
	}

	while(ch != 0){
		printf("\n--------------------------------------\n");
		printf("0. Exit\n1. Perform Matrix Addition\n2. Perform Matrix Subtraction\n3. Perform Matrix Multiplication\n4. Transpose Matrix(A)\n5. Classify Matrix(A)\n6. Calculate the Adjoint\n7. Calculate the Determinant\n8. Calculate the Inverse\n9. Display A\nEnter your choice: ");
		scanf("%d", &ch);
		
		if(ch == 0)
			break;
		
		switch(ch){
			case 1:
				addition(&A);
				break;
			case 2:
				subtraction(&A);
				break;
			case 3:
				multiplication(&A);
				if(ExceptionalOccurances() != 0)
					resetAllErrors(); // For further operations, the error codes must be reset
				break;
			case 4:
				transpose(&A);
				break;
			case 5:
				classify(&A);
				printf("\nA is a %s Matrix\n", A.type);
				break;
		/*		
			case 6:
				printf("\nAdjoint of Matrix(A):\n");
				showMatrix(adjoint(&A));
				break;
			case 7:
				printf("\nDeterminant of Matrix(A) = %d\n", determinant(&A));
				break;
			case 8:
				invert(&A);
				break;
		*/
			case 9:
				printf("\nMatrix A:\n");
				showMatrix(&A);
				break;
			default:
				if(ch != -1)
					printf("Invalid Option! Please enter a valid choice!");
				break;
		}
	}

	printf("\nThank You!");
}
