LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp\
		   $(LOCAL_PATH)/../../../Classes/Globals.cpp\
		   $(LOCAL_PATH)/../../../Classes/PauseLayer.cpp\
		   $(LOCAL_PATH)/../../../Classes/Character.cpp\
		   $(LOCAL_PATH)/../../../Classes/Enemy.cpp\
                   $(LOCAL_PATH)/../../../Classes/MainGameScene.cpp\
                   $(LOCAL_PATH)/../../../Classes/HUDInputLayer.cpp\
                   $(LOCAL_PATH)/../../../Classes/GameLayer.cpp\
                   $(LOCAL_PATH)/../../../Classes/Player.cpp\
                   $(LOCAL_PATH)/../../../Classes/Cat.cpp\
                   $(LOCAL_PATH)/../../../Classes/Spike.cpp\
                   $(LOCAL_PATH)/../../../Classes/BeeMinion.cpp\
                   $(LOCAL_PATH)/../../../Classes/TMXLevel.cpp\
                   $(LOCAL_PATH)/../../../Classes/Animator.cpp\
                   $(LOCAL_PATH)/../../../Classes/MainMenu.cpp\
		   $(LOCAL_PATH)/../../../Classes/Walk.cpp\
		   $(LOCAL_PATH)/../../../Classes/Fly.cpp\
		   $(LOCAL_PATH)/../../../Classes/RunState.cpp\
		   $(LOCAL_PATH)/../../../Classes/JumpState.cpp\
		   $(LOCAL_PATH)/../../../Classes/IdleState.cpp\
		   $(LOCAL_PATH)/../../../Classes/DeadState.cpp\
		   $(LOCAL_PATH)/../../../Classes/AttackState.cpp\
		   $(LOCAL_PATH)/../../../Classes/GameOverLayer.cpp\
		   $(LOCAL_PATH)/../../../Classes/Trigger.cpp\
		   $(LOCAL_PATH)/../../../Classes/CutePhsyco.cpp\
		   $(LOCAL_PATH)/../../../Classes/PickUp.cpp\
		   $(LOCAL_PATH)/../../../Classes/Health.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += creator_reader   # add dependence


# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module, ./../../Classes/reader)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
