  // (jasongin) Workaround Bluetooth bug in 15063

#include <sddl.h>

#define _WIN32_DCOM
#define _WIN32_WINNT 0x0500
#include <iostream>
using namespace std;
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

DWORD
MakeSDAbsolute (
    PSECURITY_DESCRIPTOR OldSD,
    PSECURITY_DESCRIPTOR *NewSD
    )
{
  PSECURITY_DESCRIPTOR  sd=NULL;
  DWORD                 descriptorSize;
  DWORD                 daclSize;
  DWORD                 saclSize;
  DWORD                 ownerSIDSize;
  DWORD                 groupSIDSize;
  PACL                  dacl;
  PACL                  sacl;
  PSID                  ownerSID;
  PSID                  groupSID;
  BOOL                  present;
  BOOL                  systemDefault;

  //
  // Get SACL
  //
  if (!GetSecurityDescriptorSacl (OldSD, &present, &sacl, &systemDefault))
    return GetLastError();

  if (sacl && present)
  {
    saclSize = sacl->AclSize;
  }
  else {
    saclSize = 0;
  }

  //
  // Get DACL
  //
  if (!GetSecurityDescriptorDacl (OldSD, &present, &dacl, &systemDefault))
      return GetLastError();

  if (dacl && present)
  {
      daclSize = dacl->AclSize;
  }
  else {
    daclSize = 0;
  }

  //
  // Get Owner
  //
  if (!GetSecurityDescriptorOwner (OldSD, &ownerSID, &systemDefault))
    return GetLastError();

  ownerSIDSize = GetLengthSid (ownerSID);

  //
  // Get Group
  //
  if (!GetSecurityDescriptorGroup (OldSD, &groupSID, &systemDefault))
    return GetLastError();

  groupSIDSize = GetLengthSid (groupSID);

  //
  // Do the conversion
  //
  descriptorSize = 0;

  MakeAbsoluteSD (OldSD, sd, &descriptorSize, dacl, &daclSize, sacl,
                  &saclSize, ownerSID, &ownerSIDSize, groupSID,
                  &groupSIDSize);

  sd = (PSECURITY_DESCRIPTOR) new BYTE [SECURITY_DESCRIPTOR_MIN_LENGTH];
  if (!InitializeSecurityDescriptor (sd, SECURITY_DESCRIPTOR_REVISION))
      return GetLastError();

  if (!MakeAbsoluteSD (OldSD, sd, &descriptorSize, dacl, &daclSize, sacl,
                        &saclSize, ownerSID, &ownerSIDSize, groupSID,
                        &groupSIDSize))
      return GetLastError();

  *NewSD = sd;
  return ERROR_SUCCESS;
}

void InitializeSecurity() {
  const char* security = "O:BAG:BAD:(A;;0x7;;;PS)(A;;0x3;;;SY)(A;;0x7;;;BA)(A;;0x3;;;AC)(A;;0x3;;;LS)(A;;0x3;;;NS)";
  PSECURITY_DESCRIPTOR pSecurityDescriptor;
  ULONG securityDescriptorSize;

  if (!ConvertStringSecurityDescriptorToSecurityDescriptor(
      security,
      SDDL_REVISION_1,
      &pSecurityDescriptor,
      &securityDescriptorSize)) {
    return;
  }

  // MakeSDAbsolute as defined in
  // https://github.com/pauldotknopf/WindowsSDK7-Samples/blob/master/com/fundamentals/dcom/dcomperm/SDMgmt.Cpp
  PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor = NULL;
  MakeSDAbsolute(pSecurityDescriptor, &pAbsoluteSecurityDescriptor);

  HRESULT hResult = CoInitializeSecurity(
      pAbsoluteSecurityDescriptor, // Converted from the above string.
      -1,
      nullptr,
      nullptr,
      RPC_C_AUTHN_LEVEL_DEFAULT,
      RPC_C_IMP_LEVEL_IDENTIFY,
      NULL,
      EOAC_NONE,
      nullptr);
  if (FAILED(hResult)) {
    return;
  }
}
