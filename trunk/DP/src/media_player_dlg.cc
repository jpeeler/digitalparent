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
const char *playtimes[2]={":start-time=5",":stop-time=8"};
int item;


void media_player_dlg::on_open_media_button_clicked()
{  
  libvlc_exception_init(&excp);
  inst = libvlc_new (0, test, &excp);
  item = libvlc_playlist_add_extended (inst, filename, NULL,2,playtimes, &excp);
}

void media_player_dlg::on_stop_button_clicked()
{

  libvlc_playlist_stop(inst,&excp);
  usleep (10000000);
  libvlc_destroy (inst);	
}

void media_player_dlg::on_previous_button_clicked()
{  
}

void media_player_dlg::on_cut_button_clicked()
{  
}

void media_player_dlg::on_next_button_clicked()
{  
}

void media_player_dlg::on_pause_button_clicked()
{  
	libvlc_playlist_pause(inst,&excp);
	//printf("Play time: " %d,libvlc_vlm_get_media_time(inst,var,&excp);
}

void media_player_dlg::on_play_button_clicked()
{  
//system("/Projects/DP/src/demo");
	  libvlc_playlist_play (inst, item, 0, NULL, &excp);
}
