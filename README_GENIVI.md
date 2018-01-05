Navigation Open Source Project
==============================

This recipe for Navigation demo is intended to be built outside AGL.
The DBus based APIs used by this demo (see src/api folder) are aligned with the release Nostromo of GENIVI:
https://github.com/GENIVI/navigation/tree/73f74aadc03a1aeffb0937220dca803e8d7149b8/api

## How-to build
./autogen.sh
./configure --enable-standalone 
additional option:
--enable-verbose --> make with -DNAVI_TRACE_DEBUG to log runtime messages
NB: To test it under Ubuntu (with weston), please comment line 30 of src/glview_wayland.c to unuse IVI_SHELL)
make

cd src/hmi
mkdir build
cd build
cmake ../
(it also generates the HMI)
make 
make install
cd ../../../

## How-to generate the QML HMI style-sheet
The native HMI is gtk based, but it's also possible to connect to the GENIVI FSA HMI. First it's needed to generate it:
./src/hmi/prepare.sh -i ./src/hmi/gimp/genivi-theme/800x480/


## Usage

1. Please download the data from the following URL.
    http://agl.wismobi.com  - navi_data.tar.gz
2. Extract TAR file in any place
3. run

    LD_LIBRARY_PATH=/usr/local/lib:/usr/lib; export LD_LIBRARY_PATH

    NAVI_DATA_DIR=./navi_data/japan_TR9; export NAVI_DATA_DIR

    navi

## Unitary tests 

This code has been tested under Ubuntu 17.10
Under the test folder there are some test scripts in Python that allows to test the APIs. 

To launch the code:
NB: into the scripts, the database is supposed to be under $HOME
weston
./run_navi
Into another terminal (outside weston)
./test/test-map-viewer-control.py -l location_tokyo.xml
--> zoom in/out
./test/test-route-calculation.py -r route_tokyo.xml
--> route calculation
./test/test-guidance.py -r route_tokyo.xml
--> route calculation and guidance 

## Test with HMI (work in progress)
weston
./run_navi
./run_hmi

## Licence

GENIVI stuff is MPLV2 license.

GPS Navigation is dual licensed under the GNU General Public License (GPL) version 2 and a commercial license with Hitachi, Ltd.  You may adopt either the GPL version 2 or a commercial license at the discretion of yourself.
GPS Navigation is available under commercial licenses negotiated directly with Hitachi, Ltd.  If you wish to combine and distribute your proprietary software with GPS Navigation, you had better adopt a commercial license, otherwise, you may be required to distribute the entire source code of your proprietary software under GPL version 2, as the GPL version 2 is applied to all loadable GPS Navigation modules used in your software.
The full text of GPL version 2 is in the file COPYING distributed with this file.

If you have any questions on our licensing policy, please contact us.

 e-mail: gpsnavi-inquiry@itg.hitachi.co.jp

Hitachi, Ltd.

