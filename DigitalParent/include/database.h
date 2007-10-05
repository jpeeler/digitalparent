/**
 * Header file for database / SQLite interface module.
**/
#ifndef DATABASE_H
#define DATABASE_H

#include <exception>
#include <iostream>
#include <string>

#include "data_structure.h"
#include <tntdb/connect.h>
#include <tntdb/connection.h>
#include <tntdb/result.h>
#include <tntdb/row.h>
#include <tntdb/value.h>
#include <tntdb/statement.h>
#include <tntdb/error.h>

class Database
{
public:
	Database();
		 ~Database();

	bool getProfile(Profile *profile);
	bool storeProfile(Profile *profile);
	bool removeProfile(Profile *profile);

	bool getUser(User *user);
	bool storeUser(User *user);
	bool removeUser(User *user);

	bool storeDisc(Disc *discInfo);
	bool getDisc(Disc *disc);

private:
	tntdb::Connection conn;

};

class DBTest
{
	public:
		static void do_DBTest();
};


#endif
