#ifndef _HLFS_MISC_H_
#define _HLFS_MISC_H_

#include <stdio.h>
#include <stdint.h>
#include "storage.h"

uint64_t get_current_time(void);
int build_segfile_name(uint32_t segno, const char* segfile);
int build_segfile_name_by_address(uint64_t storage_address, const char* segfile);
uint32_t get_segfile_no(const char * segfile);
char *read_block(struct back_storage *storage ,uint64_t storage_address,uint32_t block_size);
int parse_from_uri(const char *uri,char ** head, char** hostname ,char** dir,char** fs_name,int* port);

#endif 