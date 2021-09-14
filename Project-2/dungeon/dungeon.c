/*
** Name: Elizabeth Perez
** Student ID: eperez57
** M-number: 20966722
*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_LEN 1000000
#define ITEM_LEN 256

struct room {
	unsigned long long id;
	char item[ITEM_LEN];
	struct room left;
	struct room right;
	unsigned long long adj_rooms[];
}

struct map {
	struct room root;
}

struct map map;
unsigned long long playerPos;
unsigned long long dragonPos;
char playerItem[ITEM_LEN];

void buildMap();

int main() {
	buildMap();
	return 0;
}

/*
** 
*/
void buildMap() {
	char line[MAX_LEN];
	int getRoom = TRUE;
	while(getRoom == TRUE) {
		fgets(line, MAX_LEN, stdin);
		if(strncmp(line, "0", 1) == 0) {
			getRoom = FALSE;
		} else {
			// Add the room
		}
	}
}

/*
**
*/
void addRoom() {

}