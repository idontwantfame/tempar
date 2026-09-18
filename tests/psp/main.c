#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspthreadman.h>

PSP_MODULE_INFO("TempAR Test App", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

/*
 * Keep these values in writable user memory.  Their addresses are printed at
 * run time because EBOOT load addresses can differ between PSP environments.
 */
static volatile unsigned char test_byte;
static volatile unsigned short test_short;
static volatile unsigned int test_word;
static volatile unsigned int test_pointer_target;
static volatile unsigned int test_pointer_one;
static volatile unsigned int test_pointer_two;
static volatile unsigned int test_sequence[4];

static int running = 1;

static int exit_callback(int arg1, int arg2, void *common) {
	(void)arg1;
	(void)arg2;
	(void)common;
	running = 0;
	sceKernelExitGame();
	return 0;
}

static int callback_thread(SceSize args, void *argp) {
	int callback_id;

	(void)args;
	(void)argp;
	callback_id = sceKernelCreateCallback("Exit Callback", exit_callback, 0);
	sceKernelRegisterExitCallback(callback_id);
	sceKernelSleepThreadCB();
	return 0;
}

static void setup_callbacks(void) {
	int thread_id;

	thread_id = sceKernelCreateThread("Callback Thread", callback_thread, 0x11, 0xFA0, 0, 0);
	if(thread_id >= 0) {
		sceKernelStartThread(thread_id, 0, 0);
	}
}

static void reset_values(void) {
	test_byte = 0x11;
	test_short = 0x2222;
	test_word = 0x33333333;
	test_pointer_target = 0x44444444;
	test_pointer_one = (unsigned int)&test_pointer_target;
	test_pointer_two = (unsigned int)&test_pointer_one;
	test_sequence[0] = 0x01010101;
	test_sequence[1] = 0x02020202;
	test_sequence[2] = 0x03030303;
	test_sequence[3] = 0x04040404;
}

static void draw_screen(void) {
	pspDebugScreenSetXY(0, 0);
	pspDebugScreenPrintf("TempAR test application\n\n");
	pspDebugScreenPrintf("R+HOME: open TempAR     CROSS: reset values     HOME: exit\n\n");
	pspDebugScreenPrintf("Direct targets (address : current value)\n");
	pspDebugScreenPrintf("byte     %08X : %02X\n", (unsigned int)&test_byte, test_byte);
	pspDebugScreenPrintf("short    %08X : %04X\n", (unsigned int)&test_short, test_short);
	pspDebugScreenPrintf("word     %08X : %08X\n", (unsigned int)&test_word, test_word);
	pspDebugScreenPrintf("\nCWCheat 0x06 pointer chain\n");
	pspDebugScreenPrintf("slot 1   %08X -> %08X\n", (unsigned int)&test_pointer_one, test_pointer_one);
	pspDebugScreenPrintf("slot 2   %08X -> %08X -> %08X\n", (unsigned int)&test_pointer_two,
			test_pointer_two, test_pointer_one);
	pspDebugScreenPrintf("target   %08X : %08X\n", (unsigned int)&test_pointer_target, test_pointer_target);
	pspDebugScreenPrintf("\nMulti-write target\n");
	pspDebugScreenPrintf("words    %08X : %08X %08X %08X %08X\n", (unsigned int)&test_sequence[0],
			test_sequence[0], test_sequence[1], test_sequence[2], test_sequence[3]);
	pspDebugScreenPrintf("\nUse the displayed addresses when adapting docs/tests/tests.db.\n");
}

int main(int argc, char *argv[]) {
	SceCtrlData pad;
	unsigned int previous_buttons = 0;

	(void)argc;
	(void)argv;
	setup_callbacks();
	pspDebugScreenInit();
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	reset_values();

	while(running) {
		sceCtrlReadBufferPositive(&pad, 1);
		if((pad.Buttons & PSP_CTRL_CROSS) && !(previous_buttons & PSP_CTRL_CROSS)) {
			reset_values();
		}
		previous_buttons = pad.Buttons;
		draw_screen();
		sceKernelDelayThread(100000);
	}

	return 0;
}
