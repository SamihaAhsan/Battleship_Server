#include "helpers.h"


coord *find_coords(int x, int y, char dir){ 
		coord *head = NULL; 
			if (dir=='-' && y>=0 && y<=9 && (x-2)>=0 && (x-2)<=9 && (x+2)>=0 && (x+2)<=9){
			x=x-2;
			for (int i=0; i<5; i++){
			coord *new = calloc(1,sizeof(coord)); 
			new->x_coord=x+i;
			new->y_coord=y;
			new->next=head;
			head=new;
			}
			}
			else if (dir=='|' && x>=0 && x<=9 && (y-2)>=0 && (y-2)<=9 && (y+2)>=0 && (y+2)<=9){
			y=y-2;
			for (int i=0; i<5; i++){
			coord *new = calloc(1,sizeof(coord)); 
			new->x_coord=x;
			new->y_coord=y+i;
			new->next=head;
			head=new;}
		
			}
		return head;
}

void broadcast(person *linked, char *word){
	person *p = linked;
    while (p != NULL) {
        int size = strlen(word);
        write(p->file_des, word, size*sizeof(char));
		 p = p->next;
   }
}

person * register_person(char *names, int x, int y, char dir, person *linked, int files){ 
	person *p=linked;
	coord *check=find_coords(x,y,dir);
	
	while (p!=NULL){
		if (strcmp(p->name, names)==0 || p->file_des==files){
			write(files, "TAKEN\n", 6*sizeof(char));
			return linked; 
		}
		p=p->next;	
	}
	if (check==NULL){
		write(files, "INVALID\n", 8*sizeof(char));
	return linked;}

		person *newNode = malloc(sizeof(person));
		if (newNode == NULL) {
			return linked;
		}
		strcpy(newNode->name, names);
		newNode->my_coord=check;
		newNode->file_des=files;
		newNode->next=linked;
		linked=newNode;
		write(files, "WELCOME\n", 8*sizeof(char));
		char msg[27];
		snprintf(msg, sizeof(msg), "JOIN %s\n", names);
		broadcast(linked, msg);
		
		return linked;

	}
	

char* name_find(int files, person *linked) { 
    person *p = linked;
    while (p != NULL) {
        if (p->file_des== files) {
            return p->name;
        }
       p = p->next;
    }
    return NULL;
	
}

int counter(person *linked) {
    int count = 0;
    person *p = linked;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

coord * delete_one(int x, int y, coord *head, int *bomb){ //returns the updated pointer once deletion 
	coord *tr=NULL;
	coord *pre=NULL;
if (head==NULL) {return NULL;
} 
pre=head;
tr=head->next;

if (head->x_coord == x && head->y_coord == y)
{
free(pre); 
(*bomb)+=1;
return tr;
}
while(tr!=NULL)
{
if (tr->x_coord == x && tr->y_coord == y)
{

pre->next=tr->next; 
free(tr); 
(*bomb)+=1;
break; 
}
tr=tr->next;
pre=pre->next;
}
return head; 
	
}

	
void bomb_coord(int x, int y, person *linked, int files, int *store) { 
	person *p = linked;
	int index=0;
	char *kills=name_find(files,linked);
	if (kills == NULL){
		write(files, "INVALID\n", 8*sizeof(char));
	}
	else{
	int total=0;
    while (p != NULL) {
		int bomb = 0;
        p->my_coord=delete_one(x,y,p->my_coord, &bomb);
			if (bomb!=0){
				char msg[55];
                snprintf(msg, sizeof(msg), "HIT %s %d %d %s\n", kills, x, y, p->name);
                broadcast(linked,msg);
				total+=1;
				if (p->my_coord == NULL) {
					char msg[26];
					snprintf(msg, sizeof(msg), "GG %s\n", p->name);
					broadcast(linked, msg);
					store[index]=p->file_des;
					index+=1;
			
        }
			}

            p=p->next;
        }
	if (total == 0) {
        char miss_msg[34];
        snprintf(miss_msg, sizeof(miss_msg), "MISS %s %d %d\n", kills, x, y);
        broadcast(linked, miss_msg);
    }
    }
	store[index]=-1;
}


void free_list(coord *head){ // free all the coord linked lists in a person
	coord *p=head;
	while (p!=NULL){
		coord *tr=p->next;
		free(p);
		p=tr;	
	}
	
	
}
person *find_and_free(int files,  person *linked){
	person *tr=NULL;
	person *pre=NULL;
	if (linked==NULL) return NULL; 
	pre=linked;
	tr=linked->next;
	if (linked->file_des==files)
{
	if (linked->my_coord != NULL){
	free_list(linked->my_coord);}
	free(pre); 
	return tr;
}
	while(tr!=NULL){
		if (tr->file_des==files){
		if (tr->my_coord != NULL){
		free_list(tr->my_coord);}
		pre->next=tr->next; 
		free(tr); 
		break; 
}
tr=tr->next;
pre=pre->next;
}
return linked; 
}

 int valid_name(char *name){
	 for (int i=0; i<strlen(name); i++){
		  if (isalpha(name[i])==0 && isdigit(name[i])==0 && name[i] != '-') {
            return 0; 
	 }
	  
 }
 return 1;}
