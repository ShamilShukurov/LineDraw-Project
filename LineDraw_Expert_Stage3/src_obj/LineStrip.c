#include"LineStrip.h"

LineStrip* LS_createNode(ltype vertex){
    LineStrip* ls = (LineStrip*) malloc(sizeof(LineStrip));
    ls->value=vertex;
    ls->next=NULL;
    return ls;
}

bool LS_isEmpty(LineStrip* linestrip){
    if (linestrip == NULL) return true; 
    return false; 
}

void LS_push(LineStrip** plinestrip, ltype vertex){
    if(plinestrip!=NULL){
        if(!LS_isEmpty(*plinestrip)){
            LineStrip* temp = LS_createNode(vertex);
            temp->next = (*plinestrip);
            *plinestrip = temp;
        }
        else{
            *plinestrip=LS_createNode(vertex);
        }
    }
    
}

ltype LS_pop(LineStrip** plinestrip){
    if(plinestrip==NULL) return V_new(0,0);
    if (LS_isEmpty(*plinestrip)) return V_new(0,0); 

    LineStrip* temp = *plinestrip; 
    *plinestrip = (*plinestrip)->next; 
    ltype popped = temp->value; 
    free(temp);   
    return popped; 
}

void LS_Print(LineStrip* linestrip){
    LineStrip* temp = linestrip;
    while(!LS_isEmpty(temp)){
        V_show(temp->value,"->");
        temp = temp->next;
    }
    printf("NULL\n");
}