#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

#ifdef STEAM_HAS_MTDUTILS
int steam_flash_image_main(int argc, char** argv);
int steam_dump_image_main(int argc, char** argv);
int steam_erase_image_main(int argc, char** argv);
#endif

#ifdef STEAM_HAS_YAFFS2
int steam_mkyaffs2image_main(int argc, char** argv);
int steam_unyaffs_main(int argc, char** argv);
#endif

#ifdef STEAM_HAS_AMEND
int steam_amend_main(int argc, char** argv);
#endif

#ifdef STEAM_HAS_RECOVERY
int steam_nandroid_main(int argc, char** argv);
int steam_reboot_main(int argc, char** argv);
int steam_setprop_main(int argc, char** argv);
int steam_graphsh_main(int argc, char** argv);
int steam_graphchoice_main(int argc, char** argv);
int steam_truncate_main(int argc,char** argv);
int steam_recovery_main(int argc,char** argv);
int steam_init_main(int argc,char** argv);
int steam_earlyinit_main(int argc,char** argv);
int steam_postinit_main(int argc,char** argv);
#endif

#ifdef STEAM_HAS_JFSUTILS
int steam_mkfs_jfs_main(int argc,char** argv);
int steam_fsck_jfs_main(int argc,char** argv);
#endif

#ifdef STEAM_HAS_E2FSPROGS
int steam_mke2fs_main(int argc,char** argv);
int steam_e2fsck_main(int argc,char** argv);
int steam_tune2fs_main(int argc,char** argv);
#endif

#ifdef STEAM_HAS_DEVICEMAPPER
int steam_dmsetup_main(int argc,char** argv);
#endif

#ifdef STEAM_HAS_CRYPTSETUP
int steam_cryptsetup_main(int argc,char** argv);
#endif

#ifdef STEAM_HAS_ADBD
int steam_adbd_main(int argc,char** argv);
#endif

#ifdef STEAM_HAS_BUSYBOX
int steam_busybox_main(int argc, char** argv);
#endif

int call_busybox(char* command, ...);
int call_flash_image(char* command, ...);
int call_dump_image(char* command, ...);
int call_erase_image(char* command, ...);
int call_mkyaffs2image(char* command, ...);
int call_unyaffs(char* command, ...);
int call_amend(char* command, ...);
int call_nandroid(char* command, ...);
int call_reboot(char* command, ...);
int call_setprop(char* command, ...);
int call_graphsh(char* command, ...);
int call_graphchoice(char* command, ...);
int call_truncate(char* command, ...);
int call_lagfixer(char* command, ...);
int call_recovery(char* command, ...);
int call_init(char* command, ...);
int call_earlyinit(char* command, ...);
int call_postinit(char* command, ...);
int call_mkfs_jfs(char* command, ...);
int call_fsck_jfs(char* command, ...);
int call_mke2fs(char* command, ...);
int call_mkfs_ext2(char* command, ...);
int call_mkfs_ext3(char* command, ...);
int call_mkfs_ext4(char* command, ...);
int call_e2fsck(char* command, ...);
int call_fsck_ext2(char* command, ...);
int call_fsck_ext3(char* command, ...);
int call_fsck_ext4(char* command, ...);
int call_tune2fs(char* command, ...);
int call_dmsetup(char* command, ...);
int call_cryptsetup(char* command, ...);
int call_adbd(char* command, ...);

extern char* steam_command_list[];
