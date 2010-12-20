#include "steam_main/steam.h"
#include "sys/types.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include <signal.h>
#include <sys/wait.h>

extern char** environ;

char* steam_command_list[] = {
#ifdef STEAM_HAS_AMEND
  "amend",
#endif
#ifdef STEAM_HAS_MTDUTILS
  "dump_image",
  "erase_image",
  "flash_image",
#endif
#ifdef STEAM_HAS_RECOVERY
  "truncate",
  "nandroid",
  "mkyaffs2image",
  "unyaffs",
  "reboot",
  "recovery",
#endif
#ifdef STEAM_HAS_BUSYBOX
  "busybox",
// TODO: use bb's applet_names
  "[",
  "[[",
  "ash",
  "awk",
  "basename",
  "bbconfig",
  "bunzip2",
  "bzcat",
  "bzip2",
  "cal",
  "cat",
  "catv",
  "chgrp",
  "chmod",
  "chown",
  "chroot",
  "cksum",
  "clear",
  "cmp",
  "cp",
  "cpio",
  "cut",
  "date",
  "dc",
  "dd",
  "depmod",
  "devmem",
  "df",
  "diff",
  "dirname",
  "dmesg",
  "dos2unix",
  "du",
  "echo",
  "egrep",
  "env",
  "expr",
  "false",
  "fdisk",
  "fgrep",
  "find",
  "fold",
  "free",
  "freeramdisk",
  "fuser",
  "getopt",
  "grep",
  "gunzip",
  "gzip",
  "head",
  "hexdump",
  "id",
  "insmod",
  "install",
  "kill",
  "killall",
  "killall5",
  "length",
  "less",
  "ln",
  "losetup",
  "ls",
  "lsmod",
  "lspci",
  "lsusb",
  "lzop",
  "lzopcat",
  "md5sum",
  "mkdir",
  "mkfifo",
  "mknod",
  "mkswap",
  "mktemp",
  "modprobe",
  "more",
  "mount",
  "mountpoint",
  "mv",
  "nice",
  "nohup",
  "od",
  "patch",
  "pgrep",
  "pidof",
  "pkill",
  "printenv",
  "printf",
  "ps",
  "pwd",
  "rdev",
  "readlink",
  "realpath",
  "renice",
  "reset",
  "rm",
  "rmdir",
  "rmmod",
  "run-parts",
  "sed",
  "seq",
  "setsid",
  "sh",
  "sha1sum",
  "sha256sum",
  "sha512sum",
  "sleep",
  "sort",
  "split",
  "stat",
  "strings",
  "stty",
  "swapoff",
  "swapon",
  "sync",
  "sysctl",
  "tac",
  "tail",
  "tar",
  "tee",
  "test",
  "time",
  "top",
  "touch",
  "tr",
  "true",
  "tty",
  "umount",
  "uname",
  "uniq",
  "unix2dos",
  "unlzop",
  "unzip",
  "uptime",
  "usleep",
  "uudecode",
  "uuencode",
  "watch",
  "wc",
  "which",
  "whoami",
  "xargs",
  "yes",
  "zcat",
#endif
#ifdef STEAM_HAS_E2FSPROGS
  "e2fsck",
  "fsck.ext2",
  "fsck.ext3",
  "fsck.ext4",
  "mke2fs",
  "mkfs.ext2",
  "mkfs.ext3",
  "mkfs.ext4",
  "tune2fs",
#endif
#ifdef STEAM_HAS_JFSUTILS
  "mkfs.jfs",
  "fsck.jfs",
#endif
#ifdef STEAM_HAS_DEVICEMAPPER
  "dmsetup",
#endif
#ifdef STEAM_HAS_CRYPTSETUP
  "cryptsetup",
#endif
  NULL
};

#define CALL(NAME,ARGC,ARGV) steam_##NAME##_main(ARGC,ARGV)

#ifdef STEAM_HAS_BUSYBOX
#define busybox_CALL _exit(CALL(busybox,argc+1,&command));
#else
#define busybox_CALL execve("/sbin/busybox",&command, environ); _exit(127);
#endif

#ifdef STEAM_HAS_MTDUTILS
#define flash_image_CALL _exit(CALL(flash_image,argc+1,&command));
#define dump_image_CALL _exit(CALL(dump_image,argc+1,&command));
#define erase_image_CALL _exit(CALL(erase_image,argc+1,&command));
#else
#define flash_image_CALL execve("/sbin/flash_image",&command, environ); _exit(127);
#define dump_image_CALL execve("/sbin/dump_image",&command, environ); _exit(127);
#define erase_image_CALL execve("/sbin/erase_image",&command, environ); _exit(127);
#endif

#ifdef STEAM_HAS_YAFFS2
#define mkyaffs2image_CALL _exit(CALL(mkyaffs2image,argc+1,&command));
#define unyaffs_CALL _exit(CALL(unyaffs,argc+1,&command));
#else
#define mkyaffs2image_CALL execve("/sbin/mkyaffs2image",&command, environ); _exit(127);
#define unyaffs_CALL execve("/sbin/unyaffs",&command, environ); _exit(127);
#endif

#ifdef STEAM_HAS_AMEND
#define amend_CALL _exit(CALL(amend,argc+1,&command));
#else
#define amend_CALL execve("/sbin/amend",&command, environ); _exit(127);
#endif

#ifdef STEAM_HAS_RECOVERY
#define nandroid_CALL _exit(CALL(nandroid,argc+1,&command));
#define reboot_CALL _exit(CALL(reboot,argc+1,&command));
#define setprop_CALL _exit(CALL(setprop,argc+1,&command));
#define graphsh_CALL _exit(CALL(graphsh,argc+1,&command));
#define graphchoice_CALL _exit(CALL(graphchoice,argc+1,&command));
#define truncate_CALL _exit(CALL(truncate,argc+1,&command));
#define recovery_CALL _exit(CALL(recovery,argc+1,&command));
#define init_CALL _exit(CALL(init,argc+1,&command));
#define earlyinit_CALL _exit(CALL(earlyinit,argc+1,&command));
#define postinit_CALL _exit(CALL(postinit,argc+1,&command));
#else
#define nandroid_CALL execve("/sbin/nandroid",&command, environ); _exit(127);
#define reboot_CALL execve("/sbin/reboot",&command, environ); _exit(127);
#define setprop_CALL execve("/sbin/setprop",&command, environ); _exit(127);
#define graphsh_CALL execve("/sbin/graphsh",&command, environ); _exit(127);
#define graphchoice_CALL execve("/sbin/graphchoice",&command, environ); _exit(127);
#define truncate_CALL execve("/sbin/truncate",&command, environ); _exit(127);
#define recovery_CALL execve("/sbin/recovery",&command, environ); _exit(127);
#define init_CALL execve("/sbin/init",&command, environ); _exit(127);
#define earlyinit_CALL execve("/sbin/earlyinit",&command, environ); _exit(127);
#define postinit_CALL execve("/sbin/postinit",&command, environ); _exit(127);
#endif

#ifdef STEAM_HAS_JFSUTILS
#define mkfs_jfs_CALL _exit(CALL(mkfs_jfs,argc+1,&command));
#define fsck_jfs_CALL _exit(CALL(fsck_jfs,argc+1,&command));
#else
#define mkfs_jfs_CALL execve("/sbin/mkfs.jfs",&command, environ); _exit(127);
#define fsck_jfs_CALL execve("/sbin/fsck.jfs",&command, environ); _exit(127);
#endif

#ifdef STEAM_HAS_E2FSPROGS
#define mke2fs_CALL _exit(CALL(mke2fs,argc+1,&command));
#define mkfs_ext2_CALL _exit(CALL(mke2fs,argc+1,&command));
#define mkfs_ext3_CALL _exit(CALL(mke2fs,argc+1,&command));
#define mkfs_ext4_CALL _exit(CALL(mke2fs,argc+1,&command));
#define e2fsck_CALL _exit(CALL(e2fsck,argc+1,&command));
#define fsck_ext2_CALL _exit(CALL(e2fsck,argc+1,&command));
#define fsck_ext3_CALL _exit(CALL(e2fsck,argc+1,&command));
#define fsck_ext4_CALL _exit(CALL(e2fsck,argc+1,&command));
#define tune2fs_CALL _exit(CALL(tune2fs,argc+1,&command));
#else
#define mke2fs_CALL execve("/sbin/mke2fs",&command, environ); _exit(127);
#define mkfs_ext2_CALL execve("/sbin/mkfs.ext2",&command, environ); _exit(127);
#define mkfs_ext3_CALL execve("/sbin/mkfs.ext3",&command, environ); _exit(127);
#define mkfs_ext4_CALL execve("/sbin/mkfs.ext4",&command, environ); _exit(127);
#define e2fsck_CALL execve("/sbin/e2fsck",&command, environ); _exit(127);
#define fsck_ext2_CALL execve("/sbin/fsck.ext2",&command, environ); _exit(127);
#define fsck_ext3_CALL execve("/sbin/fsck.ext3",&command, environ); _exit(127);
#define fsck_ext4_CALL execve("/sbin/fsck.ext4",&command, environ); _exit(127);
#define tune2fs_CALL execve("/sbin/tune2fs",&command, environ); _exit(127);
#endif

#ifdef STEAM_HAS_DEVICEMAPPER
#define dmsetup_CALL _exit(CALL(dmsetup,argc+1,&command));
#else
#define dmsetup_CALL execve("/sbin/dmsetup",&command, environ); _exit(127);
#endif

#ifdef STEAM_HAS_CRYPTSETUP
#define cryptsetup_CALL _exit(CALL(cryptsetup,argc+1,&command));
#else
#define cryptsetup_CALL execve("/sbin/cryptsetup",&command, environ); _exit(127);
#endif

#ifdef STEAM_HAS_ADBD
#define adbd_CALL _exit(CALL(adbd,argc+1,&command));
#else
#define adbd_CALL execve("/sbin/adbd",&command, environ); _exit(127);
#endif

#define CREATE_CALL_XX(type) \
  int call_##type(char* command, ...) { \
  va_list vl; \
  int volatile argc = 0; \
  pid_t pid; \
  sig_t intsave, quitsave; \
  sigset_t mask, omask; \
  int pstat; \
  va_start(vl, command); \
  while (va_arg(vl,char*)) { argc++; } \
  va_end(vl); \
  sigemptyset(&mask); \
  sigaddset(&mask, SIGCHLD); \
  sigprocmask(SIG_BLOCK, &mask, &omask); \
  switch( pid = fork()) { \
    case -1: \
      sigprocmask(SIG_SETMASK, &omask, NULL); \
      return(-1); \
    case 0: \
      sigprocmask(SIG_SETMASK, &omask, NULL); \
      type##_CALL \
  } \
  intsave = (sig_t)  bsd_signal(SIGINT, SIG_IGN); \
  quitsave = (sig_t) bsd_signal(SIGQUIT, SIG_IGN); \
  pid = waitpid(pid, (int *)&pstat, 0); \
  sigprocmask(SIG_SETMASK, &omask, NULL); \
  (void)bsd_signal(SIGINT, intsave); \
  (void)bsd_signal(SIGQUIT, quitsave); \
  return (pid == -1 ? -1 : (WIFEXITED(pstat) ? WEXITSTATUS(pstat) : pstat)); \
}

CREATE_CALL_XX(busybox)
CREATE_CALL_XX(flash_image)
CREATE_CALL_XX(dump_image)
CREATE_CALL_XX(erase_image)
CREATE_CALL_XX(mkyaffs2image)
CREATE_CALL_XX(unyaffs)
CREATE_CALL_XX(amend)
CREATE_CALL_XX(nandroid)
CREATE_CALL_XX(reboot)
CREATE_CALL_XX(setprop)
CREATE_CALL_XX(graphsh)
CREATE_CALL_XX(graphchoice)
CREATE_CALL_XX(truncate)
CREATE_CALL_XX(recovery)
CREATE_CALL_XX(init)
CREATE_CALL_XX(earlyinit)
CREATE_CALL_XX(postinit)
CREATE_CALL_XX(mkfs_jfs)
CREATE_CALL_XX(fsck_jfs)
CREATE_CALL_XX(mke2fs)
CREATE_CALL_XX(mkfs_ext2)
CREATE_CALL_XX(mkfs_ext3)
CREATE_CALL_XX(mkfs_ext4)
CREATE_CALL_XX(e2fsck)
CREATE_CALL_XX(fsck_ext2)
CREATE_CALL_XX(fsck_ext3)
CREATE_CALL_XX(fsck_ext4)
CREATE_CALL_XX(tune2fs)
CREATE_CALL_XX(dmsetup)
CREATE_CALL_XX(cryptsetup)
CREATE_CALL_XX(adbd)

static const char* basename(const char *name)
{
  const char *cp = strrchr(name, '/');
  if (cp) return cp + 1;
  return name;
}

int main(int argc, char** argv) {
  if (strcmp(basename(argv[0]), "steam")==0) {
    argc--;
    argv++;
    if (argv[0] == NULL) {
      printf(EXPAND(STEAM_VERSION)" by SztupY\n");
      printf("Missing command name argument\n");
      exit(EXIT_FAILURE);
    }
  }
  char* name = basename(argv[0]);
#ifdef STEAM_HAS_MTDUTILS
  if (strcmp(name, "flash_image")==0)   return steam_flash_image_main(argc, argv);
  if (strcmp(name, "dump_image")==0)    return steam_dump_image_main(argc, argv);
  if (strcmp(name, "erase_image")==0)   return steam_erase_image_main(argc, argv);
#endif
#ifdef STEAM_HAS_YAFFS2
  if (strcmp(name, "mkyaffs2image")==0) return steam_mkyaffs2image_main(argc, argv);
  if (strcmp(name, "unyaffs")==0)       return steam_unyaffs_main(argc, argv);
#endif
#ifdef STEAM_HAS_AMEND
  if (strcmp(name, "amend")==0)         return steam_amend_main(argc, argv);
#endif
#ifdef STEAM_HAS_RECOVERY
  if (strcmp(name, "nandroid")==0)      return steam_nandroid_main(argc, argv);
  if (strcmp(name, "reboot")==0)        return steam_reboot_main(argc, argv);
  if (strcmp(name, "setprop")==0)       return steam_setprop_main(argc, argv);
  if (strcmp(name, "graphsh")==0)       return steam_graphsh_main(argc, argv);
  if (strcmp(name, "graphchoice")==0)   return steam_graphchoice_main(argc, argv);
  if (strcmp(name, "truncate")==0)      return steam_truncate_main(argc,argv);
  if (strcmp(name, "recovery")==0)      return steam_recovery_main(argc,argv);
  if (strcmp(name, "earlyinit")==0)     return steam_earlyinit_main(argc,argv);
  if (strcmp(name, "postinit")==0)      return steam_postinit_main(argc,argv);
  if (strcmp(name, "init")==0)          return steam_init_main(argc,argv);
#endif
#ifdef STEAM_HAS_JFSUTILS
  if (strcmp(name, "mkfs.jfs")==0)      return steam_mkfs_jfs_main(argc,argv);
  if (strcmp(name, "fsck.jfs")==0)      return steam_fsck_jfs_main(argc,argv);
#endif
#ifdef STEAM_HAS_E2FSPROGS
  if (strcmp(name, "mke2fs")==0)        return steam_mke2fs_main(argc,argv);
  if (strcmp(name, "mkfs.ext2")==0)     return steam_mke2fs_main(argc,argv);
  if (strcmp(name, "mkfs.ext3")==0)     return steam_mke2fs_main(argc,argv);
  if (strcmp(name, "mkfs.ext4")==0)     return steam_mke2fs_main(argc,argv);
  if (strcmp(name, "e2fsck")==0)        return steam_e2fsck_main(argc,argv);
  if (strcmp(name, "fsck.ext2")==0)     return steam_e2fsck_main(argc,argv);
  if (strcmp(name, "fsck.ext3")==0)     return steam_e2fsck_main(argc,argv);
  if (strcmp(name, "fsck.ext4")==0)     return steam_e2fsck_main(argc,argv);
  if (strcmp(name, "tune2fs")==0)       return steam_tune2fs_main(argc,argv);
#endif
#ifdef STEAM_HAS_DEVICEMAPPER
  if (strcmp(name, "dmsetup")==0)       return steam_dmsetup_main(argc,argv);
#endif
#ifdef STEAM_HAS_CRYPTSETUP
  if (strcmp(name, "cryptsetup")==0)    return steam_cryptsetup_main(argc,argv);
#endif
#ifdef STEAM_HAS_ADBD
  if (strcmp(name, "adbd")==0)          return steam_adbd_main(argc,argv);
#endif
#ifdef STEAM_HAS_BUSYBOX
  return steam_busybox_main(argc, argv);
#else
  printf("%s: Steam applet not found.\n",name);
  return 1;
#endif
}
