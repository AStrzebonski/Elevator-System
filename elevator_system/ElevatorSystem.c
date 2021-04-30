#include <stdlib.h>
#include "ElevatorSystem.h"
static Elevator elev_array[ELEV_NB];

void Elevator_Init()
{
    for(int i=0; i<ELEV_NB; i++)
    {
        elev_array[i].ID = i;
        elev_array[i].floor = 0;
        elev_array[i].direction = 0;
        elev_array[i].change_direction_soon = 0;
        elev_array[i].stop_and_open = false;
        for(int j=0; j<FLOOR_NB; j++)
        {
            elev_array[i].dest_floor[j] = false;
        }
    }
}


bool Elevator_Clear_Demands(int ID)
{
    for(int i=0; i<ELEV_NB; i++)
    {
        if(elev_array[i].ID == ID)
        {
            elev_array[i].direction = 0;
            elev_array[i].stop_and_open = false;
            elev_array[i].change_direction_soon = 0;
            for(int j=0; j<FLOOR_NB; j++)
            {
                elev_array[i].dest_floor[j] = false;
            }
            return true;
        }
    }
    //no elevator with such id found
    return false;
}


bool Elevator_Change_Status(int ID, int new_ID, int floor, int direction, bool stop_and_open)
{
    if(floor<0 || floor>FLOOR_NB-1) //no such floor
        return false;
    if(floor == 0 && direction<0) //disallowed state
        return false;
    if(floor == FLOOR_NB-1 && direction>0) //disallowed state
        return false;
    if(ID!=new_ID)
    {
        for(int i=0; i<ELEV_NB; i++) //check if new_ID is unique
        {
            if(elev_array[i].ID == new_ID)
            {
                return false; //new_ID is not unique
            }
        }
    }

    for(int i=0; i<ELEV_NB; i++)
    {
        if(elev_array[i].ID == ID)
        {
            elev_array[i].ID = new_ID;
            elev_array[i].floor = floor;
            elev_array[i].direction = direction;
            elev_array[i].stop_and_open = stop_and_open;
            return true;
        }
    }
    //no elevator with such id found
    return false;
}


const Elevator* Elevator_Status()
{
    return elev_array;
}


int* Longest_Path(int current_floor, int demanded_floor, int current_direction, int demanded_direction)
//function calculates highest possible number of floors traveled to the demanded floor including demanded direction
{
    static int ret[2]; //{longest path, new_change_direction_soon}
    ret[1] = 0;

    if(current_floor==demanded_floor)
    {
        if(current_direction==0)
        {
            ret[0] = 0;
            return ret;
        }
        if( (current_direction>0) == (demanded_direction>0) )
        {
            ret[0] = 0;
            return ret;
        }
        //directions doesn't match
        if(current_direction < 0)
        {
            ret[0] = current_floor + demanded_floor;
            ret[1] = 1; //next direction would be up
            return ret;
        }
        //elevator wants to go up, there would be change of direction
        ret[0] = FLOOR_NB - 1 - current_floor + FLOOR_NB - 1 - demanded_floor;
        ret[1] = -1; //next direction would be down
        return ret;
    }
    if(current_direction == 0)
    {
        ret[0] = abs(demanded_floor - current_floor);
        if((demanded_direction > 0) == (demanded_floor - current_floor > 0)) //elevator would start to go in the same direction as demanded_direction
        {
            return ret;
        }
        //elevator would start to go in the opposite direction to demanded_direction
        if(demanded_floor > current_floor) //elevator would go up but client wants to go down
        {
            ret[1] = -1;
            return ret;
        }
        //elevator would go down but client wants to go up
        ret[1] = 1;
        return ret;
    }
    if((current_direction > 0) == (demanded_direction > 0)) //elevator goes in the same direction as demanded
    {
        if((current_direction > 0) == (demanded_floor - current_floor > 0)) //elevator goes towards demanded floor
        {
            ret[0] = abs(demanded_floor - current_floor);
            return ret;
        }
        if(current_direction > 0)
        {
            ret[0] = FLOOR_NB - 1 - current_floor + FLOOR_NB - 1 + demanded_floor;
            ret[1] = 1;
            return ret;
        }
        //elevator goes down
        ret[0] = current_floor + FLOOR_NB - 1 + FLOOR_NB - 1 - demanded_floor;
        ret[1] = -1;
        return ret;
    }
    //elevator goes in the opposite direction to demanded
    if(current_direction > 0)
    {
        ret[0] = FLOOR_NB - 1 - current_floor + FLOOR_NB - 1 - demanded_floor;
        ret[1] = -1;
        return ret;
    }
    //elevator goes down
    ret[0] = current_floor + demanded_floor;
    ret[1] = 1;
    return ret;
}


void Refresh() //refreshes states of elevators
{
    for(int i=0; i<ELEV_NB; i++)
    {
        if(elev_array[i].dest_floor[elev_array[i].floor] == true) //elevator is on one of destined floors
        {
            elev_array[i].stop_and_open = true;
            elev_array[i].dest_floor[elev_array[i].floor] = false; //demand serviced
            continue; //it is expected that someone will click button in elevator now so we don't change direction yet
        }
        if(elev_array[i].stop_and_open == true)
            continue; //do not change direction when door are open
        int new_direction=0;
        for(int j=0; j<FLOOR_NB; j++)
        {
            if(elev_array[i].dest_floor[j]==true)
            {
                if(elev_array[i].direction==0) //elevator was not moving
                {
                    new_direction = j - elev_array[i].floor;
                    break;
                }
                if(j>elev_array[i].floor && elev_array[i].direction>0) //elevator goes in the right direction
                {
                    new_direction = elev_array[i].direction;
                    break;
                }
                if(j<elev_array[i].floor && elev_array[i].direction<0) //elevator goes in the right direction
                {
                    new_direction = elev_array[i].direction;
                    break;
                }
                new_direction = elev_array[i].direction*(-1); //possibility of changing elevator direction
            }
        }
        if(new_direction==0)
            elev_array[i].change_direction_soon=0; //we expected elevator to change direction but it didn't happened
        if(elev_array[i].direction!=0 && new_direction!=0)
        {
            if((elev_array[i].direction > 0) != (new_direction > 0)) //reversal of direction
            {
                if( (elev_array[i].change_direction_soon > 0) == (new_direction > 0) ) //direction changed as expected
                {
                    elev_array[i].change_direction_soon = 0;
                }
            }
        }
        elev_array[i].direction = new_direction;
    }
}


bool Elevator_Pickup(int floor, int direction)
{
    if(floor<0 || floor>FLOOR_NB-1) //no such floor
        return false;
    if(direction == 0) //no such button
        return false;
    if(floor == 0 && direction<0) //no such button
        return false;
    if(floor == FLOOR_NB-1 && direction>0) //no such button
        return false;
    int longest_possible_path=1000; //program searches for an elevator with the shortest longest possible path
    int best_elev_iter=0;
    int* new_longest_possible_path;
    int new_change_direction_soon = elev_array[0].change_direction_soon; //for chosen elevator
    for(int i=0; i<ELEV_NB; i++)
    {
        new_longest_possible_path = Longest_Path(elev_array[i].floor, floor, elev_array[i].direction, direction);
        if(elev_array[i].change_direction_soon!=0)
            *new_longest_possible_path += 2*FLOOR_NB; //we don't want to allocate demands to an elevator which is yet to change its direction
        if(*new_longest_possible_path < longest_possible_path) //better elevator found
        {
            longest_possible_path = *new_longest_possible_path;
            best_elev_iter = i;
            new_change_direction_soon = *(new_longest_possible_path + 1);
        }
    }
    elev_array[best_elev_iter].dest_floor[floor] = true;
    elev_array[best_elev_iter].change_direction_soon = new_change_direction_soon;
    Refresh();
    return true;
}


bool Elevator_Demand(int ID, int dest_floor)
{
    if(dest_floor<0 || dest_floor>FLOOR_NB-1) //no such floor
        return false;
    for(int i=0; i<ELEV_NB; i++)
    {
        if(elev_array[i].ID == ID)
        {
            elev_array[i].dest_floor[dest_floor] = true;
            elev_array[i].stop_and_open = false; //close the door
            if(elev_array[i].direction>0 && dest_floor<elev_array[i].floor)
                elev_array[i].change_direction_soon = -1;
            if(elev_array[i].direction<0 && dest_floor>elev_array[i].floor)
                elev_array[i].change_direction_soon = 1;
            Refresh();
            return true;
        }
    }
    //no elevator with such id found
    return false;
}


void Elevator_Step()
{
    for(int i=0; i<ELEV_NB; i++)
    {
        //when door are open, elevator doesn't move in this step
        if(elev_array[i].stop_and_open == true)
            elev_array[i].stop_and_open = false; //close the door
        else if(elev_array[i].direction > 0) //move elevator up
            elev_array[i].floor++;
        else if(elev_array[i].direction < 0) //move elevator down
            elev_array[i].floor--;
    }
    Refresh();
}

