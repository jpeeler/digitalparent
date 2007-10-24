// generated 2007/10/18 15:52:33 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to media_player_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "media_player_dlg.hh"
#include "playlist_dlg.hh"
//#include "playlist_dlg_glade.hh"
#include <vlc/libvlc.h>


libvlc_exception_t excp;
libvlc_instance_t *inst;
char *filename = "/home/ctemple/clemson/ece453/Marisa Tomei Hanes Commercial.gvi";
char **test =NULL;
const char *playtimes[2]={":start-time=1",":stop-time=5"};
const char *playtimes2[2]={":start-time=11",":stop-time=15"};
int item;
int id;
bool firstTime = false;
playlist_dlg *playlist_dlg;
Gtk::CheckButton * checkbutton;



void media_player_dlg::on_open_media_button_clicked()
{  
	libvlc_exception_init(&excp);
  	inst = libvlc_new (0, test, &excp);
  	//item= libvlc_playlist_add(inst,filename,NULL,&excp);
	item = libvlc_playlist_add_extended (inst, filename, NULL,2,playtimes, &excp);
	libvlc_playlist_add_extended (inst, filename, NULL,2,playtimes2, &excp);
	id = libvlc_get_vlc_id(inst);
	
}

void media_player_dlg::on_stop_button_clicked()
{
  libvlc_playlist_stop(inst,&excp);
  usleep (10000000);
  libvlc_destroy (inst);	
}

void media_player_dlg::on_previous_button_clicked()
{  
	libvlc_playlist_prev(inst,&excp);
}

void media_player_dlg::on_rewind_button_clicked()
{
	VLC_SpeedSlower(id);
}

void media_player_dlg::on_cut_button_toggled()
{  
	int time;
	time = VLC_TimeGet(id);
	printf("Play time:  %d\n",time);
}

void media_player_dlg::on_next_button_clicked()
{  
	libvlc_playlist_next(inst,&excp);
}

void media_player_dlg::on_fastforward_button_clicked()
{
	VLC_SpeedFaster(id);
}

void media_player_dlg::on_pause_button_clicked()
{  
	libvlc_playlist_pause(inst,&excp);
}

void media_player_dlg::on_play_button_clicked()
{  
	  libvlc_playlist_play (inst, item, 0, NULL, &excp);
	hscale1->set_value(0);
}

void media_player_dlg::on_hscale1_value_changed()
{  
	printf("Length: %d\n" , VLC_LengthGet(id));
	printf("hscale Value: %f\n", hscale1->get_value());
	hscale1->set_range(0,VLC_LengthGet(id));	
	VLC_TimeSet(id,(int)hscale1->get_value(),false);
}

void media_player_dlg::on_playlist_button_toggled()
{
	if(!firstTime){
		playlist_dlg = new class playlist_dlg();
		firstTime= true;
	}
	if(playlist_button->get_active()){
		for(int i=0; i< sizeof playtimes/sizeof *playtimes; i++){
printf("i: %d\n", i);
			checkbutton = new class Gtk::CheckButton(playtimes[i]);
			playlist_dlg->vbox4->pack_end(*checkbutton, Gtk::PACK_EXPAND_WIDGET, 0);
		}
			playlist_dlg->show();
	}
	else{
			playlist_dlg->hide();
	}
}
