#include"LineStrip.h"

LineStrip* LS_createNode(ltype vertex){
    LineStrip* ls = (LineStrip*) malloc(sizeof(LineStrip));
    ls->value=vertex;
    ls->next=NULL;
    return ls;
}

bool LS_isEmpty(LineStrip* linestrip){
    if (linestrip == NULL) { 
        return true; 
    } 
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
    if(plinestrip==NULL){
        return V_new(0,0); 
    }
    if (LS_isEmpty(*plinestrip)){ 
        return V_new(0,0); 
    }
    LineStrip* temp = *plinestrip; 
    *plinestrip = (*plinestrip)->next; 
    ltype popped = temp->value; 
    free(temp); 
  
    return popped; 
}

void LS_removeAfterNode(LineStrip* node){
    if(node==NULL){
        return;
    }
    if(node->next!=NULL){
        LineStrip* temp=node->next;
        node->next=temp->next;
        free(temp);
    }
}
LineStrip* LS_previous(LineStrip* linestrip,LineStrip* node){
    if(LS_isEmpty(linestrip) || node==NULL){
        return NULL;
    }
    LineStrip* previous=NULL;
    LineStrip* temp=linestrip;
    while(temp->next!=NULL){
        if(temp->next==node){
            previous=temp;
            break;
        }
        temp=temp->next;
    }
    return previous;
}

void LS_addAfterNode(LineStrip* node, ltype vertex){
    if(node==NULL){
        return;
    }
    LineStrip* newnode = LS_createNode(vertex);
    newnode->next=node->next;
    node->next=newnode;

}

void LS_Print(LineStrip* linestrip){
    LineStrip* temp = linestrip;
    while(!LS_isEmpty(temp)){
        V_show(temp->value,"->");
        temp = temp->next;
    }
    printf("NULL\n");
}
bool LS_isSizeGreater(LineStrip* linestrip, int n){
    if(LS_isEmpty(linestrip)){
        return false;
    }
    int c=1;
    LineStrip* temp = linestrip;
    while(temp->next!=NULL){
        if(c>n){
            return true;
        }
        temp=temp->next;
        c++;
    }
    return c>n;
}