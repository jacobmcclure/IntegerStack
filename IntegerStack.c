//-----------------------------------------------------------------------------
//   Jacob McClure
//
//   IntegerStack.c
//   Array based implementation of Integer Stack ADT in C (with array doubling)
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include"IntegerStack.h"

// Private Types and Functions -------------------------------------------------

// InitialSize
static const int InitialSize = 1;

// IntegerStackObj
typedef struct IntegerStackObj{
   int* item;         // array of IntegerStack items
   int numItems;      // number of items in this IntegerStack
   int physicalSize;  // current length of underlying array
} IntegerStackObj;

// doubleItemArray
// Doubles the physical size of the underlying array S->item.
void doubleItemArray(IntegerStack S){
   int i;
   int* newArray;
   int* oldArray = S->item;
   S->physicalSize *= 2;
   newArray = calloc(S->physicalSize, sizeof(int));
   for(i = 0; i < (S->numItems); i++){
      newArray[i] = oldArray[i];
   }
   S->item = newArray;
   free(oldArray);
}

// arrayIndex()
// transforms an IntegerStack index to an Array index
int arrayIndex(int StackIndex){
   return StackIndex-1;
}


// Constructors-Destructors ---------------------------------------------------

// newIntegerStack()
// Constructor for the IntegerStack ADT
IntegerStack newIntegerStack(){
   IntegerStack S = malloc(sizeof(IntegerStackObj));
   S->item = calloc(InitialSize, sizeof(int));
   S->numItems = 0;
   S->physicalSize = InitialSize;
   return S;
}

// freeIntegerStack()
// Destructor for the Stack ADT
void freeIntegerStack(IntegerStack* pS){
   if(pS != NULL && *pS != NULL){
      free((*pS)->item);
      free(*pS);
      *pS = NULL;
   }
}


// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if Stack S is empty, 0 (false) otherwise
int isEmpty(IntegerStack S){
   if(S == NULL){
      fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   return (S->numItems == 0);
}

// size()
// Returns the number of elements in R
int size(IntegerStack S){
   if(S == NULL){
      fprintf(stderr, "IntegerStack Error: size() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   return S->numItems;
}

// peek()
// pre: 1 <= index <= size(S)
// Returns int at position index in S
int peek(IntegerStack S){
   if(S == NULL){
      fprintf(stderr, "IntegerStack Error: get() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   return S->item[(S->numItems) - 1];
}

// push()
// Inserts int x into S at position index
void push(IntegerStack S, int x){
   if(S == NULL){
      fprintf(stderr, "IntegerStack Error: add() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   // double physical size of array if no more room to push new items
   if( (S->numItems) == (S->physicalSize) ){
      doubleItemArray(S);
   }
   // push new items
   S->item[S->numItems] = x;
   S->numItems++;
}

// pop()
// Deletes int from position index
// pre: 1 <= index <= size(S)
int pop(IntegerStack S){
   if(S == NULL){
      fprintf(stderr, "IntegerStack Error: delete() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   int item_temp = S->item[(S->numItems)-1];
   S->item[(S->numItems)-1] = 0;
   S->numItems--;
   return item_temp;
}

// deleteAll()
// Reset R to the empty state
void popAll(IntegerStack S){
   if(S == NULL){
      fprintf(stderr, "IntegerStack Error: deleteAll() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   for(int i=(S->numItems); i >= 0; i--){
      S->item[arrayIndex(i)] = 0;
   }

   S->numItems = 0;
}


// Other Operations -----------------------------------------------------------

// printIntegerStack()
// Prints a space separated Stack of items in S to file stream pointed to by out
void printIntegerStack(FILE* out, IntegerStack S){
   int i;
   if(S == NULL){
      fprintf(stderr, "IntegerStack Error: printIntegerStack() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   for(i = (S->numItems); i > 0; i--){
      fprintf(out, "%d ", S->item[arrayIndex(i)] );
   }

   fprintf(out, "\n");
}

// equals()
// Returns true (1) if R and T are matching sequences of integers, false (0) otherwise
int equals(IntegerStack S, IntegerStack T){
   int i, eq;

   // If either of the stacks are null, this is an error -- terminate
   if(S == NULL || T == NULL){
      fprintf(stderr, "IntegerStack Error: equals() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   // If the two stacks we are trying to compare are of the same size, compare items:
   if ((S->numItems) == (T->numItems))
      // iterate through each element in both stacks
      for(i = 1; eq && i <= (S->numItems); i++){
         // use eq to hold boolean (1 or 0) value of comparison between items
         eq = (S->item[arrayIndex(i)]) == (T->item[arrayIndex(i)]);
         
         // current items are not equal: return false
         if(eq == 0){
            return 0;
         }
      }

   // If this line executes, the stacks are not the same size, thus cannot be equal: return false
   else{
      return 0; 
   }

   // If this line executes, all items from both stacks were equal: return true!
   return 1;
}
