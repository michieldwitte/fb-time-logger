/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** MyRosterLogger.h
** Description: Header for MyRosterLogger.cpp
** Date: 25/07/2012
**
** Author: Michiel De Witte
** -------------------------------------------------------------------------*/

#include "gloox/client.h"
#include "gloox/connectionlistener.h"
#include "gloox/rostermanager.h"
#include "gloox/presence.h"
#include <time.h>
#include <fstream>
#include <stdio.h>
#include <locale.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <string.h>

using namespace gloox;

#ifndef MYROSTERLOGGER
#define MYROSTERLOGGER

class MyRosterLogger : public RosterListener
{
public:
	MyRosterLogger(Client* client, std::ofstream *file, bool console, bool logging);
	virtual ~MyRosterLogger();

	void handleLogin(const RosterItem& item);
	void handleLogout(const RosterItem& item);
    void handleError(const RosterItem& item);
    void log(std::string state, const RosterItem& item);

	virtual void handleRosterPresence( const RosterItem& item, const std::string& /*resource*/, Presence::PresenceType presence, const std::string& /*msg*/ );

	virtual void handleItemAdded( const JID& /*jid*/ );
	virtual void handleItemUnsubscribed( const JID& /*jid*/ );
	virtual void handleItemSubscribed( const JID& /*jid*/ );
	virtual void handleItemRemoved( const JID& /*jid*/ );
	virtual void handleItemUpdated( const JID& /*jid*/ );
	virtual void handleRoster( const Roster& /*roster*/ );
	virtual void handleRosterError( const IQ& /*iq*/ );
	virtual void handleSelfPresence( const RosterItem& /*item*/, const std::string& /*resource*/, Presence::PresenceType /*presence*/, const std::string& /*msg*/ );
	virtual bool handleUnsubscriptionRequest( const JID& /*jid*/, const std::string& /*msg*/ );
	virtual void handleNonrosterPresence( const Presence& /*presence*/ );
	virtual bool handleSubscriptionRequest( const JID& jid, const std::string& /*msg*/ );

private:
	Client *j;
	bool console;
	bool logging;
	std::ofstream* file;
};
#endif
