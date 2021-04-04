#ifndef LINESTRIP_H
#define LINESTRIP_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Vector.h"
typedef Vector ltype;
// ------------------------------------------------------------------------------
// struct LineStrip is a Stack of vectors with linked structure

//  In the algorithm of this stage of LineDraw project,
//  we either delete last vertex of Line Strip, or add new vertex
//  at the end of Line Strip, therefore Stack is suitable for this stage.

//  And since we want the program to be able to add as many
//  vertices to the line strip as the user needs,linked structure 
//  is more convenient.
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// value: Vector that represents vertex in line strip
// next: pointer to next node
typedef struct LineStrip{
    ltype value;
    struct LineStrip* next;
} LineStrip;
// -------------------------------------------------------------------------------
// linestrip = pointer to head node (pointer to first element) = stack of vertices 
// head node = last added node      (because of nature of stack);
// -------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// vertex: Vector represents vertex
// return value: new LineStrip Node which holds vertex as value
LineStrip* LS_createNode(ltype vertex);

// ------------------------------------------------------------------------------
// linestrip: pointer to LineStrip that represents stack of vertices(pointer to head node )
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
// function prints elements of linestrip with reverse order of addition
// (last added element appears first)
// in case of empty linestrip, function prints "NULL"
void LS_Print(LineStrip* linestrip);
#endif