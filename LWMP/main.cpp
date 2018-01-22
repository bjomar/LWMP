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

// some cheating for the music_finished hook function
// i'm really sorry.
LWMP* music_player;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	qApp->addLibraryPath("/platforms");

	LWMP w;

	music_player = &w;

	w.show();

	return a.exec();
}

void music_finished() {
	music_player->next_title();
}

void get_all_files_in_location(paths& v, std::string path) {

	for(auto p : fs::directory_iterator(path)) {
		if(fs::is_directory(p.path()))
			get_all_files_in_location(v, p.path().string());
		else
			v.push_back(p.path().string());
	}
}

bool flag_checker(int all_flags, int flag_to_check) {
	return (all_flags & flag_to_check) == flag_to_check;
}
