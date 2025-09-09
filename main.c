#include "helpers.h"


int main(int argc, char *argv[])
{
  if (argc!=2){
	  return 1;
  }
  person *pointers=NULL;
  int mem;
  if (sscanf(argv[1], "%d", &mem) != 1) {
        return 1;
    }
  int sfd;
  int cfd;

  struct sockaddr_in a;
 


  sfd = socket(AF_INET, SOCK_STREAM, 0);
  
  if (sfd == -1) {
    return 1;
}

  memset(&a, 0, sizeof(struct sockaddr_in));
  a.sin_family = AF_INET;
  a.sin_port = htons(mem);
  a.sin_addr.s_addr = htonl(INADDR_ANY);
  
  if (-1 == bind(sfd, (struct sockaddr *)&a, sizeof(struct sockaddr_in))) {
    return 1;
  }

  if (-1 == listen(sfd, 2)) {
    return 1;
  }
  
  int ep = epoll_create1(0);
	struct epoll_event evs;
	evs.events = EPOLLIN; 
	evs.data.fd = sfd;
	
	epoll_ctl(ep, EPOLL_CTL_ADD, sfd, &evs);
	
	struct epoll_event events[20]; 
	
	char inputs[103];
	char command[7];

  for (;;) {
	int n = epoll_wait(ep, events, 20, -1);
	for (int i = 0; i <n; i++){
	if (events[i].data.fd==sfd)
	{
		struct sockaddr_in ca;
		socklen_t sinlen;
		sinlen = sizeof(struct sockaddr_in);
		cfd = accept(sfd, (struct sockaddr *)&ca, &sinlen);
		 if (cfd == -1) {
                    perror("accept");
                    continue;
                }

		
	struct epoll_event ev;
	ev.events = EPOLLIN; 
	ev.data.fd = cfd;
	
	if (epoll_ctl(ep, EPOLL_CTL_ADD, cfd, &ev) == -1) {

}
	}
	else{
		int amount = read(events[i].data.fd, &inputs, 102);
		 if (amount>0 && amount<102) {    
			inputs[amount]='\0';
			if (sscanf(inputs, "%s", command)!=1){
				write(events[i].data.fd, "INVALID\n", 8*sizeof(char));
				continue;
			}
			
		if (strcmp("REG", command)==0){
			char name[22];
			int x;
			int y;
			char d;
			if (sscanf(inputs, "%s %s", command, name)!=2){write(events[i].data.fd, "INVALID\n", 8*sizeof(char));
			continue;}
			if (strlen(name)<=20 && valid_name(name)==1){
				if (sscanf(inputs, "%s %s %d %d %c", command, name, &x, &y, &d) !=5){write(events[i].data.fd, "INVALID\n", 8*sizeof(char));
				continue;}
			
				pointers=register_person(name,x,y,d,pointers,events[i].data.fd );
		}
		else{
			write(events[i].data.fd, "INVALID\n", 8*sizeof(char));
			continue;
		}
		
    }
	
	else if (strcmp("BOMB", command)==0){
			int x;
			int y;
			if (sscanf(inputs, "%s %d %d", command,&x, &y) !=3){
				write(events[i].data.fd, "INVALID\n", 8*sizeof(char));
				continue;

			}
			int amounted=counter(pointers);
			int store[amounted]; 
			memset(store, -1, sizeof(store));
			bomb_coord(x,y,pointers,events[i].data.fd, store);
			int i=0;
			while (store[i]!=-1){
				pointers=find_and_free(store[i], pointers);
		if (epoll_ctl(ep, EPOLL_CTL_DEL, store[i], NULL) == -1) {
			perror("epoll_ctl: client remove");
	}
		close(store[i]);
		i+=1;
		}
			}
			
		else{write(events[i].data.fd, "INVALID\n", 8*sizeof(char));
				continue;}
			
		}
		else{
		if (amount>=102){
		write(events[i].data.fd, "INVALID\n", 8*sizeof(char));
		continue;}
		else{
		char * wo_name=name_find(events[i].data.fd, pointers);
		pointers=find_and_free(events[i].data.fd, pointers);
		if (epoll_ctl(ep, EPOLL_CTL_DEL, events[i].data.fd, NULL) == -1) {
			perror("epoll_ctl: client remove");
	}
		close(events[i].data.fd);
		if (wo_name!=NULL){
		char msg[26];
		snprintf(msg, sizeof(msg), "GG %s\n", wo_name);
		broadcast(pointers, msg);}
		}
	
	}
		}
	
		
	}
	
	
	
   
    
	}
  }


