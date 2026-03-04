// to open file
int open(const char *name, int mode);
// int open(const char *name, int mode, int perms);
// returns descriptor number
// if fails returns -1
// ALWAYS CHECK RETURN DATA

// params for mode:
// O_RDONLY - only read
// O_WRONLY - only write
// O_RDWR - read and write
// also, there are modificators which can be added via OR operation
// O_APPEND
// O_CREAT
// O_TRUNC
// and other (look for p.104 in Stolyrov ch.2 v2.91)
// --------------------------------
// perms param set if mode is O_CREAT
// for all rights set 0777
//
int read(int fd, void *mem, int len);
int write(int fd, const void *data, int len);
