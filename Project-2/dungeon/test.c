#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_ITEM_LEN 255

typedef struct _deadend {
    int len;
    unsigned long **de_ids;
} de; /*** TESTING ***/

typedef struct _room {
	unsigned long id;
	struct _room *left;
	struct _room *right;
	char *item;
	int num_paths;
	struct _room **next_rooms;
    de *des; /*** TESTING ***/
} room;

typedef struct _map {
	room *root;
} map;

typedef struct _spData{
	room *r;
	int dist;
	room *prev;
} spData;

map dungeon;
char *playerItem;
room *dragonRoom;
room *playerRoom;
spData **spArr;
int prevDist;

void buildMap();
void addRoomInfo(unsigned long id);
void addItem(unsigned long id, char item[MAX_ITEM_LEN]);
void addPath(unsigned long id, room *adj_room);
room *newRoom(unsigned long id);
room *addRoom(room *root, unsigned long id);
room *getRoom(room *root, unsigned long id);
void clearMap(room *root);
void setPos();
int distance();
int getSPDataPos(room *r, int size);
spData *newSPData(room *r, int d, room *src);
void clearSPArr(int size);
void inorder(room *root); /* Debug purpose only */

void addDE(unsigned long id, unsigned long adj_id);
void clearDE(room *root);

int main() {
	dungeon.root = NULL;
	playerItem = NULL;
	buildMap();
	clearDE(dungeon.root); /* NEW */
    inorder(dungeon.root); /* Debug purpose only */
    setPos();
	prevDist = distance();

	puts("Welcome to the dungeon.");
	while(TRUE) {
		/* Describes the player's room */
		printf("You are in room %lu", playerRoom->id);
		if(playerRoom->item != NULL) {
			printf(", on the groud is a %s", playerRoom->item);
		}
		for(int i = 0; i < playerRoom->num_paths; i++) {
			if(i == 0) {
				if(playerRoom->num_paths > 1) {
					printf(". Neaby are rooms ");
				} else {
					printf(". Neaby is room ");
				}
			}
			room *temp = *(playerRoom->next_rooms + i);
			if(i == (playerRoom->num_paths - 1)) {
				printf("%lu", temp->id);
			} else {
				printf("%lu,", temp->id);
			}
		}
		puts(".");
		
		/* Gets the players next move */
		unsigned long choice;
		scanf("%lu", &choice);
		if(choice == (unsigned long) 0) {
			/* Swaps the player's item with the room's item */
			if(playerItem == NULL && playerRoom->item != NULL) {
				printf("You pick up the %s.\n", playerRoom->item);
			}
			if(playerItem != NULL && playerRoom->item == NULL) {
				printf("You drop the %s.\n", playerItem);
			}
			if(playerItem != NULL && playerRoom->item != NULL) {
				printf("You drop the %s and pick up the %s.\n", playerItem, playerRoom->item);
			}
			char *temp = playerItem;
			playerItem = playerRoom->item;
			playerRoom->item = temp;
		} else {
			/* Moves the player to the next room */
			for(int i = 0; i < playerRoom->num_paths; i++) {
				room *temp = *(playerRoom->next_rooms + i);
				if(temp->id == choice) {
					playerRoom = getRoom(dungeon.root, choice);
				}
			}
			/* Prints the outcome */
			if(playerRoom == dragonRoom) {
				if(strncmp("sword", playerItem, 5) == 0) {
					puts("You win!");
				} else {
					puts("You lose.");
				}
				break;
			} else {
				int dist = distance();
				if(dist == -1) {
					puts("You have no chance of finding the dragon. You lose.");
				} else if(dist == prevDist) {
					puts("You're neither getting warmer nor colder.");
				} else if(dist < prevDist) {
					puts("You're getting warmer!");
				} else {
					puts("You're getting colder.");
				}
				prevDist = dist;
			}
		}
	}

	clearMap(dungeon.root);
	return 0;
}

/*** TESTING ***/
void addDE(unsigned long id, unsigned long adj_id) {
	room *r = getRoom(dungeon.root, id);
	if(r->des == NULL) {
		unsigned long *ptr = malloc(sizeof(unsigned long));
		*ptr = adj_id;
		r->des = malloc(sizeof(de));
		r->des->len = 1;
		r->des->de_ids = malloc(sizeof(unsigned long *));
		*(r->des->de_ids) = ptr;
		printf("Added DE %lu to room %lu\n", **(r->des->de_ids + r->des->len - 1), id);
	} else {
 		int present = FALSE;
		for (int i = 0; i < r->des->len; i++) {
			if(**(r->des->de_ids + i) == adj_id) {
				present = TRUE;
			}
		}
		if(present == FALSE) {
			unsigned long *ptr = malloc(sizeof(unsigned long));
			*ptr = adj_id;
			r->des->de_ids = realloc(r->des->de_ids, sizeof(unsigned long *) * (r->des->len + 1));
			*(r->des->de_ids + r->des->len) = ptr;
			r->des->len += 1;
			printf("Added DE %lu to room %lu\n", **(r->des->de_ids + r->des->len - 1), id);
		}
	}
}
/*** TESTING ***/
void clearDE(room *root) {
	if(root != NULL) {
		printf("Clearing room %lu\n", root->id);
		if(root->des != NULL) {
			for(int i = 0; i < root->des->len; i++) {
				room *r = getRoom(dungeon.root, **(root->des->de_ids + i));
				if(r != NULL) {
					printf("Adding path from %lu to %lu\n", root->id, r->id);
					addPath(root->id, r);
				}
				printf("Freeing id\n");
				free(*(root->des->de_ids + i));
			}
			printf("Freeing rest\n");
			free(root->des->de_ids);
			free(root->des);
			root->des = NULL;

			clearDE(root->left);
			clearDE(root->right);	
		}
	}
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
			getRooms = FALSE;
			char throw[MAX_ITEM_LEN];
			fgets(throw, MAX_ITEM_LEN, stdin);
		} else {
			if(dungeon.root == NULL) {
				dungeon.root = newRoom(id);
			} else {
				if(getRoom(dungeon.root, id) == NULL) {
					addRoom(dungeon.root, id);
				}
			}
			addRoomInfo(id);
		}
	}
    clearDE(dungeon.root);
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
		scanf("%lu%c", &adj_id, &c);
		if(adj_id != (unsigned long) 0) {
			if(getRoom(dungeon.root, adj_id) == NULL) {
				addDE(id, adj_id); /*** TESTING ***/
			} else {
				addPath(id, getRoom(dungeon.root, adj_id));
			}
		}
		char close = ')';
		if(c == close) {
			inList = FALSE;
		}
	}

	char item[MAX_ITEM_LEN];
	fgets(item, MAX_ITEM_LEN, stdin);
	if(item[0] != '\n') {
		addItem(id, item);
	}
}

/*
** Adds an item to a room
*/
void addItem(unsigned long id, char item[MAX_ITEM_LEN]) {
	room *r = getRoom(dungeon.root, id);
	r->item = malloc(sizeof(char));
	int i = 1;
	while(TRUE) {
		if(item[i] == '\n') {
			break;
		}
		r->item = realloc(r->item, (i * sizeof(char)));
		r->item[i-1] = item[i];
		++i;
	}
}

/* 
** Adds a path to a room
*/
void addPath(unsigned long id, room *adj_room) {
	room *r = getRoom(dungeon.root, id);
	if(r->next_rooms == NULL) {
		r->next_rooms = malloc(sizeof(room *));
		*r->next_rooms = adj_room;
	} else {
		r->next_rooms = realloc(r->next_rooms, sizeof(room *) * (r->num_paths + 1));
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
    r->des = NULL; /*** TESTING ***/
	return r;
}

/*
** Adds a room to the map
*/
room *addRoom(room *root, unsigned long id) { 
	if(root == NULL) {
		return newRoom(id);
	} else if(id > root->id) {
		root->right = addRoom(root->right, id);
	} else {
		root->left = addRoom(root->left, id);
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
** Clears the dungeon map's data
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

/*** Only for debug purposes ***/
void inorder(room *root) {
	if(root!=NULL) {
		inorder(root->left);
		printf("Room %lu: ", root->id);
		if(root->item != NULL) {
			printf("On the groud is a %s. ", root->item);
		}
		for(int i = 0; i < root->num_paths; i++) {
			if(i == 0) {
				if(root->num_paths == 1) {
					printf("Neaby is room");
				} else {
					printf("Neaby are rooms");
				}
			}
			room *temp = *(root->next_rooms + i);
			printf(" %lu", temp->id);
		}
		puts(".");
		inorder(root->right);
	}
}

/*
** Sets the initial positions of the player and dragon
*/
void setPos() {
	unsigned long id1, id2;
	while(TRUE) {
		scanf("%lu%*c%lu", &id1, &id2);
		room *r1 = getRoom(dungeon.root, id1);
		room *r2 = getRoom(dungeon.root, id2);
		if(r1 == NULL || r2 == NULL) {
			puts("Entered invalid starting position(s). Try again.");
		} else {
			playerRoom = r1;
			dragonRoom = r2;
            break;
		}
    }
}

/*
** Returns the shortest distance between the player's position and dragon's position
*/
int distance() {
	spArr = malloc(sizeof(spData *));
	*spArr = newSPData(playerRoom, 0, NULL);

	int size = 1;
	int x = 0;
	 while (x < size) {
		spData *source = *(spArr + x);
		for (int i = 0; i < source->r->num_paths; i++) {
			room *r = *(source->r->next_rooms + i);
			int rPos = getSPDataPos(r, size);
			if(rPos == -1) {
				++size;
				spArr = realloc(spArr, (sizeof(spData *) * size));
				*(spArr + size - 1) = newSPData(r, (source->dist + 1), (source->r));
			} else {
				spData *tmp = *(spArr + rPos);
				int newDist = source->dist + 1;
				int currDist = tmp->dist;
				if(newDist < currDist) {
					tmp->dist = newDist;
					tmp->prev = source->r;
				}
			}
		}
		++x;
	}

	int spPos = getSPDataPos(dragonRoom, size);
	if(spPos != -1) {
		spData *tmp = *(spArr + spPos);
		int d = tmp->dist;
		clearSPArr(size);
		return d;
	} else {
		clearSPArr(size);
		return -1;
	}
}

/*
** Creates a new shortest path data element
*/
spData *newSPData(room *r, int d, room *src) {
	spData *data = malloc(sizeof(spData *));
	data->r = r;
	data->dist = d;
	data->prev = src;
	return data;
}

/*
** Returns the position of spData associated with room
** If the spData doesn't exist in spArr it returns -1
*/
int getSPDataPos(room *r, int size) {
	unsigned long id = r->id;
	for (int i = 0; i < size; i++) {
		spData *tmp = *(spArr + i);
		unsigned long cmpID = tmp->r->id;
		if(id == cmpID) {
			return i;
		}
	}
	return -1;
}

/*
** Clears the shortest path data array (spArr)
*/
void clearSPArr(int size) {
	for (int i = 0; i < size; i++) {
		spData *tmp = *(spArr + i);
		free(tmp);
	}
	free(spArr);
}