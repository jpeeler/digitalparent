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
#  define _ADMIN_DLG_HH

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
        void on_edit_User_clicked();
		void on_remove_user_button_clicked();
		void on_screen_movies_button_clicked();
		bool on_pssword_confirm_edit_box_key_press_event(GdkEventKey *ev);
        bool on_sec_ques_edit_box_key_press_event(GdkEventKey *ev);
        bool on_password_edit_box_key_press_event(GdkEventKey *ev);
        bool on_sec_ans_edit_box_key_press_event(GdkEventKey *ev);        
        bool on_icon_viewer_key_press_event(GdkEventKey *ev);
		bool on_username_edit_box_key_press_event(GdkEventKey *ev);
};
#endif
