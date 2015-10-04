/**
 * EV3RT baseline
 */
#include "ev3api.h"
#include "app.h"

#include "RMD_main.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/**
 * @brief メインタスク エントリポイント
 * @detail EV3RT OSのMAIN_TASKエントリーポイント
 */
void main_task(intptr_t unused) {
	RMD_main();
}
