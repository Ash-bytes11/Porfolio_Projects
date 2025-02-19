#include <iostream>
#include <string>
using namespace std;

#ifndef MOVIE_H
#define MOVIE_H

class Movie{
 public:
  //Name: Movie - Default Constructor
  //Precondition: None
  //Postcondition: Creates a default movie
  Movie();
  //Name: Movie - Overloaded Constructor
  //Precondition: Requires title, rating, genre, year, director, star,
  //              budget, gross, studio, and runtime
  //Postcondition: Creates a movie entry based on passed parameters
  Movie(string title, string rating, string genre, int year, string director,
	string star, long budget, long gross, string studio, int runtime);
  //Name: Mutators and Accessors
  //Precondition: None
  //Postcondition: Sets and Gets private member variables
  string GetTitle()const; // return title
  string GetRating()const; // return rating
  string GetGenre()const; //return genre
  int GetYear()const; // return year
  string GetDirector()const; // returns director
  string GetStar() const; // returns star
  long GetBudget() const; // returns budget
  long GetGross() const; // returns total box office returns (gross)
  string GetStudio() const; // returns studio
  int GetRuntime() const; //returns runtime of movie (in minutes)
  void SetTitle(string title);
  void SetRating(string rating);
  void SetGenre(string genre);
  void SetYear(int year);
  void SetDirector(string director);
  void SetStar(string star);
  void SetBudget(long budget);
  void SetGross(long gross);
  void SetStudio(string studio);
  void SetRuntime(int runtime);
  //Name: Overloaded << operator
  //Precondition: movie available
  //Postcondition: Returns output stream including title by director from year
  friend ostream& operator<<(ostream& out, Movie& m);
  //Name: Overloaded Relational Operator (<)
  //Precondition: Two movie objects required
  //Postcondition: if passed movie's year is less than first,
  //               return true else false
  bool operator<(const Movie& m);
  //Name: Overloaded Relational Operator (>)
  //Precondition: Two movie objects required
  //Postcondition: if passed movie's year is greater than first,
  //               return true else false
  bool operator>(const Movie& m);
private:
  string m_title; //Title of movie
  string m_rating; //Rating of movie (G, PG, PG-13, R)
  string m_genre; //Genre of movie
  int m_year; //Year of release
  string m_director; //Director of movie
  string m_star; //Star of movie
  long m_budget; //Total budget of movie (in dollars) 
  long m_gross; //Total box office take of movie (in dollars)
  string m_studio; //Studio who released movie
  int m_runtime; //Total length of movie (in minutes)
};

#endif
