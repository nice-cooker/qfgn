
#-----------------------------------------------------------------------

APP       := QFGN 
TARGET    := GameSvr
MFLAGS    := 
DFLAGS    :=
#CFLAGS    := -D ENABLE_TEST
CONFIG    := 
STRIP_FLAG:= N
I2CPP_FLAG:= -I . -I ../Common 

INCLUDE   += -I/opt/NCook/Util/include -I. -I/opt/Ice-3.7.0/include -I../Common
LIB       += -L/opt/NCook/Util/lib -lutil -L/opt/mysql/lib -lmysqlclient -L/opt/Ice-3.7.0/lib64/ -lIce -lIceUtil

INCLUDE		+= -I./outlib/curl/include -I./outlib/jsoncpp/include -I./outlib/openssl/include -I./outlib/oauth/include -I./outlib/tools
LIB				+= -L./outlib/curl/lib -lcurl -L./outlib/openssl/lib -lssl -lcrypto -L./outlib/oauth/lib -loauth -L./outlib/jsoncpp/lib -ljson -lrt -ldl

#-----------------------------------------------------------------------
include /opt/Ice-3.7.0/makefile.nc

#-----------------------------------------------------------------------



   
