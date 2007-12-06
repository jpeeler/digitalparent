// generated 2007/12/5 10:01:36 EST by pwightm@pwightm-desktop3.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /Projects/DP/DigitalParent.glade
// for gtk 2.12.0 and gtkmm 2.2.12
//
// Please modify the corresponding derived classes in ./src/load_dlg.cc


#if defined __GNUC__ && __GNUC__ < 3
#error This program will crash if compiled with g++ 2.x
// see the dynamic_cast bug in the gtkmm FAQ
#endif //
#include "config.h"
/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (GETTEXT_PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif
#include "load_dlg_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>

load_dlg_glade::load_dlg_glade(
) : Gtk::Window(Gtk::WINDOW_POPUP)
{  load_dlg = this;
   gmm_data = new GlademmData(get_accel_group());
   load_progress = Gtk::manage(new class Gtk::ProgressBar());
   loading_label = Gtk::manage(new class Gtk::Label(_("Loading DVD information...")));
   fixed9 = Gtk::manage(new class Gtk::Fixed());
   load_progress->set_size_request(208,24);
   loading_label->set_size_request(240,32);
   loading_label->set_flags(Gtk::CAN_FOCUS);
   loading_label->set_alignment(0.5,0.5);
   loading_label->set_padding(0,0);
   loading_label->set_justify(Gtk::JUSTIFY_LEFT);
   loading_label->set_line_wrap(false);
   loading_label->set_use_markup(false);
   loading_label->set_selectable(true);
   fixed9->grab_focus();
   fixed9->put(*load_progress, 16, 56);
   fixed9->put(*loading_label, 0, 16);
   load_dlg->set_size_request(243,100);
   load_dlg->set_sensitive(false);
   load_dlg->grab_focus();
   load_dlg->set_title(_("Digital Parent"));
   load_dlg->set_modal(false);
   load_dlg->property_window_position().set_value(Gtk::WIN_POS_CENTER);
   load_dlg->set_resizable(false);
   load_dlg->property_destroy_with_parent().set_value(false);
   load_dlg->add(*fixed9);
   load_progress->show();
   loading_label->show();
   fixed9->show();
   load_dlg->show();
}

load_dlg_glade::~load_dlg_glade()
{  delete gmm_data;
}