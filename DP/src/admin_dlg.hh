// generated 2007/10/31 10:23:45 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to admin_dlg.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _ADMIN_DLG_HH
#  include "admin_dlg_glade.hh"
#include "controller.h"
#include "data_structure.h"
#include <vector>
#include <string>
#  define _ADMIN_DLG_HH

using namespace std;

extern Controller *useController();

class admin_dlg : public admin_dlg_glade
{  
        
        void on_pg_checkbox_toggled();
        void on_unknown_checkbox_toggled();
        void on_pg13_checkbox_toggled();
        void on_nc17_checkbox_toggled();
        void on_nr_checkbox_toggled();
        void on_x_checkbox_toggled();
        void on_r_checkbox_toggled();
        void on_g_checkbox_toggled();
		void on_logout_button_clicked();
        void on_admin_settings_button_clicked();
        void on_add_user_button_clicked();
        void on_edit_user_button_clicked();
		void on_remove_user_button_clicked();
		void on_screen_movies_button_clicked();
		bool on_pssword_confirm_edit_box_key_press_event(GdkEventKey *ev);
        bool on_sec_ques_edit_box_key_press_event(GdkEventKey *ev);
        bool on_password_edit_box_key_press_event(GdkEventKey *ev);
        bool on_sec_ans_edit_box_key_press_event(GdkEventKey *ev);        
        bool on_icon_viewer_key_press_event(GdkEventKey *ev);
		bool on_username_edit_box_key_press_event(GdkEventKey *ev);
        void on_hide_password_checkbox_toggled();
        void on_hide_confirm_checkbox_toggled();
        void on_hide_sec_ques_checkbox_toggled();
        void on_hide_sec_ans_checkbox_toggled();
		void onIconButtonClicked();
		vector<class Gtk::Image*> m_image_list;		
		vector<class Gtk::Button*> m_button_list;		
	public:
		void oninit_admin();
		void oninit_user();
		void oninit_images();
		void fill_image_button_scroller();
		vector<string> m_file_list;
		
	private:
		const User *m_user;
		const User *m_admin;
		
		
};
#endif
