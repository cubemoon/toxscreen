#include <QUuid>
#include "password_generator.h"

PasswordGenerator::PasswordGenerator()
{
}

QString PasswordGenerator::generate(uint charCount) const
{
    return generate(TOXSCREEN_PASSWORD_DEFAULT_CHARSET, charCount);
}

QString PasswordGenerator::generate(const QString &charset, uint charCount) const
{
    QString result = "";

    // This could be more efficient..
    for(uint i = 0; i < 16; i++)
    {
        uint r = randomUint();
        int index = (r % charset.length());
        QChar c = charset.at(index);
        result.append(c);
    }

    return result;
}

QString PasswordGenerator::generate(const QPair<uint, uint> charCountRange) const
{
    return generate(TOXSCREEN_PASSWORD_DEFAULT_CHARSET, charCountRange);
}

QString PasswordGenerator::generate(const QString &charset, const QPair<uint, uint> charCountRange) const
{
    return generate(charset, randomCharCount(charCountRange));
}

uint PasswordGenerator::randomCharCount(const QPair<uint, uint> range) const
{
    if(range.first == range.second)
    {
        return range.first;
    }

    uint ceiling, floor;
    if(range.first >= range.second)
    {
        ceiling = range.first;
        floor = range.second;
    }
    else
    {
        ceiling = range.second;
        floor = range.first;
    }

    uint diff = ceiling - floor;
    return (ceiling + randomUint()) % diff;
}

uint PasswordGenerator::randomUint() const
{
    QByteArray bytes = QUuid::createUuid().toByteArray();
    return ((uint*)bytes.data())[0];
}
