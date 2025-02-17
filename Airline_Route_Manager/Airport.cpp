#include "Airport.h"

Airport::Airport() {
    m_code = "";
    m_name = "";
    m_city = "";
    m_country = "";
    m_north = 0.0;
    m_west = 0.0;
    m_next = nullptr;
}

Airport::Airport(string code, string name, string city, string country, double north, double west) {
    m_code = code;
    m_name = name;
    m_city = city;
    m_country = country;
    m_north = north;
    m_west = west;
    m_next = nullptr;
}

Airport::~Airport() {
    // No dynamic memory to free
}

string Airport::GetCode() {
    return m_code;
}

string Airport::GetName() {
    return m_name;
}

Airport* Airport::GetNext() {
    return m_next;
}

double Airport::GetNorth() {
    return m_north;
}

double Airport::GetWest() {
    return m_west;
}

string Airport::GetCity() {
    return m_city;
}

string Airport::GetCountry() {
    return m_country;
}

void Airport::SetNext(Airport* next) {
    m_next = next;
}

