//Name: Airport.h
//Author:  Aswanth Jeyaram Kumar
//Date:    4/10/2024
//Desc: This file contains the header details for the Airport class
//      The airports are nodes for a route

#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Airport {
 public:
  // Name: Airport() - Default Constructor
  // Desc: Used to build a new empty airport
  // Preconditions: None
  // Postconditions: Creates a new Airport for use in a Route
  Airport();
  // Name: Airport(string, string, string, string, double, double)
  // Overloaded Constructor
  // Desc: Used to build a new Airport passing it a
  //   airport code, name, city, country, north, and west
  // Preconditions: None
  // Postconditions: Creates a new airport for use in a Route
  Airport(string, string, string, string, double, double);
  // Name: ~Airport() - Destructor
  // Desc: Used to destruct a airport
  //**This function should be empty but must be implemented
  // Preconditions: There is an existing airport
  // Postconditions: Airport is deallocated and has no memory leaks!
 ~Airport();
  // Name: GetCode()
  // Desc: Returns the three letter code of the airport
  // Preconditions: None
  // Postconditions: Returns the three letter code of the airport
  string GetCode();
  // Name: GetName()
  // Desc: Returns the name of the airport
  // Preconditions: None
  // Postconditions: Returns the name of the airport
  string GetName();
  // Name: GetNext()
  // Desc: Returns the pointer to the next airport
  // Preconditions: None (may return either airport or nullptr)
  // Postconditions: Returns m_next;
  Airport* GetNext();
  // Name: GetNorth()
  // Desc: Returns the northern coordinates of the airport
  // Preconditions: None
  // Postconditions: Returns the N coordinates of the port
  double GetNorth();
  // Name: GetWest()
  // Desc: Returns the western coordinates of the airport
  // Preconditions: None
  // Postconditions: Returns the W coordinates of the airport
  double GetWest();
  // Name: GetCity()
  // Desc: Returns the city of where the airport is located
  // Preconditions: None
  // Postconditions: Returns the city of where the airport is located
  string GetCity();
  // Name: GetCountry()
  // Desc: Returns the country of where the airport is located
  // Preconditions: None
  // Postconditions: Returns the country of where the airport is located
  string GetCountry();
  // Name: SetNext()
  // Desc: Updates the pointer to a new target (either a airport or nullptr)
  // Preconditions: None
  // Postconditions: Sets the next airport
  void SetNext(Airport*);
  // Name: operator<<
  // Desc: Overloaded << operator to return ostream from an Airport
  // Must not have a cout statement in this
  // Preconditions: Requires an Airport
  // Postconditions: Returns ostream populated with Airport's name and city
  // **PROVIDED** Do not edit
  friend ostream &operator<< (ostream &output, Airport &myAirport){
    output << myAirport.m_name << ", " << myAirport.m_city;
    return output;
  }
private:
  string m_code; //Airport code (three letters)
  string m_name; //Name of airport
  string m_city; //City of airport
  string m_country; //Country of airport
  double m_north; //North of airport
  double m_west; //West of airport
  Airport *m_next; //Airport pointer to next airport
};

#endif
