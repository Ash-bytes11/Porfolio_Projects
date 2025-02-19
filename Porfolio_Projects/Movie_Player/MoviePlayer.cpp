#include "MoviePlayer.h"

// Default Constructor
MoviePlayer::MoviePlayer() {
    // Default filename for movie catalog
    m_filename = "proj5_movies.txt";
}

// Overloaded Constructor
MoviePlayer::MoviePlayer(string filename) {
    // Set filename for movie catalog
    m_filename = filename;
}

// Destructor
MoviePlayer::~MoviePlayer() {
    // Deallocate memory for each movie in the catalog
    for (size_t i = 0; i < m_movieCatalog.size(); i++) {
        delete m_movieCatalog[i];
    }
    // Clear the movie catalog
    m_movieCatalog.clear();
}


// LoadCatalog: Reads movie data from a file and populates the movie catalog
void MoviePlayer::LoadCatalog() {
    // Open the input file
    ifstream inputFile(m_filename);
    if (!inputFile) {
        cerr << "Error: Unable to open file " << m_filename << endl;
        return;
    }

    string line;
    // Read each line from the file
    while (getline(inputFile, line)) {
        // Parse the line to extract movie information
        // Format: Title;Rating;Genre;Year;Director;Star;Budget;Gross;Studio;Runtime
        string title, rating, genre, director, star, studio;
        int year, runtime;
        long budget, gross;

        // Use stringstream for parsing
        stringstream ss(line);
        getline(ss, title, ';');
        getline(ss, rating, ';');
        getline(ss, genre, ';');
        ss >> year; ss.ignore();
        getline(ss, director, ';');
        getline(ss, star, ';');
        ss >> budget; ss.ignore();
        ss >> gross; ss.ignore();
        getline(ss, studio, ';');
        ss >> runtime;

        // Create a new Movie object and add it to the movie catalog
        m_movieCatalog.push_back(new Movie(title, rating, genre, year, director, star, budget, gross, studio, runtime));
    }

    // Close the input file
    inputFile.close();
}


// MainMenu function displays the main menu options and handles user input
void MoviePlayer::MainMenu() {
    cout << m_movieCatalog.size() << " movie files loaded." << endl;

    int choice;
    // Main menu loop
    do {
        cout << "What would you like to do?" << endl;
        cout << "1. Display Movie by Type and Year" << endl;
        cout << "2. Add Movie to Playlist" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Sort Playlist by Year" << endl;
        cout << "5. Search for Movie" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 6) {
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        } else {
            switch (choice) {
                case 1:
                    DisplayMovie();
                    break;
                case 2:
                    AddMovie();
                    break;
                case 3:
                    DisplayPlaylist();
                    break;
                case 4:
                    SortPlaylist();
                    break;
                case 5:
                    SearchMovie();
                    break;    
                case 6:
                    cout << "Thank you for using the UMBC Movie Player!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }
    } while (choice != 6); // Repeat until the user chooses to quit
}



void MoviePlayer::SearchMovie() {
    cout << "What do you want to search by?" << endl;
    cout << "1. Word in Title or Director" << endl;
    cout << "2. Year" << endl;
    cout << "3. Earnings" << endl;

    int searchChoice;
    bool validSearchChoice = false;
    do {
        cout << "Enter your choice: ";
        cin >> searchChoice;

        if (searchChoice >= 1 && searchChoice <= 3) {
            validSearchChoice = true;
        } else {
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(); // Discard invalid input
        }
    } while (!validSearchChoice);

    if (searchChoice == 1) {
        cout << "What string would you like to search?" << endl;
        string searchString;
        cin.ignore(); // Ignore previous newline character
        getline(cin, searchString);

        int count = 0;
        for (Movie* movie : m_movieCatalog) {
            if (movie->GetTitle().find(searchString) != string::npos ||
                movie->GetDirector().find(searchString) != string::npos) {
                cout << ++count << ". " << *movie << endl;
            }
        }

        if (count == 0) {
            cout << "No movies found." << endl;
        }
    } else if (searchChoice == 2) {
        int searchYear;
        cout << "Enter the year you want to search for: ";
        cin >> searchYear;

        int count = 0;
        for (Movie* movie : m_movieCatalog) {
            if (movie->GetYear() == searchYear) {
                cout << ++count << ". " << *movie << endl;
            }
        }

        if (count == 0) {
            cout << "No movies found." << endl;
        }
    } else if (searchChoice == 3) {
        long minProfit;
        cout << "Enter the minimum profit: ";
        cin >> minProfit;

        int count = 0;
        for (Movie* movie : m_movieCatalog) {
            if ((movie->GetGross() - movie->GetBudget()) >= minProfit) {
                cout << ++count << ". " << *movie << endl;
            }
        }
        cout << count << " movies found." << endl;

        if (count == 0) {
            cout << "No movies found." << endl;
        }
    }
}







// DisplayMovie function allows the user to display movies based on year and genre
int MoviePlayer::DisplayMovie() {
    int year;
    // Ask the user for the year
    cout << "Which year would you like to display? (" << MIN_YEAR << "-" << MAX_YEAR << ")" << endl;
    cin >> year;
    // Validate the year input
    while (year < MIN_YEAR || year > MAX_YEAR) {
        cout << "Invalid year. Please enter a year between " << MIN_YEAR << " and " << MAX_YEAR << ": ";
        cin >> year;
    }

    // Display the selected year
    cout << "******" << year << "******" << endl;

    string genre;
    // Ask the user for the genre
    cout << "Which genre would you like?" << endl;
    cin.ignore(); // Ignore previous newline character
    getline(cin, genre);

    // Display the selected genre
    cout << "******" << genre << "******" << endl;

    // Display the total number of movies in the catalog
    cout << "MOVIES TOTAL: " << m_movieCatalog.size() << endl;

    // Open the file containing the movie details
    ifstream file(m_filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 0;
    }

    string line;
    int lineNumber = 1;
    int count = 0;
    bool done = false;
    // Read each line of the file
    while (getline(file, line) && !done) {
        // Stop reading the file once all movies are processed
        if (lineNumber > static_cast<int>(m_movieCatalog.size())) {
            done = true;
        } else {
            // Get the movie details from the catalog
            Movie* movie = m_movieCatalog[lineNumber - 1]; // Line numbers are 1-based
            // Display the movie if it matches the selected year and genre
            if (movie->GetYear() == year && movie->GetGenre() == genre) {
                cout << lineNumber << " " << movie->GetTitle() << " by " << movie->GetDirector() << " from " << movie->GetYear() << endl;
                count++;
            }
        }

        lineNumber++;
    }

    // Close the file
    file.close();

    // Display the number of movies found
    cout << count << " movies found." << endl;
    cout << endl;
    return count;
}



// AddMovie function allows the user to add a movie to the playlist
void MoviePlayer::AddMovie() {
    // Display the current playlist
    DisplayPlaylist();

    // Display movies based on user input
    int count = DisplayMovie();
    // If no movies are found, return
    if (count == 0) {
        return;
    }

    // Ask the user to select a movie to add
    cout << "Choose the movie you would like to add to the playlist." << endl;
    cout << "Enter the number of the movie you would like to add: ";
    int index;
    cin >> index;

    // Validate the user's input
    while (index < 0 || index >= static_cast<int>(m_movieCatalog.size())) {
        cout << "Invalid index. Please enter a number between 0 and " << m_movieCatalog.size() - 1 << ": ";
        cin >> index;
    }

    // Get the selected movie from the catalog
    Movie* selectedMovie = m_movieCatalog[index - 1];

    // Check if the selected movie is already in the playlist
    bool alreadyAdded = false;
    for (int i = 0; i < m_playList.GetSize(); ++i) {
        if (selectedMovie == m_playList.At(i)) {
            alreadyAdded = true;
            break;
        }
    }

    if (alreadyAdded) {
        cout << "You have already added this movie to the playlist." << endl;
    } else {
        // Inform the user that the movie has been added to the playlist
        cout << *selectedMovie << " added to the playlist." << endl;
        cout << endl;
        // Add the selected movie to the playlist
        m_playList.PushBack(selectedMovie);
    }
}




// DisplayPlaylist function displays the current playlist
void MoviePlayer::DisplayPlaylist() {
    // Check if the playlist is empty
    if (m_playList.IsEmpty()) {
        cout << "The playlist is currently empty." << endl;
        return;
    }

    // Display the current playlist
    cout << endl;
    cout << "Current Playlist:" << endl;
    // Iterate over the playlist and display each movie
    for (int i = 0; i < m_playList.GetSize(); i++) {
        cout << i + 1 << ". " << *m_playList.At(i) << endl;
    }
    cout << endl;
}



// SortPlaylist function sorts the playlist by year
void MoviePlayer::SortPlaylist() {
    // Check if the playlist is empty
    if (m_playList.IsEmpty()) {
        cout << "The playlist needs at least two movies to sort." << endl;
        return;
    }

    // Sort the playlist by year
    m_playList.Sort();

    // Display a message indicating the sorting is done
    if (m_playList.GetSize() != 0){
        cout << "Done sorting by year." << endl;
        // Display the number of items sorted
        cout << m_playList.GetSize() << " items sorted" << endl;
    }    
}





// StartPlayer function initializes the movie player by loading the catalog and starting the main menu
void MoviePlayer::StartPlayer() {
    // Load the movie catalog from the file
    LoadCatalog();
    // Display the main menu for user interaction
    MainMenu();
}

