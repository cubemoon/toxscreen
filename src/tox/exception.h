#ifndef TOXSCREEN_TOX_EXCEPTION_H
#define TOXSCREEN_TOX_EXCEPTION_H

#include <exception>
#include <string>

class ToxException : public std::exception
{
public:
    ToxException();
    explicit ToxException(const std::string &msg);
    ToxException(const std::string &fname, const std::string &msg);
    explicit ToxException(const char *msg);
    ToxException(const char *fname, const char *msg);
    virtual const std::string getFunctionName() const;
    virtual std::string getMessage() const;
    virtual const char * what() const noexcept;
protected:
    const std::string mFunctionName;
    std::string mMessage;
};

class ToxNullHandleException : public ToxException
{
public:
    ToxNullHandleException();
};

class ToxReturnException : public ToxException
{
public:
    ToxReturnException(const std::string &fname, int result, int expected = 0);
    int getExpected() const;
    int getResult() const;
protected:
    int mExpected;
    int mResult;
};

class ToxNonZeroReturnException : public ToxReturnException
{
public:
    ToxNonZeroReturnException(const std::string &fname, int result);
};

class ToxNegativeReturnException : public ToxReturnException
{
public:
    ToxNegativeReturnException(const std::string &fname, int result);
};

#endif // TOXSCREEN_TOX_EXCEPTION_H
