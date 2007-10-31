// generated 2007/10/31 10:23:45 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to admin_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "admin_dlg.hh"
#include "data_structure.h"
#include <string>
#include <gtkmm/image.h>
#include <gdkmm/pixbufloader.h>

using namespace std;

void admin_dlg::on_pg_checkbox_toggled()
{  
}

void admin_dlg::on_unknown_checkbox_toggled()
{  
}

void admin_dlg::on_pg13_checkbox_toggled()
{  
}

void admin_dlg::on_nc17_checkbox_toggled()
{  
}

void admin_dlg::on_nr_checkbox_toggled()
{  
}

void admin_dlg::on_x_checkbox_toggled()
{  
}

void admin_dlg::on_r_checkbox_toggled()
{  
}

void admin_dlg::on_g_checkbox_toggled()
{  
}

bool admin_dlg::on_pssword_confirm_edit_box_key_press_event(GdkEventKey *ev)
{  return 0;
}

bool admin_dlg::on_sec_ques_edit_box_key_press_event(GdkEventKey *ev)
{  return 0;
}

bool admin_dlg::on_password_edit_box_key_press_event(GdkEventKey *ev)
{  return 0;
}

bool admin_dlg::on_sec_ans_edit_box_key_press_event(GdkEventKey *ev)
{  return 0;
}

bool admin_dlg::on_icon_viewer_key_press_event(GdkEventKey *ev)
{  return 0;
}


bool admin_dlg::on_username_edit_box_key_press_event(GdkEventKey *ev)
{  return 0;
}

void admin_dlg::on_logout_button_clicked()
{  
	useController()->m_mode = LOGIN;
	useController()->c_clearUserLoggedIn();
	hide();
}

void admin_dlg::on_admin_settings_button_clicked()
{  
}

void admin_dlg::on_add_user_button_clicked()
{  
}

void admin_dlg::on_edit_user_button_clicked()
{  
}

void admin_dlg::on_remove_user_button_clicked()
{  
}

void admin_dlg::on_screen_movies_button_clicked()
{  
	if ( useController()->m_mode == ADMIN_PANEL )
		useController()->m_mode = ADMIN_PLAY;
	else useController()->m_mode = USER_PLAY;
	hide();
}

void admin_dlg::oninit_admin()
{
	user_label->set_text("admin");
	username_edit_box->set_text("admin");
	username_edit_box->set_editable(false);
	
	admin_icon->hide();	
	fixed8->remove(*admin_icon);
	admin_icon = Gtk::manage(new class Gtk::Image(string("/Projects/DP/pixmaps/tux.png")));
	fixed8->put(*admin_icon, 0, 40);		
	admin_icon->show();

	const User *a_user = useController()->c_getUserLoggedIn();
	password_edit_box->set_text(a_user->getPasswordHash());	
	
}

void admin_dlg::oninit_user()
{
	edit_user_button->hide();
	add_user_button->hide();
	remove_user_button->hide();
	admin_settings_button->hide();
}

void admin_dlg::on_hide_password_checkbox_toggled()
{  
}

void admin_dlg::on_hide_confirm_checkbox_toggled()
{  
}

void admin_dlg::on_hide_sec_ques_checkbox_toggled()
{  
}

void admin_dlg::on_hide_sec_ans_checkbox_toggled()
{  
}
