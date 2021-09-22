/*
** Name: Elizabeth Perez
** Student ID: eperez57
** M-number: M20966722
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX 100
#define MAX_ITEM_LEN 255

typedef struct _room {
	unsigned long id;
	struct _room *left;
	struct _room *right;
	char *item;
	int num_paths; // rename adj_rooms_count
	struct _room **next_rooms; // rename adj_rooms
} room;

typedef struct _map {
	room *root;
} map;

typedef struct _spData{
	room *r;
	int dist;
	room *prev;
} spData; // shortest path data

map dungeon; /* dungeon map */
room *dragonRoom;
room *playerRoom;
char *playerItem;
spData *spArr; // shortest path's array
int prevDist;


void buildMap();
void addRoomInfo(unsigned long);
void addItem(unsigned long id, int len, char item[len]);
void addPath(unsigned long id, room *adj_room);
struct room *newRoom(unsigned long, char []);
struct room *addRoom(room *, unsigned long, char []);
struct room *getRoom(room *, unsigned long);
void inorder(room *);

void setPos();
int foundDragon();
void swapItem();
int distance();
int getSPDataPos(room *r, int size);
void clearMap(room *root);

void debug() {
	inorder(dungeon.root);
	puts("\n");
}

int main() {
	dungeon.root = NULL;
	playerItem = NULL;

	buildMap();
	debug();

	setPos();
	prevDist = distance();

	puts("Welcome to the dungeon.\n");
	while(TRUE) {
		printf("You are in room %lu", playerRoom->id);
		if(playerRoom->item != NULL) {
			printf(", on the groud is a %s", playerRoom->item);
		}
		puts(". Neaby are rooms");
		for(int i = 0; i < playerRoom->num_paths; i++) {
			room *temp = *(playerRoom->next_rooms + i);
			printf(" %lu", temp->id);
		}
		puts(".\n");
		
		unsigned long choice;
		scanf("%lu", choice);
		if(choice == (unsigned long) 0) {
			swapItem();
		} else {
			for(int i = 0; i < playerRoom->num_paths; i++) {
				room *temp = *(playerRoom->next_rooms + i);
				if(temp->id == choice) {
					playerRoom = getRoom(dungeon.root, choice);
					if(foundDragon() == TRUE) {
						if(strncmp("sword", playerItem, 5) == 0) {
							puts("You win!");
						} else {
							puts("You lose.");
						}
						break;
					} else {
						int dist = distance();
						if(dist == -1) {
							puts("You have no chance of finding the dragon.\n");
						} else if(dist == prevDist) {
							puts("You neither getting warmer nor colder.\n");
						} else if(dist < prevDist) {
							puts("Getting warmer.\n");
						} else {
							puts("Getting colder.\n");
						}
						prevDist = dist;
					}
				}
			}
		}
	}
	
	clearMap(dungeon.root);
	return 0;
}

/*
** Builds dungeon map using user input
*/
void buildMap() {
	int getRooms = TRUE;
	while(getRooms == TRUE) {
		unsigned long id;
		scanf("%lu", &id);
		if(id == (unsigned long) 0) {
			scanf("%*[\n]s");
			getRooms = FALSE;
		} else {
			if(dungeon.root == NULL) {
				dungeon.root = newRoom(id);
			} else {
				if(roomPresent(id) == TRUE) {
					addRoomInfo(id);
				} else {
					addRoom(dungeon.root, id);
					addRoomInfo(id);
				}
			}
		}
	}
}

/*
** Adds the user provided information to the corresponding room
*/
void addRoomInfo(unsigned long id) {
	scanf(" %*c");
	int inList = TRUE;
	while(inList) {
		unsigned long adj_id;
		char c;
		scanf("%lu  %c", &adj_id, &c);
		if(adj_id != (unsigned long) 0) {
			if(getRoom(dungeon.root, adj_id) == NULL) {
				addRoom(dungeon.root, adj_id);
			}
			addPath(id, getRoom(dungeon.root, adj_id));
			printf("From room %lu player can go to room %lu", id, adj_id);
		}
		if(c == ")") {
			inList = FALSE;
		}
	}

	char item[MAX_ITEM_LEN];
	if(scanf(" %[^\n]s", &item) == 1) {
		int len = sizeof(item) / sizeof(char);
		addItem(id, len, item);
	}
}

/* 
** Adds an item to a room
*/
void addItem(unsigned long id, int len, char item[len]) {
	room *r = getRoom(dungeon.root, id);
	char *i = malloc(len * sizeof(char));
	strcpy(i, item);
	r->item = i;
}

/* 
** Adds a path
*/
void addPath(unsigned long id, room *adj_room) {
	room *r = getRoom(dungeon.root, id);
	if(r->next_rooms == NULL) {
		r->next_rooms = malloc(sizeof(room *));
		*r->next_rooms = adj_room;
	} else {
		r->next_rooms = realloc(*r->next_rooms, sizeof(room *) * (r->num_paths + 1));
		*(r->next_rooms + r->num_paths) = adj_room;
	}
	r->num_paths += 1;
}

/*
** Creates a new room (node)
*/
room *newRoom(unsigned long id) {
	room *r;
	r = malloc(sizeof(room));
	r->id = id;
	r->left = NULL;
	r->right = NULL;
	r->item = NULL;
	r->num_paths = 0;
	r->next_rooms = NULL;
	return r;
}

/*
** Adds a room to the map (binary search tree)
*/
room *addRoom(room *root, unsigned long id) { 
	if(root == NULL) {
		return newRoom(id);
	} else if(id > root->id) {
		root->right_child = addRoom(root->right, id);
	} else {
		root->left_child = addRoom(root->left, id);
	}
	return root;
}

/*
** If there is a room with the id, returns pointer to the room.
** If no room has the id, returns a NULL pointer.
*/
room *getRoom(room *root, unsigned long id) {
	if(root == NULL || root->id == id){
		return root;
	} else if(id > root->id) {
		return getRoom(root->right, id);
	} else {
		return getRoom(root->left, id);
	}
}

/*
** Clears the map
*/
void clearMap(room *root) {
	if(root!=NULL) {
        clearMap(root->left);
        clearMap(root->right);
		free(root->item);
		free(root->next_rooms);
		free(root);
    }
}

/*
** Prints out the rooms in order (lowest to highest) based on room ids
*/
void inorder(room *root) {
    if(root!=NULL) {
        inorder(root->left);
        printf(" %d ", root->data);
        inorder(root->right);
    }
}

/*
** Sets the initial positions of the player and dragon
** Initializes (prevDist) the distance between them as well
*/
void setPos() {
	int unset = TRUE;
	while(unset) {
		unsigned long id1, id2;
		scanf("%lu %*c %lu", &id1, &id2);
		room *r1 = getRoom(id1);
		room *r2 = getRoom(id2);
		if(playerRoom == NULL || dragonRoom == NULL) {
			puts("Entered invalid starting position(s). Try again.\n");
		} else {
			playerRoom = r1;
			dragonRoom = r2;
			unset = FALSE;
		}
	}
	prevDist = distance();
	free(spArr);
}

/*
** Returns 1 (TRUE) if the player is in the same room as the dragon
** Otherwise it returns 0 (FALSE)
*/
int foundDragon() {
	if(playerRoom == dragonRoom) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
** Returns the shortest distance between the player's position and dragon's position
*/
int distance() {
	spArr = malloc(sizeof(spData));
	spArr->r = playerRoom;
	spArr->dist = 0;
	spArr->prev = NULL;

	int size = 1;
	int x = 0;
	while (x < size) {
		spData *source = *(spArr + x);
		for (int i = 0; i < source->r->num_paths; i++) {
			room *r = *(source->r->next_rooms + i);
			int rPos = getSPDataPos(r, size);
			if(rPos == -1) {
				++size;
				spArr = realloc(sizeof(spData) * size);
				*(spArr+(size-1))->r = r;
				*(spArr+(size-1))->dist = source->dist + 1;
				*(spArr+(size-1))->prev;
			} else {
				if((source->dist + 1) < (*(spArr + rPos)->dist)) {
					*(spArr + rPos)->dist = source->dist + 1;
					*(spArr + rPos)->prev = source->r;
				}
			}
		}
		++x;
	}

	int spPos = getSPDataPos(dragonRoom, size);
	if(spPos != -1) {
		int d = *(spArr + spPos)->dist;
		free(spArr);
		return d;
	} else {
		free(spArr);
		return -1;
	}
}

/*
** Returns the position of spData associated with room r if the spData exists in spArr
** Otherwise it returns -1
*/
int getSPDataPos(room *r, int size) {
	for (int i = 0; i < size; i++) {
		room *cmp = *(spArr + i)->r;
		if(r == cmp) {
			return i;
		}
	}
	return -1;
}

/*
** Swaps the player's item with the item in the room that the player is currently in
*/
void swapItem() {
	char *temp = playerItem;
	playerItem = playerRoom->item;
	playerRoom->item = temp;
}