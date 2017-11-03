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

LWMP::LWMP(QWidget *parent) : QWidget(parent) {

	qApp->addLibraryPath("/platforms");

	ui.setupUi(this);

	// assinging layout because the Qt designer does not
	this->setLayout(ui.gridLayout);

	// init SDL_MIX
	Mix_Init(MIX_ALL);

	// open audio channels
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	ui.m_cbFolderList->addItem("recently used");

	QFile f;
	f.setFileName("usedlocations");
	
	if(f.open(QFile::ReadOnly)) {
		QString buffer = f.readAll();
		auto arr = buffer.split('\r');

		for(int i = 0; i < arr.count() - 1; i++) {
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

	Mix_HookMusicFinished(&music_finished);

#pragma endregion
}

LWMP::~LWMP() {

	std::fstream f;

	f.open("usedlocations", std::ios::out);

	// start at 1 to skip first item
	for(size_t i = 1; i < ui.m_cbFolderList->count(); i++) {
		f << ui.m_cbFolderList->itemText(i).toStdString() << '\r';
	}

	f.close();

	delete m_mixAudio;
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
	// buffer var because QString.toStdString().c_str() does not work properly for some reason
	std::string title_path = ui.m_lwTitleList->currentItem()->text().toStdString();

	//this->setWindowTitle(title_path.c_str());

	m_mixAudio = Mix_LoadMUS(title_path.c_str());

	if(!m_mixAudio)
		QMessageBox::critical(this, "ERROR", Mix_GetError());

	if(Mix_PlayMusic(this->m_mixAudio, 1) == -1)
		QMessageBox::critical(this, "ERROR", Mix_GetError());
}

void LWMP::select_dictionary() {

	ui.m_cbFolderList->addItem(QFileDialog::getExistingDirectory(this, "Open Directory"));
	ui.m_cbFolderList->setCurrentIndex(ui.m_cbFolderList->count() - 1);

	this->update_titlelist();
}

void LWMP::change_volume() {
	Mix_VolumeMusic(ui.m_hsVolume->value());

	ui.m_hsVolume->setToolTip(QString("Volume: ") + std::to_string(ui.m_hsVolume->value()).c_str());
	ui.m_hsVolume->setToolTipDuration(1000);
}

void LWMP::play() {
	if(Mix_PausedMusic())
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}

void LWMP::previous_title() {
	ui.m_lwTitleList->setCurrentRow(ui.m_lwTitleList->currentRow() - 1);
	this->set_title();
}

void LWMP::next_title() {
	if(!ui.m_cbShuffle->isChecked())
		ui.m_lwTitleList->setCurrentRow(ui.m_lwTitleList->currentRow() + 1);
	else {
		srand(time(NULL));
		
		ui.m_lwTitleList->setCurrentRow(rand() % ui.m_lwTitleList->count());
	}

	this->set_title();
}
