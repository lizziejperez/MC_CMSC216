#ifndef _MTCOUNTER_H
#define _MTCOUNTER_H

// Typedef for MTCounter structure.  Create a full definition in your MTCounter.c file
typedef struct _mt_counter MTCounter;

/* 
 *	MTC_init()
 *	Allocate and initialize a thread-safe counter structure.  Return a pointer to the new structure.
 */
MTCounter *MTC_init();

/*
 *	MTC_value()
 *	Takes an initialized thread-safe counter structure as a parameter.
 *	Access the value in the structure in a thread-safe manner.
 *	Returns the resulting integer value
 */
int MTC_value(MTCounter *);

/*
 *	MTC_increment()
 *	Takes an initialized thread-safe counter structure as a parameter.
 *	Access and increment the value within the structure in a thread-safe manner.
 */
void MTC_increment(MTCounter *);

/*
 *	MTC_decrement()
 *	Takes an initialized thread-safe counter structure as a parameter.
 *	Access and decrement the value within the structure in a thread-safe manner.
 */
void MTC_decrement(MTCounter *);

/*
 *	MTC_destroy()
 *	Takes an initialized thread-safe counter structure as a parameter.
 *	Access the value in the structure in a thread-safe manner.
 *	Clean-up and deallocate the structure.
 *	Returns the resulting integer value
 */
int MTC_destroy(struct MTCounter *);

#endif /* _MTCOUNTER_H */