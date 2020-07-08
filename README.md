# OBS TestPlugin

## Introduction

I'm developing a plugin for OBS and having trouble getting timer events or QTimer::timeout signals.
This is a very simple test plugin that I believe demonstrates the problem, hoping someone can help me figure out what I'm doing wrong.
This plugin has been built using the boilerplate plugintemplate project provided at: https://github.com/obsproject/obs-plugintemplate


## Building

Clone the repo to a folder parallel to your OBS source folder.
After cloning the repo, from that folder:

mkdir build
cd build

cmake .. \
    -DQTDIR=/usr/local/opt/qt \
    -DLIBOBS_INCLUDE_DIR="../../obs-studio/libobs" \
    -DLIBOBS_LIB="../../obs-studio/build/libobs/libobs.dylib" \
    -DOBS_FRONTEND_LIB="$(pwd)/../../obs-studio/build/UI/obs-frontend-api/libobs-frontend-api.dylib" \
    -DCMAKE_INSTALL_PREFIX="/usr" \
&& make -j4

After succesfully compiling, copy/move the resultant obs-testplugin.so to your OBS' Plugins folder and launch OBS.