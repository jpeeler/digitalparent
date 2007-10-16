// generated 2007/10/15 11:40:56 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/jmorey/Projects/DigitalParent/DigitalParent.glade
// for gtk 2.10.11 and gtkmm 2.10.8
//
// Please modify the corresponding derived classes in ./src/media_player_dlg.hh and./src/media_player_dlg.cc

#ifndef _MEDIA_PLAYER_DLG_GLADE_HH
#  define _MEDIA_PLAYER_DLG_GLADE_HH

// Since all your widgets were private I made them all public.
// To differentiate between accessable (e.g. entries, output labels)
// and unaccessible widgets (e.g. static labels, containers)
// you should use the 'visibility' property (only visible in C++ mode)


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
#include <gtkmm/button.h>
#include <gtkmm/fixed.h>

class media_player_dlg_glade : public Gtk::Window
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Window * media_player_dlg;
        class Gtk::Button * open_media_button;
        class Gtk::Button * stop_button;
        class Gtk::Button * play_button;
        class Gtk::Button * button5;
        class Gtk::Button * previous_button;
        class Gtk::Button * cut_button;
        class Gtk::Button * next_button;
        class Gtk::Fixed * fixed1;
protected:
        
        media_player_dlg_glade();
        
        ~media_player_dlg_glade();
private:
        virtual void on_open_media_button_clicked() = 0;
        virtual void on_stop_button_clicked() = 0;
        virtual void on_play_button_clicked() = 0;
        virtual void on_button5_clicked() = 0;
        virtual void on_previous_button_clicked() = 0;
        virtual void on_cut_button_clicked() = 0;
        virtual void on_next_button_clicked() = 0;
};
#endif
