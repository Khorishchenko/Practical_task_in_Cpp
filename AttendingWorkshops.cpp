#include <iostream>
#include <string>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

struct Workshop
{
    int start_time;
    int end_time;
    int duration;
    
    Workshop( int start = 0, int dura = 0 ) :
        start_time(start), duration(dura), end_time(start + dura) {}
};

struct Available_Workshops
{
    const int n;
    Workshop *workshops;

    Available_Workshops( int n = 0 ) : n(n) 
    {
        workshops = new Workshop[n];
    }


    ~Available_Workshops()
    {
        delete[] workshops;
    }
};

Available_Workshops* initialize( int* start, int* durat, int size )
{
    Available_Workshops *aw = new Available_Workshops[size];
    for ( int i = 0; i < size; i++ )
    {
        aw->workshops[i] = Workshop(start[i] + durat[i]);
    }
    return aw;
}

int CalculateMaxWorkshops( Available_Workshops* ptr )
{
    // Копіюємо майстер-класи в вектор для зручного сортування
    std::vector<Workshop> workshops(ptr->workshops, ptr->workshops + ptr->n);
    
    // Сортуємо майстер-класи за часом закінчення
    std::sort(workshops.begin(), workshops.end(), [](const Workshop& a, const Workshop& b) {
        return a.end_time < b.end_time;
    });

    int maxWorkshops = 0;
    int currentEndTime = 0;

    for (const auto& workshop : workshops) {
        if (workshop.start_time >= currentEndTime) {
            // Якщо майстер-клас не перекривається з попереднім, відвідуємо його
            maxWorkshops++;
            currentEndTime = workshop.end_time;
        }
    }

    return maxWorkshops;

}

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops

int main(int argc, char *argv[]) 
{
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i = 0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize( start_time, duration, n );
    cout << CalculateMaxWorkshops( ptr ) << endl;
    return 0;
}