/*
Copyright(c) 2017 Björn Marx
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//#define USE_SDL_MIXER

#include "main.h"

#include <QtWidgets/QWidget>
#include "ui_lwmp.h"

class LWMP : public QWidget
{
	Q_OBJECT

public:
	LWMP(QWidget *parent = Q_NULLPTR);
	~LWMP();

private:
	// updates title list on changed path entry in the selection combo box
	void update_titlelist();

#pragma region slot funktion for UI interaction events

	// sets m_mixAudio stream to selected title
	// called when ui.m_lwTitlelist::itemDoubleClicked is emitted
	void set_title();

	// opens dictionary select dialog and loads its contents
	// called when ui.m_btnSelectFolder::clicked is emitted
	void select_dictionary();

	// explains itself
	// called when ui.m_hsVolume::valueChanged is emitted
	void change_volume();
	
	void media_state_changed_event(QMediaPlayer::MediaStatus newState);

public:
	//pasues or resumes the music
	void play();
	//previous title (in list)
	void previous_title();
	//next title
	void next_title();

#pragma endregion
private:
	//user interface class
	Ui::LWMPClass ui;

	// thumbnail buttons
	/* 
	*	// instance to manipulate the thumbnail
	*	QWinThumbnailToolBar *m_ttbThumbnailToolbar;
	*	//thumbnail buttons
	*	QWinThumbnailToolButton *m_ttbtnNext;
	*	QWinThumbnailToolButton *m_ttbtnPause;
	*	QWinThumbnailToolButton *m_ttbtnPrevious;
	*/

#ifdef USE_SDL_MIXER

	Mix_Music *m_mixAudio;

#else

	QMediaPlayer m_mpMediaPlayer;

#endif // USE_SDL_MIXER
};
