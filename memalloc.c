// The MIT License (MIT)
// 
// Copyright (c) 2021, 2022, 2023 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software. (RmFsbCAyMDIz)
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES UTA OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "memalloc.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX 10000



struct Node nodes[10000];
enum ALGORITHM store;
int trackNext = 0; 

//int number_of_nodes = 0;


int memalloc_init( size_t size, enum ALGORITHM algorithm )
{
  //Alingn the sizes and allocation memory for arena block
  size_t requested_size = ALIGN4(size);
  nodes[0].arena = malloc(sizeof(requested_size));
  if (nodes[0].arena == NULL)
  {
    return -1;
  }
  nodes[0].size = requested_size; 
  nodes[0].type = H;
  nodes[0].next = -1;
  nodes[0].previous = -1;

  //Make a global variable to store the algorithms.
  store = algorithm;
  return 0;
}

void memalloc_destroy( )
{
  //Free the malloc of the areana and then walk through each node and set it as free 
  free(nodes[0].arena);
  for (int i = 0; i < MAX; i++)
  {
    nodes[i].type = H;
    nodes[i].next = -1;
    nodes[i].previous = -1;
    nodes[i].size = 0;
  }
  return;
}

void * memalloc_alloc( size_t size )
{
  //Align the size before we do anytign with requesting it
  size_t requested_size = ALIGN4(size);
  if (store == BEST_FIT)
  {
    //If it is best fit then we look for the smallest block that will fit 
    int min = -1; 
    for (int i = 0; i != -1; i = nodes[i].next)
    {
      //iterate through all the nodes if it is H then compare across all the minimums. The minimum is where the the best fit fits.
      //create node points to the leftover memory or else there will only be one allocation 
        if (nodes[i].type == H && nodes[i].size >= requested_size)
        {
          if(min == -1)
          { 
            //We want to make sure that the index does not reach -1 for any reason 
            min = i;
          }
          else
          {
            if(nodes[min].size > nodes[i].size)
            {
              //sets min to the 
               min = i;
            }
          }
        }
    }
        
        //check to see if there is leftover space; if there is we make a new node and track the next H
        if (nodes[min].size - requested_size > 0)
        {
          int j = 0;
          while(nodes[j].size != 0)
          {
            j++;
          }
          //Tracks the next node and set up node information 
         nodes[j].size = nodes[min].size - requested_size;
         nodes[j].next = -1;
         nodes[j].arena = nodes[min].arena + requested_size;
         nodes[j].type = H;
         nodes[j].next = nodes[min].next;
         nodes[min].next = j;
         nodes[j].previous = min;
         nodes[min].size = requested_size;
         
        }
        nodes[min].type = P;
        //Return the addres that we pick 
        return nodes[min].arena;
  }
  if (store == WORST_FIT)
  {
    //Same as best fit but we just geet the large block
    int max = -1;
    for (int i = 0; i != -1; i = nodes[i].next)
    {
      //iterate through all the nodes if it is H then compare across all the minimums. The minimum is where the the largest block 
        //create node points to the leftover memory or else there will only be one allocation 
        if (nodes[i].type == H && nodes[i].size >= requested_size)
        {
          if(max == -1)
          { 
            max = i;
          }
          else
          {
            if(nodes[max].size < nodes[i].size)
            {
               max = i;
            }
          }
        }
    }
        //check to see if there is leftover space; if there is we make a new node and track the next H
        if (nodes[max].size - requested_size > 0)
        {
          int j = 0;
          while(nodes[j].size != 0)
          {
            j++;
          }
         nodes[j].size = nodes[max].size - requested_size;
         nodes[j].next = -1;
         nodes[j].arena = nodes[max].arena + requested_size;
         nodes[j].type = H;
         nodes[j].next = nodes[max].next;
         nodes[max].next = j;
         nodes[j].previous = max;
         nodes[max].size = requested_size;
         
        }
        nodes[max].type = P;
        return nodes[max].arena;
        //Same as above but this time we want the block that will create the largest leftover memory 
  }
if (store == NEXT_FIT)
{
  //Idea is that we mark the allocation spot and then proceed from there. 
    int i = trackNext;
    do // do while will run once and then go into the while loop 
    {
        if (nodes[i].type == H && nodes[i].size >= requested_size)
        {
            nodes[i].type = P;
            if (nodes[i].size - requested_size > 0)
            {
                int j = 0;
                while (nodes[j].size != 0)
                {
                    j++;
                }
                //tracks the next Node 
                nodes[j].size = nodes[i].size - requested_size;
                nodes[j].next = -1;
                nodes[j].arena = nodes[i].arena + requested_size;
                nodes[j].type = H;
                nodes[j].next = nodes[i].next;
                nodes[i].next = j;
                nodes[j].previous = i;
                nodes[i].size = requested_size;
            }
            trackNext = i;
            //Update the location of trackNext 
            return nodes[i].arena;
        }
        i = nodes[i].next;
        if (i == -1) // If next returns -1 means we have reached the end and have not found a block.
                     //Needs to loop back to the beginning now
        {
            i = 0;
        }
    } 
    while (i != trackNext); 
}

  if (store == FIRST_FIT)
  {
    //Simply finds the first block that is big enough 
    for (int i = 0; i != -1; i = nodes[i].next)
    {
      if(nodes[i].type == H && nodes[i].size >= requested_size) 
      {
        
        nodes[i].type = P;
        if (nodes[i].size - requested_size > 0)
        {
          int j = 0;
          while(nodes[j].size != 0)
          {
            j++;
          }
          //Finds next node and points to it 
         nodes[j].size = nodes[i].size - requested_size;
         nodes[j].next = -1;
         nodes[j].arena = nodes[i].arena + requested_size;
         nodes[j].type = H;
         nodes[j].next = nodes[i].next;
         nodes[i].next = j;
         nodes[j].previous = i;
         nodes[i].size = requested_size;
         
        }
        return nodes[i].arena;
      }
    }
  }
  //Returns NULL if we do not have enough memory OR something is not of the FOUR Fits passed in
  return NULL;
}

void memalloc_free( void * ptr )
{
   
    int node_to_free = -1;
    //We want to get the location that the ptr is trying to free. Idea is that we go in and mark it first.
    for (int i = 0; i != -1; i = nodes[i].next)
    {
      if (ptr == nodes[i].arena)
      {
        nodes[i].type = H;
        node_to_free = i;
      }
    }
    //Kinda like a linked List but in array way of pointing current to next and next->previous to current->previous
    int next_node_index = nodes[node_to_free].next;
    //If the next location is freed then we add them 
    if (next_node_index != -1 && nodes[next_node_index].type == H)
    {
      nodes[node_to_free].next = nodes[next_node_index].next;
      nodes[node_to_free].size += nodes[next_node_index].size;
      if (nodes[next_node_index].next != -1)
      {
        nodes[nodes[next_node_index].next].previous = node_to_free;
      }
    }
    //IF we free the previous node and it is free, then we merge it as well. 
    int previous_node_index = nodes[node_to_free].previous; 
    if (previous_node_index != -1 && nodes[previous_node_index].type == H )
    {
      nodes[previous_node_index].size += nodes[node_to_free].size;
      nodes[previous_node_index].next = nodes[node_to_free].next;
      if (nodes[node_to_free].next != -1)
      {
        nodes[nodes[node_to_free].next ].previous = previous_node_index;
      }
    }

 
  return;
}

int memalloc_size( )
{
 
  int number_of_nodes = 0;
  if (nodes[0].size != 0)
  {
    number_of_nodes =1;
  }

  int i =0;
  while(nodes[i].next != -1 )
  {
    //Walks through the number of current nodes and returns the int
    number_of_nodes ++;
    i = nodes[i].next;
    
  }
  return number_of_nodes;
}

// RmFsbCAyMDIz-76f3-90d6-0703ac120003
