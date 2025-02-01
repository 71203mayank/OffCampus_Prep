#ifndef TAXI_APP_H
#define TAXI_APP_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Enum for cab type
enum class CabType{NORMAL, AC, LUXURY};

// Employee class
class Employee{
    protected:
        string name;
        char homeLocation;
        string designation;

    public:
        Employee(string name, char loc, string desig); // constructor
        virtual ~Employee(){}

        string getName() const;
        char getHomeLocation() const;
        virtual CabType getCabType() const = 0;
};

// Derived classes for different employees
class JuniorEmployee : public Employee{
    public:
        JuniorEmployee(string name, char loc);
        CabType getCabType() const override;
};

class SeniorEmployee : public Employee{
    public:
        SeniorEmployee(string name,char loc);
        CabType getCabType() const override;
};

class Manager : public Employee{
    public:
        Manager(string name, char loc);
        CabType getCabType() const override;
};

// Cab Class
class Cab{
    private:
        CabType type;
        double baseFare;
    
    public:
        Cab(CabType t);
        double calculateFare(double distance) const;
};

// Trip Class
class Trip{
    private:
        Employee* employee;
        Cab cab;
        double distance;
        double fare;
        string date;
    
    public:
        Trip(Employee* e, double dist, string date);
        void displayTrip() const;
        double getFare() const;
        string getEmployeeName() const;
        string getDate() const;
};

// TripManager: to handle trip records and reports
class TripManager{
    private:
        vector<Trip> trips;

    public:
        void addTrip(Employee* emp, double dist, string date);
        void generateTotalCostReport() const;
        void generateEmployeeReport(string empName) const;
        void generateMonthlyReport(string month) const;
};

#endif
