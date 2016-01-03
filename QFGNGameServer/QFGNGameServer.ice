#include <QFGNServerClientProto.ice>

module QFGN
{
	interface GameServer
    {
		int doTransmit(QFGNServerClientProto::TPackage stPackage);
        int doPrinter(string sInput);
    };
};
