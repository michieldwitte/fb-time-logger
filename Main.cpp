/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Main.cpp
** Description: A basic facebook xmpp logger using the gloox library
** Date: 25/07/2012
**
** Help: run in utf-8 terminal if your friends username contains unicode characters
**
** Author: Michiel De Witte
** -------------------------------------------------------------------------*/

#include "MyRosterLogger.h"
#include <iostream>
#include <fstream>
#include <string.h>


using namespace gloox;

int main( int argc, char** argv )
{
    int logins=0, passwds=0, filenames=0;
    std::string login, password;
    char filename[50];
    bool logging = true, console = true;
    std::ofstream file;

  for(int i = 1;i<argc; i++){       //process arguments
      if (!strcmp ("-l",argv[i]) && argc != i+1){
        login = std::string(argv[i+1]);
        logins++;
      }
      if (!strcmp ("-p",argv[i]) && argc != i+1){
        password = std::string(argv[i+1]);
        passwds++;
      }
      if (!strcmp ("-s",argv[i]) || !strcmp ("--silent",argv[i])){
        console = false;
      }
      if (!strcmp ("-n",argv[i]) || !strcmp ("--nolog",argv[i])){
        logging = false;
      }
      if (!strcmp ("-f",argv[i])){
        if (logging){
            if (argc != i+1){
                strcpy(filename, argv[i+1]);
                filenames++;
            }
        } else {
            std::cout << "Cannot specify logfile name when using -n or --nolog" << std::endl;
            return 0;
        }
      }
      if (!strcmp ("-h",argv[i]) || !strcmp ("--help",argv[i])){
        std::cout << "List of possible commandline arguments:" << std::endl;

        std::cout << "-h OR --help\t\t: display help" << std::endl;
        std::cout << "-s OR --silent\t\t: no console output" << std::endl;
        std::cout << "-n OR --nolog\t\t: do not create or write to a logfile" << std::endl;
        std::cout << "-l \t[login name]\t: specify login name" << std::endl;
        std::cout << "-p \t[password]\t: specify password" << std::endl;
        std::cout << "-f \t[logfile name]\t: specify login name (default facebook.log)" << std::endl;
        std::cout << std::endl << "if username contains unicode characters run in utf-8 compatible terminal";
        return 0;
      }
  }

   if (logins > 1 || passwds > 1 || filenames > 1){
     std::cout << "Too much arguments" << std::endl;
     return 0;
   }

   if (logins == 0){    //get login if needed
     std::cout << "Insert login: ";
     std::cin >> login;
   }
   if (passwds == 0){   //get password if needed
   		#if defined(WIN32) && !defined(UNIX)
			std::cout << "Insert password: ";
			std::cin >> password;
		#elif defined(UNIX) && !defined(WIN32)
			password=getpass("Insert password: ");
			std::cout << std::endl;
		#else
			/* Error, both can't be defined or undefined same time */
			std::cout << "Warning: this may not work, ..." << std::endl;
			std::cout << "Insert password: ";
			std::cin >> password;
		#endif
   }
   if (filenames == 0 && logging){ //set filename (not used if log is disabled)
     std::cout << "Using facebook.log as logfile" << std::endl;
     strcpy (filename, "facebook.log");
   }
   if (logging){
     file.open(filename);
   }

	JID jid( login + "@chat.facebook.com" );
	Client client( jid, password,5222);
	MyRosterLogger rstr(&client, &file, console, logging);
    	client.rosterManager()->registerRosterListener( &rstr );
	client.connect();
	client.disconnect();
	file.close();

	return 0;
}
