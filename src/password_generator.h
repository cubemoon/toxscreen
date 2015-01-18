#ifndef TOXSCREEN_PASSWORD_GENERATOR_H
#define TOXSCREEN_PASSWORD_GENERATOR_H

#include <QPair>
#include <QString>

#define TOXSCREEN_PASSWORD_DEFAULT_CHARSET "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

class PasswordGenerator
{
public:
    PasswordGenerator();
    QString generate(uint charCount = 16) const;
    QString generate(const QString &charset, uint charCount = 16) const;
    QString generate(const QPair<uint, uint> charCountRange) const;
    QString generate(const QString &charset, const QPair<uint, uint> charCountRange) const;
protected:
    uint randomCharCount(const QPair<uint, uint> range) const;
    uint randomUint() const;
};

#endif // TOXSCREEN_PASSWORD_GENERATOR_H
