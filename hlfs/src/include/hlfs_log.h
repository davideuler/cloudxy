/*
 *  Copyright (C) 2012 Harry Wei <harryxiyou@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published by
 *  the Free Software Foundation.
 */

#ifndef _HLFS_LOG_H_
#define _HLFS_LOG_H_

#include "log4c.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "glib.h"

//static GStaticMutex __hlfs_log_mutex__ = G_STATIC_MUTEX_INIT;
extern GStaticMutex __hlfs_log_mutex__;
#define LOG_LEN				2048U
static char __msg_log[LOG_LEN] = {0};
static log4c_category_t *__mycat = NULL;
static char *__hlog_path = NULL;
static char __log4cfile[128] = {0};
static int __is_init_log_path = 0;

#define HLOG_NOTICE(msg, args...) { 															\
	if (0 == __is_init_log_path) {																\
		__hlog_path = g_get_current_dir();														\
		setenv("LOG4C_RCPATH", __hlog_path, 1);													\
		sprintf(__log4cfile, "%s/%s", __hlog_path, "log4crc");									\
		g_free(__hlog_path);																	\
		if (g_file_test(__log4cfile, G_FILE_TEST_EXISTS)){										\
			__mycat = log4c_category_get("hlfslog");								    	    \
		}																						\
		__is_init_log_path = 1;																	\
	}																							\
	if (NULL != __mycat) {																		\
		g_static_mutex_lock (&__hlfs_log_mutex__);                                                         \
		memset(__msg_log, 0, LOG_LEN);															\
		snprintf(__msg_log, LOG_LEN, "[%p][%s][%s][%d]%s", g_thread_self(),__FILE__, __func__, __LINE__, msg);		\
		const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
		log4c_category_log_locinfo(__mycat, &locinfo, LOG4C_PRIORITY_NOTICE, __msg_log, ##args);	\
		g_static_mutex_unlock (&__hlfs_log_mutex__); 														\
	}else {																						\
		printf(msg, ##args);																	\
		printf("\n");																			\
	}																							\
}

#define HLOG_TRACE(msg, args...) { 																\
	if (0 == __is_init_log_path) {															\
		__hlog_path = g_get_current_dir();												\
		setenv("LOG4C_RCPATH", __hlog_path, 1);											\
		sprintf(__log4cfile, "%s/%s", __hlog_path, "log4crc");							\
		g_free(__hlog_path);															\
		if(g_file_test(__log4cfile, G_FILE_TEST_EXISTS)){								\
			__mycat = log4c_category_get("hlfslog");								    \
		}																				\
		__is_init_log_path = 1;															\
	}																					\
	if (NULL != __mycat) {																		\
		g_static_mutex_lock (&__hlfs_log_mutex__);                                                         \
		memset(__msg_log, 0, LOG_LEN);															\
		snprintf(__msg_log, LOG_LEN, "[%p][%s][%s][%d]%s", g_thread_self(),__FILE__, __func__, __LINE__, msg);		\
		const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
		log4c_category_log_locinfo(__mycat, &locinfo, LOG4C_PRIORITY_TRACE, __msg_log, ##args);		\
		g_static_mutex_unlock (&__hlfs_log_mutex__);                                                       \
	} else {																					\
		printf(msg, ##args);																	\
		printf("\n");																			\
	}																							\
}

#define HLOG_FATAL(msg, args...) { 																\
	if (0 == __is_init_log_path) {															\
		__hlog_path = g_get_current_dir();												\
		setenv("LOG4C_RCPATH", __hlog_path, 1);											\
		sprintf(__log4cfile, "%s/%s", __hlog_path, "log4crc");							\
		g_free(__hlog_path);															\
		if(g_file_test(__log4cfile, G_FILE_TEST_EXISTS)){								\
			__mycat = log4c_category_get("hlfslog");								    \
		}																				\
		__is_init_log_path = 1;															\
	}																					\
	if (NULL != __mycat) {																		\
		g_static_mutex_lock (&__hlfs_log_mutex__);                                                         \
		memset(__msg_log, 0, LOG_LEN);															\
		snprintf(__msg_log, LOG_LEN, "[%p][%s][%s][%d]%s", g_thread_self(),__FILE__, __func__, __LINE__, msg);		\
		const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
		log4c_category_log_locinfo(__mycat, &locinfo, LOG4C_PRIORITY_FATAL, __msg_log, ##args);		\
		g_static_mutex_unlock (&__hlfs_log_mutex__);                                                       \
	} else {																					\
		printf(msg, ##args);																	\
		printf("\n");																			\
	}																							\
}

#define HLOG_DEBUG(msg, args...) { 																\
	if (0 == __is_init_log_path) {																\
		__hlog_path = g_get_current_dir();														\
		setenv("LOG4C_RCPATH", __hlog_path, 1);													\
		sprintf(__log4cfile, "%s/%s", __hlog_path, "log4crc");									\
		g_free(__hlog_path);																	\
		if(g_file_test(__log4cfile, G_FILE_TEST_EXISTS)){										\
			__mycat = log4c_category_get("hlfslog");								    	    \
		}																						\
		__is_init_log_path = 1;																	\
	}																							\
	if (NULL != __mycat) {                                                         \
		g_static_mutex_lock (&__hlfs_log_mutex__);                                                   \
		memset(__msg_log, 0, LOG_LEN);															\
		snprintf(__msg_log, LOG_LEN, "[%p][%s][%s][%d]%s", g_thread_self(),__FILE__, __func__, __LINE__, msg);		\
		const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
		log4c_category_log_locinfo(__mycat, &locinfo, LOG4C_PRIORITY_DEBUG, __msg_log, ##args);		\
		g_static_mutex_unlock (&__hlfs_log_mutex__);                                                           \
	} else {																					\
		printf(msg, ##args);																	\
		printf("\n");																			\
	}																							\
}

#define HLOG_INFO(msg, args...) { 																\
	if (0 == __is_init_log_path) {																\
		__hlog_path = g_get_current_dir();														\
		setenv("LOG4C_RCPATH", __hlog_path, 1);													\
		sprintf(__log4cfile, "%s/%s", __hlog_path, "log4crc");									\
		g_free(__hlog_path);																	\
		if(g_file_test(__log4cfile, G_FILE_TEST_EXISTS)){										\
			__mycat = log4c_category_get("hlfslog");								    	    \
		}																						\
		__is_init_log_path = 1;																	\
	}																							\
	if (NULL != __mycat) {																					\
		g_static_mutex_lock (&__hlfs_log_mutex__);                                                           \
		memset(__msg_log, 0, LOG_LEN);															\
		snprintf(__msg_log, LOG_LEN, "[%p][%s][%s][%d]%s", g_thread_self(),__FILE__, __func__, __LINE__, msg);		\
		const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
		log4c_category_log_locinfo(__mycat, &locinfo, LOG4C_PRIORITY_INFO, __msg_log, ##args);		\
		g_static_mutex_unlock (&__hlfs_log_mutex__);                                                           \
	} else {																					\
		printf(msg, ##args);																	\
		printf("\n");																			\
	}																							\
}

#define HLOG_ERROR(msg, args...) { 																\
	if (0 == __is_init_log_path) {																\
		__hlog_path = g_get_current_dir();														\
		setenv("LOG4C_RCPATH", __hlog_path, 1);													\
		sprintf(__log4cfile, "%s/%s", __hlog_path, "log4crc");									\
		g_free(__hlog_path);																	\
		if(g_file_test(__log4cfile, G_FILE_TEST_EXISTS)){										\
			__mycat = log4c_category_get("hlfslog");								    	    \
		}																						\
		__is_init_log_path = 1;																	\
	}																							\
	if (NULL != __mycat) {																		\
		g_static_mutex_lock (&__hlfs_log_mutex__);                                                         \
		memset(__msg_log, 0, LOG_LEN);															\
		snprintf(__msg_log, LOG_LEN, "[%p][%s][%s][%d]%s", g_thread_self(),__FILE__, __func__, __LINE__, msg);		\
		const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
		log4c_category_log_locinfo(__mycat,&locinfo, LOG4C_PRIORITY_ERROR, __msg_log, ##args);		\
		g_static_mutex_unlock (&__hlfs_log_mutex__);                                                       \
	} else {																					\
		printf(msg, ##args);																	\
		printf("\n");																			\
	}																							\
}

#define HLOG_WARN(msg, args...) { 																\
	if (0 == __is_init_log_path) {																\
		__hlog_path = g_get_current_dir();												\
		setenv("LOG4C_RCPATH", __hlog_path, 1);											\
		sprintf(__log4cfile, "%s/%s", __hlog_path, "log4crc");							\
		g_free(__hlog_path);															\
		if(g_file_test(__log4cfile, G_FILE_TEST_EXISTS)){								\
			__mycat = log4c_category_get("hlfslog");								    \
		}																				\
		__is_init_log_path = 1;															\
	}																							\
	if (NULL != __mycat) {																		\
		g_static_mutex_lock (&__hlfs_log_mutex__);                                                         \
		memset(__msg_log, 0, LOG_LEN);															\
		snprintf(__msg_log, LOG_LEN, "[%p][%s][%s][%d]%s", g_thread_self(),__FILE__, __func__, __LINE__, msg);	\
		const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
		log4c_category_log_locinfo(__mycat, &locinfo, LOG4C_PRIORITY_WARN, __msg_log, ##args);		\
		g_static_mutex_unlock (&__hlfs_log_mutex__);                                                       \
	} else {																					\
		printf(msg, ##args);																	\
		printf("\n");																			\
	}																							\
}
#endif
