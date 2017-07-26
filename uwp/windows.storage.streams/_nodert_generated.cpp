// Copyright (c) Microsoft Corporation
// All rights reserved. 
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT. 
//
// See the Apache Version 2.0 License for specific language governing permissions and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Handle;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace Storage { namespace Streams { 

  v8::Local<v8::Value> WrapDataReaderLoadOperation(::Windows::Storage::Streams::DataReaderLoadOperation^ wintRtInstance);
  ::Windows::Storage::Streams::DataReaderLoadOperation^ UnwrapDataReaderLoadOperation(Local<Value> value);
  
  v8::Local<v8::Value> WrapIDataReader(::Windows::Storage::Streams::IDataReader^ wintRtInstance);
  ::Windows::Storage::Streams::IDataReader^ UnwrapIDataReader(Local<Value> value);
  
  v8::Local<v8::Value> WrapDataReader(::Windows::Storage::Streams::DataReader^ wintRtInstance);
  ::Windows::Storage::Streams::DataReader^ UnwrapDataReader(Local<Value> value);
  
  v8::Local<v8::Value> WrapDataWriterStoreOperation(::Windows::Storage::Streams::DataWriterStoreOperation^ wintRtInstance);
  ::Windows::Storage::Streams::DataWriterStoreOperation^ UnwrapDataWriterStoreOperation(Local<Value> value);
  
  v8::Local<v8::Value> WrapIDataWriter(::Windows::Storage::Streams::IDataWriter^ wintRtInstance);
  ::Windows::Storage::Streams::IDataWriter^ UnwrapIDataWriter(Local<Value> value);
  
  v8::Local<v8::Value> WrapDataWriter(::Windows::Storage::Streams::DataWriter^ wintRtInstance);
  ::Windows::Storage::Streams::DataWriter^ UnwrapDataWriter(Local<Value> value);
  
  v8::Local<v8::Value> WrapBuffer(::Windows::Storage::Streams::Buffer^ wintRtInstance);
  ::Windows::Storage::Streams::Buffer^ UnwrapBuffer(Local<Value> value);
  
  v8::Local<v8::Value> WrapIBuffer(::Windows::Storage::Streams::IBuffer^ wintRtInstance);
  ::Windows::Storage::Streams::IBuffer^ UnwrapIBuffer(Local<Value> value);
  
  v8::Local<v8::Value> WrapIContentTypeProvider(::Windows::Storage::Streams::IContentTypeProvider^ wintRtInstance);
  ::Windows::Storage::Streams::IContentTypeProvider^ UnwrapIContentTypeProvider(Local<Value> value);
  
  v8::Local<v8::Value> WrapIInputStream(::Windows::Storage::Streams::IInputStream^ wintRtInstance);
  ::Windows::Storage::Streams::IInputStream^ UnwrapIInputStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapIOutputStream(::Windows::Storage::Streams::IOutputStream^ wintRtInstance);
  ::Windows::Storage::Streams::IOutputStream^ UnwrapIOutputStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapIRandomAccessStream(::Windows::Storage::Streams::IRandomAccessStream^ wintRtInstance);
  ::Windows::Storage::Streams::IRandomAccessStream^ UnwrapIRandomAccessStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapIRandomAccessStreamWithContentType(::Windows::Storage::Streams::IRandomAccessStreamWithContentType^ wintRtInstance);
  ::Windows::Storage::Streams::IRandomAccessStreamWithContentType^ UnwrapIRandomAccessStreamWithContentType(Local<Value> value);
  
  v8::Local<v8::Value> WrapIRandomAccessStreamReference(::Windows::Storage::Streams::IRandomAccessStreamReference^ wintRtInstance);
  ::Windows::Storage::Streams::IRandomAccessStreamReference^ UnwrapIRandomAccessStreamReference(Local<Value> value);
  
  v8::Local<v8::Value> WrapRandomAccessStream(::Windows::Storage::Streams::RandomAccessStream^ wintRtInstance);
  ::Windows::Storage::Streams::RandomAccessStream^ UnwrapRandomAccessStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapIInputStreamReference(::Windows::Storage::Streams::IInputStreamReference^ wintRtInstance);
  ::Windows::Storage::Streams::IInputStreamReference^ UnwrapIInputStreamReference(Local<Value> value);
  
  v8::Local<v8::Value> WrapRandomAccessStreamReference(::Windows::Storage::Streams::RandomAccessStreamReference^ wintRtInstance);
  ::Windows::Storage::Streams::RandomAccessStreamReference^ UnwrapRandomAccessStreamReference(Local<Value> value);
  
  v8::Local<v8::Value> WrapFileRandomAccessStream(::Windows::Storage::Streams::FileRandomAccessStream^ wintRtInstance);
  ::Windows::Storage::Streams::FileRandomAccessStream^ UnwrapFileRandomAccessStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapFileInputStream(::Windows::Storage::Streams::FileInputStream^ wintRtInstance);
  ::Windows::Storage::Streams::FileInputStream^ UnwrapFileInputStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapFileOutputStream(::Windows::Storage::Streams::FileOutputStream^ wintRtInstance);
  ::Windows::Storage::Streams::FileOutputStream^ UnwrapFileOutputStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapRandomAccessStreamOverStream(::Windows::Storage::Streams::RandomAccessStreamOverStream^ wintRtInstance);
  ::Windows::Storage::Streams::RandomAccessStreamOverStream^ UnwrapRandomAccessStreamOverStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapInputStreamOverStream(::Windows::Storage::Streams::InputStreamOverStream^ wintRtInstance);
  ::Windows::Storage::Streams::InputStreamOverStream^ UnwrapInputStreamOverStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapOutputStreamOverStream(::Windows::Storage::Streams::OutputStreamOverStream^ wintRtInstance);
  ::Windows::Storage::Streams::OutputStreamOverStream^ UnwrapOutputStreamOverStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapInMemoryRandomAccessStream(::Windows::Storage::Streams::InMemoryRandomAccessStream^ wintRtInstance);
  ::Windows::Storage::Streams::InMemoryRandomAccessStream^ UnwrapInMemoryRandomAccessStream(Local<Value> value);
  


  static void InitByteOrderEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("ByteOrder").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("littleEndian").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::Streams::ByteOrder::LittleEndian)));
	Nan::Set(enumObject, Nan::New<String>("bigEndian").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::Streams::ByteOrder::BigEndian)));
  }


  static void InitUnicodeEncodingEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("UnicodeEncoding").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("utf8").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::Streams::UnicodeEncoding::Utf8)));
	Nan::Set(enumObject, Nan::New<String>("utf16LE").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::Streams::UnicodeEncoding::Utf16LE)));
	Nan::Set(enumObject, Nan::New<String>("utf16BE").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::Streams::UnicodeEncoding::Utf16BE)));
  }


  static void InitInputStreamOptionsEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("InputStreamOptions").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::Streams::InputStreamOptions::None)));
	Nan::Set(enumObject, Nan::New<String>("partial").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::Streams::InputStreamOptions::Partial)));
	Nan::Set(enumObject, Nan::New<String>("readAhead").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::Streams::InputStreamOptions::ReadAhead)));
  }



  
  class DataReaderLoadOperation : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DataReaderLoadOperation").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getResults", GetResults);
      Nan::SetPrototypeMethod(localRef, "cancel", Cancel);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorCode").ToLocalChecked(), ErrorCodeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("completed").ToLocalChecked(), CompletedGetter, CompletedSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DataReaderLoadOperation").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DataReaderLoadOperation(::Windows::Storage::Streams::DataReaderLoadOperation^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::DataReaderLoadOperation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReaderLoadOperation^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::DataReaderLoadOperation^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DataReaderLoadOperation *wrapperInstance = new DataReaderLoadOperation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReaderLoadOperation^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::DataReaderLoadOperation^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::DataReaderLoadOperation^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDataReaderLoadOperation(winRtInstance));
    }


  
    static void GetResults(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReaderLoadOperation^>(info.This()))
      {
        return;
      }

      DataReaderLoadOperation *wrapper = DataReaderLoadOperation::Unwrap<DataReaderLoadOperation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned int result;
          result = wrapper->_instance->GetResults();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Cancel(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReaderLoadOperation^>(info.This()))
      {
        return;
      }

      DataReaderLoadOperation *wrapper = DataReaderLoadOperation::Unwrap<DataReaderLoadOperation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Cancel();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReaderLoadOperation^>(info.This()))
      {
        return;
      }

      DataReaderLoadOperation *wrapper = DataReaderLoadOperation::Unwrap<DataReaderLoadOperation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Close();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void ErrorCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReaderLoadOperation^>(info.This()))
      {
        return;
      }

      DataReaderLoadOperation *wrapper = DataReaderLoadOperation::Unwrap<DataReaderLoadOperation>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ErrorCode;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReaderLoadOperation^>(info.This()))
      {
        return;
      }

      DataReaderLoadOperation *wrapper = DataReaderLoadOperation::Unwrap<DataReaderLoadOperation>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->Id;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReaderLoadOperation^>(info.This()))
      {
        return;
      }

      DataReaderLoadOperation *wrapper = DataReaderLoadOperation::Unwrap<DataReaderLoadOperation>(info.This());

      try 
      {
        ::Windows::Foundation::AsyncStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CompletedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReaderLoadOperation^>(info.This()))
      {
        return;
      }

      DataReaderLoadOperation *wrapper = DataReaderLoadOperation::Unwrap<DataReaderLoadOperation>(info.This());

      try 
      {
        ::Windows::Foundation::AsyncOperationCompletedHandler<unsigned int>^ result = wrapper->_instance->Completed;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "AsyncOperationCompletedHandler`1", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CompletedSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::AsyncOperationCompletedHandler<unsigned int>^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReaderLoadOperation^>(info.This()))
      {
        return;
      }

      DataReaderLoadOperation *wrapper = DataReaderLoadOperation::Unwrap<DataReaderLoadOperation>(info.This());

      try 
      {
        
        ::Windows::Foundation::AsyncOperationCompletedHandler<unsigned int>^ winRtValue = dynamic_cast<::Windows::Foundation::AsyncOperationCompletedHandler<unsigned int>^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Completed = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Storage::Streams::DataReaderLoadOperation^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDataReaderLoadOperation(::Windows::Storage::Streams::DataReaderLoadOperation^ wintRtInstance);
    friend ::Windows::Storage::Streams::DataReaderLoadOperation^ UnwrapDataReaderLoadOperation(Local<Value> value);
  };
  Persistent<FunctionTemplate> DataReaderLoadOperation::s_constructorTemplate;

  v8::Local<v8::Value> WrapDataReaderLoadOperation(::Windows::Storage::Streams::DataReaderLoadOperation^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DataReaderLoadOperation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::DataReaderLoadOperation^ UnwrapDataReaderLoadOperation(Local<Value> value)
  {
     return DataReaderLoadOperation::Unwrap<DataReaderLoadOperation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDataReaderLoadOperation(Local<Object> exports)
  {
    DataReaderLoadOperation::Init(exports);
  }

  class IDataReader : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IDataReader").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "readByte", ReadByte);
      Nan::SetPrototypeMethod(localRef, "readBytes", ReadBytes);
      Nan::SetPrototypeMethod(localRef, "readBuffer", ReadBuffer);
      Nan::SetPrototypeMethod(localRef, "readBoolean", ReadBoolean);
      Nan::SetPrototypeMethod(localRef, "readGuid", ReadGuid);
      Nan::SetPrototypeMethod(localRef, "readInt16", ReadInt16);
      Nan::SetPrototypeMethod(localRef, "readInt32", ReadInt32);
      Nan::SetPrototypeMethod(localRef, "readInt64", ReadInt64);
      Nan::SetPrototypeMethod(localRef, "readUInt16", ReadUInt16);
      Nan::SetPrototypeMethod(localRef, "readUInt32", ReadUInt32);
      Nan::SetPrototypeMethod(localRef, "readUInt64", ReadUInt64);
      Nan::SetPrototypeMethod(localRef, "readSingle", ReadSingle);
      Nan::SetPrototypeMethod(localRef, "readDouble", ReadDouble);
      Nan::SetPrototypeMethod(localRef, "readString", ReadString);
      Nan::SetPrototypeMethod(localRef, "readDateTime", ReadDateTime);
      Nan::SetPrototypeMethod(localRef, "readTimeSpan", ReadTimeSpan);
      Nan::SetPrototypeMethod(localRef, "detachBuffer", DetachBuffer);
      Nan::SetPrototypeMethod(localRef, "detachStream", DetachStream);
      
            
      Nan::SetPrototypeMethod(localRef, "loadAsync", LoadAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("byteOrder").ToLocalChecked(), ByteOrderGetter, ByteOrderSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("inputStreamOptions").ToLocalChecked(), InputStreamOptionsGetter, InputStreamOptionsSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("unconsumedBufferLength").ToLocalChecked(), UnconsumedBufferLengthGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("unicodeEncoding").ToLocalChecked(), UnicodeEncodingGetter, UnicodeEncodingSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IDataReader").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IDataReader(::Windows::Storage::Streams::IDataReader^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::IDataReader^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::IDataReader^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IDataReader *wrapperInstance = new IDataReader(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::IDataReader^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::IDataReader^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIDataReader(winRtInstance));
    }


    static void LoadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      ::Windows::Storage::Streams::DataReaderLoadOperation^ op;
    

      if (info.Length() == 2
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->LoadAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void ReadByte(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned char result;
          result = wrapper->_instance->ReadByte();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadBytes(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;
      Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Not implemented")));
    }
    static void ReadBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IBuffer^ result;
          result = wrapper->_instance->ReadBuffer(arg0);
          info.GetReturnValue().Set(WrapIBuffer(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadBoolean(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->ReadBoolean();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadGuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Guid result;
          result = wrapper->_instance->ReadGuid();
          info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          short result;
          result = wrapper->_instance->ReadInt16();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          int result;
          result = wrapper->_instance->ReadInt32();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          __int64 result;
          result = wrapper->_instance->ReadInt64();
          info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadUInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned short result;
          result = wrapper->_instance->ReadUInt16();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadUInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned int result;
          result = wrapper->_instance->ReadUInt32();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadUInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned __int64 result;
          result = wrapper->_instance->ReadUInt64();
          info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadSingle(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          float result;
          result = wrapper->_instance->ReadSingle();
          info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadDouble(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          double result;
          result = wrapper->_instance->ReadDouble();
          info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadString(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->ReadString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadDateTime(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::DateTime result;
          result = wrapper->_instance->ReadDateTime();
          info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadTimeSpan(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::TimeSpan result;
          result = wrapper->_instance->ReadTimeSpan();
          info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DetachBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ result;
          result = wrapper->_instance->DetachBuffer();
          info.GetReturnValue().Set(WrapIBuffer(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DetachStream(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IInputStream^ result;
          result = wrapper->_instance->DetachStream();
          info.GetReturnValue().Set(WrapIInputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void ByteOrderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      try 
      {
        ::Windows::Storage::Streams::ByteOrder result = wrapper->_instance->ByteOrder;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ByteOrderSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::ByteOrder winRtValue = static_cast<::Windows::Storage::Streams::ByteOrder>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ByteOrder = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void InputStreamOptionsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      try 
      {
        ::Windows::Storage::Streams::InputStreamOptions result = wrapper->_instance->InputStreamOptions;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InputStreamOptionsSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::InputStreamOptions winRtValue = static_cast<::Windows::Storage::Streams::InputStreamOptions>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->InputStreamOptions = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void UnconsumedBufferLengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->UnconsumedBufferLength;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UnicodeEncodingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      try 
      {
        ::Windows::Storage::Streams::UnicodeEncoding result = wrapper->_instance->UnicodeEncoding;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UnicodeEncodingSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataReader^>(info.This()))
      {
        return;
      }

      IDataReader *wrapper = IDataReader::Unwrap<IDataReader>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::UnicodeEncoding winRtValue = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->UnicodeEncoding = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Storage::Streams::IDataReader^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIDataReader(::Windows::Storage::Streams::IDataReader^ wintRtInstance);
    friend ::Windows::Storage::Streams::IDataReader^ UnwrapIDataReader(Local<Value> value);
  };
  Persistent<FunctionTemplate> IDataReader::s_constructorTemplate;

  v8::Local<v8::Value> WrapIDataReader(::Windows::Storage::Streams::IDataReader^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IDataReader::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::IDataReader^ UnwrapIDataReader(Local<Value> value)
  {
     return IDataReader::Unwrap<IDataReader>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIDataReader(Local<Object> exports)
  {
    IDataReader::Init(exports);
  }

  class DataReader : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DataReader").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "readByte", ReadByte);
      Nan::SetPrototypeMethod(localRef, "readBytes", ReadBytes);
      Nan::SetPrototypeMethod(localRef, "readBuffer", ReadBuffer);
      Nan::SetPrototypeMethod(localRef, "readBoolean", ReadBoolean);
      Nan::SetPrototypeMethod(localRef, "readGuid", ReadGuid);
      Nan::SetPrototypeMethod(localRef, "readInt16", ReadInt16);
      Nan::SetPrototypeMethod(localRef, "readInt32", ReadInt32);
      Nan::SetPrototypeMethod(localRef, "readInt64", ReadInt64);
      Nan::SetPrototypeMethod(localRef, "readUInt16", ReadUInt16);
      Nan::SetPrototypeMethod(localRef, "readUInt32", ReadUInt32);
      Nan::SetPrototypeMethod(localRef, "readUInt64", ReadUInt64);
      Nan::SetPrototypeMethod(localRef, "readSingle", ReadSingle);
      Nan::SetPrototypeMethod(localRef, "readDouble", ReadDouble);
      Nan::SetPrototypeMethod(localRef, "readString", ReadString);
      Nan::SetPrototypeMethod(localRef, "readDateTime", ReadDateTime);
      Nan::SetPrototypeMethod(localRef, "readTimeSpan", ReadTimeSpan);
      Nan::SetPrototypeMethod(localRef, "detachBuffer", DetachBuffer);
      Nan::SetPrototypeMethod(localRef, "detachStream", DetachStream);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "loadAsync", LoadAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("unicodeEncoding").ToLocalChecked(), UnicodeEncodingGetter, UnicodeEncodingSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("inputStreamOptions").ToLocalChecked(), InputStreamOptionsGetter, InputStreamOptionsSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("byteOrder").ToLocalChecked(), ByteOrderGetter, ByteOrderSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("unconsumedBufferLength").ToLocalChecked(), UnconsumedBufferLengthGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "fromBuffer", FromBuffer);

      Nan::Set(exports, Nan::New<String>("DataReader").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DataReader(::Windows::Storage::Streams::DataReader^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::DataReader^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::DataReader^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IInputStream^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IInputStream^ arg0 = UnwrapIInputStream(info[0]);
          
          winRtInstance = ref new ::Windows::Storage::Streams::DataReader(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DataReader *wrapperInstance = new DataReader(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::DataReader^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::DataReader^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDataReader(winRtInstance));
    }


    static void LoadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      ::Windows::Storage::Streams::DataReaderLoadOperation^ op;
    

      if (info.Length() == 2
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->LoadAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void ReadByte(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned char result;
          result = wrapper->_instance->ReadByte();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadBytes(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;
      Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Not implemented")));
    }
    static void ReadBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IBuffer^ result;
          result = wrapper->_instance->ReadBuffer(arg0);
          info.GetReturnValue().Set(WrapIBuffer(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadBoolean(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->ReadBoolean();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadGuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Guid result;
          result = wrapper->_instance->ReadGuid();
          info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          short result;
          result = wrapper->_instance->ReadInt16();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          int result;
          result = wrapper->_instance->ReadInt32();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          __int64 result;
          result = wrapper->_instance->ReadInt64();
          info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadUInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned short result;
          result = wrapper->_instance->ReadUInt16();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadUInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned int result;
          result = wrapper->_instance->ReadUInt32();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadUInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned __int64 result;
          result = wrapper->_instance->ReadUInt64();
          info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadSingle(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          float result;
          result = wrapper->_instance->ReadSingle();
          info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadDouble(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          double result;
          result = wrapper->_instance->ReadDouble();
          info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadString(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->ReadString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadDateTime(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::DateTime result;
          result = wrapper->_instance->ReadDateTime();
          info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ReadTimeSpan(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::TimeSpan result;
          result = wrapper->_instance->ReadTimeSpan();
          info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DetachBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ result;
          result = wrapper->_instance->DetachBuffer();
          info.GetReturnValue().Set(WrapIBuffer(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DetachStream(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IInputStream^ result;
          result = wrapper->_instance->DetachStream();
          info.GetReturnValue().Set(WrapIInputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
	    return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
		  return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
		  return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
		return;
      }
    }



    static void FromBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          
          ::Windows::Storage::Streams::DataReader^ result;
          result = ::Windows::Storage::Streams::DataReader::FromBuffer(arg0);
          info.GetReturnValue().Set(WrapDataReader(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void UnicodeEncodingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      try 
      {
        ::Windows::Storage::Streams::UnicodeEncoding result = wrapper->_instance->UnicodeEncoding;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UnicodeEncodingSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::UnicodeEncoding winRtValue = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->UnicodeEncoding = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void InputStreamOptionsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      try 
      {
        ::Windows::Storage::Streams::InputStreamOptions result = wrapper->_instance->InputStreamOptions;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InputStreamOptionsSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::InputStreamOptions winRtValue = static_cast<::Windows::Storage::Streams::InputStreamOptions>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->InputStreamOptions = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ByteOrderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      try 
      {
        ::Windows::Storage::Streams::ByteOrder result = wrapper->_instance->ByteOrder;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ByteOrderSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::ByteOrder winRtValue = static_cast<::Windows::Storage::Streams::ByteOrder>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ByteOrder = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void UnconsumedBufferLengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataReader^>(info.This()))
      {
        return;
      }

      DataReader *wrapper = DataReader::Unwrap<DataReader>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->UnconsumedBufferLength;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Storage::Streams::DataReader^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDataReader(::Windows::Storage::Streams::DataReader^ wintRtInstance);
    friend ::Windows::Storage::Streams::DataReader^ UnwrapDataReader(Local<Value> value);
  };
  Persistent<FunctionTemplate> DataReader::s_constructorTemplate;

  v8::Local<v8::Value> WrapDataReader(::Windows::Storage::Streams::DataReader^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DataReader::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::DataReader^ UnwrapDataReader(Local<Value> value)
  {
     return DataReader::Unwrap<DataReader>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDataReader(Local<Object> exports)
  {
    DataReader::Init(exports);
  }

  class DataWriterStoreOperation : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DataWriterStoreOperation").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getResults", GetResults);
      Nan::SetPrototypeMethod(localRef, "cancel", Cancel);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorCode").ToLocalChecked(), ErrorCodeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("completed").ToLocalChecked(), CompletedGetter, CompletedSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DataWriterStoreOperation").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DataWriterStoreOperation(::Windows::Storage::Streams::DataWriterStoreOperation^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::DataWriterStoreOperation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriterStoreOperation^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::DataWriterStoreOperation^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DataWriterStoreOperation *wrapperInstance = new DataWriterStoreOperation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriterStoreOperation^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::DataWriterStoreOperation^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::DataWriterStoreOperation^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDataWriterStoreOperation(winRtInstance));
    }


  
    static void GetResults(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriterStoreOperation^>(info.This()))
      {
        return;
      }

      DataWriterStoreOperation *wrapper = DataWriterStoreOperation::Unwrap<DataWriterStoreOperation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned int result;
          result = wrapper->_instance->GetResults();
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Cancel(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriterStoreOperation^>(info.This()))
      {
        return;
      }

      DataWriterStoreOperation *wrapper = DataWriterStoreOperation::Unwrap<DataWriterStoreOperation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Cancel();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriterStoreOperation^>(info.This()))
      {
        return;
      }

      DataWriterStoreOperation *wrapper = DataWriterStoreOperation::Unwrap<DataWriterStoreOperation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Close();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void ErrorCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriterStoreOperation^>(info.This()))
      {
        return;
      }

      DataWriterStoreOperation *wrapper = DataWriterStoreOperation::Unwrap<DataWriterStoreOperation>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ErrorCode;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriterStoreOperation^>(info.This()))
      {
        return;
      }

      DataWriterStoreOperation *wrapper = DataWriterStoreOperation::Unwrap<DataWriterStoreOperation>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->Id;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriterStoreOperation^>(info.This()))
      {
        return;
      }

      DataWriterStoreOperation *wrapper = DataWriterStoreOperation::Unwrap<DataWriterStoreOperation>(info.This());

      try 
      {
        ::Windows::Foundation::AsyncStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CompletedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriterStoreOperation^>(info.This()))
      {
        return;
      }

      DataWriterStoreOperation *wrapper = DataWriterStoreOperation::Unwrap<DataWriterStoreOperation>(info.This());

      try 
      {
        ::Windows::Foundation::AsyncOperationCompletedHandler<unsigned int>^ result = wrapper->_instance->Completed;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "AsyncOperationCompletedHandler`1", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CompletedSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::AsyncOperationCompletedHandler<unsigned int>^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriterStoreOperation^>(info.This()))
      {
        return;
      }

      DataWriterStoreOperation *wrapper = DataWriterStoreOperation::Unwrap<DataWriterStoreOperation>(info.This());

      try 
      {
        
        ::Windows::Foundation::AsyncOperationCompletedHandler<unsigned int>^ winRtValue = dynamic_cast<::Windows::Foundation::AsyncOperationCompletedHandler<unsigned int>^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Completed = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Storage::Streams::DataWriterStoreOperation^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDataWriterStoreOperation(::Windows::Storage::Streams::DataWriterStoreOperation^ wintRtInstance);
    friend ::Windows::Storage::Streams::DataWriterStoreOperation^ UnwrapDataWriterStoreOperation(Local<Value> value);
  };
  Persistent<FunctionTemplate> DataWriterStoreOperation::s_constructorTemplate;

  v8::Local<v8::Value> WrapDataWriterStoreOperation(::Windows::Storage::Streams::DataWriterStoreOperation^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DataWriterStoreOperation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::DataWriterStoreOperation^ UnwrapDataWriterStoreOperation(Local<Value> value)
  {
     return DataWriterStoreOperation::Unwrap<DataWriterStoreOperation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDataWriterStoreOperation(Local<Object> exports)
  {
    DataWriterStoreOperation::Init(exports);
  }

  class IDataWriter : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IDataWriter").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "writeByte", WriteByte);
      Nan::SetPrototypeMethod(localRef, "writeBytes", WriteBytes);
      Nan::SetPrototypeMethod(localRef, "writeBuffer", WriteBuffer);
      Nan::SetPrototypeMethod(localRef, "writeBoolean", WriteBoolean);
      Nan::SetPrototypeMethod(localRef, "writeGuid", WriteGuid);
      Nan::SetPrototypeMethod(localRef, "writeInt16", WriteInt16);
      Nan::SetPrototypeMethod(localRef, "writeInt32", WriteInt32);
      Nan::SetPrototypeMethod(localRef, "writeInt64", WriteInt64);
      Nan::SetPrototypeMethod(localRef, "writeUInt16", WriteUInt16);
      Nan::SetPrototypeMethod(localRef, "writeUInt32", WriteUInt32);
      Nan::SetPrototypeMethod(localRef, "writeUInt64", WriteUInt64);
      Nan::SetPrototypeMethod(localRef, "writeSingle", WriteSingle);
      Nan::SetPrototypeMethod(localRef, "writeDouble", WriteDouble);
      Nan::SetPrototypeMethod(localRef, "writeDateTime", WriteDateTime);
      Nan::SetPrototypeMethod(localRef, "writeTimeSpan", WriteTimeSpan);
      Nan::SetPrototypeMethod(localRef, "writeString", WriteString);
      Nan::SetPrototypeMethod(localRef, "measureString", MeasureString);
      Nan::SetPrototypeMethod(localRef, "detachBuffer", DetachBuffer);
      Nan::SetPrototypeMethod(localRef, "detachStream", DetachStream);
      
            
      Nan::SetPrototypeMethod(localRef, "storeAsync", StoreAsync);
      Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("byteOrder").ToLocalChecked(), ByteOrderGetter, ByteOrderSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("unicodeEncoding").ToLocalChecked(), UnicodeEncodingGetter, UnicodeEncodingSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("unstoredBufferLength").ToLocalChecked(), UnstoredBufferLengthGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IDataWriter").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IDataWriter(::Windows::Storage::Streams::IDataWriter^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::IDataWriter^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::IDataWriter^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IDataWriter *wrapperInstance = new IDataWriter(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::IDataWriter^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::IDataWriter^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIDataWriter(winRtInstance));
    }


    static void StoreAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      ::Windows::Storage::Streams::DataWriterStoreOperation^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->StoreAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void WriteByte(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned char arg0 = static_cast<unsigned char>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteByte(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteBytes(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<unsigned char>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<unsigned char>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<unsigned char>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<unsigned char>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsInt32();
                 },
                 [](Local<Value> value) -> unsigned char {
                   return static_cast<unsigned char>(Nan::To<int32_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<unsigned char>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          wrapper->_instance->WriteBytes(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          
          wrapper->_instance->WriteBuffer(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsUint32()
        && info[2]->IsUint32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          unsigned int arg2 = static_cast<unsigned int>(Nan::To<uint32_t>(info[2]).FromMaybe(0));
          
          wrapper->_instance->WriteBuffer(arg0, arg1, arg2);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteBoolean(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          wrapper->_instance->WriteBoolean(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteGuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          wrapper->_instance->WriteGuid(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          short arg0 = static_cast<short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteInt16(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteInt32(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          __int64 arg0 = Nan::To<int64_t>(info[0]).FromMaybe(0);
          
          wrapper->_instance->WriteInt64(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteUInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteUInt16(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteUInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteUInt32(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteUInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteUInt64(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteSingle(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          float arg0 = static_cast<float>(Nan::To<double>(info[0]).FromMaybe(0.0));
          
          wrapper->_instance->WriteSingle(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteDouble(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          double arg0 = Nan::To<double>(info[0]).FromMaybe(0.0);
          
          wrapper->_instance->WriteDouble(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteDateTime(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsDate())
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          
          wrapper->_instance->WriteDateTime(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteTimeSpan(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          ::Windows::Foundation::TimeSpan arg0 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteTimeSpan(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteString(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          unsigned int result;
          result = wrapper->_instance->WriteString(arg0);
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void MeasureString(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          unsigned int result;
          result = wrapper->_instance->MeasureString(arg0);
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DetachBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ result;
          result = wrapper->_instance->DetachBuffer();
          info.GetReturnValue().Set(WrapIBuffer(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DetachStream(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IOutputStream^ result;
          result = wrapper->_instance->DetachStream();
          info.GetReturnValue().Set(WrapIOutputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void ByteOrderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      try 
      {
        ::Windows::Storage::Streams::ByteOrder result = wrapper->_instance->ByteOrder;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ByteOrderSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::ByteOrder winRtValue = static_cast<::Windows::Storage::Streams::ByteOrder>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ByteOrder = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void UnicodeEncodingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      try 
      {
        ::Windows::Storage::Streams::UnicodeEncoding result = wrapper->_instance->UnicodeEncoding;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UnicodeEncodingSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::UnicodeEncoding winRtValue = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->UnicodeEncoding = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void UnstoredBufferLengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IDataWriter^>(info.This()))
      {
        return;
      }

      IDataWriter *wrapper = IDataWriter::Unwrap<IDataWriter>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->UnstoredBufferLength;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Storage::Streams::IDataWriter^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIDataWriter(::Windows::Storage::Streams::IDataWriter^ wintRtInstance);
    friend ::Windows::Storage::Streams::IDataWriter^ UnwrapIDataWriter(Local<Value> value);
  };
  Persistent<FunctionTemplate> IDataWriter::s_constructorTemplate;

  v8::Local<v8::Value> WrapIDataWriter(::Windows::Storage::Streams::IDataWriter^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IDataWriter::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::IDataWriter^ UnwrapIDataWriter(Local<Value> value)
  {
     return IDataWriter::Unwrap<IDataWriter>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIDataWriter(Local<Object> exports)
  {
    IDataWriter::Init(exports);
  }

  class DataWriter : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DataWriter").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "writeByte", WriteByte);
      Nan::SetPrototypeMethod(localRef, "writeBytes", WriteBytes);
      Nan::SetPrototypeMethod(localRef, "writeBuffer", WriteBuffer);
      Nan::SetPrototypeMethod(localRef, "writeBoolean", WriteBoolean);
      Nan::SetPrototypeMethod(localRef, "writeGuid", WriteGuid);
      Nan::SetPrototypeMethod(localRef, "writeInt16", WriteInt16);
      Nan::SetPrototypeMethod(localRef, "writeInt32", WriteInt32);
      Nan::SetPrototypeMethod(localRef, "writeInt64", WriteInt64);
      Nan::SetPrototypeMethod(localRef, "writeUInt16", WriteUInt16);
      Nan::SetPrototypeMethod(localRef, "writeUInt32", WriteUInt32);
      Nan::SetPrototypeMethod(localRef, "writeUInt64", WriteUInt64);
      Nan::SetPrototypeMethod(localRef, "writeSingle", WriteSingle);
      Nan::SetPrototypeMethod(localRef, "writeDouble", WriteDouble);
      Nan::SetPrototypeMethod(localRef, "writeDateTime", WriteDateTime);
      Nan::SetPrototypeMethod(localRef, "writeTimeSpan", WriteTimeSpan);
      Nan::SetPrototypeMethod(localRef, "writeString", WriteString);
      Nan::SetPrototypeMethod(localRef, "measureString", MeasureString);
      Nan::SetPrototypeMethod(localRef, "detachBuffer", DetachBuffer);
      Nan::SetPrototypeMethod(localRef, "detachStream", DetachStream);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "storeAsync", StoreAsync);
      Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("unicodeEncoding").ToLocalChecked(), UnicodeEncodingGetter, UnicodeEncodingSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("byteOrder").ToLocalChecked(), ByteOrderGetter, ByteOrderSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("unstoredBufferLength").ToLocalChecked(), UnstoredBufferLengthGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DataWriter").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DataWriter(::Windows::Storage::Streams::DataWriter^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::DataWriter^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::DataWriter^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IOutputStream^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IOutputStream^ arg0 = UnwrapIOutputStream(info[0]);
          
          winRtInstance = ref new ::Windows::Storage::Streams::DataWriter(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try
        {
          winRtInstance = ref new ::Windows::Storage::Streams::DataWriter();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DataWriter *wrapperInstance = new DataWriter(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::DataWriter^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::DataWriter^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDataWriter(winRtInstance));
    }


    static void StoreAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      ::Windows::Storage::Streams::DataWriterStoreOperation^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->StoreAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void WriteByte(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned char arg0 = static_cast<unsigned char>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteByte(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteBytes(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<unsigned char>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<unsigned char>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<unsigned char>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<unsigned char>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsInt32();
                 },
                 [](Local<Value> value) -> unsigned char {
                   return static_cast<unsigned char>(Nan::To<int32_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<unsigned char>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          wrapper->_instance->WriteBytes(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          
          wrapper->_instance->WriteBuffer(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsUint32()
        && info[2]->IsUint32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          unsigned int arg2 = static_cast<unsigned int>(Nan::To<uint32_t>(info[2]).FromMaybe(0));
          
          wrapper->_instance->WriteBuffer(arg0, arg1, arg2);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteBoolean(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          wrapper->_instance->WriteBoolean(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteGuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          wrapper->_instance->WriteGuid(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          short arg0 = static_cast<short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteInt16(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteInt32(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          __int64 arg0 = Nan::To<int64_t>(info[0]).FromMaybe(0);
          
          wrapper->_instance->WriteInt64(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteUInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteUInt16(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteUInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteUInt32(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteUInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteUInt64(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteSingle(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          float arg0 = static_cast<float>(Nan::To<double>(info[0]).FromMaybe(0.0));
          
          wrapper->_instance->WriteSingle(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteDouble(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          double arg0 = Nan::To<double>(info[0]).FromMaybe(0.0);
          
          wrapper->_instance->WriteDouble(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteDateTime(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsDate())
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          
          wrapper->_instance->WriteDateTime(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteTimeSpan(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          ::Windows::Foundation::TimeSpan arg0 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->WriteTimeSpan(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void WriteString(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          unsigned int result;
          result = wrapper->_instance->WriteString(arg0);
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void MeasureString(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          unsigned int result;
          result = wrapper->_instance->MeasureString(arg0);
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DetachBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ result;
          result = wrapper->_instance->DetachBuffer();
          info.GetReturnValue().Set(WrapIBuffer(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DetachStream(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IOutputStream^ result;
          result = wrapper->_instance->DetachStream();
          info.GetReturnValue().Set(WrapIOutputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
	    return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
		  return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
		  return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
		return;
      }
    }




    static void UnicodeEncodingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      try 
      {
        ::Windows::Storage::Streams::UnicodeEncoding result = wrapper->_instance->UnicodeEncoding;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UnicodeEncodingSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::UnicodeEncoding winRtValue = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->UnicodeEncoding = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ByteOrderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      try 
      {
        ::Windows::Storage::Streams::ByteOrder result = wrapper->_instance->ByteOrder;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ByteOrderSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::ByteOrder winRtValue = static_cast<::Windows::Storage::Streams::ByteOrder>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ByteOrder = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void UnstoredBufferLengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::DataWriter^>(info.This()))
      {
        return;
      }

      DataWriter *wrapper = DataWriter::Unwrap<DataWriter>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->UnstoredBufferLength;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Storage::Streams::DataWriter^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDataWriter(::Windows::Storage::Streams::DataWriter^ wintRtInstance);
    friend ::Windows::Storage::Streams::DataWriter^ UnwrapDataWriter(Local<Value> value);
  };
  Persistent<FunctionTemplate> DataWriter::s_constructorTemplate;

  v8::Local<v8::Value> WrapDataWriter(::Windows::Storage::Streams::DataWriter^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DataWriter::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::DataWriter^ UnwrapDataWriter(Local<Value> value)
  {
     return DataWriter::Unwrap<DataWriter>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDataWriter(Local<Object> exports)
  {
    DataWriter::Init(exports);
  }

  class Buffer : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Buffer").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("length").ToLocalChecked(), LengthGetter, LengthSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("capacity").ToLocalChecked(), CapacityGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "createCopyFromMemoryBuffer", CreateCopyFromMemoryBuffer);
      Nan::SetMethod(constructor, "createMemoryBufferOverIBuffer", CreateMemoryBufferOverIBuffer);

      Nan::Set(exports, Nan::New<String>("Buffer").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Buffer(::Windows::Storage::Streams::Buffer^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::Buffer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::Buffer^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::Buffer^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Storage::Streams::Buffer(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Buffer *wrapperInstance = new Buffer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::Buffer^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::Buffer^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::Buffer^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBuffer(winRtInstance));
    }


  


    static void CreateCopyFromMemoryBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IMemoryBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::IMemoryBuffer^ arg0 = dynamic_cast<::Windows::Foundation::IMemoryBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Storage::Streams::Buffer^ result;
          result = ::Windows::Storage::Streams::Buffer::CreateCopyFromMemoryBuffer(arg0);
          info.GetReturnValue().Set(WrapBuffer(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateMemoryBufferOverIBuffer(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          
          ::Windows::Foundation::MemoryBuffer^ result;
          result = ::Windows::Storage::Streams::Buffer::CreateMemoryBufferOverIBuffer(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "MemoryBuffer", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void LengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::Buffer^>(info.This()))
      {
        return;
      }

      Buffer *wrapper = Buffer::Unwrap<Buffer>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->Length;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LengthSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsUint32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::Buffer^>(info.This()))
      {
        return;
      }

      Buffer *wrapper = Buffer::Unwrap<Buffer>(info.This());

      try 
      {
        
        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->Length = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void CapacityGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::Buffer^>(info.This()))
      {
        return;
      }

      Buffer *wrapper = Buffer::Unwrap<Buffer>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->Capacity;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Storage::Streams::Buffer^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBuffer(::Windows::Storage::Streams::Buffer^ wintRtInstance);
    friend ::Windows::Storage::Streams::Buffer^ UnwrapBuffer(Local<Value> value);
  };
  Persistent<FunctionTemplate> Buffer::s_constructorTemplate;

  v8::Local<v8::Value> WrapBuffer(::Windows::Storage::Streams::Buffer^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Buffer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::Buffer^ UnwrapBuffer(Local<Value> value)
  {
     return Buffer::Unwrap<Buffer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBuffer(Local<Object> exports)
  {
    Buffer::Init(exports);
  }

  class IBuffer : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IBuffer").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("capacity").ToLocalChecked(), CapacityGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("length").ToLocalChecked(), LengthGetter, LengthSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IBuffer").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IBuffer(::Windows::Storage::Streams::IBuffer^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::IBuffer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::IBuffer^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IBuffer *wrapperInstance = new IBuffer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::IBuffer^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::IBuffer^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIBuffer(winRtInstance));
    }


  



    static void CapacityGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info.This()))
      {
        return;
      }

      IBuffer *wrapper = IBuffer::Unwrap<IBuffer>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->Capacity;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info.This()))
      {
        return;
      }

      IBuffer *wrapper = IBuffer::Unwrap<IBuffer>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->Length;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LengthSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsUint32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info.This()))
      {
        return;
      }

      IBuffer *wrapper = IBuffer::Unwrap<IBuffer>(info.This());

      try 
      {
        
        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->Length = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Storage::Streams::IBuffer^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIBuffer(::Windows::Storage::Streams::IBuffer^ wintRtInstance);
    friend ::Windows::Storage::Streams::IBuffer^ UnwrapIBuffer(Local<Value> value);
  };
  Persistent<FunctionTemplate> IBuffer::s_constructorTemplate;

  v8::Local<v8::Value> WrapIBuffer(::Windows::Storage::Streams::IBuffer^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IBuffer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::IBuffer^ UnwrapIBuffer(Local<Value> value)
  {
     return IBuffer::Unwrap<IBuffer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIBuffer(Local<Object> exports)
  {
    IBuffer::Init(exports);
  }

  class IContentTypeProvider : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IContentTypeProvider").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("contentType").ToLocalChecked(), ContentTypeGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IContentTypeProvider").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IContentTypeProvider(::Windows::Storage::Streams::IContentTypeProvider^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::IContentTypeProvider^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IContentTypeProvider^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::IContentTypeProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IContentTypeProvider *wrapperInstance = new IContentTypeProvider(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IContentTypeProvider^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::IContentTypeProvider^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::IContentTypeProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIContentTypeProvider(winRtInstance));
    }


  



    static void ContentTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IContentTypeProvider^>(info.This()))
      {
        return;
      }

      IContentTypeProvider *wrapper = IContentTypeProvider::Unwrap<IContentTypeProvider>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->ContentType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Storage::Streams::IContentTypeProvider^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIContentTypeProvider(::Windows::Storage::Streams::IContentTypeProvider^ wintRtInstance);
    friend ::Windows::Storage::Streams::IContentTypeProvider^ UnwrapIContentTypeProvider(Local<Value> value);
  };
  Persistent<FunctionTemplate> IContentTypeProvider::s_constructorTemplate;

  v8::Local<v8::Value> WrapIContentTypeProvider(::Windows::Storage::Streams::IContentTypeProvider^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IContentTypeProvider::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::IContentTypeProvider^ UnwrapIContentTypeProvider(Local<Value> value)
  {
     return IContentTypeProvider::Unwrap<IContentTypeProvider>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIContentTypeProvider(Local<Object> exports)
  {
    IContentTypeProvider::Init(exports);
  }

  class IInputStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IInputStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "readAsync", ReadAsync);
      
                  
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IInputStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IInputStream(::Windows::Storage::Streams::IInputStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::IInputStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IInputStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::IInputStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IInputStream *wrapperInstance = new IInputStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IInputStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::IInputStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::IInputStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIInputStream(winRtInstance));
    }


    static void ReadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IInputStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      IInputStream *wrapper = IInputStream::Unwrap<IInputStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Storage::Streams::IBuffer^, unsigned int>^ op;
    

      if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::Streams::InputStreamOptions arg2 = static_cast<::Windows::Storage::Streams::InputStreamOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->ReadAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IBuffer^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIBuffer(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  





  private:
    ::Windows::Storage::Streams::IInputStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIInputStream(::Windows::Storage::Streams::IInputStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::IInputStream^ UnwrapIInputStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> IInputStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapIInputStream(::Windows::Storage::Streams::IInputStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IInputStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::IInputStream^ UnwrapIInputStream(Local<Value> value)
  {
     return IInputStream::Unwrap<IInputStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIInputStream(Local<Object> exports)
  {
    IInputStream::Init(exports);
  }

  class IOutputStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IOutputStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "writeAsync", WriteAsync);
      Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
      
                  
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IOutputStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IOutputStream(::Windows::Storage::Streams::IOutputStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::IOutputStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IOutputStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::IOutputStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IOutputStream *wrapperInstance = new IOutputStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IOutputStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::IOutputStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::IOutputStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIOutputStream(winRtInstance));
    }


    static void WriteAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IOutputStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      IOutputStream *wrapper = IOutputStream::Unwrap<IOutputStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned int, unsigned int>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          
          op = wrapper->_instance->WriteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IOutputStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      IOutputStream *wrapper = IOutputStream::Unwrap<IOutputStream>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  





  private:
    ::Windows::Storage::Streams::IOutputStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIOutputStream(::Windows::Storage::Streams::IOutputStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::IOutputStream^ UnwrapIOutputStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> IOutputStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapIOutputStream(::Windows::Storage::Streams::IOutputStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IOutputStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::IOutputStream^ UnwrapIOutputStream(Local<Value> value)
  {
     return IOutputStream::Unwrap<IOutputStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIOutputStream(Local<Object> exports)
  {
    IOutputStream::Init(exports);
  }

  class IRandomAccessStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IRandomAccessStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getInputStreamAt", GetInputStreamAt);
      Nan::SetPrototypeMethod(localRef, "getOutputStreamAt", GetOutputStreamAt);
      Nan::SetPrototypeMethod(localRef, "seek", Seek);
      Nan::SetPrototypeMethod(localRef, "cloneStream", CloneStream);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canRead").ToLocalChecked(), CanReadGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canWrite").ToLocalChecked(), CanWriteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("size").ToLocalChecked(), SizeGetter, SizeSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IRandomAccessStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IRandomAccessStream(::Windows::Storage::Streams::IRandomAccessStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::IRandomAccessStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::IRandomAccessStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IRandomAccessStream *wrapperInstance = new IRandomAccessStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::IRandomAccessStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::IRandomAccessStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIRandomAccessStream(winRtInstance));
    }


  
    static void GetInputStreamAt(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info.This()))
      {
        return;
      }

      IRandomAccessStream *wrapper = IRandomAccessStream::Unwrap<IRandomAccessStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IInputStream^ result;
          result = wrapper->_instance->GetInputStreamAt(arg0);
          info.GetReturnValue().Set(WrapIInputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetOutputStreamAt(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info.This()))
      {
        return;
      }

      IRandomAccessStream *wrapper = IRandomAccessStream::Unwrap<IRandomAccessStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IOutputStream^ result;
          result = wrapper->_instance->GetOutputStreamAt(arg0);
          info.GetReturnValue().Set(WrapIOutputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Seek(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info.This()))
      {
        return;
      }

      IRandomAccessStream *wrapper = IRandomAccessStream::Unwrap<IRandomAccessStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->Seek(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneStream(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info.This()))
      {
        return;
      }

      IRandomAccessStream *wrapper = IRandomAccessStream::Unwrap<IRandomAccessStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IRandomAccessStream^ result;
          result = wrapper->_instance->CloneStream();
          info.GetReturnValue().Set(WrapIRandomAccessStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void CanReadGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info.This()))
      {
        return;
      }

      IRandomAccessStream *wrapper = IRandomAccessStream::Unwrap<IRandomAccessStream>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanRead;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CanWriteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info.This()))
      {
        return;
      }

      IRandomAccessStream *wrapper = IRandomAccessStream::Unwrap<IRandomAccessStream>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanWrite;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info.This()))
      {
        return;
      }

      IRandomAccessStream *wrapper = IRandomAccessStream::Unwrap<IRandomAccessStream>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->Position;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info.This()))
      {
        return;
      }

      IRandomAccessStream *wrapper = IRandomAccessStream::Unwrap<IRandomAccessStream>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->Size;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SizeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsNumber())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info.This()))
      {
        return;
      }

      IRandomAccessStream *wrapper = IRandomAccessStream::Unwrap<IRandomAccessStream>(info.This());

      try 
      {
        
        unsigned __int64 winRtValue = static_cast<unsigned __int64>(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->Size = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Storage::Streams::IRandomAccessStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIRandomAccessStream(::Windows::Storage::Streams::IRandomAccessStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::IRandomAccessStream^ UnwrapIRandomAccessStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> IRandomAccessStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapIRandomAccessStream(::Windows::Storage::Streams::IRandomAccessStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IRandomAccessStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::IRandomAccessStream^ UnwrapIRandomAccessStream(Local<Value> value)
  {
     return IRandomAccessStream::Unwrap<IRandomAccessStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIRandomAccessStream(Local<Object> exports)
  {
    IRandomAccessStream::Init(exports);
  }

  class IRandomAccessStreamWithContentType : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IRandomAccessStreamWithContentType").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IRandomAccessStreamWithContentType").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IRandomAccessStreamWithContentType(::Windows::Storage::Streams::IRandomAccessStreamWithContentType^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::IRandomAccessStreamWithContentType^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStreamWithContentType^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::IRandomAccessStreamWithContentType^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IRandomAccessStreamWithContentType *wrapperInstance = new IRandomAccessStreamWithContentType(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStreamWithContentType^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::IRandomAccessStreamWithContentType^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::IRandomAccessStreamWithContentType^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIRandomAccessStreamWithContentType(winRtInstance));
    }


  





  private:
    ::Windows::Storage::Streams::IRandomAccessStreamWithContentType^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIRandomAccessStreamWithContentType(::Windows::Storage::Streams::IRandomAccessStreamWithContentType^ wintRtInstance);
    friend ::Windows::Storage::Streams::IRandomAccessStreamWithContentType^ UnwrapIRandomAccessStreamWithContentType(Local<Value> value);
  };
  Persistent<FunctionTemplate> IRandomAccessStreamWithContentType::s_constructorTemplate;

  v8::Local<v8::Value> WrapIRandomAccessStreamWithContentType(::Windows::Storage::Streams::IRandomAccessStreamWithContentType^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IRandomAccessStreamWithContentType::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::IRandomAccessStreamWithContentType^ UnwrapIRandomAccessStreamWithContentType(Local<Value> value)
  {
     return IRandomAccessStreamWithContentType::Unwrap<IRandomAccessStreamWithContentType>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIRandomAccessStreamWithContentType(Local<Object> exports)
  {
    IRandomAccessStreamWithContentType::Init(exports);
  }

  class IRandomAccessStreamReference : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IRandomAccessStreamReference").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "openReadAsync", OpenReadAsync);
      
                  
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IRandomAccessStreamReference").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IRandomAccessStreamReference(::Windows::Storage::Streams::IRandomAccessStreamReference^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::IRandomAccessStreamReference^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStreamReference^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::IRandomAccessStreamReference^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IRandomAccessStreamReference *wrapperInstance = new IRandomAccessStreamReference(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStreamReference^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::IRandomAccessStreamReference^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::IRandomAccessStreamReference^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIRandomAccessStreamReference(winRtInstance));
    }


    static void OpenReadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStreamReference^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      IRandomAccessStreamReference *wrapper = IRandomAccessStreamReference::Unwrap<IRandomAccessStreamReference>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IRandomAccessStreamWithContentType^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->OpenReadAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IRandomAccessStreamWithContentType^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIRandomAccessStreamWithContentType(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  





  private:
    ::Windows::Storage::Streams::IRandomAccessStreamReference^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIRandomAccessStreamReference(::Windows::Storage::Streams::IRandomAccessStreamReference^ wintRtInstance);
    friend ::Windows::Storage::Streams::IRandomAccessStreamReference^ UnwrapIRandomAccessStreamReference(Local<Value> value);
  };
  Persistent<FunctionTemplate> IRandomAccessStreamReference::s_constructorTemplate;

  v8::Local<v8::Value> WrapIRandomAccessStreamReference(::Windows::Storage::Streams::IRandomAccessStreamReference^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IRandomAccessStreamReference::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::IRandomAccessStreamReference^ UnwrapIRandomAccessStreamReference(Local<Value> value)
  {
     return IRandomAccessStreamReference::Unwrap<IRandomAccessStreamReference>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIRandomAccessStreamReference(Local<Object> exports)
  {
    IRandomAccessStreamReference::Init(exports);
  }

  class RandomAccessStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("RandomAccessStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      func = Nan::GetFunction(Nan::New<FunctionTemplate>(CopyAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("copyAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(CopyAndCloseAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("copyAndCloseAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("RandomAccessStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    RandomAccessStream(::Windows::Storage::Streams::RandomAccessStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::RandomAccessStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::RandomAccessStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      RandomAccessStream *wrapperInstance = new RandomAccessStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::RandomAccessStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::RandomAccessStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapRandomAccessStream(winRtInstance));
    }


  

    static void CopyAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned __int64, unsigned __int64>^ op;
      

      if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IInputStream^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IOutputStream^>(info[1]))
      {
        try
        {
          ::Windows::Storage::Streams::IInputStream^ arg0 = UnwrapIInputStream(info[0]);
          ::Windows::Storage::Streams::IOutputStream^ arg1 = UnwrapIOutputStream(info[1]);
          
          op = ::Windows::Storage::Streams::RandomAccessStream::CopyAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IInputStream^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IOutputStream^>(info[1])
        && info[2]->IsNumber())
      {
        try
        {
          ::Windows::Storage::Streams::IInputStream^ arg0 = UnwrapIInputStream(info[0]);
          ::Windows::Storage::Streams::IOutputStream^ arg1 = UnwrapIOutputStream(info[1]);
          unsigned __int64 arg2 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[2]).FromMaybe(0));
          
          op = ::Windows::Storage::Streams::RandomAccessStream::CopyAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned __int64> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Number>(static_cast<double>(result));
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void CopyAndCloseAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned __int64, unsigned __int64>^ op;
      

      if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IInputStream^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IOutputStream^>(info[1]))
      {
        try
        {
          ::Windows::Storage::Streams::IInputStream^ arg0 = UnwrapIInputStream(info[0]);
          ::Windows::Storage::Streams::IOutputStream^ arg1 = UnwrapIOutputStream(info[1]);
          
          op = ::Windows::Storage::Streams::RandomAccessStream::CopyAndCloseAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned __int64> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Number>(static_cast<double>(result));
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }




  private:
    ::Windows::Storage::Streams::RandomAccessStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapRandomAccessStream(::Windows::Storage::Streams::RandomAccessStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::RandomAccessStream^ UnwrapRandomAccessStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> RandomAccessStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapRandomAccessStream(::Windows::Storage::Streams::RandomAccessStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(RandomAccessStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::RandomAccessStream^ UnwrapRandomAccessStream(Local<Value> value)
  {
     return RandomAccessStream::Unwrap<RandomAccessStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitRandomAccessStream(Local<Object> exports)
  {
    RandomAccessStream::Init(exports);
  }

  class IInputStreamReference : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IInputStreamReference").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "openSequentialReadAsync", OpenSequentialReadAsync);
      
                  
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IInputStreamReference").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IInputStreamReference(::Windows::Storage::Streams::IInputStreamReference^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::IInputStreamReference^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IInputStreamReference^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::IInputStreamReference^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IInputStreamReference *wrapperInstance = new IInputStreamReference(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IInputStreamReference^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::IInputStreamReference^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::IInputStreamReference^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIInputStreamReference(winRtInstance));
    }


    static void OpenSequentialReadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IInputStreamReference^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      IInputStreamReference *wrapper = IInputStreamReference::Unwrap<IInputStreamReference>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IInputStream^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->OpenSequentialReadAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IInputStream^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIInputStream(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  





  private:
    ::Windows::Storage::Streams::IInputStreamReference^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIInputStreamReference(::Windows::Storage::Streams::IInputStreamReference^ wintRtInstance);
    friend ::Windows::Storage::Streams::IInputStreamReference^ UnwrapIInputStreamReference(Local<Value> value);
  };
  Persistent<FunctionTemplate> IInputStreamReference::s_constructorTemplate;

  v8::Local<v8::Value> WrapIInputStreamReference(::Windows::Storage::Streams::IInputStreamReference^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IInputStreamReference::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::IInputStreamReference^ UnwrapIInputStreamReference(Local<Value> value)
  {
     return IInputStreamReference::Unwrap<IInputStreamReference>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIInputStreamReference(Local<Object> exports)
  {
    IInputStreamReference::Init(exports);
  }

  class RandomAccessStreamReference : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("RandomAccessStreamReference").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "openReadAsync", OpenReadAsync);
      
                  
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "createFromFile", CreateFromFile);
      Nan::SetMethod(constructor, "createFromUri", CreateFromUri);
      Nan::SetMethod(constructor, "createFromStream", CreateFromStream);

      Nan::Set(exports, Nan::New<String>("RandomAccessStreamReference").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    RandomAccessStreamReference(::Windows::Storage::Streams::RandomAccessStreamReference^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::RandomAccessStreamReference^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamReference^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::RandomAccessStreamReference^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      RandomAccessStreamReference *wrapperInstance = new RandomAccessStreamReference(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamReference^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::RandomAccessStreamReference^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::RandomAccessStreamReference^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapRandomAccessStreamReference(winRtInstance));
    }


    static void OpenReadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamReference^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      RandomAccessStreamReference *wrapper = RandomAccessStreamReference::Unwrap<RandomAccessStreamReference>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IRandomAccessStreamWithContentType^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->OpenReadAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IRandomAccessStreamWithContentType^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIRandomAccessStreamWithContentType(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  


    static void CreateFromFile(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = dynamic_cast<::Windows::Storage::IStorageFile^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Storage::Streams::RandomAccessStreamReference^ result;
          result = ::Windows::Storage::Streams::RandomAccessStreamReference::CreateFromFile(arg0);
          info.GetReturnValue().Set(WrapRandomAccessStreamReference(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateFromUri(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Storage::Streams::RandomAccessStreamReference^ result;
          result = ::Windows::Storage::Streams::RandomAccessStreamReference::CreateFromUri(arg0);
          info.GetReturnValue().Set(WrapRandomAccessStreamReference(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateFromStream(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IRandomAccessStream^ arg0 = UnwrapIRandomAccessStream(info[0]);
          
          ::Windows::Storage::Streams::RandomAccessStreamReference^ result;
          result = ::Windows::Storage::Streams::RandomAccessStreamReference::CreateFromStream(arg0);
          info.GetReturnValue().Set(WrapRandomAccessStreamReference(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



  private:
    ::Windows::Storage::Streams::RandomAccessStreamReference^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapRandomAccessStreamReference(::Windows::Storage::Streams::RandomAccessStreamReference^ wintRtInstance);
    friend ::Windows::Storage::Streams::RandomAccessStreamReference^ UnwrapRandomAccessStreamReference(Local<Value> value);
  };
  Persistent<FunctionTemplate> RandomAccessStreamReference::s_constructorTemplate;

  v8::Local<v8::Value> WrapRandomAccessStreamReference(::Windows::Storage::Streams::RandomAccessStreamReference^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(RandomAccessStreamReference::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::RandomAccessStreamReference^ UnwrapRandomAccessStreamReference(Local<Value> value)
  {
     return RandomAccessStreamReference::Unwrap<RandomAccessStreamReference>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitRandomAccessStreamReference(Local<Object> exports)
  {
    RandomAccessStreamReference::Init(exports);
  }

  class FileRandomAccessStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("FileRandomAccessStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "getInputStreamAt", GetInputStreamAt);
      Nan::SetPrototypeMethod(localRef, "getOutputStreamAt", GetOutputStreamAt);
      Nan::SetPrototypeMethod(localRef, "seek", Seek);
      Nan::SetPrototypeMethod(localRef, "cloneStream", CloneStream);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "readAsync", ReadAsync);
      Nan::SetPrototypeMethod(localRef, "writeAsync", WriteAsync);
      Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("size").ToLocalChecked(), SizeGetter, SizeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canRead").ToLocalChecked(), CanReadGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canWrite").ToLocalChecked(), CanWriteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("FileRandomAccessStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    FileRandomAccessStream(::Windows::Storage::Streams::FileRandomAccessStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::FileRandomAccessStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::FileRandomAccessStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      FileRandomAccessStream *wrapperInstance = new FileRandomAccessStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::FileRandomAccessStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::FileRandomAccessStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapFileRandomAccessStream(winRtInstance));
    }


    static void ReadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Storage::Streams::IBuffer^, unsigned int>^ op;
    

      if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::Streams::InputStreamOptions arg2 = static_cast<::Windows::Storage::Streams::InputStreamOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->ReadAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IBuffer^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIBuffer(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void WriteAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned int, unsigned int>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          
          op = wrapper->_instance->WriteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void GetInputStreamAt(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IInputStream^ result;
          result = wrapper->_instance->GetInputStreamAt(arg0);
          info.GetReturnValue().Set(WrapIInputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetOutputStreamAt(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IOutputStream^ result;
          result = wrapper->_instance->GetOutputStreamAt(arg0);
          info.GetReturnValue().Set(WrapIOutputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Seek(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->Seek(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneStream(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IRandomAccessStream^ result;
          result = wrapper->_instance->CloneStream();
          info.GetReturnValue().Set(WrapIRandomAccessStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
	    return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
		  return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
		  return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
		return;
      }
    }




    static void SizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->Size;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SizeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsNumber())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      try 
      {
        
        unsigned __int64 winRtValue = static_cast<unsigned __int64>(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->Size = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void CanReadGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanRead;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CanWriteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanWrite;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileRandomAccessStream^>(info.This()))
      {
        return;
      }

      FileRandomAccessStream *wrapper = FileRandomAccessStream::Unwrap<FileRandomAccessStream>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->Position;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Storage::Streams::FileRandomAccessStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapFileRandomAccessStream(::Windows::Storage::Streams::FileRandomAccessStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::FileRandomAccessStream^ UnwrapFileRandomAccessStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> FileRandomAccessStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapFileRandomAccessStream(::Windows::Storage::Streams::FileRandomAccessStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(FileRandomAccessStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::FileRandomAccessStream^ UnwrapFileRandomAccessStream(Local<Value> value)
  {
     return FileRandomAccessStream::Unwrap<FileRandomAccessStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitFileRandomAccessStream(Local<Object> exports)
  {
    FileRandomAccessStream::Init(exports);
  }

  class FileInputStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("FileInputStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "readAsync", ReadAsync);
      
                  
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("FileInputStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    FileInputStream(::Windows::Storage::Streams::FileInputStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::FileInputStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileInputStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::FileInputStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      FileInputStream *wrapperInstance = new FileInputStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileInputStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::FileInputStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::FileInputStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapFileInputStream(winRtInstance));
    }


    static void ReadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileInputStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      FileInputStream *wrapper = FileInputStream::Unwrap<FileInputStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Storage::Streams::IBuffer^, unsigned int>^ op;
    

      if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::Streams::InputStreamOptions arg2 = static_cast<::Windows::Storage::Streams::InputStreamOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->ReadAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IBuffer^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIBuffer(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileInputStream^>(info.This()))
      {
	    return;
      }

      FileInputStream *wrapper = FileInputStream::Unwrap<FileInputStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
		  return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
		  return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
		return;
      }
    }






  private:
    ::Windows::Storage::Streams::FileInputStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapFileInputStream(::Windows::Storage::Streams::FileInputStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::FileInputStream^ UnwrapFileInputStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> FileInputStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapFileInputStream(::Windows::Storage::Streams::FileInputStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(FileInputStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::FileInputStream^ UnwrapFileInputStream(Local<Value> value)
  {
     return FileInputStream::Unwrap<FileInputStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitFileInputStream(Local<Object> exports)
  {
    FileInputStream::Init(exports);
  }

  class FileOutputStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("FileOutputStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "writeAsync", WriteAsync);
      Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
      
                  
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("FileOutputStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    FileOutputStream(::Windows::Storage::Streams::FileOutputStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::FileOutputStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileOutputStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::FileOutputStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      FileOutputStream *wrapperInstance = new FileOutputStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileOutputStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::FileOutputStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::FileOutputStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapFileOutputStream(winRtInstance));
    }


    static void WriteAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileOutputStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      FileOutputStream *wrapper = FileOutputStream::Unwrap<FileOutputStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned int, unsigned int>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          
          op = wrapper->_instance->WriteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileOutputStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      FileOutputStream *wrapper = FileOutputStream::Unwrap<FileOutputStream>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::FileOutputStream^>(info.This()))
      {
	    return;
      }

      FileOutputStream *wrapper = FileOutputStream::Unwrap<FileOutputStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
		  return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
		  return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
		return;
      }
    }






  private:
    ::Windows::Storage::Streams::FileOutputStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapFileOutputStream(::Windows::Storage::Streams::FileOutputStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::FileOutputStream^ UnwrapFileOutputStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> FileOutputStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapFileOutputStream(::Windows::Storage::Streams::FileOutputStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(FileOutputStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::FileOutputStream^ UnwrapFileOutputStream(Local<Value> value)
  {
     return FileOutputStream::Unwrap<FileOutputStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitFileOutputStream(Local<Object> exports)
  {
    FileOutputStream::Init(exports);
  }

  class RandomAccessStreamOverStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("RandomAccessStreamOverStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "getInputStreamAt", GetInputStreamAt);
      Nan::SetPrototypeMethod(localRef, "getOutputStreamAt", GetOutputStreamAt);
      Nan::SetPrototypeMethod(localRef, "seek", Seek);
      Nan::SetPrototypeMethod(localRef, "cloneStream", CloneStream);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "readAsync", ReadAsync);
      Nan::SetPrototypeMethod(localRef, "writeAsync", WriteAsync);
      Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("size").ToLocalChecked(), SizeGetter, SizeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canRead").ToLocalChecked(), CanReadGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canWrite").ToLocalChecked(), CanWriteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("RandomAccessStreamOverStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    RandomAccessStreamOverStream(::Windows::Storage::Streams::RandomAccessStreamOverStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::RandomAccessStreamOverStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::RandomAccessStreamOverStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      RandomAccessStreamOverStream *wrapperInstance = new RandomAccessStreamOverStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::RandomAccessStreamOverStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::RandomAccessStreamOverStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapRandomAccessStreamOverStream(winRtInstance));
    }


    static void ReadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Storage::Streams::IBuffer^, unsigned int>^ op;
    

      if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::Streams::InputStreamOptions arg2 = static_cast<::Windows::Storage::Streams::InputStreamOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->ReadAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IBuffer^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIBuffer(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void WriteAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned int, unsigned int>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          
          op = wrapper->_instance->WriteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void GetInputStreamAt(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IInputStream^ result;
          result = wrapper->_instance->GetInputStreamAt(arg0);
          info.GetReturnValue().Set(WrapIInputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetOutputStreamAt(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IOutputStream^ result;
          result = wrapper->_instance->GetOutputStreamAt(arg0);
          info.GetReturnValue().Set(WrapIOutputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Seek(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->Seek(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneStream(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IRandomAccessStream^ result;
          result = wrapper->_instance->CloneStream();
          info.GetReturnValue().Set(WrapIRandomAccessStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
	    return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
		  return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
		  return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
		return;
      }
    }




    static void SizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->Size;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SizeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsNumber())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      try 
      {
        
        unsigned __int64 winRtValue = static_cast<unsigned __int64>(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->Size = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void CanReadGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanRead;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CanWriteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanWrite;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamOverStream^>(info.This()))
      {
        return;
      }

      RandomAccessStreamOverStream *wrapper = RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->Position;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Storage::Streams::RandomAccessStreamOverStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapRandomAccessStreamOverStream(::Windows::Storage::Streams::RandomAccessStreamOverStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::RandomAccessStreamOverStream^ UnwrapRandomAccessStreamOverStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> RandomAccessStreamOverStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapRandomAccessStreamOverStream(::Windows::Storage::Streams::RandomAccessStreamOverStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(RandomAccessStreamOverStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::RandomAccessStreamOverStream^ UnwrapRandomAccessStreamOverStream(Local<Value> value)
  {
     return RandomAccessStreamOverStream::Unwrap<RandomAccessStreamOverStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitRandomAccessStreamOverStream(Local<Object> exports)
  {
    RandomAccessStreamOverStream::Init(exports);
  }

  class InputStreamOverStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("InputStreamOverStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "readAsync", ReadAsync);
      
                  
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("InputStreamOverStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    InputStreamOverStream(::Windows::Storage::Streams::InputStreamOverStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::InputStreamOverStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InputStreamOverStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::InputStreamOverStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      InputStreamOverStream *wrapperInstance = new InputStreamOverStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InputStreamOverStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::InputStreamOverStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::InputStreamOverStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapInputStreamOverStream(winRtInstance));
    }


    static void ReadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InputStreamOverStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      InputStreamOverStream *wrapper = InputStreamOverStream::Unwrap<InputStreamOverStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Storage::Streams::IBuffer^, unsigned int>^ op;
    

      if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::Streams::InputStreamOptions arg2 = static_cast<::Windows::Storage::Streams::InputStreamOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->ReadAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IBuffer^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIBuffer(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InputStreamOverStream^>(info.This()))
      {
	    return;
      }

      InputStreamOverStream *wrapper = InputStreamOverStream::Unwrap<InputStreamOverStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
		  return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
		  return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
		return;
      }
    }






  private:
    ::Windows::Storage::Streams::InputStreamOverStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapInputStreamOverStream(::Windows::Storage::Streams::InputStreamOverStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::InputStreamOverStream^ UnwrapInputStreamOverStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> InputStreamOverStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapInputStreamOverStream(::Windows::Storage::Streams::InputStreamOverStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(InputStreamOverStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::InputStreamOverStream^ UnwrapInputStreamOverStream(Local<Value> value)
  {
     return InputStreamOverStream::Unwrap<InputStreamOverStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitInputStreamOverStream(Local<Object> exports)
  {
    InputStreamOverStream::Init(exports);
  }

  class OutputStreamOverStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("OutputStreamOverStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "writeAsync", WriteAsync);
      Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
      
                  
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("OutputStreamOverStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    OutputStreamOverStream(::Windows::Storage::Streams::OutputStreamOverStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::OutputStreamOverStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::OutputStreamOverStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::OutputStreamOverStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      OutputStreamOverStream *wrapperInstance = new OutputStreamOverStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::OutputStreamOverStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::OutputStreamOverStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::OutputStreamOverStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapOutputStreamOverStream(winRtInstance));
    }


    static void WriteAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::OutputStreamOverStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      OutputStreamOverStream *wrapper = OutputStreamOverStream::Unwrap<OutputStreamOverStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned int, unsigned int>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          
          op = wrapper->_instance->WriteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::OutputStreamOverStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      OutputStreamOverStream *wrapper = OutputStreamOverStream::Unwrap<OutputStreamOverStream>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::OutputStreamOverStream^>(info.This()))
      {
	    return;
      }

      OutputStreamOverStream *wrapper = OutputStreamOverStream::Unwrap<OutputStreamOverStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
		  return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
		  return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
		return;
      }
    }






  private:
    ::Windows::Storage::Streams::OutputStreamOverStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapOutputStreamOverStream(::Windows::Storage::Streams::OutputStreamOverStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::OutputStreamOverStream^ UnwrapOutputStreamOverStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> OutputStreamOverStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapOutputStreamOverStream(::Windows::Storage::Streams::OutputStreamOverStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(OutputStreamOverStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::OutputStreamOverStream^ UnwrapOutputStreamOverStream(Local<Value> value)
  {
     return OutputStreamOverStream::Unwrap<OutputStreamOverStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitOutputStreamOverStream(Local<Object> exports)
  {
    OutputStreamOverStream::Init(exports);
  }

  class InMemoryRandomAccessStream : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("InMemoryRandomAccessStream").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "getInputStreamAt", GetInputStreamAt);
      Nan::SetPrototypeMethod(localRef, "getOutputStreamAt", GetOutputStreamAt);
      Nan::SetPrototypeMethod(localRef, "seek", Seek);
      Nan::SetPrototypeMethod(localRef, "cloneStream", CloneStream);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "readAsync", ReadAsync);
      Nan::SetPrototypeMethod(localRef, "writeAsync", WriteAsync);
      Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("size").ToLocalChecked(), SizeGetter, SizeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canRead").ToLocalChecked(), CanReadGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canWrite").ToLocalChecked(), CanWriteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("InMemoryRandomAccessStream").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    InMemoryRandomAccessStream(::Windows::Storage::Streams::InMemoryRandomAccessStream^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Storage::Streams::InMemoryRandomAccessStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Storage::Streams::InMemoryRandomAccessStream^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try
        {
          winRtInstance = ref new ::Windows::Storage::Streams::InMemoryRandomAccessStream();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      InMemoryRandomAccessStream *wrapperInstance = new InMemoryRandomAccessStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Storage::Streams::InMemoryRandomAccessStream^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Storage::Streams::InMemoryRandomAccessStream^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapInMemoryRandomAccessStream(winRtInstance));
    }


    static void ReadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Storage::Streams::IBuffer^, unsigned int>^ op;
    

      if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::Streams::InputStreamOptions arg2 = static_cast<::Windows::Storage::Streams::InputStreamOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->ReadAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IBuffer^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIBuffer(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void WriteAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned int, unsigned int>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = UnwrapIBuffer(info[0]);
          
          op = wrapper->_instance->WriteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void GetInputStreamAt(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IInputStream^ result;
          result = wrapper->_instance->GetInputStreamAt(arg0);
          info.GetReturnValue().Set(WrapIInputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetOutputStreamAt(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IOutputStream^ result;
          result = wrapper->_instance->GetOutputStreamAt(arg0);
          info.GetReturnValue().Set(WrapIOutputStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Seek(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->Seek(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CloneStream(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IRandomAccessStream^ result;
          result = wrapper->_instance->CloneStream();
          info.GetReturnValue().Set(WrapIRandomAccessStream(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
	    return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
		  return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
		  return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
		return;
      }
    }




    static void SizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->Size;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SizeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsNumber())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      try 
      {
        
        unsigned __int64 winRtValue = static_cast<unsigned __int64>(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->Size = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void CanReadGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanRead;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CanWriteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanWrite;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::InMemoryRandomAccessStream^>(info.This()))
      {
        return;
      }

      InMemoryRandomAccessStream *wrapper = InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->Position;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Storage::Streams::InMemoryRandomAccessStream^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapInMemoryRandomAccessStream(::Windows::Storage::Streams::InMemoryRandomAccessStream^ wintRtInstance);
    friend ::Windows::Storage::Streams::InMemoryRandomAccessStream^ UnwrapInMemoryRandomAccessStream(Local<Value> value);
  };
  Persistent<FunctionTemplate> InMemoryRandomAccessStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapInMemoryRandomAccessStream(::Windows::Storage::Streams::InMemoryRandomAccessStream^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(InMemoryRandomAccessStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::Streams::InMemoryRandomAccessStream^ UnwrapInMemoryRandomAccessStream(Local<Value> value)
  {
     return InMemoryRandomAccessStream::Unwrap<InMemoryRandomAccessStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitInMemoryRandomAccessStream(Local<Object> exports)
  {
    InMemoryRandomAccessStream::Init(exports);
  }

} } } } 

NAN_MODULE_INIT(init)
{
  // we ignore failures for now since it probably means that the initialization already happened for STA, and that's cool
  CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  //if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
  /*{
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }*/
  
  NodeRT::Windows::Storage::Streams::InitByteOrderEnum(target);
  NodeRT::Windows::Storage::Streams::InitUnicodeEncodingEnum(target);
  NodeRT::Windows::Storage::Streams::InitInputStreamOptionsEnum(target);
  NodeRT::Windows::Storage::Streams::InitDataReaderLoadOperation(target);
  NodeRT::Windows::Storage::Streams::InitIDataReader(target);
  NodeRT::Windows::Storage::Streams::InitDataReader(target);
  NodeRT::Windows::Storage::Streams::InitDataWriterStoreOperation(target);
  NodeRT::Windows::Storage::Streams::InitIDataWriter(target);
  NodeRT::Windows::Storage::Streams::InitDataWriter(target);
  NodeRT::Windows::Storage::Streams::InitBuffer(target);
  NodeRT::Windows::Storage::Streams::InitIBuffer(target);
  NodeRT::Windows::Storage::Streams::InitIContentTypeProvider(target);
  NodeRT::Windows::Storage::Streams::InitIInputStream(target);
  NodeRT::Windows::Storage::Streams::InitIOutputStream(target);
  NodeRT::Windows::Storage::Streams::InitIRandomAccessStream(target);
  NodeRT::Windows::Storage::Streams::InitIRandomAccessStreamWithContentType(target);
  NodeRT::Windows::Storage::Streams::InitIRandomAccessStreamReference(target);
  NodeRT::Windows::Storage::Streams::InitRandomAccessStream(target);
  NodeRT::Windows::Storage::Streams::InitIInputStreamReference(target);
  NodeRT::Windows::Storage::Streams::InitRandomAccessStreamReference(target);
  NodeRT::Windows::Storage::Streams::InitFileRandomAccessStream(target);
  NodeRT::Windows::Storage::Streams::InitFileInputStream(target);
  NodeRT::Windows::Storage::Streams::InitFileOutputStream(target);
  NodeRT::Windows::Storage::Streams::InitRandomAccessStreamOverStream(target);
  NodeRT::Windows::Storage::Streams::InitInputStreamOverStream(target);
  NodeRT::Windows::Storage::Streams::InitOutputStreamOverStream(target);
  NodeRT::Windows::Storage::Streams::InitInMemoryRandomAccessStream(target);

  NodeRT::Utils::RegisterNameSpace("Windows.Storage.Streams", target);
}


NODE_MODULE(binding, init)