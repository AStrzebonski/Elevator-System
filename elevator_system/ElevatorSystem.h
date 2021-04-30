#ifndef ELEVATORSYSTEM_H_INCLUDED
#define ELEVATORSYSTEM_H_INCLUDED

#include <stdbool.h>

#define ELEV_NB 16
#define FLOOR_NB 10
typedef struct  {
    int ID;
    int floor; //elevator is either waiting at this floor or just passing it
    bool dest_floor[FLOOR_NB]; //'true' indicates that elevator is yet to stop at this floor
    int direction; //positive->up, negative->down, zero->elevator is not going anywhere, it has all 'false' values in dest_floor
    int change_direction_soon; //positive->up, negative->down, probably elevator will change its direction soon
    bool stop_and_open; //elevator stops at current floor and open its door (as a contrast to when elevator just passes some floor
} Elevator;

//functions for elevator management
void Elevator_Init();
bool Elevator_Clear_Demands(int ID); //clears all demands for one elevator
bool Elevator_Change_Status(int ID, int new_ID, int floor, int direction, bool stop_and_open); //changes elevator parameters
const Elevator* Elevator_Status();

//functions for normal usage of elevator system
bool Elevator_Pickup(int floor, int direction); //equivalent of clicking up or down button at a floor
bool Elevator_Demand(int ID, int dest_floor); //equivalent of clicking button in elevator
void Elevator_Step(); //equivalent to elapsed time

#endif // ELEVATORSYSTEM_H_INCLUDED
