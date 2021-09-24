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

/* Testing */
typedef struct _spData{
	room *r;
	int dist;
	room *prev;
} spData;

map dungeon;
char *playerItem;

/* Testing */
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
void inorder(room *root);
void clearMap(room *root);

/* Testing */
void setPos();
int distance();
int getSPDataPos(room *r, int size);

int main() {
	dungeon.root = NULL;
	playerItem = NULL;
	buildMap();
    inorder(dungeon.root);

    /* Testing */
    setPos();

    clearMap(dungeon.root);
	return 0;
}

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
}

void addRoomInfo(unsigned long id) {
	scanf(" %*c");
	int inList = TRUE;
	while(inList) {
		unsigned long adj_id;
		char c;
		scanf("%lu%c", &adj_id, &c);
		if(adj_id != (unsigned long) 0) {
			if(getRoom(dungeon.root, adj_id) == NULL) {
				addRoom(dungeon.root, adj_id);
			}
			room *tmp = getRoom(dungeon.root, adj_id);
			addPath(id, getRoom(dungeon.root, adj_id));
			printf("From room %lu player can go to room %lu\n", id, tmp->id);
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
		room *tmp = getRoom(dungeon.root, id);
		printf("Added %s to room %lu\n", tmp->item, tmp->id);
	}
}

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

room *getRoom(room *root, unsigned long id) {
	if(root == NULL || root->id == id){
		return root;
	} else if(id > root->id) {
		return getRoom(root->right, id);
	} else {
		return getRoom(root->left, id);
	}
}

void clearMap(room *root) {
	if(root!=NULL) {
		clearMap(root->left);
		clearMap(root->right);
		free(root->item);
		free(root->next_rooms);
		free(root);
	}
}

/* Only for debug purposes */
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

/* Testing*/
void setPos() {
	unsigned long id1, id2;
	while(TRUE) {
		scanf("%lu%*c%lu", &id1, &id2);
		printf("Got %lu and %lu\n", id1, id2);
		room *r1 = getRoom(dungeon.root, id1);
		room *r2 = getRoom(dungeon.root, id2);
		if(r1 == NULL || r2 == NULL) {
			puts("Entered invalid starting position(s). Try again.\n");
		} else {
			playerRoom = r1;
			dragonRoom = r2;
			puts("Set positions!");
            break;
		}
    }

	/* prevDist = distance(); */
	/* free(spArr); */
}

int distance() {
	spArr = malloc(sizeof(spData *));
	(*spArr)->r = playerRoom;
	(*spArr)->dist = 0;
	(*spArr)->prev = NULL;

	int size = 1;
	int x = 0;
	while (x < size) {
		spData *source = *(spArr + x);
		for (int i = 0; i < source->r->num_paths; i++) {
			room *r = *(source->r->next_rooms + i);
			int rPos = getSPDataPos(r, size);
			spData *tmp;
			if(rPos == -1) {
				++size;
				spArr = realloc(spArr, sizeof(spData *) * size);
				tmp = *(spArr + (size-1));
				tmp->r = r;
				tmp->dist = source->dist + 1;
				tmp->prev = source->r;
			} else {
				tmp = *(spArr + rPos);
				if((source->dist + 1) < (tmp->dist)) {
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
		free(spArr);
		return d;
	} else {
		free(spArr);
		return -1;
	}
}

int getSPDataPos(room *r, int size) {
	for (int i = 0; i < size; i++) {
		spData *tmp = *(spArr + i);
		room *cmp = tmp->r;
		if(r == cmp) {
			return i;
		}
	}
	return -1;
}