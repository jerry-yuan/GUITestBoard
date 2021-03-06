#ifndef __INCLUDE_GUI_NOTICE_H__
#define __INCLUDE_GUI_NOTICE_H__
//=======================================================================//
//= Include files.														=//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"
#include "SGUI_Text.h"

//=======================================================================//
//= Data type definition.												=//
//=======================================================================//
typedef struct
{
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_UINT8			uiDepthBits;
	#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_COLOR			eEdgeColor;
	SGUI_COLOR			eFillColor;
	SGUI_COLOR			eTextColor;
}SGUI_NOTICE_PALETTE;
typedef struct
{
	SGUI_CSZSTR				cszNoticeText;
	const SGUI_BMP_RES*		pstIcon;
	SGUI_RECT				stLayout;
	SGUI_NOTICE_PALETTE		stPalette;
}SGUI_NOTICE_BOX;

//=======================================================================//
//= Public function declaration.										=//
//=======================================================================//
SGUI_SIZE	SGUI_Notice_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_NOTICE_BOX* pstObject, const SGUI_FONT_RES* pstFontRes, SGUI_INT uiTextOffset);
void		SGUI_Notice_FitArea(SGUI_SCR_DEV* pstDeviceIF, SGUI_RECT* pstFitArea);

#endif // __INCLUDE_GUI_NOTICE_H__
