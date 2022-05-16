#include <stdio.h>
#include <display.h>
#include <kernel.h>
#include <libdbg.h>
#include <libdbgfont.h>

#define DISPLAY_WIDTH                960
#define DISPLAY_HEIGHT               544
#define DISPLAY_STRIDE_IN_PIXELS     (DISPLAY_WIDTH)

#define SCREEN_FB_SIZE  (2 * 1024 * 1024) // Must be 256KB aligned
static SceDbgFontConfig config;
static void* base;
static SceUInt32 SCE_COLOR_WHITE = 0xffffffff;
static SceUInt32 SCE_COLOR_BLACK = 0xff000000;
static SceUInt32 SCE_COLOR_YELLOW = 0xff00c0ff;
static SceUInt32 SCE_COLOR_GREEN = 0x8000c000;
static SceUInt32 SCE_COLOR_RED = 0xff0000ff;
static SceUInt32 SCE_COLOR_BLUE = 0xffff5000;
static SceUInt32 SCE_COLOR_PURPLE = 0xffff0088;

int psvDebugScreenInit() {
    SceUID displayblock = sceKernelAllocMemBlock("display", SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW, (SCREEN_FB_SIZE), NULL);
    sceKernelGetMemBlockBase(displayblock, (void**)&base);
    SceDisplayFrameBuf frame = {
        sizeof(frame), base, (DISPLAY_STRIDE_IN_PIXELS), SCE_DISPLAY_PIXELFORMAT_A8B8G8R8, (DISPLAY_WIDTH), (DISPLAY_HEIGHT)
    };
    return sceDisplaySetFrameBuf(&frame, SCE_DISPLAY_UPDATETIMING_NEXTVSYNC);
}

void psvDebugScreenPrintf(SceChar8 *uStr, int uHeight, int uWidth, SceUInt32 uColor, int uFont) {
    memset(&config, 0, sizeof(SceDbgFontConfig));
    config.fontSize = uFont;
    sceDbgFontInit(&config);
    sceDbgFontPrint(uWidth, uHeight, uColor, uStr);
    SceDbgFontFrameBufInfo info;
    memset(&info, 0, sizeof(SceDbgFontFrameBufInfo));
    info.frameBufHeight = DISPLAY_HEIGHT;
    info.frameBufWidth = DISPLAY_WIDTH;
    info.frameBufPitch = DISPLAY_STRIDE_IN_PIXELS;
    info.frameBufPixelformat = SCE_DBGFONT_PIXELFORMAT_A8B8G8R8;
    info.frameBufAddr = (SceUChar8 *)base;
    sceDbgFontFlush(&info);
    sceDbgFontExit();
}

void psvDebugScreenClear() {
    memset(base, 0, SCREEN_FB_SIZE);
}

void psvDebugScreenLineClear(int uHeight) {
    SceChar8 clearing[] = "███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████";
    int uWidth = 0;
    while (uWidth <= 960) {
        psvDebugScreenPrintf(clearing, uHeight - 2, uWidth, SCE_COLOR_BLACK, SCE_DBGFONT_FONTSIZE_LARGE);
        psvDebugScreenPrintf(clearing, uHeight + 2, uWidth, SCE_COLOR_BLACK, SCE_DBGFONT_FONTSIZE_LARGE);
        uWidth = uWidth + 5;
    }
}

void psvDebugScreenTextClear(SceChar8 *uStr, int uHeight, int uWidth, int uFont) {
    memset(&config, 0, sizeof(SceDbgFontConfig));
    config.fontSize = uFont;
    sceDbgFontInit(&config);
    sceDbgFontPrint(uWidth, uHeight, SCE_COLOR_BLACK, uStr);
    SceDbgFontFrameBufInfo info;
    memset(&info, 0, sizeof(SceDbgFontFrameBufInfo));
    info.frameBufHeight = DISPLAY_HEIGHT;
    info.frameBufWidth = DISPLAY_WIDTH;
    info.frameBufPitch = DISPLAY_STRIDE_IN_PIXELS;
    info.frameBufPixelformat = SCE_DBGFONT_PIXELFORMAT_A8B8G8R8;
    info.frameBufAddr = (SceUChar8 *)base;
    sceDbgFontFlush(&info);
    sceDbgFontExit();
}