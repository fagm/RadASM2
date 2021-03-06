
;#########################################################################
;		Include files

include windows.inc
include kernel32.inc
include user32.inc
include Comctl32.inc
;include shell32.inc
;include ComDlg32.inc
include Gdi32.inc

;#########################################################################
;		Libraries

includelib kernel32.lib
includelib user32.lib
includelib Comctl32.lib
;includelib shell32.lib
;includelib ComDlg32.lib
includelib Gdi32.lib

;#########################################################################
;		RadASM Add In Include

include ..\radasm.inc

;#########################################################################
;		VKim's Debug

include masm32.inc
includelib masm32.lib
include debug.inc
includelib debug.lib

DBGWIN_DEBUG_ON = 1		; include debug info into the program
DBGWIN_EXT_INFO = 0		; include extra debug info into the program

;#########################################################################
;		Prototypes

DLLProc					PROTO :DWORD,:DWORD,:DWORD,:DWORD
InstallDLL				PROTO :DWORD,:DWORD
TextOutput				PROTO :DWORD
clrOutput				PROTO 
HexOutput				PROTO :DWORD

PROPERTIES struct
	nSize			dd ?
	Owner			dd ?
	nType			db ?
PROPERTIES ends

ADDINOPT struct
	lpStr			dd ?
	nAnd			dd ?
	nOr				dd ?
ADDINOPT ends

.data

szProcDump				db 'Dump procs',0
mytbbutton				TBBUTTON <?,?,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,NULL,NULL>
myaddbitmap				TBADDBITMAP <NULL,?>
szEnableProcDump		db 'Enable Proc Dump',0
AddinOpt				ADDINOPT <offset szEnableProcDump,1,1>
						ADDINOPT <0,0,0>

.data?

hInstance				dd ?	;Dll's module handle
lpHandles				dd ?	;Pointer to handles struct
lpProc					dd ?	;Pointer to proc struct
lpData					dd ?	;Pointer to data struct
hOut					dd ?	;Handle of output window
IDAddIn					dd ?	;Unique ID for this AddIn
buffer					db 16384 dup(?)

.code

;#########################################################################
;		Output Window procs

TextOutput proc lpszStr

   pushad
   push  lpszStr
   mov   eax,lpProc
   call  [eax].ADDINPROCS.lpTextOut
   popad	
   ret

TextOutput endp

;#########################################################################

clrOutput proc

   pushad
   mov   eax,lpProc
   call  [eax].ADDINPROCS.lpClearOut
   popad	
   ret

clrOutput endp

;#########################################################################

HexOutput proc val:DWORD
	
	pushad
	push  val
	mov   eax,lpProc
	call  [eax].ADDINPROCS.lpHexOut
	popad
	ret
	
HexOutput endp
