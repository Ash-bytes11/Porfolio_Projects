#include <iostream>
#include "MoviePlayer.h"
#include "Movie.h"

int main (int argc, char* argv[]) {
  string movieFile;
  cout << "Welcome to UMBC Movie Player"<<endl;
  if(argc > 1){
    movieFile = argv[1];
  } else{
    cout << "One movie files required - try again" << endl;
    cout << "./proj5 proj5_movies.txt" << endl;
    return 0;
  }
  MoviePlayer* myMovie = new MoviePlayer(movieFile);
  myMovie->StartPlayer();
  delete myMovie;
  return 0;
}
