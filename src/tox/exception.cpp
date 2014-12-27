#include <sstream>
#include "exception.h"

ToxException::ToxException()
    : mFunctionName(std::string()), mMessage(std::string())
{
}

ToxException::ToxException(const std::string &msg)
    : mFunctionName(std::string()), mMessage(msg)
{
}

ToxException::ToxException(const std::string &fname, const std::string &msg)
    : mFunctionName(fname), mMessage(msg)
{
}

ToxException::ToxException(const char *msg)
    : mFunctionName(std::string()), mMessage(std::string(msg))
{
}

ToxException::ToxException(const char *fname, const char *msg)
    : mFunctionName(std::string(fname)), mMessage(std::string(msg))
{
}

const std::string ToxException::getFunctionName() const
{
    return mFunctionName;
}

std::string ToxException::getMessage() const
{
    return mMessage;
}

const char * ToxException::what() const noexcept
{
    if(!mMessage.empty())
    {
        return mMessage.c_str();
    }
    else
    {
        return "Tox exception occurred";
    }
}

ToxNullHandleException::ToxNullHandleException()
    : ToxException("Null handle")
{
}

ToxReturnException::ToxReturnException(const std::string &fname, int result, int expected)
    : ToxException(fname, std::string()), mExpected(expected), mResult(result)
{
    std::ostringstream strm;
    strm << "[" << fname << "] Unexpected return value (" << result << " instead of " << expected << ")";
    mMessage.assign(strm.str());
}

int ToxReturnException::getExpected() const
{
    return mExpected;
}

int ToxReturnException::getResult() const
{
    return mResult;
}

ToxNonZeroReturnException::ToxNonZeroReturnException(const std::string &fname, int result)
    : ToxReturnException(fname, result, 0)
{
    std::ostringstream strm;
    if(!fname.empty()) strm << "[" << fname << "] ";
    strm << "Expected 0 as return value (" << result << ")";
    mMessage.assign(strm.str());
}

ToxNegativeReturnException::ToxNegativeReturnException(const std::string &fname, int result)
    : ToxReturnException(fname, result, 0)
{
    std::ostringstream strm;
    if(!fname.empty()) strm << "[" << fname << "] ";
    strm << "Expected non-negative return value (" << result << ")";
    mMessage.assign(strm.str());
}
