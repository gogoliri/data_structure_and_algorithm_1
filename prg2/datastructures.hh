// Datastructures.hh
//
// Student name: Khoa Pham Dinh
// Student email: khoa.phamdinh@tuni.fi
// Student number: 050359620

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
// added later
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

// Types for IDs
using StationID = std::string;
using TrainID = std::string;
using RegionID = unsigned long long int;
using Name = std::string;
using Time = unsigned short int;

// Return values for cases where required thing was not found
StationID const NO_STATION = "---";
TrainID const NO_TRAIN = "---";
RegionID const NO_REGION = -1;
Name const NO_NAME = "!NO_NAME!";
Time const NO_TIME = 9999;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();


// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    //
    //
    // Estimate of performance: O(1)
    // Short rationale for estimate: Asymptotic of map size is O(1)
    unsigned int station_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Asymptotic of map, set clear is O(n)
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The for-loop goes through all element of set is O(n), push_back is O(1)
    std::vector<StationID> all_stations();

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: In the first if, find an element is O(1) for unordered map
    // Add new key to map is O(log(n))
    // Add new element to set is O(log(n))
    // overal is O(log(n))
    bool add_station(StationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered map find has theta(1) and O(n)
    Name get_station_name(StationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered map find has theta(1) and O(n)
    Coord get_station_coordinates(StationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: first, loop through all_stations_info is O(n)
    // Then for each item, at it to the set to be sorted is O(log(n))
    // So the operation is O(nlog(n))
    // Loop through the set and push back item to the vectr is O(n*1)
    // Totail is O(nlog(n))
    std::vector<StationID> stations_alphabetically();

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: first, loop through all_stations_info is O(n)
    // Then for each item, add it to the vector to be sorted is O(1)
    // So the operation is O(n)
    // Finally, sort the ID base on its distance is O(nlog(n))
    // Add the sorted pair to a vector result is O(n)
    // In conclusion, O(nlog(n))
    std::vector<StationID> stations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: loop through every element is O(n)
    StationID find_station_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find station in datastructure -> O(n) and theta(1)
    // change coord O(1) -> total is O(n) and theta(1)
    bool change_station_coord(StationID id, Coord newcoord);

    // Estimate of performance: O(n) 
    // Short rationale for estimate: find station in unordered map is theta(1) and O(n)
    // std::find_if is O(n) 
    // push_back is O(1)
    bool add_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find station in unordered map is O(1) and O(n) 
    // std::find_if is O(n)
    // vector.erase() is O(n)
    bool remove_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: first, find station in unoredered map is theta(1) and O(n)
    // sort is O(nlog(n))
    // find if is O(n)
    // initalize subvector is O(n)
    std::vector<std::pair<Time, TrainID>> station_departures_after(StationID stationid, Time time);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: find and [] in unordered map is theta(1) and O(n)
    bool add_region(RegionID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: the for loop goes through all region in unordered map
    std::vector<RegionID> all_regions();

    // Estimate of performance: O(n) 
    // Short rationale for estimate: find in unordered map theta(1) and O(n)
    Name get_region_name(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find in unordered map is theta(1) and O(n)
    std::vector<Coord> get_region_coords(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find parent/sub region take theta(1) or O(n) for unordered map
    // insert take log(n), total is O(n)
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find parent region and sub station take theta(1) and O(n) for unordered map
    // assign parent for sub station take O(1)
    bool add_station_to_region(StationID id, RegionID parentid);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: find station, and direct parent in unordered maps is theta(1) and O(n) each
    // the while loop take O(n), each iteration take theta(1) and O(n) -> somewhat O(log(n)) on average
    // So, total is O(nlog(n))
    std::vector<RegionID> station_in_regions(StationID id);

    // Non-compulsory operations

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: find in unordered map is theta(1) and O(n)
    // the sbregion_set go through every subregion and insert an element to a set which is O(nlog(n))
    std::vector<RegionID> all_subregions_of_region(RegionID id);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: loop through the unordered map is O(n)
    // sort a vector is O(nlogn)
    // loop through vector is O(n)
    // Total is O(nlog(n))
    std::vector<StationID> stations_closest_to(Coord xy);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: find station in unordered map is theta(1) and O(n)
    // erase station from unordered map is O(1)
    // erase station from a set is O(log(n))
    bool remove_station(StationID id);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: find region 1 and 2 is theta(1) and O(n)
    // first while loop goes thourgh every parent(take O(n)) and use find (take theta(1) and O(n))
    // on average -> total is O(nlog(n))
    // second while loop goes through every parent (take O(n)) and use find (take theta(1) and O(n))
    // on average -> total is O(nlog(n))
    // In total, the operation is O(nlog(n))
    RegionID common_parent_of_regions(RegionID id1, RegionID id2);
    

    // New assignment 2 operations
    //

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: for loop is O(n), insert to a set inside the loop is O(log(n))
    // total is O(nlog(n))
    bool add_train(TrainID trainid, std::vector<std::pair<StationID, Time>> stationtimes);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: for loop is O(n), there is std::find_if in a loop which is O(n)
    // total is O(n^2)
    std::vector<StationID> next_stations_from(StationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: there is only O(1) action in each O(n) loop
    std::vector<StationID> train_stations_from(StationID stationid, TrainID trainid);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: loop is O(n), clear is O(n) inside loop, total is O(n^2)
    void clear_trains();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: While loop for BFS is O(n), for loop for adj list is O(n) in while loop
    // find() is O(1) for unordered_set/map. Total is O(n^2)
    std::vector<std::pair<StationID, Distance>> route_any(StationID fromid, StationID toid);

    // Non-compulsory operations

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: while loop for BFS is O(n), for loop for adj list is O(n) in while loop
    // find() is O(1) for unordered_set/map. Total is O(n^2)
    std::vector<std::pair<StationID, Distance>> route_least_stations(StationID fromid, StationID toid);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: while loop for DFS is O(n), for loop for adj list is O(n) in while loop
    // find() is O(1) for unordered_set/map. Total is O(n^2)
    std::vector<StationID> route_with_cycle(StationID fromid);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: the big while loop for Djisktra is O(n), the for loop for adj list is O(n)
    // find() is O(1) for unordered_set/map. Total is O(n^2)
    std::vector<std::pair<StationID, Distance>> route_shortest_distance(StationID fromid, StationID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<StationID, Time>> route_earliest_arrival(StationID fromid, StationID toid, Time starttime);

private:
    // Add stuff needed for your class implementation here
    // Struct for region 
    struct region{
        Name name;
        // vector of coordinate
        std::vector<Coord> coords;
        // direct parent of a region
        //std::pair<RegionID, region>* parent_region; //pointer = all_regins_info.find() 
        RegionID parent_region = NO_REGION;
        // direct subregions of region
        std::set<RegionID> direct_sub;
    };
    // Create a struct for station
    struct station{
        Name name;
        Coord coordinate;
        RegionID parent_region = NO_REGION;
        std::vector<std::pair<Time, TrainID>> schedules;
        
        // Asignment 2
        // station ID, distance 
        std::set<std::pair<StationID, Distance>> stations_in;
    };

    // map for station
    std::unordered_map<StationID, station> all_stations_info;
    
    // map for region
    std::unordered_map<RegionID, region> all_regions_info;
    
    // function to find subregions but return a set
    std::set<RegionID> subregions_set(RegionID id);

    // station id 
    std::set<StationID> station_id_set;
   
    // Assignment 2
    // calculate distance between 2 coords
    Distance distance_cal(Coord coord1, Coord coord2);
    
    // map for train
    std::unordered_map<TrainID, std::vector<std::pair<StationID, Time>>> all_trains_info;

};

#endif // DATASTRUCTURES_HH
