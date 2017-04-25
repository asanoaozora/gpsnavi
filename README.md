Navigation Open Source Project
==============================

This recipe for Navigation demo is intended to be built either into Automotive Grade Linux (AGL) source code
(https://wiki.automotivelinux.org/agl-distro/source-code).
or outside (standalone configuration, see below).
The DBus based APIs used by this demo (see src/api folder) are aligned with the release Nostromo of GENIVI:
https://github.com/GENIVI/navigation/tree/73f74aadc03a1aeffb0937220dca803e8d7149b8/api

## How-to build
./configure [options]
available options:
--enable-standalone --> to test it outside AGL
--enable-verbose --> make with -DNAVI_TRACE_DEBUG to log runtime messages
NB: To test it under Ubuntu (with weston), please comment line 30 of src/glview_wayland.c to unuse IVI_SHELL)
make

## Usage

1. Please download the data from the following URL.
    http://agl.wismobi.com  - navi_data.tar.gz
2. Extract TAR file in any place
3. run

    LD_LIBRARY_PATH=/usr/local/lib:/usr/lib; export LD_LIBRARY_PATH

    NAVI_DATA_DIR=./navi_data/japan_TR9; export NAVI_DATA_DIR

    navi

## To test 

Except AGL, this code has been tested under Ubuntu 16.04 LTS.
Under the test folder there are some test scripts in Python that allows to test the APIs. 
(tested under Weston)
./test-map-viewer-control.py -l location_tokyo.xml
--> zoom in/out
./test-route-calculation.py -r route_tokyo.xml
--> route calculation
./test-guidance.py -r route_tokyo.xml
--> route calculation and guidance 

## Licence

GPS Navigation is dual licensed under the GNU General Public License (GPL) version 2 and a commercial license with Hitachi, Ltd.  You may adopt either the GPL version 2 or a commercial license at the discretion of yourself.
GPS Navigation is available under commercial licenses negotiated directly with Hitachi, Ltd.  If you wish to combine and distribute your proprietary software with GPS Navigation, you had better adopt a commercial license, otherwise, you may be required to distribute the entire source code of your proprietary software under GPL version 2, as the GPL version 2 is applied to all loadable GPS Navigation modules used in your software.
The full text of GPL version 2 is in the file COPYING distributed with this file.

If you have any questions on our licensing policy, please contact us.

 e-mail: gpsnavi-inquiry@itg.hitachi.co.jp

Hitachi, Ltd.

