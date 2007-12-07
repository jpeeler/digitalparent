// generated 2007/12/6 18:26:41 EST by ctemple@Barf.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /Projects/DP/DigitalParent.glade
// for gtk 2.10.11 and gtkmm 2.10.8
//
// Please modify the corresponding derived classes in ./src/DiscRating.cc


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
#include "DiscRating_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/radiobutton.h>

DiscRating_glade::DiscRating_glade(
) : Gtk::Window(Gtk::WINDOW_TOPLEVEL)
{  DiscRating = this;
   gmm_data = new GlademmData(get_accel_group());
   
   Gtk::RadioButton::Group _RadioBGroup_gButton;
   gButton = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_gButton, _("G")));
   pgButton = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_gButton, _("PG")));
   nc17Button = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_gButton, _("NC17")));
   rButton = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_gButton, _("R")));
   pg13Button = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_gButton, _("PG13")));
   image17 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-save"), Gtk::IconSize(4)));
   label15 = Gtk::manage(new class Gtk::Label(_("Save")));
   hbox10 = Gtk::manage(new class Gtk::HBox(false, 2));
   alignment12 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 0, 0));
   saveButton = Gtk::manage(new class Gtk::Button());
   allButton = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_gButton, _("ALL")));
   fixed10 = Gtk::manage(new class Gtk::Fixed());
   gButton->set_size_request(105,21);
   gButton->set_flags(Gtk::CAN_FOCUS);
   gButton->set_relief(Gtk::RELIEF_NORMAL);
   gButton->set_mode(true);
   gButton->set_active(false);
   pgButton->set_size_request(105,21);
   pgButton->set_flags(Gtk::CAN_FOCUS);
   pgButton->set_relief(Gtk::RELIEF_NORMAL);
   pgButton->set_mode(true);
   pgButton->set_active(false);
   nc17Button->set_size_request(105,21);
   nc17Button->set_flags(Gtk::CAN_FOCUS);
   nc17Button->set_relief(Gtk::RELIEF_NORMAL);
   nc17Button->set_mode(true);
   nc17Button->set_active(false);
   rButton->set_size_request(105,21);
   rButton->set_flags(Gtk::CAN_FOCUS);
   rButton->set_border_width(2);
   rButton->set_relief(Gtk::RELIEF_NORMAL);
   rButton->set_mode(true);
   rButton->set_active(false);
   pg13Button->set_size_request(104,24);
   pg13Button->set_flags(Gtk::CAN_FOCUS);
   pg13Button->set_border_width(3);
   pg13Button->set_relief(Gtk::RELIEF_NORMAL);
   pg13Button->set_mode(true);
   pg13Button->set_active(false);
   image17->set_alignment(0.5,0.5);
   image17->set_padding(0,0);
   label15->set_alignment(0.5,0.5);
   label15->set_padding(0,0);
   label15->set_justify(Gtk::JUSTIFY_LEFT);
   label15->set_line_wrap(false);
   label15->set_use_markup(false);
   label15->set_selectable(false);
   hbox10->pack_start(*image17, Gtk::PACK_SHRINK, 0);
   hbox10->pack_start(*label15, Gtk::PACK_SHRINK, 0);
   alignment12->add(*hbox10);
   saveButton->set_size_request(88,32);
   saveButton->set_flags(Gtk::CAN_FOCUS);
   saveButton->set_relief(Gtk::RELIEF_NORMAL);
   saveButton->add(*alignment12);
   allButton->set_size_request(105,21);
   allButton->set_flags(Gtk::CAN_FOCUS);
   allButton->set_relief(Gtk::RELIEF_NORMAL);
   allButton->set_mode(true);
   allButton->set_active(false);
   fixed10->put(*gButton, 16, 8);
   fixed10->put(*pgButton, 16, 32);
   fixed10->put(*nc17Button, 16, 80);
   fixed10->put(*rButton, 16, 104);
   fixed10->put(*pg13Button, 16, 56);
   fixed10->put(*saveButton, 16, 168);
   fixed10->put(*allButton, 16, 128);
   DiscRating->set_title(_("Disc Rating"));
   DiscRating->set_modal(false);
   DiscRating->property_window_position().set_value(Gtk::WIN_POS_NONE);
   DiscRating->set_resizable(true);
   DiscRating->property_destroy_with_parent().set_value(false);
   DiscRating->add(*fixed10);
   gButton->show();
   pgButton->show();
   nc17Button->show();
   rButton->show();
   pg13Button->show();
   image17->show();
   label15->show();
   hbox10->show();
   alignment12->show();
   saveButton->show();
   allButton->show();
   fixed10->show();
   DiscRating->show();
   saveButton->signal_clicked().connect(SigC::slot(*this, &DiscRating_glade::on_saveButton_clicked), false);
}

DiscRating_glade::~DiscRating_glade()
{  delete gmm_data;
}