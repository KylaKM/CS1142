/*
  Kyla Kane-Maystead
  kakanema
  Description: This program is designed to find the shortest total distance a salesmen will make using two greedy heurisitcs. 
 */
// Replace the body of all the functions in this file.
// *** DO NOT CHANGE THE FUNCTION DECLARATIONS ****

#include "TSP.h"     // Gets the Node data type and the function prototypes
#include <stdlib.h>  // Needed to get the NULL constant
#include <float.h>
#include <math.h>
#include <stdio.h>
// Print out the point stored at the given node.
// You can assume node is not NULL.
// Round to 4 decimal places and output a line feed (\n), e.g.:
// (1.2345, 6.7890)
void printNode(Node* node)
{
  printf("(%.4f, %.4f)\n", node->x, node->y);
}

// Print out all the points in the tour from first to last.
// Passed a pointer to the first node in the tour.
// If the first is NULL, doesn't print anything.
void printTour(Node* first)
{
  if(first == NULL) {
    return;
  }
  else {
    printNode(first);
    printTour(first->next);
  }
}

// Get the number of points in the tour.
// Passed a pointer to the first node in the tour.
// If first is NULL, return a size of 0.
int tourSize(Node* first)
{
  if(first == NULL) {
    return 0;
  }
  int count = 0;
  for(Node* current = first; current != NULL; current = current->next) {
    count++;
  }
  return count;
}

// Calculate the Euclidean distance between two nodes.
// You can assume both a and b are both not NULL.
double distance(Node* a, Node* b)
{
  double xa = a->x;
  double ya = a->y;
  double xb = b->x;
  double yb = b->y;
  double distance = 0.0;
  distance = sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
  return distance;
}

// Calculate the total distance between all points in the tour.
// Since the tour is circular, this includes the distance from the last point back to the start.
// Passed a pointer to the first node in the tour.
// If first is NULL, return a tour length of 0.0.
double tourDistance(Node* first)
{
  if(first == NULL) {
    return 0.0;
  }
  double totalDist = 0.0;
  Node* current = first;
  while(current->next != NULL) {
    if(current->next  == NULL) {
      totalDist += distance(first, current);
    }
    else {
      totalDist += distance(current, current->next);
      current = current->next;
    }
  }
  totalDist += distance(current, first);
  return totalDist;
}

// Add a new point after the point that it is closest to.
// If there is a tie, insert it after the first such point you find.
// Passed a pointer to the first node in the tour, NULL if creating a new tour.
// Returns pointer to the first node in the linked list after the addition.
Node* addNearestNeighbor(Node* first, double x, double y)
{
  Node* add = malloc(sizeof(Node));
  add->x = x;
  add->y = y;
  if(first == NULL) {
    return add;
  }
  Node* current = first;
  Node* near = first;
  double dist = distance(first, add);
  
  while(current->next != NULL) {
    current = current->next;
    double temp = distance(current, add);
    if(temp < dist) {
      near = current;
      dist = temp;
    }
  }
  add->next = near->next;
  near->next = add;
  return first;
}

// Add a new point after the point where it results in the least increase in tour length.
// If there is a tie, insert it after the first such point you find.
// Passed a pointer to the first node in the tour, NULL if creating a new tour.
// Returns pointer to the first node in the linked list after the addition.
Node* addSmallestIncrease(Node* first, double x, double y)
{
  Node* add = malloc(sizeof(Node));
  add->x = x;
  add->y = y;
  
  if(first == NULL) {
    return add;
  }
  
  Node* current = first->next;
  if(current == NULL) {
    first->next = add;
    return first;
  }
  
  Node* bestn = first;
  double dist = distance(first, add) + distance(add, current) - distance(first, current);
  
  while(current->next != NULL) {
    double temp = distance(current, add) + distance(add, current->next) - distance(current, current->next);
    if(temp < dist) {
      dist = temp;
      bestn = current;
    }
    current = current->next;
  }
  double temp = distance(current, add) + distance(add, first) - distance(current, first);
  if(temp < dist) {
    dist = temp;
    bestn = current;
  }
  add->next = bestn->next;
  bestn->next = add;
  return first;
}

// Deallocate all the memory of the Node structures in the linked list.
// Passed a pointer to the first node in the tour.
// If first is NULL, don't do anything.
void freeTour(Node* first)
{
  if(first == NULL) {
    return;
  }
  else {
    Node* current = first;
    Node* currentNext = first->next;
    while(currentNext != NULL) {
      free(current);
      current = currentNext;
      currentNext = currentNext->next;
    }
    free(current);
    free(currentNext);
  }
}

