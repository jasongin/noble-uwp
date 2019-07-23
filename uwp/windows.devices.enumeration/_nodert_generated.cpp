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

namespace NodeRT { namespace Windows { namespace Devices { namespace Enumeration { 

  v8::Local<v8::Value> WrapDeviceConnectionChangeTriggerDetails(::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^ UnwrapDeviceConnectionChangeTriggerDetails(Local<Value> value);
  
  v8::Local<v8::Value> WrapDevicePickerAppearance(::Windows::Devices::Enumeration::DevicePickerAppearance^ wintRtInstance);
  ::Windows::Devices::Enumeration::DevicePickerAppearance^ UnwrapDevicePickerAppearance(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceSelectedEventArgs(::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ UnwrapDeviceSelectedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceDisconnectButtonClickedEventArgs(::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ UnwrapDeviceDisconnectButtonClickedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapDevicePickerFilter(::Windows::Devices::Enumeration::DevicePickerFilter^ wintRtInstance);
  ::Windows::Devices::Enumeration::DevicePickerFilter^ UnwrapDevicePickerFilter(Local<Value> value);
  
  v8::Local<v8::Value> WrapDevicePicker(::Windows::Devices::Enumeration::DevicePicker^ wintRtInstance);
  ::Windows::Devices::Enumeration::DevicePicker^ UnwrapDevicePicker(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceThumbnail(::Windows::Devices::Enumeration::DeviceThumbnail^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceThumbnail^ UnwrapDeviceThumbnail(Local<Value> value);
  
  v8::Local<v8::Value> WrapEnclosureLocation(::Windows::Devices::Enumeration::EnclosureLocation^ wintRtInstance);
  ::Windows::Devices::Enumeration::EnclosureLocation^ UnwrapEnclosureLocation(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceInformationUpdate(::Windows::Devices::Enumeration::DeviceInformationUpdate^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceInformationUpdate^ UnwrapDeviceInformationUpdate(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceInformationCollection(::Windows::Devices::Enumeration::DeviceInformationCollection^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceInformationCollection^ UnwrapDeviceInformationCollection(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceWatcher(::Windows::Devices::Enumeration::DeviceWatcher^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceWatcher^ UnwrapDeviceWatcher(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceInformation(::Windows::Devices::Enumeration::DeviceInformation^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceInformation^ UnwrapDeviceInformation(Local<Value> value);
  
  v8::Local<v8::Value> WrapDevicePairingResult(::Windows::Devices::Enumeration::DevicePairingResult^ wintRtInstance);
  ::Windows::Devices::Enumeration::DevicePairingResult^ UnwrapDevicePairingResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceUnpairingResult(::Windows::Devices::Enumeration::DeviceUnpairingResult^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceUnpairingResult^ UnwrapDeviceUnpairingResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapIDevicePairingSettings(::Windows::Devices::Enumeration::IDevicePairingSettings^ wintRtInstance);
  ::Windows::Devices::Enumeration::IDevicePairingSettings^ UnwrapIDevicePairingSettings(Local<Value> value);
  
  v8::Local<v8::Value> WrapDevicePairingRequestedEventArgs(::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ wintRtInstance);
  ::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ UnwrapDevicePairingRequestedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceInformationCustomPairing(::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ UnwrapDeviceInformationCustomPairing(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceInformationPairing(::Windows::Devices::Enumeration::DeviceInformationPairing^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceInformationPairing^ UnwrapDeviceInformationPairing(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceAccessChangedEventArgs(::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ UnwrapDeviceAccessChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceAccessInformation(::Windows::Devices::Enumeration::DeviceAccessInformation^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceAccessInformation^ UnwrapDeviceAccessInformation(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceWatcherEvent(::Windows::Devices::Enumeration::DeviceWatcherEvent^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceWatcherEvent^ UnwrapDeviceWatcherEvent(Local<Value> value);
  
  v8::Local<v8::Value> WrapDeviceWatcherTriggerDetails(::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^ wintRtInstance);
  ::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^ UnwrapDeviceWatcherTriggerDetails(Local<Value> value);
  


  static void InitDevicePickerDisplayStatusOptionsEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DevicePickerDisplayStatusOptions").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePickerDisplayStatusOptions::None)));
	Nan::Set(enumObject, Nan::New<String>("showProgress").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePickerDisplayStatusOptions::ShowProgress)));
	Nan::Set(enumObject, Nan::New<String>("showDisconnectButton").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePickerDisplayStatusOptions::ShowDisconnectButton)));
	Nan::Set(enumObject, Nan::New<String>("showRetryButton").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePickerDisplayStatusOptions::ShowRetryButton)));
  }


  static void InitDeviceClassEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DeviceClass").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("all").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceClass::All)));
	Nan::Set(enumObject, Nan::New<String>("audioCapture").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceClass::AudioCapture)));
	Nan::Set(enumObject, Nan::New<String>("audioRender").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceClass::AudioRender)));
	Nan::Set(enumObject, Nan::New<String>("portableStorageDevice").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceClass::PortableStorageDevice)));
	Nan::Set(enumObject, Nan::New<String>("videoCapture").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceClass::VideoCapture)));
	Nan::Set(enumObject, Nan::New<String>("imageScanner").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceClass::ImageScanner)));
	Nan::Set(enumObject, Nan::New<String>("location").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceClass::Location)));
  }


  static void InitDeviceWatcherStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DeviceWatcherStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("created").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceWatcherStatus::Created)));
	Nan::Set(enumObject, Nan::New<String>("started").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceWatcherStatus::Started)));
	Nan::Set(enumObject, Nan::New<String>("enumerationCompleted").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceWatcherStatus::EnumerationCompleted)));
	Nan::Set(enumObject, Nan::New<String>("stopping").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceWatcherStatus::Stopping)));
	Nan::Set(enumObject, Nan::New<String>("stopped").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceWatcherStatus::Stopped)));
	Nan::Set(enumObject, Nan::New<String>("aborted").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceWatcherStatus::Aborted)));
  }


  static void InitPanelEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("Panel").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::Panel::Unknown)));
	Nan::Set(enumObject, Nan::New<String>("front").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::Panel::Front)));
	Nan::Set(enumObject, Nan::New<String>("back").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::Panel::Back)));
	Nan::Set(enumObject, Nan::New<String>("top").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::Panel::Top)));
	Nan::Set(enumObject, Nan::New<String>("bottom").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::Panel::Bottom)));
	Nan::Set(enumObject, Nan::New<String>("left").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::Panel::Left)));
	Nan::Set(enumObject, Nan::New<String>("right").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::Panel::Right)));
  }


  static void InitDeviceInformationKindEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DeviceInformationKind").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceInformationKind::Unknown)));
	Nan::Set(enumObject, Nan::New<String>("deviceInterface").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceInformationKind::DeviceInterface)));
	Nan::Set(enumObject, Nan::New<String>("deviceContainer").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceInformationKind::DeviceContainer)));
	Nan::Set(enumObject, Nan::New<String>("device").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceInformationKind::Device)));
	Nan::Set(enumObject, Nan::New<String>("deviceInterfaceClass").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceInformationKind::DeviceInterfaceClass)));
	Nan::Set(enumObject, Nan::New<String>("associationEndpoint").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceInformationKind::AssociationEndpoint)));
	Nan::Set(enumObject, Nan::New<String>("associationEndpointContainer").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceInformationKind::AssociationEndpointContainer)));
	Nan::Set(enumObject, Nan::New<String>("associationEndpointService").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceInformationKind::AssociationEndpointService)));
  }


  static void InitDeviceWatcherEventKindEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DeviceWatcherEventKind").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("add").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceWatcherEventKind::Add)));
	Nan::Set(enumObject, Nan::New<String>("update").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceWatcherEventKind::Update)));
	Nan::Set(enumObject, Nan::New<String>("remove").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceWatcherEventKind::Remove)));
  }


  static void InitDevicePairingKindsEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DevicePairingKinds").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingKinds::None)));
	Nan::Set(enumObject, Nan::New<String>("confirmOnly").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingKinds::ConfirmOnly)));
	Nan::Set(enumObject, Nan::New<String>("displayPin").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingKinds::DisplayPin)));
	Nan::Set(enumObject, Nan::New<String>("providePin").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingKinds::ProvidePin)));
	Nan::Set(enumObject, Nan::New<String>("confirmPinMatch").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingKinds::ConfirmPinMatch)));
  }


  static void InitDevicePairingResultStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DevicePairingResultStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("paired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::Paired)));
	Nan::Set(enumObject, Nan::New<String>("notReadyToPair").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::NotReadyToPair)));
	Nan::Set(enumObject, Nan::New<String>("notPaired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::NotPaired)));
	Nan::Set(enumObject, Nan::New<String>("alreadyPaired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::AlreadyPaired)));
	Nan::Set(enumObject, Nan::New<String>("connectionRejected").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::ConnectionRejected)));
	Nan::Set(enumObject, Nan::New<String>("tooManyConnections").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::TooManyConnections)));
	Nan::Set(enumObject, Nan::New<String>("hardwareFailure").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::HardwareFailure)));
	Nan::Set(enumObject, Nan::New<String>("authenticationTimeout").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::AuthenticationTimeout)));
	Nan::Set(enumObject, Nan::New<String>("authenticationNotAllowed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::AuthenticationNotAllowed)));
	Nan::Set(enumObject, Nan::New<String>("authenticationFailure").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::AuthenticationFailure)));
	Nan::Set(enumObject, Nan::New<String>("noSupportedProfiles").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::NoSupportedProfiles)));
	Nan::Set(enumObject, Nan::New<String>("protectionLevelCouldNotBeMet").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::ProtectionLevelCouldNotBeMet)));
	Nan::Set(enumObject, Nan::New<String>("accessDenied").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::AccessDenied)));
	Nan::Set(enumObject, Nan::New<String>("invalidCeremonyData").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::InvalidCeremonyData)));
	Nan::Set(enumObject, Nan::New<String>("pairingCanceled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::PairingCanceled)));
	Nan::Set(enumObject, Nan::New<String>("operationAlreadyInProgress").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::OperationAlreadyInProgress)));
	Nan::Set(enumObject, Nan::New<String>("requiredHandlerNotRegistered").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::RequiredHandlerNotRegistered)));
	Nan::Set(enumObject, Nan::New<String>("rejectedByHandler").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::RejectedByHandler)));
	Nan::Set(enumObject, Nan::New<String>("remoteDeviceHasAssociation").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::RemoteDeviceHasAssociation)));
	Nan::Set(enumObject, Nan::New<String>("failed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingResultStatus::Failed)));
  }


  static void InitDeviceUnpairingResultStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DeviceUnpairingResultStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unpaired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceUnpairingResultStatus::Unpaired)));
	Nan::Set(enumObject, Nan::New<String>("alreadyUnpaired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceUnpairingResultStatus::AlreadyUnpaired)));
	Nan::Set(enumObject, Nan::New<String>("operationAlreadyInProgress").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceUnpairingResultStatus::OperationAlreadyInProgress)));
	Nan::Set(enumObject, Nan::New<String>("accessDenied").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceUnpairingResultStatus::AccessDenied)));
	Nan::Set(enumObject, Nan::New<String>("failed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceUnpairingResultStatus::Failed)));
  }


  static void InitDevicePairingProtectionLevelEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DevicePairingProtectionLevel").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("default").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingProtectionLevel::Default)));
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingProtectionLevel::None)));
	Nan::Set(enumObject, Nan::New<String>("encryption").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingProtectionLevel::Encryption)));
	Nan::Set(enumObject, Nan::New<String>("encryptionAndAuthentication").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DevicePairingProtectionLevel::EncryptionAndAuthentication)));
  }


  static void InitDeviceAccessStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DeviceAccessStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unspecified").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceAccessStatus::Unspecified)));
	Nan::Set(enumObject, Nan::New<String>("allowed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceAccessStatus::Allowed)));
	Nan::Set(enumObject, Nan::New<String>("deniedByUser").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceAccessStatus::DeniedByUser)));
	Nan::Set(enumObject, Nan::New<String>("deniedBySystem").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Enumeration::DeviceAccessStatus::DeniedBySystem)));
  }



  
  static bool IsColorJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::UI::Color ColorFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::UI::Color returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> ColorToJsObject(::Windows::UI::Color value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  static bool IsRectJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Foundation::Rect RectFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::Foundation::Rect returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> RectToJsObject(::Windows::Foundation::Rect value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  class DeviceConnectionChangeTriggerDetails : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceConnectionChangeTriggerDetails").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceId").ToLocalChecked(), DeviceIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceConnectionChangeTriggerDetails").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceConnectionChangeTriggerDetails(::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceConnectionChangeTriggerDetails *wrapperInstance = new DeviceConnectionChangeTriggerDetails(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceConnectionChangeTriggerDetails(winRtInstance));
    }


  



    static void DeviceIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^>(info.This()))
      {
        return;
      }

      DeviceConnectionChangeTriggerDetails *wrapper = DeviceConnectionChangeTriggerDetails::Unwrap<DeviceConnectionChangeTriggerDetails>(info.This());

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
    


  private:
    ::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceConnectionChangeTriggerDetails(::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^ UnwrapDeviceConnectionChangeTriggerDetails(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceConnectionChangeTriggerDetails::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceConnectionChangeTriggerDetails(::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceConnectionChangeTriggerDetails::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceConnectionChangeTriggerDetails^ UnwrapDeviceConnectionChangeTriggerDetails(Local<Value> value)
  {
     return DeviceConnectionChangeTriggerDetails::Unwrap<DeviceConnectionChangeTriggerDetails>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceConnectionChangeTriggerDetails(Local<Object> exports)
  {
    DeviceConnectionChangeTriggerDetails::Init(exports);
  }

  class DevicePickerAppearance : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DevicePickerAppearance").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("title").ToLocalChecked(), TitleGetter, TitleSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("selectedForegroundColor").ToLocalChecked(), SelectedForegroundColorGetter, SelectedForegroundColorSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("selectedBackgroundColor").ToLocalChecked(), SelectedBackgroundColorGetter, SelectedBackgroundColorSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("selectedAccentColor").ToLocalChecked(), SelectedAccentColorGetter, SelectedAccentColorSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("foregroundColor").ToLocalChecked(), ForegroundColorGetter, ForegroundColorSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("backgroundColor").ToLocalChecked(), BackgroundColorGetter, BackgroundColorSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("accentColor").ToLocalChecked(), AccentColorGetter, AccentColorSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DevicePickerAppearance").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DevicePickerAppearance(::Windows::Devices::Enumeration::DevicePickerAppearance^ instance)
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
      
      ::Windows::Devices::Enumeration::DevicePickerAppearance^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DevicePickerAppearance^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DevicePickerAppearance *wrapperInstance = new DevicePickerAppearance(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DevicePickerAppearance^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DevicePickerAppearance^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDevicePickerAppearance(winRtInstance));
    }


  



    static void TitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Title;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TitleSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Title = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void SelectedForegroundColorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        ::Windows::UI::Color result = wrapper->_instance->SelectedForegroundColor;
        info.GetReturnValue().Set(NodeRT::Utils::ColorToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SelectedForegroundColorSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsColor(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        
        ::Windows::UI::Color winRtValue = NodeRT::Utils::ColorFromJs(value);

        wrapper->_instance->SelectedForegroundColor = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void SelectedBackgroundColorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        ::Windows::UI::Color result = wrapper->_instance->SelectedBackgroundColor;
        info.GetReturnValue().Set(NodeRT::Utils::ColorToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SelectedBackgroundColorSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsColor(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        
        ::Windows::UI::Color winRtValue = NodeRT::Utils::ColorFromJs(value);

        wrapper->_instance->SelectedBackgroundColor = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void SelectedAccentColorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        ::Windows::UI::Color result = wrapper->_instance->SelectedAccentColor;
        info.GetReturnValue().Set(NodeRT::Utils::ColorToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SelectedAccentColorSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsColor(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        
        ::Windows::UI::Color winRtValue = NodeRT::Utils::ColorFromJs(value);

        wrapper->_instance->SelectedAccentColor = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ForegroundColorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        ::Windows::UI::Color result = wrapper->_instance->ForegroundColor;
        info.GetReturnValue().Set(NodeRT::Utils::ColorToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ForegroundColorSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsColor(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        
        ::Windows::UI::Color winRtValue = NodeRT::Utils::ColorFromJs(value);

        wrapper->_instance->ForegroundColor = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void BackgroundColorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        ::Windows::UI::Color result = wrapper->_instance->BackgroundColor;
        info.GetReturnValue().Set(NodeRT::Utils::ColorToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BackgroundColorSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsColor(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        
        ::Windows::UI::Color winRtValue = NodeRT::Utils::ColorFromJs(value);

        wrapper->_instance->BackgroundColor = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void AccentColorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        ::Windows::UI::Color result = wrapper->_instance->AccentColor;
        info.GetReturnValue().Set(NodeRT::Utils::ColorToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AccentColorSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsColor(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerAppearance^>(info.This()))
      {
        return;
      }

      DevicePickerAppearance *wrapper = DevicePickerAppearance::Unwrap<DevicePickerAppearance>(info.This());

      try 
      {
        
        ::Windows::UI::Color winRtValue = NodeRT::Utils::ColorFromJs(value);

        wrapper->_instance->AccentColor = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Devices::Enumeration::DevicePickerAppearance^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDevicePickerAppearance(::Windows::Devices::Enumeration::DevicePickerAppearance^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DevicePickerAppearance^ UnwrapDevicePickerAppearance(Local<Value> value);
  };
  Persistent<FunctionTemplate> DevicePickerAppearance::s_constructorTemplate;

  v8::Local<v8::Value> WrapDevicePickerAppearance(::Windows::Devices::Enumeration::DevicePickerAppearance^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DevicePickerAppearance::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DevicePickerAppearance^ UnwrapDevicePickerAppearance(Local<Value> value)
  {
     return DevicePickerAppearance::Unwrap<DevicePickerAppearance>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDevicePickerAppearance(Local<Object> exports)
  {
    DevicePickerAppearance::Init(exports);
  }

  class DeviceSelectedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceSelectedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("selectedDevice").ToLocalChecked(), SelectedDeviceGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceSelectedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceSelectedEventArgs(::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceSelectedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceSelectedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceSelectedEventArgs *wrapperInstance = new DeviceSelectedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceSelectedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceSelectedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceSelectedEventArgs(winRtInstance));
    }


  



    static void SelectedDeviceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceSelectedEventArgs^>(info.This()))
      {
        return;
      }

      DeviceSelectedEventArgs *wrapper = DeviceSelectedEventArgs::Unwrap<DeviceSelectedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformation^ result = wrapper->_instance->SelectedDevice;
        info.GetReturnValue().Set(WrapDeviceInformation(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceSelectedEventArgs(::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ UnwrapDeviceSelectedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceSelectedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceSelectedEventArgs(::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceSelectedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ UnwrapDeviceSelectedEventArgs(Local<Value> value)
  {
     return DeviceSelectedEventArgs::Unwrap<DeviceSelectedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceSelectedEventArgs(Local<Object> exports)
  {
    DeviceSelectedEventArgs::Init(exports);
  }

  class DeviceDisconnectButtonClickedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceDisconnectButtonClickedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("device").ToLocalChecked(), DeviceGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceDisconnectButtonClickedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceDisconnectButtonClickedEventArgs(::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceDisconnectButtonClickedEventArgs *wrapperInstance = new DeviceDisconnectButtonClickedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceDisconnectButtonClickedEventArgs(winRtInstance));
    }


  



    static void DeviceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^>(info.This()))
      {
        return;
      }

      DeviceDisconnectButtonClickedEventArgs *wrapper = DeviceDisconnectButtonClickedEventArgs::Unwrap<DeviceDisconnectButtonClickedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformation^ result = wrapper->_instance->Device;
        info.GetReturnValue().Set(WrapDeviceInformation(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceDisconnectButtonClickedEventArgs(::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ UnwrapDeviceDisconnectButtonClickedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceDisconnectButtonClickedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceDisconnectButtonClickedEventArgs(::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceDisconnectButtonClickedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ UnwrapDeviceDisconnectButtonClickedEventArgs(Local<Value> value)
  {
     return DeviceDisconnectButtonClickedEventArgs::Unwrap<DeviceDisconnectButtonClickedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceDisconnectButtonClickedEventArgs(Local<Object> exports)
  {
    DeviceDisconnectButtonClickedEventArgs::Init(exports);
  }

  class DevicePickerFilter : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DevicePickerFilter").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("supportedDeviceClasses").ToLocalChecked(), SupportedDeviceClassesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("supportedDeviceSelectors").ToLocalChecked(), SupportedDeviceSelectorsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DevicePickerFilter").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DevicePickerFilter(::Windows::Devices::Enumeration::DevicePickerFilter^ instance)
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
      
      ::Windows::Devices::Enumeration::DevicePickerFilter^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerFilter^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DevicePickerFilter^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DevicePickerFilter *wrapperInstance = new DevicePickerFilter(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerFilter^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DevicePickerFilter^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DevicePickerFilter^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDevicePickerFilter(winRtInstance));
    }


  



    static void SupportedDeviceClassesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerFilter^>(info.This()))
      {
        return;
      }

      DevicePickerFilter *wrapper = DevicePickerFilter::Unwrap<DevicePickerFilter>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVector<::Windows::Devices::Enumeration::DeviceClass>^ result = wrapper->_instance->SupportedDeviceClasses;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Windows::Devices::Enumeration::DeviceClass>::CreateVectorWrapper(result, 
            [](::Windows::Devices::Enumeration::DeviceClass val) -> Local<Value> {
              return Nan::New<Integer>(static_cast<int>(val));
            },
            [](Local<Value> value) -> bool {
              return value->IsInt32();
            },
            [](Local<Value> value) -> ::Windows::Devices::Enumeration::DeviceClass {
              return static_cast<::Windows::Devices::Enumeration::DeviceClass>(Nan::To<int32_t>(value).FromMaybe(0));
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
    
    static void SupportedDeviceSelectorsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePickerFilter^>(info.This()))
      {
        return;
      }

      DevicePickerFilter *wrapper = DevicePickerFilter::Unwrap<DevicePickerFilter>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVector<::Platform::String^>^ result = wrapper->_instance->SupportedDeviceSelectors;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Platform::String^>::CreateVectorWrapper(result, 
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
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Enumeration::DevicePickerFilter^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDevicePickerFilter(::Windows::Devices::Enumeration::DevicePickerFilter^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DevicePickerFilter^ UnwrapDevicePickerFilter(Local<Value> value);
  };
  Persistent<FunctionTemplate> DevicePickerFilter::s_constructorTemplate;

  v8::Local<v8::Value> WrapDevicePickerFilter(::Windows::Devices::Enumeration::DevicePickerFilter^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DevicePickerFilter::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DevicePickerFilter^ UnwrapDevicePickerFilter(Local<Value> value)
  {
     return DevicePickerFilter::Unwrap<DevicePickerFilter>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDevicePickerFilter(Local<Object> exports)
  {
    DevicePickerFilter::Init(exports);
  }

  class DevicePicker : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DevicePicker").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "show", Show);
      Nan::SetPrototypeMethod(localRef, "hide", Hide);
      Nan::SetPrototypeMethod(localRef, "setDisplayStatus", SetDisplayStatus);
      
            
      Nan::SetPrototypeMethod(localRef, "pickSingleDeviceAsync", PickSingleDeviceAsync);
      
            
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("appearance").ToLocalChecked(), AppearanceGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("filter").ToLocalChecked(), FilterGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("requestedProperties").ToLocalChecked(), RequestedPropertiesGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DevicePicker").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DevicePicker(::Windows::Devices::Enumeration::DevicePicker^ instance)
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
      
      ::Windows::Devices::Enumeration::DevicePicker^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DevicePicker^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Enumeration::DevicePicker();
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

      DevicePicker *wrapperInstance = new DevicePicker(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DevicePicker^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DevicePicker^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDevicePicker(winRtInstance));
    }


    static void PickSingleDeviceAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Enumeration::DeviceInformation^>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsRect(info[0]))
      {
        try
        {
          ::Windows::Foundation::Rect arg0 = NodeRT::Utils::RectFromJs(info[0]);
          
          op = wrapper->_instance->PickSingleDeviceAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsRect(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Rect arg0 = NodeRT::Utils::RectFromJs(info[0]);
          ::Windows::UI::Popups::Placement arg1 = static_cast<::Windows::UI::Popups::Placement>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->PickSingleDeviceAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Enumeration::DeviceInformation^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapDeviceInformation(result);
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
  
    static void Show(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
      {
        return;
      }

      DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsRect(info[0]))
      {
        try
        {
          ::Windows::Foundation::Rect arg0 = NodeRT::Utils::RectFromJs(info[0]);
          
          wrapper->_instance->Show(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsRect(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Rect arg0 = NodeRT::Utils::RectFromJs(info[0]);
          ::Windows::UI::Popups::Placement arg1 = static_cast<::Windows::UI::Popups::Placement>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          wrapper->_instance->Show(arg0, arg1);
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
    static void Hide(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
      {
        return;
      }

      DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Hide();
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
    static void SetDisplayStatus(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
      {
        return;
      }

      DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());

      if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info[0])
        && info[1]->IsString()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Enumeration::DeviceInformation^ arg0 = UnwrapDeviceInformation(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Devices::Enumeration::DevicePickerDisplayStatusOptions arg2 = static_cast<::Windows::Devices::Enumeration::DevicePickerDisplayStatusOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          wrapper->_instance->SetDisplayStatus(arg0, arg1, arg2);
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



    static void AppearanceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
      {
        return;
      }

      DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DevicePickerAppearance^ result = wrapper->_instance->Appearance;
        info.GetReturnValue().Set(WrapDevicePickerAppearance(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void FilterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
      {
        return;
      }

      DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DevicePickerFilter^ result = wrapper->_instance->Filter;
        info.GetReturnValue().Set(WrapDevicePickerFilter(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RequestedPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
      {
        return;
      }

      DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVector<::Platform::String^>^ result = wrapper->_instance->RequestedProperties;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Platform::String^>::CreateVectorWrapper(result, 
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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"devicePickerDismissed", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());
      
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

          registrationToken = wrapper->_instance->DevicePickerDismissed::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Enumeration::DevicePicker^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Enumeration::DevicePicker^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapDevicePicker(arg0);
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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"deviceSelected", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());
      
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

          registrationToken = wrapper->_instance->DeviceSelected::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Enumeration::DevicePicker^, ::Windows::Devices::Enumeration::DeviceSelectedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Enumeration::DevicePicker^ arg0, ::Windows::Devices::Enumeration::DeviceSelectedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapDevicePicker(arg0);
                  wrappedArg1 = WrapDeviceSelectedEventArgs(arg1);


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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"disconnectButtonClicked", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());
      
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

          registrationToken = wrapper->_instance->DisconnectButtonClicked::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Enumeration::DevicePicker^, ::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Enumeration::DevicePicker^ arg0, ::Windows::Devices::Enumeration::DeviceDisconnectButtonClickedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapDevicePicker(arg0);
                  wrappedArg1 = WrapDeviceDisconnectButtonClickedEventArgs(arg1);


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

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"devicePickerDismissed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"deviceSelected", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"disconnectButtonClicked", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"devicePickerDismissed", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());
          wrapper->_instance->DevicePickerDismissed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"deviceSelected", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());
          wrapper->_instance->DeviceSelected::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"disconnectButtonClicked", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePicker^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          DevicePicker *wrapper = DevicePicker::Unwrap<DevicePicker>(info.This());
          wrapper->_instance->DisconnectButtonClicked::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Enumeration::DevicePicker^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDevicePicker(::Windows::Devices::Enumeration::DevicePicker^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DevicePicker^ UnwrapDevicePicker(Local<Value> value);
  };
  Persistent<FunctionTemplate> DevicePicker::s_constructorTemplate;

  v8::Local<v8::Value> WrapDevicePicker(::Windows::Devices::Enumeration::DevicePicker^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DevicePicker::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DevicePicker^ UnwrapDevicePicker(Local<Value> value)
  {
     return DevicePicker::Unwrap<DevicePicker>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDevicePicker(Local<Object> exports)
  {
    DevicePicker::Init(exports);
  }

  class DeviceThumbnail : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceThumbnail").ToLocalChecked());
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
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("contentType").ToLocalChecked(), ContentTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("size").ToLocalChecked(), SizeGetter, SizeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canRead").ToLocalChecked(), CanReadGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canWrite").ToLocalChecked(), CanWriteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceThumbnail").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceThumbnail(::Windows::Devices::Enumeration::DeviceThumbnail^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceThumbnail^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceThumbnail^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceThumbnail *wrapperInstance = new DeviceThumbnail(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceThumbnail^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceThumbnail^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceThumbnail(winRtInstance));
    }


    static void ReadAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Storage::Streams::IBuffer^, unsigned int>^ op;
    

      if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
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
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result);
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned int, unsigned int>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IInputStream^ result;
          result = wrapper->_instance->GetInputStreamAt(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IInputStream", result));
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IOutputStream^ result;
          result = wrapper->_instance->GetOutputStreamAt(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IOutputStream", result));
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IRandomAccessStream^ result;
          result = wrapper->_instance->CloneStream();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IRandomAccessStream", result));
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
	    return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

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




    static void ContentTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

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
    
    static void SizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceThumbnail^>(info.This()))
      {
        return;
      }

      DeviceThumbnail *wrapper = DeviceThumbnail::Unwrap<DeviceThumbnail>(info.This());

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
    ::Windows::Devices::Enumeration::DeviceThumbnail^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceThumbnail(::Windows::Devices::Enumeration::DeviceThumbnail^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceThumbnail^ UnwrapDeviceThumbnail(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceThumbnail::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceThumbnail(::Windows::Devices::Enumeration::DeviceThumbnail^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceThumbnail::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceThumbnail^ UnwrapDeviceThumbnail(Local<Value> value)
  {
     return DeviceThumbnail::Unwrap<DeviceThumbnail>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceThumbnail(Local<Object> exports)
  {
    DeviceThumbnail::Init(exports);
  }

  class EnclosureLocation : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("EnclosureLocation").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("inDock").ToLocalChecked(), InDockGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("inLid").ToLocalChecked(), InLidGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("panel").ToLocalChecked(), PanelGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("rotationAngleInDegreesClockwise").ToLocalChecked(), RotationAngleInDegreesClockwiseGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("EnclosureLocation").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    EnclosureLocation(::Windows::Devices::Enumeration::EnclosureLocation^ instance)
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
      
      ::Windows::Devices::Enumeration::EnclosureLocation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::EnclosureLocation^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::EnclosureLocation^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      EnclosureLocation *wrapperInstance = new EnclosureLocation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::EnclosureLocation^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::EnclosureLocation^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::EnclosureLocation^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapEnclosureLocation(winRtInstance));
    }


  



    static void InDockGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::EnclosureLocation^>(info.This()))
      {
        return;
      }

      EnclosureLocation *wrapper = EnclosureLocation::Unwrap<EnclosureLocation>(info.This());

      try 
      {
        bool result = wrapper->_instance->InDock;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InLidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::EnclosureLocation^>(info.This()))
      {
        return;
      }

      EnclosureLocation *wrapper = EnclosureLocation::Unwrap<EnclosureLocation>(info.This());

      try 
      {
        bool result = wrapper->_instance->InLid;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PanelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::EnclosureLocation^>(info.This()))
      {
        return;
      }

      EnclosureLocation *wrapper = EnclosureLocation::Unwrap<EnclosureLocation>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::Panel result = wrapper->_instance->Panel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RotationAngleInDegreesClockwiseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::EnclosureLocation^>(info.This()))
      {
        return;
      }

      EnclosureLocation *wrapper = EnclosureLocation::Unwrap<EnclosureLocation>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->RotationAngleInDegreesClockwise;
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
    ::Windows::Devices::Enumeration::EnclosureLocation^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapEnclosureLocation(::Windows::Devices::Enumeration::EnclosureLocation^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::EnclosureLocation^ UnwrapEnclosureLocation(Local<Value> value);
  };
  Persistent<FunctionTemplate> EnclosureLocation::s_constructorTemplate;

  v8::Local<v8::Value> WrapEnclosureLocation(::Windows::Devices::Enumeration::EnclosureLocation^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(EnclosureLocation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::EnclosureLocation^ UnwrapEnclosureLocation(Local<Value> value)
  {
     return EnclosureLocation::Unwrap<EnclosureLocation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitEnclosureLocation(Local<Object> exports)
  {
    EnclosureLocation::Init(exports);
  }

  class DeviceInformationUpdate : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceInformationUpdate").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("properties").ToLocalChecked(), PropertiesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("kind").ToLocalChecked(), KindGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceInformationUpdate").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceInformationUpdate(::Windows::Devices::Enumeration::DeviceInformationUpdate^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceInformationUpdate^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationUpdate^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceInformationUpdate^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceInformationUpdate *wrapperInstance = new DeviceInformationUpdate(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationUpdate^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceInformationUpdate^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceInformationUpdate^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceInformationUpdate(winRtInstance));
    }


  



    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationUpdate^>(info.This()))
      {
        return;
      }

      DeviceInformationUpdate *wrapper = DeviceInformationUpdate::Unwrap<DeviceInformationUpdate>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Id;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationUpdate^>(info.This()))
      {
        return;
      }

      DeviceInformationUpdate *wrapper = DeviceInformationUpdate::Unwrap<DeviceInformationUpdate>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Platform::Object^>^ result = wrapper->_instance->Properties;
        info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Platform::Object^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            },
            [](::Platform::Object^ val) -> Local<Value> {
              return CreateOpaqueWrapper(val);
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
    
    static void KindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationUpdate^>(info.This()))
      {
        return;
      }

      DeviceInformationUpdate *wrapper = DeviceInformationUpdate::Unwrap<DeviceInformationUpdate>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformationKind result = wrapper->_instance->Kind;
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
    ::Windows::Devices::Enumeration::DeviceInformationUpdate^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceInformationUpdate(::Windows::Devices::Enumeration::DeviceInformationUpdate^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceInformationUpdate^ UnwrapDeviceInformationUpdate(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceInformationUpdate::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceInformationUpdate(::Windows::Devices::Enumeration::DeviceInformationUpdate^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceInformationUpdate::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceInformationUpdate^ UnwrapDeviceInformationUpdate(Local<Value> value)
  {
     return DeviceInformationUpdate::Unwrap<DeviceInformationUpdate>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceInformationUpdate(Local<Object> exports)
  {
    DeviceInformationUpdate::Init(exports);
  }

  class DeviceInformationCollection : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceInformationCollection").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getAt", GetAt);
      Nan::SetPrototypeMethod(localRef, "indexOf", IndexOf);
      Nan::SetPrototypeMethod(localRef, "getMany", GetMany);
      Nan::SetPrototypeMethod(localRef, "first", First);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceInformationCollection").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceInformationCollection(::Windows::Devices::Enumeration::DeviceInformationCollection^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceInformationCollection^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationCollection^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceInformationCollection^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceInformationCollection *wrapperInstance = new DeviceInformationCollection(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationCollection^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceInformationCollection^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceInformationCollection^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceInformationCollection(winRtInstance));
    }


  
    static void GetAt(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationCollection^>(info.This()))
      {
        return;
      }

      DeviceInformationCollection *wrapper = DeviceInformationCollection::Unwrap<DeviceInformationCollection>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Devices::Enumeration::DeviceInformation^ result;
          result = wrapper->_instance->GetAt(arg0);
          info.GetReturnValue().Set(WrapDeviceInformation(result));
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationCollection^>(info.This()))
      {
        return;
      }

      DeviceInformationCollection *wrapper = DeviceInformationCollection::Unwrap<DeviceInformationCollection>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info[0]))
      {
        try
        {
          ::Windows::Devices::Enumeration::DeviceInformation^ arg0 = UnwrapDeviceInformation(info[0]);
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
    static void First(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationCollection^>(info.This()))
      {
        return;
      }

      DeviceInformationCollection *wrapper = DeviceInformationCollection::Unwrap<DeviceInformationCollection>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Devices::Enumeration::DeviceInformation^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Devices::Enumeration::DeviceInformation^>::CreateIteratorWrapper(result, 
            [](::Windows::Devices::Enumeration::DeviceInformation^ val) -> Local<Value> {
              return WrapDeviceInformation(val);
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





  private:
    ::Windows::Devices::Enumeration::DeviceInformationCollection^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceInformationCollection(::Windows::Devices::Enumeration::DeviceInformationCollection^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceInformationCollection^ UnwrapDeviceInformationCollection(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceInformationCollection::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceInformationCollection(::Windows::Devices::Enumeration::DeviceInformationCollection^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceInformationCollection::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceInformationCollection^ UnwrapDeviceInformationCollection(Local<Value> value)
  {
     return DeviceInformationCollection::Unwrap<DeviceInformationCollection>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceInformationCollection(Local<Object> exports)
  {
    DeviceInformationCollection::Init(exports);
  }

  class DeviceWatcher : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceWatcher").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "start", Start);
      Nan::SetPrototypeMethod(localRef, "stop", Stop);
      Nan::SetPrototypeMethod(localRef, "getBackgroundTrigger", GetBackgroundTrigger);
      
                  
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceWatcher").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceWatcher(::Windows::Devices::Enumeration::DeviceWatcher^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceWatcher^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceWatcher^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceWatcher *wrapperInstance = new DeviceWatcher(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceWatcher^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceWatcher^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceWatcher(winRtInstance));
    }


  
    static void Start(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
      {
        return;
      }

      DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());

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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
      {
        return;
      }

      DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());

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
    static void GetBackgroundTrigger(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
      {
        return;
      }

      DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Enumeration::DeviceWatcherEventKind>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Enumeration::DeviceWatcherEventKind>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Enumeration::DeviceWatcherEventKind>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Devices::Enumeration::DeviceWatcherEventKind>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsInt32();
                 },
                 [](Local<Value> value) -> ::Windows::Devices::Enumeration::DeviceWatcherEventKind {
                   return static_cast<::Windows::Devices::Enumeration::DeviceWatcherEventKind>(Nan::To<int32_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Enumeration::DeviceWatcherEventKind>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Windows::ApplicationModel::Background::DeviceWatcherTrigger^ result;
          result = wrapper->_instance->GetBackgroundTrigger(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.ApplicationModel.Background", "DeviceWatcherTrigger", result));
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



    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
      {
        return;
      }

      DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceWatcherStatus result = wrapper->_instance->Status;
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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"added", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());
      
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

          registrationToken = wrapper->_instance->Added::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Enumeration::DeviceWatcher^, ::Windows::Devices::Enumeration::DeviceInformation^>(
            [callbackObjPtr](::Windows::Devices::Enumeration::DeviceWatcher^ arg0, ::Windows::Devices::Enumeration::DeviceInformation^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapDeviceWatcher(arg0);
                  wrappedArg1 = WrapDeviceInformation(arg1);


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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"enumerationCompleted", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());
      
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

          registrationToken = wrapper->_instance->EnumerationCompleted::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Enumeration::DeviceWatcher^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Enumeration::DeviceWatcher^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapDeviceWatcher(arg0);
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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"removed", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());
      
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

          registrationToken = wrapper->_instance->Removed::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Enumeration::DeviceWatcher^, ::Windows::Devices::Enumeration::DeviceInformationUpdate^>(
            [callbackObjPtr](::Windows::Devices::Enumeration::DeviceWatcher^ arg0, ::Windows::Devices::Enumeration::DeviceInformationUpdate^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapDeviceWatcher(arg0);
                  wrappedArg1 = WrapDeviceInformationUpdate(arg1);


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
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());
      
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
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Enumeration::DeviceWatcher^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Enumeration::DeviceWatcher^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapDeviceWatcher(arg0);
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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"updated", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());
      
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

          registrationToken = wrapper->_instance->Updated::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Enumeration::DeviceWatcher^, ::Windows::Devices::Enumeration::DeviceInformationUpdate^>(
            [callbackObjPtr](::Windows::Devices::Enumeration::DeviceWatcher^ arg0, ::Windows::Devices::Enumeration::DeviceInformationUpdate^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapDeviceWatcher(arg0);
                  wrappedArg1 = WrapDeviceInformationUpdate(arg1);


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

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"added", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"enumerationCompleted", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"removed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"stopped", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"updated", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"added", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());
          wrapper->_instance->Added::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"enumerationCompleted", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());
          wrapper->_instance->EnumerationCompleted::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"removed", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());
          wrapper->_instance->Removed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"stopped", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());
          wrapper->_instance->Stopped::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"updated", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcher^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          DeviceWatcher *wrapper = DeviceWatcher::Unwrap<DeviceWatcher>(info.This());
          wrapper->_instance->Updated::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Enumeration::DeviceWatcher^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceWatcher(::Windows::Devices::Enumeration::DeviceWatcher^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceWatcher^ UnwrapDeviceWatcher(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceWatcher::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceWatcher(::Windows::Devices::Enumeration::DeviceWatcher^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceWatcher::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceWatcher^ UnwrapDeviceWatcher(Local<Value> value)
  {
     return DeviceWatcher::Unwrap<DeviceWatcher>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceWatcher(Local<Object> exports)
  {
    DeviceWatcher::Init(exports);
  }

  class DeviceInformation : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceInformation").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "update", Update);
      
            
      Nan::SetPrototypeMethod(localRef, "getThumbnailAsync", GetThumbnailAsync);
      Nan::SetPrototypeMethod(localRef, "getGlyphThumbnailAsync", GetGlyphThumbnailAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("enclosureLocation").ToLocalChecked(), EnclosureLocationGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isDefault").ToLocalChecked(), IsDefaultGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isEnabled").ToLocalChecked(), IsEnabledGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("properties").ToLocalChecked(), PropertiesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("kind").ToLocalChecked(), KindGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pairing").ToLocalChecked(), PairingGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "getAqsFilterFromDeviceClass", GetAqsFilterFromDeviceClass);
      Nan::SetMethod(constructor, "createWatcher", CreateWatcher);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateFromIdAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("createFromIdAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FindAllAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("findAllAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("DeviceInformation").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceInformation(::Windows::Devices::Enumeration::DeviceInformation^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceInformation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceInformation^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceInformation *wrapperInstance = new DeviceInformation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceInformation^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceInformation^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceInformation(winRtInstance));
    }


    static void GetThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Enumeration::DeviceThumbnail^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetThumbnailAsync();
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Enumeration::DeviceThumbnail^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapDeviceThumbnail(result);
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
    static void GetGlyphThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Enumeration::DeviceThumbnail^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetGlyphThumbnailAsync();
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Enumeration::DeviceThumbnail^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapDeviceThumbnail(result);
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
  
    static void Update(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationUpdate^>(info[0]))
      {
        try
        {
          ::Windows::Devices::Enumeration::DeviceInformationUpdate^ arg0 = UnwrapDeviceInformationUpdate(info[0]);
          
          wrapper->_instance->Update(arg0);
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

    static void CreateFromIdAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Enumeration::DeviceInformation^>^ op;
      

      if (info.Length() == 4
        && info[0]->IsString()
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray())
        && info[2]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
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
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          ::Windows::Devices::Enumeration::DeviceInformationKind arg2 = static_cast<::Windows::Devices::Enumeration::DeviceInformationKind>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = ::Windows::Devices::Enumeration::DeviceInformation::CreateFromIdAsync(arg0,arg1,arg2);
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
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = ::Windows::Devices::Enumeration::DeviceInformation::CreateFromIdAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray()))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
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
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          
          op = ::Windows::Devices::Enumeration::DeviceInformation::CreateFromIdAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Enumeration::DeviceInformation^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapDeviceInformation(result);
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
    static void FindAllAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Enumeration::DeviceInformationCollection^>^ op;
      

      if (info.Length() == 4
        && info[0]->IsString()
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray())
        && info[2]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
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
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          ::Windows::Devices::Enumeration::DeviceInformationKind arg2 = static_cast<::Windows::Devices::Enumeration::DeviceInformationKind>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = ::Windows::Devices::Enumeration::DeviceInformation::FindAllAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::Devices::Enumeration::DeviceInformation::FindAllAsync();
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
          ::Windows::Devices::Enumeration::DeviceClass arg0 = static_cast<::Windows::Devices::Enumeration::DeviceClass>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = ::Windows::Devices::Enumeration::DeviceInformation::FindAllAsync(arg0);
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
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = ::Windows::Devices::Enumeration::DeviceInformation::FindAllAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray()))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
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
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          
          op = ::Windows::Devices::Enumeration::DeviceInformation::FindAllAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Enumeration::DeviceInformationCollection^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapDeviceInformationCollection(result);
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

    static void GetAqsFilterFromDeviceClass(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Enumeration::DeviceClass arg0 = static_cast<::Windows::Devices::Enumeration::DeviceClass>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = ::Windows::Devices::Enumeration::DeviceInformation::GetAqsFilterFromDeviceClass(arg0);
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
    static void CreateWatcher(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 3
        && info[0]->IsString()
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray())
        && info[2]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
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
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          ::Windows::Devices::Enumeration::DeviceInformationKind arg2 = static_cast<::Windows::Devices::Enumeration::DeviceInformationKind>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          ::Windows::Devices::Enumeration::DeviceWatcher^ result;
          result = ::Windows::Devices::Enumeration::DeviceInformation::CreateWatcher(arg0, arg1, arg2);
          info.GetReturnValue().Set(WrapDeviceWatcher(result));
          return;
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
          ::Windows::Devices::Enumeration::DeviceWatcher^ result;
          result = ::Windows::Devices::Enumeration::DeviceInformation::CreateWatcher();
          info.GetReturnValue().Set(WrapDeviceWatcher(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Enumeration::DeviceClass arg0 = static_cast<::Windows::Devices::Enumeration::DeviceClass>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Devices::Enumeration::DeviceWatcher^ result;
          result = ::Windows::Devices::Enumeration::DeviceInformation::CreateWatcher(arg0);
          info.GetReturnValue().Set(WrapDeviceWatcher(result));
          return;
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
          
          ::Windows::Devices::Enumeration::DeviceWatcher^ result;
          result = ::Windows::Devices::Enumeration::DeviceInformation::CreateWatcher(arg0);
          info.GetReturnValue().Set(WrapDeviceWatcher(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsString()
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray()))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
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
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          
          ::Windows::Devices::Enumeration::DeviceWatcher^ result;
          result = ::Windows::Devices::Enumeration::DeviceInformation::CreateWatcher(arg0, arg1);
          info.GetReturnValue().Set(WrapDeviceWatcher(result));
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

    static void EnclosureLocationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::EnclosureLocation^ result = wrapper->_instance->EnclosureLocation;
        info.GetReturnValue().Set(WrapEnclosureLocation(result));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Id;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsDefaultGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsDefault;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

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
    
    static void PropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Platform::Object^>^ result = wrapper->_instance->Properties;
        info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Platform::Object^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            },
            [](::Platform::Object^ val) -> Local<Value> {
              return CreateOpaqueWrapper(val);
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
    
    static void KindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformationKind result = wrapper->_instance->Kind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PairingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(info.This()))
      {
        return;
      }

      DeviceInformation *wrapper = DeviceInformation::Unwrap<DeviceInformation>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformationPairing^ result = wrapper->_instance->Pairing;
        info.GetReturnValue().Set(WrapDeviceInformationPairing(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Enumeration::DeviceInformation^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceInformation(::Windows::Devices::Enumeration::DeviceInformation^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceInformation^ UnwrapDeviceInformation(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceInformation::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceInformation(::Windows::Devices::Enumeration::DeviceInformation^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceInformation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceInformation^ UnwrapDeviceInformation(Local<Value> value)
  {
     return DeviceInformation::Unwrap<DeviceInformation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceInformation(Local<Object> exports)
  {
    DeviceInformation::Init(exports);
  }

  class DevicePairingResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DevicePairingResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protectionLevelUsed").ToLocalChecked(), ProtectionLevelUsedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DevicePairingResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DevicePairingResult(::Windows::Devices::Enumeration::DevicePairingResult^ instance)
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
      
      ::Windows::Devices::Enumeration::DevicePairingResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DevicePairingResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DevicePairingResult *wrapperInstance = new DevicePairingResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DevicePairingResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DevicePairingResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDevicePairingResult(winRtInstance));
    }


  



    static void ProtectionLevelUsedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingResult^>(info.This()))
      {
        return;
      }

      DevicePairingResult *wrapper = DevicePairingResult::Unwrap<DevicePairingResult>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DevicePairingProtectionLevel result = wrapper->_instance->ProtectionLevelUsed;
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingResult^>(info.This()))
      {
        return;
      }

      DevicePairingResult *wrapper = DevicePairingResult::Unwrap<DevicePairingResult>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DevicePairingResultStatus result = wrapper->_instance->Status;
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
    ::Windows::Devices::Enumeration::DevicePairingResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDevicePairingResult(::Windows::Devices::Enumeration::DevicePairingResult^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DevicePairingResult^ UnwrapDevicePairingResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> DevicePairingResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapDevicePairingResult(::Windows::Devices::Enumeration::DevicePairingResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DevicePairingResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DevicePairingResult^ UnwrapDevicePairingResult(Local<Value> value)
  {
     return DevicePairingResult::Unwrap<DevicePairingResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDevicePairingResult(Local<Object> exports)
  {
    DevicePairingResult::Init(exports);
  }

  class DeviceUnpairingResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceUnpairingResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceUnpairingResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceUnpairingResult(::Windows::Devices::Enumeration::DeviceUnpairingResult^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceUnpairingResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceUnpairingResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceUnpairingResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceUnpairingResult *wrapperInstance = new DeviceUnpairingResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceUnpairingResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceUnpairingResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceUnpairingResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceUnpairingResult(winRtInstance));
    }


  



    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceUnpairingResult^>(info.This()))
      {
        return;
      }

      DeviceUnpairingResult *wrapper = DeviceUnpairingResult::Unwrap<DeviceUnpairingResult>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceUnpairingResultStatus result = wrapper->_instance->Status;
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
    ::Windows::Devices::Enumeration::DeviceUnpairingResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceUnpairingResult(::Windows::Devices::Enumeration::DeviceUnpairingResult^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceUnpairingResult^ UnwrapDeviceUnpairingResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceUnpairingResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceUnpairingResult(::Windows::Devices::Enumeration::DeviceUnpairingResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceUnpairingResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceUnpairingResult^ UnwrapDeviceUnpairingResult(Local<Value> value)
  {
     return DeviceUnpairingResult::Unwrap<DeviceUnpairingResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceUnpairingResult(Local<Object> exports)
  {
    DeviceUnpairingResult::Init(exports);
  }

  class IDevicePairingSettings : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IDevicePairingSettings").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IDevicePairingSettings").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IDevicePairingSettings(::Windows::Devices::Enumeration::IDevicePairingSettings^ instance)
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
      
      ::Windows::Devices::Enumeration::IDevicePairingSettings^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::IDevicePairingSettings^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::IDevicePairingSettings^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IDevicePairingSettings *wrapperInstance = new IDevicePairingSettings(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::IDevicePairingSettings^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::IDevicePairingSettings^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::IDevicePairingSettings^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIDevicePairingSettings(winRtInstance));
    }


  





  private:
    ::Windows::Devices::Enumeration::IDevicePairingSettings^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIDevicePairingSettings(::Windows::Devices::Enumeration::IDevicePairingSettings^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::IDevicePairingSettings^ UnwrapIDevicePairingSettings(Local<Value> value);
  };
  Persistent<FunctionTemplate> IDevicePairingSettings::s_constructorTemplate;

  v8::Local<v8::Value> WrapIDevicePairingSettings(::Windows::Devices::Enumeration::IDevicePairingSettings^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IDevicePairingSettings::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::IDevicePairingSettings^ UnwrapIDevicePairingSettings(Local<Value> value)
  {
     return IDevicePairingSettings::Unwrap<IDevicePairingSettings>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIDevicePairingSettings(Local<Object> exports)
  {
    IDevicePairingSettings::Init(exports);
  }

  class DevicePairingRequestedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DevicePairingRequestedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "accept", Accept);
      Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceInformation").ToLocalChecked(), DeviceInformationGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pairingKind").ToLocalChecked(), PairingKindGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pin").ToLocalChecked(), PinGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DevicePairingRequestedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DevicePairingRequestedEventArgs(::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ instance)
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
      
      ::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DevicePairingRequestedEventArgs *wrapperInstance = new DevicePairingRequestedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDevicePairingRequestedEventArgs(winRtInstance));
    }


  
    static void Accept(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^>(info.This()))
      {
        return;
      }

      DevicePairingRequestedEventArgs *wrapper = DevicePairingRequestedEventArgs::Unwrap<DevicePairingRequestedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Accept();
          return;   
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
          
          wrapper->_instance->Accept(arg0);
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
    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^>(info.This()))
      {
        return;
      }

      DevicePairingRequestedEventArgs *wrapper = DevicePairingRequestedEventArgs::Unwrap<DevicePairingRequestedEventArgs>(info.This());

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



    static void DeviceInformationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^>(info.This()))
      {
        return;
      }

      DevicePairingRequestedEventArgs *wrapper = DevicePairingRequestedEventArgs::Unwrap<DevicePairingRequestedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformation^ result = wrapper->_instance->DeviceInformation;
        info.GetReturnValue().Set(WrapDeviceInformation(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PairingKindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^>(info.This()))
      {
        return;
      }

      DevicePairingRequestedEventArgs *wrapper = DevicePairingRequestedEventArgs::Unwrap<DevicePairingRequestedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DevicePairingKinds result = wrapper->_instance->PairingKind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PinGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^>(info.This()))
      {
        return;
      }

      DevicePairingRequestedEventArgs *wrapper = DevicePairingRequestedEventArgs::Unwrap<DevicePairingRequestedEventArgs>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Pin;
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
    ::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDevicePairingRequestedEventArgs(::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ UnwrapDevicePairingRequestedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> DevicePairingRequestedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapDevicePairingRequestedEventArgs(::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DevicePairingRequestedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ UnwrapDevicePairingRequestedEventArgs(Local<Value> value)
  {
     return DevicePairingRequestedEventArgs::Unwrap<DevicePairingRequestedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDevicePairingRequestedEventArgs(Local<Object> exports)
  {
    DevicePairingRequestedEventArgs::Init(exports);
  }

  class DeviceInformationCustomPairing : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceInformationCustomPairing").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "pairAsync", PairAsync);
      
            
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceInformationCustomPairing").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceInformationCustomPairing(::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationCustomPairing^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceInformationCustomPairing^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceInformationCustomPairing *wrapperInstance = new DeviceInformationCustomPairing(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationCustomPairing^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceInformationCustomPairing^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceInformationCustomPairing(winRtInstance));
    }


    static void PairAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationCustomPairing^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DeviceInformationCustomPairing *wrapper = DeviceInformationCustomPairing::Unwrap<DeviceInformationCustomPairing>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Enumeration::DevicePairingResult^>^ op;
    

      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Enumeration::DevicePairingKinds arg0 = static_cast<::Windows::Devices::Enumeration::DevicePairingKinds>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->PairAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Enumeration::DevicePairingKinds arg0 = static_cast<::Windows::Devices::Enumeration::DevicePairingKinds>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Devices::Enumeration::DevicePairingProtectionLevel arg1 = static_cast<::Windows::Devices::Enumeration::DevicePairingProtectionLevel>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->PairAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::IDevicePairingSettings^>(info[2]))
      {
        try
        {
          ::Windows::Devices::Enumeration::DevicePairingKinds arg0 = static_cast<::Windows::Devices::Enumeration::DevicePairingKinds>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Devices::Enumeration::DevicePairingProtectionLevel arg1 = static_cast<::Windows::Devices::Enumeration::DevicePairingProtectionLevel>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Devices::Enumeration::IDevicePairingSettings^ arg2 = UnwrapIDevicePairingSettings(info[2]);
          
          op = wrapper->_instance->PairAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Enumeration::DevicePairingResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapDevicePairingResult(result);
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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"pairingRequested", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationCustomPairing^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        DeviceInformationCustomPairing *wrapper = DeviceInformationCustomPairing::Unwrap<DeviceInformationCustomPairing>(info.This());
      
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

          registrationToken = wrapper->_instance->PairingRequested::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Enumeration::DeviceInformationCustomPairing^, ::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ arg0, ::Windows::Devices::Enumeration::DevicePairingRequestedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapDeviceInformationCustomPairing(arg0);
                  wrappedArg1 = WrapDevicePairingRequestedEventArgs(arg1);


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

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"pairingRequested", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"pairingRequested", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationCustomPairing^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          DeviceInformationCustomPairing *wrapper = DeviceInformationCustomPairing::Unwrap<DeviceInformationCustomPairing>(info.This());
          wrapper->_instance->PairingRequested::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceInformationCustomPairing(::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ UnwrapDeviceInformationCustomPairing(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceInformationCustomPairing::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceInformationCustomPairing(::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceInformationCustomPairing::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ UnwrapDeviceInformationCustomPairing(Local<Value> value)
  {
     return DeviceInformationCustomPairing::Unwrap<DeviceInformationCustomPairing>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceInformationCustomPairing(Local<Object> exports)
  {
    DeviceInformationCustomPairing::Init(exports);
  }

  class DeviceInformationPairing : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceInformationPairing").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "pairAsync", PairAsync);
      Nan::SetPrototypeMethod(localRef, "unpairAsync", UnpairAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canPair").ToLocalChecked(), CanPairGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isPaired").ToLocalChecked(), IsPairedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("custom").ToLocalChecked(), CustomGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protectionLevel").ToLocalChecked(), ProtectionLevelGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "tryRegisterForAllInboundPairingRequests", TryRegisterForAllInboundPairingRequests);

      Nan::Set(exports, Nan::New<String>("DeviceInformationPairing").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceInformationPairing(::Windows::Devices::Enumeration::DeviceInformationPairing^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceInformationPairing^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationPairing^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceInformationPairing^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceInformationPairing *wrapperInstance = new DeviceInformationPairing(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationPairing^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceInformationPairing^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceInformationPairing^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceInformationPairing(winRtInstance));
    }


    static void PairAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationPairing^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DeviceInformationPairing *wrapper = DeviceInformationPairing::Unwrap<DeviceInformationPairing>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Enumeration::DevicePairingResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->PairAsync();
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
          ::Windows::Devices::Enumeration::DevicePairingProtectionLevel arg0 = static_cast<::Windows::Devices::Enumeration::DevicePairingProtectionLevel>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->PairAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::IDevicePairingSettings^>(info[1]))
      {
        try
        {
          ::Windows::Devices::Enumeration::DevicePairingProtectionLevel arg0 = static_cast<::Windows::Devices::Enumeration::DevicePairingProtectionLevel>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Devices::Enumeration::IDevicePairingSettings^ arg1 = UnwrapIDevicePairingSettings(info[1]);
          
          op = wrapper->_instance->PairAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Enumeration::DevicePairingResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapDevicePairingResult(result);
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
    static void UnpairAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationPairing^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      DeviceInformationPairing *wrapper = DeviceInformationPairing::Unwrap<DeviceInformationPairing>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Enumeration::DeviceUnpairingResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->UnpairAsync();
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Enumeration::DeviceUnpairingResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapDeviceUnpairingResult(result);
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
  


    static void TryRegisterForAllInboundPairingRequests(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Enumeration::DevicePairingKinds arg0 = static_cast<::Windows::Devices::Enumeration::DevicePairingKinds>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          bool result;
          result = ::Windows::Devices::Enumeration::DeviceInformationPairing::TryRegisterForAllInboundPairingRequests(arg0);
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

    static void CanPairGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationPairing^>(info.This()))
      {
        return;
      }

      DeviceInformationPairing *wrapper = DeviceInformationPairing::Unwrap<DeviceInformationPairing>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanPair;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsPairedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationPairing^>(info.This()))
      {
        return;
      }

      DeviceInformationPairing *wrapper = DeviceInformationPairing::Unwrap<DeviceInformationPairing>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsPaired;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CustomGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationPairing^>(info.This()))
      {
        return;
      }

      DeviceInformationPairing *wrapper = DeviceInformationPairing::Unwrap<DeviceInformationPairing>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformationCustomPairing^ result = wrapper->_instance->Custom;
        info.GetReturnValue().Set(WrapDeviceInformationCustomPairing(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProtectionLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformationPairing^>(info.This()))
      {
        return;
      }

      DeviceInformationPairing *wrapper = DeviceInformationPairing::Unwrap<DeviceInformationPairing>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DevicePairingProtectionLevel result = wrapper->_instance->ProtectionLevel;
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
    ::Windows::Devices::Enumeration::DeviceInformationPairing^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceInformationPairing(::Windows::Devices::Enumeration::DeviceInformationPairing^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceInformationPairing^ UnwrapDeviceInformationPairing(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceInformationPairing::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceInformationPairing(::Windows::Devices::Enumeration::DeviceInformationPairing^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceInformationPairing::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceInformationPairing^ UnwrapDeviceInformationPairing(Local<Value> value)
  {
     return DeviceInformationPairing::Unwrap<DeviceInformationPairing>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceInformationPairing(Local<Object> exports)
  {
    DeviceInformationPairing::Init(exports);
  }

  class DeviceAccessChangedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceAccessChangedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceAccessChangedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceAccessChangedEventArgs(::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceAccessChangedEventArgs *wrapperInstance = new DeviceAccessChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceAccessChangedEventArgs(winRtInstance));
    }


  



    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^>(info.This()))
      {
        return;
      }

      DeviceAccessChangedEventArgs *wrapper = DeviceAccessChangedEventArgs::Unwrap<DeviceAccessChangedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceAccessStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^>(info.This()))
      {
        return;
      }

      DeviceAccessChangedEventArgs *wrapper = DeviceAccessChangedEventArgs::Unwrap<DeviceAccessChangedEventArgs>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Id;
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
    ::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceAccessChangedEventArgs(::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ UnwrapDeviceAccessChangedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceAccessChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceAccessChangedEventArgs(::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceAccessChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ UnwrapDeviceAccessChangedEventArgs(Local<Value> value)
  {
     return DeviceAccessChangedEventArgs::Unwrap<DeviceAccessChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceAccessChangedEventArgs(Local<Object> exports)
  {
    DeviceAccessChangedEventArgs::Init(exports);
  }

  class DeviceAccessInformation : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceAccessInformation").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                        
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("currentStatus").ToLocalChecked(), CurrentStatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "createFromId", CreateFromId);
      Nan::SetMethod(constructor, "createFromDeviceClassId", CreateFromDeviceClassId);
      Nan::SetMethod(constructor, "createFromDeviceClass", CreateFromDeviceClass);

      Nan::Set(exports, Nan::New<String>("DeviceAccessInformation").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceAccessInformation(::Windows::Devices::Enumeration::DeviceAccessInformation^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceAccessInformation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceAccessInformation^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceAccessInformation^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceAccessInformation *wrapperInstance = new DeviceAccessInformation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceAccessInformation^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceAccessInformation^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceAccessInformation^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceAccessInformation(winRtInstance));
    }


  


    static void CreateFromId(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Devices::Enumeration::DeviceAccessInformation^ result;
          result = ::Windows::Devices::Enumeration::DeviceAccessInformation::CreateFromId(arg0);
          info.GetReturnValue().Set(WrapDeviceAccessInformation(result));
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
    static void CreateFromDeviceClassId(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          ::Windows::Devices::Enumeration::DeviceAccessInformation^ result;
          result = ::Windows::Devices::Enumeration::DeviceAccessInformation::CreateFromDeviceClassId(arg0);
          info.GetReturnValue().Set(WrapDeviceAccessInformation(result));
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
    static void CreateFromDeviceClass(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Enumeration::DeviceClass arg0 = static_cast<::Windows::Devices::Enumeration::DeviceClass>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Devices::Enumeration::DeviceAccessInformation^ result;
          result = ::Windows::Devices::Enumeration::DeviceAccessInformation::CreateFromDeviceClass(arg0);
          info.GetReturnValue().Set(WrapDeviceAccessInformation(result));
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

    static void CurrentStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceAccessInformation^>(info.This()))
      {
        return;
      }

      DeviceAccessInformation *wrapper = DeviceAccessInformation::Unwrap<DeviceAccessInformation>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceAccessStatus result = wrapper->_instance->CurrentStatus;
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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"accessChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceAccessInformation^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        DeviceAccessInformation *wrapper = DeviceAccessInformation::Unwrap<DeviceAccessInformation>(info.This());
      
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

          registrationToken = wrapper->_instance->AccessChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Enumeration::DeviceAccessInformation^, ::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Enumeration::DeviceAccessInformation^ arg0, ::Windows::Devices::Enumeration::DeviceAccessChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapDeviceAccessInformation(arg0);
                  wrappedArg1 = WrapDeviceAccessChangedEventArgs(arg1);


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

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"accessChanged", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"accessChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceAccessInformation^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          DeviceAccessInformation *wrapper = DeviceAccessInformation::Unwrap<DeviceAccessInformation>(info.This());
          wrapper->_instance->AccessChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Enumeration::DeviceAccessInformation^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceAccessInformation(::Windows::Devices::Enumeration::DeviceAccessInformation^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceAccessInformation^ UnwrapDeviceAccessInformation(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceAccessInformation::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceAccessInformation(::Windows::Devices::Enumeration::DeviceAccessInformation^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceAccessInformation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceAccessInformation^ UnwrapDeviceAccessInformation(Local<Value> value)
  {
     return DeviceAccessInformation::Unwrap<DeviceAccessInformation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceAccessInformation(Local<Object> exports)
  {
    DeviceAccessInformation::Init(exports);
  }

  class DeviceWatcherEvent : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceWatcherEvent").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceInformation").ToLocalChecked(), DeviceInformationGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceInformationUpdate").ToLocalChecked(), DeviceInformationUpdateGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("kind").ToLocalChecked(), KindGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceWatcherEvent").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceWatcherEvent(::Windows::Devices::Enumeration::DeviceWatcherEvent^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceWatcherEvent^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcherEvent^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceWatcherEvent^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceWatcherEvent *wrapperInstance = new DeviceWatcherEvent(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcherEvent^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceWatcherEvent^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceWatcherEvent^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceWatcherEvent(winRtInstance));
    }


  



    static void DeviceInformationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcherEvent^>(info.This()))
      {
        return;
      }

      DeviceWatcherEvent *wrapper = DeviceWatcherEvent::Unwrap<DeviceWatcherEvent>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformation^ result = wrapper->_instance->DeviceInformation;
        info.GetReturnValue().Set(WrapDeviceInformation(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DeviceInformationUpdateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcherEvent^>(info.This()))
      {
        return;
      }

      DeviceWatcherEvent *wrapper = DeviceWatcherEvent::Unwrap<DeviceWatcherEvent>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformationUpdate^ result = wrapper->_instance->DeviceInformationUpdate;
        info.GetReturnValue().Set(WrapDeviceInformationUpdate(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void KindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcherEvent^>(info.This()))
      {
        return;
      }

      DeviceWatcherEvent *wrapper = DeviceWatcherEvent::Unwrap<DeviceWatcherEvent>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceWatcherEventKind result = wrapper->_instance->Kind;
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
    ::Windows::Devices::Enumeration::DeviceWatcherEvent^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceWatcherEvent(::Windows::Devices::Enumeration::DeviceWatcherEvent^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceWatcherEvent^ UnwrapDeviceWatcherEvent(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceWatcherEvent::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceWatcherEvent(::Windows::Devices::Enumeration::DeviceWatcherEvent^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceWatcherEvent::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceWatcherEvent^ UnwrapDeviceWatcherEvent(Local<Value> value)
  {
     return DeviceWatcherEvent::Unwrap<DeviceWatcherEvent>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceWatcherEvent(Local<Object> exports)
  {
    DeviceWatcherEvent::Init(exports);
  }

  class DeviceWatcherTriggerDetails : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DeviceWatcherTriggerDetails").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceWatcherEvents").ToLocalChecked(), DeviceWatcherEventsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DeviceWatcherTriggerDetails").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DeviceWatcherTriggerDetails(::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^ instance)
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
      
      ::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      DeviceWatcherTriggerDetails *wrapperInstance = new DeviceWatcherTriggerDetails(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDeviceWatcherTriggerDetails(winRtInstance));
    }


  



    static void DeviceWatcherEventsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^>(info.This()))
      {
        return;
      }

      DeviceWatcherTriggerDetails *wrapper = DeviceWatcherTriggerDetails::Unwrap<DeviceWatcherTriggerDetails>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Enumeration::DeviceWatcherEvent^>^ result = wrapper->_instance->DeviceWatcherEvents;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Enumeration::DeviceWatcherEvent^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Enumeration::DeviceWatcherEvent^ val) -> Local<Value> {
              return WrapDeviceWatcherEvent(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceWatcherEvent^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Enumeration::DeviceWatcherEvent^ {
              return UnwrapDeviceWatcherEvent(value);
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
    ::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDeviceWatcherTriggerDetails(::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^ wintRtInstance);
    friend ::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^ UnwrapDeviceWatcherTriggerDetails(Local<Value> value);
  };
  Persistent<FunctionTemplate> DeviceWatcherTriggerDetails::s_constructorTemplate;

  v8::Local<v8::Value> WrapDeviceWatcherTriggerDetails(::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DeviceWatcherTriggerDetails::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Enumeration::DeviceWatcherTriggerDetails^ UnwrapDeviceWatcherTriggerDetails(Local<Value> value)
  {
     return DeviceWatcherTriggerDetails::Unwrap<DeviceWatcherTriggerDetails>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDeviceWatcherTriggerDetails(Local<Object> exports)
  {
    DeviceWatcherTriggerDetails::Init(exports);
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
  
  NodeRT::Windows::Devices::Enumeration::InitDevicePickerDisplayStatusOptionsEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceClassEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceWatcherStatusEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitPanelEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceInformationKindEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceWatcherEventKindEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitDevicePairingKindsEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitDevicePairingResultStatusEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceUnpairingResultStatusEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitDevicePairingProtectionLevelEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceAccessStatusEnum(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceConnectionChangeTriggerDetails(target);
  NodeRT::Windows::Devices::Enumeration::InitDevicePickerAppearance(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceSelectedEventArgs(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceDisconnectButtonClickedEventArgs(target);
  NodeRT::Windows::Devices::Enumeration::InitDevicePickerFilter(target);
  NodeRT::Windows::Devices::Enumeration::InitDevicePicker(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceThumbnail(target);
  NodeRT::Windows::Devices::Enumeration::InitEnclosureLocation(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceInformationUpdate(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceInformationCollection(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceWatcher(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceInformation(target);
  NodeRT::Windows::Devices::Enumeration::InitDevicePairingResult(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceUnpairingResult(target);
  NodeRT::Windows::Devices::Enumeration::InitIDevicePairingSettings(target);
  NodeRT::Windows::Devices::Enumeration::InitDevicePairingRequestedEventArgs(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceInformationCustomPairing(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceInformationPairing(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceAccessChangedEventArgs(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceAccessInformation(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceWatcherEvent(target);
  NodeRT::Windows::Devices::Enumeration::InitDeviceWatcherTriggerDetails(target);

  NodeRT::Utils::RegisterNameSpace("Windows.Devices.Enumeration", target);
}


NODE_MODULE(binding, init)