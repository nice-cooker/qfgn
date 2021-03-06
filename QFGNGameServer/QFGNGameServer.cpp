// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.7.0
//
// <auto-generated>
//
// Generated from file `QFGNGameServer.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include <QFGNGameServer.h>
#include <IceUtil/PushDisableWarnings.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/Outgoing.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/BasicStream.h>
#include <IceUtil/Iterator.h>
#include <IceUtil/PopDisableWarnings.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 307
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

namespace
{

const ::std::string __QFGN__GameServer__doTransmit_name = "doTransmit";

const ::std::string __QFGN__GameServer__doPrinter_name = "doPrinter";

}
::IceProxy::Ice::Object* ::IceProxy::QFGN::upCast(::IceProxy::QFGN::GameServer* p) { return p; }

void
::IceProxy::QFGN::__read(::IceInternal::BasicStream* __is, ::IceInternal::ProxyHandle< ::IceProxy::QFGN::GameServer>& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::QFGN::GameServer;
        v->__copyFrom(proxy);
    }
}

::Ice::Int
IceProxy::QFGN::GameServer::doTransmit(const ::QFGNServerClientProto::TPackage& __p_stPackage, const ::Ice::Context* __ctx)
{
    __checkTwowayOnly(__QFGN__GameServer__doTransmit_name);
    ::IceInternal::Outgoing __og(this, __QFGN__GameServer__doTransmit_name, ::Ice::Normal, __ctx);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(__p_stPackage);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    if(!__og.invoke())
    {
        try
        {
            __og.throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
            throw __uue;
        }
    }
    ::Ice::Int __ret;
    ::IceInternal::BasicStream* __is = __og.startReadParams();
    __is->read(__ret);
    __og.endReadParams();
    return __ret;
}

::Ice::AsyncResultPtr
IceProxy::QFGN::GameServer::begin_doTransmit(const ::QFGNServerClientProto::TPackage& __p_stPackage, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__QFGN__GameServer__doTransmit_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __QFGN__GameServer__doTransmit_name, __del, __cookie);
    try
    {
        __result->prepare(__QFGN__GameServer__doTransmit_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->startWriteParams(::Ice::DefaultFormat);
        __os->write(__p_stPackage);
        __result->endWriteParams();
        __result->invoke();
    }
    catch(const ::Ice::Exception& __ex)
    {
        __result->abort(__ex);
    }
    return __result;
}

#ifdef ICE_CPP11

::Ice::AsyncResultPtr
IceProxy::QFGN::GameServer::__begin_doTransmit(const ::QFGNServerClientProto::TPackage& __p_stPackage, const ::Ice::Context* __ctx, const ::IceInternal::Function<void (::Ice::Int)>& __response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& __exception, const ::IceInternal::Function<void (bool)>& __sent)
{
    class Cpp11CB : public ::IceInternal::Cpp11FnCallbackNC
    {
    public:

        Cpp11CB(const ::std::function<void (::Ice::Int)>& responseFunc, const ::std::function<void (const ::Ice::Exception&)>& exceptionFunc, const ::std::function<void (bool)>& sentFunc) :
            ::IceInternal::Cpp11FnCallbackNC(exceptionFunc, sentFunc),
            _response(responseFunc)
        {
            CallbackBase::checkCallback(true, responseFunc || exceptionFunc != nullptr);
        }

        virtual void completed(const ::Ice::AsyncResultPtr& __result) const
        {
            ::QFGN::GameServerPrx __proxy = ::QFGN::GameServerPrx::uncheckedCast(__result->getProxy());
            ::Ice::Int __ret;
            try
            {
                __ret = __proxy->end_doTransmit(__result);
            }
            catch(const ::Ice::Exception& ex)
            {
                Cpp11FnCallbackNC::exception(__result, ex);
                return;
            }
            if(_response != nullptr)
            {
                _response(__ret);
            }
        }
    
    private:
        
        ::std::function<void (::Ice::Int)> _response;
    };
    return begin_doTransmit(__p_stPackage, __ctx, new Cpp11CB(__response, __exception, __sent));
}
#endif

::Ice::Int
IceProxy::QFGN::GameServer::end_doTransmit(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __QFGN__GameServer__doTransmit_name);
    ::Ice::Int __ret;
    if(!__result->__wait())
    {
        try
        {
            __result->__throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
        }
    }
    ::IceInternal::BasicStream* __is = __result->__startReadParams();
    __is->read(__ret);
    __result->__endReadParams();
    return __ret;
}

::Ice::Int
IceProxy::QFGN::GameServer::doPrinter(const ::std::string& __p_sInput, const ::Ice::Context* __ctx)
{
    __checkTwowayOnly(__QFGN__GameServer__doPrinter_name);
    ::IceInternal::Outgoing __og(this, __QFGN__GameServer__doPrinter_name, ::Ice::Normal, __ctx);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(__p_sInput);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    if(!__og.invoke())
    {
        try
        {
            __og.throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
            throw __uue;
        }
    }
    ::Ice::Int __ret;
    ::IceInternal::BasicStream* __is = __og.startReadParams();
    __is->read(__ret);
    __og.endReadParams();
    return __ret;
}

::Ice::AsyncResultPtr
IceProxy::QFGN::GameServer::begin_doPrinter(const ::std::string& __p_sInput, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__QFGN__GameServer__doPrinter_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __QFGN__GameServer__doPrinter_name, __del, __cookie);
    try
    {
        __result->prepare(__QFGN__GameServer__doPrinter_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->startWriteParams(::Ice::DefaultFormat);
        __os->write(__p_sInput);
        __result->endWriteParams();
        __result->invoke();
    }
    catch(const ::Ice::Exception& __ex)
    {
        __result->abort(__ex);
    }
    return __result;
}

#ifdef ICE_CPP11

::Ice::AsyncResultPtr
IceProxy::QFGN::GameServer::__begin_doPrinter(const ::std::string& __p_sInput, const ::Ice::Context* __ctx, const ::IceInternal::Function<void (::Ice::Int)>& __response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& __exception, const ::IceInternal::Function<void (bool)>& __sent)
{
    class Cpp11CB : public ::IceInternal::Cpp11FnCallbackNC
    {
    public:

        Cpp11CB(const ::std::function<void (::Ice::Int)>& responseFunc, const ::std::function<void (const ::Ice::Exception&)>& exceptionFunc, const ::std::function<void (bool)>& sentFunc) :
            ::IceInternal::Cpp11FnCallbackNC(exceptionFunc, sentFunc),
            _response(responseFunc)
        {
            CallbackBase::checkCallback(true, responseFunc || exceptionFunc != nullptr);
        }

        virtual void completed(const ::Ice::AsyncResultPtr& __result) const
        {
            ::QFGN::GameServerPrx __proxy = ::QFGN::GameServerPrx::uncheckedCast(__result->getProxy());
            ::Ice::Int __ret;
            try
            {
                __ret = __proxy->end_doPrinter(__result);
            }
            catch(const ::Ice::Exception& ex)
            {
                Cpp11FnCallbackNC::exception(__result, ex);
                return;
            }
            if(_response != nullptr)
            {
                _response(__ret);
            }
        }
    
    private:
        
        ::std::function<void (::Ice::Int)> _response;
    };
    return begin_doPrinter(__p_sInput, __ctx, new Cpp11CB(__response, __exception, __sent));
}
#endif

::Ice::Int
IceProxy::QFGN::GameServer::end_doPrinter(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __QFGN__GameServer__doPrinter_name);
    ::Ice::Int __ret;
    if(!__result->__wait())
    {
        try
        {
            __result->__throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
        }
    }
    ::IceInternal::BasicStream* __is = __result->__startReadParams();
    __is->read(__ret);
    __result->__endReadParams();
    return __ret;
}

const ::std::string&
IceProxy::QFGN::GameServer::ice_staticId()
{
    return ::QFGN::GameServer::ice_staticId();
}

::IceProxy::Ice::Object*
IceProxy::QFGN::GameServer::__newInstance() const
{
    return new GameServer;
}

::Ice::Object* QFGN::upCast(::QFGN::GameServer* p) { return p; }

namespace
{
const ::std::string __QFGN__GameServer_ids[2] =
{
    "::Ice::Object",
    "::QFGN::GameServer"
};

}

bool
QFGN::GameServer::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__QFGN__GameServer_ids, __QFGN__GameServer_ids + 2, _s);
}

::std::vector< ::std::string>
QFGN::GameServer::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__QFGN__GameServer_ids[0], &__QFGN__GameServer_ids[2]);
}

const ::std::string&
QFGN::GameServer::ice_id(const ::Ice::Current&) const
{
    return __QFGN__GameServer_ids[1];
}

const ::std::string&
QFGN::GameServer::ice_staticId()
{
#ifdef ICE_HAS_THREAD_SAFE_LOCAL_STATIC
    static const ::std::string typeId = "::QFGN::GameServer";
    return typeId;
#else
    return __QFGN__GameServer_ids[1];
#endif
}

::Ice::DispatchStatus
QFGN::GameServer::___doTransmit(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::QFGNServerClientProto::TPackage __p_stPackage;
    __is->read(__p_stPackage);
    __inS.endReadParams();
    ::Ice::Int __ret = doTransmit(__p_stPackage, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
QFGN::GameServer::___doPrinter(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::std::string __p_sInput;
    __is->read(__p_sInput);
    __inS.endReadParams();
    ::Ice::Int __ret = doPrinter(__p_sInput, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

namespace
{
const ::std::string __QFGN__GameServer_all[] =
{
    "doPrinter",
    "doTransmit",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

}

::Ice::DispatchStatus
QFGN::GameServer::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< const ::std::string*, const ::std::string*> r = ::std::equal_range(__QFGN__GameServer_all, __QFGN__GameServer_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __QFGN__GameServer_all)
    {
        case 0:
        {
            return ___doPrinter(in, current);
        }
        case 1:
        {
            return ___doTransmit(in, current);
        }
        case 2:
        {
            return ___ice_id(in, current);
        }
        case 3:
        {
            return ___ice_ids(in, current);
        }
        case 4:
        {
            return ___ice_isA(in, current);
        }
        case 5:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
QFGN::GameServer::__writeImpl(::IceInternal::BasicStream* __os) const
{
    __os->startWriteSlice(ice_staticId(), -1, true);
    __os->endWriteSlice();
}

void
QFGN::GameServer::__readImpl(::IceInternal::BasicStream* __is)
{
    __is->startReadSlice();
    __is->endReadSlice();
}

void 
QFGN::__patch(GameServerPtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::QFGN::GameServerPtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::QFGN::GameServer::ice_staticId(), v);
    }
}
