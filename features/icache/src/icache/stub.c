#include "glib.h"
#include "icache.h"
ICACHE_CTRL *icache_new(){
    return NULL;
}
int icache_init(ICACHE_CTRL *icache_ctrl,
		uint64_t iblock_size,
		uint64_t icache_size,
		uint64_t invalidate_trigger_level,
		uint64_t invalidate_once_size){
    return 0;
}
//int icache_insert_blocks(CACHE_CTRL *cache_ctrl, uint32_t start_block_no, uint32_t block_count,char *block_buf);
int icache_insert_iblock(ICACHE_CTRL *icache_ctrl, uint32_t iblock_no, char *iblock_buf){
    return 0;
}
int icache_query_iblock(ICACHE_CTRL *icache_ctrl, uint64_t iblock_no, char *iblock_buf){
    return 0;
}
gboolean  icache_iblock_exist(ICACHE_CTRL *icache_ctrl, uint64_t iblock_no){
    return 0;
}
int icache_destroy(ICACHE_CTRL *icache_ctrl){
    return 0;
}