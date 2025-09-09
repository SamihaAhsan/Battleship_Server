

#ifndef HELPERS_H
#define HELPERS_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct coords{
	int x_coord;
	int y_coord;
	struct coords *next;
	
} coord;

typedef struct persons {  
    char name[21]; 
	coord *my_coord; 
	int file_des; 
    struct persons *next;  
} person;  



coord *find_coords(int x, int y, char dir);


void broadcast(person *linked, char *word);


person *register_person(char *names, int x, int y, char dir, person *linked, int files);


char *name_find(int files, person *linked);


int counter(person *linked);


coord *delete_one(int x, int y, coord *head, int *bomb);


void bomb_coord(int x, int y, person *linked, int files, int *store);


void free_list(coord *head);

person *find_and_free(int files, person *linked);


int valid_name(char *name);

#endif 
