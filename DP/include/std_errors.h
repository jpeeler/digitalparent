/***************************************************************************
 *            std_errors.h
 *
 *  Mon Oct 22 18:51:02 2007
 ****************************************************************************/

#ifndef _STD_ERRORS_H
#define _STD_ERRORS_H

#define DEB_MODE false // this is for deb file creation only

//#define SUCCESS 0
//#define GEN_ERROR 1

/**
 * Database Errors
**/

/*
#define DB_GEN_ERROR 100
#define DB_DATABASE_NOT_FOUND 101
#define DB_UNKNOWN_USER 110
#define DB_UNKNOWN_DISC 111
#define DB_UNKNOWN_PROFILE 112
#define DB_BAD_PASSWORD 120
#define DB_USERNAME_IN_USE 121
*/
typedef enum {
	SUCCESS,
	GEN_ERROR,
	DB_GEN_ERROR,
	DB_DATABASE_NOT_FOUND,
	DB_UNKNOWN_USER,
	DB_UNKNOWN_DISC,
	DB_UNKNOWN_PROFILE,
	DB_BAD_PASSWORD,
	DB_USERNAME_IN_USE,
	C_DISC_NOT_LOADED,
	C_HAL_ERROR
} ERRORS;

typedef enum {
	G,
	PG,
	PG13,
	NC17,
	R,
	X,
	NR
} RATINGS;
	
#endif /* _STD_ERRORS_H */
