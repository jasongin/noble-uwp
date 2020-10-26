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

namespace NodeRT { namespace Windows { namespace Devices { namespace Bluetooth { namespace Advertisement { 

  v8::Local<v8::Value> WrapBluetoothLEManufacturerData(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ UnwrapBluetoothLEManufacturerData(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAdvertisementDataSection(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ UnwrapBluetoothLEAdvertisementDataSection(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAdvertisement(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ UnwrapBluetoothLEAdvertisement(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAdvertisementBytePattern(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ UnwrapBluetoothLEAdvertisementBytePattern(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAdvertisementFilter(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ UnwrapBluetoothLEAdvertisementFilter(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAdvertisementWatcherStoppedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ UnwrapBluetoothLEAdvertisementWatcherStoppedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAdvertisementWatcher(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ UnwrapBluetoothLEAdvertisementWatcher(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAdvertisementReceivedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ UnwrapBluetoothLEAdvertisementReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAdvertisementDataTypes(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^ UnwrapBluetoothLEAdvertisementDataTypes(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAdvertisementPublisherStatusChangedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ UnwrapBluetoothLEAdvertisementPublisherStatusChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAdvertisementPublisher(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ wintRtInstance);
  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ UnwrapBluetoothLEAdvertisementPublisher(Local<Value> value);
  


  static void InitBluetoothLEScanningModeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothLEScanningMode").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("passive").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEScanningMode::Passive)));
	Nan::Set(enumObject, Nan::New<String>("active").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEScanningMode::Active)));
  }


  static void InitBluetoothLEAdvertisementFlagsEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementFlags").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFlags::None)));
	Nan::Set(enumObject, Nan::New<String>("limitedDiscoverableMode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFlags::LimitedDiscoverableMode)));
	Nan::Set(enumObject, Nan::New<String>("generalDiscoverableMode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFlags::GeneralDiscoverableMode)));
	Nan::Set(enumObject, Nan::New<String>("classicNotSupported").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFlags::ClassicNotSupported)));
	Nan::Set(enumObject, Nan::New<String>("dualModeControllerCapable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFlags::DualModeControllerCapable)));
	Nan::Set(enumObject, Nan::New<String>("dualModeHostCapable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFlags::DualModeHostCapable)));
  }


  static void InitBluetoothLEAdvertisementTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("connectableUndirected").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementType::ConnectableUndirected)));
	Nan::Set(enumObject, Nan::New<String>("connectableDirected").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementType::ConnectableDirected)));
	Nan::Set(enumObject, Nan::New<String>("scannableUndirected").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementType::ScannableUndirected)));
	Nan::Set(enumObject, Nan::New<String>("nonConnectableUndirected").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementType::NonConnectableUndirected)));
	Nan::Set(enumObject, Nan::New<String>("scanResponse").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementType::ScanResponse)));
  }


  static void InitBluetoothLEAdvertisementWatcherStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementWatcherStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("created").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStatus::Created)));
	Nan::Set(enumObject, Nan::New<String>("started").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStatus::Started)));
	Nan::Set(enumObject, Nan::New<String>("stopping").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStatus::Stopping)));
	Nan::Set(enumObject, Nan::New<String>("stopped").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStatus::Stopped)));
	Nan::Set(enumObject, Nan::New<String>("aborted").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStatus::Aborted)));
  }


  static void InitBluetoothLEAdvertisementPublisherStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementPublisherStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("created").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatus::Created)));
	Nan::Set(enumObject, Nan::New<String>("waiting").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatus::Waiting)));
	Nan::Set(enumObject, Nan::New<String>("started").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatus::Started)));
	Nan::Set(enumObject, Nan::New<String>("stopping").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatus::Stopping)));
	Nan::Set(enumObject, Nan::New<String>("stopped").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatus::Stopped)));
	Nan::Set(enumObject, Nan::New<String>("aborted").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatus::Aborted)));
  }



  
  class BluetoothLEManufacturerData : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEManufacturerData").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("data").ToLocalChecked(), DataGetter, DataSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("companyId").ToLocalChecked(), CompanyIdGetter, CompanyIdSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothLEManufacturerData").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEManufacturerData(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[1]))
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Storage::Streams::IBuffer^ arg1 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData(arg0,arg1);
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

      BluetoothLEManufacturerData *wrapperInstance = new BluetoothLEManufacturerData(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEManufacturerData(winRtInstance));
    }


  



    static void DataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>(info.This()))
      {
        return;
      }

      BluetoothLEManufacturerData *wrapper = BluetoothLEManufacturerData::Unwrap<BluetoothLEManufacturerData>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->Data;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DataSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>(info.This()))
      {
        return;
      }

      BluetoothLEManufacturerData *wrapper = BluetoothLEManufacturerData::Unwrap<BluetoothLEManufacturerData>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::IBuffer^ winRtValue = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Data = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void CompanyIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>(info.This()))
      {
        return;
      }

      BluetoothLEManufacturerData *wrapper = BluetoothLEManufacturerData::Unwrap<BluetoothLEManufacturerData>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->CompanyId;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CompanyIdSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>(info.This()))
      {
        return;
      }

      BluetoothLEManufacturerData *wrapper = BluetoothLEManufacturerData::Unwrap<BluetoothLEManufacturerData>(info.This());

      try 
      {
        
        unsigned short winRtValue = static_cast<unsigned short>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->CompanyId = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEManufacturerData(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ UnwrapBluetoothLEManufacturerData(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEManufacturerData::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEManufacturerData(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEManufacturerData::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ UnwrapBluetoothLEManufacturerData(Local<Value> value)
  {
     return BluetoothLEManufacturerData::Unwrap<BluetoothLEManufacturerData>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEManufacturerData(Local<Object> exports)
  {
    BluetoothLEManufacturerData::Init(exports);
  }

  class BluetoothLEAdvertisementDataSection : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAdvertisementDataSection").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dataType").ToLocalChecked(), DataTypeGetter, DataTypeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("data").ToLocalChecked(), DataGetter, DataSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementDataSection").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAdvertisementDataSection(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[1]))
      {
        try
        {
          unsigned char arg0 = static_cast<unsigned char>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Storage::Streams::IBuffer^ arg1 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection(arg0,arg1);
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

      BluetoothLEAdvertisementDataSection *wrapperInstance = new BluetoothLEAdvertisementDataSection(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAdvertisementDataSection(winRtInstance));
    }


  



    static void DataTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementDataSection *wrapper = BluetoothLEAdvertisementDataSection::Unwrap<BluetoothLEAdvertisementDataSection>(info.This());

      try 
      {
        unsigned char result = wrapper->_instance->DataType;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DataTypeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementDataSection *wrapper = BluetoothLEAdvertisementDataSection::Unwrap<BluetoothLEAdvertisementDataSection>(info.This());

      try 
      {
        
        unsigned char winRtValue = static_cast<unsigned char>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->DataType = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void DataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementDataSection *wrapper = BluetoothLEAdvertisementDataSection::Unwrap<BluetoothLEAdvertisementDataSection>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->Data;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DataSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementDataSection *wrapper = BluetoothLEAdvertisementDataSection::Unwrap<BluetoothLEAdvertisementDataSection>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::IBuffer^ winRtValue = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Data = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAdvertisementDataSection(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ UnwrapBluetoothLEAdvertisementDataSection(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAdvertisementDataSection::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAdvertisementDataSection(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAdvertisementDataSection::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ UnwrapBluetoothLEAdvertisementDataSection(Local<Value> value)
  {
     return BluetoothLEAdvertisementDataSection::Unwrap<BluetoothLEAdvertisementDataSection>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAdvertisementDataSection(Local<Object> exports)
  {
    BluetoothLEAdvertisementDataSection::Init(exports);
  }

  class BluetoothLEAdvertisement : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAdvertisement").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getManufacturerDataByCompanyId", GetManufacturerDataByCompanyId);
      Nan::SetPrototypeMethod(localRef, "getSectionsByType", GetSectionsByType);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localName").ToLocalChecked(), LocalNameGetter, LocalNameSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("flags").ToLocalChecked(), FlagsGetter, FlagsSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dataSections").ToLocalChecked(), DataSectionsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("manufacturerData").ToLocalChecked(), ManufacturerDataGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("serviceUuids").ToLocalChecked(), ServiceUuidsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisement").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAdvertisement(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement();
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

      BluetoothLEAdvertisement *wrapperInstance = new BluetoothLEAdvertisement(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAdvertisement(winRtInstance));
    }


  
    static void GetManufacturerDataByCompanyId(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisement *wrapper = BluetoothLEAdvertisement::Unwrap<BluetoothLEAdvertisement>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>^ result;
          result = wrapper->_instance->GetManufacturerDataByCompanyId(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ val) -> Local<Value> {
              return WrapBluetoothLEManufacturerData(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ {
              return UnwrapBluetoothLEManufacturerData(value);
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
    static void GetSectionsByType(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisement *wrapper = BluetoothLEAdvertisement::Unwrap<BluetoothLEAdvertisement>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned char arg0 = static_cast<unsigned char>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>^ result;
          result = wrapper->_instance->GetSectionsByType(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ val) -> Local<Value> {
              return WrapBluetoothLEAdvertisementDataSection(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ {
              return UnwrapBluetoothLEAdvertisementDataSection(value);
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



    static void LocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisement *wrapper = BluetoothLEAdvertisement::Unwrap<BluetoothLEAdvertisement>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->LocalName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LocalNameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisement *wrapper = BluetoothLEAdvertisement::Unwrap<BluetoothLEAdvertisement>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->LocalName = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void FlagsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisement *wrapper = BluetoothLEAdvertisement::Unwrap<BluetoothLEAdvertisement>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFlags>^ result = wrapper->_instance->Flags;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(static_cast<int>(result->Value))) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void FlagsSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisement *wrapper = BluetoothLEAdvertisement::Unwrap<BluetoothLEAdvertisement>(info.This());

      try 
      {
        
        ::Platform::IBox<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFlags>^ winRtValue = ref new ::Platform::Box<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFlags>(static_cast<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFlags>(Nan::To<int32_t>(value).FromMaybe(0)));

        wrapper->_instance->Flags = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void DataSectionsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisement *wrapper = BluetoothLEAdvertisement::Unwrap<BluetoothLEAdvertisement>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVector<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>^ result = wrapper->_instance->DataSections;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>::CreateVectorWrapper(result, 
            [](::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ val) -> Local<Value> {
              return WrapBluetoothLEAdvertisementDataSection(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataSection^ {
              return UnwrapBluetoothLEAdvertisementDataSection(value);
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
    
    static void ManufacturerDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisement *wrapper = BluetoothLEAdvertisement::Unwrap<BluetoothLEAdvertisement>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVector<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>^ result = wrapper->_instance->ManufacturerData;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>::CreateVectorWrapper(result, 
            [](::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ val) -> Local<Value> {
              return WrapBluetoothLEManufacturerData(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEManufacturerData^ {
              return UnwrapBluetoothLEManufacturerData(value);
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
    
    static void ServiceUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisement *wrapper = BluetoothLEAdvertisement::Unwrap<BluetoothLEAdvertisement>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVector<::Platform::Guid>^ result = wrapper->_instance->ServiceUuids;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Platform::Guid>::CreateVectorWrapper(result, 
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
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAdvertisement(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ UnwrapBluetoothLEAdvertisement(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAdvertisement::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAdvertisement(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAdvertisement::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ UnwrapBluetoothLEAdvertisement(Local<Value> value)
  {
     return BluetoothLEAdvertisement::Unwrap<BluetoothLEAdvertisement>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAdvertisement(Local<Object> exports)
  {
    BluetoothLEAdvertisement::Init(exports);
  }

  class BluetoothLEAdvertisementBytePattern : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAdvertisementBytePattern").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("offset").ToLocalChecked(), OffsetGetter, OffsetSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dataType").ToLocalChecked(), DataTypeGetter, DataTypeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("data").ToLocalChecked(), DataGetter, DataSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementBytePattern").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAdvertisementBytePattern(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[2]))
      {
        try
        {
          unsigned char arg0 = static_cast<unsigned char>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          short arg1 = static_cast<short>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::Streams::IBuffer^ arg2 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[2]));
          
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern(arg0,arg1,arg2);
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

      BluetoothLEAdvertisementBytePattern *wrapperInstance = new BluetoothLEAdvertisementBytePattern(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAdvertisementBytePattern(winRtInstance));
    }


  



    static void OffsetGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementBytePattern *wrapper = BluetoothLEAdvertisementBytePattern::Unwrap<BluetoothLEAdvertisementBytePattern>(info.This());

      try 
      {
        short result = wrapper->_instance->Offset;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void OffsetSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementBytePattern *wrapper = BluetoothLEAdvertisementBytePattern::Unwrap<BluetoothLEAdvertisementBytePattern>(info.This());

      try 
      {
        
        short winRtValue = static_cast<short>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Offset = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void DataTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementBytePattern *wrapper = BluetoothLEAdvertisementBytePattern::Unwrap<BluetoothLEAdvertisementBytePattern>(info.This());

      try 
      {
        unsigned char result = wrapper->_instance->DataType;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DataTypeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementBytePattern *wrapper = BluetoothLEAdvertisementBytePattern::Unwrap<BluetoothLEAdvertisementBytePattern>(info.This());

      try 
      {
        
        unsigned char winRtValue = static_cast<unsigned char>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->DataType = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void DataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementBytePattern *wrapper = BluetoothLEAdvertisementBytePattern::Unwrap<BluetoothLEAdvertisementBytePattern>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->Data;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DataSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementBytePattern *wrapper = BluetoothLEAdvertisementBytePattern::Unwrap<BluetoothLEAdvertisementBytePattern>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::IBuffer^ winRtValue = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Data = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAdvertisementBytePattern(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ UnwrapBluetoothLEAdvertisementBytePattern(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAdvertisementBytePattern::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAdvertisementBytePattern(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAdvertisementBytePattern::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ UnwrapBluetoothLEAdvertisementBytePattern(Local<Value> value)
  {
     return BluetoothLEAdvertisementBytePattern::Unwrap<BluetoothLEAdvertisementBytePattern>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAdvertisementBytePattern(Local<Object> exports)
  {
    BluetoothLEAdvertisementBytePattern::Init(exports);
  }

  class BluetoothLEAdvertisementFilter : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAdvertisementFilter").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("advertisement").ToLocalChecked(), AdvertisementGetter, AdvertisementSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bytePatterns").ToLocalChecked(), BytePatternsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementFilter").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAdvertisementFilter(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter();
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

      BluetoothLEAdvertisementFilter *wrapperInstance = new BluetoothLEAdvertisementFilter(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAdvertisementFilter(winRtInstance));
    }


  



    static void AdvertisementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementFilter *wrapper = BluetoothLEAdvertisementFilter::Unwrap<BluetoothLEAdvertisementFilter>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ result = wrapper->_instance->Advertisement;
        info.GetReturnValue().Set(WrapBluetoothLEAdvertisement(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AdvertisementSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementFilter *wrapper = BluetoothLEAdvertisementFilter::Unwrap<BluetoothLEAdvertisementFilter>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ winRtValue = dynamic_cast<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Advertisement = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void BytePatternsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementFilter *wrapper = BluetoothLEAdvertisementFilter::Unwrap<BluetoothLEAdvertisementFilter>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVector<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>^ result = wrapper->_instance->BytePatterns;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>::CreateVectorWrapper(result, 
            [](::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ val) -> Local<Value> {
              return WrapBluetoothLEAdvertisementBytePattern(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementBytePattern^ {
              return UnwrapBluetoothLEAdvertisementBytePattern(value);
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
    


  private:
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAdvertisementFilter(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ UnwrapBluetoothLEAdvertisementFilter(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAdvertisementFilter::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAdvertisementFilter(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAdvertisementFilter::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ UnwrapBluetoothLEAdvertisementFilter(Local<Value> value)
  {
     return BluetoothLEAdvertisementFilter::Unwrap<BluetoothLEAdvertisementFilter>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAdvertisementFilter(Local<Object> exports)
  {
    BluetoothLEAdvertisementFilter::Init(exports);
  }

  class BluetoothLEAdvertisementWatcherStoppedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAdvertisementWatcherStoppedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("error").ToLocalChecked(), ErrorGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementWatcherStoppedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAdvertisementWatcherStoppedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothLEAdvertisementWatcherStoppedEventArgs *wrapperInstance = new BluetoothLEAdvertisementWatcherStoppedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAdvertisementWatcherStoppedEventArgs(winRtInstance));
    }


  



    static void ErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcherStoppedEventArgs *wrapper = BluetoothLEAdvertisementWatcherStoppedEventArgs::Unwrap<BluetoothLEAdvertisementWatcherStoppedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothError result = wrapper->_instance->Error;
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
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAdvertisementWatcherStoppedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ UnwrapBluetoothLEAdvertisementWatcherStoppedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAdvertisementWatcherStoppedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAdvertisementWatcherStoppedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAdvertisementWatcherStoppedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ UnwrapBluetoothLEAdvertisementWatcherStoppedEventArgs(Local<Value> value)
  {
     return BluetoothLEAdvertisementWatcherStoppedEventArgs::Unwrap<BluetoothLEAdvertisementWatcherStoppedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAdvertisementWatcherStoppedEventArgs(Local<Object> exports)
  {
    BluetoothLEAdvertisementWatcherStoppedEventArgs::Init(exports);
  }

  class BluetoothLEAdvertisementWatcher : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAdvertisementWatcher").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "start", Start);
      Nan::SetPrototypeMethod(localRef, "stop", Stop);
      
                  
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("signalStrengthFilter").ToLocalChecked(), SignalStrengthFilterGetter, SignalStrengthFilterSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("scanningMode").ToLocalChecked(), ScanningModeGetter, ScanningModeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("advertisementFilter").ToLocalChecked(), AdvertisementFilterGetter, AdvertisementFilterSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maxOutOfRangeTimeout").ToLocalChecked(), MaxOutOfRangeTimeoutGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maxSamplingInterval").ToLocalChecked(), MaxSamplingIntervalGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("minOutOfRangeTimeout").ToLocalChecked(), MinOutOfRangeTimeoutGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("minSamplingInterval").ToLocalChecked(), MinSamplingIntervalGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementWatcher").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAdvertisementWatcher(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^>(info[0]))
      {
        try
        {
          ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ arg0 = UnwrapBluetoothLEAdvertisementFilter(info[0]);
          
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher(arg0);
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

      BluetoothLEAdvertisementWatcher *wrapperInstance = new BluetoothLEAdvertisementWatcher(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAdvertisementWatcher(winRtInstance));
    }


  
    static void Start(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Start();
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
    static void Stop(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Stop();
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



    static void SignalStrengthFilterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ result = wrapper->_instance->SignalStrengthFilter;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Bluetooth", "BluetoothSignalStrengthFilter", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SignalStrengthFilterSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ winRtValue = dynamic_cast<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->SignalStrengthFilter = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ScanningModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEScanningMode result = wrapper->_instance->ScanningMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ScanningModeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEScanningMode winRtValue = static_cast<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEScanningMode>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ScanningMode = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void AdvertisementFilterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ result = wrapper->_instance->AdvertisementFilter;
        info.GetReturnValue().Set(WrapBluetoothLEAdvertisementFilter(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AdvertisementFilterSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^ winRtValue = dynamic_cast<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementFilter^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->AdvertisementFilter = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void MaxOutOfRangeTimeoutGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->MaxOutOfRangeTimeout;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MaxSamplingIntervalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->MaxSamplingInterval;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MinOutOfRangeTimeoutGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->MinOutOfRangeTimeout;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MinSamplingIntervalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->MinSamplingInterval;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"received", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());
      
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

          registrationToken = wrapper->_instance->Received::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^, ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ arg0, ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapBluetoothLEAdvertisementWatcher(arg0);
                  wrappedArg1 = WrapBluetoothLEAdvertisementReceivedEventArgs(arg1);


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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"stopped", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());
      
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

          registrationToken = wrapper->_instance->Stopped::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^, ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ arg0, ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapBluetoothLEAdvertisementWatcher(arg0);
                  wrappedArg1 = WrapBluetoothLEAdvertisementWatcherStoppedEventArgs(arg1);


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

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"received", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"stopped", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"received", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());
          wrapper->_instance->Received::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"stopped", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          BluetoothLEAdvertisementWatcher *wrapper = BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(info.This());
          wrapper->_instance->Stopped::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAdvertisementWatcher(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ UnwrapBluetoothLEAdvertisementWatcher(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAdvertisementWatcher::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAdvertisementWatcher(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAdvertisementWatcher::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher^ UnwrapBluetoothLEAdvertisementWatcher(Local<Value> value)
  {
     return BluetoothLEAdvertisementWatcher::Unwrap<BluetoothLEAdvertisementWatcher>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAdvertisementWatcher(Local<Object> exports)
  {
    BluetoothLEAdvertisementWatcher::Init(exports);
  }

  class BluetoothLEAdvertisementReceivedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAdvertisementReceivedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("advertisement").ToLocalChecked(), AdvertisementGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("advertisementType").ToLocalChecked(), AdvertisementTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bluetoothAddress").ToLocalChecked(), BluetoothAddressGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("rawSignalStrengthInDBm").ToLocalChecked(), RawSignalStrengthInDBmGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("timestamp").ToLocalChecked(), TimestampGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementReceivedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAdvertisementReceivedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothLEAdvertisementReceivedEventArgs *wrapperInstance = new BluetoothLEAdvertisementReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAdvertisementReceivedEventArgs(winRtInstance));
    }


  



    static void AdvertisementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementReceivedEventArgs *wrapper = BluetoothLEAdvertisementReceivedEventArgs::Unwrap<BluetoothLEAdvertisementReceivedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ result = wrapper->_instance->Advertisement;
        info.GetReturnValue().Set(WrapBluetoothLEAdvertisement(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AdvertisementTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementReceivedEventArgs *wrapper = BluetoothLEAdvertisementReceivedEventArgs::Unwrap<BluetoothLEAdvertisementReceivedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementType result = wrapper->_instance->AdvertisementType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BluetoothAddressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementReceivedEventArgs *wrapper = BluetoothLEAdvertisementReceivedEventArgs::Unwrap<BluetoothLEAdvertisementReceivedEventArgs>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->BluetoothAddress;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RawSignalStrengthInDBmGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementReceivedEventArgs *wrapper = BluetoothLEAdvertisementReceivedEventArgs::Unwrap<BluetoothLEAdvertisementReceivedEventArgs>(info.This());

      try 
      {
        short result = wrapper->_instance->RawSignalStrengthInDBm;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TimestampGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementReceivedEventArgs *wrapper = BluetoothLEAdvertisementReceivedEventArgs::Unwrap<BluetoothLEAdvertisementReceivedEventArgs>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->Timestamp;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAdvertisementReceivedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ UnwrapBluetoothLEAdvertisementReceivedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAdvertisementReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAdvertisementReceivedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAdvertisementReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs^ UnwrapBluetoothLEAdvertisementReceivedEventArgs(Local<Value> value)
  {
     return BluetoothLEAdvertisementReceivedEventArgs::Unwrap<BluetoothLEAdvertisementReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAdvertisementReceivedEventArgs(Local<Object> exports)
  {
    BluetoothLEAdvertisementReceivedEventArgs::Init(exports);
  }

  class BluetoothLEAdvertisementDataTypes : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAdvertisementDataTypes").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("advertisingInterval").ToLocalChecked(), AdvertisingIntervalGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("appearance").ToLocalChecked(), AppearanceGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("completeLocalName").ToLocalChecked(), CompleteLocalNameGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("completeService128BitUuids").ToLocalChecked(), CompleteService128BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("completeService16BitUuids").ToLocalChecked(), CompleteService16BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("completeService32BitUuids").ToLocalChecked(), CompleteService32BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("flags").ToLocalChecked(), FlagsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("incompleteService128BitUuids").ToLocalChecked(), IncompleteService128BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("incompleteService16BitUuids").ToLocalChecked(), IncompleteService16BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("incompleteService32BitUuids").ToLocalChecked(), IncompleteService32BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("manufacturerSpecificData").ToLocalChecked(), ManufacturerSpecificDataGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("publicTargetAddress").ToLocalChecked(), PublicTargetAddressGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("randomTargetAddress").ToLocalChecked(), RandomTargetAddressGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("serviceData128BitUuids").ToLocalChecked(), ServiceData128BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("serviceData16BitUuids").ToLocalChecked(), ServiceData16BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("serviceData32BitUuids").ToLocalChecked(), ServiceData32BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("serviceSolicitation128BitUuids").ToLocalChecked(), ServiceSolicitation128BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("serviceSolicitation16BitUuids").ToLocalChecked(), ServiceSolicitation16BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("serviceSolicitation32BitUuids").ToLocalChecked(), ServiceSolicitation32BitUuidsGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("shortenedLocalName").ToLocalChecked(), ShortenedLocalNameGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("slaveConnectionIntervalRange").ToLocalChecked(), SlaveConnectionIntervalRangeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("txPowerLevel").ToLocalChecked(), TxPowerLevelGetter);

      Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementDataTypes").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAdvertisementDataTypes(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothLEAdvertisementDataTypes *wrapperInstance = new BluetoothLEAdvertisementDataTypes(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAdvertisementDataTypes(winRtInstance));
    }


  




    static void AdvertisingIntervalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::AdvertisingInterval;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AppearanceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::Appearance;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CompleteLocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::CompleteLocalName;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CompleteService128BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::CompleteService128BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CompleteService16BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::CompleteService16BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CompleteService32BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::CompleteService32BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void FlagsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::Flags;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IncompleteService128BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::IncompleteService128BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IncompleteService16BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::IncompleteService16BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IncompleteService32BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::IncompleteService32BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ManufacturerSpecificDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::ManufacturerSpecificData;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PublicTargetAddressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::PublicTargetAddress;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RandomTargetAddressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::RandomTargetAddress;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceData128BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::ServiceData128BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceData16BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::ServiceData16BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceData32BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::ServiceData32BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceSolicitation128BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::ServiceSolicitation128BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceSolicitation16BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::ServiceSolicitation16BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceSolicitation32BitUuidsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::ServiceSolicitation32BitUuids;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ShortenedLocalNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::ShortenedLocalName;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SlaveConnectionIntervalRangeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::SlaveConnectionIntervalRange;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TxPowerLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes::TxPowerLevel;
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
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAdvertisementDataTypes(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^ UnwrapBluetoothLEAdvertisementDataTypes(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAdvertisementDataTypes::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAdvertisementDataTypes(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAdvertisementDataTypes::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementDataTypes^ UnwrapBluetoothLEAdvertisementDataTypes(Local<Value> value)
  {
     return BluetoothLEAdvertisementDataTypes::Unwrap<BluetoothLEAdvertisementDataTypes>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAdvertisementDataTypes(Local<Object> exports)
  {
    BluetoothLEAdvertisementDataTypes::Init(exports);
  }

  class BluetoothLEAdvertisementPublisherStatusChangedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAdvertisementPublisherStatusChangedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("error").ToLocalChecked(), ErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementPublisherStatusChangedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAdvertisementPublisherStatusChangedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothLEAdvertisementPublisherStatusChangedEventArgs *wrapperInstance = new BluetoothLEAdvertisementPublisherStatusChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAdvertisementPublisherStatusChangedEventArgs(winRtInstance));
    }


  



    static void ErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementPublisherStatusChangedEventArgs *wrapper = BluetoothLEAdvertisementPublisherStatusChangedEventArgs::Unwrap<BluetoothLEAdvertisementPublisherStatusChangedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothError result = wrapper->_instance->Error;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementPublisherStatusChangedEventArgs *wrapper = BluetoothLEAdvertisementPublisherStatusChangedEventArgs::Unwrap<BluetoothLEAdvertisementPublisherStatusChangedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatus result = wrapper->_instance->Status;
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
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAdvertisementPublisherStatusChangedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ UnwrapBluetoothLEAdvertisementPublisherStatusChangedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAdvertisementPublisherStatusChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAdvertisementPublisherStatusChangedEventArgs(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAdvertisementPublisherStatusChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ UnwrapBluetoothLEAdvertisementPublisherStatusChangedEventArgs(Local<Value> value)
  {
     return BluetoothLEAdvertisementPublisherStatusChangedEventArgs::Unwrap<BluetoothLEAdvertisementPublisherStatusChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAdvertisementPublisherStatusChangedEventArgs(Local<Object> exports)
  {
    BluetoothLEAdvertisementPublisherStatusChangedEventArgs::Init(exports);
  }

  class BluetoothLEAdvertisementPublisher : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAdvertisementPublisher").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "start", Start);
      Nan::SetPrototypeMethod(localRef, "stop", Stop);
      
                  
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("advertisement").ToLocalChecked(), AdvertisementGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothLEAdvertisementPublisher").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAdvertisementPublisher(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ instance)
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
      
      ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^>(info[0]))
      {
        try
        {
          ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ arg0 = UnwrapBluetoothLEAdvertisement(info[0]);
          
          winRtInstance = ref new ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher(arg0);
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

      BluetoothLEAdvertisementPublisher *wrapperInstance = new BluetoothLEAdvertisementPublisher(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAdvertisementPublisher(winRtInstance));
    }


  
    static void Start(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementPublisher *wrapper = BluetoothLEAdvertisementPublisher::Unwrap<BluetoothLEAdvertisementPublisher>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Start();
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
    static void Stop(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementPublisher *wrapper = BluetoothLEAdvertisementPublisher::Unwrap<BluetoothLEAdvertisementPublisher>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Stop();
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



    static void AdvertisementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementPublisher *wrapper = BluetoothLEAdvertisementPublisher::Unwrap<BluetoothLEAdvertisementPublisher>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement^ result = wrapper->_instance->Advertisement;
        info.GetReturnValue().Set(WrapBluetoothLEAdvertisement(result));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^>(info.This()))
      {
        return;
      }

      BluetoothLEAdvertisementPublisher *wrapper = BluetoothLEAdvertisementPublisher::Unwrap<BluetoothLEAdvertisementPublisher>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"statusChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        BluetoothLEAdvertisementPublisher *wrapper = BluetoothLEAdvertisementPublisher::Unwrap<BluetoothLEAdvertisementPublisher>(info.This());
      
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

          registrationToken = wrapper->_instance->StatusChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^, ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ arg0, ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisherStatusChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapBluetoothLEAdvertisementPublisher(arg0);
                  wrappedArg1 = WrapBluetoothLEAdvertisementPublisherStatusChangedEventArgs(arg1);


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

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"statusChanged", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"statusChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          BluetoothLEAdvertisementPublisher *wrapper = BluetoothLEAdvertisementPublisher::Unwrap<BluetoothLEAdvertisementPublisher>(info.This());
          wrapper->_instance->StatusChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAdvertisementPublisher(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ UnwrapBluetoothLEAdvertisementPublisher(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAdvertisementPublisher::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAdvertisementPublisher(::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAdvertisementPublisher::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementPublisher^ UnwrapBluetoothLEAdvertisementPublisher(Local<Value> value)
  {
     return BluetoothLEAdvertisementPublisher::Unwrap<BluetoothLEAdvertisementPublisher>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAdvertisementPublisher(Local<Object> exports)
  {
    BluetoothLEAdvertisementPublisher::Init(exports);
  }

} } } } } 

NAN_MODULE_INIT(init)
{
  // we ignore failures for now since it probably means that the initialization already happened for STA, and that's cool
  CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  //if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
  /*{
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }*/
  
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEScanningModeEnum(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementFlagsEnum(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementTypeEnum(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementWatcherStatusEnum(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementPublisherStatusEnum(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEManufacturerData(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementDataSection(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisement(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementBytePattern(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementFilter(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementWatcherStoppedEventArgs(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementWatcher(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementReceivedEventArgs(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementDataTypes(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementPublisherStatusChangedEventArgs(target);
  NodeRT::Windows::Devices::Bluetooth::Advertisement::InitBluetoothLEAdvertisementPublisher(target);

  NodeRT::Utils::RegisterNameSpace("Windows.Devices.Bluetooth.Advertisement", target);
}


NODE_MODULE(binding, init)