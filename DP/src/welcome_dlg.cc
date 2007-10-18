// generated 2007/10/17 13:39:21 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to welcome_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "welcome_dlg.hh"
#include <string.h>

void welcome_dlg::on_init_password_edit_box_editing_done()
{  
}

void welcome_dlg::on_repeat_password_edit_box_editing_done()
{  
}

void welcome_dlg::on_secret_q_edit_box_editing_done()
{  
}

void welcome_dlg::on_secret_a_edit_box_editing_done()
{  
}

void welcome_dlg::on_welcome_next_button_clicked()
{  
	std::string password = init_password_edit_box->get_text();
	std::string confirm = repeat_password_edit_box->get_text();
	if ( password != confirm || password == "" || confirm == "" )
	{
		init_password_edit_box->set_text("");
		repeat_password_edit_box->set_text("");
		return;
	}
	std::string question = secret_q_edit_box->get_text();
	std::string answer = secret_a_edit_box->get_text();
	if ( question == "" || answer == "" ) return;
	hide();
}
