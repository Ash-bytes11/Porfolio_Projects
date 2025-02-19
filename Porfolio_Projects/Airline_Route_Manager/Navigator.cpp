#include "Navigator.h"

// Constructor that initializes a Navigator object with a file name.
Navigator::Navigator(string fileName = "proj3_data.txt") {
    m_fileName = fileName; // Assign the provided file name to the member variable.
}

// Destructor that cleans up dynamically allocated memory for airports and routes.
Navigator::~Navigator() {
    // Delete all dynamically allocated Airport objects.
    for (int i = 0; i < static_cast<int>(m_airports.size()); i++) {
        delete m_airports[i];
    }
    // Delete all dynamically allocated Route objects.
    for (int i = 0; i < static_cast<int>(m_routes.size()); i++) {
        delete m_routes[i];
    }
}

void Navigator::Start() {
    ReadFile();
    MainMenu();
}

// Displays all loaded airports to the console.
void Navigator::DisplayAirports() {
    // Check if there are no airports to display.
    if (m_airports.size() == 0) {
        cout << "No airports available." << endl;
        return;
    }
    // Iterate through the list of airports and display each one.
    for (int i = 0; i < static_cast<int>(m_airports.size()); i++) {
        cout << i + 1 << ". " << *m_airports[i] << endl;
    }
}

// Reads airport data from a file and populates the airports vector.
void Navigator::ReadFile() {
    ifstream inFile(m_fileName);
    if (!inFile.is_open()) {
        cerr << "Error opening file " << m_fileName << endl;
        return;
    }

    string line;
    // Read each line from the file.
    while (getline(inFile, line)) {
        vector<string> fields; // Temporary storage for the fields in each line.
        // Parse the line into comma-separated fields.
        int start = 0, end;
        while ((end = static_cast<int>(line.find(',', start))) != -1) {
            fields.push_back(line.substr(start, end - start));
            start = end + 1;
        }
        // Add the last field after the last comma.
        fields.push_back(line.substr(start));
        // If the correct number of fields are found, create a new Airport object.
        if (fields.size() == 6) {
            // Parse and store the fields.
            string code = fields[0];
            string name = fields[1];
            string city = fields[2];
            string country = fields[3];
            double latitude = stod(fields[4]);
            double longitude = stod(fields[5]);

            // Add the new Airport to the list.
            m_airports.push_back(new Airport(code, name, city, country, latitude, longitude));
        }
    }

    inFile.close();
    cout << "Opened file" << endl;
    cout << "Airports loaded: " << m_airports.size() << endl;
}


// Allows the user to create and add a new route.
void Navigator::InsertNewRoute() {
    cout << "Select airports for the new route (minimum 2 airports)." << endl;
    DisplayAirports(); // Show available airports to choose from.

    Route* route = new Route(); // Create a new route.

    int airportIndex;
    // Allow the user to select airports until they decide to finish.
    do {
        cout << "Enter the number of the airport to add to your Route: (-1 to end)" << endl;
        cin >> airportIndex;
        cin.ignore(); // Clear the input buffer to prevent input errors.

        // Validate the input and add the selected airport to the route.
        if (airportIndex >= 1 && airportIndex <= (int)m_airports.size()) {
            Airport* airport = m_airports[airportIndex - 1];
            route->InsertEnd(airport->GetCode(), airport->GetName(), airport->GetCity(), airport->GetCountry(), airport->GetNorth(), airport->GetWest());
        } else if (airportIndex != -1) {
            cout << "Invalid airport number - Please try again" << endl;
        }
    } while (airportIndex != -1);

    // Ensure the route has at least two airports.
    if (route->GetSize() < 2) {
        cout << "Route cannot have less than two airports." << endl;
        delete route; // Delete the route to avoid memory leak.
        return;
    }

    // Finalize and store the route.
    string routeName = route->UpdateName();
    cout << "Done Building a New Route named " << routeName << endl;

    m_routes.push_back(route); // Add the new route to the list of routes.
}


// Displays main menu
void Navigator::MainMenu() {
    int choice;
    do {
        cout << "What would you like to do?:\n"
             << "1. Create New Route\n"
             << "2. Display Route\n"
             << "3. Remove Airport From Route\n"
             << "4. Reverse Route\n"
             << "5. Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                InsertNewRoute();
                break;
            case 2:
                DisplayRoute();
                break;
            case 3:
                RemoveAirportFromRoute();
                break;
            case 4:
                ReverseRoute();
                break;
            case 5:
                cout << "Routes removed from memory" << endl;
                cout << "Deleting Airports" << endl;
                cout << "Deleting Routes" << endl;
                //~Navigator() desctructor is executed automatically.
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}

// Function to let the user choose one of the available routes.
int Navigator::ChooseRoute() {
    // CIf no routes are available to display.
    if (m_routes.size() == 0) {
        cout << "No routes to display" << endl;
        return -1; // Return -1 for invalid input
    }

    cout << "Which route would you like to use?" << endl;
    for (int i = 0; i < static_cast<int>(m_routes.size()); i++) {
        // Display each route with a numbering system.
        cout << i + 1 << ". " << m_routes[i]->UpdateName() << endl;
    }

    int choice; // Variable to hold the user's choice.
    bool validChoice = false; // Monitor the status of the choice validity.
    do {
        cin >> choice;
        
        // Validate the input: checks for input failure, or if the choice is outside the range of available routes.
        if (cin.fail() || choice < 1 || choice > static_cast<int>(m_routes.size())) {
            cout << "Invalid selection. Please choose a valid route number:" << endl;
            // Re-display all routes to allow the user to make a valid selection.
            for (int i = 0; i < static_cast<int>(m_routes.size()); i++) {
                cout << i + 1 << ". " << m_routes[i]->UpdateName() << endl;
            }
            cin.clear(); // Clear the error flag on cin to allow future input operations.
            cin.ignore(); // Clear input buffer
        } else {
            validChoice = true; // Set the flag to true to exit loop.
        }
    } while (!validChoice); // Repeat this process until a valid choice is made.

    return choice - 1; // Return the index of the chosen route (adjusted for zero-based indexing).
}



void Navigator::DisplayRoute() {
    // Prompt the user to choose a route and store the selected route's index.
    int routeIndex = ChooseRoute(); 

    // If the returned index is -1, it means no route was selected or available, so exit the function.
    if (routeIndex == -1) {
        return;
    }

    // Retrieve the pointer to the selected route based on the user's choice.
    Route* route = m_routes[routeIndex];

    // Display the name of the route.
    cout << route->UpdateName() << endl;

    // Iterate over each airport in the route to display its details.
    for (int i = 0; i < route->GetSize(); ++i) {
        // Get the pointer to the airport at position i in the route.
        Airport* airport = route->GetData(i);
        // Display the details of the airport including its code, name, city, country, and coordinates.
        cout << i + 1 << ". " << airport->GetCode() << ", " << airport->GetName() << ", " << airport->GetCity() << ", " << airport->GetCountry() << " (" << "N" << airport->GetNorth() << " W" << airport->GetWest() << ")" << endl;
    }
    // Display the total distance of the route
    cout << "The total miles of this route is " << RouteDistance(route) << " miles" << endl;
}


void Navigator::RemoveAirportFromRoute() {
    if (m_routes.size() == 0) {
        // If no route exists
        cout << "No routes to remove airports" << endl;
        return;
    }

    // Prompt the user to choose a route and store the selected route's index.
    int routeIndex = ChooseRoute();
    if (routeIndex == -1) {
        return;
    }

    // Retrieve the pointer to the selected route based on the user's choice.
    Route* route = m_routes[routeIndex];
    if (route->GetSize() < 3) {
        cout << "Route cannot have less than two airports." << endl;
        return;
    }

    // Display the current route and its airports to the user for reference.
    cout << route->UpdateName() << endl;
    for (int i = 0; i < route->GetSize(); ++i) {
        Airport* airport = route->GetData(i);
        cout << i + 1 << ". " << airport->GetCode() << ", " << airport->GetName()
             << ", " << airport->GetCity() << ", " << airport->GetCountry()
             << " (" << "N" << airport->GetNorth() << " W" << airport->GetWest() << ")" << endl;
    }

    // Prompt the user to choose the airport to remove from the route.
    int airportIndex;
    cout << "Which airport would you like to remove?\n";
    bool isValidInput = false;
    while (!isValidInput) {
        //  Get input from the user and check whether it is valid
        if (!(cin >> airportIndex) || airportIndex < 1 || airportIndex > route->GetSize()) {
        cin.clear(); // Clear error state
        cin.ignore(); // Clear input buffer
        cout << "Invalid airport number. Please enter a number between 1 and " << route->GetSize() << "." << endl;
        }  else {
        isValidInput = true; // Valid input, exit the loop
    }
}
    // Remove the selected airport from the route.
    cout << route->UpdateName() << endl;
    route->RemoveAirport(airportIndex - 1);

    // Display the updated route after removing the airport.
    for (int i = 0; i < route->GetSize(); ++i) {
        Airport* airport = route->GetData(i);
        cout << i + 1 << ". " << airport->GetCode() << ", " << airport->GetName()
             << ", " << airport->GetCity() << ", " << airport->GetCountry()
             << " (" << "N" << airport->GetNorth() << " W" << airport->GetWest() << ")" << endl;
    }

    // Prints updated route name
    cout << "Route named " << route->UpdateName() << " updated\n" << endl;
}


void Navigator::ReverseRoute() {
    // Check if there are no routes available.
    if (m_routes.size() == 0) {
        cout << "No routes to reverse" << endl;
        return;
    }

    // If no valid route is selected, exit function.
    int routeIndex = ChooseRoute();
    if (routeIndex == -1) {
        return;
    }

     // Retrieve the pointer to the selected route based on the user's choice.
    Route* route = m_routes[routeIndex];
    // Reverse the order of airports in the route. Calls the function from Route.cpp
    route->ReverseRoute();
    // Prints the updated reversed route name
    cout << "Done reversing Route " << route->UpdateName() << endl;
}

double Navigator::RouteDistance(Route* route) {
    double totalDistance = 0.0;

    // Iterate through each airport in the route, except the last one
    for (int i = 0; i < route->GetSize() - 1; i++) {
        Airport* currentAirport = route->GetData(i); // Get the current airport
        Airport* nextAirport = route->GetData(i + 1); // Get the next airport

        // Calculate the distance between the current and next airports. Calls the function from Navigator.h
        totalDistance += CalcDistance(currentAirport->GetNorth(), currentAirport->GetWest(),
                                       nextAirport->GetNorth(), nextAirport->GetWest());
    }
    return totalDistance; // Returns total distance
}
