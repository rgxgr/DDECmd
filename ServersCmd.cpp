////////////////////////////////////////////////////////////////////////////////
//! \file   ServersCmd.cpp
//! \brief  The ServersCmd class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ServersCmd.hpp"
#include <Core/tiostream.hpp>
#include <NCL/DDEClient.hpp>
#include <WCL/StrArray.hpp>
#include "CmdLineArgs.hpp"
#include <WCL/StringIO.hpp>
#include <NCL/DDEClientFactory.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The table of command specific command line switches.

static Core::CmdLineSwitch s_switches[] = 
{
	{ USAGE,	TXT("?"),	nullptr,		Core::CmdLineSwitch::ONCE,	Core::CmdLineSwitch::NONE,		nullptr,		TXT("Display the command syntax")	},
	{ USAGE,	nullptr,	TXT("help"),	Core::CmdLineSwitch::ONCE,	Core::CmdLineSwitch::NONE,		nullptr,		TXT("Display the command syntax")	},
};
static size_t s_switchCount = ARRAY_SIZE(s_switches);

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

ServersCmd::ServersCmd(int argc, tchar* argv[])
	: WCL::ConsoleCmd(s_switches, s_switches+s_switchCount, argc, argv, USAGE)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ServersCmd::~ServersCmd()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Get the description of the command.

const tchar* ServersCmd::getDescription()
{
	return TXT("List the running servers and their topics");
}

////////////////////////////////////////////////////////////////////////////////
//! Get the expected command usage.

const tchar* ServersCmd::getUsage()
{
	return TXT("USAGE: DDECmd servers");
}

////////////////////////////////////////////////////////////////////////////////
//! The implementation of the command.

int ServersCmd::doExecute(tostream& out, tostream& /*err*/)
{
	ASSERT(m_parser.getUnnamedArgs().at(0) == TXT("servers"));

	DDE::IDDEClientPtr client = DDE::DDEClientFactory::create();

	// Find the running servers.
	CStrArray servers, topics;

	client->QueryAll(servers, topics);

	// Display results.
	for (size_t i = 0, size = servers.Size(); i != size; ++i)
		out << servers[i] << TXT("|") << topics[i] << std::endl;

	return EXIT_SUCCESS;
}
