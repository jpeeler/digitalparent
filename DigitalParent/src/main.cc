/* Created by Anjuta version 1.2.4a */
/*	This file will not be overwritten */

#define TEST_DATABASE true
#define TEST_DATA_STRUCTURE true
#define TEST_CONTROLLER true

#include <iostream>
#include "database.h"
#include "controller.h"

int main()
{
	if(TEST_DATABASE) 
	{
		printf("\n------ Begin Database Test ------\n");
		DBTest::do_DBTest();
		printf("\n------- End Database Test -------\n");
	}
	
	if(TEST_DATA_STRUCTURE) 
	{
		printf("\n------ Begin Data Structure Test ------\n");
		DataTest::do_test();
		printf("\n------- End Data Structure Test -------\n");
	}
	
	if(TEST_CONTROLLER)
	{
		printf("\n------ Begin Controller Test ------\n");
		TestController::do_test();
		printf("\n------- End Controller Test -------\n");
	}
	
	return 0;
}
