###there is an issue, on linux the cpu-usage is abnormally high (fix is underneath), windows does not have this problem

###to run, install gloox library:<br>
debian/ubuntu/mint/... : sudo apt-get install gloox<br>
arch: sudo pacman -S gloox<br>

###compile<br>
g++ *.cpp -lgloox -o fb-time-logger<br>

###run!<br>
./fb-time-logger<br>

to find your facebook username click here:<br>
https://www.facebook.com/username<br>

###linux cpu-usage fix:<br>
#####Dirty fix: <br>
get the gloox code from http://camaya.net/gloox/download and extract it,<br>
go into the src folder and edit the connectiontcpbase.cpp like here<br>
http://camaya.net/glooxlist/dev/msg01191.html<br>
just change the recv(10) to recv(-1)<br>
./configure --without-gnutls --without-examples --without-tests<br>
copy the src folder to the fb-time-logger folder<br>
edit the MyRosterLogger.h and change "gloox/\*.h" to "src/\*.h"<br>
copy the config.h in the src directory to config.h.unix in the src directory<br>
g++ -o fbl \*.cpp src/\*.cpp<br>
And you're done !

#####Less dirty fix?: <br>
get the gloox code from http://camaya.net/gloox/download and extract it,<br>
go into the src folder and edit the connectiontcpbase.cpp like here<br>
http://camaya.net/glooxlist/dev/msg01191.html<br>
just change the recv(10) to recv(-1)<br>
then compile and install the gloox library and try if you can compile<br>

if not, you can try to compile and install gloox without gnutls:<br>
./configure --without-gnutls --without-examples --without-tests<br>
make<br>
sudo make install<br>

then try to compile the fb-time-logger<br>

if it still doesn't work, backup:<br>
libgloox.a  libgloox.so  libgloox.so.8  libgloox.so.8.0.0<br>
from /usr/local/lib<br>

uninstall gloox(your own compiled version):<br>
sudo make uninstall<br>
make clean<br>

install gloox the normal way (pacman -S gloox)<br>
and copy the backupped files to /usr/lib<br>

####note this fix is only tested on arch, the locations may vary upon distro.<br>
