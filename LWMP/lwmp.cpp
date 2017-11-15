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

#include "lwmp.h"

LWMP::LWMP(QWidget *parent) : QWidget(parent), m_mpMediaPlayer(this) {

	qApp->addLibraryPath("/platforms");

	srand(time(NULL));

	ui.setupUi(this);

	// thumbnail buttons - not working right now
	/*
	// create thumbnail toolbar and assign handle
	m_ttbThumbnailToolbar = new QWinThumbnailToolBar(this);
	m_ttbThumbnailToolbar->setWindow(this->windowHandle());

	// create thumbnail tool buttons
	m_ttbtnNext = new QWinThumbnailToolButton(m_ttbThumbnailToolbar);
	m_ttbtnPause = new QWinThumbnailToolButton(m_ttbThumbnailToolbar);
	m_ttbtnPrevious = new QWinThumbnailToolButton(m_ttbThumbnailToolbar);

	// set tooltip and icon
	m_ttbtnNext->setToolTip("NEXT");
	m_ttbtnNext->setIcon(QIcon("next.ico"));
	m_ttbtnPause->setToolTip("PAUSE");
	m_ttbtnPause->setIcon(QIcon("playpause.png"));
	m_ttbtnPrevious->setToolTip("PREV");
	m_ttbtnPrevious->setIcon(QIcon("prev.ico"));

	// add to thumbnail toolbar
	m_ttbThumbnailToolbar->addButton(m_ttbtnPrevious);
	m_ttbThumbnailToolbar->addButton(m_ttbtnPause);
	m_ttbThumbnailToolbar->addButton(m_ttbtnNext);
	*/

	// assinging layout because the Qt designer does not
	this->setLayout(ui.gridLayout);

#ifdef USE_SDL_MIXER

	// init SDL_MIX
	int inited = Mix_Init(MIX_ALL);		

	if(flag_checker(inited, MIX_INIT_MP3))
		ui.m_lwInitialised->addItem(stringyfy(MP3));

	if(flag_checker(inited, MIX_INIT_FLAC))
		ui.m_lwInitialised->addItem(stringyfy(FLAC));

	if(flag_checker(inited, MIX_INIT_FLUIDSYNTH))
		ui.m_lwInitialised->addItem(stringyfy(FLUIDSYNTH));
	
	if(flag_checker(inited, MIX_INIT_MOD))
		ui.m_lwInitialised->addItem(stringyfy(MOD));

	if(flag_checker(inited, MIX_INIT_OGG))
		ui.m_lwInitialised->addItem(stringyfy(OGG));

	// open audio channels
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

#endif // USE_SDL_MIXER

	ui.m_cbFolderList->addItem("recently used");

	QFile f;
	f.setFileName("usedlocations");
	
	if(f.open(QFile::ReadOnly)) {
		QString buffer = f.readAll();
		auto arr = buffer.split('\r');

		for(int i = 0; i < arr.count() - 1; i++) {
			if(!arr.isEmpty())
				ui.m_cbFolderList->addItem(arr[i]);
		}
	}

#pragma region event connections
	
	this->connect(ui.m_btnSelectFolder, &QPushButton::clicked, this, &LWMP::select_dictionary);

	this->connect(ui.m_lwTitleList, &QListWidget::itemDoubleClicked, this, &LWMP::set_title);

	this->connect(ui.m_hsVolume, &QSlider::valueChanged, this, &LWMP::change_volume);

	this->connect(ui.m_btnStartStopResume, &QPushButton::clicked, this, &LWMP::play);

	this->connect(ui.m_btnNext, &QPushButton::clicked, this, &LWMP::next_title);

	this->connect(ui.m_btnPrevious, &QPushButton::clicked, this, &LWMP::previous_title);

	this->connect(ui.m_cbFolderList, &QComboBox::currentTextChanged, this, &LWMP::update_titlelist);

	this->connect(&this->m_mpMediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &LWMP::media_state_changed_event);

	// thumbnail connections
	/*
	this->connect(m_ttbtnPause, &QWinThumbnailToolButton::clicked, this, &LWMP::play);

	this->connect(m_ttbtnNext, &QWinThumbnailToolButton::clicked, this, &LWMP::next_title);

	this->connect(m_ttbtnPrevious, &QWinThumbnailToolButton::clicked, this, &LWMP::previous_title);
	*/

#ifdef USE_SDL_MIXER

	// SDL connections
	Mix_HookMusicFinished(&music_finished);

#endif // USE_SDL_MIXER 

#pragma endregion
}

LWMP::~LWMP() {

	std::fstream f;

	f.open("usedlocations", std::ios::out);

	// start at 1 to skip first item with is the recently used entry
	for(size_t i = 1; i < ui.m_cbFolderList->count(); i++) {
		f << ui.m_cbFolderList->itemText(i).toStdString() << '\r';
	}

	f.close();

	/*
	delete m_ttbThumbnailToolbar;
	delete m_ttbtnNext;
	delete m_ttbtnPause;
	delete m_ttbtnPrevious;*/

#ifdef USE_SDL_MIXER

	delete m_mixAudio;

#endif // USE_SDL_MIXER
}

void LWMP::update_titlelist() {

	m_qsCurrentDir = ui.m_cbFolderList->currentText();

	get_all_files_in_location(m_pTitles, m_qsCurrentDir.toStdString());

#pragma omp parallel for
	for(int i = 0; i < m_pTitles.size(); i++) {
		ui.m_lwTitleList->addItem(QString::fromStdString(m_pTitles[i]));
	}
}

void LWMP::set_title() {

#ifdef USE_SDL_MIXER

	// buffer var because QString.toStdString().c_str() does not work properly for some reason
	std::string title_path = ui.m_lwTitleList->currentItem()->text().toStdString();

	// free current audio-stream and set it to null
	Mix_FreeMusic(m_mixAudio);
	m_mixAudio = 0;

	m_mixAudio = Mix_LoadMUS(title_path.c_str());

	if(!m_mixAudio) {
		this->next_title();
	}
	else {
		if(Mix_PlayMusic(this->m_mixAudio, 1) == -1)
			QMessageBox::critical(this, "ERROR", Mix_GetError());
	}

#else

	if(this->m_mpMediaPlayer.state() == QMediaPlayer::State::PlayingState)
		this->m_mpMediaPlayer.stop();

	this->m_mpMediaPlayer.setMedia(QUrl::fromLocalFile(ui.m_lwTitleList->currentItem()->text()));
	this->m_mpMediaPlayer.play();

#endif // USE_SDL_MIXER
}

void LWMP::select_dictionary() {

	ui.m_cbFolderList->addItem(QFileDialog::getExistingDirectory(this, "Open Directory"));
	ui.m_cbFolderList->setCurrentIndex(ui.m_cbFolderList->count() - 1);

	this->update_titlelist();
}

void LWMP::change_volume() {

#ifdef USE_SDL_MIXER

	Mix_VolumeMusic(ui.m_hsVolume->value());

#else

	this->m_mpMediaPlayer.setVolume(ui.m_hsVolume->value());

#endif // USE_SDL_MIXER
	ui.m_hsVolume->setToolTip(QString("Volume: ") + std::to_string(ui.m_hsVolume->value()).c_str());
	ui.m_hsVolume->setToolTipDuration(3000);
}

void LWMP::media_state_changed_event(QMediaPlayer::MediaStatus newState) {

	if(newState == QMediaPlayer::MediaStatus::EndOfMedia)
		this->next_title();
}

void LWMP::play() {

#ifdef USE_SDL_MIXER

	if(Mix_PausedMusic())
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();

#else

	if(this->m_mpMediaPlayer.state() == QMediaPlayer::State::PlayingState)
		this->m_mpMediaPlayer.pause();
	else
		this->m_mpMediaPlayer.play();

#endif // USE_SDL_MIXER
}

void LWMP::previous_title() {
	ui.m_lwTitleList->setCurrentRow(ui.m_lwTitleList->currentRow() - 1);
	this->set_title();
}

void LWMP::next_title() {
	if(!ui.m_cbShuffle->isChecked()) {
		ui.m_lwTitleList->setCurrentRow(ui.m_lwTitleList->currentRow() + 1);
	}
	else {		
		ui.m_lwTitleList->setCurrentRow(rand() % ui.m_lwTitleList->count());
	}

	this->set_title();
}
