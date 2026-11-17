; ==================================================================================================
; Title:   Pahor1_Globals.inc
; Author:  Pahor.m (Tempuyax) ~ September 2019.
; Version: 1.0.0
; Purpose: tutorial No.1 with ObjAsm32.
; ==================================================================================================

;Creates szPahor1 string in .const == Classname
;This is the same as "Classname" in Iczelions tutorial
CStr szPahor1, "IczPahor1"                

;This is the same as "AppName" in Iczelions tutorial
CStr szAppTitle, "ObjAsm32, by Pahor.m September 2019"    

                                             
;This is the Copyright
CStr szAboutText, "Pahor1 Application", 13, 10, 13, 10, \
                  "Designed with ObjAsm32", 13, 10, \
                  "using Microsoft's MASM32", 13, 10, 13, 10, \
                  "Copyright © Pahor.m ~ September 2019"

;Menu ID
IDM_FILE  equ  1000
IDM_NEW	  equ  1001
IDM_OPEN  equ  1002
IDM_SAVE  equ  1003
IDM_EXIT  equ  1004

IDM_INFO  equ  2000
IDM_HELP  equ  2001
IDM_ASST  equ  2002
IDM_ABOUT equ  2003
