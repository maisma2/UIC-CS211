/* Lab5.c
    Name: Abeer Ismail
    Date: 5/22/2023
    CS211 Summer 2023
*/


#include <stdio.h>
#include <stdlib.h>

#define TRUE   1
#define FALSE  0
#define COUNT 10


/* Task 1 - Complete the following typedef and struct to define a 
type "Node", as a struct containing an int named "data" and a 
pointer to another struct of the same type, named "next"
*/

typedef struct nodeStruct {
    int data;
    struct nodeStruct * next;

} Node;


/* prototypes of the functions used in this code  */
/*   also called "forward function declarations" */

void printList( Node * head );
int addNodeToHead( Node ** head, Node *newNode );
int addValueToHead( Node ** head, int value );
Node * removeNodeFromHead( Node ** head );


int main( void ) {

    Node *list1 = NULL; // Always initialize for safety sake.
    Node *list2 = NULL;

    // The first 5 tasks use statically allocated Nodes

    /* Task 2 - Create three ordinary variables of type Node,
       named node1, node2, and node3.  Populate the data
       fields with 25, 50, and 75 respectively.  Then make
       node1 point to node2; Make node2 point to node3;
       And set the next pointer in node3 to NULL;  Finally
       make the Node pointer named list1 point to node1.
       You should have created the following list:

        list1 --> node1( 25 ) --> node2( 50 ) --> node3( 75 ) --> NULL
    */
    Node node1;
    Node node2;
    Node node3;
    node1.data = 25;
    node2.data = 50;
    node3.data = 75;

    node1.next = &node2;
    node2.next = &node3;
    node3.next = NULL;

    list1 = &node1;

    /* Task 3 - page down and complete the print function */

    printf( "After task 3, list 1 = " );
    printList( list1 );
    printf( "\n" );

    /* Task 4 - Create another Node, and give it value 100.
       Then pass it to addNodeToHead( ) and print the new
       version of the list.  ( Requires jumping down to
       task 5, which is to complete addNodeToHead( ).
    */
    printf( "After task 5, . . . " );
    Node newNode;
    newNode.data = 100;
    addNodeToHead(&list1, &newNode);
    printList(list1);
    printf("\n");

    // The next tasks use dynamically allocated Nodes

    /* Task 6 - Create three Node pointers, named nodePtr1,
       nodePtr2, and nodePtr3.  Use malloc( ) to dynamically
       allocate 3 Nodes, with each of these pointers pointing to
       one of the new Nodes.  Then populate the data fields of
       the 3 Nodes with 225, 250, and 275 respectively.  Finally
       set the pointer fields of the 3 Nodes to form the
       following linked list:

list2 --> node( 225 ) --> node( 250 ) --> node( 275 ) --> NULL

       ( These nodes do not have variable names of their own,
       but they are pointed to by nodePtr1, nodePtr2, and
       nodePtr3 respectively. )
    */

    printf( "After task 6, list 2 = " );

    Node* nodePtr1 = malloc(sizeof(Node));
    Node* nodePtr2 = malloc(sizeof(Node));
    Node* nodePtr3 = malloc(sizeof(Node));

    nodePtr1 -> data = 225;
    nodePtr2 -> data = 250;
    nodePtr3 -> data = 275;

    nodePtr1 -> next = nodePtr2;
    nodePtr2 -> next = nodePtr3;
    nodePtr3 -> next = NULL;

    list2 = nodePtr1;

    printList( list2 );
    printf( "\n" );

    /* Task 7 - Call addValueToHead( ), passing in list2 and the
       value 300, and then print the new version of the list.
       ( Requires jumping down to task 8, which is to complete
       addValueToHead( ).
    */

    printf( "After task 8, . . . " );
    addValueToHead(&list2, 300);
    printList(list2);
    printf("\n");

    // The final tasks require emptying the lists
    // Run valgrind before step 9, in preparation for step 10.

    /* Task 9 - Jump down and complete removeNodeFromHead.
       Make any corretions that are necessary in the 2 loops.
    */

    printf( "Task9 : \n" );

    Node * temp;

    while( ( temp = removeNodeFromHead( &list1 ) ) != NULL ) {
        printf( "List 1 = " );
        printList( list1 );
        printf( "\n" );
    }

    printf( "\n" );

    while( ( temp = removeNodeFromHead( &list2 ) ) != NULL ) {
        printf( "List 2 = " );
        printList( list2 );
        printf( "\n" );
        free(temp);
    }

    // Task 10 - Run valgrind on this code, and fix any remaining errors.
    //free(temp) clears all the dynamic memory allocated to temp
} // main


/* Task 3 - Uncomment and complete the for loop and printf
   statement in the following function, to traverse the linked
   list and print the contents of each node, separated by spaces
*/

void printList( Node * head ) {

    Node * current;
    for( current = head; current != NULL; current = current -> next ) {
        printf( "%d ", current -> data );
    }
    return;
} // printList

/* Task 5 - Complete the following function to add newNode to the
   head of the linked list.  Note that both head ( a Node * ) and
   newNode ( a Node ) are passed by pointer/address.
*/

int addNodeToHead( Node ** head, Node *newNode ) {

    if (head == NULL || newNode == NULL) {
        return -1;
    }

    newNode->next = *head;
    *head = newNode;

    return 0;; // No problems found
} // addNodeToHead

/* Task 8 - Complete the following function to add "value" to the
   head of the linked list.  Note that head is passed by
   pointer/address, and that value will have to be added to a new
   dynamically allocated Node.
*/

int addValueToHead( Node ** head, int value ) {

    if (head == NULL) {
        return -1;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) return -1; //fa
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;

    return 0;

} // addValueToHead

/* Task 9 - Complete the following function to remove a node from
   the head of the linked list.  Note that head is passed by 
   pointer/address, and that the node removed from the list is 
   returned.  If the work can't be done, ( e.g. if head is NULL 
   to begin with ), then the function returns NULL.
*/

Node * removeNodeFromHead( Node ** head ) {

    if (head == NULL || *head == NULL) {
        return NULL;
    }

    Node* removedNode = *head;
    *head = (*head)->next;
    removedNode->next = NULL;

    return removedNode;

} // removeNodeFromHead
