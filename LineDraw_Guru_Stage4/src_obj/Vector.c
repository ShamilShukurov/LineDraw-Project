#include "Vector.h"


Vector V_new(vtype i, vtype j){
    Vector v;
    v.x=i;
    v.y=j;
    return v;
}

void V_show(Vector v, char*label){
    printf("(%.3f,%.3f)%s",v.x,v.y,label);
}

Vector V_diff(Vector v1, Vector v2){
    return V_new((v1.x-v2.x),(v1.y-v2.y));
}

Vector V_mult(Vector v, float k){
    return V_new((k*v.x),(k*v.y));
}

float V_dotProduct(Vector v1, Vector v2){
    return ((v1.x*v2.x)+(v1.y*v2.y));
}

float V_magnitude(Vector v){
    return sqrt((double)V_dotProduct(v,v));
}

float V_PtPtDistance(Vector A, Vector P){
    return V_magnitude(V_diff(P,A));
}
//Returns a unit vector parallel to v
Vector V_unit(Vector v){
    if(v.x==0 && v.y==1){
        return V_new(1,0);
    }
    return V_mult(v,(1.0/V_magnitude(v)));
}

float V_PtLineDistance(Vector A, Vector B, Vector P){
    if(A.x==B.x && A.y==B.y){
        return V_PtPtDistance(A,P);
    }
    // unit vector of line AB
    Vector u=V_unit(V_diff(B,A)); 
    Vector AP=V_diff(P,A); 
    float mAP= V_magnitude(AP); 
    float dAPu = V_dotProduct(AP,u); 
    return sqrt(pow(mAP,2)-pow(dAPu,2)); 
}

bool V_isInRegionI(Vector P, Vector A, Vector B){
    return V_dotProduct(V_diff(P,A),V_diff(B,A))<=0; // if AP*AB<0 => theta>=90
}
bool V_isInRegionIII(Vector P, Vector A, Vector B){
    return V_dotProduct(V_diff(P,B),V_diff(A,B))<=0; // if BP*BA<0 => theta>=90
}
bool V_isInRegionII(Vector P, Vector A, Vector B){
    return (V_dotProduct(V_diff(P,B),V_diff(A,B))>0)&&(V_dotProduct(V_diff(P,A),V_diff(B,A))>0);
}

float V_PtSegmentDistance(Vector P, Vector A, Vector B){
    if(V_isInRegionI(P,A,B)){
        return V_PtPtDistance(A,P);
    }
    else if (V_isInRegionIII(P,A,B))
    {
        return V_PtPtDistance(B,P);
    }
    else{
        return V_PtLineDistance(A,B,P);
    }
}

void V_move(Vector * pvector, int xval,int yval){
    if(pvector!=NULL){
        pvector->x=pvector->x+xval;
        pvector->y=pvector->y+yval;
    }
}


int V_isNear(Vector p1, Vector p2,float lim){
    if(V_PtPtDistance(p1,p2)<lim){
        return 1;
    }
    return 0;
}

Vector V_middle(Vector A, Vector B){
    float xPos = (A.x+B.x)/2.0;
    float yPos = (A.y+B.y)/2.0;
    return V_new(xPos,yPos);
}