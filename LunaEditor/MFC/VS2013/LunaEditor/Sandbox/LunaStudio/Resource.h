LOCAL_PATH := $(call my-dir)/../../../../../../..
PVRSDKDIR := $(realpath $(LOCAL_PATH))

# Module OGLES2BinaryShader
include $(CLEAR_VARS)

LOCAL_MODULE    := OGLES2BinaryShader

### Add all source file names to be included in lib separated by a whitespace
LOCAL_SRC_FILES  := Examples/Advanced/BinaryShader/OGLES2/OGLES2BinaryShader.cpp \
                    Shell/PVRShell.cpp \
                    Shell/API/KEGL/PVRShellAPI.cpp \
                    Shell/OS/Android/PVRShellOS.cpp

LOCAL_C_INCLUDES := $(PVRSDKDIR)/Shell \
                    $(PVRSDKDIR)/Shell/API/KEGL \
                    $(PVRSDKDIR)/Shell/OS/Android \
                    $(PVRSDKDIR)/Builds/Include

LOCAL_CFLAGS := -DBUILD_OGLES2

LOCAL_LDLIBS := -llog \
              