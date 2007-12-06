// generated 2007/12/6 12:12:01 EST by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /Projects/DP/DigitalParent.glade
// for gtk 2.10.11 and gtkmm 2.10.8
//
// Please modify the corresponding derived classes in ./src/admin_dlg.hh and./src/admin_dlg.cc

#ifndef _ADMIN_DLG_GLADE_HH
#  define _ADMIN_DLG_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  
        
        Glib::RefPtr<Gtk::AccelGroup> accgrp;
public:
        
        GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
        {  
        }
        
        Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtkmm/window.h>
#include <gtkmm/separator.h>
#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/entry.h>
#include <gtkmm/table.h>
#include <gtkmm/viewport.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/image.h>
#include <gtkmm/fixed.h>

class admin_dlg_glade : public Gtk::Window
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Window * admin_dlg;
        class Gtk::VSeparator * vseparator1;
        class Gtk::Button * logout_button;
        class Gtk::RadioButton * g_radio_button;
        class Gtk::RadioButton * pg_radio_button;
        class Gtk::RadioButton * pg13_radio_button;
        class Gtk::RadioButton * nc17_radio_button;
        class Gtk::RadioButton * r_radio_button;
        class Gtk::RadioButton * x_radio_button;
        class Gtk::CheckButton * nr_checkbox;
        class Gtk::Button * screen_movies_button;
        class Gtk::VBox * vbox7;
        class Gtk::Alignment * alignment7;
        class Gtk::Label * user_level_label;
        class Gtk::Frame * frame3;
        class Gtk::Button * add_user_button;
        class Gtk::Button * edit_user_button;
        class Gtk::Button * remove_user_button;
        class Gtk::Label * error_label;
        class Gtk::Entry * user_name_edit_box;
        class Gtk::Entry * password_edit_box;
        class Gtk::CheckButton * cf_checkbox;
        class Gtk::CheckButton * sq_checkbox;
        class Gtk::CheckButton * sa_checkbox;
        class Gtk::Entry * confirm_edit_box;
        class Gtk::Entry * sq_edit_box;
        class Gtk::Entry * sa_edit_box;
        class Gtk::Button * user_save_button;
        class Gtk::CheckButton * pw_checkbox;
        class Gtk::Label * confirm_label;
        class Gtk::Label * label10;
        class Gtk::Label * user_name_label;
        class Gtk::Label * sa_label;
        class Gtk::Label * sq_label;
        class Gtk::Table * table1;
        class Gtk::VBox * vbox6;
        class Gtk::VBox * vbox5;
        class Gtk::Alignment * alignment5;
        class Gtk::Frame * frame1;
        class Gtk::HBox * hbox5;
        class Gtk::Viewport * viewport1;
        class Gtk::ScrolledWindow * scrolledwindow1;
        class Gtk::Alignment * alignment6;
        class Gtk::Label * icon_select_frame_label;
        class Gtk::Frame * frame2;
        class Gtk::HSeparator * hseparator3;
        class Gtk::Button * media_player_button;
        class Gtk::Button * admin_settings_button;
        class Gtk::Button * change_icon_button;
        class Gtk::Button * confirm_delete_button;
        class Gtk::Label * user_label;
        class Gtk::HSeparator * hseparator2;
        class Gtk::Button * cancel_delete_button;
        class Gtk::Label * confirn_delete_label;
        class Gtk::Image * admin_icon;
        class Gtk::Fixed * fixed8;
		virtual void onIconButtonClicked() = 0;
protected:
        
        admin_dlg_glade();
        
        ~admin_dlg_glade();
private:
        virtual void on_logout_button_clicked() = 0;
        virtual void on_screen_movies_button_clicked() = 0;
        virtual void on_add_user_button_clicked() = 0;
        virtual void on_edit_user_button_clicked() = 0;
        virtual void on_remove_user_button_clicked() = 0;
        virtual void on_cf_checkbox_toggled() = 0;
        virtual void on_sq_checkbox_toggled() = 0;
        virtual void on_sa_checkbox_toggled() = 0;
        virtual void on_user_save_button_clicked() = 0;
        virtual void on_pw_checkbox_toggled() = 0;
        virtual void on_media_player_button_clicked() = 0;
        virtual void on_admin_settings_button_clicked() = 0;
        virtual void on_change_icon_clicked() = 0;
        virtual void on_confirm_delete_button_clicked() = 0;
        virtual void on_cancel_delete_button_clicked() = 0;
        virtual bool on_admin_dlg_delete_event(GdkEventAny *ev) = 0;
};
#endif
