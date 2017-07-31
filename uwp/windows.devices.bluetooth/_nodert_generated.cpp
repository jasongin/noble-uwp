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
#include "../InitializeSecurity.h"

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

namespace NodeRT { namespace Windows { namespace Devices { namespace Bluetooth { 

  v8::Local<v8::Value> WrapBluetoothAdapter(::Windows::Devices::Bluetooth::BluetoothAdapter^ wintRtInstance);
  ::Windows::Devices::Bluetooth::BluetoothAdapter^ UnwrapBluetoothAdapter(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothDeviceId(::Windows::Devices::Bluetooth::BluetoothDeviceId^ wintRtInstance);
  ::Windows::Devices::Bluetooth::BluetoothDeviceId^ UnwrapBluetoothDeviceId(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothUuidHelper(::Windows::Devices::Bluetooth::BluetoothUuidHelper^ wintRtInstance);
  ::Windows::Devices::Bluetooth::BluetoothUuidHelper^ UnwrapBluetoothUuidHelper(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothDevice(::Windows::Devices::Bluetooth::BluetoothDevice^ wintRtInstance);
  ::Windows::Devices::Bluetooth::BluetoothDevice^ UnwrapBluetoothDevice(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothClassOfDevice(::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ wintRtInstance);
  ::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ UnwrapBluetoothClassOfDevice(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAppearanceCategories(::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^ wintRtInstance);
  ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^ UnwrapBluetoothLEAppearanceCategories(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAppearanceSubcategories(::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^ wintRtInstance);
  ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^ UnwrapBluetoothLEAppearanceSubcategories(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEAppearance(::Windows::Devices::Bluetooth::BluetoothLEAppearance^ wintRtInstance);
  ::Windows::Devices::Bluetooth::BluetoothLEAppearance^ UnwrapBluetoothLEAppearance(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothLEDevice(::Windows::Devices::Bluetooth::BluetoothLEDevice^ wintRtInstance);
  ::Windows::Devices::Bluetooth::BluetoothLEDevice^ UnwrapBluetoothLEDevice(Local<Value> value);
  
  v8::Local<v8::Value> WrapBluetoothSignalStrengthFilter(::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ wintRtInstance);
  ::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ UnwrapBluetoothSignalStrengthFilter(Local<Value> value);
  


  static void InitBluetoothCacheModeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothCacheMode").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("cached").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothCacheMode::Cached)));
	Nan::Set(enumObject, Nan::New<String>("uncached").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothCacheMode::Uncached)));
  }


  static void InitBluetoothMajorClassEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothMajorClass").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("miscellaneous").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMajorClass::Miscellaneous)));
	Nan::Set(enumObject, Nan::New<String>("computer").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMajorClass::Computer)));
	Nan::Set(enumObject, Nan::New<String>("phone").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMajorClass::Phone)));
	Nan::Set(enumObject, Nan::New<String>("networkAccessPoint").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMajorClass::NetworkAccessPoint)));
	Nan::Set(enumObject, Nan::New<String>("audioVideo").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMajorClass::AudioVideo)));
	Nan::Set(enumObject, Nan::New<String>("peripheral").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMajorClass::Peripheral)));
	Nan::Set(enumObject, Nan::New<String>("imaging").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMajorClass::Imaging)));
	Nan::Set(enumObject, Nan::New<String>("wearable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMajorClass::Wearable)));
	Nan::Set(enumObject, Nan::New<String>("toy").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMajorClass::Toy)));
	Nan::Set(enumObject, Nan::New<String>("health").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMajorClass::Health)));
  }


  static void InitBluetoothMinorClassEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothMinorClass").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("uncategorized").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::Uncategorized)));
	Nan::Set(enumObject, Nan::New<String>("networkFullyAvailable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::NetworkFullyAvailable)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoWearableHeadset").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoWearableHeadset)));
	Nan::Set(enumObject, Nan::New<String>("phoneCellular").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PhoneCellular)));
	Nan::Set(enumObject, Nan::New<String>("peripheralJoystick").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PeripheralJoystick)));
	Nan::Set(enumObject, Nan::New<String>("healthBloodPressureMonitor").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthBloodPressureMonitor)));
	Nan::Set(enumObject, Nan::New<String>("wearableWristwatch").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::WearableWristwatch)));
	Nan::Set(enumObject, Nan::New<String>("computerDesktop").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ComputerDesktop)));
	Nan::Set(enumObject, Nan::New<String>("toyRobot").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ToyRobot)));
	Nan::Set(enumObject, Nan::New<String>("peripheralGamepad").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PeripheralGamepad)));
	Nan::Set(enumObject, Nan::New<String>("wearablePager").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::WearablePager)));
	Nan::Set(enumObject, Nan::New<String>("computerServer").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ComputerServer)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoHandsFree").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoHandsFree)));
	Nan::Set(enumObject, Nan::New<String>("toyVehicle").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ToyVehicle)));
	Nan::Set(enumObject, Nan::New<String>("healthThermometer").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthThermometer)));
	Nan::Set(enumObject, Nan::New<String>("phoneCordless").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PhoneCordless)));
	Nan::Set(enumObject, Nan::New<String>("phoneSmartPhone").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PhoneSmartPhone)));
	Nan::Set(enumObject, Nan::New<String>("computerLaptop").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ComputerLaptop)));
	Nan::Set(enumObject, Nan::New<String>("wearableJacket").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::WearableJacket)));
	Nan::Set(enumObject, Nan::New<String>("peripheralRemoteControl").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PeripheralRemoteControl)));
	Nan::Set(enumObject, Nan::New<String>("healthWeighingScale").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthWeighingScale)));
	Nan::Set(enumObject, Nan::New<String>("toyDoll").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ToyDoll)));
	Nan::Set(enumObject, Nan::New<String>("computerHandheld").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ComputerHandheld)));
	Nan::Set(enumObject, Nan::New<String>("toyController").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ToyController)));
	Nan::Set(enumObject, Nan::New<String>("phoneWired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PhoneWired)));
	Nan::Set(enumObject, Nan::New<String>("wearableHelmet").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::WearableHelmet)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoMicrophone").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoMicrophone)));
	Nan::Set(enumObject, Nan::New<String>("peripheralSensing").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PeripheralSensing)));
	Nan::Set(enumObject, Nan::New<String>("healthGlucoseMeter").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthGlucoseMeter)));
	Nan::Set(enumObject, Nan::New<String>("wearableGlasses").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::WearableGlasses)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoLoudspeaker").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoLoudspeaker)));
	Nan::Set(enumObject, Nan::New<String>("healthPulseOximeter").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthPulseOximeter)));
	Nan::Set(enumObject, Nan::New<String>("toyGame").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ToyGame)));
	Nan::Set(enumObject, Nan::New<String>("phoneIsdn").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PhoneIsdn)));
	Nan::Set(enumObject, Nan::New<String>("peripheralDigitizerTablet").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PeripheralDigitizerTablet)));
	Nan::Set(enumObject, Nan::New<String>("computerPalmSize").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ComputerPalmSize)));
	Nan::Set(enumObject, Nan::New<String>("peripheralCardReader").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PeripheralCardReader)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoHeadphones").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoHeadphones)));
	Nan::Set(enumObject, Nan::New<String>("computerWearable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ComputerWearable)));
	Nan::Set(enumObject, Nan::New<String>("healthHeartRateMonitor").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthHeartRateMonitor)));
	Nan::Set(enumObject, Nan::New<String>("peripheralDigitalPen").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PeripheralDigitalPen)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoPortableAudio").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoPortableAudio)));
	Nan::Set(enumObject, Nan::New<String>("healthHealthDataDisplay").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthHealthDataDisplay)));
	Nan::Set(enumObject, Nan::New<String>("computerTablet").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::ComputerTablet)));
	Nan::Set(enumObject, Nan::New<String>("peripheralHandheldScanner").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PeripheralHandheldScanner)));
	Nan::Set(enumObject, Nan::New<String>("networkUsed01To17Percent").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::NetworkUsed01To17Percent)));
	Nan::Set(enumObject, Nan::New<String>("healthStepCounter").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthStepCounter)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoCarAudio").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoCarAudio)));
	Nan::Set(enumObject, Nan::New<String>("peripheralHandheldGesture").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::PeripheralHandheldGesture)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoSetTopBox").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoSetTopBox)));
	Nan::Set(enumObject, Nan::New<String>("healthBodyCompositionAnalyzer").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthBodyCompositionAnalyzer)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoHifiAudioDevice").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoHifiAudioDevice)));
	Nan::Set(enumObject, Nan::New<String>("healthPeakFlowMonitor").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthPeakFlowMonitor)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoVcr").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoVcr)));
	Nan::Set(enumObject, Nan::New<String>("healthMedicationMonitor").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthMedicationMonitor)));
	Nan::Set(enumObject, Nan::New<String>("healthKneeProsthesis").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthKneeProsthesis)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoVideoCamera").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoVideoCamera)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoCamcorder").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoCamcorder)));
	Nan::Set(enumObject, Nan::New<String>("healthAnkleProsthesis").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthAnkleProsthesis)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoVideoMonitor").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoVideoMonitor)));
	Nan::Set(enumObject, Nan::New<String>("healthGenericHealthManager").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthGenericHealthManager)));
	Nan::Set(enumObject, Nan::New<String>("healthPersonalMobilityDevice").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::HealthPersonalMobilityDevice)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoVideoDisplayAndLoudspeaker").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoVideoDisplayAndLoudspeaker)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoVideoConferencing").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoVideoConferencing)));
	Nan::Set(enumObject, Nan::New<String>("networkUsed17To33Percent").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::NetworkUsed17To33Percent)));
	Nan::Set(enumObject, Nan::New<String>("audioVideoGamingOrToy").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::AudioVideoGamingOrToy)));
	Nan::Set(enumObject, Nan::New<String>("networkUsed33To50Percent").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::NetworkUsed33To50Percent)));
	Nan::Set(enumObject, Nan::New<String>("networkUsed50To67Percent").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::NetworkUsed50To67Percent)));
	Nan::Set(enumObject, Nan::New<String>("networkUsed67To83Percent").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::NetworkUsed67To83Percent)));
	Nan::Set(enumObject, Nan::New<String>("networkUsed83To99Percent").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::NetworkUsed83To99Percent)));
	Nan::Set(enumObject, Nan::New<String>("networkNoServiceAvailable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothMinorClass::NetworkNoServiceAvailable)));
  }


  static void InitBluetoothServiceCapabilitiesEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothServiceCapabilities").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothServiceCapabilities::None)));
	Nan::Set(enumObject, Nan::New<String>("limitedDiscoverableMode").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothServiceCapabilities::LimitedDiscoverableMode)));
	Nan::Set(enumObject, Nan::New<String>("positioningService").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothServiceCapabilities::PositioningService)));
	Nan::Set(enumObject, Nan::New<String>("networkingService").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothServiceCapabilities::NetworkingService)));
	Nan::Set(enumObject, Nan::New<String>("renderingService").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothServiceCapabilities::RenderingService)));
	Nan::Set(enumObject, Nan::New<String>("capturingService").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothServiceCapabilities::CapturingService)));
	Nan::Set(enumObject, Nan::New<String>("objectTransferService").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothServiceCapabilities::ObjectTransferService)));
	Nan::Set(enumObject, Nan::New<String>("audioService").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothServiceCapabilities::AudioService)));
	Nan::Set(enumObject, Nan::New<String>("telephoneService").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothServiceCapabilities::TelephoneService)));
	Nan::Set(enumObject, Nan::New<String>("informationService").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothServiceCapabilities::InformationService)));
  }


  static void InitBluetoothConnectionStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothConnectionStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("disconnected").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothConnectionStatus::Disconnected)));
	Nan::Set(enumObject, Nan::New<String>("connected").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothConnectionStatus::Connected)));
  }


  static void InitBluetoothErrorEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothError").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("success").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothError::Success)));
	Nan::Set(enumObject, Nan::New<String>("radioNotAvailable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothError::RadioNotAvailable)));
	Nan::Set(enumObject, Nan::New<String>("resourceInUse").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothError::ResourceInUse)));
	Nan::Set(enumObject, Nan::New<String>("deviceNotConnected").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothError::DeviceNotConnected)));
	Nan::Set(enumObject, Nan::New<String>("otherError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothError::OtherError)));
	Nan::Set(enumObject, Nan::New<String>("disabledByPolicy").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothError::DisabledByPolicy)));
	Nan::Set(enumObject, Nan::New<String>("notSupported").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothError::NotSupported)));
	Nan::Set(enumObject, Nan::New<String>("disabledByUser").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothError::DisabledByUser)));
	Nan::Set(enumObject, Nan::New<String>("consentRequired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothError::ConsentRequired)));
	Nan::Set(enumObject, Nan::New<String>("transportNotSupported").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothError::TransportNotSupported)));
  }


  static void InitBluetoothAddressTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BluetoothAddressType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("public").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothAddressType::Public)));
	Nan::Set(enumObject, Nan::New<String>("random").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothAddressType::Random)));
	Nan::Set(enumObject, Nan::New<String>("unspecified").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Bluetooth::BluetoothAddressType::Unspecified)));
  }



  
  class BluetoothAdapter : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothAdapter").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "getRadioAsync", GetRadioAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bluetoothAddress").ToLocalChecked(), BluetoothAddressGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceId").ToLocalChecked(), DeviceIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isAdvertisementOffloadSupported").ToLocalChecked(), IsAdvertisementOffloadSupportedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isCentralRoleSupported").ToLocalChecked(), IsCentralRoleSupportedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isClassicSupported").ToLocalChecked(), IsClassicSupportedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isLowEnergySupported").ToLocalChecked(), IsLowEnergySupportedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isPeripheralRoleSupported").ToLocalChecked(), IsPeripheralRoleSupportedGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "getDeviceSelector", GetDeviceSelector);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FromIdAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("fromIdAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetDefaultAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("getDefaultAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("BluetoothAdapter").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothAdapter(::Windows::Devices::Bluetooth::BluetoothAdapter^ instance)
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
      
      ::Windows::Devices::Bluetooth::BluetoothAdapter^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothAdapter^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::BluetoothAdapter^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothAdapter *wrapperInstance = new BluetoothAdapter(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothAdapter^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::BluetoothAdapter^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::BluetoothAdapter^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothAdapter(winRtInstance));
    }


    static void GetRadioAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothAdapter^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      BluetoothAdapter *wrapper = BluetoothAdapter::Unwrap<BluetoothAdapter>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Radios::Radio^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetRadioAsync();
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Radios::Radio^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Radios", "Radio", result);
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
  

    static void FromIdAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::BluetoothAdapter^>^ op;
      

      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = ::Windows::Devices::Bluetooth::BluetoothAdapter::FromIdAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::BluetoothAdapter^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBluetoothAdapter(result);
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
    static void GetDefaultAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::BluetoothAdapter^>^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::Devices::Bluetooth::BluetoothAdapter::GetDefaultAsync();
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::BluetoothAdapter^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBluetoothAdapter(result);
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

    static void GetDeviceSelector(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothAdapter::GetDeviceSelector();
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

    static void BluetoothAddressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothAdapter^>(info.This()))
      {
        return;
      }

      BluetoothAdapter *wrapper = BluetoothAdapter::Unwrap<BluetoothAdapter>(info.This());

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
    
    static void DeviceIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothAdapter^>(info.This()))
      {
        return;
      }

      BluetoothAdapter *wrapper = BluetoothAdapter::Unwrap<BluetoothAdapter>(info.This());

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
    
    static void IsAdvertisementOffloadSupportedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothAdapter^>(info.This()))
      {
        return;
      }

      BluetoothAdapter *wrapper = BluetoothAdapter::Unwrap<BluetoothAdapter>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsAdvertisementOffloadSupported;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsCentralRoleSupportedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothAdapter^>(info.This()))
      {
        return;
      }

      BluetoothAdapter *wrapper = BluetoothAdapter::Unwrap<BluetoothAdapter>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsCentralRoleSupported;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsClassicSupportedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothAdapter^>(info.This()))
      {
        return;
      }

      BluetoothAdapter *wrapper = BluetoothAdapter::Unwrap<BluetoothAdapter>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsClassicSupported;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsLowEnergySupportedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothAdapter^>(info.This()))
      {
        return;
      }

      BluetoothAdapter *wrapper = BluetoothAdapter::Unwrap<BluetoothAdapter>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsLowEnergySupported;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsPeripheralRoleSupportedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothAdapter^>(info.This()))
      {
        return;
      }

      BluetoothAdapter *wrapper = BluetoothAdapter::Unwrap<BluetoothAdapter>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsPeripheralRoleSupported;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::BluetoothAdapter^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothAdapter(::Windows::Devices::Bluetooth::BluetoothAdapter^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::BluetoothAdapter^ UnwrapBluetoothAdapter(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothAdapter::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothAdapter(::Windows::Devices::Bluetooth::BluetoothAdapter^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothAdapter::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::BluetoothAdapter^ UnwrapBluetoothAdapter(Local<Value> value)
  {
     return BluetoothAdapter::Unwrap<BluetoothAdapter>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothAdapter(Local<Object> exports)
  {
    BluetoothAdapter::Init(exports);
  }

  class BluetoothDeviceId : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothDeviceId").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isClassicDevice").ToLocalChecked(), IsClassicDeviceGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isLowEnergyDevice").ToLocalChecked(), IsLowEnergyDeviceGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothDeviceId").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothDeviceId(::Windows::Devices::Bluetooth::BluetoothDeviceId^ instance)
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
      
      ::Windows::Devices::Bluetooth::BluetoothDeviceId^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::BluetoothDeviceId^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothDeviceId *wrapperInstance = new BluetoothDeviceId(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::BluetoothDeviceId^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::BluetoothDeviceId^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothDeviceId(winRtInstance));
    }


  



    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(info.This()))
      {
        return;
      }

      BluetoothDeviceId *wrapper = BluetoothDeviceId::Unwrap<BluetoothDeviceId>(info.This());

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
    
    static void IsClassicDeviceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(info.This()))
      {
        return;
      }

      BluetoothDeviceId *wrapper = BluetoothDeviceId::Unwrap<BluetoothDeviceId>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsClassicDevice;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsLowEnergyDeviceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDeviceId^>(info.This()))
      {
        return;
      }

      BluetoothDeviceId *wrapper = BluetoothDeviceId::Unwrap<BluetoothDeviceId>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsLowEnergyDevice;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::BluetoothDeviceId^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothDeviceId(::Windows::Devices::Bluetooth::BluetoothDeviceId^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::BluetoothDeviceId^ UnwrapBluetoothDeviceId(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothDeviceId::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothDeviceId(::Windows::Devices::Bluetooth::BluetoothDeviceId^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothDeviceId::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::BluetoothDeviceId^ UnwrapBluetoothDeviceId(Local<Value> value)
  {
     return BluetoothDeviceId::Unwrap<BluetoothDeviceId>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothDeviceId(Local<Object> exports)
  {
    BluetoothDeviceId::Init(exports);
  }

  class BluetoothUuidHelper : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothUuidHelper").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "fromShortId", FromShortId);
      Nan::SetMethod(constructor, "tryGetShortId", TryGetShortId);

      Nan::Set(exports, Nan::New<String>("BluetoothUuidHelper").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothUuidHelper(::Windows::Devices::Bluetooth::BluetoothUuidHelper^ instance)
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
      
      ::Windows::Devices::Bluetooth::BluetoothUuidHelper^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothUuidHelper^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::BluetoothUuidHelper^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothUuidHelper *wrapperInstance = new BluetoothUuidHelper(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothUuidHelper^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::BluetoothUuidHelper^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::BluetoothUuidHelper^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothUuidHelper(winRtInstance));
    }


  


    static void FromShortId(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Platform::Guid result;
          result = ::Windows::Devices::Bluetooth::BluetoothUuidHelper::FromShortId(arg0);
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
    static void TryGetShortId(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          ::Platform::IBox<unsigned int>^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothUuidHelper::TryGetShortId(arg0);
          info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
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
    ::Windows::Devices::Bluetooth::BluetoothUuidHelper^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothUuidHelper(::Windows::Devices::Bluetooth::BluetoothUuidHelper^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::BluetoothUuidHelper^ UnwrapBluetoothUuidHelper(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothUuidHelper::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothUuidHelper(::Windows::Devices::Bluetooth::BluetoothUuidHelper^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothUuidHelper::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::BluetoothUuidHelper^ UnwrapBluetoothUuidHelper(Local<Value> value)
  {
     return BluetoothUuidHelper::Unwrap<BluetoothUuidHelper>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothUuidHelper(Local<Object> exports)
  {
    BluetoothUuidHelper::Init(exports);
  }

  class BluetoothDevice : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothDevice").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "requestAccessAsync", RequestAccessAsync);
      Nan::SetPrototypeMethod(localRef, "getRfcommServicesAsync", GetRfcommServicesAsync);
      Nan::SetPrototypeMethod(localRef, "getRfcommServicesForIdAsync", GetRfcommServicesForIdAsync);
      
            
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bluetoothAddress").ToLocalChecked(), BluetoothAddressGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("classOfDevice").ToLocalChecked(), ClassOfDeviceGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("connectionStatus").ToLocalChecked(), ConnectionStatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceId").ToLocalChecked(), DeviceIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hostName").ToLocalChecked(), HostNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("rfcommServices").ToLocalChecked(), RfcommServicesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("sdpRecords").ToLocalChecked(), SdpRecordsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceInformation").ToLocalChecked(), DeviceInformationGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceAccessInformation").ToLocalChecked(), DeviceAccessInformationGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "getDeviceSelectorFromPairingState", GetDeviceSelectorFromPairingState);
      Nan::SetMethod(constructor, "getDeviceSelectorFromConnectionStatus", GetDeviceSelectorFromConnectionStatus);
      Nan::SetMethod(constructor, "getDeviceSelectorFromDeviceName", GetDeviceSelectorFromDeviceName);
      Nan::SetMethod(constructor, "getDeviceSelectorFromBluetoothAddress", GetDeviceSelectorFromBluetoothAddress);
      Nan::SetMethod(constructor, "getDeviceSelectorFromClassOfDevice", GetDeviceSelectorFromClassOfDevice);
      Nan::SetMethod(constructor, "getDeviceSelector", GetDeviceSelector);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FromIdAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("fromIdAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FromHostNameAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("fromHostNameAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FromBluetoothAddressAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("fromBluetoothAddressAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("BluetoothDevice").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothDevice(::Windows::Devices::Bluetooth::BluetoothDevice^ instance)
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
      
      ::Windows::Devices::Bluetooth::BluetoothDevice^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::BluetoothDevice^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothDevice *wrapperInstance = new BluetoothDevice(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::BluetoothDevice^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::BluetoothDevice^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothDevice(winRtInstance));
    }


    static void RequestAccessAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

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
    static void GetRfcommServicesAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::Rfcomm::RfcommDeviceServicesResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetRfcommServicesAsync();
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
          
          op = wrapper->_instance->GetRfcommServicesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::Rfcomm::RfcommDeviceServicesResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Bluetooth.Rfcomm", "RfcommDeviceServicesResult", result);
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
    static void GetRfcommServicesForIdAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::Rfcomm::RfcommDeviceServicesResult^>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Rfcomm::RfcommServiceId^>(info[0]))
      {
        try
        {
          ::Windows::Devices::Bluetooth::Rfcomm::RfcommServiceId^ arg0 = dynamic_cast<::Windows::Devices::Bluetooth::Rfcomm::RfcommServiceId^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->GetRfcommServicesForIdAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Rfcomm::RfcommServiceId^>(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::Rfcomm::RfcommServiceId^ arg0 = dynamic_cast<::Windows::Devices::Bluetooth::Rfcomm::RfcommServiceId^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Devices::Bluetooth::BluetoothCacheMode arg1 = static_cast<::Windows::Devices::Bluetooth::BluetoothCacheMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetRfcommServicesForIdAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::Rfcomm::RfcommDeviceServicesResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Bluetooth.Rfcomm", "RfcommDeviceServicesResult", result);
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
	    return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

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


    static void FromIdAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::BluetoothDevice^>^ op;
      

      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = ::Windows::Devices::Bluetooth::BluetoothDevice::FromIdAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::BluetoothDevice^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBluetoothDevice(result);
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
    static void FromHostNameAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::BluetoothDevice^>^ op;
      

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::HostName^>(info[0]))
      {
        try
        {
          ::Windows::Networking::HostName^ arg0 = dynamic_cast<::Windows::Networking::HostName^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = ::Windows::Devices::Bluetooth::BluetoothDevice::FromHostNameAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::BluetoothDevice^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBluetoothDevice(result);
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
    static void FromBluetoothAddressAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::BluetoothDevice^>^ op;
      

      if (info.Length() == 2
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          op = ::Windows::Devices::Bluetooth::BluetoothDevice::FromBluetoothAddressAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::BluetoothDevice^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBluetoothDevice(result);
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

    static void GetDeviceSelectorFromPairingState(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothDevice::GetDeviceSelectorFromPairingState(arg0);
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
    static void GetDeviceSelectorFromConnectionStatus(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothConnectionStatus arg0 = static_cast<::Windows::Devices::Bluetooth::BluetoothConnectionStatus>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothDevice::GetDeviceSelectorFromConnectionStatus(arg0);
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
    static void GetDeviceSelectorFromDeviceName(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothDevice::GetDeviceSelectorFromDeviceName(arg0);
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
    static void GetDeviceSelectorFromBluetoothAddress(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothDevice::GetDeviceSelectorFromBluetoothAddress(arg0);
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
    static void GetDeviceSelectorFromClassOfDevice(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothClassOfDevice^>(info[0]))
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ arg0 = UnwrapBluetoothClassOfDevice(info[0]);
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothDevice::GetDeviceSelectorFromClassOfDevice(arg0);
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
    static void GetDeviceSelector(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothDevice::GetDeviceSelector();
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

    static void BluetoothAddressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

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
    
    static void ClassOfDeviceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ result = wrapper->_instance->ClassOfDevice;
        info.GetReturnValue().Set(WrapBluetoothClassOfDevice(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ConnectionStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothConnectionStatus result = wrapper->_instance->ConnectionStatus;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

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
    
    static void HostNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

      try 
      {
        ::Windows::Networking::HostName^ result = wrapper->_instance->HostName;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Networking", "HostName", result));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

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
    
    static void RfcommServicesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::Rfcomm::RfcommDeviceService^>^ result = wrapper->_instance->RfcommServices;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::Rfcomm::RfcommDeviceService^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::Rfcomm::RfcommDeviceService^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Bluetooth.Rfcomm", "RfcommDeviceService", val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::Rfcomm::RfcommDeviceService^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::Rfcomm::RfcommDeviceService^ {
              return dynamic_cast<::Windows::Devices::Bluetooth::Rfcomm::RfcommDeviceService^>(NodeRT::Utils::GetObjectInstance(value));
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
    
    static void SdpRecordsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Storage::Streams::IBuffer^>^ result = wrapper->_instance->SdpRecords;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Storage::Streams::IBuffer^>::CreateVectorViewWrapper(result, 
            [](::Windows::Storage::Streams::IBuffer^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(value);
            },
            [](Local<Value> value) -> ::Windows::Storage::Streams::IBuffer^ {
              return dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(value));
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
    
    static void DeviceInformationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformation^ result = wrapper->_instance->DeviceInformation;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Enumeration", "DeviceInformation", result));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
      {
        return;
      }

      BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());

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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"connectionStatusChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());
      
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

          registrationToken = wrapper->_instance->ConnectionStatusChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::BluetoothDevice^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::BluetoothDevice^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapBluetoothDevice(arg0);
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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"nameChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());
      
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

          registrationToken = wrapper->_instance->NameChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::BluetoothDevice^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::BluetoothDevice^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapBluetoothDevice(arg0);
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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"sdpRecordsChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());
      
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

          registrationToken = wrapper->_instance->SdpRecordsChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::BluetoothDevice^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::BluetoothDevice^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapBluetoothDevice(arg0);
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

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"connectionStatusChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"nameChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"sdpRecordsChanged", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"connectionStatusChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());
          wrapper->_instance->ConnectionStatusChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"nameChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());
          wrapper->_instance->NameChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"sdpRecordsChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothDevice^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          BluetoothDevice *wrapper = BluetoothDevice::Unwrap<BluetoothDevice>(info.This());
          wrapper->_instance->SdpRecordsChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::BluetoothDevice^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothDevice(::Windows::Devices::Bluetooth::BluetoothDevice^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::BluetoothDevice^ UnwrapBluetoothDevice(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothDevice::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothDevice(::Windows::Devices::Bluetooth::BluetoothDevice^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothDevice::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::BluetoothDevice^ UnwrapBluetoothDevice(Local<Value> value)
  {
     return BluetoothDevice::Unwrap<BluetoothDevice>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothDevice(Local<Object> exports)
  {
    BluetoothDevice::Init(exports);
  }

  class BluetoothClassOfDevice : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothClassOfDevice").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("majorClass").ToLocalChecked(), MajorClassGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("minorClass").ToLocalChecked(), MinorClassGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("rawValue").ToLocalChecked(), RawValueGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("serviceCapabilities").ToLocalChecked(), ServiceCapabilitiesGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "fromRawValue", FromRawValue);
      Nan::SetMethod(constructor, "fromParts", FromParts);

      Nan::Set(exports, Nan::New<String>("BluetoothClassOfDevice").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothClassOfDevice(::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ instance)
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
      
      ::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothClassOfDevice^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::BluetoothClassOfDevice^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothClassOfDevice *wrapperInstance = new BluetoothClassOfDevice(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothClassOfDevice^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::BluetoothClassOfDevice^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothClassOfDevice(winRtInstance));
    }


  


    static void FromRawValue(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothClassOfDevice::FromRawValue(arg0);
          info.GetReturnValue().Set(WrapBluetoothClassOfDevice(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void FromParts(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothMajorClass arg0 = static_cast<::Windows::Devices::Bluetooth::BluetoothMajorClass>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Devices::Bluetooth::BluetoothMinorClass arg1 = static_cast<::Windows::Devices::Bluetooth::BluetoothMinorClass>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Devices::Bluetooth::BluetoothServiceCapabilities arg2 = static_cast<::Windows::Devices::Bluetooth::BluetoothServiceCapabilities>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          ::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothClassOfDevice::FromParts(arg0, arg1, arg2);
          info.GetReturnValue().Set(WrapBluetoothClassOfDevice(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void MajorClassGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothClassOfDevice^>(info.This()))
      {
        return;
      }

      BluetoothClassOfDevice *wrapper = BluetoothClassOfDevice::Unwrap<BluetoothClassOfDevice>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothMajorClass result = wrapper->_instance->MajorClass;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MinorClassGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothClassOfDevice^>(info.This()))
      {
        return;
      }

      BluetoothClassOfDevice *wrapper = BluetoothClassOfDevice::Unwrap<BluetoothClassOfDevice>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothMinorClass result = wrapper->_instance->MinorClass;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RawValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothClassOfDevice^>(info.This()))
      {
        return;
      }

      BluetoothClassOfDevice *wrapper = BluetoothClassOfDevice::Unwrap<BluetoothClassOfDevice>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->RawValue;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceCapabilitiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothClassOfDevice^>(info.This()))
      {
        return;
      }

      BluetoothClassOfDevice *wrapper = BluetoothClassOfDevice::Unwrap<BluetoothClassOfDevice>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothServiceCapabilities result = wrapper->_instance->ServiceCapabilities;
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
    ::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothClassOfDevice(::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ UnwrapBluetoothClassOfDevice(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothClassOfDevice::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothClassOfDevice(::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothClassOfDevice::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::BluetoothClassOfDevice^ UnwrapBluetoothClassOfDevice(Local<Value> value)
  {
     return BluetoothClassOfDevice::Unwrap<BluetoothClassOfDevice>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothClassOfDevice(Local<Object> exports)
  {
    BluetoothClassOfDevice::Init(exports);
  }

  class BluetoothLEAppearanceCategories : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAppearanceCategories").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("barcodeScanner").ToLocalChecked(), BarcodeScannerGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bloodPressure").ToLocalChecked(), BloodPressureGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("clock").ToLocalChecked(), ClockGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("computer").ToLocalChecked(), ComputerGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cycling").ToLocalChecked(), CyclingGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("display").ToLocalChecked(), DisplayGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("eyeGlasses").ToLocalChecked(), EyeGlassesGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("glucoseMeter").ToLocalChecked(), GlucoseMeterGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("heartRate").ToLocalChecked(), HeartRateGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("humanInterfaceDevice").ToLocalChecked(), HumanInterfaceDeviceGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("keyring").ToLocalChecked(), KeyringGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("mediaPlayer").ToLocalChecked(), MediaPlayerGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("outdoorSportActivity").ToLocalChecked(), OutdoorSportActivityGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("phone").ToLocalChecked(), PhoneGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("pulseOximeter").ToLocalChecked(), PulseOximeterGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("remoteControl").ToLocalChecked(), RemoteControlGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("runningWalking").ToLocalChecked(), RunningWalkingGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("tag").ToLocalChecked(), TagGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("thermometer").ToLocalChecked(), ThermometerGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("uncategorized").ToLocalChecked(), UncategorizedGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("watch").ToLocalChecked(), WatchGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("weightScale").ToLocalChecked(), WeightScaleGetter);

      Nan::Set(exports, Nan::New<String>("BluetoothLEAppearanceCategories").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAppearanceCategories(::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^ instance)
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
      
      ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothLEAppearanceCategories *wrapperInstance = new BluetoothLEAppearanceCategories(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAppearanceCategories(winRtInstance));
    }


  




    static void BarcodeScannerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::BarcodeScanner;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
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
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::BloodPressure;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ClockGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::Clock;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ComputerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::Computer;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::Cycling;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DisplayGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::Display;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void EyeGlassesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::EyeGlasses;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GlucoseMeterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::GlucoseMeter;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
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
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::HeartRate;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
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
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::HumanInterfaceDevice;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void KeyringGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::Keyring;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MediaPlayerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::MediaPlayer;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void OutdoorSportActivityGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::OutdoorSportActivity;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PhoneGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::Phone;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PulseOximeterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::PulseOximeter;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RemoteControlGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::RemoteControl;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RunningWalkingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::RunningWalking;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TagGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::Tag;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ThermometerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::Thermometer;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UncategorizedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::Uncategorized;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WatchGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::Watch;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WeightScaleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories::WeightScale;
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
    ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAppearanceCategories(::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^ UnwrapBluetoothLEAppearanceCategories(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAppearanceCategories::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAppearanceCategories(::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAppearanceCategories::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::BluetoothLEAppearanceCategories^ UnwrapBluetoothLEAppearanceCategories(Local<Value> value)
  {
     return BluetoothLEAppearanceCategories::Unwrap<BluetoothLEAppearanceCategories>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAppearanceCategories(Local<Object> exports)
  {
    BluetoothLEAppearanceCategories::Init(exports);
  }

  class BluetoothLEAppearanceSubcategories : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAppearanceSubcategories").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("barcodeScanner").ToLocalChecked(), BarcodeScannerGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bloodPressureArm").ToLocalChecked(), BloodPressureArmGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bloodPressureWrist").ToLocalChecked(), BloodPressureWristGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cardReader").ToLocalChecked(), CardReaderGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cyclingCadenceSensor").ToLocalChecked(), CyclingCadenceSensorGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cyclingComputer").ToLocalChecked(), CyclingComputerGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cyclingPowerSensor").ToLocalChecked(), CyclingPowerSensorGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cyclingSpeedCadenceSensor").ToLocalChecked(), CyclingSpeedCadenceSensorGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("cyclingSpeedSensor").ToLocalChecked(), CyclingSpeedSensorGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("digitalPen").ToLocalChecked(), DigitalPenGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("digitizerTablet").ToLocalChecked(), DigitizerTabletGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("gamepad").ToLocalChecked(), GamepadGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("generic").ToLocalChecked(), GenericGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("heartRateBelt").ToLocalChecked(), HeartRateBeltGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("joystick").ToLocalChecked(), JoystickGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("keyboard").ToLocalChecked(), KeyboardGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("locationDisplay").ToLocalChecked(), LocationDisplayGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("locationNavigationDisplay").ToLocalChecked(), LocationNavigationDisplayGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("locationNavigationPod").ToLocalChecked(), LocationNavigationPodGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("locationPod").ToLocalChecked(), LocationPodGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("mouse").ToLocalChecked(), MouseGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("oximeterFingertip").ToLocalChecked(), OximeterFingertipGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("oximeterWristWorn").ToLocalChecked(), OximeterWristWornGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("runningWalkingInShoe").ToLocalChecked(), RunningWalkingInShoeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("runningWalkingOnHip").ToLocalChecked(), RunningWalkingOnHipGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("runningWalkingOnShoe").ToLocalChecked(), RunningWalkingOnShoeGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("sportsWatch").ToLocalChecked(), SportsWatchGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("thermometerEar").ToLocalChecked(), ThermometerEarGetter);

      Nan::Set(exports, Nan::New<String>("BluetoothLEAppearanceSubcategories").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAppearanceSubcategories(::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^ instance)
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
      
      ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothLEAppearanceSubcategories *wrapperInstance = new BluetoothLEAppearanceSubcategories(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAppearanceSubcategories(winRtInstance));
    }


  




    static void BarcodeScannerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::BarcodeScanner;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BloodPressureArmGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::BloodPressureArm;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BloodPressureWristGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::BloodPressureWrist;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CardReaderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::CardReader;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingCadenceSensorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::CyclingCadenceSensor;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingComputerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::CyclingComputer;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingPowerSensorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::CyclingPowerSensor;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingSpeedCadenceSensorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::CyclingSpeedCadenceSensor;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CyclingSpeedSensorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::CyclingSpeedSensor;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DigitalPenGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::DigitalPen;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DigitizerTabletGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::DigitizerTablet;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GamepadGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::Gamepad;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GenericGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::Generic;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HeartRateBeltGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::HeartRateBelt;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void JoystickGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::Joystick;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void KeyboardGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::Keyboard;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LocationDisplayGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::LocationDisplay;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LocationNavigationDisplayGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::LocationNavigationDisplay;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LocationNavigationPodGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::LocationNavigationPod;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LocationPodGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::LocationPod;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MouseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::Mouse;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void OximeterFingertipGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::OximeterFingertip;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void OximeterWristWornGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::OximeterWristWorn;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RunningWalkingInShoeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::RunningWalkingInShoe;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RunningWalkingOnHipGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::RunningWalkingOnHip;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RunningWalkingOnShoeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::RunningWalkingOnShoe;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SportsWatchGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::SportsWatch;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ThermometerEarGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        unsigned short result = ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories::ThermometerEar;
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
    ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAppearanceSubcategories(::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^ UnwrapBluetoothLEAppearanceSubcategories(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAppearanceSubcategories::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAppearanceSubcategories(::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAppearanceSubcategories::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::BluetoothLEAppearanceSubcategories^ UnwrapBluetoothLEAppearanceSubcategories(Local<Value> value)
  {
     return BluetoothLEAppearanceSubcategories::Unwrap<BluetoothLEAppearanceSubcategories>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAppearanceSubcategories(Local<Object> exports)
  {
    BluetoothLEAppearanceSubcategories::Init(exports);
  }

  class BluetoothLEAppearance : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEAppearance").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("category").ToLocalChecked(), CategoryGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("rawValue").ToLocalChecked(), RawValueGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("subCategory").ToLocalChecked(), SubCategoryGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "fromRawValue", FromRawValue);
      Nan::SetMethod(constructor, "fromParts", FromParts);

      Nan::Set(exports, Nan::New<String>("BluetoothLEAppearance").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEAppearance(::Windows::Devices::Bluetooth::BluetoothLEAppearance^ instance)
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
      
      ::Windows::Devices::Bluetooth::BluetoothLEAppearance^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEAppearance^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::BluetoothLEAppearance^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothLEAppearance *wrapperInstance = new BluetoothLEAppearance(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEAppearance^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::BluetoothLEAppearance^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::BluetoothLEAppearance^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEAppearance(winRtInstance));
    }


  


    static void FromRawValue(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Devices::Bluetooth::BluetoothLEAppearance^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothLEAppearance::FromRawValue(arg0);
          info.GetReturnValue().Set(WrapBluetoothLEAppearance(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void FromParts(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 2
        && info[0]->IsInt32()
        && info[1]->IsInt32())
      {
        try
        {
          unsigned short arg0 = static_cast<unsigned short>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned short arg1 = static_cast<unsigned short>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          ::Windows::Devices::Bluetooth::BluetoothLEAppearance^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothLEAppearance::FromParts(arg0, arg1);
          info.GetReturnValue().Set(WrapBluetoothLEAppearance(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void CategoryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEAppearance^>(info.This()))
      {
        return;
      }

      BluetoothLEAppearance *wrapper = BluetoothLEAppearance::Unwrap<BluetoothLEAppearance>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->Category;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RawValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEAppearance^>(info.This()))
      {
        return;
      }

      BluetoothLEAppearance *wrapper = BluetoothLEAppearance::Unwrap<BluetoothLEAppearance>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->RawValue;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SubCategoryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEAppearance^>(info.This()))
      {
        return;
      }

      BluetoothLEAppearance *wrapper = BluetoothLEAppearance::Unwrap<BluetoothLEAppearance>(info.This());

      try 
      {
        unsigned short result = wrapper->_instance->SubCategory;
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
    ::Windows::Devices::Bluetooth::BluetoothLEAppearance^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEAppearance(::Windows::Devices::Bluetooth::BluetoothLEAppearance^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::BluetoothLEAppearance^ UnwrapBluetoothLEAppearance(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEAppearance::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEAppearance(::Windows::Devices::Bluetooth::BluetoothLEAppearance^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEAppearance::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::BluetoothLEAppearance^ UnwrapBluetoothLEAppearance(Local<Value> value)
  {
     return BluetoothLEAppearance::Unwrap<BluetoothLEAppearance>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEAppearance(Local<Object> exports)
  {
    BluetoothLEAppearance::Init(exports);
  }

  class BluetoothLEDevice : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothLEDevice").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "getGattService", GetGattService);
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
            
      Nan::SetPrototypeMethod(localRef, "requestAccessAsync", RequestAccessAsync);
      Nan::SetPrototypeMethod(localRef, "getGattServicesAsync", GetGattServicesAsync);
      Nan::SetPrototypeMethod(localRef, "getGattServicesForUuidAsync", GetGattServicesForUuidAsync);
      
            
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bluetoothAddress").ToLocalChecked(), BluetoothAddressGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("connectionStatus").ToLocalChecked(), ConnectionStatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceId").ToLocalChecked(), DeviceIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("gattServices").ToLocalChecked(), GattServicesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("appearance").ToLocalChecked(), AppearanceGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bluetoothAddressType").ToLocalChecked(), BluetoothAddressTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceInformation").ToLocalChecked(), DeviceInformationGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deviceAccessInformation").ToLocalChecked(), DeviceAccessInformationGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "getDeviceSelectorFromPairingState", GetDeviceSelectorFromPairingState);
      Nan::SetMethod(constructor, "getDeviceSelectorFromConnectionStatus", GetDeviceSelectorFromConnectionStatus);
      Nan::SetMethod(constructor, "getDeviceSelectorFromDeviceName", GetDeviceSelectorFromDeviceName);
      Nan::SetMethod(constructor, "getDeviceSelectorFromBluetoothAddress", GetDeviceSelectorFromBluetoothAddress);
      Nan::SetMethod(constructor, "getDeviceSelectorFromAppearance", GetDeviceSelectorFromAppearance);
      Nan::SetMethod(constructor, "getDeviceSelector", GetDeviceSelector);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FromBluetoothAddressAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("fromBluetoothAddressAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FromIdAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("fromIdAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("BluetoothLEDevice").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothLEDevice(::Windows::Devices::Bluetooth::BluetoothLEDevice^ instance)
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
      
      ::Windows::Devices::Bluetooth::BluetoothLEDevice^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::BluetoothLEDevice^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BluetoothLEDevice *wrapperInstance = new BluetoothLEDevice(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::BluetoothLEDevice^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::BluetoothLEDevice^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothLEDevice(winRtInstance));
    }


    static void RequestAccessAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

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
    static void GetGattServicesAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetGattServicesAsync();
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
          
          op = wrapper->_instance->GetGattServicesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
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
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Bluetooth.GenericAttributeProfile", "GattDeviceServicesResult", result);
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
    static void GetGattServicesForUuidAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult^>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          op = wrapper->_instance->GetGattServicesForUuidAsync(arg0);
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
          
          op = wrapper->_instance->GetGattServicesForUuidAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
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
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Bluetooth.GenericAttributeProfile", "GattDeviceServicesResult", result);
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
  
    static void GetGattService(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsGuid(info[0]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          
          ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ result;
          result = wrapper->_instance->GetGattService(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Bluetooth.GenericAttributeProfile", "GattDeviceService", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
	    return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

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


    static void FromBluetoothAddressAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::BluetoothLEDevice^>^ op;
      

      if (info.Length() == 3
        && info[0]->IsNumber()
        && info[1]->IsInt32())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          ::Windows::Devices::Bluetooth::BluetoothAddressType arg1 = static_cast<::Windows::Devices::Bluetooth::BluetoothAddressType>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = ::Windows::Devices::Bluetooth::BluetoothLEDevice::FromBluetoothAddressAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          op = ::Windows::Devices::Bluetooth::BluetoothLEDevice::FromBluetoothAddressAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::BluetoothLEDevice^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBluetoothLEDevice(result);
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
    static void FromIdAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Bluetooth::BluetoothLEDevice^>^ op;
      

      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = ::Windows::Devices::Bluetooth::BluetoothLEDevice::FromIdAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
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

      opTask.then( [asyncToken] (task<::Windows::Devices::Bluetooth::BluetoothLEDevice^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBluetoothLEDevice(result);
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

    static void GetDeviceSelectorFromPairingState(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothLEDevice::GetDeviceSelectorFromPairingState(arg0);
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
    static void GetDeviceSelectorFromConnectionStatus(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothConnectionStatus arg0 = static_cast<::Windows::Devices::Bluetooth::BluetoothConnectionStatus>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothLEDevice::GetDeviceSelectorFromConnectionStatus(arg0);
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
    static void GetDeviceSelectorFromDeviceName(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothLEDevice::GetDeviceSelectorFromDeviceName(arg0);
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
    static void GetDeviceSelectorFromBluetoothAddress(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothLEDevice::GetDeviceSelectorFromBluetoothAddress(arg0);
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
        && info[0]->IsNumber()
        && info[1]->IsInt32())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          ::Windows::Devices::Bluetooth::BluetoothAddressType arg1 = static_cast<::Windows::Devices::Bluetooth::BluetoothAddressType>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothLEDevice::GetDeviceSelectorFromBluetoothAddress(arg0, arg1);
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
    static void GetDeviceSelectorFromAppearance(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEAppearance^>(info[0]))
      {
        try
        {
          ::Windows::Devices::Bluetooth::BluetoothLEAppearance^ arg0 = UnwrapBluetoothLEAppearance(info[0]);
          
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothLEDevice::GetDeviceSelectorFromAppearance(arg0);
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
    static void GetDeviceSelector(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = ::Windows::Devices::Bluetooth::BluetoothLEDevice::GetDeviceSelector();
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

    static void BluetoothAddressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

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
    
    static void ConnectionStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothConnectionStatus result = wrapper->_instance->ConnectionStatus;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

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
    
    static void GattServicesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>^ result = wrapper->_instance->GattServices;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Bluetooth.GenericAttributeProfile", "GattDeviceService", val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^ {
              return dynamic_cast<::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService^>(NodeRT::Utils::GetObjectInstance(value));
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
    
    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

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
    
    static void AppearanceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothLEAppearance^ result = wrapper->_instance->Appearance;
        info.GetReturnValue().Set(WrapBluetoothLEAppearance(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BluetoothAddressTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

      try 
      {
        ::Windows::Devices::Bluetooth::BluetoothAddressType result = wrapper->_instance->BluetoothAddressType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

      try 
      {
        ::Windows::Devices::Enumeration::DeviceInformation^ result = wrapper->_instance->DeviceInformation;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Enumeration", "DeviceInformation", result));
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
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
      {
        return;
      }

      BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());

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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"connectionStatusChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());
      
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

          registrationToken = wrapper->_instance->ConnectionStatusChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::BluetoothLEDevice^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::BluetoothLEDevice^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapBluetoothLEDevice(arg0);
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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"gattServicesChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());
      
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

          registrationToken = wrapper->_instance->GattServicesChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::BluetoothLEDevice^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::BluetoothLEDevice^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapBluetoothLEDevice(arg0);
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
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"nameChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());
      
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

          registrationToken = wrapper->_instance->NameChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Bluetooth::BluetoothLEDevice^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::Bluetooth::BluetoothLEDevice^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapBluetoothLEDevice(arg0);
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

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"connectionStatusChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"gattServicesChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"nameChanged", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"connectionStatusChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());
          wrapper->_instance->ConnectionStatusChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"gattServicesChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());
          wrapper->_instance->GattServicesChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"nameChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothLEDevice^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          BluetoothLEDevice *wrapper = BluetoothLEDevice::Unwrap<BluetoothLEDevice>(info.This());
          wrapper->_instance->NameChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Bluetooth::BluetoothLEDevice^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothLEDevice(::Windows::Devices::Bluetooth::BluetoothLEDevice^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::BluetoothLEDevice^ UnwrapBluetoothLEDevice(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothLEDevice::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothLEDevice(::Windows::Devices::Bluetooth::BluetoothLEDevice^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothLEDevice::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::BluetoothLEDevice^ UnwrapBluetoothLEDevice(Local<Value> value)
  {
     return BluetoothLEDevice::Unwrap<BluetoothLEDevice>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothLEDevice(Local<Object> exports)
  {
    BluetoothLEDevice::Init(exports);
  }

  class BluetoothSignalStrengthFilter : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BluetoothSignalStrengthFilter").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("samplingInterval").ToLocalChecked(), SamplingIntervalGetter, SamplingIntervalSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("outOfRangeTimeout").ToLocalChecked(), OutOfRangeTimeoutGetter, OutOfRangeTimeoutSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("outOfRangeThresholdInDBm").ToLocalChecked(), OutOfRangeThresholdInDBmGetter, OutOfRangeThresholdInDBmSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("inRangeThresholdInDBm").ToLocalChecked(), InRangeThresholdInDBmGetter, InRangeThresholdInDBmSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("BluetoothSignalStrengthFilter").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BluetoothSignalStrengthFilter(::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ instance)
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
      
      ::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter();
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

      BluetoothSignalStrengthFilter *wrapperInstance = new BluetoothSignalStrengthFilter(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapBluetoothSignalStrengthFilter(winRtInstance));
    }


  



    static void SamplingIntervalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(info.This()))
      {
        return;
      }

      BluetoothSignalStrengthFilter *wrapper = BluetoothSignalStrengthFilter::Unwrap<BluetoothSignalStrengthFilter>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->SamplingInterval;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SamplingIntervalSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsNumber())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(info.This()))
      {
        return;
      }

      BluetoothSignalStrengthFilter *wrapper = BluetoothSignalStrengthFilter::Unwrap<BluetoothSignalStrengthFilter>(info.This());

      try 
      {
        
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->SamplingInterval = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void OutOfRangeTimeoutGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(info.This()))
      {
        return;
      }

      BluetoothSignalStrengthFilter *wrapper = BluetoothSignalStrengthFilter::Unwrap<BluetoothSignalStrengthFilter>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->OutOfRangeTimeout;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void OutOfRangeTimeoutSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsNumber())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(info.This()))
      {
        return;
      }

      BluetoothSignalStrengthFilter *wrapper = BluetoothSignalStrengthFilter::Unwrap<BluetoothSignalStrengthFilter>(info.This());

      try 
      {
        
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->OutOfRangeTimeout = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void OutOfRangeThresholdInDBmGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(info.This()))
      {
        return;
      }

      BluetoothSignalStrengthFilter *wrapper = BluetoothSignalStrengthFilter::Unwrap<BluetoothSignalStrengthFilter>(info.This());

      try 
      {
        ::Platform::IBox<short>^ result = wrapper->_instance->OutOfRangeThresholdInDBm;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void OutOfRangeThresholdInDBmSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(info.This()))
      {
        return;
      }

      BluetoothSignalStrengthFilter *wrapper = BluetoothSignalStrengthFilter::Unwrap<BluetoothSignalStrengthFilter>(info.This());

      try 
      {
        
        ::Platform::IBox<short>^ winRtValue = ref new ::Platform::Box<short>(static_cast<short>(Nan::To<int32_t>(value).FromMaybe(0)));

        wrapper->_instance->OutOfRangeThresholdInDBm = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void InRangeThresholdInDBmGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(info.This()))
      {
        return;
      }

      BluetoothSignalStrengthFilter *wrapper = BluetoothSignalStrengthFilter::Unwrap<BluetoothSignalStrengthFilter>(info.This());

      try 
      {
        ::Platform::IBox<short>^ result = wrapper->_instance->InRangeThresholdInDBm;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InRangeThresholdInDBmSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^>(info.This()))
      {
        return;
      }

      BluetoothSignalStrengthFilter *wrapper = BluetoothSignalStrengthFilter::Unwrap<BluetoothSignalStrengthFilter>(info.This());

      try 
      {
        
        ::Platform::IBox<short>^ winRtValue = ref new ::Platform::Box<short>(static_cast<short>(Nan::To<int32_t>(value).FromMaybe(0)));

        wrapper->_instance->InRangeThresholdInDBm = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBluetoothSignalStrengthFilter(::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ wintRtInstance);
    friend ::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ UnwrapBluetoothSignalStrengthFilter(Local<Value> value);
  };
  Persistent<FunctionTemplate> BluetoothSignalStrengthFilter::s_constructorTemplate;

  v8::Local<v8::Value> WrapBluetoothSignalStrengthFilter(::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BluetoothSignalStrengthFilter::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Bluetooth::BluetoothSignalStrengthFilter^ UnwrapBluetoothSignalStrengthFilter(Local<Value> value)
  {
     return BluetoothSignalStrengthFilter::Unwrap<BluetoothSignalStrengthFilter>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBluetoothSignalStrengthFilter(Local<Object> exports)
  {
    BluetoothSignalStrengthFilter::Init(exports);
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

  // (jasongin) Hand-patched generated code due to Bluetooth bug in 15063
  InitializeSecurity();

  NodeRT::Windows::Devices::Bluetooth::InitBluetoothCacheModeEnum(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothMajorClassEnum(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothMinorClassEnum(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothServiceCapabilitiesEnum(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothConnectionStatusEnum(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothErrorEnum(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothAddressTypeEnum(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothAdapter(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothDeviceId(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothUuidHelper(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothDevice(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothClassOfDevice(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothLEAppearanceCategories(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothLEAppearanceSubcategories(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothLEAppearance(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothLEDevice(target);
  NodeRT::Windows::Devices::Bluetooth::InitBluetoothSignalStrengthFilter(target);

  NodeRT::Utils::RegisterNameSpace("Windows.Devices.Bluetooth", target);
}


NODE_MODULE(binding, init)