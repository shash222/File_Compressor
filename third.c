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
  char * s;
  struct node *next;

};

struct node * hashtable[size];
struct node* head;
struct node*  insert(struct node *head,  char* str, int key)
{

  if(head==NULL)
  {
    head=(struct node *)malloc(sizeof(struct node));
    head->data=1;
    head -> s = str;
    head->next=NULL;
    //printf("inserted\n");
    //hashtable[key]=head;
    return head;
  }




  struct node *temp;
  temp=head;



  while(temp->next!=NULL)
  {
    if(temp->s==str)
    {
      temp->data = (temp->data)+1;
      return;
    }
    temp=temp->next;
  }
  struct node *nxt=(struct node *)malloc(sizeof(struct node));
  nxt->data=1;
  nxt->s = str;
  nxt->next=NULL;
  temp->next = nxt;
  return head;

}


int search(struct node* head, char * str)
{
  struct node* temp;
  temp=head;	
  //printf("%d\n", data);

  if(temp==NULL)
  {
    //printf("absent\n");
    return -1;
  }

  while(temp!=NULL)
  {   
    if(temp->s==str)
    {
      //printf("present\n");
      return temp->data;
    }
    //printf("searching %d temp %d\n", data, temp->data );
    temp=temp->next;
  }

  //broke out and didnt find
  //printf("absent\n");
  return -1;
}

int main()
{

  head = NULL;
  head = insert(head, "hello", 0);
  head = insert(head, "there", 0);
  head = insert(head, "this", 0);
  head = insert(head, "hello", 0);
  int i=0;
  struct node* temp = head;
  while(temp!=NULL)
  {
    printf("String:%s data:%d\n", temp->s, temp->data);
    temp = temp->next;
  }





}
