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
};

struct map {
	struct room root;
};

struct map map; /* dungeon map */
unsigned long long dragonPos; /* dragon position */
unsigned long long playerPos; /* player position */
char playerItem[ITEM_LEN];

void buildMap();
void buildRoom(char []);
void addRoom(struct room);
void setPos();

int main() {
	struct room nullRoom;
	nullRoom.id = 0;
	map.root = nullRoom;

	buildMap();
	setPos();

	return 0;
}

/*
** Builds dungeon map using user input
*/
void buildMap() {
	char line[MAX_LEN];
	int getRoom = TRUE;
	while(getRoom == TRUE) {
		fgets(line, MAX_LEN, stdin);
		if(strncmp(line, "0", 1) == 0) {
			getRoom = FALSE;
		} else {
			buildRoom(line);
		}
	}
}

/*
** Initializes and adds the room constructed by input
*/
void buildRoom(char input[MAX_LEN]) {
	struct room room;
	char *ptr;
	ptr = strtok(input, " ()");
	room.id = (unsigned long long) strtol(ptr, NULL, 10);

	// ptr = strtok(input, " ()");
	// char list[MAX_LEN];
	// strcpy(list, ptr);

	// ptr = strtok(input, " ()");
	// if(ptr != NULL){
	// 	strcpy(room.item, ptr);
	// }

	if(map.root.id == 0) {
		map.root = room;
	} else {
		addRoom(room);
	}
}

/*
** Adds the room to the dungeon map (as a new leaf node)
*/
void addRoom(struct room room) {
	struct room root;
	root = map.root;

	int cont = TRUE;
	while(cont) {
		if(room.id < root.id) {
			if(root.left == NULL) {
				root.left = room;
				cont = FALSE;
			} else {
				root = root.left;
			}
		} else {
			if(root.right = NULL) {
				root.right = room;
				cont = FALSE;
			} else {
				root = root.right;
			}
		}
	}
}

/*
** Sets the initial positions of the player and dragon
*/
void setPos() {
}