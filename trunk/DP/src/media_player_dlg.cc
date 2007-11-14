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
#include <gtkmm/checkbutton.h>
#include <dvdnav/dvdnav.h>

#include <sstream>


std::string filename= "/dev/dvd";
const char **dvdtitle;
const char *playtimes[4]={":start-time=0",":stop-time=30",":start-time=45",":stop-time=60"};
int item;
int id;
bool firstTime = true;
playlist_dlg *playlist_dlg;
media_chooser_dlg *media_chooser;
bool audioSkipped=false;
Gtk::CheckButton * checkbutton;
bool isAdmin;
long startTime;
long endTime;
int dvdLength;


extern Controller* useController();



void media_player_dlg::init()
{
	isAdmin = useController()->c_getUserLoggedIn()->getUser()=="admin";
	char **test =NULL;					//used for VLC only
	libvlc_exception_init(&excp);
  	inst = libvlc_new (0, test, &excp);
	id = libvlc_get_vlc_id(inst);
	item = libvlc_playlist_add_extended (inst, filename.c_str(), NULL,sizeof playtimes/sizeof *playtimes,playtimes, &excp);
	
	useController()->loadDisc();
	
	currentUser->set_text("User: " +useController()->c_getUserLoggedIn()->getUser());
	media->set_text(useController()->c_getDisc()->getDiscName());
	if(!isAdmin){
		cut_video->hide();
	}
	
	playlist_dlg = new class playlist_dlg();
	playlist_dlg->hide();						//made so the dlg isn't shown
	
	volume_slider->set_value(libvlc_audio_get_volume(inst,&excp));
	time_slider->set_range(0,VLC_LengthGet(id));
	
	
	slider_signal = Glib::signal_idle().connect(SigC::slot(*this, &media_player_dlg::update_slider));
	buildPlaylist();

}

void media_player_dlg::on_open_media_button_clicked()
{  
	libvlc_destroy(inst);
	init();
/* 	if(inst==NULL){
 * 	printf("VLC set up\n");
 * 	init();
 * 	}
 * 	libvlc_destroy (inst);
 * 	inst = libvlc_new (0, test, &excp);
 * 	id = libvlc_get_vlc_id(inst);
 * 	item = libvlc_playlist_add_extended (inst, filename.c_str(), NULL,sizeof filename/sizeof *playtimes,playtimes, &excp);
 * 	media->set_text("Currently Playing: " + filename);
 * 	status = dvdnav_get_title_string(dvdnav, dvdtitle);
 * 	printf("DVD title: %s\n",dvdtitle);
 */
		
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
	
	//time = libvlc_vlm_get_media_time(inst,filename,time,&excp);
	if(cut_video->get_active()){
		startTime = (long)VLC_TimeGet(id);
		dvdLength = VLC_LengthGet(id);
		printf("Cut Video start time:  %ld\n",startTime);
	} else {
		endTime = (long)VLC_TimeGet(id);
		printf("Cut Video end time:  %ld\n",endTime);
	
		if(startTime < endTime){
			//useController()->addSkipTiming(startTime,endTime);
			printf("Added skip time\tStart time: %ld\tEnd time: %ld\n",startTime, endTime);
		} else {
			//useController()->addSkipTiming(startTime,(long)dvdLength);
			printf("Length: %d\n",VLC_LengthGet(id));
			printf("Start time not smaller then end time\n");
			printf("Added skip time\tStart time: %ld\tEnd time: %d\n",startTime,dvdLength);
		}
	}
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
	//not using becuase it will restart playback if play is hit when paused
	//libvlc_playlist_play (inst, item, 0, NULL, &excp); 
	VLC_Play(id);
}

bool media_player_dlg::update_slider()
{
	if(libvlc_playlist_isplaying(inst,&excp)){
		if(VLC_TimeGet(id)<0){
			time_slider->set_value(0);
		} else {
			time_slider->set_value(VLC_TimeGet(id));
		}
	}
	
	return true;
}

void media_player_dlg::on_time_slider_value_changed()
{  
	//time_slider->set_range(0,VLC_LengthGet(id));	
	//VLC_TimeSet(id,(int)time_slider->get_value(),false);
}

bool media_player_dlg::on_time_slider_button_press(GdkEventButton *ev)
{  
       slider_signal.disconnect();
       return 0;
}

bool media_player_dlg::on_time_slider_button_release_event(GdkEventButton *ev)
{
       VLC_TimeSet(id,(int)time_slider->get_value(),false);
       slider_signal = Glib::signal_idle().connect(SigC::slot(*this, &media_player_dlg::update_slider));

       return 0;
}


void media_player_dlg::on_playlist_button_toggled()
{
	if(playlist_button->get_active()){
		if(firstTime){
			firstTime=false;
			for(uint i=0; i< sizeof playtimes/sizeof *playtimes; i++){
 				printf("i: %d\n", i);
				if(i%2==0){
				checkbutton = new class Gtk::CheckButton(playtimes[i]);
				} else {
					checkbutton->set_label(checkbutton->get_label() +" , " + playtimes[i]);
				}
				checkbutton->set_active();
				//checkbutton->show();
				playlist_dlg->vbox4->pack_start(*checkbutton, Gtk::PACK_EXPAND_WIDGET, 0);
			}
		}
		//playlist_dlg->vbox4->show();
		//playlist_dlg->show();
		playlist_dlg->show_all_children();
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
	if(inst!=NULL){
		libvlc_destroy (inst);
	}
	if(!isAdmin){
		hide();
	} else {
		useController()->dp_state=DP_LOGIN;
		hide();
	}
}

void media_player_dlg::on_fullscreen_clicked()
{  
	VLC_FullScreen(id);
}

void media_player_dlg::on_mute_button_toggled()
{  
		VLC_VolumeMute(id);
}


bool media_player_dlg::on_delete_event(GdkEventAny * event){
	libvlc_destroy(inst);
	return true;
}



void media_player_dlg::buildPlaylist(){
	//const Profile *aprofile = useController()->c_getProfile();
	//const std::vector<SkipTime>& skipTimes = aprofile->getSkipTimes();
	std::vector<SkipTime> skipTimes;
	SkipTime askiptime1;
	askiptime1.setSkipStart(30);
	askiptime1.setSkipStop(60);
	skipTimes.push_back(askiptime1);
	SkipTime askiptime2;
	askiptime2.setSkipStart(90);
	askiptime2.setSkipStop(100);
	skipTimes.push_back(askiptime2);
	SkipTime askiptime3;
	askiptime3.setSkipStart(110);
	askiptime3.setSkipStop(200);
	skipTimes.push_back(askiptime3);
	const char *times[6];

	
	printf("Correct Skip Times\n");
/* 	for (std::vector<SkipTime>::const_iterator itt = skipTimes.begin();
 * 		itt!=skipTimes.end(); ++itt)
 * 	{
 * 		printf("[%ld-%ld] ",itt->getSkipStart(), itt->getSkipStop());
 * 	}
 * 	puts("");
 */
	int counter=0;
	std::string temp;
	std::vector<SkipTime>::const_iterator it;
	for (it = skipTimes.begin(); it!=skipTimes.end(); ++it){
		if(it->getSkipStart()!=0 && counter==0){
			printf("$$$$$Entering Skip time != zero$$$$$\n");
			times[counter]=":startTime=0";
			printf("times[%d]: %s\n",counter,times[counter]);
			counter++;
			temp=":endTime="+to_string(it->getSkipStart());
			times[counter]= temp.c_str();
			printf("times[%d]: %s\n",counter,times[counter]);
			counter++;
			temp=":startTime="+to_string(it->getSkipStop());
			times[counter]=temp.c_str();
			printf("times[%d]: %s\n",counter,times[counter]);
			counter++;
			printf("$$$$$Leaving skip time != zero$$$$$\n");
		} else {
			printf("*****entering Else*****\n");
			temp=":startTime="+ to_string(it->getSkipStop());
			times[counter]=temp.c_str();
			printf("times[%d]: %s\n",counter,times[counter]);
			counter++;
			temp=":endTime=" + to_string(it->getSkipStart());
			times[counter]=temp.c_str();
			printf("times[%d]: %s\n",counter,times[counter]);
			counter++;
			printf("*****end of else*****\n");
		}
		if(counter%2==0){
			temp=":endTime="+ to_string(it->getSkipStop());
			times[counter]=temp.c_str();
			printf("times[%d]: %s\n",counter,times[counter]);
			counter++;
			temp=":startTime=" + to_string(it->getSkipStart());
			times[counter]=temp.c_str();
			printf("times[%d]: %s\n",counter,times[counter]);
			counter++;
		} else {
			temp=":startTime="+ to_string(it->getSkipStart());
			times[counter]=temp.c_str();
			printf("times[%d]: %s\n",counter,times[counter]);
			counter++;
			temp=":endTime=" + to_string(it->getSkipStop());
			times[counter]=temp.c_str();
			printf("times[%d]: %s\n",counter,times[counter]);
			counter++;
		}
			
	}
	printf("Skip Times start\n");
	for(uint i=0; i< sizeof times/sizeof *times; i++){
		printf(times[i]);
		printf("\n");
	}
	printf("Skip Times end\n");
	
}

template <class T>
inline std::string media_player_dlg::to_string (const T& t)
{
std::stringstream ss;
ss << t;
return ss.str();
}
