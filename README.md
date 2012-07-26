###there is an issue, on linux the cpu-usage is abnormally high (fix is underneath), windows does not have this problem

###to run, install gloox library:
debian/ubuntu/mint/... : sudo apt-get install gloox
arch: sudo pacman -S gloox

###compile
g++ *.cpp -lgloox -o fb-time-logger

###run!
./fb-time-logger

to find your facebook username click here:
https://www.facebook.com/username

###linux cpu-usage fix:
get the gloox code from http://camaya.net/gloox/download
and extract it,
go into the src folder and edit the connectiontcpbase.cpp like here
http://camaya.net/glooxlist/dev/msg01191.html
just change the recv(10) to recv(-1)
then compile and install the gloox library and try if you can compile

if not, you can try to compile and install gloox without gnutls:
./configure --without-gnutls --without-examples --without-tests
make
sudo make install

then try to compile the fb-time-logger

if it still doesnt work
backup
libgloox.a  libgloox.so  libgloox.so.8  libgloox.so.8.0.0
from /usr/local/lib

uninstall gloox(your own compiled version):
sudo make uninstall
make clean

install gloox the normal way (pacman -S gloox)
and copy the backupped files to /usr/lib

####note this fix is only tested on arch, the locations may vary upon distro.
