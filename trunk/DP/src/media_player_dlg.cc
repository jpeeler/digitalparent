// generated 2007/10/18 15:52:33 EDT by jmorey@jmorey-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to media_player_dlg.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "media_player_dlg.hh"
#include "playlist_dlg.hh"
#include "media_chooser_dlg.hh"
#include "controller.h"

#include <vlc/libvlc.h>


//~ libvlc_exception_t excp;
//~ libvlc_instance_t *inst;
//char *filename = "/home/ctemple/clemson/ece453/Marisa Tomei Hanes Commercial.gvi";
char *filename ="/media/cdrom0";
char **test =NULL;
const char *playtimes[2]={":start-time=0",":stop-time=30"};
const char *playtimes2[2]={":start-time=45",":stop-time=60"};
int item;
int id;
bool firstTime = false;
playlist_dlg *playlist_dlg;
media_chooser_dlg *media_chooser;
bool audioSkipped=false;
Gtk::CheckButton * checkbutton;
bool isAdmin;

extern Controller* useController();



void media_player_dlg::init()
{
	isAdmin = useController()->c_getUserLoggedIn()->getUser()=="admin";
	libvlc_exception_init(&excp);
  	inst = libvlc_new (0, test, &excp);
	id = libvlc_get_vlc_id(inst);
	volume_slider->set_value(libvlc_audio_get_volume(inst,&excp));
	item = libvlc_playlist_add_extended (inst, filename, NULL,2,playtimes, &excp);
	libvlc_playlist_add_extended (inst, filename, NULL,2,playtimes2, &excp);
	if(!isAdmin){
		cut_audio->hide();
		cut_video->hide();
	}

}

void media_player_dlg::on_open_media_button_clicked()
{  
	//~ libvlc_exception_init(&excp);
  	//~ inst = libvlc_new (0, test, &excp);
  	//item= libvlc_playlist_add(inst,filename,NULL,&excp);
	if(inst==NULL){
	printf("VLC set up\n");
	init();
	}
	
	//~ item = libvlc_playlist_add_extended (inst, filename, NULL,2,playtimes, &excp);
	//~ libvlc_playlist_add_extended (inst, filename, NULL,2,playtimes2, &excp);
	//media_chooser =  new class mFILE_CHOOSER_ACTION_OPENedia_chooser_dlg("Choose File",Gtk::FILE_CHOOSER_ACTION_OPEN);
	//media_chooser->show();	
}

void media_player_dlg::on_stop_button_clicked()
{
  libvlc_playlist_stop(inst,&excp);
  
}

void media_player_dlg::on_previous_button_clicked()
{  
	libvlc_playlist_prev(inst,&excp);
}

void media_player_dlg::on_rewind_button_clicked()
{
	VLC_SpeedSlower(id);
}

void media_player_dlg::on_cut_video_toggled()
{  
	int time;
	//time = libvlc_vlm_get_media_time(inst,filename,time,&excp);
	time=VLC_TimeGet(id);
	time_slider->set_value(VLC_TimeGet(id));
	printf("Video Lenght: %d\n",VLC_LengthGet(id));
	printf("Video time:  %d\n",time);
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
	//~ while(libvlc_playlist_isplaying(inst,&excp)){
		//~ if(VLC_TimeGet(id)<0){
			//~ time_slider->set_value(0);
		//~ } else {
		//~ time_slider->set_value(VLC_TimeGet(id));
		//~ }
	//~ }
}

void media_player_dlg::on_time_slider_value_changed()
{  
	time_slider->set_range(0,VLC_LengthGet(id));	
	VLC_TimeSet(id,(int)time_slider->get_value(),false);
}

void media_player_dlg::on_playlist_button_toggled()
{
	if(!firstTime){
		playlist_dlg = new class playlist_dlg();
		firstTime= true;
	}
	if(playlist_button->get_active()){
		for(uint i=0; i< sizeof playtimes/sizeof *playtimes; i++){
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


void media_player_dlg::on_volume_slider_value_changed()
{  
	libvlc_audio_set_volume(inst,(int)volume_slider->get_value(),&excp);
}

void media_player_dlg::on_Logout_clicked()
{  
	libvlc_destroy (inst);
	hide();
}

void media_player_dlg::on_cut_audio_toggled()
{  
	int time;
	//time = libvlc_vlm_get_media_time(inst,filename,time,&excp);
	time=VLC_TimeGet(id);
	printf("Audio time:  %d\n",time);
}

void media_player_dlg::on_mute_button_toggled()
{  
	if(!audioSkipped || !isAdmin){
		VLC_VolumeMute(id);
	} 
}
