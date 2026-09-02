!include "MUI2.nsh"

!ifndef VERSION
	!define VERSION 0.0.0
!endif
!define NAME "OpenVPN Config Manager"
!define UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}"

Name "${NAME}"
OutFile "OpenVPNConfigManagerSetup-${VERSION}.exe"
InstallDir "$PROGRAMFILES32\${NAME}" 
RequestExecutionLevel "admin"

; Installer Page
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "LICENSE"
!insertmacro MUI_PAGE_DIRECTORY
ShowInstDetails show
!insertmacro MUI_PAGE_INSTFILES
!define MUI_FINISHPAGE_NOAUTOCLOSE
!insertmacro MUI_PAGE_FINISH

; Uninstaller Page
!insertmacro MUI_UNPAGE_WELCOME
!define MUI_UNCONFIRMPAGE_TEXT_TOP "This wizard will completely uninstall ${NAME} and all of its components from this computer."
!define MUI_UNCONFIRMPAGE_TEXT_LOCATION "Uninstall Directory"
!insertmacro MUI_UNPAGE_CONFIRM
ShowUnInstDetails show
!insertmacro MUI_UNPAGE_INSTFILES
!define MUI_UNFINISHPAGE_NOAUTOCLOSE
!define MUI_FINISHPAGE_LINK "Propose issues on Github"
!define MUI_FINISHPAGE_LINK_LOCATION "https://github.com/Narezzurri/OpenVPN-Config-Manager/issues"
!insertmacro Mui_Unpage_Finish

!insertmacro Mui_Language "English"

Section "install"
; Program files
SetOutPath "$INSTDIR"
File "Checker.exe"
File "Auth.exe"
File "LICENSE"
WriteUninstaller "Uninstall.exe"
CreateDirectory "$SMPROGRAMS\${NAME}"
CreateShortCut "$SMPROGRAMS\${NAME}\${NAME}.lnk" $INSTDIR\Uninstall.exe
CreateShortCut "$SMPROGRAMS\${NAME}\Uninstall.lnk" $INSTDIR\Uninstall.exe
; Register in the Control Panel
SetRegView 32
WriteRegStr "HKLM" "${UNINST_KEY}" "DisplayName" "${NAME}"
WriteRegStr "HKLM" "${UNINST_KEY}" "UninstallString" "$INSTDIR\Uninstall.exe"
WriteRegStr "HKLM" "${UNINST_KEY}" "DisplayVersion" "${VERSION}"
WriteRegStr "HKLM" "${UNINST_KEY}" "Publisher" "Narezzurri"
WriteRegStr "HKLM" "${UNINST_KEY}" "HelpLink" "https://github.com/Narezzurri/OpenVPN-Config-Manager"
SectionEnd

Section "uninstall"
; Program files
RMDir /r "$INSTDIR"
RMDir /r "$SMPROGRAMS\${NAME}"
; Regedit
SetRegView 32
DeleteRegKey "HKLM" "${UNINST_KEY}"
SectionEnd
