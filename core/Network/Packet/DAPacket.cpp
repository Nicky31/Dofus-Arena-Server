#include "DAPacket.h"

DAPacket::DAPacket(quint16 opcode, QByteArray datas) : m_opcode(opcode), m_datas(datas), m_stream(&m_datas, QIODevice::WriteOnly)
{
}

QByteArray DAPacket::GetDatas(bool header)
{
    QByteArray datas(m_datas);
    if(header)
    {
        datas.insert(0, GetHeader());
    }

    return datas;
}

QByteArray DAPacket::GetHeader()
{
    QByteArray header;
    quint16 size = m_datas.length() + 4;
    char* charSize = (char*)&size;
    char* charOpcode = (char*)&m_opcode;
    header.append(*(charSize + 1)).append(*charSize).append(*(charOpcode +1)).append(*charOpcode);

    return header;
}

quint16 DAPacket::GetOpcode() const
{
    return m_opcode;
}


