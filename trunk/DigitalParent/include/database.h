/**
 * Header file for database / SQLite interface module.
**/
#ifndef DATABASE_H
#define DATABASE_H

#include <exception>
#include <iostream>
#include <string>

#include "../include/data_structure.h"
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

	Profile getProfile(int diskID, int userID);
	bool storeProfile(Profile *profile);
	bool removeProfile(Profile *profile);

	User getUser(std::string& username, std::string& password);
	bool storeUser(User *user);
	bool removeUser(User *user);

	bool storeDisc(Disc *discInfo);
	Disc getDisc(std::string& discName, int numChapters, long discLength);

private:
	tntdb::Connection conn;

};


#endif
