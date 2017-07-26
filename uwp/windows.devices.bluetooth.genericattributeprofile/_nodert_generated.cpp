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

namespace NodeRT { namespace Windows { namespace Devices { namespace Bluetooth { namespace GenericAttributeProfile { 

  v8::Local<v8::Value> WrapGattDeviceService(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ UnwrapGattDeviceService(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattDeviceServicesResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^ UnwrapGattDeviceServicesResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattProtocolError(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^ UnwrapGattProtocolError(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattSession(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ UnwrapGattSession(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattSessionStatusChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ UnwrapGattSessionStatusChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattCharacteristic(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ UnwrapGattCharacteristic(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattCharacteristicsResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^ UnwrapGattCharacteristicsResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattDescriptor(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ UnwrapGattDescriptor(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattPresentationFormat(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ UnwrapGattPresentationFormat(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattReadResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^ UnwrapGattReadResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattReadClientCharacteristicConfigurationDescriptorResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^ UnwrapGattReadClientCharacteristicConfigurationDescriptorResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattValueChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ UnwrapGattValueChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattDescriptorsResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^ UnwrapGattDescriptorsResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattWriteResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^ UnwrapGattWriteResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattPresentationFormatTypes(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^ UnwrapGattPresentationFormatTypes(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattServiceUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^ UnwrapGattServiceUuids(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattCharacteristicUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^ UnwrapGattCharacteristicUuids(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattDescriptorUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^ UnwrapGattDescriptorUuids(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattReliableWriteTransaction(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^ UnwrapGattReliableWriteTransaction(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattServiceProviderAdvertisingParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ UnwrapGattServiceProviderAdvertisingParameters(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattLocalCharacteristicParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ UnwrapGattLocalCharacteristicParameters(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattLocalDescriptorParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ UnwrapGattLocalDescriptorParameters(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattServiceProviderResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^ UnwrapGattServiceProviderResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattLocalService(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ UnwrapGattLocalService(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattServiceProvider(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ UnwrapGattServiceProvider(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattServiceProviderAdvertisementStatusChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ UnwrapGattServiceProviderAdvertisementStatusChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattLocalCharacteristicResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^ UnwrapGattLocalCharacteristicResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattLocalCharacteristic(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ UnwrapGattLocalCharacteristic(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattLocalDescriptorResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^ UnwrapGattLocalDescriptorResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattLocalDescriptor(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ UnwrapGattLocalDescriptor(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattSubscribedClient(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ UnwrapGattSubscribedClient(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattReadRequestedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ UnwrapGattReadRequestedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattWriteRequestedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ UnwrapGattWriteRequestedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattClientNotificationResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ UnwrapGattClientNotificationResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattReadRequest(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ UnwrapGattReadRequest(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattRequestStateChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ UnwrapGattRequestStateChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapGattWriteRequest(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ wintRtInstance);
  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ UnwrapGattWriteRequest(Local<Value> value);
  


  static void InitGattSessionStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GattSessionStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("closed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatus::Closed)));
	Nan::Set(enumObject, Nan::New<String>("active").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatus::Active)));
  }


  static void InitGattCharacteristicPropertiesEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GattCharacteristicProperties").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::None)));
	Nan::Set(enumObject, Nan::New<String>("broadcast").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::Broadcast)));
	Nan::Set(enumObject, Nan::New<String>("read").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::Read)));
	Nan::Set(enumObject, Nan::New<String>("writeWithoutResponse").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::WriteWithoutResponse)));
	Nan::Set(enumObject, Nan::New<String>("write").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::Write)));
	Nan::Set(enumObject, Nan::New<String>("notify").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::Notify)));
	Nan::Set(enumObject, Nan::New<String>("indicate").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::Indicate)));
	Nan::Set(enumObject, Nan::New<String>("authenticatedSignedWrites").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::AuthenticatedSignedWrites)));
	Nan::Set(enumObject, Nan::New<String>("extendedProperties").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::ExtendedProperties)));
	Nan::Set(enumObject, Nan::New<String>("reliableWrites").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::ReliableWrites)));
	Nan::Set(enumObject, Nan::New<String>("writableAuxiliaries").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties::WritableAuxiliaries)));
  }


  static void InitGattClientCharacteristicConfigurationDescriptorValueEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GattClientCharacteristicConfigurationDescriptorValue").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientCharacteristicConfigurationDescriptorValue::None)));
	Nan::Set(enumObject, Nan::New<String>("notify").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientCharacteristicConfigurationDescriptorValue::Notify)));
	Nan::Set(enumObject, Nan::New<String>("indicate").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientCharacteristicConfigurationDescriptorValue::Indicate)));
  }


  static void InitGattProtectionLevelEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GattProtectionLevel").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("plain").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel::Plain)));
	Nan::Set(enumObject, Nan::New<String>("authenticationRequired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel::AuthenticationRequired)));
	Nan::Set(enumObject, Nan::New<String>("encryptionRequired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel::EncryptionRequired)));
	Nan::Set(enumObject, Nan::New<String>("encryptionAndAuthenticationRequired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel::EncryptionAndAuthenticationRequired)));
  }


  static void InitGattWriteOptionEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GattWriteOption").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("writeWithResponse").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteOption::WriteWithResponse)));
	Nan::Set(enumObject, Nan::New<String>("writeWithoutResponse").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteOption::WriteWithoutResponse)));
  }


  static void InitGattCommunicationStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GattCommunicationStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("success").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus::Success)));
	Nan::Set(enumObject, Nan::New<String>("unreachable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus::Unreachable)));
	Nan::Set(enumObject, Nan::New<String>("protocolError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus::ProtocolError)));
	Nan::Set(enumObject, Nan::New<String>("accessDenied").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus::AccessDenied)));
  }


  static void InitGattSharingModeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GattSharingMode").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unspecified").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSharingMode::Unspecified)));
	Nan::Set(enumObject, Nan::New<String>("exclusive").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSharingMode::Exclusive)));
	Nan::Set(enumObject, Nan::New<String>("sharedReadOnly").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSharingMode::SharedReadOnly)));
	Nan::Set(enumObject, Nan::New<String>("sharedReadAndWrite").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSharingMode::SharedReadAndWrite)));
  }


  static void InitGattOpenStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GattOpenStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unspecified").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattOpenStatus::Unspecified)));
	Nan::Set(enumObject, Nan::New<String>("success").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattOpenStatus::Success)));
	Nan::Set(enumObject, Nan::New<String>("alreadyOpened").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattOpenStatus::AlreadyOpened)));
	Nan::Set(enumObject, Nan::New<String>("notFound").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattOpenStatus::NotFound)));
	Nan::Set(enumObject, Nan::New<String>("sharingViolation").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattOpenStatus::SharingViolation)));
	Nan::Set(enumObject, Nan::New<String>("accessDenied").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattOpenStatus::AccessDenied)));
  }


  static void InitGattRequestStateEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GattRequestState").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("pending").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestState::Pending)));
	Nan::Set(enumObject, Nan::New<String>("completed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestState::Completed)));
	Nan::Set(enumObject, Nan::New<String>("canceled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestState::Canceled)));
  }


  static void InitGattServiceProviderAdvertisementStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GattServiceProviderAdvertisementStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("created").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatus::Created)));
	Nan::Set(enumObject, Nan::New<String>("stopped").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatus::Stopped)));
	Nan::Set(enumObject, Nan::New<String>("started").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatus::Started)));
	Nan::Set(enumObject, Nan::New<String>("aborted").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatus::Aborted)));
  }



  
  class GattDeviceService : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattDeviceService").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "getCharacteristics", GetCharacteristics);
      Nan::SetPrototypeMethod(localRef, "getIncludedServices", GetIncludedServices);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      Nan::SetPrototypeMethod(localRef, "getAllCharacteristics", GetAllCharacteristics);
      Nan::SetPrototypeMethod(localRef, "getAllIncludedServices", GetAllIncludedServices);
      
            
      Nan::SetPrototypeMethod(localRef, "requestAccessAsync", RequestAccessAsync);
      Nan::SetPrototypeMethod(localRef, "openAsync", OpenAsync);
      Nan::SetPrototypeMethod(localRef, "getCharacteristicsAsync", GetCharacteristicsAsync);
      Nan::SetPrototypeMethod(localRef, "getCharacteristicsForUuidAsync", GetCharacteristicsForUuidAsync);
      Nan::SetPrototypeMethod(localRef, "getIncludedServicesAsync", GetIncludedServicesAsync);
      Nan::SetPrototypeMethod(localRef, "getIncludedServicesForUuidAsync", GetIncludedServicesForUuidAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributeHandle").ToLocalChecked(), AttributeHandleGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceId").ToLocalChecked(), DeviceIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("uuid").ToLocalChecked(), UuidGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("device").ToLocalChecked(), DeviceGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("parentServices").ToLocalChecked(), ParentServicesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceAccessInformation").ToLocalChecked(), DeviceAccessInformationGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("session").ToLocalChecked(), SessionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("sharingMode").ToLocalChecked(), SharingModeGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "getDeviceSelectorForBluetoothDeviceId", GetDeviceSelectorForBluetoothDeviceId);
      Nan::SetMethod(constructor, "getDeviceSelectorForBluetoothDeviceIdAndUuid", GetDeviceSelectorForBluetoothDeviceIdAndUuid);
      Nan::SetMethod(constructor, "getDeviceSelectorFromUuid", GetDeviceSelectorFromUuid);
      Nan::SetMethod(constructor, "getDeviceSelectorFromShortId", GetDeviceSelectorFromShortId);
      Nan::SetMethod(constructor, "convertShortIdToUuid", ConvertShortIdToUuid);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FromIdAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("fromIdAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("GattDeviceService").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattDeviceService(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattDeviceService *wrapperInstance = new GattDeviceService(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattDeviceService(winRtInstance));
    }


    static void RequestAccessAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Enumeration::DeviceAccessStatus>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->RequestAccessAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Enumeration::DeviceAccessStatus> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(static_cast<int>(result));
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
    static void OpenAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattOpenStatus>^ op;
    

      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSharingMode arg0 = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSharingMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->OpenAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattOpenStatus> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(static_cast<int>(result));
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
    static void GetCharacteristicsAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetCharacteristicsAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg0 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetCharacteristicsAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattCharacteristicsResult(result);
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
    static void GetCharacteristicsForUuidAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          op = wrapper->_instance->GetCharacteristicsForUuidAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsGuid(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg1 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetCharacteristicsForUuidAsync(arg0,arg1);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattCharacteristicsResult(result);
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
    static void GetIncludedServicesAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetIncludedServicesAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg0 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetIncludedServicesAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattDeviceServicesResult(result);
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
    static void GetIncludedServicesForUuidAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          op = wrapper->_instance->GetIncludedServicesForUuidAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsGuid(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg1 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetIncludedServicesForUuidAsync(arg0,arg1);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattDeviceServicesResult(result);
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
  
    static void GetCharacteristics(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>^ result;
          result = wrapper->_instance->GetCharacteristics(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ val) -> Local<Value> {
              return WrapGattCharacteristic(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ {
              return UnwrapGattCharacteristic(value);
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
    static void GetIncludedServices(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>^ result;
          result = wrapper->_instance->GetIncludedServices(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ val) -> Local<Value> {
              return WrapGattDeviceService(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ {
              return UnwrapGattDeviceService(value);
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
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
	    return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

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

    static void GetAllCharacteristics(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>^ result;
          result = wrapper->_instance->GetAllCharacteristics();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ val) -> Local<Value> {
              return WrapGattCharacteristic(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ {
              return UnwrapGattCharacteristic(value);
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
    static void GetAllIncludedServices(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>^ result;
          result = wrapper->_instance->GetAllIncludedServices();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ val) -> Local<Value> {
              return WrapGattDeviceService(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ {
              return UnwrapGattDeviceService(value);
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

    static void FromIdAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>^ op;
      

      if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSharingMode arg1 = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSharingMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService::FromIdAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService::FromIdAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattDeviceService(result);
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

    static void GetDeviceSelectorForBluetoothDeviceId(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(info[0]))
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothDeviceId^ arg0 = dynamic_cast<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService::GetDeviceSelectorForBluetoothDeviceId(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothDeviceId^ arg0 = dynamic_cast<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg1 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService::GetDeviceSelectorForBluetoothDeviceId(arg0, arg1);
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
    static void GetDeviceSelectorForBluetoothDeviceIdAndUuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(info[0])
        && NodeRT::Utils::IsGuid(info[1]))
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothDeviceId^ arg0 = dynamic_cast<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Platform::Guid arg1 = NodeRT::Utils::GuidFromJs(info[1]);
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService::GetDeviceSelectorForBluetoothDeviceIdAndUuid(arg0, arg1);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(info[0])
        && NodeRT::Utils::IsGuid(info[1])
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothDeviceId^ arg0 = dynamic_cast<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Platform::Guid arg1 = NodeRT::Utils::GuidFromJs(info[1]);
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg2 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService::GetDeviceSelectorForBluetoothDeviceIdAndUuid(arg0, arg1, arg2);
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
    static void GetDeviceSelectorFromUuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService::GetDeviceSelectorFromUuid(arg0);
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
    static void GetDeviceSelectorFromShortId(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService::GetDeviceSelectorFromShortId(arg0);
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
    static void ConvertShortIdToUuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Platform::Guid result;
          result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService::ConvertShortIdToUuid(arg0);
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

    static void AttributeHandleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->AttributeHandle;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DeviceIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->DeviceId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UuidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->Uuid;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DeviceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothLEDevice^ result = wrapper->_instance->Device;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Bluetooth", "BluetoothLEDevice", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ParentServicesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>^ result = wrapper->_instance->ParentServices;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ val) -> Local<Value> {
              return WrapGattDeviceService(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ {
              return UnwrapGattDeviceService(value);
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
    
    static void DeviceAccessInformationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceAccessInformation^ result = wrapper->_instance->DeviceAccessInformation;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Enumeration", "DeviceAccessInformation", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SessionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ result = wrapper->_instance->Session;
        info.GetReturnValue().Set(WrapGattSession(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SharingModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(info.This()))
      {
        return;
      }

      GattDeviceService *wrapper = GattDeviceService::Unwrap<GattDeviceService>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSharingMode result = wrapper->_instance->SharingMode;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattDeviceService(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ UnwrapGattDeviceService(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattDeviceService::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattDeviceService(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattDeviceService::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ UnwrapGattDeviceService(Local<Value> value)
  {
     return GattDeviceService::Unwrap<GattDeviceService>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattDeviceService(Local<Object> exports)
  {
    GattDeviceService::Init(exports);
  }

  class GattDeviceServicesResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattDeviceServicesResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protocolError").ToLocalChecked(), ProtocolErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("services").ToLocalChecked(), ServicesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattDeviceServicesResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattDeviceServicesResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattDeviceServicesResult *wrapperInstance = new GattDeviceServicesResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattDeviceServicesResult(winRtInstance));
    }


  



    static void ProtocolErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^>(info.This()))
      {
        return;
      }

      GattDeviceServicesResult *wrapper = GattDeviceServicesResult::Unwrap<GattDeviceServicesResult>(info.This());

      try 
      {
        ::Platform::IBox<unsigned char>^ result = wrapper->_instance->ProtocolError;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServicesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^>(info.This()))
      {
        return;
      }

      GattDeviceServicesResult *wrapper = GattDeviceServicesResult::Unwrap<GattDeviceServicesResult>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>^ result = wrapper->_instance->Services;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ val) -> Local<Value> {
              return WrapGattDeviceService(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ {
              return UnwrapGattDeviceService(value);
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
    
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^>(info.This()))
      {
        return;
      }

      GattDeviceServicesResult *wrapper = GattDeviceServicesResult::Unwrap<GattDeviceServicesResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus result = wrapper->_instance->Status;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattDeviceServicesResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^ UnwrapGattDeviceServicesResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattDeviceServicesResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattDeviceServicesResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattDeviceServicesResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^ UnwrapGattDeviceServicesResult(Local<Value> value)
  {
     return GattDeviceServicesResult::Unwrap<GattDeviceServicesResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattDeviceServicesResult(Local<Object> exports)
  {
    GattDeviceServicesResult::Init(exports);
  }

  class GattProtocolError : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattProtocolError").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("attributeNotFound").ToLocalChecked(), AttributeNotFoundGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("attributeNotLong").ToLocalChecked(), AttributeNotLongGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("insufficientAuthentication").ToLocalChecked(), InsufficientAuthenticationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("insufficientAuthorization").ToLocalChecked(), InsufficientAuthorizationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("insufficientEncryption").ToLocalChecked(), InsufficientEncryptionGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("insufficientEncryptionKeySize").ToLocalChecked(), InsufficientEncryptionKeySizeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("insufficientResources").ToLocalChecked(), InsufficientResourcesGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("invalidAttributeValueLength").ToLocalChecked(), InvalidAttributeValueLengthGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("invalidHandle").ToLocalChecked(), InvalidHandleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("invalidOffset").ToLocalChecked(), InvalidOffsetGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("invalidPdu").ToLocalChecked(), InvalidPduGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("prepareQueueFull").ToLocalChecked(), PrepareQueueFullGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("readNotPermitted").ToLocalChecked(), ReadNotPermittedGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("requestNotSupported").ToLocalChecked(), RequestNotSupportedGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("unlikelyError").ToLocalChecked(), UnlikelyErrorGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("unsupportedGroupType").ToLocalChecked(), UnsupportedGroupTypeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("writeNotPermitted").ToLocalChecked(), WriteNotPermittedGetter);

      Nan::Set(exports, Nan::New<String>("GattProtocolError").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattProtocolError(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattProtocolError *wrapperInstance = new GattProtocolError(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattProtocolError(winRtInstance));
    }


  




    static void AttributeNotFoundGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::AttributeNotFound;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AttributeNotLongGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::AttributeNotLong;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InsufficientAuthenticationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::InsufficientAuthentication;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InsufficientAuthorizationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::InsufficientAuthorization;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InsufficientEncryptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::InsufficientEncryption;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InsufficientEncryptionKeySizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::InsufficientEncryptionKeySize;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InsufficientResourcesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::InsufficientResources;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InvalidAttributeValueLengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::InvalidAttributeValueLength;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InvalidHandleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::InvalidHandle;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InvalidOffsetGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::InvalidOffset;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InvalidPduGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::InvalidPdu;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PrepareQueueFullGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::PrepareQueueFull;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ReadNotPermittedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::ReadNotPermitted;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RequestNotSupportedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::RequestNotSupported;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UnlikelyErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::UnlikelyError;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UnsupportedGroupTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::UnsupportedGroupType;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WriteNotPermittedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError::WriteNotPermitted;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattProtocolError(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^ UnwrapGattProtocolError(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattProtocolError::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattProtocolError(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattProtocolError::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtocolError^ UnwrapGattProtocolError(Local<Value> value)
  {
     return GattProtocolError::Unwrap<GattProtocolError>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattProtocolError(Local<Object> exports)
  {
    GattProtocolError::Init(exports);
  }

  class GattSession : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattSession").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
                  
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maintainConnection").ToLocalChecked(), MaintainConnectionGetter, MaintainConnectionSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canMaintainConnection").ToLocalChecked(), CanMaintainConnectionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceId").ToLocalChecked(), DeviceIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maxPduSize").ToLocalChecked(), MaxPduSizeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("sessionStatus").ToLocalChecked(), SessionStatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FromDeviceIdAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("fromDeviceIdAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("GattSession").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattSession(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattSession *wrapperInstance = new GattSession(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattSession(winRtInstance));
    }


  
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
      {
	    return;
      }

      GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());

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


    static void FromDeviceIdAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>^ op;
      

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(info[0]))
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothDeviceId^ arg0 = dynamic_cast<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession::FromDeviceIdAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattSession(result);
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


    static void MaintainConnectionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
      {
        return;
      }

      GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());

      try 
      {
        bool result = wrapper->_instance->MaintainConnection;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MaintainConnectionSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
      {
        return;
      }

      GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->MaintainConnection = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void CanMaintainConnectionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
      {
        return;
      }

      GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanMaintainConnection;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DeviceIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
      {
        return;
      }

      GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothDeviceId^ result = wrapper->_instance->DeviceId;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Bluetooth", "BluetoothDeviceId", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MaxPduSizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
      {
        return;
      }

      GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->MaxPduSize;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SessionStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
      {
        return;
      }

      GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatus result = wrapper->_instance->SessionStatus;
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

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"maxPduSizeChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());
      
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

          registrationToken = wrapper->_instance->MaxPduSizeChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattSession(arg0);
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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"sessionStatusChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());
      
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

          registrationToken = wrapper->_instance->SessionStatusChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ arg0, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattSession(arg0);
                  wrappedArg1 = WrapGattSessionStatusChangedEventArgs(arg1);


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
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"maxPduSizeChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"sessionStatusChanged", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"maxPduSizeChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());
          wrapper->_instance->MaxPduSizeChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"sessionStatusChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattSession *wrapper = GattSession::Unwrap<GattSession>(info.This());
          wrapper->_instance->SessionStatusChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattSession(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ UnwrapGattSession(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattSession::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattSession(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattSession::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ UnwrapGattSession(Local<Value> value)
  {
     return GattSession::Unwrap<GattSession>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattSession(Local<Object> exports)
  {
    GattSession::Init(exports);
  }

  class GattSessionStatusChangedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattSessionStatusChangedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("error").ToLocalChecked(), ErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattSessionStatusChangedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattSessionStatusChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattSessionStatusChangedEventArgs *wrapperInstance = new GattSessionStatusChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattSessionStatusChangedEventArgs(winRtInstance));
    }


  



    static void ErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^>(info.This()))
      {
        return;
      }

      GattSessionStatusChangedEventArgs *wrapper = GattSessionStatusChangedEventArgs::Unwrap<GattSessionStatusChangedEventArgs>(info.This());

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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^>(info.This()))
      {
        return;
      }

      GattSessionStatusChangedEventArgs *wrapper = GattSessionStatusChangedEventArgs::Unwrap<GattSessionStatusChangedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatus result = wrapper->_instance->Status;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattSessionStatusChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ UnwrapGattSessionStatusChangedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattSessionStatusChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattSessionStatusChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattSessionStatusChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSessionStatusChangedEventArgs^ UnwrapGattSessionStatusChangedEventArgs(Local<Value> value)
  {
     return GattSessionStatusChangedEventArgs::Unwrap<GattSessionStatusChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattSessionStatusChangedEventArgs(Local<Object> exports)
  {
    GattSessionStatusChangedEventArgs::Init(exports);
  }

  class GattCharacteristic : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattCharacteristic").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "getDescriptors", GetDescriptors);
      Nan::SetPrototypeMethod(localRef, "getAllDescriptors", GetAllDescriptors);
      
            
      Nan::SetPrototypeMethod(localRef, "readValueAsync", ReadValueAsync);
      Nan::SetPrototypeMethod(localRef, "writeValueAsync", WriteValueAsync);
      Nan::SetPrototypeMethod(localRef, "readClientCharacteristicConfigurationDescriptorAsync", ReadClientCharacteristicConfigurationDescriptorAsync);
      Nan::SetPrototypeMethod(localRef, "writeClientCharacteristicConfigurationDescriptorAsync", WriteClientCharacteristicConfigurationDescriptorAsync);
      Nan::SetPrototypeMethod(localRef, "getDescriptorsAsync", GetDescriptorsAsync);
      Nan::SetPrototypeMethod(localRef, "getDescriptorsForUuidAsync", GetDescriptorsForUuidAsync);
      Nan::SetPrototypeMethod(localRef, "writeValueWithResultAsync", WriteValueWithResultAsync);
      Nan::SetPrototypeMethod(localRef, "writeClientCharacteristicConfigurationDescriptorWithResultAsync", WriteClientCharacteristicConfigurationDescriptorWithResultAsync);
      
            
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protectionLevel").ToLocalChecked(), ProtectionLevelGetter, ProtectionLevelSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributeHandle").ToLocalChecked(), AttributeHandleGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("characteristicProperties").ToLocalChecked(), CharacteristicPropertiesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("presentationFormats").ToLocalChecked(), PresentationFormatsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userDescription").ToLocalChecked(), UserDescriptionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("uuid").ToLocalChecked(), UuidGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("service").ToLocalChecked(), ServiceGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "convertShortIdToUuid", ConvertShortIdToUuid);

      Nan::Set(exports, Nan::New<String>("GattCharacteristic").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattCharacteristic(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattCharacteristic *wrapperInstance = new GattCharacteristic(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattCharacteristic(winRtInstance));
    }


    static void ReadValueAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->ReadValueAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg0 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->ReadValueAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattReadResult(result);
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
    static void WriteValueAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->WriteValueAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteOption arg1 = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->WriteValueAsync(arg0,arg1);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(static_cast<int>(result));
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
    static void ReadClientCharacteristicConfigurationDescriptorAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->ReadClientCharacteristicConfigurationDescriptorAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattReadClientCharacteristicConfigurationDescriptorResult(result);
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
    static void WriteClientCharacteristicConfigurationDescriptorAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus>^ op;
    

      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientCharacteristicConfigurationDescriptorValue arg0 = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientCharacteristicConfigurationDescriptorValue>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->WriteClientCharacteristicConfigurationDescriptorAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(static_cast<int>(result));
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
    static void GetDescriptorsAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetDescriptorsAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg0 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetDescriptorsAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattDescriptorsResult(result);
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
    static void GetDescriptorsForUuidAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          op = wrapper->_instance->GetDescriptorsForUuidAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsGuid(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg1 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetDescriptorsForUuidAsync(arg0,arg1);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattDescriptorsResult(result);
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
    static void WriteValueWithResultAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->WriteValueWithResultAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteOption arg1 = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->WriteValueWithResultAsync(arg0,arg1);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattWriteResult(result);
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
    static void WriteClientCharacteristicConfigurationDescriptorWithResultAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^>^ op;
    

      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientCharacteristicConfigurationDescriptorValue arg0 = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientCharacteristicConfigurationDescriptorValue>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->WriteClientCharacteristicConfigurationDescriptorWithResultAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattWriteResult(result);
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
  
    static void GetDescriptors(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>^ result;
          result = wrapper->_instance->GetDescriptors(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ val) -> Local<Value> {
              return WrapGattDescriptor(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ {
              return UnwrapGattDescriptor(value);
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
    static void GetAllDescriptors(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>^ result;
          result = wrapper->_instance->GetAllDescriptors();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ val) -> Local<Value> {
              return WrapGattDescriptor(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ {
              return UnwrapGattDescriptor(value);
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


    static void ConvertShortIdToUuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Platform::Guid result;
          result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic::ConvertShortIdToUuid(arg0);
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

    static void ProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel result = wrapper->_instance->ProtectionLevel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProtectionLevelSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel winRtValue = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ProtectionLevel = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void AttributeHandleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->AttributeHandle;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CharacteristicPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties result = wrapper->_instance->CharacteristicProperties;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PresentationFormatsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>^ result = wrapper->_instance->PresentationFormats;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ val) -> Local<Value> {
              return WrapGattPresentationFormat(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ {
              return UnwrapGattPresentationFormat(value);
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
    
    static void UserDescriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->UserDescription;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UuidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->Uuid;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
      {
        return;
      }

      GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ result = wrapper->_instance->Service;
        info.GetReturnValue().Set(WrapGattDeviceService(result));
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

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"valueChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());
      
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

          registrationToken = wrapper->_instance->ValueChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ arg0, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattCharacteristic(arg0);
                  wrappedArg1 = WrapGattValueChangedEventArgs(arg1);


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
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"valueChanged", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"valueChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattCharacteristic *wrapper = GattCharacteristic::Unwrap<GattCharacteristic>(info.This());
          wrapper->_instance->ValueChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattCharacteristic(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ UnwrapGattCharacteristic(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattCharacteristic::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattCharacteristic(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattCharacteristic::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ UnwrapGattCharacteristic(Local<Value> value)
  {
     return GattCharacteristic::Unwrap<GattCharacteristic>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattCharacteristic(Local<Object> exports)
  {
    GattCharacteristic::Init(exports);
  }

  class GattCharacteristicsResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattCharacteristicsResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("characteristics").ToLocalChecked(), CharacteristicsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protocolError").ToLocalChecked(), ProtocolErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattCharacteristicsResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattCharacteristicsResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattCharacteristicsResult *wrapperInstance = new GattCharacteristicsResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattCharacteristicsResult(winRtInstance));
    }


  



    static void CharacteristicsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^>(info.This()))
      {
        return;
      }

      GattCharacteristicsResult *wrapper = GattCharacteristicsResult::Unwrap<GattCharacteristicsResult>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>^ result = wrapper->_instance->Characteristics;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ val) -> Local<Value> {
              return WrapGattCharacteristic(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ {
              return UnwrapGattCharacteristic(value);
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
    
    static void ProtocolErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^>(info.This()))
      {
        return;
      }

      GattCharacteristicsResult *wrapper = GattCharacteristicsResult::Unwrap<GattCharacteristicsResult>(info.This());

      try 
      {
        ::Platform::IBox<unsigned char>^ result = wrapper->_instance->ProtocolError;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^>(info.This()))
      {
        return;
      }

      GattCharacteristicsResult *wrapper = GattCharacteristicsResult::Unwrap<GattCharacteristicsResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus result = wrapper->_instance->Status;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattCharacteristicsResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^ UnwrapGattCharacteristicsResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattCharacteristicsResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattCharacteristicsResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattCharacteristicsResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult^ UnwrapGattCharacteristicsResult(Local<Value> value)
  {
     return GattCharacteristicsResult::Unwrap<GattCharacteristicsResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattCharacteristicsResult(Local<Object> exports)
  {
    GattCharacteristicsResult::Init(exports);
  }

  class GattDescriptor : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattDescriptor").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "readValueAsync", ReadValueAsync);
      Nan::SetPrototypeMethod(localRef, "writeValueAsync", WriteValueAsync);
      Nan::SetPrototypeMethod(localRef, "writeValueWithResultAsync", WriteValueWithResultAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protectionLevel").ToLocalChecked(), ProtectionLevelGetter, ProtectionLevelSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributeHandle").ToLocalChecked(), AttributeHandleGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("uuid").ToLocalChecked(), UuidGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "convertShortIdToUuid", ConvertShortIdToUuid);

      Nan::Set(exports, Nan::New<String>("GattDescriptor").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattDescriptor(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattDescriptor *wrapperInstance = new GattDescriptor(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattDescriptor(winRtInstance));
    }


    static void ReadValueAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattDescriptor *wrapper = GattDescriptor::Unwrap<GattDescriptor>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->ReadValueAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg0 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->ReadValueAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattReadResult(result);
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
    static void WriteValueAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattDescriptor *wrapper = GattDescriptor::Unwrap<GattDescriptor>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->WriteValueAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(static_cast<int>(result));
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
    static void WriteValueWithResultAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattDescriptor *wrapper = GattDescriptor::Unwrap<GattDescriptor>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->WriteValueWithResultAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattWriteResult(result);
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
  


    static void ConvertShortIdToUuid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Platform::Guid result;
          result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor::ConvertShortIdToUuid(arg0);
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

    static void ProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(info.This()))
      {
        return;
      }

      GattDescriptor *wrapper = GattDescriptor::Unwrap<GattDescriptor>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel result = wrapper->_instance->ProtectionLevel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProtectionLevelSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(info.This()))
      {
        return;
      }

      GattDescriptor *wrapper = GattDescriptor::Unwrap<GattDescriptor>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel winRtValue = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ProtectionLevel = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void AttributeHandleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(info.This()))
      {
        return;
      }

      GattDescriptor *wrapper = GattDescriptor::Unwrap<GattDescriptor>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->AttributeHandle;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UuidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(info.This()))
      {
        return;
      }

      GattDescriptor *wrapper = GattDescriptor::Unwrap<GattDescriptor>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->Uuid;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattDescriptor(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ UnwrapGattDescriptor(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattDescriptor::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattDescriptor(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattDescriptor::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ UnwrapGattDescriptor(Local<Value> value)
  {
     return GattDescriptor::Unwrap<GattDescriptor>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattDescriptor(Local<Object> exports)
  {
    GattDescriptor::Init(exports);
  }

  class GattPresentationFormat : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattPresentationFormat").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("description").ToLocalChecked(), DescriptionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("exponent").ToLocalChecked(), ExponentGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("formatType").ToLocalChecked(), FormatTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("namespace").ToLocalChecked(), NamespaceGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("unit").ToLocalChecked(), UnitGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "fromParts", FromParts);
      Nan::SetAccessor(constructor, Nan::New<String>("bluetoothSigAssignedNumbers").ToLocalChecked(), BluetoothSigAssignedNumbersGetter);

      Nan::Set(exports, Nan::New<String>("GattPresentationFormat").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattPresentationFormat(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattPresentationFormat *wrapperInstance = new GattPresentationFormat(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattPresentationFormat(winRtInstance));
    }


  


    static void FromParts(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 5
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && info[2]->IsInt32()
        && info[3]->IsInt32()
        && info[4]->IsInt32())
      {
        try
        {
          unsigned char arg0 = static_cast<unsigned char>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          int arg1 = static_cast<int>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          unsigned short arg2 = static_cast<unsigned short>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          unsigned char arg3 = static_cast<unsigned char>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          unsigned short arg4 = static_cast<unsigned short>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ result;
          result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat::FromParts(arg0, arg1, arg2, arg3, arg4);
          info.GetReturnValue().Set(WrapGattPresentationFormat(result));
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

    static void DescriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>(info.This()))
      {
        return;
      }

      GattPresentationFormat *wrapper = GattPresentationFormat::Unwrap<GattPresentationFormat>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->Description;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ExponentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>(info.This()))
      {
        return;
      }

      GattPresentationFormat *wrapper = GattPresentationFormat::Unwrap<GattPresentationFormat>(info.This());

      try 
      {
        int result = wrapper->_instance->Exponent;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void FormatTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>(info.This()))
      {
        return;
      }

      GattPresentationFormat *wrapper = GattPresentationFormat::Unwrap<GattPresentationFormat>(info.This());

      try 
      {
        unsigned char result = wrapper->_instance->FormatType;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NamespaceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>(info.This()))
      {
        return;
      }

      GattPresentationFormat *wrapper = GattPresentationFormat::Unwrap<GattPresentationFormat>(info.This());

      try 
      {
        unsigned char result = wrapper->_instance->Namespace;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UnitGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>(info.This()))
      {
        return;
      }

      GattPresentationFormat *wrapper = GattPresentationFormat::Unwrap<GattPresentationFormat>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->Unit;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

    static void BluetoothSigAssignedNumbersGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat::BluetoothSigAssignedNumbers;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattPresentationFormat(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ UnwrapGattPresentationFormat(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattPresentationFormat::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattPresentationFormat(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattPresentationFormat::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ UnwrapGattPresentationFormat(Local<Value> value)
  {
     return GattPresentationFormat::Unwrap<GattPresentationFormat>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattPresentationFormat(Local<Object> exports)
  {
    GattPresentationFormat::Init(exports);
  }

  class GattReadResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattReadResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("value").ToLocalChecked(), ValueGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protocolError").ToLocalChecked(), ProtocolErrorGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattReadResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattReadResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattReadResult *wrapperInstance = new GattReadResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattReadResult(winRtInstance));
    }


  



    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^>(info.This()))
      {
        return;
      }

      GattReadResult *wrapper = GattReadResult::Unwrap<GattReadResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^>(info.This()))
      {
        return;
      }

      GattReadResult *wrapper = GattReadResult::Unwrap<GattReadResult>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->Value;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProtocolErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^>(info.This()))
      {
        return;
      }

      GattReadResult *wrapper = GattReadResult::Unwrap<GattReadResult>(info.This());

      try 
      {
        ::Platform::IBox<unsigned char>^ result = wrapper->_instance->ProtocolError;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattReadResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^ UnwrapGattReadResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattReadResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattReadResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattReadResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadResult^ UnwrapGattReadResult(Local<Value> value)
  {
     return GattReadResult::Unwrap<GattReadResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattReadResult(Local<Object> exports)
  {
    GattReadResult::Init(exports);
  }

  class GattReadClientCharacteristicConfigurationDescriptorResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattReadClientCharacteristicConfigurationDescriptorResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("clientCharacteristicConfigurationDescriptor").ToLocalChecked(), ClientCharacteristicConfigurationDescriptorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protocolError").ToLocalChecked(), ProtocolErrorGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattReadClientCharacteristicConfigurationDescriptorResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattReadClientCharacteristicConfigurationDescriptorResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattReadClientCharacteristicConfigurationDescriptorResult *wrapperInstance = new GattReadClientCharacteristicConfigurationDescriptorResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattReadClientCharacteristicConfigurationDescriptorResult(winRtInstance));
    }


  



    static void ClientCharacteristicConfigurationDescriptorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^>(info.This()))
      {
        return;
      }

      GattReadClientCharacteristicConfigurationDescriptorResult *wrapper = GattReadClientCharacteristicConfigurationDescriptorResult::Unwrap<GattReadClientCharacteristicConfigurationDescriptorResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientCharacteristicConfigurationDescriptorValue result = wrapper->_instance->ClientCharacteristicConfigurationDescriptor;
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^>(info.This()))
      {
        return;
      }

      GattReadClientCharacteristicConfigurationDescriptorResult *wrapper = GattReadClientCharacteristicConfigurationDescriptorResult::Unwrap<GattReadClientCharacteristicConfigurationDescriptorResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProtocolErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^>(info.This()))
      {
        return;
      }

      GattReadClientCharacteristicConfigurationDescriptorResult *wrapper = GattReadClientCharacteristicConfigurationDescriptorResult::Unwrap<GattReadClientCharacteristicConfigurationDescriptorResult>(info.This());

      try 
      {
        ::Platform::IBox<unsigned char>^ result = wrapper->_instance->ProtocolError;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattReadClientCharacteristicConfigurationDescriptorResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^ UnwrapGattReadClientCharacteristicConfigurationDescriptorResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattReadClientCharacteristicConfigurationDescriptorResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattReadClientCharacteristicConfigurationDescriptorResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattReadClientCharacteristicConfigurationDescriptorResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadClientCharacteristicConfigurationDescriptorResult^ UnwrapGattReadClientCharacteristicConfigurationDescriptorResult(Local<Value> value)
  {
     return GattReadClientCharacteristicConfigurationDescriptorResult::Unwrap<GattReadClientCharacteristicConfigurationDescriptorResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattReadClientCharacteristicConfigurationDescriptorResult(Local<Object> exports)
  {
    GattReadClientCharacteristicConfigurationDescriptorResult::Init(exports);
  }

  class GattValueChangedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattValueChangedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("characteristicValue").ToLocalChecked(), CharacteristicValueGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("timestamp").ToLocalChecked(), TimestampGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattValueChangedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattValueChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattValueChangedEventArgs *wrapperInstance = new GattValueChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattValueChangedEventArgs(winRtInstance));
    }


  



    static void CharacteristicValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^>(info.This()))
      {
        return;
      }

      GattValueChangedEventArgs *wrapper = GattValueChangedEventArgs::Unwrap<GattValueChangedEventArgs>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->CharacteristicValue;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^>(info.This()))
      {
        return;
      }

      GattValueChangedEventArgs *wrapper = GattValueChangedEventArgs::Unwrap<GattValueChangedEventArgs>(info.This());

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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattValueChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ UnwrapGattValueChangedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattValueChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattValueChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattValueChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattValueChangedEventArgs^ UnwrapGattValueChangedEventArgs(Local<Value> value)
  {
     return GattValueChangedEventArgs::Unwrap<GattValueChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattValueChangedEventArgs(Local<Object> exports)
  {
    GattValueChangedEventArgs::Init(exports);
  }

  class GattDescriptorsResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattDescriptorsResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("descriptors").ToLocalChecked(), DescriptorsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protocolError").ToLocalChecked(), ProtocolErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattDescriptorsResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattDescriptorsResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattDescriptorsResult *wrapperInstance = new GattDescriptorsResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattDescriptorsResult(winRtInstance));
    }


  



    static void DescriptorsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^>(info.This()))
      {
        return;
      }

      GattDescriptorsResult *wrapper = GattDescriptorsResult::Unwrap<GattDescriptorsResult>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>^ result = wrapper->_instance->Descriptors;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ val) -> Local<Value> {
              return WrapGattDescriptor(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptor^ {
              return UnwrapGattDescriptor(value);
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
    
    static void ProtocolErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^>(info.This()))
      {
        return;
      }

      GattDescriptorsResult *wrapper = GattDescriptorsResult::Unwrap<GattDescriptorsResult>(info.This());

      try 
      {
        ::Platform::IBox<unsigned char>^ result = wrapper->_instance->ProtocolError;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^>(info.This()))
      {
        return;
      }

      GattDescriptorsResult *wrapper = GattDescriptorsResult::Unwrap<GattDescriptorsResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus result = wrapper->_instance->Status;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattDescriptorsResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^ UnwrapGattDescriptorsResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattDescriptorsResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattDescriptorsResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattDescriptorsResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorsResult^ UnwrapGattDescriptorsResult(Local<Value> value)
  {
     return GattDescriptorsResult::Unwrap<GattDescriptorsResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattDescriptorsResult(Local<Object> exports)
  {
    GattDescriptorsResult::Init(exports);
  }

  class GattWriteResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattWriteResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protocolError").ToLocalChecked(), ProtocolErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattWriteResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattWriteResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattWriteResult *wrapperInstance = new GattWriteResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattWriteResult(winRtInstance));
    }


  



    static void ProtocolErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^>(info.This()))
      {
        return;
      }

      GattWriteResult *wrapper = GattWriteResult::Unwrap<GattWriteResult>(info.This());

      try 
      {
        ::Platform::IBox<unsigned char>^ result = wrapper->_instance->ProtocolError;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^>(info.This()))
      {
        return;
      }

      GattWriteResult *wrapper = GattWriteResult::Unwrap<GattWriteResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus result = wrapper->_instance->Status;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattWriteResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^ UnwrapGattWriteResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattWriteResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattWriteResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattWriteResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^ UnwrapGattWriteResult(Local<Value> value)
  {
     return GattWriteResult::Unwrap<GattWriteResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattWriteResult(Local<Object> exports)
  {
    GattWriteResult::Init(exports);
  }

  class GattPresentationFormatTypes : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattPresentationFormatTypes").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("bit2").ToLocalChecked(), Bit2Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("boolean").ToLocalChecked(), BooleanGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("dUInt16").ToLocalChecked(), DUInt16Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("float").ToLocalChecked(), FloatGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("float32").ToLocalChecked(), Float32Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("float64").ToLocalChecked(), Float64Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("nibble").ToLocalChecked(), NibbleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("sFloat").ToLocalChecked(), SFloatGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("sInt12").ToLocalChecked(), SInt12Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("sInt128").ToLocalChecked(), SInt128Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("sInt16").ToLocalChecked(), SInt16Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("sInt24").ToLocalChecked(), SInt24Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("sInt32").ToLocalChecked(), SInt32Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("sInt48").ToLocalChecked(), SInt48Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("sInt64").ToLocalChecked(), SInt64Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("sInt8").ToLocalChecked(), SInt8Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("struct").ToLocalChecked(), StructGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("uInt12").ToLocalChecked(), UInt12Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("uInt128").ToLocalChecked(), UInt128Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("uInt16").ToLocalChecked(), UInt16Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("uInt24").ToLocalChecked(), UInt24Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("uInt32").ToLocalChecked(), UInt32Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("uInt48").ToLocalChecked(), UInt48Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("uInt64").ToLocalChecked(), UInt64Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("uInt8").ToLocalChecked(), UInt8Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("utf16").ToLocalChecked(), Utf16Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("utf8").ToLocalChecked(), Utf8Getter);

      Nan::Set(exports, Nan::New<String>("GattPresentationFormatTypes").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattPresentationFormatTypes(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattPresentationFormatTypes *wrapperInstance = new GattPresentationFormatTypes(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattPresentationFormatTypes(winRtInstance));
    }


  




    static void Bit2Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::Bit2;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BooleanGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::Boolean;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DUInt16Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::DUInt16;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void FloatGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::Float;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Float32Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::Float32;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Float64Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::Float64;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NibbleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::Nibble;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SFloatGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::SFloat;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SInt12Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::SInt12;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SInt128Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::SInt128;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SInt16Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::SInt16;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SInt24Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::SInt24;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SInt32Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::SInt32;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SInt48Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::SInt48;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SInt64Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::SInt64;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SInt8Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::SInt8;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StructGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::Struct;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UInt12Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::UInt12;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UInt128Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::UInt128;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UInt16Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::UInt16;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UInt24Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::UInt24;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UInt32Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::UInt32;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UInt48Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::UInt48;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UInt64Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::UInt64;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UInt8Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::UInt8;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Utf16Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::Utf16;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Utf8Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned char result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes::Utf8;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattPresentationFormatTypes(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^ UnwrapGattPresentationFormatTypes(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattPresentationFormatTypes::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattPresentationFormatTypes(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattPresentationFormatTypes::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormatTypes^ UnwrapGattPresentationFormatTypes(Local<Value> value)
  {
     return GattPresentationFormatTypes::Unwrap<GattPresentationFormatTypes>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattPresentationFormatTypes(Local<Object> exports)
  {
    GattPresentationFormatTypes::Init(exports);
  }

  class GattServiceUuids : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattServiceUuids").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("cyclingSpeedAndCadence").ToLocalChecked(), CyclingSpeedAndCadenceGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("battery").ToLocalChecked(), BatteryGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bloodPressure").ToLocalChecked(), BloodPressureGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("genericAccess").ToLocalChecked(), GenericAccessGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("genericAttribute").ToLocalChecked(), GenericAttributeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("glucose").ToLocalChecked(), GlucoseGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("healthThermometer").ToLocalChecked(), HealthThermometerGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("heartRate").ToLocalChecked(), HeartRateGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("runningSpeedAndCadence").ToLocalChecked(), RunningSpeedAndCadenceGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("nextDstChange").ToLocalChecked(), NextDstChangeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("alertNotification").ToLocalChecked(), AlertNotificationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("currentTime").ToLocalChecked(), CurrentTimeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cyclingPower").ToLocalChecked(), CyclingPowerGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("deviceInformation").ToLocalChecked(), DeviceInformationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("humanInterfaceDevice").ToLocalChecked(), HumanInterfaceDeviceGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("immediateAlert").ToLocalChecked(), ImmediateAlertGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("linkLoss").ToLocalChecked(), LinkLossGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("locationAndNavigation").ToLocalChecked(), LocationAndNavigationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("phoneAlertStatus").ToLocalChecked(), PhoneAlertStatusGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("referenceTimeUpdate").ToLocalChecked(), ReferenceTimeUpdateGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("scanParameters").ToLocalChecked(), ScanParametersGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("txPower").ToLocalChecked(), TxPowerGetter);

      Nan::Set(exports, Nan::New<String>("GattServiceUuids").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattServiceUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattServiceUuids *wrapperInstance = new GattServiceUuids(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattServiceUuids(winRtInstance));
    }


  




    static void CyclingSpeedAndCadenceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::CyclingSpeedAndCadence;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BatteryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::Battery;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BloodPressureGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::BloodPressure;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GenericAccessGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::GenericAccess;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GenericAttributeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::GenericAttribute;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GlucoseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::Glucose;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HealthThermometerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::HealthThermometer;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HeartRateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::HeartRate;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RunningSpeedAndCadenceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::RunningSpeedAndCadence;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NextDstChangeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::NextDstChange;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AlertNotificationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::AlertNotification;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CurrentTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::CurrentTime;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingPowerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::CyclingPower;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DeviceInformationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::DeviceInformation;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HumanInterfaceDeviceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::HumanInterfaceDevice;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ImmediateAlertGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::ImmediateAlert;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LinkLossGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::LinkLoss;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LocationAndNavigationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::LocationAndNavigation;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PhoneAlertStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::PhoneAlertStatus;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ReferenceTimeUpdateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::ReferenceTimeUpdate;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ScanParametersGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::ScanParameters;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TxPowerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids::TxPower;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattServiceUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^ UnwrapGattServiceUuids(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattServiceUuids::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattServiceUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattServiceUuids::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceUuids^ UnwrapGattServiceUuids(Local<Value> value)
  {
     return GattServiceUuids::Unwrap<GattServiceUuids>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattServiceUuids(Local<Object> exports)
  {
    GattServiceUuids::Init(exports);
  }

  class GattCharacteristicUuids : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattCharacteristicUuids").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("batteryLevel").ToLocalChecked(), BatteryLevelGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bloodPressureFeature").ToLocalChecked(), BloodPressureFeatureGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bloodPressureMeasurement").ToLocalChecked(), BloodPressureMeasurementGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bodySensorLocation").ToLocalChecked(), BodySensorLocationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cscFeature").ToLocalChecked(), CscFeatureGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cscMeasurement").ToLocalChecked(), CscMeasurementGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("glucoseFeature").ToLocalChecked(), GlucoseFeatureGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("glucoseMeasurement").ToLocalChecked(), GlucoseMeasurementGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("glucoseMeasurementContext").ToLocalChecked(), GlucoseMeasurementContextGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("heartRateControlPoint").ToLocalChecked(), HeartRateControlPointGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("heartRateMeasurement").ToLocalChecked(), HeartRateMeasurementGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("intermediateCuffPressure").ToLocalChecked(), IntermediateCuffPressureGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("intermediateTemperature").ToLocalChecked(), IntermediateTemperatureGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("measurementInterval").ToLocalChecked(), MeasurementIntervalGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("recordAccessControlPoint").ToLocalChecked(), RecordAccessControlPointGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("rscFeature").ToLocalChecked(), RscFeatureGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("rscMeasurement").ToLocalChecked(), RscMeasurementGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("sCControlPoint").ToLocalChecked(), SCControlPointGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("sensorLocation").ToLocalChecked(), SensorLocationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("temperatureMeasurement").ToLocalChecked(), TemperatureMeasurementGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("temperatureType").ToLocalChecked(), TemperatureTypeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("lnFeature").ToLocalChecked(), LnFeatureGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("alertCategoryId").ToLocalChecked(), AlertCategoryIdGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("alertCategoryIdBitMask").ToLocalChecked(), AlertCategoryIdBitMaskGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("alertLevel").ToLocalChecked(), AlertLevelGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("alertNotificationControlPoint").ToLocalChecked(), AlertNotificationControlPointGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("alertStatus").ToLocalChecked(), AlertStatusGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bootKeyboardInputReport").ToLocalChecked(), BootKeyboardInputReportGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bootKeyboardOutputReport").ToLocalChecked(), BootKeyboardOutputReportGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bootMouseInputReport").ToLocalChecked(), BootMouseInputReportGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("currentTime").ToLocalChecked(), CurrentTimeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cyclingPowerControlPoint").ToLocalChecked(), CyclingPowerControlPointGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cyclingPowerFeature").ToLocalChecked(), CyclingPowerFeatureGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cyclingPowerMeasurement").ToLocalChecked(), CyclingPowerMeasurementGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cyclingPowerVector").ToLocalChecked(), CyclingPowerVectorGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("dateTime").ToLocalChecked(), DateTimeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("dayDateTime").ToLocalChecked(), DayDateTimeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("dayOfWeek").ToLocalChecked(), DayOfWeekGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("dstOffset").ToLocalChecked(), DstOffsetGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("exactTime256").ToLocalChecked(), ExactTime256Getter);
      Nan::SetAccessor(constructor, Nan::New<String>("firmwareRevisionString").ToLocalChecked(), FirmwareRevisionStringGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("gapAppearance").ToLocalChecked(), GapAppearanceGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("gapDeviceName").ToLocalChecked(), GapDeviceNameGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("gapPeripheralPreferredConnectionParameters").ToLocalChecked(), GapPeripheralPreferredConnectionParametersGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("gapPeripheralPrivacyFlag").ToLocalChecked(), GapPeripheralPrivacyFlagGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("gapReconnectionAddress").ToLocalChecked(), GapReconnectionAddressGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("gattServiceChanged").ToLocalChecked(), GattServiceChangedGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("hardwareRevisionString").ToLocalChecked(), HardwareRevisionStringGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("hidControlPoint").ToLocalChecked(), HidControlPointGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("hidInformation").ToLocalChecked(), HidInformationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("ieee1107320601RegulatoryCertificationDataList").ToLocalChecked(), Ieee1107320601RegulatoryCertificationDataListGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("lnControlPoint").ToLocalChecked(), LnControlPointGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("localTimeInformation").ToLocalChecked(), LocalTimeInformationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("locationAndSpeed").ToLocalChecked(), LocationAndSpeedGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("manufacturerNameString").ToLocalChecked(), ManufacturerNameStringGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("modelNumberString").ToLocalChecked(), ModelNumberStringGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("navigation").ToLocalChecked(), NavigationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("newAlert").ToLocalChecked(), NewAlertGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("pnpId").ToLocalChecked(), PnpIdGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("positionQuality").ToLocalChecked(), PositionQualityGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("protocolMode").ToLocalChecked(), ProtocolModeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("referenceTimeInformation").ToLocalChecked(), ReferenceTimeInformationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("report").ToLocalChecked(), ReportGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("reportMap").ToLocalChecked(), ReportMapGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("ringerControlPoint").ToLocalChecked(), RingerControlPointGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("ringerSetting").ToLocalChecked(), RingerSettingGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("scanIntervalWindow").ToLocalChecked(), ScanIntervalWindowGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("scanRefresh").ToLocalChecked(), ScanRefreshGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("serialNumberString").ToLocalChecked(), SerialNumberStringGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("softwareRevisionString").ToLocalChecked(), SoftwareRevisionStringGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("supportUnreadAlertCategory").ToLocalChecked(), SupportUnreadAlertCategoryGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("supportedNewAlertCategory").ToLocalChecked(), SupportedNewAlertCategoryGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("systemId").ToLocalChecked(), SystemIdGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("timeAccuracy").ToLocalChecked(), TimeAccuracyGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("timeSource").ToLocalChecked(), TimeSourceGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("timeUpdateControlPoint").ToLocalChecked(), TimeUpdateControlPointGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("timeUpdateState").ToLocalChecked(), TimeUpdateStateGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("timeWithDst").ToLocalChecked(), TimeWithDstGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("timeZone").ToLocalChecked(), TimeZoneGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("txPowerLevel").ToLocalChecked(), TxPowerLevelGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("unreadAlertStatus").ToLocalChecked(), UnreadAlertStatusGetter);

      Nan::Set(exports, Nan::New<String>("GattCharacteristicUuids").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattCharacteristicUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattCharacteristicUuids *wrapperInstance = new GattCharacteristicUuids(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattCharacteristicUuids(winRtInstance));
    }


  




    static void BatteryLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::BatteryLevel;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BloodPressureFeatureGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::BloodPressureFeature;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BloodPressureMeasurementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::BloodPressureMeasurement;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BodySensorLocationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::BodySensorLocation;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CscFeatureGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::CscFeature;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CscMeasurementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::CscMeasurement;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GlucoseFeatureGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::GlucoseFeature;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GlucoseMeasurementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::GlucoseMeasurement;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GlucoseMeasurementContextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::GlucoseMeasurementContext;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HeartRateControlPointGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::HeartRateControlPoint;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HeartRateMeasurementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::HeartRateMeasurement;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IntermediateCuffPressureGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::IntermediateCuffPressure;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IntermediateTemperatureGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::IntermediateTemperature;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MeasurementIntervalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::MeasurementInterval;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RecordAccessControlPointGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::RecordAccessControlPoint;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RscFeatureGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::RscFeature;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RscMeasurementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::RscMeasurement;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SCControlPointGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::SCControlPoint;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SensorLocationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::SensorLocation;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TemperatureMeasurementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::TemperatureMeasurement;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TemperatureTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::TemperatureType;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LnFeatureGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::LnFeature;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AlertCategoryIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::AlertCategoryId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AlertCategoryIdBitMaskGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::AlertCategoryIdBitMask;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AlertLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::AlertLevel;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AlertNotificationControlPointGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::AlertNotificationControlPoint;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AlertStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::AlertStatus;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BootKeyboardInputReportGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::BootKeyboardInputReport;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BootKeyboardOutputReportGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::BootKeyboardOutputReport;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BootMouseInputReportGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::BootMouseInputReport;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CurrentTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::CurrentTime;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingPowerControlPointGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::CyclingPowerControlPoint;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingPowerFeatureGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::CyclingPowerFeature;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingPowerMeasurementGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::CyclingPowerMeasurement;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingPowerVectorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::CyclingPowerVector;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DateTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::DateTime;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DayDateTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::DayDateTime;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DayOfWeekGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::DayOfWeek;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DstOffsetGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::DstOffset;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ExactTime256Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::ExactTime256;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void FirmwareRevisionStringGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::FirmwareRevisionString;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GapAppearanceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::GapAppearance;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GapDeviceNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::GapDeviceName;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GapPeripheralPreferredConnectionParametersGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::GapPeripheralPreferredConnectionParameters;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GapPeripheralPrivacyFlagGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::GapPeripheralPrivacyFlag;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GapReconnectionAddressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::GapReconnectionAddress;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GattServiceChangedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::GattServiceChanged;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HardwareRevisionStringGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::HardwareRevisionString;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HidControlPointGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::HidControlPoint;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HidInformationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::HidInformation;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Ieee1107320601RegulatoryCertificationDataListGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::Ieee1107320601RegulatoryCertificationDataList;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LnControlPointGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::LnControlPoint;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LocalTimeInformationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::LocalTimeInformation;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LocationAndSpeedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::LocationAndSpeed;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ManufacturerNameStringGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::ManufacturerNameString;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ModelNumberStringGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::ModelNumberString;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NavigationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::Navigation;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NewAlertGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::NewAlert;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PnpIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::PnpId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PositionQualityGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::PositionQuality;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProtocolModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::ProtocolMode;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ReferenceTimeInformationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::ReferenceTimeInformation;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ReportGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::Report;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ReportMapGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::ReportMap;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RingerControlPointGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::RingerControlPoint;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RingerSettingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::RingerSetting;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ScanIntervalWindowGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::ScanIntervalWindow;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ScanRefreshGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::ScanRefresh;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SerialNumberStringGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::SerialNumberString;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SoftwareRevisionStringGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::SoftwareRevisionString;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SupportUnreadAlertCategoryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::SupportUnreadAlertCategory;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SupportedNewAlertCategoryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::SupportedNewAlertCategory;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SystemIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::SystemId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TimeAccuracyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::TimeAccuracy;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TimeSourceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::TimeSource;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TimeUpdateControlPointGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::TimeUpdateControlPoint;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TimeUpdateStateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::TimeUpdateState;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TimeWithDstGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::TimeWithDst;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TimeZoneGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::TimeZone;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
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
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::TxPowerLevel;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UnreadAlertStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids::UnreadAlertStatus;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattCharacteristicUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^ UnwrapGattCharacteristicUuids(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattCharacteristicUuids::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattCharacteristicUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattCharacteristicUuids::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicUuids^ UnwrapGattCharacteristicUuids(Local<Value> value)
  {
     return GattCharacteristicUuids::Unwrap<GattCharacteristicUuids>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattCharacteristicUuids(Local<Object> exports)
  {
    GattCharacteristicUuids::Init(exports);
  }

  class GattDescriptorUuids : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattDescriptorUuids").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("characteristicAggregateFormat").ToLocalChecked(), CharacteristicAggregateFormatGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("characteristicExtendedProperties").ToLocalChecked(), CharacteristicExtendedPropertiesGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("characteristicPresentationFormat").ToLocalChecked(), CharacteristicPresentationFormatGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("characteristicUserDescription").ToLocalChecked(), CharacteristicUserDescriptionGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("clientCharacteristicConfiguration").ToLocalChecked(), ClientCharacteristicConfigurationGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("serverCharacteristicConfiguration").ToLocalChecked(), ServerCharacteristicConfigurationGetter);

      Nan::Set(exports, Nan::New<String>("GattDescriptorUuids").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattDescriptorUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattDescriptorUuids *wrapperInstance = new GattDescriptorUuids(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattDescriptorUuids(winRtInstance));
    }


  




    static void CharacteristicAggregateFormatGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids::CharacteristicAggregateFormat;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CharacteristicExtendedPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids::CharacteristicExtendedProperties;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CharacteristicPresentationFormatGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids::CharacteristicPresentationFormat;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CharacteristicUserDescriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids::CharacteristicUserDescription;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ClientCharacteristicConfigurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids::ClientCharacteristicConfiguration;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServerCharacteristicConfigurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::Guid result = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids::ServerCharacteristicConfiguration;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattDescriptorUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^ UnwrapGattDescriptorUuids(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattDescriptorUuids::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattDescriptorUuids(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattDescriptorUuids::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDescriptorUuids^ UnwrapGattDescriptorUuids(Local<Value> value)
  {
     return GattDescriptorUuids::Unwrap<GattDescriptorUuids>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattDescriptorUuids(Local<Object> exports)
  {
    GattDescriptorUuids::Init(exports);
  }

  class GattReliableWriteTransaction : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattReliableWriteTransaction").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "writeValue", WriteValue);
      
            
      Nan::SetPrototypeMethod(localRef, "commitAsync", CommitAsync);
      Nan::SetPrototypeMethod(localRef, "commitWithResultAsync", CommitWithResultAsync);
      
                  
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattReliableWriteTransaction").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattReliableWriteTransaction(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction();
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

      GattReliableWriteTransaction *wrapperInstance = new GattReliableWriteTransaction(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattReliableWriteTransaction(winRtInstance));
    }


    static void CommitAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattReliableWriteTransaction *wrapper = GattReliableWriteTransaction::Unwrap<GattReliableWriteTransaction>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->CommitAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(static_cast<int>(result));
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
    static void CommitWithResultAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattReliableWriteTransaction *wrapper = GattReliableWriteTransaction::Unwrap<GattReliableWriteTransaction>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->CommitWithResultAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattWriteResult(result);
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
  
    static void WriteValue(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^>(info.This()))
      {
        return;
      }

      GattReliableWriteTransaction *wrapper = GattReliableWriteTransaction::Unwrap<GattReliableWriteTransaction>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[1]))
      {
        try
        {
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic^ arg0 = UnwrapGattCharacteristic(info[0]);
          ::Windows::Storage::Streams::IBuffer^ arg1 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          wrapper->_instance->WriteValue(arg0, arg1);
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattReliableWriteTransaction(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^ UnwrapGattReliableWriteTransaction(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattReliableWriteTransaction::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattReliableWriteTransaction(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattReliableWriteTransaction::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReliableWriteTransaction^ UnwrapGattReliableWriteTransaction(Local<Value> value)
  {
     return GattReliableWriteTransaction::Unwrap<GattReliableWriteTransaction>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattReliableWriteTransaction(Local<Object> exports)
  {
    GattReliableWriteTransaction::Init(exports);
  }

  class GattServiceProviderAdvertisingParameters : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattServiceProviderAdvertisingParameters").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isDiscoverable").ToLocalChecked(), IsDiscoverableGetter, IsDiscoverableSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isConnectable").ToLocalChecked(), IsConnectableGetter, IsConnectableSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattServiceProviderAdvertisingParameters").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattServiceProviderAdvertisingParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters();
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

      GattServiceProviderAdvertisingParameters *wrapperInstance = new GattServiceProviderAdvertisingParameters(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattServiceProviderAdvertisingParameters(winRtInstance));
    }


  



    static void IsDiscoverableGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^>(info.This()))
      {
        return;
      }

      GattServiceProviderAdvertisingParameters *wrapper = GattServiceProviderAdvertisingParameters::Unwrap<GattServiceProviderAdvertisingParameters>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsDiscoverable;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsDiscoverableSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^>(info.This()))
      {
        return;
      }

      GattServiceProviderAdvertisingParameters *wrapper = GattServiceProviderAdvertisingParameters::Unwrap<GattServiceProviderAdvertisingParameters>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsDiscoverable = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void IsConnectableGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^>(info.This()))
      {
        return;
      }

      GattServiceProviderAdvertisingParameters *wrapper = GattServiceProviderAdvertisingParameters::Unwrap<GattServiceProviderAdvertisingParameters>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsConnectable;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsConnectableSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^>(info.This()))
      {
        return;
      }

      GattServiceProviderAdvertisingParameters *wrapper = GattServiceProviderAdvertisingParameters::Unwrap<GattServiceProviderAdvertisingParameters>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsConnectable = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattServiceProviderAdvertisingParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ UnwrapGattServiceProviderAdvertisingParameters(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattServiceProviderAdvertisingParameters::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattServiceProviderAdvertisingParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattServiceProviderAdvertisingParameters::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ UnwrapGattServiceProviderAdvertisingParameters(Local<Value> value)
  {
     return GattServiceProviderAdvertisingParameters::Unwrap<GattServiceProviderAdvertisingParameters>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattServiceProviderAdvertisingParameters(Local<Object> exports)
  {
    GattServiceProviderAdvertisingParameters::Init(exports);
  }

  class GattLocalCharacteristicParameters : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattLocalCharacteristicParameters").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("writeProtectionLevel").ToLocalChecked(), WriteProtectionLevelGetter, WriteProtectionLevelSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userDescription").ToLocalChecked(), UserDescriptionGetter, UserDescriptionSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("staticValue").ToLocalChecked(), StaticValueGetter, StaticValueSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("readProtectionLevel").ToLocalChecked(), ReadProtectionLevelGetter, ReadProtectionLevelSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("characteristicProperties").ToLocalChecked(), CharacteristicPropertiesGetter, CharacteristicPropertiesSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("presentationFormats").ToLocalChecked(), PresentationFormatsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattLocalCharacteristicParameters").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattLocalCharacteristicParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters();
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

      GattLocalCharacteristicParameters *wrapperInstance = new GattLocalCharacteristicParameters(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattLocalCharacteristicParameters(winRtInstance));
    }


  



    static void WriteProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel result = wrapper->_instance->WriteProtectionLevel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WriteProtectionLevelSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel winRtValue = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->WriteProtectionLevel = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void UserDescriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->UserDescription;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UserDescriptionSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->UserDescription = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void StaticValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->StaticValue;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StaticValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::IBuffer^ winRtValue = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->StaticValue = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ReadProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel result = wrapper->_instance->ReadProtectionLevel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ReadProtectionLevelSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel winRtValue = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ReadProtectionLevel = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void CharacteristicPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties result = wrapper->_instance->CharacteristicProperties;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CharacteristicPropertiesSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties winRtValue = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->CharacteristicProperties = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void PresentationFormatsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicParameters *wrapper = GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVector<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>^ result = wrapper->_instance->PresentationFormats;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>::CreateVectorWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ val) -> Local<Value> {
              return WrapGattPresentationFormat(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ {
              return UnwrapGattPresentationFormat(value);
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattLocalCharacteristicParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ UnwrapGattLocalCharacteristicParameters(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattLocalCharacteristicParameters::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattLocalCharacteristicParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattLocalCharacteristicParameters::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ UnwrapGattLocalCharacteristicParameters(Local<Value> value)
  {
     return GattLocalCharacteristicParameters::Unwrap<GattLocalCharacteristicParameters>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattLocalCharacteristicParameters(Local<Object> exports)
  {
    GattLocalCharacteristicParameters::Init(exports);
  }

  class GattLocalDescriptorParameters : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattLocalDescriptorParameters").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("writeProtectionLevel").ToLocalChecked(), WriteProtectionLevelGetter, WriteProtectionLevelSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("staticValue").ToLocalChecked(), StaticValueGetter, StaticValueSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("readProtectionLevel").ToLocalChecked(), ReadProtectionLevelGetter, ReadProtectionLevelSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattLocalDescriptorParameters").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattLocalDescriptorParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters();
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

      GattLocalDescriptorParameters *wrapperInstance = new GattLocalDescriptorParameters(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattLocalDescriptorParameters(winRtInstance));
    }


  



    static void WriteProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^>(info.This()))
      {
        return;
      }

      GattLocalDescriptorParameters *wrapper = GattLocalDescriptorParameters::Unwrap<GattLocalDescriptorParameters>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel result = wrapper->_instance->WriteProtectionLevel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WriteProtectionLevelSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^>(info.This()))
      {
        return;
      }

      GattLocalDescriptorParameters *wrapper = GattLocalDescriptorParameters::Unwrap<GattLocalDescriptorParameters>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel winRtValue = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->WriteProtectionLevel = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void StaticValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^>(info.This()))
      {
        return;
      }

      GattLocalDescriptorParameters *wrapper = GattLocalDescriptorParameters::Unwrap<GattLocalDescriptorParameters>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->StaticValue;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StaticValueSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^>(info.This()))
      {
        return;
      }

      GattLocalDescriptorParameters *wrapper = GattLocalDescriptorParameters::Unwrap<GattLocalDescriptorParameters>(info.This());

      try 
      {
        
        ::Windows::Storage::Streams::IBuffer^ winRtValue = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->StaticValue = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ReadProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^>(info.This()))
      {
        return;
      }

      GattLocalDescriptorParameters *wrapper = GattLocalDescriptorParameters::Unwrap<GattLocalDescriptorParameters>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel result = wrapper->_instance->ReadProtectionLevel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ReadProtectionLevelSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^>(info.This()))
      {
        return;
      }

      GattLocalDescriptorParameters *wrapper = GattLocalDescriptorParameters::Unwrap<GattLocalDescriptorParameters>(info.This());

      try 
      {
        
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel winRtValue = static_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ReadProtectionLevel = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattLocalDescriptorParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ UnwrapGattLocalDescriptorParameters(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattLocalDescriptorParameters::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattLocalDescriptorParameters(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattLocalDescriptorParameters::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ UnwrapGattLocalDescriptorParameters(Local<Value> value)
  {
     return GattLocalDescriptorParameters::Unwrap<GattLocalDescriptorParameters>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattLocalDescriptorParameters(Local<Object> exports)
  {
    GattLocalDescriptorParameters::Init(exports);
  }

  class GattServiceProviderResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattServiceProviderResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("error").ToLocalChecked(), ErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("serviceProvider").ToLocalChecked(), ServiceProviderGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattServiceProviderResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattServiceProviderResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattServiceProviderResult *wrapperInstance = new GattServiceProviderResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattServiceProviderResult(winRtInstance));
    }


  



    static void ErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^>(info.This()))
      {
        return;
      }

      GattServiceProviderResult *wrapper = GattServiceProviderResult::Unwrap<GattServiceProviderResult>(info.This());

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
    
    static void ServiceProviderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^>(info.This()))
      {
        return;
      }

      GattServiceProviderResult *wrapper = GattServiceProviderResult::Unwrap<GattServiceProviderResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ result = wrapper->_instance->ServiceProvider;
        info.GetReturnValue().Set(WrapGattServiceProvider(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattServiceProviderResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^ UnwrapGattServiceProviderResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattServiceProviderResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattServiceProviderResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattServiceProviderResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^ UnwrapGattServiceProviderResult(Local<Value> value)
  {
     return GattServiceProviderResult::Unwrap<GattServiceProviderResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattServiceProviderResult(Local<Object> exports)
  {
    GattServiceProviderResult::Init(exports);
  }

  class GattLocalService : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattLocalService").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "createCharacteristicAsync", CreateCharacteristicAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("characteristics").ToLocalChecked(), CharacteristicsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("uuid").ToLocalChecked(), UuidGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattLocalService").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattLocalService(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattLocalService *wrapperInstance = new GattLocalService(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattLocalService(winRtInstance));
    }


    static void CreateCharacteristicAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattLocalService *wrapper = GattLocalService::Unwrap<GattLocalService>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^>^ op;
    

      if (info.Length() == 3
        && NodeRT::Utils::IsGuid(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^>(info[1]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicParameters^ arg1 = UnwrapGattLocalCharacteristicParameters(info[1]);
          
          op = wrapper->_instance->CreateCharacteristicAsync(arg0,arg1);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattLocalCharacteristicResult(result);
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
  



    static void CharacteristicsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^>(info.This()))
      {
        return;
      }

      GattLocalService *wrapper = GattLocalService::Unwrap<GattLocalService>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>^ result = wrapper->_instance->Characteristics;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ val) -> Local<Value> {
              return WrapGattLocalCharacteristic(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ {
              return UnwrapGattLocalCharacteristic(value);
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
    
    static void UuidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^>(info.This()))
      {
        return;
      }

      GattLocalService *wrapper = GattLocalService::Unwrap<GattLocalService>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->Uuid;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattLocalService(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ UnwrapGattLocalService(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattLocalService::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattLocalService(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattLocalService::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ UnwrapGattLocalService(Local<Value> value)
  {
     return GattLocalService::Unwrap<GattLocalService>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattLocalService(Local<Object> exports)
  {
    GattLocalService::Init(exports);
  }

  class GattServiceProvider : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattServiceProvider").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "startAdvertising", StartAdvertising);
      Nan::SetPrototypeMethod(localRef, "stopAdvertising", StopAdvertising);
      
                  
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("advertisementStatus").ToLocalChecked(), AdvertisementStatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("service").ToLocalChecked(), ServiceGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("createAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("GattServiceProvider").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattServiceProvider(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattServiceProvider *wrapperInstance = new GattServiceProvider(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattServiceProvider(winRtInstance));
    }


  
    static void StartAdvertising(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^>(info.This()))
      {
        return;
      }

      GattServiceProvider *wrapper = GattServiceProvider::Unwrap<GattServiceProvider>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->StartAdvertising();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^>(info[0]))
      {
        try
        {
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisingParameters^ arg0 = UnwrapGattServiceProviderAdvertisingParameters(info[0]);
          
          wrapper->_instance->StartAdvertising(arg0);
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
    static void StopAdvertising(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^>(info.This()))
      {
        return;
      }

      GattServiceProvider *wrapper = GattServiceProvider::Unwrap<GattServiceProvider>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->StopAdvertising();
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

    static void CreateAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^>^ op;
      

      if (info.Length() == 2
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          op = ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider::CreateAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattServiceProviderResult(result);
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


    static void AdvertisementStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^>(info.This()))
      {
        return;
      }

      GattServiceProvider *wrapper = GattServiceProvider::Unwrap<GattServiceProvider>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatus result = wrapper->_instance->AdvertisementStatus;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^>(info.This()))
      {
        return;
      }

      GattServiceProvider *wrapper = GattServiceProvider::Unwrap<GattServiceProvider>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalService^ result = wrapper->_instance->Service;
        info.GetReturnValue().Set(WrapGattLocalService(result));
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

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"advertisementStatusChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattServiceProvider *wrapper = GattServiceProvider::Unwrap<GattServiceProvider>(info.This());
      
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

          registrationToken = wrapper->_instance->AdvertisementStatusChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ arg0, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattServiceProvider(arg0);
                  wrappedArg1 = WrapGattServiceProviderAdvertisementStatusChangedEventArgs(arg1);


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
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"advertisementStatusChanged", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"advertisementStatusChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattServiceProvider *wrapper = GattServiceProvider::Unwrap<GattServiceProvider>(info.This());
          wrapper->_instance->AdvertisementStatusChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattServiceProvider(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ UnwrapGattServiceProvider(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattServiceProvider::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattServiceProvider(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattServiceProvider::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProvider^ UnwrapGattServiceProvider(Local<Value> value)
  {
     return GattServiceProvider::Unwrap<GattServiceProvider>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattServiceProvider(Local<Object> exports)
  {
    GattServiceProvider::Init(exports);
  }

  class GattServiceProviderAdvertisementStatusChangedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattServiceProviderAdvertisementStatusChangedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("error").ToLocalChecked(), ErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattServiceProviderAdvertisementStatusChangedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattServiceProviderAdvertisementStatusChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattServiceProviderAdvertisementStatusChangedEventArgs *wrapperInstance = new GattServiceProviderAdvertisementStatusChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattServiceProviderAdvertisementStatusChangedEventArgs(winRtInstance));
    }


  



    static void ErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^>(info.This()))
      {
        return;
      }

      GattServiceProviderAdvertisementStatusChangedEventArgs *wrapper = GattServiceProviderAdvertisementStatusChangedEventArgs::Unwrap<GattServiceProviderAdvertisementStatusChangedEventArgs>(info.This());

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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^>(info.This()))
      {
        return;
      }

      GattServiceProviderAdvertisementStatusChangedEventArgs *wrapper = GattServiceProviderAdvertisementStatusChangedEventArgs::Unwrap<GattServiceProviderAdvertisementStatusChangedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatus result = wrapper->_instance->Status;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattServiceProviderAdvertisementStatusChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ UnwrapGattServiceProviderAdvertisementStatusChangedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattServiceProviderAdvertisementStatusChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattServiceProviderAdvertisementStatusChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattServiceProviderAdvertisementStatusChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattServiceProviderAdvertisementStatusChangedEventArgs^ UnwrapGattServiceProviderAdvertisementStatusChangedEventArgs(Local<Value> value)
  {
     return GattServiceProviderAdvertisementStatusChangedEventArgs::Unwrap<GattServiceProviderAdvertisementStatusChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattServiceProviderAdvertisementStatusChangedEventArgs(Local<Object> exports)
  {
    GattServiceProviderAdvertisementStatusChangedEventArgs::Init(exports);
  }

  class GattLocalCharacteristicResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattLocalCharacteristicResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("characteristic").ToLocalChecked(), CharacteristicGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("error").ToLocalChecked(), ErrorGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattLocalCharacteristicResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattLocalCharacteristicResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattLocalCharacteristicResult *wrapperInstance = new GattLocalCharacteristicResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattLocalCharacteristicResult(winRtInstance));
    }


  



    static void CharacteristicGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicResult *wrapper = GattLocalCharacteristicResult::Unwrap<GattLocalCharacteristicResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ result = wrapper->_instance->Characteristic;
        info.GetReturnValue().Set(WrapGattLocalCharacteristic(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristicResult *wrapper = GattLocalCharacteristicResult::Unwrap<GattLocalCharacteristicResult>(info.This());

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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattLocalCharacteristicResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^ UnwrapGattLocalCharacteristicResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattLocalCharacteristicResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattLocalCharacteristicResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattLocalCharacteristicResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristicResult^ UnwrapGattLocalCharacteristicResult(Local<Value> value)
  {
     return GattLocalCharacteristicResult::Unwrap<GattLocalCharacteristicResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattLocalCharacteristicResult(Local<Object> exports)
  {
    GattLocalCharacteristicResult::Init(exports);
  }

  class GattLocalCharacteristic : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattLocalCharacteristic").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "createDescriptorAsync", CreateDescriptorAsync);
      Nan::SetPrototypeMethod(localRef, "notifyValueAsync", NotifyValueAsync);
      
            
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("characteristicProperties").ToLocalChecked(), CharacteristicPropertiesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("descriptors").ToLocalChecked(), DescriptorsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("presentationFormats").ToLocalChecked(), PresentationFormatsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("readProtectionLevel").ToLocalChecked(), ReadProtectionLevelGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("staticValue").ToLocalChecked(), StaticValueGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("subscribedClients").ToLocalChecked(), SubscribedClientsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userDescription").ToLocalChecked(), UserDescriptionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("uuid").ToLocalChecked(), UuidGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("writeProtectionLevel").ToLocalChecked(), WriteProtectionLevelGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattLocalCharacteristic").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattLocalCharacteristic(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattLocalCharacteristic *wrapperInstance = new GattLocalCharacteristic(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattLocalCharacteristic(winRtInstance));
    }


    static void CreateDescriptorAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^>^ op;
    

      if (info.Length() == 3
        && NodeRT::Utils::IsGuid(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^>(info[1]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorParameters^ arg1 = UnwrapGattLocalDescriptorParameters(info[1]);
          
          op = wrapper->_instance->CreateDescriptorAsync(arg0,arg1);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattLocalDescriptorResult(result);
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
    static void NotifyValueAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      // (jasongin) Hand-patched generated code due to NodeRT bug for method overloads having different return types.
      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^>^>^ op1 = nullptr;
      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^>^ op2 = nullptr;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op1 = wrapper->_instance->NotifyValueAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^>(info[1]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ arg1 = UnwrapGattSubscribedClient(info[1]);
          
          op2 = wrapper->_instance->NotifyValueAsync(arg0,arg1);
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
    
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      if (op1 != nullptr)
      {
      auto opTask = create_task(op1);
      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ val) -> Local<Value> {
              return WrapGattClientNotificationResult(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ {
              return UnwrapGattClientNotificationResult(value);
            }
          );
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
      else
      {
      auto opTask = create_task(op2);
      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattClientNotificationResult(result);
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
    }
  



    static void CharacteristicPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties result = wrapper->_instance->CharacteristicProperties;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DescriptorsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>^ result = wrapper->_instance->Descriptors;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ val) -> Local<Value> {
              return WrapGattLocalDescriptor(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ {
              return UnwrapGattLocalDescriptor(value);
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
    
    static void PresentationFormatsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>^ result = wrapper->_instance->PresentationFormats;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ val) -> Local<Value> {
              return WrapGattPresentationFormat(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattPresentationFormat^ {
              return UnwrapGattPresentationFormat(value);
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
    
    static void ReadProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel result = wrapper->_instance->ReadProtectionLevel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StaticValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->StaticValue;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SubscribedClientsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^>^ result = wrapper->_instance->SubscribedClients;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ val) -> Local<Value> {
              return WrapGattSubscribedClient(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ {
              return UnwrapGattSubscribedClient(value);
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
    
    static void UserDescriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->UserDescription;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UuidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->Uuid;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WriteProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
      {
        return;
      }

      GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel result = wrapper->_instance->WriteProtectionLevel;
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

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"readRequested", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());
      
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

          registrationToken = wrapper->_instance->ReadRequested::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ arg0, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattLocalCharacteristic(arg0);
                  wrappedArg1 = WrapGattReadRequestedEventArgs(arg1);


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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"subscribedClientsChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());
      
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

          registrationToken = wrapper->_instance->SubscribedClientsChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattLocalCharacteristic(arg0);
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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"writeRequested", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());
      
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

          registrationToken = wrapper->_instance->WriteRequested::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ arg0, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattLocalCharacteristic(arg0);
                  wrappedArg1 = WrapGattWriteRequestedEventArgs(arg1);


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
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"readRequested", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"subscribedClientsChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"writeRequested", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"readRequested", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());
          wrapper->_instance->ReadRequested::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"subscribedClientsChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());
          wrapper->_instance->SubscribedClientsChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"writeRequested", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattLocalCharacteristic *wrapper = GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(info.This());
          wrapper->_instance->WriteRequested::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattLocalCharacteristic(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ UnwrapGattLocalCharacteristic(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattLocalCharacteristic::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattLocalCharacteristic(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattLocalCharacteristic::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalCharacteristic^ UnwrapGattLocalCharacteristic(Local<Value> value)
  {
     return GattLocalCharacteristic::Unwrap<GattLocalCharacteristic>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattLocalCharacteristic(Local<Object> exports)
  {
    GattLocalCharacteristic::Init(exports);
  }

  class GattLocalDescriptorResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattLocalDescriptorResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("descriptor").ToLocalChecked(), DescriptorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("error").ToLocalChecked(), ErrorGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattLocalDescriptorResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattLocalDescriptorResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattLocalDescriptorResult *wrapperInstance = new GattLocalDescriptorResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattLocalDescriptorResult(winRtInstance));
    }


  



    static void DescriptorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^>(info.This()))
      {
        return;
      }

      GattLocalDescriptorResult *wrapper = GattLocalDescriptorResult::Unwrap<GattLocalDescriptorResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ result = wrapper->_instance->Descriptor;
        info.GetReturnValue().Set(WrapGattLocalDescriptor(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^>(info.This()))
      {
        return;
      }

      GattLocalDescriptorResult *wrapper = GattLocalDescriptorResult::Unwrap<GattLocalDescriptorResult>(info.This());

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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattLocalDescriptorResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^ UnwrapGattLocalDescriptorResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattLocalDescriptorResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattLocalDescriptorResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattLocalDescriptorResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptorResult^ UnwrapGattLocalDescriptorResult(Local<Value> value)
  {
     return GattLocalDescriptorResult::Unwrap<GattLocalDescriptorResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattLocalDescriptorResult(Local<Object> exports)
  {
    GattLocalDescriptorResult::Init(exports);
  }

  class GattLocalDescriptor : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattLocalDescriptor").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                        
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("readProtectionLevel").ToLocalChecked(), ReadProtectionLevelGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("staticValue").ToLocalChecked(), StaticValueGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("uuid").ToLocalChecked(), UuidGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("writeProtectionLevel").ToLocalChecked(), WriteProtectionLevelGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattLocalDescriptor").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattLocalDescriptor(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattLocalDescriptor *wrapperInstance = new GattLocalDescriptor(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattLocalDescriptor(winRtInstance));
    }


  



    static void ReadProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(info.This()))
      {
        return;
      }

      GattLocalDescriptor *wrapper = GattLocalDescriptor::Unwrap<GattLocalDescriptor>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel result = wrapper->_instance->ReadProtectionLevel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StaticValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(info.This()))
      {
        return;
      }

      GattLocalDescriptor *wrapper = GattLocalDescriptor::Unwrap<GattLocalDescriptor>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->StaticValue;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UuidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(info.This()))
      {
        return;
      }

      GattLocalDescriptor *wrapper = GattLocalDescriptor::Unwrap<GattLocalDescriptor>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->Uuid;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WriteProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(info.This()))
      {
        return;
      }

      GattLocalDescriptor *wrapper = GattLocalDescriptor::Unwrap<GattLocalDescriptor>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattProtectionLevel result = wrapper->_instance->WriteProtectionLevel;
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

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"readRequested", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattLocalDescriptor *wrapper = GattLocalDescriptor::Unwrap<GattLocalDescriptor>(info.This());
      
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

          registrationToken = wrapper->_instance->ReadRequested::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ arg0, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattLocalDescriptor(arg0);
                  wrappedArg1 = WrapGattReadRequestedEventArgs(arg1);


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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"writeRequested", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattLocalDescriptor *wrapper = GattLocalDescriptor::Unwrap<GattLocalDescriptor>(info.This());
      
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

          registrationToken = wrapper->_instance->WriteRequested::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ arg0, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattLocalDescriptor(arg0);
                  wrappedArg1 = WrapGattWriteRequestedEventArgs(arg1);


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
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"readRequested", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"writeRequested", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"readRequested", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattLocalDescriptor *wrapper = GattLocalDescriptor::Unwrap<GattLocalDescriptor>(info.This());
          wrapper->_instance->ReadRequested::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"writeRequested", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattLocalDescriptor *wrapper = GattLocalDescriptor::Unwrap<GattLocalDescriptor>(info.This());
          wrapper->_instance->WriteRequested::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattLocalDescriptor(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ UnwrapGattLocalDescriptor(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattLocalDescriptor::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattLocalDescriptor(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattLocalDescriptor::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattLocalDescriptor^ UnwrapGattLocalDescriptor(Local<Value> value)
  {
     return GattLocalDescriptor::Unwrap<GattLocalDescriptor>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattLocalDescriptor(Local<Object> exports)
  {
    GattLocalDescriptor::Init(exports);
  }

  class GattSubscribedClient : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattSubscribedClient").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                        
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maxNotificationSize").ToLocalChecked(), MaxNotificationSizeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("session").ToLocalChecked(), SessionGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattSubscribedClient").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattSubscribedClient(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattSubscribedClient *wrapperInstance = new GattSubscribedClient(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattSubscribedClient(winRtInstance));
    }


  



    static void MaxNotificationSizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^>(info.This()))
      {
        return;
      }

      GattSubscribedClient *wrapper = GattSubscribedClient::Unwrap<GattSubscribedClient>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->MaxNotificationSize;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SessionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^>(info.This()))
      {
        return;
      }

      GattSubscribedClient *wrapper = GattSubscribedClient::Unwrap<GattSubscribedClient>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ result = wrapper->_instance->Session;
        info.GetReturnValue().Set(WrapGattSession(result));
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

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"maxNotificationSizeChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattSubscribedClient *wrapper = GattSubscribedClient::Unwrap<GattSubscribedClient>(info.This());
      
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

          registrationToken = wrapper->_instance->MaxNotificationSizeChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattSubscribedClient(arg0);
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
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"maxNotificationSizeChanged", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"maxNotificationSizeChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattSubscribedClient *wrapper = GattSubscribedClient::Unwrap<GattSubscribedClient>(info.This());
          wrapper->_instance->MaxNotificationSizeChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattSubscribedClient(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ UnwrapGattSubscribedClient(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattSubscribedClient::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattSubscribedClient(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattSubscribedClient::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ UnwrapGattSubscribedClient(Local<Value> value)
  {
     return GattSubscribedClient::Unwrap<GattSubscribedClient>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattSubscribedClient(Local<Object> exports)
  {
    GattSubscribedClient::Init(exports);
  }

  class GattReadRequestedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattReadRequestedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
      
            
      Nan::SetPrototypeMethod(localRef, "getRequestAsync", GetRequestAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("session").ToLocalChecked(), SessionGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattReadRequestedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattReadRequestedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattReadRequestedEventArgs *wrapperInstance = new GattReadRequestedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattReadRequestedEventArgs(winRtInstance));
    }


    static void GetRequestAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattReadRequestedEventArgs *wrapper = GattReadRequestedEventArgs::Unwrap<GattReadRequestedEventArgs>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetRequestAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattReadRequest(result);
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
  
    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^>(info.This()))
      {
        return;
      }

      GattReadRequestedEventArgs *wrapper = GattReadRequestedEventArgs::Unwrap<GattReadRequestedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
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



    static void SessionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^>(info.This()))
      {
        return;
      }

      GattReadRequestedEventArgs *wrapper = GattReadRequestedEventArgs::Unwrap<GattReadRequestedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ result = wrapper->_instance->Session;
        info.GetReturnValue().Set(WrapGattSession(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattReadRequestedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ UnwrapGattReadRequestedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattReadRequestedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattReadRequestedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattReadRequestedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequestedEventArgs^ UnwrapGattReadRequestedEventArgs(Local<Value> value)
  {
     return GattReadRequestedEventArgs::Unwrap<GattReadRequestedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattReadRequestedEventArgs(Local<Object> exports)
  {
    GattReadRequestedEventArgs::Init(exports);
  }

  class GattWriteRequestedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattWriteRequestedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
      
            
      Nan::SetPrototypeMethod(localRef, "getRequestAsync", GetRequestAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("session").ToLocalChecked(), SessionGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattWriteRequestedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattWriteRequestedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattWriteRequestedEventArgs *wrapperInstance = new GattWriteRequestedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattWriteRequestedEventArgs(winRtInstance));
    }


    static void GetRequestAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      GattWriteRequestedEventArgs *wrapper = GattWriteRequestedEventArgs::Unwrap<GattWriteRequestedEventArgs>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetRequestAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapGattWriteRequest(result);
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
  
    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^>(info.This()))
      {
        return;
      }

      GattWriteRequestedEventArgs *wrapper = GattWriteRequestedEventArgs::Unwrap<GattWriteRequestedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
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



    static void SessionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^>(info.This()))
      {
        return;
      }

      GattWriteRequestedEventArgs *wrapper = GattWriteRequestedEventArgs::Unwrap<GattWriteRequestedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession^ result = wrapper->_instance->Session;
        info.GetReturnValue().Set(WrapGattSession(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattWriteRequestedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ UnwrapGattWriteRequestedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattWriteRequestedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattWriteRequestedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattWriteRequestedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequestedEventArgs^ UnwrapGattWriteRequestedEventArgs(Local<Value> value)
  {
     return GattWriteRequestedEventArgs::Unwrap<GattWriteRequestedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattWriteRequestedEventArgs(Local<Object> exports)
  {
    GattWriteRequestedEventArgs::Init(exports);
  }

  class GattClientNotificationResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattClientNotificationResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protocolError").ToLocalChecked(), ProtocolErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("subscribedClient").ToLocalChecked(), SubscribedClientGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattClientNotificationResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattClientNotificationResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattClientNotificationResult *wrapperInstance = new GattClientNotificationResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattClientNotificationResult(winRtInstance));
    }


  



    static void ProtocolErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^>(info.This()))
      {
        return;
      }

      GattClientNotificationResult *wrapper = GattClientNotificationResult::Unwrap<GattClientNotificationResult>(info.This());

      try 
      {
        ::Platform::IBox<unsigned char>^ result = wrapper->_instance->ProtocolError;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^>(info.This()))
      {
        return;
      }

      GattClientNotificationResult *wrapper = GattClientNotificationResult::Unwrap<GattClientNotificationResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SubscribedClientGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^>(info.This()))
      {
        return;
      }

      GattClientNotificationResult *wrapper = GattClientNotificationResult::Unwrap<GattClientNotificationResult>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSubscribedClient^ result = wrapper->_instance->SubscribedClient;
        info.GetReturnValue().Set(WrapGattSubscribedClient(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattClientNotificationResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ UnwrapGattClientNotificationResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattClientNotificationResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattClientNotificationResult(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattClientNotificationResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattClientNotificationResult^ UnwrapGattClientNotificationResult(Local<Value> value)
  {
     return GattClientNotificationResult::Unwrap<GattClientNotificationResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattClientNotificationResult(Local<Object> exports)
  {
    GattClientNotificationResult::Init(exports);
  }

  class GattReadRequest : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattReadRequest").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "respondWithValue", RespondWithValue);
      Nan::SetPrototypeMethod(localRef, "respondWithProtocolError", RespondWithProtocolError);
      
                  
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("length").ToLocalChecked(), LengthGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("offset").ToLocalChecked(), OffsetGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("state").ToLocalChecked(), StateGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattReadRequest").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattReadRequest(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattReadRequest *wrapperInstance = new GattReadRequest(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattReadRequest(winRtInstance));
    }


  
    static void RespondWithValue(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^>(info.This()))
      {
        return;
      }

      GattReadRequest *wrapper = GattReadRequest::Unwrap<GattReadRequest>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          wrapper->_instance->RespondWithValue(arg0);
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
    static void RespondWithProtocolError(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^>(info.This()))
      {
        return;
      }

      GattReadRequest *wrapper = GattReadRequest::Unwrap<GattReadRequest>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned char arg0 = static_cast<unsigned char>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->RespondWithProtocolError(arg0);
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^>(info.This()))
      {
        return;
      }

      GattReadRequest *wrapper = GattReadRequest::Unwrap<GattReadRequest>(info.This());

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
    
    static void OffsetGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^>(info.This()))
      {
        return;
      }

      GattReadRequest *wrapper = GattReadRequest::Unwrap<GattReadRequest>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->Offset;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^>(info.This()))
      {
        return;
      }

      GattReadRequest *wrapper = GattReadRequest::Unwrap<GattReadRequest>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestState result = wrapper->_instance->State;
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

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"stateChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattReadRequest *wrapper = GattReadRequest::Unwrap<GattReadRequest>(info.This());
      
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

          registrationToken = wrapper->_instance->StateChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ arg0, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattReadRequest(arg0);
                  wrappedArg1 = WrapGattRequestStateChangedEventArgs(arg1);


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
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"stateChanged", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"stateChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattReadRequest *wrapper = GattReadRequest::Unwrap<GattReadRequest>(info.This());
          wrapper->_instance->StateChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattReadRequest(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ UnwrapGattReadRequest(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattReadRequest::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattReadRequest(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattReadRequest::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattReadRequest^ UnwrapGattReadRequest(Local<Value> value)
  {
     return GattReadRequest::Unwrap<GattReadRequest>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattReadRequest(Local<Object> exports)
  {
    GattReadRequest::Init(exports);
  }

  class GattRequestStateChangedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattRequestStateChangedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("error").ToLocalChecked(), ErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("state").ToLocalChecked(), StateGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattRequestStateChangedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattRequestStateChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattRequestStateChangedEventArgs *wrapperInstance = new GattRequestStateChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattRequestStateChangedEventArgs(winRtInstance));
    }


  



    static void ErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^>(info.This()))
      {
        return;
      }

      GattRequestStateChangedEventArgs *wrapper = GattRequestStateChangedEventArgs::Unwrap<GattRequestStateChangedEventArgs>(info.This());

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
    
    static void StateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^>(info.This()))
      {
        return;
      }

      GattRequestStateChangedEventArgs *wrapper = GattRequestStateChangedEventArgs::Unwrap<GattRequestStateChangedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestState result = wrapper->_instance->State;
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
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattRequestStateChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ UnwrapGattRequestStateChangedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattRequestStateChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattRequestStateChangedEventArgs(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattRequestStateChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ UnwrapGattRequestStateChangedEventArgs(Local<Value> value)
  {
     return GattRequestStateChangedEventArgs::Unwrap<GattRequestStateChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattRequestStateChangedEventArgs(Local<Object> exports)
  {
    GattRequestStateChangedEventArgs::Init(exports);
  }

  class GattWriteRequest : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GattWriteRequest").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "respond", Respond);
      Nan::SetPrototypeMethod(localRef, "respondWithProtocolError", RespondWithProtocolError);
      
                  
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("offset").ToLocalChecked(), OffsetGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("option").ToLocalChecked(), OptionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("state").ToLocalChecked(), StateGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("value").ToLocalChecked(), ValueGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("GattWriteRequest").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GattWriteRequest(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ instance)
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
      
      ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      GattWriteRequest *wrapperInstance = new GattWriteRequest(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapGattWriteRequest(winRtInstance));
    }


  
    static void Respond(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>(info.This()))
      {
        return;
      }

      GattWriteRequest *wrapper = GattWriteRequest::Unwrap<GattWriteRequest>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Respond();
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
    static void RespondWithProtocolError(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>(info.This()))
      {
        return;
      }

      GattWriteRequest *wrapper = GattWriteRequest::Unwrap<GattWriteRequest>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned char arg0 = static_cast<unsigned char>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->RespondWithProtocolError(arg0);
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



    static void OffsetGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>(info.This()))
      {
        return;
      }

      GattWriteRequest *wrapper = GattWriteRequest::Unwrap<GattWriteRequest>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->Offset;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void OptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>(info.This()))
      {
        return;
      }

      GattWriteRequest *wrapper = GattWriteRequest::Unwrap<GattWriteRequest>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteOption result = wrapper->_instance->Option;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>(info.This()))
      {
        return;
      }

      GattWriteRequest *wrapper = GattWriteRequest::Unwrap<GattWriteRequest>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestState result = wrapper->_instance->State;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>(info.This()))
      {
        return;
      }

      GattWriteRequest *wrapper = GattWriteRequest::Unwrap<GattWriteRequest>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->Value;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
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

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"stateChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        GattWriteRequest *wrapper = GattWriteRequest::Unwrap<GattWriteRequest>(info.This());
      
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

          registrationToken = wrapper->_instance->StateChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ arg0, ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattRequestStateChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapGattWriteRequest(arg0);
                  wrappedArg1 = WrapGattRequestStateChangedEventArgs(arg1);


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
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"stateChanged", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"stateChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          GattWriteRequest *wrapper = GattWriteRequest::Unwrap<GattWriteRequest>(info.This());
          wrapper->_instance->StateChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGattWriteRequest(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ UnwrapGattWriteRequest(Local<Value> value);
  };
  Persistent<FunctionTemplate> GattWriteRequest::s_constructorTemplate;

  v8::Local<v8::Value> WrapGattWriteRequest(::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GattWriteRequest::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteRequest^ UnwrapGattWriteRequest(Local<Value> value)
  {
     return GattWriteRequest::Unwrap<GattWriteRequest>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGattWriteRequest(Local<Object> exports)
  {
    GattWriteRequest::Init(exports);
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
  
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattSessionStatusEnum(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattCharacteristicPropertiesEnum(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattClientCharacteristicConfigurationDescriptorValueEnum(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattProtectionLevelEnum(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattWriteOptionEnum(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattCommunicationStatusEnum(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattSharingModeEnum(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattOpenStatusEnum(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattRequestStateEnum(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattServiceProviderAdvertisementStatusEnum(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattDeviceService(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattDeviceServicesResult(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattProtocolError(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattSession(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattSessionStatusChangedEventArgs(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattCharacteristic(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattCharacteristicsResult(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattDescriptor(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattPresentationFormat(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattReadResult(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattReadClientCharacteristicConfigurationDescriptorResult(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattValueChangedEventArgs(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattDescriptorsResult(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattWriteResult(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattPresentationFormatTypes(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattServiceUuids(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattCharacteristicUuids(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattDescriptorUuids(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattReliableWriteTransaction(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattServiceProviderAdvertisingParameters(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattLocalCharacteristicParameters(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattLocalDescriptorParameters(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattServiceProviderResult(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattLocalService(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattServiceProvider(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattServiceProviderAdvertisementStatusChangedEventArgs(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattLocalCharacteristicResult(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattLocalCharacteristic(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattLocalDescriptorResult(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattLocalDescriptor(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattSubscribedClient(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattReadRequestedEventArgs(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattWriteRequestedEventArgs(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattClientNotificationResult(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattReadRequest(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattRequestStateChangedEventArgs(target);
  NodeRT::Windows::Devices::Bluetooth::GenericAttributeProfile::InitGattWriteRequest(target);

  NodeRT::Utils::RegisterNameSpace("Windows.Devices.Bluetooth.GenericAttributeProfile", target);
}


NODE_MODULE(binding, init)