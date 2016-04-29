LOCAL_PATH := $(call my-dir)

common_cflags := -Wall -Werror

include $(CLEAR_VARS)
LOCAL_MODULE := dexopt
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := $(common_cflags)
LOCAL_SRC_FILES := dexopt.cpp
LOCAL_C_INCLUDES := frameworks/native/cmds/installd
LOCAL_STATIC_LIBRARIES := libinstalld
LOCAL_SHARED_LIBRARIES := \
    libbase \
    libcutils \
    liblog \
    liblogwrap
LOCAL_CLANG := true
include $(BUILD_EXECUTABLE)
