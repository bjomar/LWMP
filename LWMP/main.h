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

// SDL
//#include <SDL.h>
#include <SDL_mixer.h>

// Qt5.9
#include <QtWinExtras\qwinthumbnailtoolbar.h>
#include <QtWinExtras\qwinthumbnailtoolbutton.h>
#include <qapplication.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <qmediaplayer.h>
#include <qmediaplaylist.h>

// std
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

#define stringyfy(x) #x
#define MIX_ALL MIX_INIT_FLAC | MIX_INIT_FLUIDSYNTH | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG

using paths = std::vector<std::string>;
using Qpaths = std::vector<QString>;
namespace fs = std::experimental::filesystem;

int main(int argc, char *argv[]);

// hook function for Mix_HookMusicFinished
// will trigger LWMP::next_title()
void music_finished();

// adds all paths to files in the given path (must be a directory)
// also adds files in subfolders
void get_all_files_in_location(paths& v, std::string path);

// for debugging purpose
bool flag_checker(int, int);