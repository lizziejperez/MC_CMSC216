/*
** Name: Elizabeth Perez
** Student ID: eperez57
** M-number: M20966722
*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_LEN 1000000
#define ITEM_LEN 256

struct room {
	unsigned long long id;
	char item[ITEM_LEN];
	struct room *left;
	struct room *right;
	// unsigned long long adj_rooms[];
};



struct map {
	struct room root;
};

struct map map; /* dungeon map */
unsigned long long dragonPos; /* dragon position */
unsigned long long playerPos; /* player position */
char playerItem[ITEM_LEN];
int foundDragon;

void buildMap();
struct room *newRoom(unsigned long long, char []);
struct room *addRoom(struct room *, unsigned long long, char []);
struct room *getRoom(struct room *, unsigned long long);
void setPos();

int main() {
	map.root = NULL;

	buildMap();
	setPos();

	puts("Welcome to the dungeon.\n");
	if(playerPos == dragonPos) {
		foundDragon = TRUE;
	} else {
		foundDragon = FALSE;
	}
	while(foundDragon != TRUE) {
		printf("You are in room %llu", playerPos);
		struct room *curRoom = getRoom(playerPos);
		if(strncmp("empty", curRoom->item, 5) != 0) {
			printf(", on the groud is a %s", curRoom->item);
		}
		puts(". Neaby are rooms");

	}

	return 0;
}

/*
** (Incomplete) Builds dungeon map using user input
*/
void buildMap() {
	int getRooms = TRUE;
	while(getRooms == TRUE) {
		unsigned long long id;
		scanf("%llu %*c", &id);
		if(id == (unsigned long long) 0) {
			getRooms = FALSE;
		} else {
			/* TODO: store the adj_room_ids */
			int i = 0;
			char c;
			unsigned long long adj_id;
			int done = FALSE;
			while(!done) {
				scanf("%llu  %c", &adj_id, &c);
				if(adj_id != (unsigned long long) 0) {
					++i;
				}
				if(c == ")") {
					done = TRUE;
				}
			}

			char item[ITEM_LEN];
			if(scanf(" %s", &item) == 0) {
				if(map.root == NULL) {
					map.root = newRoom(id, NULL);
				} else {
					addRoom(&map.root, id, NULL);
				}
			} else {
				if(map.root == NULL) {
					map.root = newRoom(id, item);
				} else {
					addRoom(&map.root, id, item);
				}
			}
		}
	}
}

/*
** Creates a new room (node)
*/
struct room *newRoom(unsigned long long id, char item[ITEM_LEN]) {
	struct room *p;
	p = malloc(sizeof(struct room));
	p->id = id;
	p->item = item;
	p->left = NULL;
	p->right= NULL;
	return p;
}

/*
** Adds a room to the map (binary search tree)
*/
struct room *addRoom(struct room *root, unsigned long long id, char item[ITEM_LEN]) { 
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
struct room *getRoom(struct room *root, unsigned long long id) {
	if(root == NULL || root->id == id){
		return root;
	} else if(id > root->id) {
		return search(root->right_child, id);
	} else {
		return search(root->left_child, id);
	}
}

/*
** (Incomplete) Sets the initial positions of the player and dragon
*/
void setPos() {
	char *input = (char *) malloc(2*sizeof(unsigned long long)+2);
	fgets(input, (2*sizeof(unsigned long long)+2), stdin);
	char *ptr;
	ptr = strtok(input, ", ");
	playerPos = (unsigned long long) strtol(ptr, NULL, 10);
	ptr = strtok(input, ", ");
	dragonPos = (unsigned long long) strtol(ptr, NULL, 10);
	/* check that the rooms exist */
}