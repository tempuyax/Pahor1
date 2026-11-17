; ==================================================================================================
; Title:   Pahor1.asm
; Author:  Pahor.m  @ September 2019
; Version: 1.0.0
; Purpose: Demonstration program 1 of ObjAsm32.
; ==================================================================================================

%include @Environ(OA32_PATH)\\Code\\Macros\\Model.inc       ;Include & initialize standard modules
SysSetup OOP_WINDOWS ;, DEBUG(WND)                          ;Loads OOP files and OS related objects

include Pahor1_Globals.inc                                  ;Includes application globals

; For XMenu Function
% include &MacPath&UStrings.inc                             ;Includes Unicode support for DlgTmpl
% include &MacPath&DlgTmpl.inc                              ;Includes Dlg Template macros for XMenu
IncludeAPIs HtmlHelp

; For COM Function
% include &MacPath&BStrings.inc                             ;UNICODE string support
% include &COMPath&COM.inc                                  ;COM basic support
% include &COMPath&OAIDL.inc
% include &COMPath&COM_Dispatch.inc
% include &COMPath&COM_Interfaces.inc                       ;COM common interfaces
IncludeAPIs ole32, oleaut32, AdvApi32             			;Includes COM these APIs

;Load or build the following objects
LoadObjects Dialog, DialogModal, DialogModalIndirect, DialogAbout
LoadObjects SimpleImageList, MaskedImageList
LoadObjects WinApp, SdiApp                                  ;Include SDI framework library
LoadObjects Stream, Collection
LoadObjects MsgInterceptor, XMenu
LoadObjects MSAgent

include Pahor1.inc                                          ;Includes Demonstration object (insert .code)
                                                            ;The application is an object called "DemoX"
start:                                                      ;Program entry point
    SysInit                                                 ;Runtime initialization of OOP model (Required)
                                                            ;Registering of the class is carried out
    OCall TPL_Pahor1::Pahor1.Init                           ;Initialize the object data
    OCall TPL_Pahor1::Pahor1.Run                      
    OCall TPL_Pahor1::Pahor1.Done                           ; insert If COM Active

    SysDone                                                 ;Runtime finalization of the OOP model (Required)
    invoke ExitProcess, 0                                   ;Exits program returning 0 to the OS
end start                                                   ;Code end and defines prg entry point
