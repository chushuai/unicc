; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "UniCC Parser Generator"
#define MyAppVersion "1.3.1"
#define MyAppPublisher "Phorward Software Technologies"
#define MyAppURL "http://phorward.info"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{03C9B79B-502F-4BCE-BDC7-62993EB39F8E}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\UniCC
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
OutputBaseFilename=unicc-1.3.1
Compression=lzma
SolidCompression=yes
ChangesEnvironment=yes
LicenseFile=..\..\LICENSE
InfoBeforeFile=..\..\CHANGELOG.md
ArchitecturesAllowed=x86 x64 
;ArchitecturesInstallIn64BitMode=x64

[Tasks]
Name: "setenv_PATH"; Description: "Add UniCC to &PATH (recommended)"; GroupDescription: "{cm:AdditionalIcons}";
Name: "setenv_UNICC_TPLDIR"; Description: "Create &UNICC_TPLDIR-variable (recommended)"; GroupDescription: "{cm:AdditionalIcons}";

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "..\..\unicc.exe"; DestDir: "{app}\bin"; DestName: "unicc.exe"; Flags: ignoreversion;
Source: "..\..\unicc.dtd"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\unicc.pdf"; DestDir: "{app}"; Flags: ignoreversion

Source: "..\..\README.md"; DestDir: "{app}"; DestName: "README.txt"; Flags: ignoreversion
Source: "..\..\CHANGELOG.md"; DestDir: "{app}"; DestName: "CHANGELOG.txt"; Flags: ignoreversion
Source: "..\..\LICENSE"; DestDir: "{app}"; DestName: "LICENSE.txt"; Flags: ignoreversion

Source: "..\..\targets\*.tlt"; DestDir: "{app}\targets"; Flags: ignoreversion
Source: "..\..\examples\*"; DestDir: "{app}\examples"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\README"; Filename: "{cmd}"; Parameters: "/C more ""{app}\README.txt"""
Name: "{group}\CHANGELOG"; Filename: "{cmd}"; Parameters: "/C more ""{app}\CHANGELOG.txt"""
Name: "{group}\LICENSE"; Filename: "{cmd}"; Parameters: "/C more ""{app}\LICENSE.txt"""
Name: "{group}\examples"; Filename: "{app}\examples"
Name: "{group}\User's Manual"; Filename: "{app}\doc\unicc.pdf"; WorkingDir: "{app}"
Name: "{group}\UniCC prompt"; Filename: "{cmd}"; Parameters: "/K ""title UniCC prompt"""; WorkingDir: "{app}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: expandsz; ValueName: "UNICC_TPLDIR"; ValueData: "{app}\targets"; Tasks: setenv_UNICC_TPLDIR

;http://stackoverflow.com/questions/3304463/how-do-i-modify-the-path-environment-variable-when-running-an-inno-setup-install
[Code]
const
	ModPathName = 'setenv_PATH';
	ModPathType = 'user';

function ModPathDir(): TArrayOfString;
begin
	setArrayLength(Result, 1)
	Result[0] := ExpandConstant('{app}\bin');
end;
#include "modpath.iss"
