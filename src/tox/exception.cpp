#include <sstream>
#include "exception.h"

/**
 * Construct an exception related to Tox.
 */
ToxException::ToxException()
    : mFunctionName(std::string()), mMessage(std::string())
{
}

/**
 * Construct an exception related to Tox with a message.
 * @param msg Message
 */
ToxException::ToxException(const std::string &msg)
    : mFunctionName(std::string()), mMessage(msg)
{
}

/**
 * Construct an exception related to Tox and a libtoxcore function
 * with a message.
 * @param fname Function name
 * @param msg Message
 */
ToxException::ToxException(const std::string &fname, const std::string &msg)
    : mFunctionName(fname), mMessage(msg)
{
}

/**
 * Construct an exception related to Tox with a message.
 * @param msg Message (null-terminated)
 */
ToxException::ToxException(const char *msg)
    : mFunctionName(std::string()), mMessage(std::string(msg))
{
}

/**
 * Construct an exception related to Tox and a libtoxcore function
 * with a message.
 * @param fname Function name (null-terminated)
 * @param msg Message (null-terminated)
 */
ToxException::ToxException(const char *fname, const char *msg)
    : mFunctionName(std::string(fname)), mMessage(std::string(msg))
{
}

/**
 * Get the function name this exception is related to. May be empty.
 * @return Function name
 */
const std::string ToxException::getFunctionName() const
{
    return mFunctionName;
}

/**
 * Get the message passed to this exception. May be empty.
 * @return Message
 */
std::string ToxException::getMessage() const
{
    return mMessage;
}

/**
 * Get a string representation of this exception.
 * @return String representation. If no message,
 *         will return a default message.
 */
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

/**
 * Exception thrown if a tox operation is attempted without
 * a Tox handle.
 */
ToxNullHandleException::ToxNullHandleException()
    : ToxException("Null handle")
{
}

/**
 * Construct an exception relating to the return value of a libtoxcore
 * function.
 * @param fname Function name
 * @param result Actual return value
 * @param expected Expected return value
 */
ToxReturnException::ToxReturnException(const std::string &fname, int result, int expected)
    : ToxException(fname, std::string()), mExpected(expected), mResult(result)
{
    std::ostringstream strm;
    strm << "[" << fname << "] Unexpected return value (" << result << " instead of " << expected << ")";
    mMessage.assign(strm.str());
}

/**
 * Get the expected return value.
 * @return expected return value
 */
int ToxReturnException::getExpected() const
{
    return mExpected;
}

/**
 * Get the actual return value.
 * @return actual return value
 */
int ToxReturnException::getResult() const
{
    return mResult;
}

/**
 * Construct an exception relating to a libtoxcore function that
 * returned an unexpected non-zero value.
 * @param fname Function name
 * @param result Actual return value
 */
ToxNonZeroReturnException::ToxNonZeroReturnException(const std::string &fname, int result)
    : ToxReturnException(fname, result, 0)
{
    std::ostringstream strm;
    if(!fname.empty()) strm << "[" << fname << "] ";
    strm << "Expected 0 as return value (" << result << ")";
    mMessage.assign(strm.str());
}

/**
 * Construct an exception relating to a libtoxcore function that
 * returned an unexpected negative value.
 * @param fname Function name
 * @param result Actual return value
 */
ToxNegativeReturnException::ToxNegativeReturnException(const std::string &fname, int result)
    : ToxReturnException(fname, result, 0)
{
    std::ostringstream strm;
    if(!fname.empty()) strm << "[" << fname << "] ";
    strm << "Expected non-negative return value (" << result << ")";
    mMessage.assign(strm.str());
}
