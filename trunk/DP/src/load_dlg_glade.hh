// generated 2007/12/5 8:23:26 EST by pwightm@pwightm-desktop3.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /Projects/DP/DigitalParent.glade
// for gtk 2.12.0 and gtkmm 2.2.12
//
// Please modify the corresponding derived classes in ./src/load_dlg.hh and./src/load_dlg.cc

#ifndef _LOAD_DLG_GLADE_HH
#  define _LOAD_DLG_GLADE_HH


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
#include <gtkmm/progressbar.h>
#include <gtkmm/label.h>
#include <gtkmm/fixed.h>

class load_dlg_glade : public Gtk::Window
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Window * load_dlg;
        class Gtk::ProgressBar * load_progress;
        class Gtk::Label * loading_label;
        class Gtk::Fixed * fixed9;
protected:
        
        load_dlg_glade();
        
        ~load_dlg_glade();
};
#endif
