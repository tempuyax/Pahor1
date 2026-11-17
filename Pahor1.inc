; ==================================================================================================
; Title:   Pahor1.inc
; Author:  Pahor.m (Tempuyax) ~ September 2019.
; Version: 1.0.0
; Purpose: Demenstrasi tutorial No.1 dengan mode ObjAsm32.
; ==================================================================================================

Object Pahor1, 10001, SdiApp      			;Objek Turunan dari Single Document Interface (SDI) dgn (ID >= 10001)
  RedefineMethod    Init          			;redefinisi Metode Init untuk memmbuat window 
  RedefineMethod    Done
  StaticMethod      Startup       			;Startup method redefinition to mirror Iczelion registration
                                  			;Note: WM_DESTROY and Default handling is inherited from
                                  			;the SdiApp object. We will reuse this source as is.
  DynamicEvent      OnCommand,  		WM_COMMAND
  ;VirtualEvent      OnCreate,   		WM_CREATE
  VirtualEvent      OnClose,    		WM_CLOSE, WM_QUERYENDSESSION
  VirtualEvent      OnPaint,    		WM_PAINT
  VirtualEvent      OnDestroy,  		WM_DESTROY
  
  DefineVariable 	dWwd, 				DWord,	500 ;Default Main Window creation width
  DefineVariable 	dWht, 				DWord,	350 ;Default Main Window creation height
  DefineVariable	dWtx, 				DWord,	  0	 
  DefineVariable	dWty, 				DWord,	  0
  DefineVariable    hMenuInit,          Handle,   0
  DefineVariable    pIconImageList,     Pointer,  0
  DefineVariable    pXMenu,     		Pointer,  0
  DefineVariable    pAgent,     		Pointer,  0
  DefineVariable	fChek,      		DWord,    MF_UNCHECKED ;init value


ObjectEnd                         		;Ends object definition

.code
; ==================================================================================================
;    Pahor1 implementation
; ==================================================================================================

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    Pahor1.Init
; Purpose:   Initalizes the SDI application object, when an instance is created.
;            This mirrors Iczelions "WinMain" proceedure (mid section)
;            Note: The inherited "Run" method from SdiApp is equivalent to the last message loop
;                  section in Iczelions "WinMain". So we need not redefine this method, we will
;                  simply reuse the source as provided.
; Arguments: None.
; Return:    Nothing.

Method Pahor1.Init, uses ebx esi
    invoke CoInitialize, NULL                                  ; insert If COM Active

;	esi = This Object Instance
    SetObject esi 
    ACall esi.Init

;   Setup XMenu icons
    mov ebx, $New(MaskedImageList, Init, esi, 16, 16, 1)
    mov [esi].pIconImageList, ebx
    OCall ebx::MaskedImageList.IconLoadResource, "ICON_NEW"    ; index at 00, See Resource Xmenu
    OCall ebx::MaskedImageList.IconLoadResource, "ICON_OPEN"   ; index at 01, See Resource Xmenu
    OCall ebx::MaskedImageList.IconLoadResource, "ICON_SAVE"   ; index at 02, See Resource Xmenu
    OCall ebx::MaskedImageList.IconLoadResource, "ICON_EXIT"   ; index at 03, See Resource Xmenu
    OCall ebx::MaskedImageList.IconLoadResource, "ICON_HELP"   ; index at 04, See Resource Xmenu
    OCall ebx::MaskedImageList.IconLoadResource, "ICON_ABOUT"  ; index at 05, See Resource Xmenu

;   Load Menu to window
    mov [esi].hMenuInit, $invoke(LoadMenu, hInstance, "MENU_APP")

;   Create Main Windows
    mov [esi].dWtx, $invoke(CenterForm, [esi].dWwd, $invoke(GetSystemMetrics, SM_CXSCREEN)) ;Center the form
    mov [esi].dWty, $invoke(CenterForm, [esi].dWht, $invoke(GetSystemMetrics, SM_CYSCREEN)) ;Center the form

    invoke CreateWindowEx, NULL, offset szPahor1, offset szAppTitle, WS_OVERLAPPEDWINDOW, \
              [esi].dWtx, [esi].dWty, [esi].dWwd, [esi].dWht, NULL, [esi].hMenuInit, hInstance, esi ;Pass the instance pointer

;   Show XMenu After CreateWindowEx function
    mov [esi].pXMenu, $New(XMenu, Init, esi, [esi].hWnd, 0, 0, [esi].pIconImageList, NULL, 0)

;   Init MSAgent Object and active
			mov [esi].pAgent, $New(MSAgent, Init, esi, 0009H)   ;English
			mov eax, [esi].dWwd
			shr eax, 2
			add eax, [esi].dWtx
			add eax, 50
			mov ecx, [esi].dWht
			shr ecx, 2
			add ecx, [esi].dWty
			add ecx, 50
			OCall [esi].pAgent::MSAgent.SetPosition, eax, ecx

    invoke ShowWindow, [esi].hWnd, SW_SHOWNORMAL        ;Show the window
    invoke UpdateWindow, [esi].hWnd                     ;Update if necessary
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    Pahor1.Done
; Purpose:   Finalizes the SDI application object.
; Arguments: None.
; Return:    Nothing.

Method Pahor1.Done, uses esi
    SetObject esi
    Destroy [esi].pIconImageList
    Destroy [esi].pXMenu
    Destroy [esi].pAgent
    ACall esi.Done
    invoke CoUninitialize
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    Pahor1.OnCreate
; Purpose:   Event procedure for WM_CREATE message.
; Arguments: Arg1: First message parameter.
;            Arg2: Second message parameter.
; Return:    Zero if handled.

;Method Pahor1.OnCreate, uses ebx esi, wParam:dword, lParam:dword
;    SetObject esi
;
;    mov [esi].pToolbarData, $New(Toolbar, Init, esi, [esi].hWnd, offset ToolbarData, [esi].pIconImageList, NULL, NULL)
;
;    mov ebx, $OCall([esi].pToolbarData::Toolbar.GetHeight)
;    OCall [esi].pToolbarData::Toolbar.GetWidth
;    mov ecx, [esi].pToolbarData
;    OCall [esi].pRebar::Rebar.InsertBand, [ecx].Toolbar.hWnd, eax, ebx
;
;    xor eax, eax
;MethodEnd

; —————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    Pahor1.OnDestroy
; Purpose:   Event procedure for WM_DESTROY message.
; Arguments: Arg1: First message parameter.
;            Arg2: Second message parameter.
; Return:    Zero.

Method Pahor1.OnDestroy, uses esi, wParam:dword, lParam:dword
    SetObject esi
    invoke DestroyMenu, [esi].hMenuInit
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    Pahor1.OnPaint
; Purpose:   Event procedure for WM_PAINT message.
; Arguments: Arg1: First message parameter.
;            Arg2: Second message parameter.
; Return:    Zero if handled.

Method Pahor1.OnPaint, uses esi, wParam:dword, lParam:dword
    local PS:PAINTSTRUCT, hDC:Handle, Rct:RECT

    SetObject esi
    mov hDC, $invoke(BeginPaint, [esi].hWnd, addr PS)

    invoke GetClientRect, [esi].hWnd, addr Rct
    invoke DrawEdge, hDC, addr Rct, EDGE_SUNKEN, BF_RECT
    invoke EndPaint, [esi].hWnd, addr PS
    mov eax, TRUE
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    Pahor1.OnCommand
; Purpose:   Event procedure for WM_COMMAND message.
; Arguments: Arg1: First message parameter.
;            Arg2: Second message parameter.
; Return:    Zero if handled.

Method Pahor1.OnCommand, uses esi, wParam:dword, lParam:dword
    local bBuffer[MAX_PATH]:byte
	local wRect:RECT, dRect:RECT, pt:POINT, Dpt:POINT
	local pDlg:Pointer, hdcMenu:HANDLE

    SetObject esi
    mov eax, wParam
    .if ax == IDM_EXIT
      invoke SendMessage, [esi].hWnd, WM_SYSCOMMAND, SC_CLOSE, NULL
      xor eax, eax

    .elseif ax == IDM_ASST
        .If [esi].fChek == MF_UNCHECKED
            Mov [esi].fChek, MF_CHECKED
            mov ebx, [esi].pXMenu
            Invoke CheckMenuItem, [ebx].XMenu.hMenu, IDM_ASST, [esi].fChek
		    OCall [esi].pAgent::MSAgent.Show
        .ElseIf [esi].fChek == MF_CHECKED
            Mov [esi].fChek, MF_UNCHECKED
            mov ebx, [esi].pXMenu
            Invoke CheckMenuItem, [ebx].XMenu.hMenu, IDM_ASST, [esi].fChek
		    OCall [esi].pAgent::MSAgent.Hide
       .EndIf
    	xor eax, eax

    .elseif ax == IDM_ABOUT
      ;   Center Main Dialog
      invoke GetClientRect, [esi].hWnd, addr wRect
      mov pDlg, $New(DialogAbout,Init, esi, [esi].hWnd)
      mov pt.x, $invoke(CenterForm, 0, wRect.right) ;Center the form
      mov pt.y, $invoke(CenterForm, 0, wRect.bottom) ;Center the form
      ;sub pt.x, 160
      ;sub pt.y, 100
      invoke ClientToScreen, [esi].hWnd, addr pt
      OCall pDlg::DialogAbout.ShowAt, pt.x, pt.y
      OCall pDlg::DialogAbout.Done
      xor eax, eax

    .elseif ax == IDM_HELP
      @invoke GetEnvironmentVariable, "OA32_PATH", addr bBuffer, sizeof bBuffer
      @invoke StrLCat, addr bBuffer, "\Help\ObjAsm32.chm", sizeof bBuffer
      invoke HtmlHelp, [esi].hWnd, addr bBuffer, HH_DISPLAY_TOPIC, 0
      xor eax, eax

    .else
      invoke DefWindowProc, [esi].hWnd, WM_COMMAND, wParam, lParam
    .endif
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    Pahor1.OnClose
; Purpose:   Event procedure for WM_CLOSE message.
; Arguments: Arg1: First message parameter.
;            Arg2: Second message parameter.
; Return:    Zero if handled.

Method Pahor1.OnClose, uses esi, wParam:dword, lParam:dword
    SetObject esi
    @invoke MessageBox, [esi].hWnd, "Are you sure ?", "Application exit", MB_YESNO or MB_ICONQUESTION
    .if eax == IDNO
      xor eax, eax
    .else
      invoke DefWindowProc, [esi].hWnd, WM_CLOSE, wParam, lParam
    .endif
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    Pahor1.Startup
; Purpose:   Registers the object class with the OS when the ObjectsInit macro is executed.
;            This mirrors Iczelions "WinMain" proceedure up to RegisterClassEx.
; Arguments: None.
; Return:    Nothing.

Method Pahor1.Startup
    local WC:WNDCLASSEX

    mov WC.cbSize, sizeof WNDCLASSEX
    mov WC.style, CS_VREDRAW or CS_HREDRAW
    m2m WC.lpfnWndProc, $MethodAddr(Pahor1.WndProc)  			;$MethodAddr is like offset but will
                                                     			;retrieve object method offsets
    mov WC.cbClsExtra, 0
    mov WC.cbWndExtra, 0
    m2m WC.hInstance, hInstance
    @invoke LoadBitmap, hInstance, "BMP_BACKGROUND"  			;Get Background Windowed from resource (file.rc)
    mov WC.hbrBackground, $invoke(CreatePatternBrush, eax) 		;Return Background to register
    mov WC.lpszMenuName, 0                          			;Menu is Null
    mov WC.lpszClassName, offset szPahor1            			;Same as "Classname" in Iczelions tutorial
    mov WC.hIcon, $invoke(LoadIcon, hInstance, "ICON_APP_32")   ;Get Icon image from resource (file.rc) 
    mov WC.hIconSm, 0
    mov WC.hCursor, $invoke(LoadCursor, 0, IDC_ARROW)

    invoke RegisterClassEx, addr WC
MethodEnd