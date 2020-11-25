; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "CXML"
#define MyAppVersion "1.7"
#define MyAppExeName "CXML_GTK_1.7.exe"
#define MyAppPublisher "Nouuu"
#define MyAppURL "https://github.com/Nouuu/CXML"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{2B4823CE-0A54-4C0C-98DC-D9096E1AAE24}}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
LicenseFile=D:\Projets\CXML\LICENSE
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputDir=D:\Projets\CXML\working_builds\part_4\windows\v{#MyAppVersion}
OutputBaseFilename=CXML_setup_{#MyAppVersion}
SetupIconFile=D:\Projets\CXML\working_builds\part_4\windows\v{#MyAppVersion}\gtk_files\CXML.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\Projets\CXML\working_builds\part_4\windows\v{#MyAppVersion}\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projets\CXML\working_builds\part_4\windows\v{#MyAppVersion}\gtk_files\*"; DestDir: "{app}\gtk_files"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Projets\CXML\working_builds\part_4\windows\gtk3-runtime-3.24.23-2020-11-22-ts-win64.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{tmp}\gtk3-runtime-3.24.23-2020-11-22-ts-win64.exe"; StatusMsg: Installing GTK+3.24.23 Runtime Libraries... 
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent unchecked;

