#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/tree.h"

Tree createTree(char* val, Tree ls, Tree rs)
{
    Tree res;
    //printf("%s\n",val);
    res = malloc(sizeof(*res));

    if(res == NULL)
    {
        perror("Impossible d'allouer le noeud");
        return NULL;
    }

    res->value = val;
    res->left = ls;
    res->right = rs;
    return res;
}

void addNode(Tree t, char* val)
{
    if(isEmpty(t))
        t = createTree(val,NULL,NULL);
    else if(isEmpty(left(t)))
        t->left = createTree(val,NULL,NULL);
    else if(isEmpty(right(t)))
        t->right = createTree(val,NULL,NULL);
    else
        addNode(left(t),val);
}

void constructTree()
{
    
}

char* root(Tree t)
{
	return t->value;
}

void display(Tree t){
    if(isEmpty(left(t)) == false){
		printf("%s -> %s\n",root(t),root(left(t)));
		display(left(t));
	}
	if(isEmpty(right(t)) == false){
		printf("%s -> %s\n",root(t),root(right(t)));	
		display(right(t));
    }
    if(isEmpty(t) == false && sizeTree(t) == 1){
		printf("%s\n",root(t));	
    }
}


int sizeTree(Tree t)
{
    if(isEmpty(t) == true)
        return 0;
    else   
        return sizeTree(left(t)) + sizeTree(right(t)) + 1;
}

bool isEmpty(Tree t)
{
    if (t == NULL)
        return true;
    else
        return false;

}

Tree left(Tree t)
{
    if(isEmpty(t) == true)
        return NULL;
    else
        return t->left;
}

Tree right(Tree t)
{
    if(isEmpty(t) == true )
        return NULL;
    else
        return t->right;
}

bool isLeaf(Tree t)
{
    if(isEmpty(t))
        return false;
    else if (sizeTree(t) == 1 )
        return true;
    else
        return false;
}

void parcoursPrefixe(Tree a){
	if(isEmpty(a) == false){
        //do smth
		printf("%s\n" ,root(a));
		parcoursPrefixe(left(a));
		parcoursPrefixe(right(a));
	}
}