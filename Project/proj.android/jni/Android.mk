LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

FILE_LIST := hellocpp/main.cpp
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../SuperAnim/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../InterfaceLoaders/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../AnimationsLoaders/*.cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../SuperAnim \
$(LOCAL_PATH)/../../InterfaceLoaders \
$(LOCAL_PATH)/../../AnimationsLoaders

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx)

