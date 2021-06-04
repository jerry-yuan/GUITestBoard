/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

/* Definitions of physical drive number for each drive */
#define DEV_W25X		0	/* Example: Map Ramdisk to physical drive 0 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/
/* Physical drive nmuber to identify the drive */
DSTATUS disk_status (BYTE pdrv) {
    DSTATUS stat;
    int result;

    switch (pdrv) {
    case DEV_W25X:

        // translate the reslut code here

        return 0;
    }
    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
/* Physical drive nmuber to identify the drive */
DSTATUS disk_initialize (BYTE pdrv) {
    DSTATUS stat;
    int result;

    switch (pdrv) {
    case DEV_W25X :
        return 0;
    }
    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE pdrv,		/* Physical drive nmuber to identify the drive */
    BYTE *buff,		/* Data buffer to store read data */
    LBA_t sector,	/* Start sector in LBA */
    UINT count		/* Number of sectors to read */
) {
    DRESULT res;
    int result;

    switch (pdrv) {
    case DEV_W25X :
        // translate the arguments here
		W25X_Read_Data(sector*512,buff,count*512);
        return RES_OK;
    }

    return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
    BYTE pdrv,			/* Physical drive nmuber to identify the drive */
    const BYTE *buff,	/* Data to be written */
    LBA_t sector,		/* Start sector in LBA */
    UINT count			/* Number of sectors to write */
) {
    DRESULT res;
    int result;

    switch (pdrv) {
    case DEV_W25X :
        // translate the arguments here
        W25X_Write_Buffer(sector*512,buff,count*512);
        return RES_OK;
    }

    return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
    BYTE pdrv,		/* Physical drive nmuber (0..) */
    BYTE cmd,		/* Control code */
    void *buff		/* Buffer to send/receive control data */
) {
    DRESULT res;
    int result;

    switch (pdrv) {
    case DEV_W25X :
        // Process of the command for the RAM drive
        if(cmd == GET_SECTOR_COUNT){
			(*(DWORD*)buff) = 32768;
			return RES_OK;
        }else if(cmd==GET_BLOCK_SIZE){
			(*(DWORD*)buff) = 256;
			return RES_OK;
        }else if(cmd==CTRL_SYNC){
			return RES_OK;
        }
        return res;
    }

    return RES_PARERR;
}

DWORD get_fattime(void){
	return 0;
}
