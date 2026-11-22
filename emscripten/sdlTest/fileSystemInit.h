#ifdef __EMSCRIPTEN__
#define PATH_SAVE "/saveData/"
#else
#define PATH_SAVE "saveData/"
#endif

void fileSystemInit();
bool fileSystemReady();
