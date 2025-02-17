//Name: Route.h
//Author:  Aswanth Jeyaram Kumar
//Date:    4/10/2024
//Desc: This file contains the header details for the Route class
//      A route is a linked list that uses airports as nodes

#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "Airport.h"
using namespace std;

class Route {
 public:
  // Name: Route() - Default Constructor
  // Desc: Used to build a new Route (linked list) make up of airports
  // Preconditions: None
  // Postconditions: Creates a new Route where m_head and m_tail
  //   point to nullptr and size = 0
  Route();
  // Name: SetName(string)
  // Desc: Sets the name of the route (usually first
  //   airport to last airport)
  // Preconditions: None
  // Postconditions: Sets name of route
  void  SetName(string name);
  // Name: ~Route() - Destructor
  // Desc: Used to destruct a strand of Route
  // Preconditions: There is an existing Route strand with at least
  //   one airport
  // Postconditions: Route is deallocated (including all
  //   dynamically allocated airports) to have no memory leaks!
 ~Route();
  // Name: InsertEnd (string, string, double double)
  // Desc: Creates a new airport using the data passed to it.
  //   Inserts the new airport at the end of the route
  // Preconditions: Takes in a Airport
  //                Requires a Route
  // Postconditions: Adds the new airport to the end of a route
  void InsertEnd(string, string, string, string, double, double);
  // Name: RemoveAirport(int index)
  // Desc: Removes a airport from the route at the index provided
  //   Hint: Special cases (first airport, last airport, middle airport)
  // Preconditions: Index must be less than the size of the route
  //   Cannot make route less than two airports. If the route has
  //   two or fewer airports, fails.
  // Postconditions: Name may be updated. Size is reduced.
  //   Route has one less airport.
  void RemoveAirport(int airport);
  // Name: GetName()
  // Desc: Returns the name of the route (Usually starting
  //  airport to last airport)
  //  For example: Baltimore to Boston
  // Preconditions: Requires a Route
  // Postconditions: Returns m_name;
  string GetName();
  // Name: UpdateName()
  // Desc: Updates m_name based on the name of the first airport
  //   in the route and the last airport in the route
  //       For example: Baltimore to Boston
  // Preconditions: Requires a Route with at least two airports
  // Postconditions: Returns m_name;
  string UpdateName();
  // Name: GetSize()
  // Desc: Returns the number of airports in a route
  // Preconditions: Requires a Route
  // Postconditions: Returns m_size;
  int GetSize();
  // Name: ReverseRoute
  // Desc: Reverses a route
  // Preconditions: Reverses the Route
  // Postconditions: Route is reversed in place; nothing returned
  void ReverseRoute();
  // Name: GetData (int)
  // Desc: Returns an airport at a specific index
  // Preconditions: Requires a Route
  // Postconditions: Returns the airport from specific item
  Airport* GetData(int index);
  // Name: DisplayRoute
  // Desc: Displays all of the airports in a route
  // Preconditions: Requires a Route
  // Postconditions: Displays all of the airports in a route
  // Formatted: Baltimore, Maryland (N39.209 W76.517)
  void DisplayRoute();
 private:
  string m_name; //Name of the Route
  Airport *m_head; //Front of the Route (Starting Point)
  Airport *m_tail; //End of the Route (Ending Point)
  int m_size; //Total size of the Route
};

#endif
