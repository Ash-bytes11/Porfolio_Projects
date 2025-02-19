#ifndef MOVIEPLAYER_H
#define MOVIEPLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Movie.h"
#include "Queue.cpp"

using namespace std;

//**********Project Constants**************
const int MIN_YEAR = 1980; //Earliest year of movies in input file
const int MAX_YEAR = 2020; //Latest year of movies in input file


class MoviePlayer{
 public:
  //Name: MoviePlayer - Default Constructor
  //Precondition: None
  //Postcondition: Creates a new MoviePlayer with m_filename of "proj5_movies.txt"
  MoviePlayer();
  //Name: MoviePlayer - Overloaded Constructor
  //Precondition: None
  //Postcondition: Creates a new MoviePlayer with passed filename
  MoviePlayer(string filename);
  //Name: ~MoviePlayer - Destructor
  //Precondition: None
  //Postcondition: Deallocates movies from m_movieCatalog
  ~MoviePlayer();
  //Name: LoadCatalog()
  //Precondition: Requires m_filename to be populated
  //Postcondition: Dynamically allocates each movie and inserts into m_movieCatalog
  //Hint:          Allowed to use stoi (string to integer) if needed
  //Hint:          Allowed to use stoul (string to long) if needed
  void LoadCatalog();
  //Name: MainMenu
  //Precondition: None
  //Postcondition: Manages the menu
  void MainMenu();
  //Name: DisplayMovie
  //Desc: Asks user for year (between min and max year)
  //      Asks user for genre (no validation)
  //      Displays all movies with year and genre with location in vector
  //      Uses iterators
  //Precondition: m_movieCatalog, MIN_YEAR, and MAX_YEAR are all populated
  //Postcondition: Returns count of movies found matching year and genre else 0
  //Hint: Allowed to use ** if necessary
  int DisplayMovie();
  //Name: AddMovie
  //Desc: Calls DisplayMovie where user chooses year and genre
  //      User enters index of movie to choose
  //      Validates for number to be between 0 - m_movieCatalog size
  //      Does NOT validate that movie chosen was from year and genre
  //      Uses overloaded << operator to display the example below
  //Example: Airplane! by Jim Abrahams from 1980 added to the playlist
  //Precondition: m_movieCatalog is populated
  //Postcondition: Adds pointer from m_catalog and inserts into m_playList
  void AddMovie();
  //Name: DisplayPlaylist
  //Precondition: None (will indicate if list is empty)
  //Postcondition: Displays the playlist using the overloaded << operator
  void DisplayPlaylist();
  //Name: SortPlaylist
  //Precondition: None (will indicate if list is empty)
  //Postcondition: Sorts the playlist by year
  void SortPlaylist();
  //Name: StartPlayer
  //Precondition: None (file name has already been provided)
  //Postcondition: Loads file and calls main menu
  void StartPlayer();
  //Name: SearchMovie
  //Precondition: None
  //Postcondition: Executes SearchString, SearchYear, or SearchEarnings of movies based on user choice
  void SearchMovie();

private:
  string m_filename; //Name of input file
  vector<Movie*> m_movieCatalog; //Holds all movies in file
  Queue<Movie*> m_playList; //Holds all movies in play list
};


#endif
