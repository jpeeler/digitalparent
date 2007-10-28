// generated 2007/10/16 21:20:58 EDT by jmorey@jmorey-desktop.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /Projects/DP/DigitalParent.glade
// for gtk 2.10.11 and gtkmm 2.10.8
//
// Please modify the corresponding derived classes in ./src/psswrd_prompt_dlg.cc


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
#include <gtkmmconfig.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#include <sigc++/compatibility.h>
#define GMM_GTKMM_22_24(a,b) b
#else //gtkmm 2.2
#define GMM_GTKMM_22_24(a,b) a
#endif //
#include "psswrd_prompt_dlg_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>

psswrd_prompt_dlg_glade::psswrd_prompt_dlg_glade(
) : Gtk::Window(Gtk::WINDOW_TOPLEVEL)
{  psswrd_prompt_dlg = this;
   gmm_data = new GlademmData(get_accel_group());
   psswrd_edit_box = Gtk::manage(new class Gtk::Entry());
   login_text_box = Gtk::manage(new class Gtk::TextView());
   drawingarea1 = Gtk::manage(new class Gtk::DrawingArea());
   drawingarea5 = Gtk::manage(new class Gtk::DrawingArea());
   login_icon_button = Gtk::manage(new class Gtk::Button());
   fixed2 = Gtk::manage(new class Gtk::Fixed());
   psswrd_edit_box->set_size_request(160,27);
   psswrd_edit_box->set_flags(Gtk::CAN_FOCUS);
   psswrd_edit_box->set_visibility(false);
   psswrd_edit_box->set_editable(true);
   psswrd_edit_box->set_max_length(16);
   psswrd_edit_box->set_text(_(""));
   psswrd_edit_box->set_has_frame(true);
   psswrd_edit_box->set_activates_default(true);
   login_text_box->set_size_request(160,40);
   login_text_box->set_flags(Gtk::CAN_FOCUS);
   login_text_box->set_editable(false);
   login_text_box->set_cursor_visible(false);
   login_text_box->set_pixels_above_lines(0);
   login_text_box->set_pixels_below_lines(0);
   login_text_box->set_pixels_inside_wrap(0);
   login_text_box->set_left_margin(0);
   login_text_box->set_right_margin(0);
   login_text_box->set_indent(0);
   login_text_box->set_wrap_mode(Gtk::WRAP_WORD);
   login_text_box->set_justification(Gtk::JUSTIFY_LEFT);
   login_text_box->get_buffer()->set_text(_("Please Enter the Password For This User"));
   drawingarea1->set_size_request(312,16);
   login_icon_button->set_size_request(128,112);
   login_icon_button->set_flags(Gtk::CAN_FOCUS);
   login_icon_button->set_relief(Gtk::RELIEF_NORMAL);
   login_icon_button->add(*drawingarea5);
   fixed2->put(*psswrd_edit_box, 152, 88);
   fixed2->put(*login_text_box, 152, 24);
   fixed2->put(*drawingarea1, 16, 128);
   fixed2->put(*login_icon_button, 8, 8);
   psswrd_prompt_dlg->set_title(_("Login -  Password Required"));
   psswrd_prompt_dlg->set_modal(false);
   psswrd_prompt_dlg->property_window_position().set_value(Gtk::WIN_POS_CENTER);
   psswrd_prompt_dlg->set_resizable(false);
   psswrd_prompt_dlg->property_destroy_with_parent().set_value(false);
   psswrd_prompt_dlg->add(*fixed2);
   psswrd_edit_box->show();
   login_text_box->show();
   drawingarea1->show();
   drawingarea5->show();
   login_icon_button->show();
   fixed2->show();
   psswrd_prompt_dlg->show();
   psswrd_edit_box->signal_editing_done().connect(SigC::slot(*this, &psswrd_prompt_dlg_glade::on_psswrd_edit_box_editing_done), false);
   login_icon_button->signal_clicked().connect(SigC::slot(*this, &psswrd_prompt_dlg_glade::on_login_icon_button_clicked), false);
}

psswrd_prompt_dlg_glade::~psswrd_prompt_dlg_glade()
{  delete gmm_data;
}