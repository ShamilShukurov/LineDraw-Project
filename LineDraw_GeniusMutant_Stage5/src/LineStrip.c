#include"LineStrip.h"
#include<stdio.h>

LineStrip* LS_createNode(ltype vertex, bool isHead){
    LineStrip* ls= (LineStrip*) malloc(sizeof(LineStrip));
    ls->isHead=isHead;
    ls->next=NULL;
    ls->previous=NULL;
    ls->value=vertex;
    return ls;
}

bool LS_isEmpty(LineStrip* linestrip){
    if(linestrip==NULL){
        return true;
    }
    return false;
}

void LSL_push(LineStrip** plinestripList, ltype vertex){
    if(plinestripList==NULL){
        return;
    }
    LineStrip* newNode = LS_createNode(vertex,true);
    if(LS_isEmpty(*plinestripList)){
        *plinestripList=newNode;
    }
    else{
        newNode->next =*plinestripList;
        (*plinestripList)->previous = newNode;
        *plinestripList=newNode;
    }

}

void LS_insertAfter(LineStrip* node,ltype vertex, bool isHead){
    if(node==NULL){
        return;
    }
    LineStrip* newNode = LS_createNode(vertex,isHead);
    if(node->next!=NULL){
        node->next->previous=newNode;
        newNode->next=node->next;
    }
    node->next=newNode;
    newNode->previous=node;
}
void LS_push(LineStrip** plinestripList, LineStrip** plinestrip, ltype vertex){
    if(plinestrip==NULL || plinestrip==NULL){
        return;
    }
    if(LS_isEmpty(*plinestrip)){
        LSL_push(plinestripList,vertex);
        *plinestrip=*plinestripList;
        return;
    }
    if(!(*plinestrip)->isHead){
        return;
    }

    if(*plinestrip!=*plinestripList){
        LineStrip* previous = (*plinestrip)->previous;
        LS_insertAfter(previous,vertex,true);
        (*plinestrip)->isHead=false;
        // changing head of list
        *plinestrip = previous->next;
    }
    // if linestrip is first linestrip in linestrip list
    else{
        LineStrip* newNode = LS_createNode(vertex,true);
        (*plinestrip)->isHead=false;
        (*plinestrip)->previous = newNode;
        newNode->next = *plinestrip;
        // changing head of list
        *plinestrip = newNode;
        *plinestripList=*plinestrip;
    }
}

void LS_pop(LineStrip** plinestripList, LineStrip** plinestrip){
    if(plinestrip==NULL || plinestripList==NULL){
        return;
    }
    if(LS_isEmpty(*plinestripList) || LS_isEmpty(*plinestrip) || !(*plinestrip)->isHead){
        return;
    }
    // if there is just one node in strip we raise flag
    //  and at the end we will set *plinestrip to NULL
    bool flag= false;
    LineStrip* temp= *plinestrip;
    if(temp->previous!=NULL){
        temp->previous->next=temp->next;
    }
    if(temp->next!=NULL){
        if(temp->next->isHead==true){
            flag=true;
        }
        temp->next->isHead=true;
        temp->next->previous=temp->previous;
    }

    if(*plinestripList==*plinestrip){
        *plinestripList=temp->next;
        // if user inputs same variable for plinestrip and plinestripList
        // we should be sure that *plinestripList will not be null
        if(plinestrip==plinestripList){
            free(temp);
            return;
        }
    }
    if(flag){
        *plinestrip=NULL;
    }
    else{
        *plinestrip=temp->next;
    }
    
    free(temp);

}

void LS_removeNode(LineStrip** plinestripList, LineStrip** plinestrip,LineStrip* node){
    if(plinestripList==NULL || plinestrip==NULL || node==NULL){
        return;
    }
    if(node->isHead && node==*plinestrip){
        LS_pop(plinestripList,plinestrip);
        return;
    }
    
    if(node->previous!=NULL){
        node->previous->next=node->next;
    }
    if(node->next!=NULL){
        node->next->previous=node->previous;
    }
    free(node);
}

void LSL_removeStrip(LineStrip** plinestripList, LineStrip** plinestrip){
    if(plinestripList==NULL || plinestrip==NULL){
        return;
    }
    if(LS_isEmpty(*plinestripList)|| LS_isEmpty(*plinestrip)){
        return;
    }
    if((*plinestrip)->isHead == false){
        return;
    }
    LineStrip* current = *plinestrip;
    current->isHead=false;
    LineStrip* previous = current->previous;
    LineStrip* next;
    while(current!=NULL && !(current->isHead)){
        next=current->next;
        free(current);
        current=next;
    }
    if(previous!=NULL){
        previous->next = next;
    }
    if(next!=NULL){
        next->previous = previous;
    }
    
    if(*plinestrip == *plinestripList){
        *plinestripList=next;
    }
    *plinestrip=next;
    
}

bool LS_isSizeGreater(LineStrip* linestrip, int n){
    if(LS_isEmpty(linestrip) || !(linestrip->isHead)){
        return false;
    }
    int c=1;
    LineStrip* temp = linestrip;
    while(temp->next!=NULL && !(temp->next->isHead)){
        if(c>n){
            return true;
        }
        temp=temp->next;
        c++;
    }
    return c>n;
}

void LSL_print(LineStrip* linestripList){
    printf("Value\t\tisHead\t\tAdress\t\tNext\t\tPrevious\n");
    LineStrip* temp= linestripList;
    while(temp!=NULL){
        V_show(temp->value,"|  ");
        printf("%d\t|%p\t|%p\t\t|%p\t\n",temp->isHead,temp,temp->next,temp->previous);
        printf("-------------------------------------------------------------------------------\n");
        temp=temp->next;
    }
    printf("NULL\n");    
}
