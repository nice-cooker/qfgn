#ifndef __QFGNGameServerI_h__
#define __QFGNGameServerI_h__

#include <QFGNGameServer.h>

namespace QFGN
{

class GameServerI : virtual public GameServer
{
public:

    virtual ::Ice::Int doTransmit(const ::QFGNServerClientProto::TPackage&,
                                  const Ice::Current&);

    virtual ::Ice::Int doPrinter(const ::std::string&,
                                 const Ice::Current&);
};

}

#endif
