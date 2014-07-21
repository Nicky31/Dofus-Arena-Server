SOURCES += \
    main.cpp \
    core/Network/Server/TCPServer.cpp \
    core/Network/Server/SocketHandler.cpp \
    game/Com/Session/ClientSession.cpp \
    game/Com/Opcodes/OpcodesMgr.cpp \
    core/Network/Packet/DAPacket.cpp \
    core/Configurations/Config.cpp \
    game/Configs/AuthConfig.cpp \
    core/Logs/Log.cpp \
    game/World/World.cpp \
    game/Com/Handlers/LoginHandler.cpp

HEADERS += \
    core/Network/Server/TCPServer.h \
    core/Network/Server/SocketHandler.h \
    core/Utils/Common.h \
    game/Com/Session/ClientSession.h \
    game/Com/Opcodes/OpcodesMgr.h \
    core/Network/Packet/DAPacket.h \
    core/Configurations/Config.h \
    game/Configs/AuthConfig.h \
    game/Configs/Configs.h \
    core/Logs/Log.h \
    game/World/World.h

QT += core network sql
QT -= gui

INCLUDEPATH +=  . ../core ../game
