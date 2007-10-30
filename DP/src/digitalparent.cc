// generated 2007/10/15 10:20:36 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to digitalparent.cc_new

// This file is for your program, I won't touch it again!

#include <gtkmm/main.h>
#include <glib/gi18n.h>
#include <iostream>

#include "login_dlg.hh"
#include "media_player_dlg.hh"
#include "welcome_dlg.hh"
#include "dp_gui.h"
#include "controller.h"

#define RUN_WINDOW true
#define TEST_CONTROLLER false
#define TEST_DATABASE false
#define TEST_DATA_STRUCTURE false
#define TEST_WINDOWS false
#define SHOW_WELCOME false
#define TEST_USERS false

// the one and only controller
Controller m_control;

// global function to allow all objects to access controller
Controller* useController()
{
	return &m_control;
}

void fillWithUsers();

int main(int argc, char **argv)
{  
#if defined(ENABLE_NLS)
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif //ENABLE_NLS   

#if RUN_WINDOW
   Gtk::Main m(&argc, &argv);
   m_mode = START;
   welcome_dlg *welcome_dlg;   
   login_dlg *login_dlg;   
   media_player_dlg *media_player_dlg;	   
   
#if TEST_USERS
	fillWithUsers();
#endif	
	
   while ( m_mode != STOP )
   {
	   switch ( m_mode )
	   {
		   case START:
		   {
			   std::string password = "";							   
			   std::string admin = "admin";	   
			   int status = 
			   		useController()->loadCurrentUser(admin,password);
		   	   switch( status )
			   {
				   case DB_UNKNOWN_USER:
					   m_mode = RUNONCE;
				   break;
				   case DB_BAD_PASSWORD:
					   m_mode = LOGIN;
				   break;				   
				   default:
					   // figure this out later
				   break;
			   }		   			   
		   break;
		   }		   
		   case RUNONCE:
		   {
			   welcome_dlg = new class welcome_dlg();
				   m.run(*welcome_dlg);
			   delete welcome_dlg;
			   m_mode = LOGIN;
		   break;
		   }			   
		   case LOGIN:
		   {
			   login_dlg =  new class login_dlg();
				login_dlg->oninit();				   
				   m.run(*login_dlg);
			   delete login_dlg;
			   m_mode = USER_PLAY;			  
		   break;
		   }		   
		   case USER_PLAY:
		   {			   
			   media_player_dlg = new class media_player_dlg();
				   m.run(*media_player_dlg);
			   delete media_player_dlg;
			   m_mode = LOGIN;
		   break;
		   }			   
		   case ADMIN_PLAY:
			   //run media player in admin mode;
		   	   m_mode = USER_PLAY;  //temporary
		   break;
		   
		   case EDIT_USER:
			   // pull up edit user dlg;
		   m_mode = LOGIN;
		   break;
			   
	   	   default:
			   //do nothing, should exit while loop
		   break;
	   }
   }   


#endif
   
#if TEST_WINDOWS
   Gtk::Main m(&argc, &argv);
    welcome_dlg *welcome_dlg = new class welcome_dlg();
	 m.run(*welcome_dlg);	
 delete welcome_dlg;
	

//~ login_dlg *login_dlg = new class login_dlg();
	//~ m.run(*login_dlg);	
//~ delete login_dlg;

//psswrd_prompt_dlg *psswrd_prompt_dlg = new class psswrd_prompt_dlg();
//	m.run(*psswrd_prompt_dlg);
//delete psswrd_prompt_dlg;	


/*   
media_player_dlg *media_player_dlg = new class media_player_dlg();
   m.run(*media_player_dlg);
delete media_player_dlg;
*/

#endif

  
#if TEST_CONTROLLER
	printf("\n------ Begin Controller Test ------\n\n");
	TestController::do_test();
	printf("\n------- End Controller Test -------\n\n");
#endif
	
#if TEST_DATABASE
	printf("\n------ Begin Database Test ------\n\n");
	DBTest::do_DBTest();
	printf("\n------- End Database Test -------\n\n");
#endif
	
#if TEST_DATA_STRUCTURE
	printf("\n------ Begin Data Structure Test ------\n\n");
	DataTest::do_test();
	printf("\n------- End Data Structure Test -------\n\n");
#endif

#if SHOW_WELCOME
	Gtk::Main m(&argc, &argv);
	welcome_dlg *welcome_dlg = new class welcome_dlg();
		m.run(*welcome_dlg);
	delete welcome_dlg;
	
	const User *auser = useController()->c_getUserLoggedIn();
	printf("%s",auser->getPasswordHash().c_str());	
#endif
	
    return 0;
}

void fillWithUsers()
{
	//setup user Jeremy
	useController()->c_setCurrentUser(std::string("Jeremy"));
	useController()->c_setCurrentUserPasswordHash(std::string("jeremys_password"));
	useController()->c_setCurrentUserIcon(std::string("/Projects/DP/pixmaps/tired_smile.png"));
	useController()->c_setCurrentUserCanPlayUnknown(true);
	useController()->c_setCurrentUserMaxPlayLevel(NR);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
	//setup user Jeff
	useController()->c_setCurrentUser(std::string("Jeff"));
	useController()->c_setCurrentUserPasswordHash(std::string(""));
	useController()->c_setCurrentUserIcon(std::string("/Projects/DP/pixmaps/butterfly.png"));
	useController()->c_setCurrentUserCanPlayUnknown(false);
	useController()->c_setCurrentUserMaxPlayLevel(PG13);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
	
	//setup user Chris
	useController()->c_setCurrentUser(std::string("Chris"));
	useController()->c_setCurrentUserPasswordHash(std::string(""));
	useController()->c_setCurrentUserIcon(std::string("/Projects/DP/pixmaps/roswell_smile.png"));
	useController()->c_setCurrentUserCanPlayUnknown(true);
	useController()->c_setCurrentUserMaxPlayLevel(R);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
	
	//setup user Paul
	useController()->c_setCurrentUser(std::string("Paul"));
	useController()->c_setCurrentUserPasswordHash(std::string("pauls_password"));
	useController()->c_setCurrentUserIcon(std::string("/Projects/DP/pixmaps/full_matrix.png"));
	useController()->c_setCurrentUserCanPlayUnknown(false);
	useController()->c_setCurrentUserMaxPlayLevel(G);
	useController()->storeCurrentUser();
	useController()->c_clearUserLoggedIn();
}
