#include "installd.h"

int initialize_globals() {
    // Get the android data directory.
    if (get_path_from_env(&android_data_dir, "ANDROID_DATA") < 0) {
        return -1;
    }

    // Get the android app directory.
    if (copy_and_append(&android_app_dir, &android_data_dir, APP_SUBDIR) < 0) {
        return -1;
    }

    // Get the android protected app directory.
    if (copy_and_append(&android_app_private_dir, &android_data_dir, PRIVATE_APP_SUBDIR) < 0) {
        return -1;
    }

    // Get the android app native library directory.
    if (copy_and_append(&android_app_lib_dir, &android_data_dir, APP_LIB_SUBDIR) < 0) {
        return -1;
    }

    // Get the sd-card ASEC mount point.
    if (get_path_from_env(&android_asec_dir, "ASEC_MOUNTPOINT") < 0) {
        return -1;
    }

    // Get the android media directory.
    if (copy_and_append(&android_media_dir, &android_data_dir, MEDIA_SUBDIR) < 0) {
        return -1;
    }

    // Get the android external app directory.
    if (get_path_from_string(&android_mnt_expand_dir, "/mnt/expand/") < 0) {
        return -1;
    }

    // Take note of the system and vendor directories.
    android_system_dirs.count = 4;

    android_system_dirs.dirs = (dir_rec_t*) calloc(android_system_dirs.count, sizeof(dir_rec_t));
    if (android_system_dirs.dirs == NULL) {
        ALOGE("Couldn't allocate array for dirs; aborting\n");
        return -1;
    }

    dir_rec_t android_root_dir;
    if (get_path_from_env(&android_root_dir, "ANDROID_ROOT") < 0) {
        ALOGE("Missing ANDROID_ROOT; aborting\n");
        return -1;
    }

    android_system_dirs.dirs[0].path = build_string2(android_root_dir.path, APP_SUBDIR);
    android_system_dirs.dirs[0].len = strlen(android_system_dirs.dirs[0].path);

    android_system_dirs.dirs[1].path = build_string2(android_root_dir.path, PRIV_APP_SUBDIR);
    android_system_dirs.dirs[1].len = strlen(android_system_dirs.dirs[1].path);

    android_system_dirs.dirs[2].path = strdup("/vendor/app/");
    android_system_dirs.dirs[2].len = strlen(android_system_dirs.dirs[2].path);

    android_system_dirs.dirs[3].path = strdup("/oem/app/");
    android_system_dirs.dirs[3].len = strlen(android_system_dirs.dirs[3].path);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 11) {
        fprintf(stderr, "argument < 11");
        return 1;
    }

    if (initialize_globals() < 0) {
        fprintf(stderr, "Could not initialize globals; exiting.\n");
        return 1;
    }

    argv++;

    /* apk_path, uid, is_public, pkgname, instruction_set,
     * dexopt_needed, vm_safe_mode, debuggable, oat_dir, boot_complete */
    // dexopt /data/app/com.tencent.mm-1/base.apk 50125 1 com.tencent.mm arm 1 0 0 /data/app/com.tencent.mm-1/oat 0
    return dexopt(argv[0], atoi(argv[1]), atoi(argv[2]),
                  argv[3], argv[4], atoi(argv[5]),
                  atoi(argv[6]), atoi(argv[7]), argv[8], atoi(argv[9]));
}
