// generated 2007/10/31 10:23:45 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to admin_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "admin_dlg.hh"
#include <gtkmm/image.h>
#include <gdkmm/pixbufloader.h>
#include <iostream>

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

void admin_dlg::fill_image_button_scroller()
{
}

void admin_dlg::on_add_user_button_clicked()
{  	
	user_label->set_text("");
	username_edit_box->set_text("");
	username_edit_box->set_editable(true);
	
	admin_icon->hide();	
	fixed8->remove(*admin_icon);
	admin_icon = Gtk::manage(new class Gtk::Image(string("/Projects/DP/pixmaps/no_user.png")));
	fixed8->put(*admin_icon, 0, 40);		
	admin_icon->show();
	
	password_edit_box->set_text("");
	hide_password_checkbox->set_active(true);
	pssword_confirm_edit_box->set_text("");
	hide_confirm_checkbox->set_active(true);
	sec_ques_edit_box->set_text("");
	hide_sec_ques_checkbox->set_active(true);
	sec_ans_edit_box->set_text("");
	hide_sec_ans_checkbox->set_active(true);
	
	g_checkbox->show();
	g_checkbox->set_active(true);
	pg_checkbox->show();
	pg_checkbox->set_active(false);
	pg13_checkbox->show();
	pg13_checkbox->set_active(false);
	nc17_checkbox->show();
	nc17_checkbox->set_active(false);
	r_checkbox->show();
	r_checkbox->set_active(false);
	x_checkbox->show();
	x_checkbox->set_active(false);
	nr_checkbox->show();
	nr_checkbox->set_active(false);
	screen_movies_button->show();
	
	hseparator2->show();
	vseparator1->show();
	frame2->show();
	icon_select_frame_label->show();	
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
	//username_edit_box->set_text("admin");
	//username_edit_box->set_editable(false);
	
	admin_icon->hide();	
	fixed8->remove(*admin_icon);
	admin_icon = Gtk::manage(new class Gtk::Image(string("/Projects/DP/pixmaps/tux.png")));
	fixed8->put(*admin_icon, 0, 40);		
	admin_icon->show();

	m_admin = useController()->c_getUserLoggedIn();
	//password_edit_box->set_text(m_admin->getPasswordHash());
	//pssword_confirm_edit_box->set_text(m_admin->getPasswordHash());
	//sec_ques_edit_box->set_text(m_admin->getQuestion());
	//sec_ans_edit_box->set_text(m_admin->getAnswer());
	
}

void admin_dlg::oninit_user()
{
	edit_user_button->hide();
	add_user_button->hide();
	remove_user_button->hide();
	admin_settings_button->hide();
}

void admin_dlg::oninit_images()
{
	system("ls /Projects/DP/images > pixmaps.dat");
	FILE *fp = fopen("pixmaps.dat","r");
	int c;
	string fname = "/Projects/DP/pixmaps/";
	c = fgetc(fp);
	class Gtk::Button *button;
	class Gtk::Image *image;
	while ( c != EOF )
	{
		if ( c == '\n' )
		{
			m_file_list.push_back(fname);
			image = Gtk::manage(new class Gtk::Image(fname)); 
			image->set_alignment(0.5,0.5);
   			image->set_padding(0,0);   
			m_image_list.push_back(image);				
			button = Gtk::manage(new class Gtk::Button());			
			button->set_flags(Gtk::CAN_FOCUS);
  			button->set_relief(Gtk::RELIEF_NORMAL);
			button->add(*image);
   			image->show();	
			button->show();
			m_button_list.push_back(button);
			hbox5->pack_start(*button, Gtk::PACK_SHRINK, 0);
			button->signal_clicked().connect(SigC::slot(*this, &admin_dlg_glade::onIconButtonClicked), false);
			fname = "/Projects/DP/images/";
		}
		else	fname+=c;
		c = fgetc(fp);
	}	
}

void admin_dlg::on_hide_password_checkbox_toggled()
{  
	bool visible = password_edit_box->get_visibility();
	if ( visible ) password_edit_box->set_visibility(false);
	else password_edit_box->set_visibility(true);
}

void admin_dlg::on_hide_confirm_checkbox_toggled()
{  
	bool visible = pssword_confirm_edit_box->get_visibility();
	if ( visible ) pssword_confirm_edit_box->set_visibility(false);
	else pssword_confirm_edit_box->set_visibility(true);
}

void admin_dlg::on_hide_sec_ques_checkbox_toggled()
{  
	bool visible = sec_ques_edit_box->get_visibility();
	if ( visible ) sec_ques_edit_box->set_visibility(false);
	else sec_ques_edit_box->set_visibility(true);		
}

void admin_dlg::on_hide_sec_ans_checkbox_toggled()
{  
	bool visible = sec_ans_edit_box->get_visibility();
	if ( visible ) sec_ans_edit_box->set_visibility(false);
	else sec_ans_edit_box->set_visibility(true);
}

void admin_dlg::onIconButtonClicked()
{
	printf("\nbutton clicked");
	
	for ( unsigned int i = 0; i < m_button_list.size(); i++ )
	{
		if ( get_focus() == m_button_list.at(i) )
		{			
			admin_icon->hide();	
			fixed8->remove(*admin_icon);
			admin_icon = Gtk::manage(new class Gtk::Image(m_file_list.at(i)));
			fixed8->put(*admin_icon, 0, 40);		
			admin_icon->show();
		}
	}
}
