#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ElevatorSystem.h"

void clear_demands()
{
    char str[100];
    printf("Type ID of elevator.\n");
    scanf("%s", str);
    fflush(stdin);
    if(Elevator_Clear_Demands(atoi(str)) == false)
        printf("Operation failed. No such ID.\n");
}

void change_status()
{
    char str[100];
    printf("Type ID.\n");
    scanf("%s", str);
    fflush(stdin);
    int ID=atoi(str);
    printf("Type new ID.\n");
    scanf("%s", str);
    fflush(stdin);
    int new_ID=atoi(str);
    printf("Type new floor number.\n");
    scanf("%s", str);
    fflush(stdin);
    int floor=atoi(str);
    printf("Type new direction.\n");
    scanf("%s", str);
    fflush(stdin);
    int direction=atoi(str);
    printf("Type 'open' to open the elevator's door or anything else to close it.\n");
    scanf("%s", str);
    fflush(stdin);
    bool open=false;
    if(!strcmp(str, "open"))
        open=true;
    if(Elevator_Change_Status(ID, new_ID, floor, direction, open)==false)
        printf("Operation failed. Invalid values used.\n");
}

void print_status()
{
    const Elevator* elev_array_ = Elevator_Status();
    for(int i=0; i<ELEV_NB; i++)
    {
        printf("ID: %d, Floor: %d, ", elev_array_[i].ID, elev_array_[i].floor);
        printf("Direction: ");
        if(elev_array_[i].direction == 0)
            printf("none");
        else if(elev_array_[i].direction > 0)
            printf("up");
        else
            printf("down");
        printf(", New predicted direction: ");
        if(elev_array_[i].change_direction_soon == 0)
            printf("none");
        else if(elev_array_[i].change_direction_soon > 0)
            printf("up");
        else
            printf("down");
        printf(", Door open? %s ", elev_array_[i].stop_and_open ? "true, " : "false, ");
        printf("Destination floor numbers: ");
        for(int j=0; j<FLOOR_NB; j++)
        {
            if(elev_array_[i].dest_floor_down[j] || elev_array_[i].dest_floor_down[j] || elev_array_[i].dest_floor_down[j]) //print dest floor no matter what direction
                printf("%d, ", j);
        }
        printf("\n");
    }
}

void pickup()
{
    char str[100];
    printf("Type floor number.\n");
    scanf("%s", str);
    fflush(stdin);
    int floor = atoi(str);
    printf("Type direction.\n");
    scanf("%s", str);
    fflush(stdin);
    int direction = atoi(str);
    if(Elevator_Pickup(floor, direction) == false)
        printf("Operation failed. Invalid values used.\n");
}

void demand()
{
    char str[100];
    printf("Type ID.\n");
    scanf("%s", str);
    fflush(stdin);
    int ID = atoi(str);
    printf("Type destination floor number.\n");
    scanf("%s", str);
    fflush(stdin);
    int floor = atoi(str);
    if(Elevator_Demand(ID, floor) == false)
        printf("Operation failed. Invalid values used.\n");
}

void step()
{
    char str[100];
    printf("Type number of steps.\n");
    scanf("%s", str);
    fflush(stdin);
    int steps_nb = atoi(str);
    for(int i=0; i<steps_nb; i++)
        Elevator_Step();
    printf("Simulated %d steps.\n", steps_nb);
}

int main()
{
    char str[100];
    Elevator_Init();
    printf("This is elevator system. There are %d elevators and %d floors. Current state of elevator is: \n", ELEV_NB, FLOOR_NB);
    print_status();
    while(true)
    {
        printf("Type 'exit' to exit, 'clear' to clear all demands, 'change' to change status, 'status' to display status, 'pickup' to click button on a floor, 'demand' to click button in an elevator, 'step' to do chosen number of steps of simulation.\n");
        scanf("%s", str);
        fflush(stdin);
        if(!strcmp(str, "exit"))
            break;
        if(!strcmp(str, "clear"))
            clear_demands();
        else if(!strcmp(str, "change"))
            change_status();
        else if(!strcmp(str, "status"))
            print_status();
        else if(!strcmp(str, "pickup"))
            pickup();
        else if(!strcmp(str, "demand"))
            demand();
        else if(!strcmp(str, "step"))
            step();
        else
            printf("Unrecognized command.\n");
    }
}
