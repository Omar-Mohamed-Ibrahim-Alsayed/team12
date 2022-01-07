#define _SYSTEM 1
#include <stdlib.h>
#include <stdio.h>
#include "pagetable.h"
#include "util.h"
#include "vm.h"
#include <minix/config.h>
#include <minix/const.h>
//structure of the outer page-table containing an array of all inner page tables.
struct outer_pagetable {
 struct pagetable inner_pagetables[NR_SYS_CHUNKS]; /*NR_SYS_CHUNKS is pre-defined minix variable 
from config file that represent the total number of memory block that can be made avaliable to the processes.*/
}


