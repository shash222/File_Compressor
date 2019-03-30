#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//size of hashtable

#define size 10000

/*
****************************************
****************************************
              / HashTable\
****************************************
****************************************
                                        */

/*still*/


struct node
{
	int data;
	struct node *next;
	
};

struct node * hashtable[size];

void  insert(struct node *head, int data, int key)
{
	 if(head==NULL)
	 {
	 	head=(struct node *)malloc(sizeof(struct node));
	 	head->data=data;
	 	head->next=NULL;
	 	printf("inserted\n");
	 	hashtable[key]=head;
                return;
	 }




	struct node *temp;
	temp=head;

        if(temp->data==data)
       {
             printf("duplicate\n");
             return;
       }


	while(temp->next!=NULL)
	{
		if(temp->data==data)
		{
			printf("duplicate\n");
			return;
		}
			temp=temp->next;
	}
	    struct node *nxt=(struct node *)malloc(sizeof(struct node));
	    nxt->data=data;
	    nxt->next=head;
	    printf("inserted\n");
	    hashtable[key]= nxt;
            return;
	
}


bool search(struct node* head, int data)
{
	struct node* temp;
	temp=head;	
	//printf("%d\n", data);

	if(temp==NULL)
	{
		//printf("absent\n");
		return false;
	}
   
   	while(temp!=NULL)
	{   
		if(temp->data==data)
		{
			//printf("present\n");
			return true;
		}
		//printf("searching %d temp %d\n", data, temp->data );
		temp=temp->next;
	}

	//broke out and didnt find
	//printf("absent\n");
	return false;
}