//Name: Navigator.h
//Author:  Aswanth Jeyaram Kumar
//Date:   4/10/2024
//Desc: This file contains the header details for the Navigator class

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "Airport.h"
#include "Route.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

//Constants used for calculating distance
#define PI 3.14159265358979323846
#define EARTH_RADIUS 3958.8 //in miles
#define DEG_2_RAD PI / 180
#define RAD_2_DEG 180 / PI
//Constants
const int ROUTE_MIN = 2; //Minimum number of airports in a route

class Navigator {
 public:
  // Name: Navigator (string) - Overloaded Constructor
  // Desc: Creates a navigator object to manage routes
  // Preconditions:  Provided with a filename of airports to load
  // Postconditions: m_filename is populated with fileName
  Navigator(string fileName);
  // Name: Navigator (destructor)
  // Desc: Deallocates all dynamic aspects of a Navigator
  // Preconditions: There is an existing Navigator
  // Postconditions: All airports and routes are cleared
  ~Navigator();
  // Name: Start
  // Desc: Loads the file and calls the main menu
  // Preconditions: m_fileName is populated
  // Postconditions: All ports are loaded and the main menu runs
  void Start();
  // Name: DisplayAirports
  // Desc: Displays each airport in m_airports
  // Preconditions: At least one airport is in m_airports
  // Postconditions: Displays all airports.
  //  Uses overloaded << provided in Airport.h
  void DisplayAirports();
  // Name: ReadFile
  // Desc: Reads in a file that has data about each airport
  //   including code, name, city, country, degrees north and degrees west.
  //   Dynamically allocates airports and stores them in m_airports
  //   The vector can hold many airports.
  // Preconditions: Valid file name of airports
  // Postconditions: Dynamically allocates each airport
  //   and enters it into m_airports
  void ReadFile();
  // Name: InsertNewRoute
  // Desc: Dynamically allocates a new route with the user selecting
  //   each airport in the route. Each route can have a minimum of two
  //   airports. Will not allow a one airport route.
  //   Checks for min of two valid airports (1-40)
  //   Route named using Route's UpdateName.
  //   For example, Baltimore to Boston
  //   Once route is created, inserted into m_routes.
  // Preconditions: Populated m_routes
  // Postconditions: Inserts a new route into m_routes
  void InsertNewRoute();
  // Name: MainMenu
  // Desc: Displays the main menu and manages exiting
  // Preconditions: Populated m_airports
  // Postconditions: Exits when someone chooses 5
  void MainMenu();
  // Name: ChooseRoute
  // Desc: Allows user to choose a specific route to work with
  //   by displaying numbered list
  // Preconditions: Populated m_routes
  // Postconditions: Returns the index of the selected route minus 1
  int ChooseRoute();
  // Name: DisplayRoute
  // Desc: Using ChooseRoute, displays a numbered list of all routes.
  //    If no routes, indicates that there are no routes to display
  //    User selects a route from list to display
  //    Displays numbered list of each airport in route
  //    Displays total miles of a route using RouteDistance
  // Preconditions: Routes has more than one airport
  // Postconditions: Displays all airports in a route and
  //    the total miles of the route
  void DisplayRoute();
  // Name: RemoveAirportFromRoute()
  // Desc: Using ChooseRoute, displays a numbered list of all routes.
  //    User selects one of the routes to remove an airport from.
  //    Displays a numbered list of all airports in selected route.
  //    User selects airport to remove from list.
  //    Each route has a minimum of two airports (will not allow).
  //    Removes airport from route if more than two.
  //    If first or last airport removed,
  //    updates name of route using UpdateName
  // Preconditions: Route has more than one airport
  // Postconditions: Displays updated route with removed airport
  //    and new name
  void RemoveAirportFromRoute();
  // Name: RouteDistance
  // Desc: Calculates the total distance of a route
  //    Goes from airport 1 to airport 2 then airport 2 to airport 3
  //    and repeats for length of route.
  //    Calculates the distance using CalcDistance (provided)
  //    Aggregates the total and returns the total in miles
  // Preconditions: Populated route with more than one airport
  // Postconditions: Returns the total miles between all airports in a route
  double RouteDistance(Route*);
  // Name: ReverseRoute
  // Desc: Using ChooseRoute, users chooses route and the route is reversed
  //   If no routes in m_routes, indicates no routes available to reverse
  //   Updates route name using UpdateName
  //   For example, Baltimore to Boston becomes Boston to Baltimore
  // Preconditions: Populated m_routes
  // Postconditions: Reverses a specific route by reversing the airports
  //   in place. Must move airports, cannot just change data in airports.
  void ReverseRoute();
  // Name:  CalcDistance (provided - DO NOT EDIT)
  // Desc: Calculates the distance between two airports by using
  //  their coordinates
  //  Takes in airport1 latitude (North), Airport1 Longitude (West)
  //  Takes in airport2 latitude (North), Airport2 longitude (West)
  // Preconditions: Requires two airports with their N (in degrees)
  //  and W (in degrees)
  // Postconditions: Returns distance in miles between two airports
  double CalcDistance(double airport1_north, double airport1_west,
		      double airport2_north, double airport2_west) {
    double lat_new = airport2_north * DEG_2_RAD;
    double lat_old = airport1_north * DEG_2_RAD;
    double lat_diff = (airport1_north-airport2_north) * DEG_2_RAD;
    double lng_diff = (airport1_west-airport2_west) * DEG_2_RAD;

    double a = sin(lat_diff/2) * sin(lat_diff/2) +
      cos(lat_new) * cos(lat_old) *
      sin(lng_diff/2) * sin(lng_diff/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return double(EARTH_RADIUS) * c;
  }
private:
  vector<Airport*> m_airports; //Vector of all airports
  vector<Route*> m_routes; //Vector of all routes
  string m_fileName; //File to read in
};

#endif
