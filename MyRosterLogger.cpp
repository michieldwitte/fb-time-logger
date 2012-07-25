/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** MyRosterLogger.cpp
** Description: A Roster Logger which will output the login/logout time to the console and/or a file
** Date: 25/07/2012
**
** Author: Michiel De Witte
** -------------------------------------------------------------------------*/

#include "MyRosterLogger.h"

using namespace gloox;

MyRosterLogger::MyRosterLogger(Client *client, std::ofstream *file, bool console, bool logging)
{
    j = client;
    this->file = file;
    this->console = console;
    this->logging = logging;
}

MyRosterLogger::~MyRosterLogger() {}

void MyRosterLogger::handleRosterPresence( const RosterItem& item, const std::string& /*resource*/, Presence::PresenceType presence, const std::string& /*msg*/ )
{
	if (presence == 0){
	    handleLogin(item);
	} else if (presence == 5){
	    handleLogout(item);
	} else {
	    handleError(item);
	}
}

void MyRosterLogger::handleLogin(const RosterItem& item)
{
    //ruimte voor eventuele uitbreiding
    log("Login", item);
}

void MyRosterLogger::handleLogout(const RosterItem& item)
{
    //ruimte voor eventuele uitbreiding
    log("Logout", item);
}
void MyRosterLogger::handleError(const RosterItem& item)
{
    //ruimte voor eventuele uitbreiding
    log("Error", item);
}

void MyRosterLogger::log(std::string state, const RosterItem& item)
{
    struct tm *current;         //struct en time_t mss als klassevariabelen --> performantie ?
    time_t now;
    time(&now);
    current = localtime(&now);

    if (this->logging){
        *(file) << item.name().c_str() << "\t\t|\t" << current->tm_mday << "/" << current->tm_mon << "/" << current->tm_year << "\t|\t" << current->tm_hour << ":" << current->tm_min << ":" << current->tm_sec << "\t|\t"<< state <<std::endl;
    }
    if (this->console){
        std::cout << item.name().c_str() << "\t\t|\t" << current->tm_mday << "/" << current->tm_mon << "/" << current->tm_year << "\t|\t" << current->tm_hour << ":" << current->tm_min << ":" << current->tm_sec << "\t|\t"<< state <<std::endl;
    }
}

bool MyRosterLogger::handleSubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
{
	StringList groups;
	JID id( jid );
	j->rosterManager()->subscribe( id, "", groups, "" );
	return true;
}


bool MyRosterLogger::handleUnsubscriptionRequest( const JID& /*jid*/, const std::string& /*msg*/ )
{
    return true;
}

void MyRosterLogger::handleSelfPresence( const RosterItem& /*item*/, const std::string& /*resource*/, Presence::PresenceType /*presence*/, const std::string& /*msg*/ )
{
}

void MyRosterLogger::handleNonrosterPresence( const Presence& /*presence*/ )
{
}

void MyRosterLogger::handleItemAdded( const JID& /*jid*/ )
{
}

void MyRosterLogger::handleItemUnsubscribed( const JID& /*jid*/ )
{
}

void MyRosterLogger::handleItemSubscribed( const JID& /*jid*/ )
{
}

void MyRosterLogger::handleItemRemoved( const JID& /*jid*/ )
{
}

void MyRosterLogger::handleItemUpdated( const JID& /*jid*/ )
{
}

void MyRosterLogger::handleRoster( const Roster& /*roster*/ )
{
}

void MyRosterLogger::handleRosterError( const IQ& /*iq*/ )
{
}
