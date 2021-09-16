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
#define ITEM_LEN 256

typedef struct _room {
	unsigned long id;
	char item[ITEM_LEN];
	struct _room *left;
	struct _room *right;
	// unsigned long adj_rooms[];
	// struct room *adj_rooms[];
} room;

typedef struct _map {
	room root;
} map;

map dungeon; /* dungeon map */
unsigned long dragonPos; /* dragon position */
unsigned long playerPos; /* player position */
char playerItem[ITEM_LEN];
int foundDragon;

void buildMap();
struct room *newRoom(unsigned long, char []);
struct room *addRoom(room *, unsigned long, char []);
struct room *getRoom(room *, unsigned long;
void inorder(room *);
// void setPos();
void debug() {
	inorder(&dungeon.root);
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
** (Incomplete) Builds dungeon map using user input
*/
void buildMap() {
	int getRooms = TRUE;
	while(getRooms == TRUE) {
		unsigned long id;
		scanf("%lu %*c", &id);
		if(id == (unsigned long) 0) {
			getRooms = FALSE;
		} else {
			/* TODO: store the adj_room_ids */
			int i = 0;
			char c;
			// unsigned long *adj_ptrs[MAX];
			for(int i = 0; i < MAX; ++i) {
				// adj_ptrs[i] = malloc(sizeof(unsigned long));
				// scanf("%llu  %c", adj_ptrs[i], &c);
				// if(adj_ptrs[i] == (unsigned long) 0) {
				// 	free(adj_ptrs[i]);
				// 	--i;
				// }
				// *Start* debug code
				unsigned long adj_id;
				scanf("%lu  %c", &adj_id, &c);
				if(adj_id == (unsigned long) 0) {
					printf("From room %lu player can go to room %lu", id, adj_id);
				}
				// *End* debug code
				if(c == ")") {
					// &adj_ptrs = realloc(adj_ptrs, sizeof(unsigned long long)*i);
					break;
				}
			}

			char item[ITEM_LEN];
			if(scanf(" %s", &item) == 0) {
				if(dungeon.root == NULL) {
					dungeon.root = newRoom(id, NULL);
				} else {
					addRoom(&dungeon.root, id, NULL);
				}
			} else {
				if(dungeon.root == NULL) {
					dungeon.root = newRoom(id, item);
				} else {
					addRoom(&dungeon.root, id, item);
				}
			}
		}
	}
}

/*
** Creates a new room (node)
*/
room *newRoom(unsigned long id, char item[ITEM_LEN]) {
	room *p;
	p = malloc(sizeof(room));
	p->id = id;
	p->item = item;
	p->left = NULL;
	p->right= NULL;
	return p;
}

/*
** Adds a room to the map (binary search tree)
*/
room *addRoom(room *root, unsigned long id, char item[ITEM_LEN]) { 
	if(root == NULL) {
		return newRoom(id, item);
	} else if(x > root->id) {
		root->right_child = addRoom(root->right, id, item);
	} else {
		root->left_child = addRoom(root->left, id, item);
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

void inorder(room *root) {
    if(root!=NULL) {
        inorder(root->left_child);
        printf(" %d ", root->data);
        inorder(root->right_child);
    }
}

/*
** (Incomplete) Sets the initial positions of the player and dragon
*/
// void setPos() {
// 	char *input = (char *) malloc(2*sizeof(unsigned long long)+2);
// 	fgets(input, (2*sizeof(unsigned long long)+2), stdin);
// 	char *ptr;
// 	ptr = strtok(input, ", ");
// 	playerPos = (unsigned long long) strtol(ptr, NULL, 10);
// 	ptr = strtok(input, ", ");
// 	dragonPos = (unsigned long long) strtol(ptr, NULL, 10);
// 	/* check that the rooms exist */
// }