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
    game/Com/Handlers/LoginHandler.cpp \
    core/Databases/DatabaseConnection.cpp \
    game/DAO/DAOFactory.cpp \
    game/Com/Handlers/CoachHandler.cpp \
    game/Com/Handlers/WorldHandler.cpp

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
    game/World/World.h \
    game/World/Entities/Account.h \
    game/World/Managers/Account/AccountMgr.h \
    core/Utils/Observer.h \
    core/Databases/DatabaseConnection.h \
    game/DAO/AccountDAO.h \
    game/DAO/DAOFactory.h \
    game/World/Entities/Coach.h \
    game/DAO/CoachDAO.h

QT += core network sql
QT -= gui

INCLUDEPATH +=  . ../core ../game
