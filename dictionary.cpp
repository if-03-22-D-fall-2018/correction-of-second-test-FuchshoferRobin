/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			dictionary.cpp
 * Author:			P. Bauer
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Implementation of dictionary.h.
 * ----------------------------------------------------------
 */
 #include "dictionary.h"
 #include "general.h"
 #include "string.h"
 #include <stdlib.h>
 #include <ctype.h>

typedef struct NodeImplementation* Node;

struct NodeImplementation
{
  const char* word;
  Node next;
};

struct DictionaryImplementation {
  int length;
  Node head;
  bool isIterating;
};

 Dictionary new_dictionary()
 {
   Dictionary dictionary = (Dictionary)malloc(sizeof(struct DictionaryImplementation));
   dictionary->length = 0;
   dictionary->head = 0;
   dictionary->isIterating = false;
   return dictionary;
 }

 void 	delete_dictionary (Dictionary dictionary)
 {
   Node currentNode = dictionary->head;

   while (currentNode != 0)
   {
     Node deleteNode = currentNode;
     currentNode = currentNode->next;
     sfree(deleteNode);
   }
   dictionary->length = 0;
   dictionary->head = 0;
   sfree(dictionary);
 }

 void 	add (Dictionary dict, const char *word)
 {
   Node insert = (Node)malloc(sizeof(struct NodeImplementation));
   insert->word = word;
   insert->next = 0;

   Node currentNode = dict->head;

   if(is_in_dict(dict,word))return;


   if(dict->head == 0)
   {
     dict->head = insert;
   }

   else
   {
    while (currentNode->next != 0)
    {
     currentNode = currentNode->next;
    }

    currentNode->next = insert;
   }
   dict->length++;
 }

 int 	get_size (Dictionary dict)
 {
   return dict->length;
 }

 bool 	is_in_dict (Dictionary dict, const char *word)
 {
   Node currentNode = dict->head;

    while (currentNode != 0)
    {
      if(strcasecmp(currentNode->word,word) == 0)
      {
        return true;
      }
      currentNode = currentNode->next;

    }
    return false;
 }

 void 	start_iterating (Dictionary dict)
 {
   dict->isIterating = true;
 }

 bool 	has_next (Dictionary dict)
 {
   if(dict->head != 0 && dict->isIterating == true)
   {
     return true;
   }
   return false;
 }

 const char * 	get_next_entry (Dictionary dict)
 {
   if(has_next(dict)== true && dict->isIterating == true)
   {
     const char* word = dict->head->word;
     dict->head = dict->head->next;
     return word;
   }
   return 0;
 }

 void 	insert_sorted (Dictionary dict, const char *word) //added everything
{

  if (dict->head == 0)
  {
      add(dict,word);
  }
  else
  {
    if (is_in_dict(dict,word)) return;

    Node dictionary=(Node)malloc(sizeof(NodeImplementation));
    dictionary->word=word;
    dictionary->next=0;
    if (strcasecmp(dict->head->word,word)>0)
    {
      dictionary->next=dict->head;
      dict->head=dictionary;
      dict->length++;
    }
    else
    {
      Node current=dict->head;
      while (current->next !=0 && strcasecmp(current->next->word,word)<0)
      {
        current=current->next;
      }

      if (current->next == 0)
      {
        add(dict,word);
      }

      if (strcasecmp(current->next->word,word)>0)
      {
        dictionary->next=current->next;
        current->next=dictionary;
        dict->length++;
      }
    }
  }
}
