/* ------------------------------
   $Id: mount.h,v 1.1 2009/11/16 05:38:07 marquet Exp $
   ------------------------------------------------------------

   Initialization and finalization
   Philippe Marquet, Nov 2009

*/

#ifndef MY_MOUNT_H_
#define MY_MOUNT_H_
#include "bloc.h"
#include "tools.h"

/*  initialize hardware, mount the "current" volume
    configuration with the $HW_CONFIG and $CURRENT_VOLUME environment
    variables.
 */
void mount();
void umount();

#endif
