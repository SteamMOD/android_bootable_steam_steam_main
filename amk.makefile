# link this file to the base steam directory as Android.mk

ifneq ($(TARGET_SIMULATOR),true)
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

STEAM_VERSION := Steam Recovery v2.9.9.0
STEAM_FUNCTIONS := -DSTEAM_HAS_MTDUTILS \
									 -DSTEAM_HAS_YAFFS2 \
									 -DSTEAM_HAS_AMEND \
									 -DSTEAM_HAS_RECOVERY \
									 -DSTEAM_HAS_JFSUTILS \
									 -DSTEAM_HAS_E2FSPROGS \
									 -DSTEAM_HAS_DEVICEMAPPER \
									 -DSTEAM_HAS_CRYPTSETUP \
									 -DSTEAM_HAS_ADBD \
									 -DSTEAM_HAS_BUSYBOX

LOCAL_CFLAGS := -Os -DSTEAM_VERSION="$(STEAM_VERSION)" $(STEAM_FUNCTIONS)
commands_steam_local_path := $(LOCAL_PATH)

LOCAL_SRC_FILES := steam_main/steam.c
LOCAL_MODULE := steam
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_MODULE_TAGS := eng

ifneq (,$(findstring BUSYBOX,$(STEAM_FUNCTIONS)))
LOCAL_STATIC_LIBRARIES += libsteam_busybox \
													libsteam_clearsilverregex
endif
ifneq (,$(findstring YAFFS2,$(STEAM_FUNCTIONS)))
LOCAL_STATIC_LIBRARIES += libsteam_mkyaffs2image \
													libsteam_unyaffs
endif
ifneq (,$(findstring MTDUTILS,$(STEAM_FUNCTIONS)))
LOCAL_STATIC_LIBRARIES +=	libsteam_erase_image \
													libsteam_dump_image \
													libsteam_flash_image \
													libsteam_mtdutils
endif
ifneq (,$(findstring RECOVERY,$(STEAM_FUNCTIONS)))
LOCAL_STATIC_LIBRARIES += libsteam_recovery
endif
ifneq (,$(findstring AMEND,$(STEAM_FUNCTIONS)))
LOCAL_STATIC_LIBRARIES +=	libsteam_amend
endif
ifneq (,$(findstring JFSUTILS,$(STEAM_FUNCTIONS)))
LOCAL_STATIC_LIBRARIES +=	libsteam_mkfs_jfs \
													libsteam_fsck_jfs \
													libsteam_fs \
													libsteam_fs_uuid
endif
ifneq (,$(findstring E2FSPROGS,$(STEAM_FUNCTIONS)))
LOCAL_STATIC_LIBRARIES +=	libsteam_mke2fs \
													libsteam_e2fsck \
													libsteam_tune2fs \
													libsteam_resize2fs \
													libsteam_ext2fs \
													libsteam_ext2_blkid \
													libsteam_ext2_uuid \
													libsteam_ext2_profile \
													libsteam_ext2_com_err \
													libsteam_ext2_e2p
endif
ifneq (,$(findstring CRYPTSETUP,$(STEAM_FUNCTIONS)))
LOCAL_STATIC_LIBRARIES += libsteam_cryptsetup_main \
													libsteam_cryptsetup
endif
ifneq (,$(findstring DEVICEMAPPER,$(STEAM_FUNCTIONS)))
LOCAL_STATIC_LIBRARIES +=	libsteam_dmsetup \
													libsteam_devmapper
endif
ifneq (,$(findstring ADBD,$(STEAM_FUNCTIONS)))
LOCAL_STATIC_LIBRARIES +=	libsteam_adbd
endif
LOCAL_STATIC_LIBRARIES += libsteam_minzip \
													libunz \
													libsteam_mtdutils \
													libsteam_mmcutils \
													libsteam_luks \
													libsteam_popt \
													libsteam_crypto \
													libmincrypt
LOCAL_STATIC_LIBRARIES += libsteam_minui \
													libpixelflinger_static \
													libpng \
													libcutils
LOCAL_STATIC_LIBRARIES += libstdc++ \
													libc

include $(BUILD_EXECUTABLE)

include $(call all-subdir-makefiles)
include $(commands_steam_local_path)/recovery/Android.mk
include $(commands_steam_local_path)/busybox/Android.mk
include $(commands_steam_local_path)/yaffs2/Android.mk
include $(commands_steam_local_path)/amend/Android.mk
include $(commands_steam_local_path)/applypatch/Android.mk
include $(commands_steam_local_path)/mtdutils/Android.mk
include $(commands_steam_local_path)/minzip/Android.mk
include $(commands_steam_local_path)/minui/Android.mk
include $(commands_steam_local_path)/mmcutils/Android.mk
include $(commands_steam_local_path)/jfsutils/Android.mk
include $(commands_steam_local_path)/e2fsprogs/Android.mk
include $(commands_steam_local_path)/device-mapper/Android.mk
include $(commands_steam_local_path)/cryptsetup/Android.mk
include $(commands_steam_local_path)/adb/Android.mk
commands_steam_local_path :=
endif
