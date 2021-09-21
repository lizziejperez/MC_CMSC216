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
	int num_paths;
	struct _room **next_rooms;
} room;

typedef struct _map {
	room *root;
} map;

map dungeon; /* dungeon map */
room *dragonRoom;
room *playerRoom;
// unsigned long dragonPos; /* dragon position */
// unsigned long playerPos; /* player position */
char *playerItem;
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
void swapItem(room *r);

void debug() {
	inorder(dungeon.root);
	puts("\n");
}

int main() {
	dungeon.root = NULL;

	buildMap();
	debug();
	setPos();

	puts("Welcome to the dungeon.\n");
	while(foundDragon() != TRUE) {
		printf("You are in room %lu", playerPos);
		room *r = getRoom(playerPos);
		if(r->item != NULL) {
			printf(", on the groud is a %s", r->item);
		}
		puts(". Neaby are rooms");
		for(int i = 0; i < r->num_paths; i++) {
			room *temp = *(r->next_rooms + i); // pointer to the room
			printf(" %lu", temp->id);
		}
		puts(".\n");
		
		unsigned long choice;
		scanf("%lu", choice);
		if(choice == (unsigned long) 0) {
			swapItem(r);
		} else {
			for(int i = 0; i < r->num_paths; i++) {
				room *temp = *(r->next_rooms + i); // pointer to the room
				if(temp->id == choice) {
					playerPos = choice;
					if(foundDragon() == TRUE) {
						// battle();
						if(strncmp("sword", playerItem, 5) == 0) {
							puts("You win!");
						}
					} else {
						// hint();
					}
				}
			}
		}
	}
	free(&dungeon);
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
	r->dest_ids = NULL;
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
		return search(root->right_child, id);
	} else {
		return search(root->left_child, id);
	}
}

/*
** Prints out the rooms in order (lowest to highest) based on room ids
*/
void inorder(room *root) {
    if(root!=NULL) {
        inorder(root->left_child);
        printf(" %d ", root->data);
        inorder(root->right_child);
    }
}

/*
** Sets the initial positions of the player and dragon
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
}

/*
** 
*/
int foundDragon() {
	if(playerRoom == dragonRoom) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
** (Incomplete) Returns the shortest distance between the start room and the room with the dragon
*/
int distance() {
	typedef struct _element{
		room *r;
		int dist;
		room *prev;
	} element;

	element *a = malloc(sizeof(element));
	a->r = playerRoom;
	a->dist = 0;
	a->prev = NULL;

	int size = 1;
	for(int i = 0; i < a->r->num_paths; i++) {
		room *temp = *(a->r->next_rooms + i); // pointer to the room
		for(int j = 0; j < size; j++) {
			if(temp == (a->r + j)) {
				
			}
		}
	}
}

/*
** (Incomplete) Swaps player item with room's item
*/
void swapItem(room *r) {

}

/*
** (Incomplete) Clears the dungeon map
*/
// void clearMap() {
	// delete (free) lowest leaves all the way up to the root
// }

/* Obsolete? */
// void addRoomConnection(unsigned long id, room *adj_room) {
// 	room *r = getRoom(dungeon.root, id);
// 	if(r->adj_rooms == NULL) {
// 		room *rooms = (room *) malloc(sizeof(room *));
// 		r->adj_rooms = &rooms;
// 		(*r->adj_rooms)[0] = adj_room; // room *adj_rooms[0] = adj_room
// 	} else {
// 		int num_rooms =  (int) (sizeof(r->adj_rooms) / sizeof(room *)) + 1;
// 		(*r->adj_rooms) = (room *) realloc((*r->adj_rooms), sizeof(room *) * num_rooms);
// 		(*r->adj_rooms)[num_rooms-1] = adj_room;
// 	}
// }
// void addRoomItem(unsigned long id, char item[MAX_ITEM_LEN]) {
// 	room *r = getRoom(dungeon.root, id);
// 	r->item = item;
// }
// void setPos() {
// 	int unset = TRUE;
// 	while(unset) {
// 		unsigned long pos1, pos2;
// 		scanf("%lu %*c %lu", &pos1, &pos2);
// 		if(getRoom(pos1) == NULL || getRoom(pos2) == NULL) {
// 			puts("Entered invalid starting position(s). Try again.\n");
// 		} else {
// 			playerPos = pos1;
// 			dragonPos = pos2;
// 			unset = FALSE;
// 		}
// 	}
// }