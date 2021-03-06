#ifndef _INCLUDE_SGUI_MENU_H_
#define _INCLUDE_SGUI_MENU_H_
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"
#include "SGUI_Text.h"
#include "SGUI_ItemsBase.h"
//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef struct
{
    #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
    SGUI_UINT8                  uiDepthBits;
    #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
    SGUI_COLOR                  eBorder;
    SGUI_COLOR                  eDirectionIconColor;
} SGUI_MENU_PALETTE;
typedef struct
{
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_UINT8					uiDepthBits;
	#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_MENU_PALETTE			stMenu;
	SGUI_ITEMS_BASE_PALETTE		stItemBase;
} SGUI_MENU_PALETTE_INIT_PARAM;
typedef struct
{
	SGUI_RECT					stLayout;
	SGUI_MENU_PALETTE           stPalette;
	SGUI_ITEMS_BASE				stItems;
	const SGUI_FONT_RES*        pstFontRes;
}SGUI_MENU;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void					SGUI_Menu_Initialize(SGUI_MENU* pstObj, const SGUI_RECT* cpstLayout, const SGUI_MENU_PALETTE_INIT_PARAM* cpstPaletteInit, const SGUI_FONT_RES* pstFontRes, SGUI_ITEMS_ITEM* pstItemsData, SGUI_INT iItemsCount);
void					SGUI_Menu_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_MENU* pstObj);
void 					SGUI_Menu_Resize(SGUI_MENU* pstObj, const SGUI_RECT* pstNewLayout);
void 					SGUI_Menu_PopupSubMenu(SGUI_SCR_DEV* pstDeviceIF, SGUI_MENU* pstObj, const SGUI_RECT* cpstParentLayout);
#define					SGUI_Menu_GetSelection(OBJ) \
							(SGUI_ItemsBase_GetSelection(&(OBJ->stItems)))
#define					SGUI_Menu_Selecte(OBJ, IDX) \
							(SGUI_ItemsBase_Selecte(&(OBJ->stItems), IDX))

#define					SGUI_Menu_CanScrollUp(OBJ) \
							(SGUI_ItemsBase_CanScrollUp(&(OBJ->stItems)))
#define					SGUI_Menu_CanScrollDown(OBJ) \
							(SGUI_ItemsBase_CanScrollDown(&(OBJ->stItems)))

#endif // _INCLUDE_SGUI_MENU_H_
