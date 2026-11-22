#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static bool fs_ready = false;

void fileSystemInit()
{
#ifdef __EMSCRIPTEN__
// Mount IDBFS and flip fs_ready to true (1) once IndexedDB finishes syncing
    EM_ASM({
        FS.mkdir('/saveData');
        FS.mount(IDBFS, {autoPersist: true}, '/saveData');
        FS.syncfs(true, function(err) {
            if (err) {
                console.error('IDBFS load error:', err);
            }
            setValue($0, 1, 'i8');
            console.log("fs ready!");
        });
    }, &fs_ready);
#else
    fs_ready = true;
#endif
}

bool fileSystemReady()
{
    return fs_ready;
}
