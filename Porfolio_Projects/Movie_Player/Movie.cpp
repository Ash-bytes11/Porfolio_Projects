#include "Movie.h"
#include <iostream>

// Default constructor
Movie::Movie() {
    m_title = "";
    m_rating = "";
    m_genre = "";
    m_year = 0;
    m_director = "";
    m_star = "";
    m_budget = 0;
    m_gross = 0;
    m_studio = "";
    m_runtime = 0;
}

// Overloaded constructor
Movie::Movie(string title, string rating, string genre, int year, string director,
             string star, long budget, long gross, string studio, int runtime) {
    m_title = title;
    m_rating = rating;
    m_genre = genre;
    m_year = year;
    m_director = director;
    m_star = star;
    m_budget = budget;
    m_gross = gross;
    m_studio = studio;
    m_runtime = runtime;
}

// Accessors

// Get the title of the movie
string Movie::GetTitle() const {
    return m_title;
}

// Get the rating of the movie
string Movie::GetRating() const {
    return m_rating;
}

// Get the genre of the movie
string Movie::GetGenre() const {
    return m_genre;
}

// Get the year of the movie
int Movie::GetYear() const {
    return m_year;
}

// Get the director of the movie
string Movie::GetDirector() const {
    return m_director;
}

// Get the star of the movie
string Movie::GetStar() const {
    return m_star;
}

// Get the budget of the movie
long Movie::GetBudget() const {
    return m_budget;
}

// Get the gross income of the movie
long Movie::GetGross() const {
    return m_gross;
}

// Get the studio of the movie
string Movie::GetStudio() const {
    return m_studio;
}

// Get the runtime of the movie
int Movie::GetRuntime() const {
    return m_runtime;
}

// Mutators

// Set the title of the movie
void Movie::SetTitle(string title) {
    m_title = title;
}

// Set the rating of the movie
void Movie::SetRating(string rating) {
    m_rating = rating;
}

// Set the genre of the movie
void Movie::SetGenre(string genre) {
    m_genre = genre;
}

// Set the year of the movie
void Movie::SetYear(int year) {
    m_year = year;
}

// Set the director of the movie
void Movie::SetDirector(string director) {
    m_director = director;
}

// Set the star of the movie
void Movie::SetStar(string star) {
    m_star = star;
}

// Set the budget of the movie
void Movie::SetBudget(long budget) {
    m_budget = budget;
}

// Set the gross income of the movie
void Movie::SetGross(long gross) {
    m_gross = gross;
}

// Set the studio of the movie
void Movie::SetStudio(string studio) {
    m_studio = studio;
}

// Set the runtime of the movie
void Movie::SetRuntime(int runtime) {
    m_runtime = runtime;
}

// Overloaded << operator to print Movie information
ostream& operator<<(ostream& out, Movie& m) {
    out << m.GetTitle() << " by " << m.GetDirector() << " from " << m.GetYear();
    return out;
}

// Overloaded < operator to compare Movies based on year
bool Movie::operator<(const Movie& m) {
    return m_year < m.GetYear();
}

// Overloaded > operator to compare Movies based on year
bool Movie::operator>(const Movie& m) {
    return m_year > m.GetYear();
}
