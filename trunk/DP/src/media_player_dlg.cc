// generated 2007/10/18 15:52:33 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to media_player_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "media_player_dlg.hh"
#include "libvlc.h"


libvlc_exception_t excp;
libvlc_instance_t *inst;
char *filename = "/home/ctemple/clemson/ece453/Marisa Tomei Hanes Commercial.gvi";
char **test =NULL;
const char *playtimes[3]={":start-time=1",":stop-time=5"};
const char *playtimes2[2]={":start-time=11",":stop-time=15"};
int item;
int id;



void media_player_dlg::on_open_media_button_clicked()
{  
	libvlc_exception_init(&excp);
  	inst = libvlc_new (0, test, &excp);
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

void media_player_dlg::on_cut_button_clicked()
{  
	int time;
	time = VLC_TimeGet(id);
	printf("Play time:  %d\n",time);
}

void media_player_dlg::on_next_button_clicked()
{  
	//	VLC_SpeedFaster(id);
	libvlc_playlist_next(inst,&excp);
}

void media_player_dlg::on_pause_button_clicked()
{  
	libvlc_playlist_pause(inst,&excp);
}

void media_player_dlg::on_play_button_clicked()
{  
//system("/Projects/DP/src/demo");
	  libvlc_playlist_play (inst, item, 0, NULL, &excp);
}
