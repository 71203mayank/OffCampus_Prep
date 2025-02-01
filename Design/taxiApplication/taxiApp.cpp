#include "taxiApp.h"

// Employee Class
Employee::Employee(string name, char loc, string desig){
    this->name = name;
    this->homeLocation = loc;
    this->designation = desig;
}

string Employee::getName() const {
    return name;
}

char Employee::getHomeLocation() const{
    return homeLocation;
}

// Junior Employee
JuniorEmployee::JuniorEmployee(string name, char loc): Employee(name, loc, "Junior"){}
CabType JuniorEmployee::getCabType() const {
    return CabType::NORMAL;
}

// senior employee
SeniorEmployee::SeniorEmployee(string name, char loc) : Employee(name, loc, "Senior"){}
CabType SeniorEmployee::getCabType() const{
    return CabType::AC;
}

// manager
Manager::Manager(string name, char loc) : Employee(name, loc, "Manager"){}
CabType Manager::getCabType() const {
    return CabType::NORMAL;
}

// cab Class
Cab::Cab(CabType t) : type(t){
    if(type == CabType::NORMAL) baseFare = 10.0;
    else if(type == CabType::AC) baseFare = 15.0;
    else baseFare = 25.0;
}

double Cab::calculateFare(double distance) const{
    return baseFare * distance;
}

// Trip Class
Trip::Trip(Employee* e, double dist, string date) : employee(e), cab(e->getCabType()), distance(dist), date(date){
    fare = cab.calculateFare(distance);
}

void Trip::displayTrip() const {
    cout<<"Employee: "<<employee->getName()<<" | Distance: "<<distance<<" km | Fare: $"<<fare<<" | Date: "<<date<<endl;
}

double Trip::getFare() const {
    return fare;
}

string Trip::getEmployeeName() const {
    return employee->getName();
}

string Trip::getDate() const {
    return date;
}


// Class TripManager
void TripManager::addTrip(Employee *e, double dist, string date){
    Trip newTrip(e, dist, date);
    trips.emplace_back(newTrip);
}

void TripManager::generateTotalCostReport() const {
    double totalCost = 0;
    for(auto i : trips){
        totalCost += i.getFare();
    }

    cout<<"Total cost of all trips: $"<<totalCost <<endl;
}

void TripManager::generateEmployeeReport(string empName) const{
    cout<<"Trips for "<<empName<<":"<<endl;

    double totalCost = 0;
    for(auto i : trips){
        if(i.getEmployeeName() == empName){
            i.displayTrip();
            totalCost += i.getFare();
        }
    }

    cout<<"Total cost for "<<empName<<": $"<<totalCost<<endl;
}

void TripManager::generateMonthlyReport(string month) const{
    cout<<"Trip for the month "<< month<<":"<<endl;

    double totalCost = 0;
    for(auto i : trips){
        if(i.getDate().substr(5,2) == month){ // assuming date formate "YYYY-MM-DD"
            i.displayTrip();
            totalCost += i.getFare();
        }
    }

    cout<< "Total Cost for "<<month<<": $"<< totalCost<<endl;
}

// Main
int main(){
    TripManager manager;

    // Create employees;
    JuniorEmployee e1("Mayank", 'A');
    SeniorEmployee e2("Shalin", 'B');
    Manager e3("Avinash",'C');

    // Add trips
    manager.addTrip(&e1, 10, "2025-02-01");
    manager.addTrip(&e2, 15, "2025-02-02");
    manager.addTrip(&e3, 20, "2025-02-03");
    manager.addTrip(&e1, 12, "2025-03-05");

    // Reports;
    cout<<"\n---Total Cost Report ---\n";
    manager.generateTotalCostReport();

    cout<<"\n--- Employee Report (Mayank) ---\n";
    manager.generateEmployeeReport("Mayank");

    cout<<"\n--- Employee Report (Shalin) ---\n";
    manager.generateEmployeeReport("Shalin");

    cout<<"\n--- Monthly Report (Feb) ---\n";
    manager.generateMonthlyReport("02");

    cout<<"\n--- Monthly Report (March) ---\n";
    manager.generateMonthlyReport("03");

    return 0;

}