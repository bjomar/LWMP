/*
Copyright(c) 2017 Bj�rn Marx
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
//#include <SDL.h> // <- not needed
#include <SDL_mixer.h>

// Qt5.9
#include <qapplication.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qfile.h>

// std
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

#define MIX_ALL MIX_INIT_FLAC | MIX_INIT_FLUIDSYNTH | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG

// std::vector<std::string>
using paths = std::vector<std::string>;
namespace fs = std::experimental::filesystem;

int main(int argc, char *argv[]);

// hook funktion for Mix_HookMusicFinished
// will trigger LWMP::next_title()
void music_finished();

void get_all_files_in_location(paths& v, std::string path);