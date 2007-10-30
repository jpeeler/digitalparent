/**
 * Header file for database / SQLite interface module.
**/
#ifndef DATABASE_H
#define DATABASE_H

#include <exception>
#include <iostream>
#include <string>

#include "data_structure.h"
#include "std_errors.h"
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

	int getProfile(Profile *profile);
	int storeProfile(Profile *profile);
	int deleteProfile(Profile *profile);

	int getUser(User *user);
	int storeUser(User *user);
	int deleteUser(User *user);
	int getUserUsingAnswer(User *user);
	int getUserForEdit(User *user);
	std::vector <std::string> getUserList();
	std::vector <std::string> getIconList();

	int storeDisc(Disc *discInfo);
	int getDisc(Disc *disc);

    void printErrorMessage(int errorNumber);

private:
	tntdb::Connection conn;

    int userExists(User *user);
    int fillSecretQuestionAndIcon(User *user);

};

class DBTest
{
	public:
		static void do_DBTest();
};


#endif
