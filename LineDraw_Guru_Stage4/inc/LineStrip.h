#ifndef LINESTRIP_H
#define LINESTRIP_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Vector.h"
typedef Vector ltype;

// -----------------------------------------------------------------------------------------
// struct LineStrip is singly linked list of vectors

//  In the algorithm of this stage of LineDraw project,
//  we insert vertices in the middle or at the end of a LineStrip
//  and also delete vertices from anywhere, therefore List is suitable for this stage.

//  Linked structure is more convenient in this stage, because:
//  1. Insertion and removing elements is faster than contiguous
//  2. We want the program to be able to add as many vertices to the line strip as the user needs.
//      The only limit should be the computer’s memory 

// -----------------------------------------------------------------------------------------



// -----------------------------------------------------------------------------------------
// linestrip = pointer to head node  = list of vertices 

// head node = last added node:
//     We accept last added node as head node, Because:
//      1. In create mode, selected vertex is always has to be last vertex in list.
//      2. When changing mode from edit to create, selected vertex should be last vertex in list.
//      By condisering these features, we want faster access to the last added node in the list. 
// -----------------------------------------------------------------------------------------


// -----------------------------------------------------------------------------------------
// value: Vector that represents vertex in line strip
// next: pointer to next node
typedef struct LineStrip{
    ltype value;
    struct LineStrip* next;
}LineStrip;




// ------------------------------------------------------------------------------
// vertex: Vector represents vertex
// return value: new Line Strip Node which holds vertex as value
LineStrip* LS_createNode(ltype vertex);

// ------------------------------------------------------------------------------
// linestrip: pointer to LineStrip that represents list of vertices
                        // (pointer to head node )
// return value: true, if list is empty, false otherwise
bool LS_isEmpty(LineStrip* linestrip);

// ------------------------------------------------------------------------------
// plinestrip: double pointer to head node 
// the function removes the last added vertex from linestrip and
// returns : removed element
//      precondition: if linestrip is empty or it doesn't exist (plinestrip=NULL),  
//          function returns vector (0,0). 
ltype LS_pop(LineStrip** plinestrip);

// ------------------------------------------------------------------------------
// plinestrip: double pointer to head node
// precondition: if plinestrip is NULL (i.e stack doesn't exist)
//              function terminates without doing anything 
// vertex: Vector, represents vertex
// the function adds vertex to the end of the linestrip 
void LS_push(LineStrip** plinestrip, ltype vertex);

// ------------------------------------------------------------------------------
// linestrip: pointer to head node
// node : pointer to node, which represents one element
// return value: pointer to previous node of given node
// preconditions: if list is empty; if node is NULL; if node is head node
//                function returns NULL
LineStrip* LS_previous(LineStrip* linestrip,LineStrip* node);

// ------------------------------------------------------------------------------
// node : pointer to node, which represents one element whose next node will be deleted
// The function deletes the element coming after node
// preconditions: if node is NULL; if node is tail node (i.e. first added element)         
//             function terminates without doing anything.
void LS_removeAfterNode(LineStrip* node);

// ------------------------------------------------------------------------------
// node : pointer to node, which represents one element.
// vertex: Vector represents new element that will be added after node
// The function inserts the vertex after the node
// preconditions: if node is NULL;
//             function terminates without doing anything. 
void LS_addAfterNode(LineStrip* node, ltype vertex);

// ------------------------------------------------------------------------------
// linestrip: pointer to head node
// function prints elements of linestrip with reverse order of addition
// (last added element appears first)
// in case of empty linestrip, function prints "NULL"
void LS_Print(LineStrip* linestrip);

// ------------------------------------------------------------------------------
// linestrip: pointer to head node
// n: integer
// return value: true, if size of linestrip is bigger than n; false, otherwise.          
bool LS_isSizeGreater(LineStrip* linestrip, int n);

#endif