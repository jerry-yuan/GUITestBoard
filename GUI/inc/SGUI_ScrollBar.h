#ifndef __INCLUDE_GUI_SCROLLBAR__
#define __INCLUDE_GUI_SCROLLBAR__
//=======================================================================//
//= Include files.														=//
//=======================================================================//
#include "SGUI_Basic.h"
#include "SGUI_Common.h"

//=======================================================================//
//= Data type definition.												=//
//=======================================================================//
typedef enum
{
	SGUI_SCROLLBAR_VERTICAL = 0,						//Vertical scroll bar.
	SGUI_SCROLLBAR_HORIZONTAL,						//Horizontal scroll bar.
}SGUI_SCROLLBAR_DIRECTION;

typedef struct
{
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_UINT8				uiDepthBits;
	#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_COLOR				eHandleColor;
	SGUI_COLOR				eEdgeColor;
	SGUI_COLOR				eBackgroundColor;
} SGUI_SCROLLBAR_PALETTE;

typedef struct
{
	SGUI_RECT					stLayout;
	SGUI_SIZE					sMaxValue;
	SGUI_SCROLLBAR_DIRECTION	eDirection;
	SGUI_SCROLLBAR_PALETTE		stPalette;
}SGUI_SCROLLBAR_PARAM;

typedef struct
{
	SGUI_SIZE					sValue;
}SGUI_SCROLLBAR_DATA;

typedef struct
{
	SGUI_SCROLLBAR_PARAM		stParam;
	SGUI_SCROLLBAR_DATA			stData;
}SGUI_SCROLLBAR_STRUCT;

//=======================================================================//
//= Public function declaration.										=//
//=======================================================================//
void		SGUI_ScrollBar_Initialize(SGUI_SCROLLBAR_STRUCT* pstObj, const SGUI_SCROLLBAR_PARAM* pcstInitParam);
#define		SGUI_ScrollBar_SetMax(OBJ, MAX) \
				{(OBJ)->stParam.sMaxValue = MAX;}
#define 	SGUI_ScrollBar_GetMax(OBJ) \
				((OBJ)->stParam.sMaxValue)
void		SGUI_ScrollBar_SetValue(SGUI_SCROLLBAR_STRUCT* pstObj, SGUI_SIZE sNewValue);
#define 	SGUI_ScrollBar_GetValue(OBJ) \
				((OBJ)->stData.sValue)
void		SGUI_ScrollBar_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_SCROLLBAR_STRUCT* pstObj);

#endif // __INCLUDE_GUI_SCROLLBAR_STRUCT__
