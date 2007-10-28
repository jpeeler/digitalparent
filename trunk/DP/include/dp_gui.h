#ifndef __DP_GUI__
#define __DP_GUI__

#include <string.h>
#include <vector>
#include "data_structure.h"
#include "controller.h"

typedef enum {
	STOP,
	START,
	RUNONCE,
	LOGIN,
	PROMPT_PASSWORD,
	EDIT_USER,
	USER_PLAY,
	ADMIN_PLAY
} MODE;
User *m_current_user;
std::vector<User> *m_user_list;
Controller *m_control;
MODE m_mode;
Glib::RefPtr<Gtk::Clipboard> m_DPClipboard;

class DP_Gui
{
	
public:
	void on_welcome_text_received(const Glib::ustring& text);
};

#endif //__DP_GUI__
