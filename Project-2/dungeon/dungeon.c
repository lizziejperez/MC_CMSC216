/*
** Name: Elizabeth Perez
** Student ID: eperez57
** M-number: M20966722
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 100
#define MAX_ITEM_LEN 255

typedef struct _room {
	unsigned long id;
	struct _room *left;
	struct _room *right;
	char item[MAX_ITEM_LEN];
	struct _room **adj_rooms;
} room;

typedef struct _map {
	room *root;
} map;

map dungeon; /* dungeon map */
unsigned long dragonPos; /* dragon position */
unsigned long playerPos; /* player position */
char playerItem[MAX_ITEM_LEN];
int foundDragon;

void buildMap();
void addRoomInfo(unsigned long);
void addRoomItem(unsigned long, char);
void addRoomConnection(unsigned long, room *);
struct room *newRoom(unsigned long, char []);
struct room *addRoom(room *, unsigned long, char []);
struct room *getRoom(room *, unsigned long;
void inorder(room *);

void setPos();

void debug() {
	inorder(dungeon.root);
	puts("\n");
}

int main() {
	dungeon.root = NULL;

	buildMap();
	debug();
	// setPos();

	// puts("Welcome to the dungeon.\n");
	// if(playerPos == dragonPos) {
	// 	foundDragon = TRUE;
	// } else {
	// 	foundDragon = FALSE;
	// }
	// while(foundDragon != TRUE) {
	// 	printf("You are in room %llu", playerPos);
	// 	struct room *curRoom = getRoom(playerPos);
	// 	if(strncmp("empty", curRoom->item, 5) != 0) {
	// 		printf(", on the groud is a %s", curRoom->item);
	// 	}
	// 	puts(". Neaby are rooms");
	// }
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
				addRoomConnection(id, getRoom(dungeon.root, adj_id));
			} else {
				addRoomConnection(id, getRoom(dungeon.root, adj_id));
			}
			printf("From room %lu player can go to room %lu", id, adj_id);
		}
		if(c == ")") {
			inList = FALSE;
		}
	}

	char item[MAX_ITEM_LEN];
	if(scanf(" %[^\n]s", &item) == 1) {
		addRoomItem(id, item);
	}
}

/*
** Adds an item to a room
*/
void addRoomItem(unsigned long id, char item[MAX_ITEM_LEN]) {
	room *r = getRoom(dungeon.root, id);
	r->item = item;
}

/*
** Adds a room connection
*/
void addRoomConnection(unsigned long id, room *adj_room) {
	room *r = getRoom(dungeon.root, id);
	if(r->adj_rooms == NULL) {
		room *rooms = (room *) malloc(sizeof(room *));
		r->adj_rooms = &rooms;
		(*r->adj_rooms)[0] = adj_room; // room *adj_rooms[0] = adj_room
	} else {
		int num_rooms = (sizeof(r->adj_rooms) / sizeof(room *)) + 1;
		(*r->adj_rooms) = (room *) realloc((*r->adj_rooms), sizeof(room *) * num_rooms);
		(*r->adj_rooms)[num_rooms-1] = adj_room;
	}
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
	r->adj_rooms = NULL; 
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
		unsigned long pos1, pos2;
		scanf("%lu %*c %lu", &pos1, &pos2);
		if(getRoom(pos1) == NULL || getRoom(pos2) == NULL) {
			puts("Entered invalid starting position(s). Try again.\n");
		} else {
			playerPos = pos1;
			dragonPos = pos2;
			unset = FALSE;
		}
	}
}