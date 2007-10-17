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

int main(int argc, char **argv)
{  
#if defined(ENABLE_NLS)
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif //ENABLE_NLS
   
   Gtk::Main m(&argc, &argv);

welcome_dlg *welcome_dlg = new class welcome_dlg();
	m.run(*welcome_dlg);
delete welcome_dlg;
	
	
//psswrd_prompt_dlg *psswrd_prompt_dlg = new class psswrd_prompt_dlg();
//	m.run(*psswrd_prompt_dlg);
//delete psswrd_prompt_dlg;
	
	
//media_player_dlg *media_player_dlg = new class media_player_dlg();
//   m.run(*media_player_dlg);
//delete media_player_dlg;
   return 0;
}
