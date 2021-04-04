#ifndef LINESTRIP_H
#define LINESTRIP_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Vector.h"
typedef Vector ltype;

// -----------------------------------------------------------------------------------------
// struct LineStrip is a linked structure that allows us to do operations on
// either one or multiple linestrips.
// We can think about this data structure as concatenation of multiple lists, 
// but we exactly now head (beginning) of each list (thanks to isHead value).
// It is basically doubly linked list of vectors, 
// but we can do operations on each linestrip seperately.

// With struct LineStrip, we can:
// *Add elements to one linestrip: either push element, or insert into middle or end.
// *Add linestrips to whole list.
// *Remove elements from any linestrip: either pop or remove from middle,end.
// *Remove any of linestrips.
// And since in this stage of project we need to edit multiple linestrips,
//  we can use this data type.

//  Linked structure is more convenient in this stage, because:
//  1. Insertion and removing elements is faster than contiguous
//  2. We want the program to be able to add as many vertices to the line strip as the user needs.
//      The only limit should be the computer’s memory 
// -----------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// value: Vector that represents vertex
// isHead: bool value, indicates whether node is beginning of new linestrip or not
// next: pointer to next node in linestrip
// previous: pointer to previous node in linestrip
typedef struct LineStrip{
    ltype value;
    bool isHead;
    struct LineStrip* next;
    struct LineStrip* previous;
}LineStrip;

// ------------------------------------------------------------------------------------------
// linestrip list = pointer very first node of whole list = pointer to head of whole list
// linestrip = pointer to head node of one linestrip 
// pointer to head of whole list can also represent first linestrip in whole list
// ------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// vertex: Vector represents vertex
// isHead: boolean, indicates wether created node will be head node or not
// return value: new LineStrip Node which holds vertex as value
LineStrip* LS_createNode(ltype vertex,bool isHead);

// ------------------------------------------------------------------------------------------
// linestrip: pointer to LineStrip that represents linestrip or list of linestrips
// return value: true if linestrip or linestrip list is empty, false otherwise
bool LS_isEmpty(LineStrip* linestrip);

// ------------------------------------------------------------------------------------------
// plinestripList: double pointer to the head node of list
// vertex: Vector, represents vertex that will be added to the list
// function pushes new linestrip contains vertex to the linestrip list
// precondition:
//      if linestrip list doesn't exists (plinestripList=NULL)
//      function terminates without doing anything
void LSL_push(LineStrip** plinestripList, ltype vertex);

// ------------------------------------------------------------------------------------------
// plinestripList: double pointer to the head node of list
// plinestrip: double pointer to head node of one linestrip
// vertex: Vector, represents vertex that will be added to the list
// Function pushes vertex to the given linestrip 
// preconditions:
//      if plinestripList or plinestrip is NULL (i.e. list doesn't exists);
//      if inputted node is not head ( (*plinestrip)->isHead=false )
//      function terminates without doing anything.
//      if linestrip is empty ( *plinestrip = NULL)
//      function first pushes vertex to linestrip, then pushes linestrip to the whole list
void LS_push(LineStrip** plinestripList,LineStrip** plinestrip, ltype vertex);

// ------------------------------------------------------------------------------------------
// node: pointer to node after which new element will added
// vertex: Vector, represents vertex that will be added to the list
// isHead: boolean, indicates wether inserted node will be head node or not
// function inserts new element after the given node
// precndition: if node is NULL, function terminates without doing anything 
void LS_insertAfter(LineStrip* node,ltype vertex, bool isHead);

// ------------------------------------------------------------------------------------------
// plinestripList: double pointer to the head node of line strip list
// plinestrip: double pointer to the head node of one linestrip
// function deletes last added vertex from the linestrip
// preconditions:
//      if plinestripList or plinestrip is NULL;
//      if linestrip list or linestrip is empty (*plinestripList=NULL or *plinestrip=NULL);
//      if plinestrip doesn't point head node ( (*plinestrip)->isHead=false )
//      function terminates without doing anything.
//      linestriplist must hold linestrip;
void LS_pop(LineStrip** plinestripList,LineStrip** plinestrip);

// ------------------------------------------------------------------------------------------
// plinestripList: double pointer to the head node of line strip list
// plinestrip: double pointer to the head node of one linestrip which will be deleted
// function deletes given linestrip from linestrip list
// preconditions:
//      if plinestripList or plinestrip is NULL;
//      if linestrip list or linestrip is empty (*plinestripList=NULL or *plinestrip=NULL);
//      if plinestrip doesn't point head node ( (*plinestrip)->isHead=false )
//      function terminates without doing anything.
//      linestriplist must hold linestrip;
void LSL_removeStrip(LineStrip** plinestripList,LineStrip** plinestrip);

// ------------------------------------------------------------------------------------------
// plinestripList: double pointer to the head node of line strip list
// plinestrip: double pointer to the head node of one linestrip which holds given node
// node: pointer to one node of linestrip which will be deleted; 
// function deletes given node from given linestrip
// preconditions:
//      if plinestripList, plinestrip or node is NULL;
//      if linestrip list or linestrip is empty (*plinestripList=NULL or *plinestrip=NULL);
//      if plinestrip doesn't point head node ( (*plinestrip)->isHead=false )
//      function terminates without doing anything.
//      linestriplist must hold linestrip; linestrip must hold node.
void LS_removeNode(LineStrip** plinestripList, LineStrip** plinestrip, LineStrip* node);

// ------------------------------------------------------------------------------------------
// linestrip: pointer to head node
// n: integer
// return value: true, if size of linestrip is bigger than n; false, otherwise.          
bool LS_isSizeGreater(LineStrip* linestrip, int n);

// ------------------------------------------------------------------------------------------
// linestripList: pointer to head node of list
// function prints elements of linestrip
void LSL_print(LineStrip* linestripList);
#endif



// FootNote: Alternatives of this data structure that I thought to implement,
//                      and reason of choosing this one.

// First, I implemented new linked list called LineStripList which stores Linestrips,
// but it required a lot of effort, a lot of work, and the code was not enough clean.

// Then I started to think about  one data structure, with which we can handle 
// both linestrip and linestrip list. And I tried to implement linked data structure
//  that each node has 3 pointers, 2 of them was for connecting
//  different linestrips, and one for connecting nodes of one linestrip.
// That would work but it had big disadvantage: waste of memory. For one node there was 3 pointers
//  and 2 of them served just for the head nodes of linestrips.

// Finally I implement data structure which I've used here. It is simpler than having another 
// list for storing linestrips, and doesn't waste so much memory as 2nd alternative.