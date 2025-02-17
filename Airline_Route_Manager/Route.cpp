#include "Route.h"

Route::Route() {
    m_name = "";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

Route::~Route() {
    Airport* current = m_head;
    while (current != nullptr) {
        Airport* next = current->GetNext();
        delete current;
        current = next;
    }
}

void Route::SetName(string name) {
    m_name = name;
}

void Route::InsertEnd(string code, string name, string city, string country, double north, double west) {
    Airport* newAirport = new Airport(code, name, city, country, north, west);
    if (m_head == nullptr) {
        m_head = newAirport;
        m_tail = newAirport;
    } else {
        m_tail->SetNext(newAirport);
        m_tail = newAirport;
    }
    m_size++;
}

void Route::RemoveAirport(int index) {
    if (m_size <= 2) {
        cout << "Cannot remove airport. Route must have at least two airports." << endl;
        return;
    }

    if (index < 0 || index >= m_size) {
        cout << "Invalid index." << endl;
        return;
    }

    Airport* current = m_head;
    Airport* previous = nullptr;
    for (int i = 0; i < index; i++) {
        previous = current;
        current = current->GetNext();
    }

    if (current == m_head) {
        m_head = current->GetNext();
    } else if (current == m_tail) {
        m_tail = previous;
        m_tail->SetNext(nullptr);
    } else {
        previous->SetNext(current->GetNext());
    }

    delete current;
    m_size--;
}

string Route::GetName() {
    return m_name;
}

string Route::UpdateName() {
    if (m_head == nullptr || m_tail == nullptr) {
        return "";
    }
    return m_head->GetCity() + " to " + m_tail->GetCity();
}

int Route::GetSize() {
    return m_size;
}

void Route::ReverseRoute() {
    if (m_size < 2) {
        cout << "Route must have at least two airports to be reversed." << endl;
        return;
    }

    Airport* previous = nullptr;
    Airport* current = m_head;
    Airport* next = nullptr;

    while (current != nullptr) {
        next = current->GetNext();
        current->SetNext(previous);
        previous = current;
        current = next;
    }

    m_tail = m_head;
    m_head = previous;
}

Airport* Route::GetData(int index) {
    if (index < 0 || index >= m_size) {
        cout << "Invalid index." << endl;
        return nullptr;
    }

    Airport* current = m_head;
    for (int i = 0; i < index; i++) {
        current = current->GetNext();
    }

    return current;
}

void Route::DisplayRoute() {
    if (m_head == nullptr) {
        cout << "Route is empty." << endl;
        return;
    }

    Airport* current = m_head;
    while (current != nullptr) {
        cout << current->GetCity() << ", " << current->GetCountry() << " (N" << current->GetNorth() << " W" << current->GetWest() << ")" << endl;
        current = current->GetNext();
    }
}
