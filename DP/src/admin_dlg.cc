// generated 2007/10/31 10:23:45 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to admin_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "admin_dlg.hh"

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

void admin_dlg::on_edit_User_clicked()
{  
}

void admin_dlg::on_remove_user_button_clicked()
{  
}

void admin_dlg::on_screen_movies_button_clicked()
{  
	useController()->m_mode = ADMIN_PLAY;
	hide();
}
