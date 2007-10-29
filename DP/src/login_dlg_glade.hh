// generated 2007/10/29 0:46:38 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /Projects/DP/DigitalParent.glade
// for gtk 2.10.11 and gtkmm 2.10.8
//
// Please modify the corresponding derived classes in ./src/login_dlg.hh and./src/login_dlg.cc

#ifndef _LOGIN_DLG_GLADE_HH
#  define _LOGIN_DLG_GLADE_HH


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
#include <gtkmm/drawingarea.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/separator.h>
#include <gtkmm/fixed.h>
#include <gtkmm/box.h>
#include "images.h"

class login_dlg_glade : public Gtk::Window
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Window * login_dlg;
        class Gtk::DrawingArea * drawingarea2;
        class Gtk::Entry * admin_psswrd_edit_box;
        class Gtk::Button * previous_user_button;
        class Gtk::Image * admin_icon;
        class Gtk::Button * admin_login_button;
        class Gtk::Label * admin_login_label;
        class Gtk::Button * next_user_button;
        class Gtk::HSeparator * hseparator1;
        class Gtk::Image * user_button2_icon;
        class Gtk::Button * user_icon_select_button_2;
        class Gtk::Image * user_button3_icon;
        class Gtk::Button * user_icon_select_button_3;
        class Gtk::Entry * secret_q_edit_box;
        class Gtk::Entry * secret_a_edit_box;
        class Gtk::Label * secret_question_label;
        class Gtk::Label * secret_answer_label;
        class Gtk::Label * login_hint_label;
        class Gtk::Image * user_button1_icon;
        class Gtk::Button * user_icon_select_button_1;
        class Gtk::Fixed * fixed5;
        class Gtk::VBox * vbox1;
		int m_error_count;
protected:
        
        login_dlg_glade();
        
        ~login_dlg_glade();
private:
        virtual void on_admin_psswrd_edit_box_editing_done() = 0;
        virtual void on_previous_user_button_clicked() = 0;
        virtual void on_admin_login_button_clicked() = 0;
        virtual void on_next_user_button_clicked() = 0;
        virtual void on_user_icon_select_button_2_clicked() = 0;
        virtual void on_user_icon_select_button_3_clicked() = 0;
        virtual void on_user_icon_select_button_1_clicked() = 0;
};
#endif
