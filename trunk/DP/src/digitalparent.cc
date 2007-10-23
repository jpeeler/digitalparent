// generated 2007/10/15 10:20:36 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to digitalparent.cc_new

// This file is for your program, I won't touch it again!

#include <config.h>
#include <gtkmm/main.h>
#include <glib/gi18n.h>

#include "login_dlg.hh"
#include "media_player_dlg.hh"
#include "psswrd_prompt_dlg.hh"
#include "welcome_dlg.hh"

#include "dp_gui.h"
#include "controller.h"

#define RUN_WINDOW true
#define TEST_CONTROLLER false
#define TEST_DATABASE false
#define TEST_DATA_STRUCTURE false

int main(int argc, char **argv)
{  
#if defined(ENABLE_NLS)
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif //ENABLE_NLS

   m_control = new class Controller();

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
	
#if RUN_WINDOW
   Gtk::Main m(&argc, &argv);
   m_mode = START;
   welcome_dlg *welcome_dlg;
   psswrd_prompt_dlg *psswrd_prompt_dlg;  
   login_dlg *login_dlg;   
   media_player_dlg *media_player_dlg;
   while ( m_mode != STOP )
   {
	   switch ( m_mode )
	   {
		   case START:		   
			   m_mode = RUNONCE;
			   //load users
		   	   //if ( users exist ) m_mode = LOGIN		   		
		   	   //else m_mode = RUNONCE
		   break;
		   
		   case RUNONCE:
			   welcome_dlg = new class welcome_dlg();
				   m.run(*welcome_dlg);
			   delete welcome_dlg;
			   m_mode = LOGIN;
		   break;		
			   
		   case LOGIN:
			   login_dlg =  new class login_dlg();
				   m.run(*login_dlg);
			   delete login_dlg;
			   m_mode = USER_PLAY;
		   break;
		   
		   case PROMPT_PASSWORD:
			   psswrd_prompt_dlg = new class psswrd_prompt_dlg();
				   m.run(*psswrd_prompt_dlg);
			   delete psswrd_prompt_dlg;
		   break;
		
		   case USER_PLAY:
			   media_player_dlg = new class media_player_dlg();
				   m.run(*media_player_dlg);
			   delete media_player_dlg;
			   m_mode = STOP;
		   break;
			   
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

//psswrd_prompt_dlg *psswrd_prompt_dlg = new class psswrd_prompt_dlg();
//	m.run(*psswrd_prompt_dlg);
//delete psswrd_prompt_dlg;	

#endif

    return 0;
}
