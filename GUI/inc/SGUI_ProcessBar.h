#ifndef __INCLUDE_GUI_PROCESSBAR_H__
#define __INCLUDE_GUI_PROCESSBAR_H__
//=======================================================================//
//= Include files.														=//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"

//=======================================================================//
//= Data type definition.												=//
//=======================================================================//
typedef enum
{
	SGUI_PROCBAR_UP = 0,							//Process bar direction to up.
	SGUI_PROCBAR_DOWN,							//Process bar direction to down.
	SGUI_PROCBAR_LEFT,							//Process bar direction to left.
	SGUI_PROCBAR_RIGHT,							//Process bar direction to right.
}SGUI_PROCBAR_DIRECTION;

typedef struct
{
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_UINT8			uiDepthBits;
	#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_COLOR			eProcessBarColor;
	SGUI_COLOR			eEdgeColor;
	SGUI_COLOR			eBackgroundColor;
} SGUI_PROCBAR_PALETTE;

typedef struct
{
	SGUI_RECT				stLayout;
	SGUI_UINT32				sMaxValue;
	SGUI_PROCBAR_DIRECTION	eDirection;
	SGUI_PROCBAR_PALETTE	stPalette;
}SGUI_PROCBAR_PARAMETER;

typedef struct
{
	SGUI_SIZE				sValue;
}SGUI_PROCBAR_DATA;

typedef struct
{
	SGUI_PROCBAR_PARAMETER	stParameter;
	SGUI_PROCBAR_DATA		stData;
}SGUI_PROCBAR_STRUCT;

//=======================================================================//
//= Public function declaration.										=//
//=======================================================================//
void SGUI_ProcessBar_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_PROCBAR_STRUCT *pProcessBarData);

#endif // __INCLUDE_GUI_PROCESSBAR_H__
