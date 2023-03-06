// Datastructures.cc
//
// Student name: Khoa Pham Dinh
// Student email: khoa.phamdinh@tuni.fi
// Student number: 050359620
//

#include "datastructures.hh"

#include <algorithm>
#include <random>

#include <cmath>
#include <unordered_set>
#include <vector>
std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}
/**
 * @brief station_count return the number of station in the data structure
 * @return size of the data structure
 */
unsigned int Datastructures::station_count()
{
    return all_stations_info.size();
}

/**
 * @brief clear_all clear all the data in  data structure
 */
void Datastructures::clear_all()
{
   // clear all the data structure
   all_stations_info.clear();
   all_regions_info.clear(); 
   station_id_set.clear();
}

/**
 * @brief all_stations return id of all stations in vectors
 * @return vector of StationID
 */
std::vector<StationID> Datastructures::all_stations()
{
    // loop through the data structure
    std::vector<StationID> result;
    for(auto& item : station_id_set){
        result.push_back(item);
    }
    return result;

}

/**
 * @brief add_station add station and its attribution to the data structure
 * @param id the id of the station to add
 * @param name the name of the station to add
 * @param xy the coordinate of the station to add
 * @return true if successfully add the station, false if the station is already in the data structure 
 */
bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    
    
    // Find the station in the data structure
    if (all_stations_info.find(id) != all_stations_info.end()){
        return false;
    }
    
    // initialize a new station
    struct station new_station = {
        .name = name,
        .coordinate = xy,
    };

    // add new station to data structure
    all_stations_info[id] = new_station;
    station_id_set.insert(id);
    return true;

}

/**
 * @brief get_station_name get name of the station from id
 * @param id station to get name from
 * @return name of the station
 * NO_NAME if there is no such station
 */
Name Datastructures::get_station_name(StationID id)
{
    // loop through the data structure to find the target station
    auto s = all_stations_info.find(id);
    if( s != all_stations_info.end()){
        return s->second.name;
    }
    return NO_NAME;
}

/**
 * @brief get_station_coordinates get coords of the station from id
 * @param id station to get coordinates from
 * @return coordinates of the station
 * NO_COORD if there is no such station
 */
Coord Datastructures::get_station_coordinates(StationID id)
{
    // Loop through the data structure to find the target station
    auto s = all_stations_info.find(id);    
    if( s != all_stations_info.end()){
        return s->second.coordinate;
    }
    return NO_COORD;
}

/**
 * @brief stations_alphabetically return the station id but in order of name
 * @return a vector of StationID contain station id with name sorted
 */
std::vector<StationID> Datastructures::stations_alphabetically()
{
    
    // initialized the containers
    std::multimap<Name, StationID> tobe_sorted;
    std::vector<StationID> result;
    
    // Loop through the data structure to add the pairs
    // multi map will sort the data according to the first element
    for(auto item: all_stations_info)
    {   
        tobe_sorted.insert({item.second.name, item.first});
    }
    
    // Data is already sorted, so I just add it to a vector to be returned
    for(auto item : tobe_sorted){
        result.push_back(item.second);
    }
    
    return result;
}

/**
 * @brief stations_distance_increasing return the station id but in order of coords
 * @return a vector of Station ID contain station id with coord sorted
 */
std::vector<StationID> Datastructures::stations_distance_increasing()
{
    
    std::vector<std::pair<StationID, station>> tobe_sorted;
    std::vector<StationID> result;
    
    // Loop through the data structure to add data to a container
    for(auto item : all_stations_info)
    {
        tobe_sorted.push_back({item.first, item.second});
    }
    
    // Sort the distance using std
    std::sort(tobe_sorted.begin(), tobe_sorted.end(), [](std::pair<StationID, station> a, std::pair<StationID, station> b){
            auto coord_a = a.second.coordinate;
            auto coord_b = b.second.coordinate;
            
            auto dis_a = pow(pow(coord_a.x, 2) + pow(coord_a.y, 2), 0.5); 
            auto dis_b = pow(pow(coord_b.x, 2) + pow(coord_b.y, 2), 0.5); 
            
            if(dis_a == dis_b){
                
                return coord_a < coord_b;
            }
            return dis_a < dis_b;
            });
   
    for(auto s: tobe_sorted){
        result.push_back(s.first);
    }
    
    return result;
}


/**
 * @brief find_station_with_coord find the station id that associate with a given coordinate
 * @param xy coordinate of the station to be found
 * @return the station id that has given coords
 * NO_STATION if there is no station with give xy
 */
StationID Datastructures::find_station_with_coord(Coord xy)
{
    // Loop through data structure to find 
    for(auto it = all_stations_info.begin(), end = all_stations_info.end(); it != end; it++){
        if(it->second.coordinate == xy){
            return it->first;
        }
    }
    return NO_STATION;
}

/**
 * @brief change_station_coord  change coord of a given station
 * @param id the id of given station
 * @param newcoord new coord of a given statuon
 * @return true if change successfully, false if staion id not in data structure
 */
bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{
    
    // loop to find the station and then change it coordinate
    auto s = all_stations_info.find(id);
    if(s == all_stations_info.end()){
        return false;
    }
    s->second.coordinate = newcoord;
    return true;

}

/**
 * @brief add_departure add depature(time and train) to a station
 * @param stationid the station that we add depature
 * @param trainid id of the train to be added
 * @param time the time of the depature to be added
 * @return true if add successfully, false if station not in data structure or depature already added
 */
bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{
    
    // New depature
    std::pair<Time, TrainID> new_depature;
    new_depature.first = time;
    new_depature.second = trainid;
    
    // Find the station
    auto s = all_stations_info.find(stationid);
    if(s == all_stations_info.end()){
        return false;
    }

    // Find if the schedule is already added
    auto& schedule_vec = s->second.schedules;
    auto a = std::find(schedule_vec.begin(), schedule_vec.end(), new_depature);

    if(a != schedule_vec.end()){
        return false;
    }

    // add schedule
    schedule_vec.push_back(new_depature);
    return true;
}

/**
 * @brief remove_departure remove a depature from a station
 * @param stationid the id of the station we remove depature from
 * @param trainid the id of the train in the depature
 * @param time the time of the depature
 * @return true if remove successfully, false if station not found or depature not in data structure (schedule_vec)
 */
bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    
    // deleted depature
    std::pair<Time, TrainID> deleted_depature;
    deleted_depature.first = time;
    deleted_depature.second = trainid;
    
    // Find the station
    auto s = all_stations_info.find(stationid);
    if(s == all_stations_info.end()){
        return false;
    }

    // Find if the schedule is in the data structure
    auto& schedule_vec = s->second.schedules;
    auto deleted_pointer = std::find(schedule_vec.begin(), schedule_vec.end(), deleted_depature);

    if(deleted_pointer == schedule_vec.end()){
        return false;
    }
    
    // delete schedule
    schedule_vec.erase(deleted_pointer);
    
    
    return true;
}

/**
 * @brief station_departures_after return a list of depature after certain time
 * @param stationid id of the station
 * @param time time after that we show the depature
 * @return a vector of depature after the given time, sorted in time order
 */
std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{
    
    // find if station in the data structure
    std::vector<std::pair<Time, TrainID>> result;
    auto s = all_stations_info.find(stationid);
    if(s == all_stations_info.end()){
        std::pair<Time, TrainID> null_depature;
        null_depature.first = NO_TIME;
        null_depature.second = NO_TRAIN;
        result.push_back(null_depature);
        return result;
    }

    result = s->second.schedules; //vector of depatures
    
    // Sorting 
    std::sort(result.begin(), result.end(), [](std::pair<Time, TrainID> a, std::pair<Time, TrainID> b){
                if (a.first < b.first) { return true; }
                else if (b.first < a.first) { return false; }
                else { return a.second < b.second; }
            });

    // Find the schedule after a specific time
    auto p = std::find_if(result.begin(), result.end(), [time](std::pair<Time, TrainID> a){
            return a.first >= time;});

    std::vector<std::pair<Time, TrainID>> subvector = {p, result.end()};
    return subvector;


}

/**
 * @brief add_region add a region to the data structure, initialize its property
 * @param id the id of added region
 * @param name the name of added region
 * @param coords list of coords of added region
 * @return true if add successfully, false if region is already in the data structure
 */
bool Datastructures::add_region(RegionID id, const Name & name, std::vector<Coord> coords)
{
    
    // Find regions in the data structure
    if (all_regions_info.find(id) != all_regions_info.end()){
        return false;
    }
    struct region new_region = {
        .name = name,
        .coords = coords,
    };
    
    // Add new region
    all_regions_info[id] = new_region;
    return true;

    
}

/**
 * @brief all_regions list all region
 * @return vector of regions
 */
std::vector<RegionID> Datastructures::all_regions()
{
    
    // loop through data structure to add region
    std::vector<RegionID> result;
    for(auto& item : all_regions_info){
        result.push_back(item.first);
    }
    return result;
}

/**
 * @brief get_region_name get the name of a region with given id
 * @param id id of the region
 * @return name of the given region id
 * NO_NAME if there is no such region
 */
Name Datastructures::get_region_name(RegionID id)
{
    // loop through data structure to find the target region
    auto s = all_regions_info.find(id);
    if( s != all_regions_info.end()){
        return s->second.name;
    }
    return NO_NAME;
}

/**
 * @brief get_region_coords get the coords of a region with given id
 * @param id of given region
 * @return a vector of coords for the given region id
 * NO_COORD if there is no region
 */
std::vector<Coord> Datastructures::get_region_coords(RegionID id)
{
    // loop through the data structure to find the target region 
    auto s = all_regions_info.find(id);
    if( s != all_regions_info.end()){
        return s->second.coords;
    }
    std::vector<Coord> no_coord;
    no_coord.push_back(NO_COORD);
    return no_coord;
}

/**
 * @brief add_subregion_to_region add a region to subregion of another
 * @param id the subregion id
 * @param parentid the parent region id
 * @return true if add successfully, false if sub region or parent region not found or sub region already belong to
 * another parent
 */
bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    auto sub_region = all_regions_info.find(id);
    auto parent_region = all_regions_info.find(parentid);

    // Check if the sub region and parent region are in the data structure 
    if(sub_region == all_regions_info.end() or parent_region == all_regions_info.end()){
        return false;
    }else if(sub_region->second.parent_region != NO_REGION){
        return false;
    }
    
    // add the relationship between 2 regions
    sub_region->second.parent_region = parentid;
    parent_region->second.direct_sub.insert(id);
    return true;
}

/**
 * @brief add_station_to_region add a sub station to a region
 * @param id the id of sub station
 * @param parentid the id of the parent region
 * @return true if add successfully, false if station or region not found or station already belong to another region
 */
bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{
     
    auto sub_station = all_stations_info.find(id);
    auto parent_region = all_regions_info.find(parentid);
    // Find if station and parent region are in the data structure
    if(sub_station == all_stations_info.end() or parent_region == all_regions_info.end()){
        return false;
    }else if(sub_station->second.parent_region != NO_REGION){
        return false;
    }
    // Add the relationship between station and region
    sub_station->second.parent_region = parentid;
    return true;

}

/**
 * @brief station_in_regions find all the direct and indirect region that a station belong to
 * @param id the id of station that we will search parent region
 * @return vector of region id that direct/indirectly the parent of the stationi
 * NO_REGION if station not found
 */
std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
     
    std::vector<RegionID> result;
    
    // Check if station is in the data structure
    auto s = all_stations_info.find(id);
    if(s == all_stations_info.end()){
        result.push_back(NO_REGION);
        return result;
    }
     
    // Check if station have parent regions
    RegionID direct_parent = s->second.parent_region;
    if(direct_parent == NO_REGION){
        return result;
    }
    result.push_back(direct_parent);

    // Loop to add indirect parent
    RegionID indirect_parent = all_regions_info.find(direct_parent)->second.parent_region;
    while(indirect_parent != NO_REGION){
        result.push_back(indirect_parent);
        indirect_parent = all_regions_info.find(indirect_parent)->second.parent_region;
    }   
    return result;
}

/**
 * @brief all_subregions_of_region return the subregions of a region
 * @param id the id of region we are interesting 
 * @return a vector of regionID contains the subregions directly or indirectly
 */
std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID id)
{
    auto s = all_regions_info.find(id);
    std::vector<RegionID> direct_sub_vec;

    // Check if the region is in the data structure
    if(s == all_regions_info.end()){
        direct_sub_vec.push_back(NO_REGION);
        return direct_sub_vec;
    }

    // Using the subregion set function set to return set of all sub regions
    // the name is a bit confusing, it is indirect and direct sub set
    // the function subregion set use recursion, set help the adding process faster
    auto direct_sub_set = subregions_set(id);
    
    for(auto it =direct_sub_set.begin(), end = direct_sub_set.end(); it!= end; it++){
        direct_sub_vec.push_back(*it);
    }
    

    return direct_sub_vec;

}

/**
 * @brief station_closest_to arrange the station in order closest to a point xy
 * @param xy coordinate that we use as pivot
 * @return the vector station id sorted based on distance from xy
 */
std::vector<StationID> Datastructures::stations_closest_to(Coord xy)
{
    
    std::vector<std::pair<StationID, station>> tobe_sorted;
    std::vector<StationID> result;

    // push all stations to a container
    for(auto it = all_stations_info.begin(); it != all_stations_info.end(); it++)
    {
        tobe_sorted.push_back({it->first, it->second});
    }
    if(tobe_sorted.size() == 0){ return result;}
    
    // Sort based on distance from a coordinate
    std::sort(tobe_sorted.begin(), tobe_sorted.end(), [xy = xy](std::pair<StationID, station> a, std::pair<StationID, station> b){
            auto coord_a = a.second.coordinate;
            auto coord_b = b.second.coordinate;
            
            auto dis_a = pow(pow(xy.x - coord_a.x, 2) + pow(xy.y -  coord_a.y, 2), 0.5); 
            auto dis_b = pow(pow(xy.x - coord_b.x, 2) + pow(xy.y - coord_b.y, 2), 0.5); 
            
            if(dis_a == dis_b){
                
                return coord_a < coord_b;
            }
            return dis_a < dis_b;
            });
    
    // Push the ID only
    for(auto s: tobe_sorted){
        result.push_back(s.first);
    }

    // Return all if size <3
    if(result.size() <=  2){return result;}

    return std::vector<StationID>(result.begin() + 0, result.begin()+3);
}

/**
 * @brief remove_station remove the station from data structure
 * @param id id of the station to be removed
 * @return true if remove successfully, false if id not in data structure
 */
bool Datastructures::remove_station(StationID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    //throw NotImplemented("remove_station()");
    
    // Find if station is in the data structure
    auto deleted_station = all_stations_info.find(id);
    if(deleted_station == all_stations_info.end()){
        return false;
    }
    
    // delete station from id set
    station_id_set.erase(id);
    // delete station from main data structure
    all_stations_info.erase(deleted_station);
    return true;
}

/**
 * @brief common_parent_of_regions return the closest common parent of 2 regions
 * @param id1 region 1
 * @param id2 region 2
 * @return common parant id, NO_REGION if there is no common region
 */
RegionID Datastructures::common_parent_of_regions(RegionID id1, RegionID id2)
{
    //
    auto r1 = all_regions_info.find(id1);
    auto r2 = all_regions_info.find(id2);
    RegionID common_parent = NO_REGION;
    
    // Find if id1 and id2 are in the data structure
    if(r1 == all_regions_info.end() or r2 == all_regions_info.end()){
        return common_parent;
    }

    
    // All the parent of id1
    std::set<RegionID> parent_of_r1;
    RegionID parent_1 = r1->second.parent_region;
    while (parent_1 != NO_REGION){
        parent_of_r1.insert(parent_1);
        parent_1 = all_regions_info.find(parent_1)->second.parent_region;
    }
    
    // All the parent of id2, if one of them is in list of common parent of id1, return immidiately the first
    RegionID parent_2 = r2->second.parent_region;
    while (parent_2 != NO_REGION and common_parent == NO_REGION){
        if(parent_of_r1.find(parent_2) !=  parent_of_r1.end()){
            common_parent = parent_2;
            break;
        }else{
        parent_2 = all_regions_info.find(parent_2)->second.parent_region;
        }
    }

    return common_parent;

}

/**
 * @brief subregions_set return subregion of a region in set
 * @param id region of interest
 * @return the set of subregion
 */
std::set<RegionID> Datastructures::subregions_set(RegionID id)
{
    auto s = all_regions_info.find(id);
    std::set<RegionID> result; 
    
    // Loop through region and use recursive to add sub regions
    // set help the insert command faster
    for(auto it = s->second.direct_sub.begin(), end = s->second.direct_sub.end(); it!=end; it++)
    {  
        result.insert(*it);
        auto others = subregions_set(*it);
        result.insert(others.begin(), others.end());
    }


    return result;
}
