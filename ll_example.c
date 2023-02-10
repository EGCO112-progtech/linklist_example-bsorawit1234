// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self-referential structure                       
struct Node {                                      
   int id; // each listNode contains a character 
   char name[20];
   struct Node *nextPtr; // pointer to next node
   struct Node *prevPtr; // pointer to prev node
}; // end structure listNode                        

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

void insert( LLPtr *sPtr, int std_id, char *std_name );
int deletes( LLPtr *sPtr, int value );

int isEmpty( LLPtr sPtr );
void printList( LLPtr currentPtr );
void reverseList(LLPtr currentPtr);
void instructions( void );
void clearAllNodes(LLPtr *sPtr);

int main( void )
{ 
   LLPtr startPtr = NULL, temp; // initially there are no nodes
   unsigned int choice; // user's choice
   int id; // char entered by user
   char name[50];

   instructions(); // display the menu
   printf( "%s", "? " );
   scanf( "%u", &choice );

   // loop while user does not choose 3
   while ( choice != 3 ) { 

      switch ( choice ) { 
         case 1:
            printf( "%s", "Enter a student id: " );
            scanf( "%d", &id );
            printf("Enter a student name: ");
            scanf("%s", name);
            insert( &startPtr, id, name ); // insert item in list
            printList( startPtr );
            reverseList( startPtr );
            break;
         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "%s", "Enter student id to be deleted: " );
               scanf( "%d", &id );

               // if character is found, remove it
               if ( deletes( &startPtr, id ) ) { // remove id
                  printf( "%d deleted.\n", id );
                  printList( startPtr );
                  reverseList(startPtr);
               } // end if
               else {
                  printf( "%d not found.\n\n", id );
               } // end else
            } // end if
            else {
               puts( "List is empty.\n" );
            } // end else

            break;
         default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
      } // end switch

      printf( "%s", "? " );
      scanf( "%u", &choice );
   } // end while
  /* Clear all nodes at the end of nodes*/
   clearAllNodes(&startPtr);

   puts( "End of run." );
} // end main

// display program instructions to user
void instructions( void )
{ 
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int std_id, char *std_name)
{ 
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->id = std_id; // place std_id in node
      strcpy(newPtr->name, std_name);
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->prevPtr = NULL;

      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list       
      while ( currentPtr != NULL && std_id > currentPtr->id ) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      } // end while                                         

      // insert new node at beginning of list
      if ( previousPtr == NULL ) { 
         newPtr->nextPtr = *sPtr;
         newPtr->prevPtr = NULL;
         if(currentPtr) currentPtr->prevPtr = newPtr;
         *sPtr = newPtr;
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->nextPtr = currentPtr;
         newPtr->prevPtr = previousPtr;
         if(currentPtr != NULL) currentPtr->prevPtr = newPtr;
      } // end else
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", std_id );
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int value )
{ 
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if ( value == ( *sPtr )->id ) { 
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      if((*sPtr)) (*sPtr)->prevPtr = NULL;
      
      free( tempPtr ); // free the de-threaded node
      return value;
   } // end if
   else { 
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->id != value ) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } // end while

      // delete node at currentPtr
      if ( currentPtr != NULL ) { 
         tempPtr = currentPtr;
         currentPtr = currentPtr->nextPtr;
         previousPtr->nextPtr = currentPtr;
         if(currentPtr) currentPtr->prevPtr = previousPtr;
         free( tempPtr );
         return value;
      } // end if
   } // end else

   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{ 
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr->nextPtr!= NULL ) {
         printf( "%d %s --> ", currentPtr->id, currentPtr->name );
         currentPtr = currentPtr->nextPtr;   
      } // end while

      printf( "%d %s --> NULL\n", currentPtr->id, currentPtr->name );
   } // end else
} // end function printList

// print reverse the list
void reverseList( LLPtr currentPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The list is:" );

      // move currentPtr to the end of node
      while( currentPtr->nextPtr != NULL) {
         currentPtr = currentPtr->nextPtr;
      }

      // print node from the end to start
      while ( currentPtr->prevPtr != NULL ) {
         printf( "%d %s --> ", currentPtr->id, currentPtr->name );
         currentPtr = currentPtr->prevPtr;   
      } // end while

      printf( "%d %s --> NULL\n", currentPtr->id, currentPtr->name );
   } // end else
} // end function printList

void clearAllNodes(LLPtr *sPtr) {
   LLPtr temp;
   if(!isEmpty((*sPtr))) {
      while((*sPtr) != NULL) {
         temp = (*sPtr);
         (*sPtr) = (*sPtr)->nextPtr;
         free(temp);
      }
   }
}