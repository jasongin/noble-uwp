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

namespace NodeRT { namespace Windows { namespace Foundation { 

  v8::Local<v8::Value> WrapPropertyValue(::Windows::Foundation::PropertyValue^ wintRtInstance);
  ::Windows::Foundation::PropertyValue^ UnwrapPropertyValue(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStringable(::Windows::Foundation::IStringable^ wintRtInstance);
  ::Windows::Foundation::IStringable^ UnwrapIStringable(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeferral(::Windows::Foundation::Deferral^ wintRtInstance);
  ::Windows::Foundation::Deferral^ UnwrapDeferral(Local<Value> value);
  
  v8::Local<v8::Value> WrapIAsyncInfo(::Windows::Foundation::IAsyncInfo^ wintRtInstance);
  ::Windows::Foundation::IAsyncInfo^ UnwrapIAsyncInfo(Local<Value> value);
  
  v8::Local<v8::Value> WrapIAsyncAction(::Windows::Foundation::IAsyncAction^ wintRtInstance);
  ::Windows::Foundation::IAsyncAction^ UnwrapIAsyncAction(Local<Value> value);
  
  v8::Local<v8::Value> WrapIMemoryBufferReference(::Windows::Foundation::IMemoryBufferReference^ wintRtInstance);
  ::Windows::Foundation::IMemoryBufferReference^ UnwrapIMemoryBufferReference(Local<Value> value);
  
  v8::Local<v8::Value> WrapIMemoryBuffer(::Windows::Foundation::IMemoryBuffer^ wintRtInstance);
  ::Windows::Foundation::IMemoryBuffer^ UnwrapIMemoryBuffer(Local<Value> value);
  
  v8::Local<v8::Value> WrapMemoryBuffer(::Windows::Foundation::MemoryBuffer^ wintRtInstance);
  ::Windows::Foundation::MemoryBuffer^ UnwrapMemoryBuffer(Local<Value> value);
  
  v8::Local<v8::Value> WrapWwwFormUrlDecoder(::Windows::Foundation::WwwFormUrlDecoder^ wintRtInstance);
  ::Windows::Foundation::WwwFormUrlDecoder^ UnwrapWwwFormUrlDecoder(Local<Value> value);
  
  v8::Local<v8::Value> WrapIWwwFormUrlDecoderEntry(::Windows::Foundation::IWwwFormUrlDecoderEntry^ wintRtInstance);
  ::Windows::Foundation::IWwwFormUrlDecoderEntry^ UnwrapIWwwFormUrlDecoderEntry(Local<Value> value);
  
  v8::Local<v8::Value> WrapWwwFormUrlDecoderEntry(::Windows::Foundation::WwwFormUrlDecoderEntry^ wintRtInstance);
  ::Windows::Foundation::WwwFormUrlDecoderEntry^ UnwrapWwwFormUrlDecoderEntry(Local<Value> value);
  
  v8::Local<v8::Value> WrapIGetActivationFactory(::Windows::Foundation::IGetActivationFactory^ wintRtInstance);
  ::Windows::Foundation::IGetActivationFactory^ UnwrapIGetActivationFactory(Local<Value> value);
  
  v8::Local<v8::Value> WrapIPropertyValue(::Windows::Foundation::IPropertyValue^ wintRtInstance);
  ::Windows::Foundation::IPropertyValue^ UnwrapIPropertyValue(Local<Value> value);
  
  v8::Local<v8::Value> WrapUri(::Windows::Foundation::Uri^ wintRtInstance);
  ::Windows::Foundation::Uri^ UnwrapUri(Local<Value> value);
  


  static void InitPropertyTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("PropertyType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("empty").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Empty)));
	Nan::Set(enumObject, Nan::New<String>("uInt8").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::UInt8)));
	Nan::Set(enumObject, Nan::New<String>("int16").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Int16)));
	Nan::Set(enumObject, Nan::New<String>("uInt16").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::UInt16)));
	Nan::Set(enumObject, Nan::New<String>("int32").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Int32)));
	Nan::Set(enumObject, Nan::New<String>("uInt32").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::UInt32)));
	Nan::Set(enumObject, Nan::New<String>("int64").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Int64)));
	Nan::Set(enumObject, Nan::New<String>("uInt64").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::UInt64)));
	Nan::Set(enumObject, Nan::New<String>("single").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Single)));
	Nan::Set(enumObject, Nan::New<String>("double").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Double)));
	Nan::Set(enumObject, Nan::New<String>("char16").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Char16)));
	Nan::Set(enumObject, Nan::New<String>("boolean").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Boolean)));
	Nan::Set(enumObject, Nan::New<String>("string").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::String)));
	Nan::Set(enumObject, Nan::New<String>("inspectable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Inspectable)));
	Nan::Set(enumObject, Nan::New<String>("dateTime").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::DateTime)));
	Nan::Set(enumObject, Nan::New<String>("timeSpan").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::TimeSpan)));
	Nan::Set(enumObject, Nan::New<String>("guid").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Guid)));
	Nan::Set(enumObject, Nan::New<String>("point").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Point)));
	Nan::Set(enumObject, Nan::New<String>("size").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Size)));
	Nan::Set(enumObject, Nan::New<String>("rect").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Rect)));
	Nan::Set(enumObject, Nan::New<String>("otherType").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::OtherType)));
	Nan::Set(enumObject, Nan::New<String>("uInt8Array").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::UInt8Array)));
	Nan::Set(enumObject, Nan::New<String>("int16Array").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Int16Array)));
	Nan::Set(enumObject, Nan::New<String>("uInt16Array").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::UInt16Array)));
	Nan::Set(enumObject, Nan::New<String>("int32Array").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Int32Array)));
	Nan::Set(enumObject, Nan::New<String>("uInt32Array").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::UInt32Array)));
	Nan::Set(enumObject, Nan::New<String>("int64Array").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Int64Array)));
	Nan::Set(enumObject, Nan::New<String>("uInt64Array").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::UInt64Array)));
	Nan::Set(enumObject, Nan::New<String>("singleArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::SingleArray)));
	Nan::Set(enumObject, Nan::New<String>("doubleArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::DoubleArray)));
	Nan::Set(enumObject, Nan::New<String>("char16Array").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::Char16Array)));
	Nan::Set(enumObject, Nan::New<String>("booleanArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::BooleanArray)));
	Nan::Set(enumObject, Nan::New<String>("stringArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::StringArray)));
	Nan::Set(enumObject, Nan::New<String>("inspectableArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::InspectableArray)));
	Nan::Set(enumObject, Nan::New<String>("dateTimeArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::DateTimeArray)));
	Nan::Set(enumObject, Nan::New<String>("timeSpanArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::TimeSpanArray)));
	Nan::Set(enumObject, Nan::New<String>("guidArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::GuidArray)));
	Nan::Set(enumObject, Nan::New<String>("pointArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::PointArray)));
	Nan::Set(enumObject, Nan::New<String>("sizeArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::SizeArray)));
	Nan::Set(enumObject, Nan::New<String>("rectArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::RectArray)));
	Nan::Set(enumObject, Nan::New<String>("otherTypeArray").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::PropertyType::OtherTypeArray)));
  }


  static void InitAsyncStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("AsyncStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("started").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::AsyncStatus::Started)));
	Nan::Set(enumObject, Nan::New<String>("completed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::AsyncStatus::Completed)));
	Nan::Set(enumObject, Nan::New<String>("canceled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::AsyncStatus::Canceled)));
	Nan::Set(enumObject, Nan::New<String>("error").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Foundation::AsyncStatus::Error)));
  }



  
  static bool IsFoundationContractJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Foundation::FoundationContract FoundationContractFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::Foundation::FoundationContract returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> FoundationContractToJsObject(::Windows::Foundation::FoundationContract value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  static bool IsUniversalApiContractJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Foundation::UniversalApiContract UniversalApiContractFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::Foundation::UniversalApiContract returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> UniversalApiContractToJsObject(::Windows::Foundation::UniversalApiContract value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  class PropertyValue : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PropertyValue").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "createEmpty", CreateEmpty);
      Nan::SetMethod(constructor, "createUInt8", CreateUInt8);
      Nan::SetMethod(constructor, "createInt16", CreateInt16);
      Nan::SetMethod(constructor, "createUInt16", CreateUInt16);
      Nan::SetMethod(constructor, "createInt32", CreateInt32);
      Nan::SetMethod(constructor, "createUInt32", CreateUInt32);
      Nan::SetMethod(constructor, "createInt64", CreateInt64);
      Nan::SetMethod(constructor, "createUInt64", CreateUInt64);
      Nan::SetMethod(constructor, "createSingle", CreateSingle);
      Nan::SetMethod(constructor, "createDouble", CreateDouble);
      Nan::SetMethod(constructor, "createChar16", CreateChar16);
      Nan::SetMethod(constructor, "createBoolean", CreateBoolean);
      Nan::SetMethod(constructor, "createString", CreateString);
      Nan::SetMethod(constructor, "createInspectable", CreateInspectable);
      Nan::SetMethod(constructor, "createGuid", CreateGuid);
      Nan::SetMethod(constructor, "createDateTime", CreateDateTime);
      Nan::SetMethod(constructor, "createTimeSpan", CreateTimeSpan);
      Nan::SetMethod(constructor, "createPoint", CreatePoint);
      Nan::SetMethod(constructor, "createSize", CreateSize);
      Nan::SetMethod(constructor, "createRect", CreateRect);
      Nan::SetMethod(constructor, "createUInt8Array", CreateUInt8Array);
      Nan::SetMethod(constructor, "createInt16Array", CreateInt16Array);
      Nan::SetMethod(constructor, "createUInt16Array", CreateUInt16Array);
      Nan::SetMethod(constructor, "createInt32Array", CreateInt32Array);
      Nan::SetMethod(constructor, "createUInt32Array", CreateUInt32Array);
      Nan::SetMethod(constructor, "createInt64Array", CreateInt64Array);
      Nan::SetMethod(constructor, "createUInt64Array", CreateUInt64Array);
      Nan::SetMethod(constructor, "createSingleArray", CreateSingleArray);
      Nan::SetMethod(constructor, "createDoubleArray", CreateDoubleArray);
      Nan::SetMethod(constructor, "createChar16Array", CreateChar16Array);
      Nan::SetMethod(constructor, "createBooleanArray", CreateBooleanArray);
      Nan::SetMethod(constructor, "createStringArray", CreateStringArray);
      Nan::SetMethod(constructor, "createInspectableArray", CreateInspectableArray);
      Nan::SetMethod(constructor, "createGuidArray", CreateGuidArray);
      Nan::SetMethod(constructor, "createDateTimeArray", CreateDateTimeArray);
      Nan::SetMethod(constructor, "createTimeSpanArray", CreateTimeSpanArray);
      Nan::SetMethod(constructor, "createPointArray", CreatePointArray);
      Nan::SetMethod(constructor, "createSizeArray", CreateSizeArray);
      Nan::SetMethod(constructor, "createRectArray", CreateRectArray);

      Nan::Set(exports, Nan::New<String>("PropertyValue").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PropertyValue(::Windows::Foundation::PropertyValue^ instance)
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
      
      ::Windows::Foundation::PropertyValue^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::PropertyValue^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::PropertyValue^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      PropertyValue *wrapperInstance = new PropertyValue(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::PropertyValue^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::PropertyValue^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::PropertyValue^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPropertyValue(winRtInstance));
    }


  


    static void CreateEmpty(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateEmpty();
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateUInt8(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned char arg0 = static_cast<unsigned char>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateUInt8(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          short arg0 = static_cast<short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateInt16(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateUInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateUInt16(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateInt32(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateUInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateUInt32(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          __int64 arg0 = Nan::To<int64_t>(info[0]).FromMaybe(0);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateInt64(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateUInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateUInt64(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateSingle(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          float arg0 = static_cast<float>(Nan::To<double>(info[0]).FromMaybe(0.0));
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateSingle(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateDouble(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          double arg0 = Nan::To<double>(info[0]).FromMaybe(0.0);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateDouble(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateChar16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          wchar_t arg0 = NodeRT::Utils::GetFirstChar(info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateChar16(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateBoolean(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateBoolean(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateString(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateString(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateInspectable(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[0]))
      {
        try
        {
          ::Platform::Object^ arg0 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateInspectable(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateGuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateGuid(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateDateTime(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsDate())
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateDateTime(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateTimeSpan(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          ::Windows::Foundation::TimeSpan arg0 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateTimeSpan(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreatePoint(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsPoint(info[0]))
      {
        try
        {
          ::Windows::Foundation::Point arg0 = NodeRT::Utils::PointFromJs(info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreatePoint(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateSize(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsSize(info[0]))
      {
        try
        {
          ::Windows::Foundation::Size arg0 = NodeRT::Utils::SizeFromJs(info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateSize(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateRect(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsRect(info[0]))
      {
        try
        {
          ::Windows::Foundation::Rect arg0 = NodeRT::Utils::RectFromJs(info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateRect(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateUInt8Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

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
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateUInt8Array(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateInt16Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<short>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<short>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<short>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<short>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsInt32();
                 },
                 [](Local<Value> value) -> short {
                   return static_cast<short>(Nan::To<int32_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<short>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateInt16Array(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateUInt16Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<unsigned short>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<unsigned short>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<unsigned short>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<unsigned short>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsInt32();
                 },
                 [](Local<Value> value) -> unsigned short {
                   return static_cast<unsigned short>(Nan::To<int32_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<unsigned short>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateUInt16Array(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateInt32Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<int>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<int>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<int>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<int>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsInt32();
                 },
                 [](Local<Value> value) -> int {
                   return static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<int>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateInt32Array(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateUInt32Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<unsigned int>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<unsigned int>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<unsigned int>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<unsigned int>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsUint32();
                 },
                 [](Local<Value> value) -> unsigned int {
                   return static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<unsigned int>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateUInt32Array(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateInt64Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<__int64>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<__int64>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<__int64>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<__int64>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsNumber();
                 },
                 [](Local<Value> value) -> __int64 {
                   return Nan::To<int64_t>(value).FromMaybe(0);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<__int64>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateInt64Array(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateUInt64Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<unsigned __int64>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<unsigned __int64>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<unsigned __int64>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<unsigned __int64>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsNumber();
                 },
                 [](Local<Value> value) -> unsigned __int64 {
                   return static_cast<unsigned __int64>(Nan::To<int64_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<unsigned __int64>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateUInt64Array(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateSingleArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<float>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<float>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<float>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<float>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsNumber();
                 },
                 [](Local<Value> value) -> float {
                   return static_cast<float>(Nan::To<double>(value).FromMaybe(0.0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<float>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateSingleArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateDoubleArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<double>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<double>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<double>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<double>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsNumber();
                 },
                 [](Local<Value> value) -> double {
                   return Nan::To<double>(value).FromMaybe(0.0);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<double>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateDoubleArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateChar16Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<wchar_t>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<wchar_t>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<wchar_t>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<wchar_t>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsString();
                 },
                 [](Local<Value> value) -> wchar_t {
                   return NodeRT::Utils::GetFirstChar(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<wchar_t>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateChar16Array(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateBooleanArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<bool>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<bool>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<bool>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<bool>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsBoolean();
                 },
                 [](Local<Value> value) -> bool {
                   return Nan::To<bool>(value).FromMaybe(false);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<bool>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateBooleanArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateStringArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<::Platform::String^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateStringArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateInspectableArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<::Platform::Object^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<::Platform::Object^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<::Platform::Object^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<::Platform::Object^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value);
                 },
                 [](Local<Value> value) -> ::Platform::Object^ {
                   return dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<::Platform::Object^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateInspectableArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateGuidArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<::Platform::Guid>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<::Platform::Guid>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<::Platform::Guid>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<::Platform::Guid>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsGuid(value);
                 },
                 [](Local<Value> value) -> ::Platform::Guid {
                   return NodeRT::Utils::GuidFromJs(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<::Platform::Guid>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateGuidArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateDateTimeArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<::Windows::Foundation::DateTime>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<::Windows::Foundation::DateTime>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<::Windows::Foundation::DateTime>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<::Windows::Foundation::DateTime>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsDate();
                 },
                 [](Local<Value> value) -> ::Windows::Foundation::DateTime {
                   return NodeRT::Utils::DateTimeFromJSDate(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<::Windows::Foundation::DateTime>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateDateTimeArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateTimeSpanArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<::Windows::Foundation::TimeSpan>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<::Windows::Foundation::TimeSpan>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<::Windows::Foundation::TimeSpan>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<::Windows::Foundation::TimeSpan>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsNumber();
                 },
                 [](Local<Value> value) -> ::Windows::Foundation::TimeSpan {
                   return NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<::Windows::Foundation::TimeSpan>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateTimeSpanArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreatePointArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<::Windows::Foundation::Point>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<::Windows::Foundation::Point>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<::Windows::Foundation::Point>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<::Windows::Foundation::Point>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsPoint(value);
                 },
                 [](Local<Value> value) -> ::Windows::Foundation::Point {
                   return NodeRT::Utils::PointFromJs(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<::Windows::Foundation::Point>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreatePointArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateSizeArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<::Windows::Foundation::Size>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<::Windows::Foundation::Size>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<::Windows::Foundation::Size>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<::Windows::Foundation::Size>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsSize(value);
                 },
                 [](Local<Value> value) -> ::Windows::Foundation::Size {
                   return NodeRT::Utils::SizeFromJs(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<::Windows::Foundation::Size>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateSizeArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void CreateRectArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<::Windows::Foundation::Rect>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Platform::Array<::Windows::Foundation::Rect>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<::Windows::Foundation::Rect>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<::Windows::Foundation::Rect>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsRect(value);
                 },
                 [](Local<Value> value) -> ::Windows::Foundation::Rect {
                   return NodeRT::Utils::RectFromJs(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<::Windows::Foundation::Rect>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Platform::Object^ result;
          result = ::Windows::Foundation::PropertyValue::CreateRectArray(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    ::Windows::Foundation::PropertyValue^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPropertyValue(::Windows::Foundation::PropertyValue^ wintRtInstance);
    friend ::Windows::Foundation::PropertyValue^ UnwrapPropertyValue(Local<Value> value);
  };
  Persistent<FunctionTemplate> PropertyValue::s_constructorTemplate;

  v8::Local<v8::Value> WrapPropertyValue(::Windows::Foundation::PropertyValue^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PropertyValue::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::PropertyValue^ UnwrapPropertyValue(Local<Value> value)
  {
     return PropertyValue::Unwrap<PropertyValue>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPropertyValue(Local<Object> exports)
  {
    PropertyValue::Init(exports);
  }

  class IStringable : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IStringable").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "toString", ToString);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IStringable").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IStringable(::Windows::Foundation::IStringable^ instance)
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
      
      ::Windows::Foundation::IStringable^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IStringable^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::IStringable^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IStringable *wrapperInstance = new IStringable(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IStringable^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::IStringable^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::IStringable^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIStringable(winRtInstance));
    }


  
    static void ToString(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IStringable^>(info.This()))
      {
        return;
      }

      IStringable *wrapper = IStringable::Unwrap<IStringable>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->ToString();
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





  private:
    ::Windows::Foundation::IStringable^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIStringable(::Windows::Foundation::IStringable^ wintRtInstance);
    friend ::Windows::Foundation::IStringable^ UnwrapIStringable(Local<Value> value);
  };
  Persistent<FunctionTemplate> IStringable::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStringable(::Windows::Foundation::IStringable^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStringable::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::IStringable^ UnwrapIStringable(Local<Value> value)
  {
     return IStringable::Unwrap<IStringable>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStringable(Local<Object> exports)
  {
    IStringable::Init(exports);
  }

  class Deferral : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Deferral").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "complete", Complete);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("Deferral").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Deferral(::Windows::Foundation::Deferral^ instance)
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
      
      ::Windows::Foundation::Deferral^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Deferral^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::Deferral^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::DeferralCompletedHandler^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::DeferralCompletedHandler^ arg0 = dynamic_cast<::Windows::Foundation::DeferralCompletedHandler^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          winRtInstance = ref new ::Windows::Foundation::Deferral(arg0);
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

      Deferral *wrapperInstance = new Deferral(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Deferral^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::Deferral^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::Deferral^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeferral(winRtInstance));
    }


  
    static void Complete(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Deferral^>(info.This()))
      {
        return;
      }

      Deferral *wrapper = Deferral::Unwrap<Deferral>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Complete();
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Deferral^>(info.This()))
      {
	    return;
      }

      Deferral *wrapper = Deferral::Unwrap<Deferral>(info.This());

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
    ::Windows::Foundation::Deferral^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeferral(::Windows::Foundation::Deferral^ wintRtInstance);
    friend ::Windows::Foundation::Deferral^ UnwrapDeferral(Local<Value> value);
  };
  Persistent<FunctionTemplate> Deferral::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeferral(::Windows::Foundation::Deferral^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Deferral::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::Deferral^ UnwrapDeferral(Local<Value> value)
  {
     return Deferral::Unwrap<Deferral>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeferral(Local<Object> exports)
  {
    Deferral::Init(exports);
  }

  class IAsyncInfo : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IAsyncInfo").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "cancel", Cancel);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorCode").ToLocalChecked(), ErrorCodeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IAsyncInfo").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IAsyncInfo(::Windows::Foundation::IAsyncInfo^ instance)
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
      
      ::Windows::Foundation::IAsyncInfo^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncInfo^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::IAsyncInfo^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IAsyncInfo *wrapperInstance = new IAsyncInfo(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncInfo^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::IAsyncInfo^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::IAsyncInfo^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIAsyncInfo(winRtInstance));
    }


  
    static void Cancel(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncInfo^>(info.This()))
      {
        return;
      }

      IAsyncInfo *wrapper = IAsyncInfo::Unwrap<IAsyncInfo>(info.This());

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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncInfo^>(info.This()))
      {
        return;
      }

      IAsyncInfo *wrapper = IAsyncInfo::Unwrap<IAsyncInfo>(info.This());

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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncInfo^>(info.This()))
      {
        return;
      }

      IAsyncInfo *wrapper = IAsyncInfo::Unwrap<IAsyncInfo>(info.This());

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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncInfo^>(info.This()))
      {
        return;
      }

      IAsyncInfo *wrapper = IAsyncInfo::Unwrap<IAsyncInfo>(info.This());

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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncInfo^>(info.This()))
      {
        return;
      }

      IAsyncInfo *wrapper = IAsyncInfo::Unwrap<IAsyncInfo>(info.This());

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
    


  private:
    ::Windows::Foundation::IAsyncInfo^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIAsyncInfo(::Windows::Foundation::IAsyncInfo^ wintRtInstance);
    friend ::Windows::Foundation::IAsyncInfo^ UnwrapIAsyncInfo(Local<Value> value);
  };
  Persistent<FunctionTemplate> IAsyncInfo::s_constructorTemplate;

  v8::Local<v8::Value> WrapIAsyncInfo(::Windows::Foundation::IAsyncInfo^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IAsyncInfo::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::IAsyncInfo^ UnwrapIAsyncInfo(Local<Value> value)
  {
     return IAsyncInfo::Unwrap<IAsyncInfo>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIAsyncInfo(Local<Object> exports)
  {
    IAsyncInfo::Init(exports);
  }

  class IAsyncAction : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IAsyncAction").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getResults", GetResults);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("completed").ToLocalChecked(), CompletedGetter, CompletedSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IAsyncAction").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IAsyncAction(::Windows::Foundation::IAsyncAction^ instance)
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
      
      ::Windows::Foundation::IAsyncAction^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncAction^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::IAsyncAction^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IAsyncAction *wrapperInstance = new IAsyncAction(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncAction^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::IAsyncAction^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::IAsyncAction^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIAsyncAction(winRtInstance));
    }


  
    static void GetResults(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncAction^>(info.This()))
      {
        return;
      }

      IAsyncAction *wrapper = IAsyncAction::Unwrap<IAsyncAction>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->GetResults();
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



    static void CompletedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncAction^>(info.This()))
      {
        return;
      }

      IAsyncAction *wrapper = IAsyncAction::Unwrap<IAsyncAction>(info.This());

      try 
      {
        ::Windows::Foundation::AsyncActionCompletedHandler^ result = wrapper->_instance->Completed;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "AsyncActionCompletedHandler", result));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::AsyncActionCompletedHandler^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IAsyncAction^>(info.This()))
      {
        return;
      }

      IAsyncAction *wrapper = IAsyncAction::Unwrap<IAsyncAction>(info.This());

      try 
      {
        
        ::Windows::Foundation::AsyncActionCompletedHandler^ winRtValue = dynamic_cast<::Windows::Foundation::AsyncActionCompletedHandler^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Completed = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Foundation::IAsyncAction^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIAsyncAction(::Windows::Foundation::IAsyncAction^ wintRtInstance);
    friend ::Windows::Foundation::IAsyncAction^ UnwrapIAsyncAction(Local<Value> value);
  };
  Persistent<FunctionTemplate> IAsyncAction::s_constructorTemplate;

  v8::Local<v8::Value> WrapIAsyncAction(::Windows::Foundation::IAsyncAction^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IAsyncAction::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::IAsyncAction^ UnwrapIAsyncAction(Local<Value> value)
  {
     return IAsyncAction::Unwrap<IAsyncAction>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIAsyncAction(Local<Object> exports)
  {
    IAsyncAction::Init(exports);
  }

  class IMemoryBufferReference : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IMemoryBufferReference").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                        
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("capacity").ToLocalChecked(), CapacityGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IMemoryBufferReference").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IMemoryBufferReference(::Windows::Foundation::IMemoryBufferReference^ instance)
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
      
      ::Windows::Foundation::IMemoryBufferReference^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IMemoryBufferReference^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::IMemoryBufferReference^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IMemoryBufferReference *wrapperInstance = new IMemoryBufferReference(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IMemoryBufferReference^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::IMemoryBufferReference^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::IMemoryBufferReference^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIMemoryBufferReference(winRtInstance));
    }


  



    static void CapacityGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IMemoryBufferReference^>(info.This()))
      {
        return;
      }

      IMemoryBufferReference *wrapper = IMemoryBufferReference::Unwrap<IMemoryBufferReference>(info.This());

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
    


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
		return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"closed", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IMemoryBufferReference^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        IMemoryBufferReference *wrapper = IMemoryBufferReference::Unwrap<IMemoryBufferReference>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->Closed::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Foundation::IMemoryBufferReference^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Foundation::IMemoryBufferReference^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapIMemoryBufferReference(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else 
      {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
		return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false))
      {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      }
      else
      {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"closed", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
                
      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false))
      {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false))
      {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());
            
      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;
        
      try 
      {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"closed", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IMemoryBufferReference^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          IMemoryBufferReference *wrapper = IMemoryBufferReference::Unwrap<IMemoryBufferReference>(info.This());
          wrapper->_instance->Closed::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Foundation::IMemoryBufferReference^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIMemoryBufferReference(::Windows::Foundation::IMemoryBufferReference^ wintRtInstance);
    friend ::Windows::Foundation::IMemoryBufferReference^ UnwrapIMemoryBufferReference(Local<Value> value);
  };
  Persistent<FunctionTemplate> IMemoryBufferReference::s_constructorTemplate;

  v8::Local<v8::Value> WrapIMemoryBufferReference(::Windows::Foundation::IMemoryBufferReference^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IMemoryBufferReference::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::IMemoryBufferReference^ UnwrapIMemoryBufferReference(Local<Value> value)
  {
     return IMemoryBufferReference::Unwrap<IMemoryBufferReference>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIMemoryBufferReference(Local<Object> exports)
  {
    IMemoryBufferReference::Init(exports);
  }

  class IMemoryBuffer : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IMemoryBuffer").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "createReference", CreateReference);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IMemoryBuffer").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IMemoryBuffer(::Windows::Foundation::IMemoryBuffer^ instance)
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
      
      ::Windows::Foundation::IMemoryBuffer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IMemoryBuffer^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::IMemoryBuffer^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IMemoryBuffer *wrapperInstance = new IMemoryBuffer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IMemoryBuffer^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::IMemoryBuffer^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::IMemoryBuffer^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIMemoryBuffer(winRtInstance));
    }


  
    static void CreateReference(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IMemoryBuffer^>(info.This()))
      {
        return;
      }

      IMemoryBuffer *wrapper = IMemoryBuffer::Unwrap<IMemoryBuffer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::IMemoryBufferReference^ result;
          result = wrapper->_instance->CreateReference();
          info.GetReturnValue().Set(WrapIMemoryBufferReference(result));
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
    ::Windows::Foundation::IMemoryBuffer^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIMemoryBuffer(::Windows::Foundation::IMemoryBuffer^ wintRtInstance);
    friend ::Windows::Foundation::IMemoryBuffer^ UnwrapIMemoryBuffer(Local<Value> value);
  };
  Persistent<FunctionTemplate> IMemoryBuffer::s_constructorTemplate;

  v8::Local<v8::Value> WrapIMemoryBuffer(::Windows::Foundation::IMemoryBuffer^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IMemoryBuffer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::IMemoryBuffer^ UnwrapIMemoryBuffer(Local<Value> value)
  {
     return IMemoryBuffer::Unwrap<IMemoryBuffer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIMemoryBuffer(Local<Object> exports)
  {
    IMemoryBuffer::Init(exports);
  }

  class MemoryBuffer : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("MemoryBuffer").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "createReference", CreateReference);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("MemoryBuffer").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    MemoryBuffer(::Windows::Foundation::MemoryBuffer^ instance)
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
      
      ::Windows::Foundation::MemoryBuffer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::MemoryBuffer^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::MemoryBuffer^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          
          winRtInstance = ref new ::Windows::Foundation::MemoryBuffer(arg0);
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

      MemoryBuffer *wrapperInstance = new MemoryBuffer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::MemoryBuffer^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::MemoryBuffer^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::MemoryBuffer^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapMemoryBuffer(winRtInstance));
    }


  
    static void CreateReference(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::MemoryBuffer^>(info.This()))
      {
        return;
      }

      MemoryBuffer *wrapper = MemoryBuffer::Unwrap<MemoryBuffer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::IMemoryBufferReference^ result;
          result = wrapper->_instance->CreateReference();
          info.GetReturnValue().Set(WrapIMemoryBufferReference(result));
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::MemoryBuffer^>(info.This()))
      {
	    return;
      }

      MemoryBuffer *wrapper = MemoryBuffer::Unwrap<MemoryBuffer>(info.This());

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
    ::Windows::Foundation::MemoryBuffer^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapMemoryBuffer(::Windows::Foundation::MemoryBuffer^ wintRtInstance);
    friend ::Windows::Foundation::MemoryBuffer^ UnwrapMemoryBuffer(Local<Value> value);
  };
  Persistent<FunctionTemplate> MemoryBuffer::s_constructorTemplate;

  v8::Local<v8::Value> WrapMemoryBuffer(::Windows::Foundation::MemoryBuffer^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MemoryBuffer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::MemoryBuffer^ UnwrapMemoryBuffer(Local<Value> value)
  {
     return MemoryBuffer::Unwrap<MemoryBuffer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMemoryBuffer(Local<Object> exports)
  {
    MemoryBuffer::Init(exports);
  }

  class WwwFormUrlDecoder : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("WwwFormUrlDecoder").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getFirstValueByName", GetFirstValueByName);
      Nan::SetPrototypeMethod(localRef, "first", First);
      Nan::SetPrototypeMethod(localRef, "getAt", GetAt);
      Nan::SetPrototypeMethod(localRef, "indexOf", IndexOf);
      Nan::SetPrototypeMethod(localRef, "getMany", GetMany);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("WwwFormUrlDecoder").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    WwwFormUrlDecoder(::Windows::Foundation::WwwFormUrlDecoder^ instance)
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
      
      ::Windows::Foundation::WwwFormUrlDecoder^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::WwwFormUrlDecoder^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::WwwFormUrlDecoder^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          winRtInstance = ref new ::Windows::Foundation::WwwFormUrlDecoder(arg0);
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

      WwwFormUrlDecoder *wrapperInstance = new WwwFormUrlDecoder(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::WwwFormUrlDecoder^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::WwwFormUrlDecoder^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::WwwFormUrlDecoder^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapWwwFormUrlDecoder(winRtInstance));
    }


  
    static void GetFirstValueByName(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::WwwFormUrlDecoder^>(info.This()))
      {
        return;
      }

      WwwFormUrlDecoder *wrapper = WwwFormUrlDecoder::Unwrap<WwwFormUrlDecoder>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          Platform::String^ result;
          result = wrapper->_instance->GetFirstValueByName(arg0);
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
    static void First(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::WwwFormUrlDecoder^>(info.This()))
      {
        return;
      }

      WwwFormUrlDecoder *wrapper = WwwFormUrlDecoder::Unwrap<WwwFormUrlDecoder>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Foundation::IWwwFormUrlDecoderEntry^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Foundation::IWwwFormUrlDecoderEntry^>::CreateIteratorWrapper(result, 
            [](::Windows::Foundation::IWwwFormUrlDecoderEntry^ val) -> Local<Value> {
              return WrapIWwwFormUrlDecoderEntry(val);
            }
          ));
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
    static void GetAt(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::WwwFormUrlDecoder^>(info.This()))
      {
        return;
      }

      WwwFormUrlDecoder *wrapper = WwwFormUrlDecoder::Unwrap<WwwFormUrlDecoder>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Foundation::IWwwFormUrlDecoderEntry^ result;
          result = wrapper->_instance->GetAt(arg0);
          info.GetReturnValue().Set(WrapIWwwFormUrlDecoderEntry(result));
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
    static void IndexOf(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::WwwFormUrlDecoder^>(info.This()))
      {
        return;
      }

      WwwFormUrlDecoder *wrapper = WwwFormUrlDecoder::Unwrap<WwwFormUrlDecoder>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IWwwFormUrlDecoderEntry^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::IWwwFormUrlDecoderEntry^ arg0 = UnwrapIWwwFormUrlDecoderEntry(info[0]);
          unsigned int arg1;
          
          bool result;
          result = wrapper->_instance->IndexOf(arg0, &arg1);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("boolean").ToLocalChecked(), Nan::New<Boolean>(result));
          Nan::Set(resObj, Nan::New<String>("index").ToLocalChecked(), Nan::New<Integer>(arg1));
          info.GetReturnValue().Set(resObj);
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
    static void GetMany(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;
      Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Not implemented")));
    }





  private:
    ::Windows::Foundation::WwwFormUrlDecoder^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapWwwFormUrlDecoder(::Windows::Foundation::WwwFormUrlDecoder^ wintRtInstance);
    friend ::Windows::Foundation::WwwFormUrlDecoder^ UnwrapWwwFormUrlDecoder(Local<Value> value);
  };
  Persistent<FunctionTemplate> WwwFormUrlDecoder::s_constructorTemplate;

  v8::Local<v8::Value> WrapWwwFormUrlDecoder(::Windows::Foundation::WwwFormUrlDecoder^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(WwwFormUrlDecoder::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::WwwFormUrlDecoder^ UnwrapWwwFormUrlDecoder(Local<Value> value)
  {
     return WwwFormUrlDecoder::Unwrap<WwwFormUrlDecoder>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitWwwFormUrlDecoder(Local<Object> exports)
  {
    WwwFormUrlDecoder::Init(exports);
  }

  class IWwwFormUrlDecoderEntry : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IWwwFormUrlDecoderEntry").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("value").ToLocalChecked(), ValueGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IWwwFormUrlDecoderEntry").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IWwwFormUrlDecoderEntry(::Windows::Foundation::IWwwFormUrlDecoderEntry^ instance)
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
      
      ::Windows::Foundation::IWwwFormUrlDecoderEntry^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IWwwFormUrlDecoderEntry^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::IWwwFormUrlDecoderEntry^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IWwwFormUrlDecoderEntry *wrapperInstance = new IWwwFormUrlDecoderEntry(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IWwwFormUrlDecoderEntry^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::IWwwFormUrlDecoderEntry^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::IWwwFormUrlDecoderEntry^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIWwwFormUrlDecoderEntry(winRtInstance));
    }


  



    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IWwwFormUrlDecoderEntry^>(info.This()))
      {
        return;
      }

      IWwwFormUrlDecoderEntry *wrapper = IWwwFormUrlDecoderEntry::Unwrap<IWwwFormUrlDecoderEntry>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IWwwFormUrlDecoderEntry^>(info.This()))
      {
        return;
      }

      IWwwFormUrlDecoderEntry *wrapper = IWwwFormUrlDecoderEntry::Unwrap<IWwwFormUrlDecoderEntry>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Value;
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
    ::Windows::Foundation::IWwwFormUrlDecoderEntry^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIWwwFormUrlDecoderEntry(::Windows::Foundation::IWwwFormUrlDecoderEntry^ wintRtInstance);
    friend ::Windows::Foundation::IWwwFormUrlDecoderEntry^ UnwrapIWwwFormUrlDecoderEntry(Local<Value> value);
  };
  Persistent<FunctionTemplate> IWwwFormUrlDecoderEntry::s_constructorTemplate;

  v8::Local<v8::Value> WrapIWwwFormUrlDecoderEntry(::Windows::Foundation::IWwwFormUrlDecoderEntry^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IWwwFormUrlDecoderEntry::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::IWwwFormUrlDecoderEntry^ UnwrapIWwwFormUrlDecoderEntry(Local<Value> value)
  {
     return IWwwFormUrlDecoderEntry::Unwrap<IWwwFormUrlDecoderEntry>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIWwwFormUrlDecoderEntry(Local<Object> exports)
  {
    IWwwFormUrlDecoderEntry::Init(exports);
  }

  class WwwFormUrlDecoderEntry : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("WwwFormUrlDecoderEntry").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("value").ToLocalChecked(), ValueGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("WwwFormUrlDecoderEntry").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    WwwFormUrlDecoderEntry(::Windows::Foundation::WwwFormUrlDecoderEntry^ instance)
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
      
      ::Windows::Foundation::WwwFormUrlDecoderEntry^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::WwwFormUrlDecoderEntry^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::WwwFormUrlDecoderEntry^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      WwwFormUrlDecoderEntry *wrapperInstance = new WwwFormUrlDecoderEntry(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::WwwFormUrlDecoderEntry^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::WwwFormUrlDecoderEntry^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::WwwFormUrlDecoderEntry^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapWwwFormUrlDecoderEntry(winRtInstance));
    }


  



    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::WwwFormUrlDecoderEntry^>(info.This()))
      {
        return;
      }

      WwwFormUrlDecoderEntry *wrapper = WwwFormUrlDecoderEntry::Unwrap<WwwFormUrlDecoderEntry>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::WwwFormUrlDecoderEntry^>(info.This()))
      {
        return;
      }

      WwwFormUrlDecoderEntry *wrapper = WwwFormUrlDecoderEntry::Unwrap<WwwFormUrlDecoderEntry>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Value;
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
    ::Windows::Foundation::WwwFormUrlDecoderEntry^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapWwwFormUrlDecoderEntry(::Windows::Foundation::WwwFormUrlDecoderEntry^ wintRtInstance);
    friend ::Windows::Foundation::WwwFormUrlDecoderEntry^ UnwrapWwwFormUrlDecoderEntry(Local<Value> value);
  };
  Persistent<FunctionTemplate> WwwFormUrlDecoderEntry::s_constructorTemplate;

  v8::Local<v8::Value> WrapWwwFormUrlDecoderEntry(::Windows::Foundation::WwwFormUrlDecoderEntry^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(WwwFormUrlDecoderEntry::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::WwwFormUrlDecoderEntry^ UnwrapWwwFormUrlDecoderEntry(Local<Value> value)
  {
     return WwwFormUrlDecoderEntry::Unwrap<WwwFormUrlDecoderEntry>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitWwwFormUrlDecoderEntry(Local<Object> exports)
  {
    WwwFormUrlDecoderEntry::Init(exports);
  }

  class IGetActivationFactory : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IGetActivationFactory").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getActivationFactory", GetActivationFactory);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IGetActivationFactory").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IGetActivationFactory(::Windows::Foundation::IGetActivationFactory^ instance)
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
      
      ::Windows::Foundation::IGetActivationFactory^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IGetActivationFactory^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::IGetActivationFactory^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IGetActivationFactory *wrapperInstance = new IGetActivationFactory(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IGetActivationFactory^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::IGetActivationFactory^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::IGetActivationFactory^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIGetActivationFactory(winRtInstance));
    }


  
    static void GetActivationFactory(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IGetActivationFactory^>(info.This()))
      {
        return;
      }

      IGetActivationFactory *wrapper = IGetActivationFactory::Unwrap<IGetActivationFactory>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Platform::Object^ result;
          result = wrapper->_instance->GetActivationFactory(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    ::Windows::Foundation::IGetActivationFactory^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIGetActivationFactory(::Windows::Foundation::IGetActivationFactory^ wintRtInstance);
    friend ::Windows::Foundation::IGetActivationFactory^ UnwrapIGetActivationFactory(Local<Value> value);
  };
  Persistent<FunctionTemplate> IGetActivationFactory::s_constructorTemplate;

  v8::Local<v8::Value> WrapIGetActivationFactory(::Windows::Foundation::IGetActivationFactory^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IGetActivationFactory::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::IGetActivationFactory^ UnwrapIGetActivationFactory(Local<Value> value)
  {
     return IGetActivationFactory::Unwrap<IGetActivationFactory>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIGetActivationFactory(Local<Object> exports)
  {
    IGetActivationFactory::Init(exports);
  }

  class IPropertyValue : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IPropertyValue").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getUInt8", GetUInt8);
      Nan::SetPrototypeMethod(localRef, "getInt16", GetInt16);
      Nan::SetPrototypeMethod(localRef, "getUInt16", GetUInt16);
      Nan::SetPrototypeMethod(localRef, "getInt32", GetInt32);
      Nan::SetPrototypeMethod(localRef, "getUInt32", GetUInt32);
      Nan::SetPrototypeMethod(localRef, "getInt64", GetInt64);
      Nan::SetPrototypeMethod(localRef, "getUInt64", GetUInt64);
      Nan::SetPrototypeMethod(localRef, "getSingle", GetSingle);
      Nan::SetPrototypeMethod(localRef, "getDouble", GetDouble);
      Nan::SetPrototypeMethod(localRef, "getChar16", GetChar16);
      Nan::SetPrototypeMethod(localRef, "getBoolean", GetBoolean);
      Nan::SetPrototypeMethod(localRef, "getString", GetString);
      Nan::SetPrototypeMethod(localRef, "getGuid", GetGuid);
      Nan::SetPrototypeMethod(localRef, "getDateTime", GetDateTime);
      Nan::SetPrototypeMethod(localRef, "getTimeSpan", GetTimeSpan);
      Nan::SetPrototypeMethod(localRef, "getPoint", GetPoint);
      Nan::SetPrototypeMethod(localRef, "getSize", GetSize);
      Nan::SetPrototypeMethod(localRef, "getRect", GetRect);
      Nan::SetPrototypeMethod(localRef, "getUInt8Array", GetUInt8Array);
      Nan::SetPrototypeMethod(localRef, "getInt16Array", GetInt16Array);
      Nan::SetPrototypeMethod(localRef, "getUInt16Array", GetUInt16Array);
      Nan::SetPrototypeMethod(localRef, "getInt32Array", GetInt32Array);
      Nan::SetPrototypeMethod(localRef, "getUInt32Array", GetUInt32Array);
      Nan::SetPrototypeMethod(localRef, "getInt64Array", GetInt64Array);
      Nan::SetPrototypeMethod(localRef, "getUInt64Array", GetUInt64Array);
      Nan::SetPrototypeMethod(localRef, "getSingleArray", GetSingleArray);
      Nan::SetPrototypeMethod(localRef, "getDoubleArray", GetDoubleArray);
      Nan::SetPrototypeMethod(localRef, "getChar16Array", GetChar16Array);
      Nan::SetPrototypeMethod(localRef, "getBooleanArray", GetBooleanArray);
      Nan::SetPrototypeMethod(localRef, "getStringArray", GetStringArray);
      Nan::SetPrototypeMethod(localRef, "getInspectableArray", GetInspectableArray);
      Nan::SetPrototypeMethod(localRef, "getGuidArray", GetGuidArray);
      Nan::SetPrototypeMethod(localRef, "getDateTimeArray", GetDateTimeArray);
      Nan::SetPrototypeMethod(localRef, "getTimeSpanArray", GetTimeSpanArray);
      Nan::SetPrototypeMethod(localRef, "getPointArray", GetPointArray);
      Nan::SetPrototypeMethod(localRef, "getSizeArray", GetSizeArray);
      Nan::SetPrototypeMethod(localRef, "getRectArray", GetRectArray);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isNumericScalar").ToLocalChecked(), IsNumericScalarGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("type").ToLocalChecked(), TypeGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IPropertyValue").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IPropertyValue(::Windows::Foundation::IPropertyValue^ instance)
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
      
      ::Windows::Foundation::IPropertyValue^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::IPropertyValue^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IPropertyValue *wrapperInstance = new IPropertyValue(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::IPropertyValue^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::IPropertyValue^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIPropertyValue(winRtInstance));
    }


  
    static void GetUInt8(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned char result;
          result = wrapper->_instance->GetUInt8();
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
    static void GetInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          short result;
          result = wrapper->_instance->GetInt16();
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
    static void GetUInt16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned short result;
          result = wrapper->_instance->GetUInt16();
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
    static void GetInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          int result;
          result = wrapper->_instance->GetInt32();
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
    static void GetUInt32(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned int result;
          result = wrapper->_instance->GetUInt32();
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
    static void GetInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          __int64 result;
          result = wrapper->_instance->GetInt64();
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
    static void GetUInt64(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          unsigned __int64 result;
          result = wrapper->_instance->GetUInt64();
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
    static void GetSingle(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          float result;
          result = wrapper->_instance->GetSingle();
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
    static void GetDouble(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          double result;
          result = wrapper->_instance->GetDouble();
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
    static void GetChar16(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wchar_t result;
          result = wrapper->_instance->GetChar16();
          info.GetReturnValue().Set(NodeRT::Utils::JsStringFromChar(result));
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
    static void GetBoolean(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->GetBoolean();
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
    static void GetString(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetString();
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
    static void GetGuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Guid result;
          result = wrapper->_instance->GetGuid();
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
    static void GetDateTime(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::DateTime result;
          result = wrapper->_instance->GetDateTime();
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
    static void GetTimeSpan(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::TimeSpan result;
          result = wrapper->_instance->GetTimeSpan();
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
    static void GetPoint(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Point result;
          result = wrapper->_instance->GetPoint();
          info.GetReturnValue().Set(NodeRT::Utils::PointToJs(result));
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
    static void GetSize(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Size result;
          result = wrapper->_instance->GetSize();
          info.GetReturnValue().Set(NodeRT::Utils::SizeToJs(result));
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
    static void GetRect(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Rect result;
          result = wrapper->_instance->GetRect();
          info.GetReturnValue().Set(NodeRT::Utils::RectToJs(result));
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
    static void GetUInt8Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<unsigned char>^ arg0;
          
          wrapper->_instance->GetUInt8Array(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<unsigned char>::CreateArrayWrapper(arg0, 
            [](unsigned char val) -> Local<Value> {
              return Nan::New<Integer>(val);
            },
            [](Local<Value> value) -> bool {
              return value->IsInt32();
            },
            [](Local<Value> value) -> unsigned char {
              return static_cast<unsigned char>(Nan::To<int32_t>(value).FromMaybe(0));
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetInt16Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<short>^ arg0;
          
          wrapper->_instance->GetInt16Array(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<short>::CreateArrayWrapper(arg0, 
            [](short val) -> Local<Value> {
              return Nan::New<Integer>(val);
            },
            [](Local<Value> value) -> bool {
              return value->IsInt32();
            },
            [](Local<Value> value) -> short {
              return static_cast<short>(Nan::To<int32_t>(value).FromMaybe(0));
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetUInt16Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<unsigned short>^ arg0;
          
          wrapper->_instance->GetUInt16Array(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<unsigned short>::CreateArrayWrapper(arg0, 
            [](unsigned short val) -> Local<Value> {
              return Nan::New<Integer>(val);
            },
            [](Local<Value> value) -> bool {
              return value->IsInt32();
            },
            [](Local<Value> value) -> unsigned short {
              return static_cast<unsigned short>(Nan::To<int32_t>(value).FromMaybe(0));
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetInt32Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<int>^ arg0;
          
          wrapper->_instance->GetInt32Array(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<int>::CreateArrayWrapper(arg0, 
            [](int val) -> Local<Value> {
              return Nan::New<Integer>(val);
            },
            [](Local<Value> value) -> bool {
              return value->IsInt32();
            },
            [](Local<Value> value) -> int {
              return static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetUInt32Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<unsigned int>^ arg0;
          
          wrapper->_instance->GetUInt32Array(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<unsigned int>::CreateArrayWrapper(arg0, 
            [](unsigned int val) -> Local<Value> {
              return Nan::New<Integer>(val);
            },
            [](Local<Value> value) -> bool {
              return value->IsUint32();
            },
            [](Local<Value> value) -> unsigned int {
              return static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetInt64Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<__int64>^ arg0;
          
          wrapper->_instance->GetInt64Array(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<__int64>::CreateArrayWrapper(arg0, 
            [](__int64 val) -> Local<Value> {
              return Nan::New<Number>(static_cast<double>(val));
            },
            [](Local<Value> value) -> bool {
              return value->IsNumber();
            },
            [](Local<Value> value) -> __int64 {
              return Nan::To<int64_t>(value).FromMaybe(0);
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetUInt64Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<unsigned __int64>^ arg0;
          
          wrapper->_instance->GetUInt64Array(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<unsigned __int64>::CreateArrayWrapper(arg0, 
            [](unsigned __int64 val) -> Local<Value> {
              return Nan::New<Number>(static_cast<double>(val));
            },
            [](Local<Value> value) -> bool {
              return value->IsNumber();
            },
            [](Local<Value> value) -> unsigned __int64 {
              return static_cast<unsigned __int64>(Nan::To<int64_t>(value).FromMaybe(0));
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetSingleArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<float>^ arg0;
          
          wrapper->_instance->GetSingleArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<float>::CreateArrayWrapper(arg0, 
            [](float val) -> Local<Value> {
              return Nan::New<Number>(static_cast<double>(val));
            },
            [](Local<Value> value) -> bool {
              return value->IsNumber();
            },
            [](Local<Value> value) -> float {
              return static_cast<float>(Nan::To<double>(value).FromMaybe(0.0));
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetDoubleArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<double>^ arg0;
          
          wrapper->_instance->GetDoubleArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<double>::CreateArrayWrapper(arg0, 
            [](double val) -> Local<Value> {
              return Nan::New<Number>(static_cast<double>(val));
            },
            [](Local<Value> value) -> bool {
              return value->IsNumber();
            },
            [](Local<Value> value) -> double {
              return Nan::To<double>(value).FromMaybe(0.0);
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetChar16Array(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<wchar_t>^ arg0;
          
          wrapper->_instance->GetChar16Array(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<wchar_t>::CreateArrayWrapper(arg0, 
            [](wchar_t val) -> Local<Value> {
              return NodeRT::Utils::JsStringFromChar(val);
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> wchar_t {
              return NodeRT::Utils::GetFirstChar(value);
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetBooleanArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<bool>^ arg0;
          
          wrapper->_instance->GetBooleanArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<bool>::CreateArrayWrapper(arg0, 
            [](bool val) -> Local<Value> {
              return Nan::New<Boolean>(val);
            },
            [](Local<Value> value) -> bool {
              return value->IsBoolean();
            },
            [](Local<Value> value) -> bool {
              return Nan::To<bool>(value).FromMaybe(false);
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetStringArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<::Platform::String^>^ arg0;
          
          wrapper->_instance->GetStringArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<::Platform::String^>::CreateArrayWrapper(arg0, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetInspectableArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<::Platform::Object^>^ arg0;
          
          wrapper->_instance->GetInspectableArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<::Platform::Object^>::CreateArrayWrapper(arg0, 
            [](::Platform::Object^ val) -> Local<Value> {
              return CreateOpaqueWrapper(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(value);
            },
            [](Local<Value> value) -> ::Platform::Object^ {
              return dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(value));
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetGuidArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<::Platform::Guid>^ arg0;
          
          wrapper->_instance->GetGuidArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<::Platform::Guid>::CreateArrayWrapper(arg0, 
            [](::Platform::Guid val) -> Local<Value> {
              return NodeRT::Utils::GuidToJs(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsGuid(value);
            },
            [](Local<Value> value) -> ::Platform::Guid {
              return NodeRT::Utils::GuidFromJs(value);
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetDateTimeArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<::Windows::Foundation::DateTime>^ arg0;
          
          wrapper->_instance->GetDateTimeArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<::Windows::Foundation::DateTime>::CreateArrayWrapper(arg0, 
            [](::Windows::Foundation::DateTime val) -> Local<Value> {
              return NodeRT::Utils::DateTimeToJS(val);
            },
            [](Local<Value> value) -> bool {
              return value->IsDate();
            },
            [](Local<Value> value) -> ::Windows::Foundation::DateTime {
              return NodeRT::Utils::DateTimeFromJSDate(value);
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetTimeSpanArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<::Windows::Foundation::TimeSpan>^ arg0;
          
          wrapper->_instance->GetTimeSpanArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<::Windows::Foundation::TimeSpan>::CreateArrayWrapper(arg0, 
            [](::Windows::Foundation::TimeSpan val) -> Local<Value> {
              return Nan::New<Number>(val.Duration/10000.0);
            },
            [](Local<Value> value) -> bool {
              return value->IsNumber();
            },
            [](Local<Value> value) -> ::Windows::Foundation::TimeSpan {
              return NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetPointArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<::Windows::Foundation::Point>^ arg0;
          
          wrapper->_instance->GetPointArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<::Windows::Foundation::Point>::CreateArrayWrapper(arg0, 
            [](::Windows::Foundation::Point val) -> Local<Value> {
              return NodeRT::Utils::PointToJs(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsPoint(value);
            },
            [](Local<Value> value) -> ::Windows::Foundation::Point {
              return NodeRT::Utils::PointFromJs(value);
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetSizeArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<::Windows::Foundation::Size>^ arg0;
          
          wrapper->_instance->GetSizeArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<::Windows::Foundation::Size>::CreateArrayWrapper(arg0, 
            [](::Windows::Foundation::Size val) -> Local<Value> {
              return NodeRT::Utils::SizeToJs(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsSize(value);
            },
            [](Local<Value> value) -> ::Windows::Foundation::Size {
              return NodeRT::Utils::SizeFromJs(value);
            }
          ));
          info.GetReturnValue().Set(resObj);
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
    static void GetRectArray(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<::Windows::Foundation::Rect>^ arg0;
          
          wrapper->_instance->GetRectArray(&arg0);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("value").ToLocalChecked(), NodeRT::Collections::ArrayWrapper<::Windows::Foundation::Rect>::CreateArrayWrapper(arg0, 
            [](::Windows::Foundation::Rect val) -> Local<Value> {
              return NodeRT::Utils::RectToJs(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsRect(value);
            },
            [](Local<Value> value) -> ::Windows::Foundation::Rect {
              return NodeRT::Utils::RectFromJs(value);
            }
          ));
          info.GetReturnValue().Set(resObj);
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



    static void IsNumericScalarGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsNumericScalar;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::IPropertyValue^>(info.This()))
      {
        return;
      }

      IPropertyValue *wrapper = IPropertyValue::Unwrap<IPropertyValue>(info.This());

      try 
      {
        ::Windows::Foundation::PropertyType result = wrapper->_instance->Type;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Foundation::IPropertyValue^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIPropertyValue(::Windows::Foundation::IPropertyValue^ wintRtInstance);
    friend ::Windows::Foundation::IPropertyValue^ UnwrapIPropertyValue(Local<Value> value);
  };
  Persistent<FunctionTemplate> IPropertyValue::s_constructorTemplate;

  v8::Local<v8::Value> WrapIPropertyValue(::Windows::Foundation::IPropertyValue^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IPropertyValue::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::IPropertyValue^ UnwrapIPropertyValue(Local<Value> value)
  {
     return IPropertyValue::Unwrap<IPropertyValue>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIPropertyValue(Local<Object> exports)
  {
    IPropertyValue::Init(exports);
  }

  class Uri : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Uri").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "equals", Equals);
      Nan::SetPrototypeMethod(localRef, "combineUri", CombineUri);
      Nan::SetPrototypeMethod(localRef, "toString", ToString);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("absoluteUri").ToLocalChecked(), AbsoluteUriGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayUri").ToLocalChecked(), DisplayUriGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("domain").ToLocalChecked(), DomainGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extension").ToLocalChecked(), ExtensionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("fragment").ToLocalChecked(), FragmentGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("host").ToLocalChecked(), HostGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("password").ToLocalChecked(), PasswordGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("path").ToLocalChecked(), PathGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("port").ToLocalChecked(), PortGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("query").ToLocalChecked(), QueryGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("queryParsed").ToLocalChecked(), QueryParsedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("rawUri").ToLocalChecked(), RawUriGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("schemeName").ToLocalChecked(), SchemeNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("suspicious").ToLocalChecked(), SuspiciousGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userName").ToLocalChecked(), UserNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("absoluteCanonicalUri").ToLocalChecked(), AbsoluteCanonicalUriGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayIri").ToLocalChecked(), DisplayIriGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "unescapeComponent", UnescapeComponent);
      Nan::SetMethod(constructor, "escapeComponent", EscapeComponent);

      Nan::Set(exports, Nan::New<String>("Uri").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Uri(::Windows::Foundation::Uri^ instance)
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
      
      ::Windows::Foundation::Uri^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Foundation::Uri^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          winRtInstance = ref new ::Windows::Foundation::Uri(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          winRtInstance = ref new ::Windows::Foundation::Uri(arg0,arg1);
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

      Uri *wrapperInstance = new Uri(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Foundation::Uri^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Foundation::Uri^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapUri(winRtInstance));
    }


  
    static void Equals(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          bool result;
          result = wrapper->_instance->Equals(arg0);
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
    static void CombineUri(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Foundation::Uri^ result;
          result = wrapper->_instance->CombineUri(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
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
    static void ToString(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->ToString();
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


    static void UnescapeComponent(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          Platform::String^ result;
          result = ::Windows::Foundation::Uri::UnescapeComponent(arg0);
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
    static void EscapeComponent(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          Platform::String^ result;
          result = ::Windows::Foundation::Uri::EscapeComponent(arg0);
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

    static void AbsoluteUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->AbsoluteUri;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DisplayUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->DisplayUri;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DomainGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Domain;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ExtensionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Extension;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void FragmentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Fragment;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HostGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Host;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PasswordGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Password;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PathGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Path;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PortGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        int result = wrapper->_instance->Port;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void QueryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Query;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void QueryParsedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        ::Windows::Foundation::WwwFormUrlDecoder^ result = wrapper->_instance->QueryParsed;
        info.GetReturnValue().Set(WrapWwwFormUrlDecoder(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RawUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->RawUri;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SchemeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->SchemeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SuspiciousGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        bool result = wrapper->_instance->Suspicious;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UserNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->UserName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AbsoluteCanonicalUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->AbsoluteCanonicalUri;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DisplayIriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info.This()))
      {
        return;
      }

      Uri *wrapper = Uri::Unwrap<Uri>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->DisplayIri;
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
    ::Windows::Foundation::Uri^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapUri(::Windows::Foundation::Uri^ wintRtInstance);
    friend ::Windows::Foundation::Uri^ UnwrapUri(Local<Value> value);
  };
  Persistent<FunctionTemplate> Uri::s_constructorTemplate;

  v8::Local<v8::Value> WrapUri(::Windows::Foundation::Uri^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Uri::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Foundation::Uri^ UnwrapUri(Local<Value> value)
  {
     return Uri::Unwrap<Uri>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitUri(Local<Object> exports)
  {
    Uri::Init(exports);
  }

} } } 

NAN_MODULE_INIT(init)
{
  // we ignore failures for now since it probably means that the initialization already happened for STA, and that's cool
  CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  //if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
  /*{
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }*/
  
  NodeRT::Windows::Foundation::InitPropertyTypeEnum(target);
  NodeRT::Windows::Foundation::InitAsyncStatusEnum(target);
  NodeRT::Windows::Foundation::InitPropertyValue(target);
  NodeRT::Windows::Foundation::InitIStringable(target);
  NodeRT::Windows::Foundation::InitDeferral(target);
  NodeRT::Windows::Foundation::InitIAsyncInfo(target);
  NodeRT::Windows::Foundation::InitIAsyncAction(target);
  NodeRT::Windows::Foundation::InitIMemoryBufferReference(target);
  NodeRT::Windows::Foundation::InitIMemoryBuffer(target);
  NodeRT::Windows::Foundation::InitMemoryBuffer(target);
  NodeRT::Windows::Foundation::InitWwwFormUrlDecoder(target);
  NodeRT::Windows::Foundation::InitIWwwFormUrlDecoderEntry(target);
  NodeRT::Windows::Foundation::InitWwwFormUrlDecoderEntry(target);
  NodeRT::Windows::Foundation::InitIGetActivationFactory(target);
  NodeRT::Windows::Foundation::InitIPropertyValue(target);
  NodeRT::Windows::Foundation::InitUri(target);

  NodeRT::Utils::RegisterNameSpace("Windows.Foundation", target);
}


NODE_MODULE(binding, init)