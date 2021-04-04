#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include<stdbool.h>
#include<math.h>
typedef float vtype;

//----------------------------------------------------------------------------
// Vector structure represents Vector and Point in Cartesian coordiante system,
// which means vector has two components: x coordinate, y coordinate which are
// represented with float numbers 

typedef struct Vector{
    vtype x;
    vtype y;
}Vector;

//-----------------------------------------------------------------
// i,j: float numbers representing coordinates of vector (x and y respectively)
// return value: Vector whose coordinates are i and j respectively
Vector V_new(vtype i, vtype j);


//-----------------------------------------------------------------
// Prints out coordinates of vector v with an identifying label
// v: Vector whose coordinates will be printed
// label: char array (string) representing label of vector
void V_show(Vector v, char*label);


//-----------------------------------------------------------------
// v1, v2: two Vectors
// return value:  Vector whose value is difference of v1 and v2. i.e: v1-v2
Vector V_diff(Vector v1, Vector v2);


//-----------------------------------------------------------------
// v: Vector
// k: float number
// return value: Vector whose value is multiplication of k and v
Vector V_mult(Vector v, float k);


//-----------------------------------------------------------------
// v1 and v2: two Vectors
// return value: Vector whose value is dot product of v1 and v2
float V_dotProduct(Vector v1, Vector v2);


//-----------------------------------------------------------------
// v: Vector
// return value: float number which represents magnitude of Vector v
float V_magnitude(Vector v);


//-----------------------------------------------------------------
// A, P : Vectors which represent 2 points
// return value: distance between points A,P with float number
float V_PtPtDistance(Vector A, Vector P);


//-----------------------------------------------------------------
// v: Vector
    // precondition: v can't be null vector ((0,0))
// return value: unit vector parallel to v
    // if v is (0,0), function returns Vector (1,0)
Vector V_unit(Vector v);


//-----------------------------------------------------------------
// A,B : Vectors that represent two points where line AB pass through
// P : Vector that represent Point
// return value: distance between Point P and line AB in float number
// precondition: if A=B i.e. there is no line, function returns
//  distance between point A (or B, they are same).
float V_PtLineDistance(Vector A, Vector B, Vector P);


//-----------------------------------------------------------------
// In order to find distance betweeen point and segment,
// we can define 3 positions of point according to segment.
// In the following 3 functions:
// A,B : Vectors that represent segment [AB]
// P : Vector that represents point P
// return value: true, if point is in given region(position) according to segment [AB],
             //  false, otherwise.
bool V_isInRegionI(Vector P, Vector A, Vector B);
bool V_isInRegionII(Vector P, Vector A, Vector B);
bool V_isInRegionIII(Vector P, Vector A, Vector B);


//-----------------------------------------------------------------
// A,B : Vectors that represent segment [AB]
// P : Vector that represent point P
// return value: distance between point P and segment [AB] in float number
// precondition: if A=B i.e. there is no segment, function returns
//  distance between point A (or B, they are same).
float V_PtSegmentDistance(Vector P, Vector A, Vector B);


//-----------------------------------------------------------------
// pvector: pointer to vector
//      precondition: pvector must not be NULL;
//                    if it is, function terminates without doing anything
// xval:int, represents change in x coordinate of vector pointed by pvector
// yval:int, represents change in y coordinate of vector pointed by pvector
// The function changes position of vector 
// which is pointed by pvector by given values:
//      changes x coordinate of vector by xval
//      changes y coordinate of vector by yval
void V_move(Vector * pvector, int xval,int yval);

//-----------------------------------------------------------------
// v1, v2 : two Vectors represents two points
// lim: float value that represents 
//      max distance between v1 and v2 if they are near to each other
// The function checks if v1 and v2 are near each other:
//      Returns 1 if distance between v1 and v2 is less than limit
//      returns 0, otherwise.
int V_isNear(Vector v1, Vector v2,float lim);

//-----------------------------------------------------------------
// A,B : Vectors that represent segment [AB]
// returns: new Vector that represents middle of segment or edge AB
Vector V_middle(Vector A, Vector B);
#endif