#include "efs.h"
#include "file.h"
#include "utils.h"
#include "fs_api.h"
#include "ls.h"

#define FILE_DELETED_SUCCESS TRUE
#define FILE_DELETED_NO_SUCH_FILE FALSE

static U8 file_system_status = FALSE;

EmbeddedFileSystem efs;

/* begin binary data: */
U8 bin_data[] = /* 163840 */
{0xEB,0x58,0x90,0x57,0x49,0x4E,0x49,0x4D,0x41,0x47,0x45,0x00,0x02,0x02,0x01
,0x00,0x02,0x70,0x00,0x40,0x01,0xFD,0x01,0x00,0x08,0x00,0x01,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x0D,0x6C,0x4C,0x50,0x20,0x20
,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x46,0x41,0x54,0x31,0x32,0x20
,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0xFA,0x33,0xC0,0x8E,0xD0,0xBC,0x00,0x7C,0xB8,0xB0,0x07,0x8E,0xD8,0x8E,0xC0
,0xB9,0x00,0x01,0x8B,0xF1,0xBF,0x00,0x03,0xF3,0xA5,0xB8,0xD0,0x07,0x50,0x8E
,0xD8,0x8E,0xC0,0xB8,0x80,0x01,0x50,0xCB,0xFB,0xBE,0x13,0x02,0xE8,0x3A,0x00
,0xB8,0x01,0x02,0xB9,0x01,0x00,0xBA,0x80,0x00,0x33,0xDB,0x8E,0xC3,0xBB,0x00
,0x7C,0x06,0x53,0xCD,0x13,0x72,0x0A,0x26,0x81,0x3E,0xFE,0x7D,0x55,0xAA,0x75
,0x01,0xCB,0xBE,0xD0,0x01,0xE8,0x14,0x00,0xB4,0x01,0xCD,0x16,0x74,0x06,0x32
,0xE4,0xCD,0x16,0xEB,0xF4,0x32,0xE4,0xCD,0x16,0x33,0xD2,0xCD,0x19,0xFC,0xAC
,0x0A,0xC0,0x74,0x08,0x56,0xB4,0x0E,0xCD,0x10,0x5E,0xEB,0xF3,0xC3,0x43,0x61
,0x6E,0x6E,0x6F,0x74,0x20,0x6C,0x6F,0x61,0x64,0x20,0x66,0x72,0x6F,0x6D,0x20
,0x68,0x61,0x72,0x64,0x64,0x69,0x73,0x6B,0x2E,0x0D,0x0A,0x49,0x6E,0x73,0x65
,0x72,0x74,0x20,0x53,0x79,0x73,0x74,0x65,0x6D,0x64,0x69,0x73,0x6B,0x20,0x61
,0x6E,0x64,0x20,0x70,0x72,0x65,0x73,0x73,0x20,0x61,0x6E,0x79,0x20,0x6B,0x65
,0x79,0x2E,0x0D,0x0A,0x00,0x44,0x69,0x73,0x6B,0x20,0x66,0x6F,0x72,0x6D,0x61
,0x74,0x74,0x65,0x64,0x20,0x77,0x69,0x74,0x68,0x20,0x57,0x69,0x6E,0x49,0x6D
,0x61,0x67,0x65,0x20,0x36,0x2E,0x35,0x30,0x20,0x28,0x63,0x29,0x20,0x31,0x39
,0x39,0x33,0x2D,0x32,0x30,0x30,0x34,0x20,0x47,0x69,0x6C,0x6C,0x65,0x73,0x20
,0x56,0x6F,0x6C,0x6C,0x61,0x6E,0x74,0x0D,0x0A,0x73,0x65,0x65,0x20,0x68,0x74
,0x74,0x70,0x3A,0x2F,0x2F,0x77,0x77,0x77,0x2E,0x77,0x69,0x6E,0x69,0x6D,0x61
,0x67,0x65,0x2E,0x63,0x6F,0x6D,0x0D,0x0A,0x42,0x6F,0x6F,0x74,0x73,0x65,0x63
,0x74,0x6F,0x72,0x20,0x66,0x72,0x6F,0x6D,0x20,0x43,0x2E,0x48,0x2E,0x20,0x48
,0x6F,0x63,0x68,0x73,0x74,0x61,0x74,0x74,0x65,0x72,0x0D,0x0A,0x0D,0x0A,0x4E
,0x6F,0x20,0x53,0x79,0x73,0x74,0x65,0x6D,0x64,0x69,0x73,0x6B,0x2E,0x20,0x42
,0x6F,0x6F,0x74,0x69,0x6E,0x67,0x20,0x66,0x72,0x6F,0x6D,0x20,0x68,0x61,0x72
,0x64,0x64,0x69,0x73,0x6B,0x2E,0x0D,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x55,0xAA};
/* end binary data. size = 163840 bytes */

U8 extra_bytes[]={0xfd,0xff,0xff};//write it at 0x200 and 0x400

/**
********************************************************************************************
 Function Name : fs_init()

 Description   :	

 Input         :	

 Output        : Void

 Note          :
********************************************************************************************
*/
S32 fs_init(void)
{
  return efs_init( &efs, 0 );
}
/**
********************************************************************************************
 Function Name : fs_close()

 Description   :	

 Input         :	

 Output        : Void

 Note          :
********************************************************************************************
*/
S32 fs_close(void)
{
  return  fs_umount(&efs.myFs);
}
/**
********************************************************************************************
 Function Name : fopen()

 Description   :	

 Input         :	

 Output        : Void

 Note          :
********************************************************************************************
*/
U8 fopen(File* file, S8 *filename,U8 open_mode)
{
  return file_fopen( file, &efs.myFs ,filename, open_mode);
}

/**
*******************************************************************************
  Function Name : get_available_free_size()

  Description :	 

  Input :	

  Output :	none

  Note : 
*******************************************************************************
*/
U32 get_available_free_size(void)
{
  U32 cluster = 0;
  
  cluster = fat_countFreeClusters(&efs.myFs);
  return cluster * NUM_OF_BYTES_PER_CLUSTER;
}

/**
*******************************************************************************
  Function Name : set_file_system_status()

  Description :	 

  Input :	

  Output :	none

  Note : 
*******************************************************************************
*/
void set_file_system_status(U8 status)
{
  file_system_status = status;
}

/**
*******************************************************************************
  Function Name : get_file_system_status()

  Description :	 

  Input :	

  Output :	none

  Note : 
*******************************************************************************
*/
U8 get_file_system_status(void)
{
  return file_system_status;
}

/**
*******************************************************************************
  Function Name : delete_file()

  Description :	 

  Input :	

  Output :	none

  Note : 
*******************************************************************************
*/
U8 delete_file(U8 *name)
{
  DirList list;
  U8 retval = FILE_DELETED_SUCCESS;

  ls_openDir(&list,&efs.myFs,"/");
  if(rmfile(&efs.myFs,name) == -1)
  {
    retval = FILE_DELETED_NO_SUCH_FILE;
  }
  fs_umount(&efs.myFs);

  return retval;
}


