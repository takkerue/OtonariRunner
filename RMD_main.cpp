#include "ev3api.h"
#include "app.h"

#include "Motor.h"

#include "RMD_main.h"
#include "SW_ButtonController.h"

using namespace ev3api;

// 内部関数プロトタイプ宣言

static Motor *leftMotor;
static Motor *rightMotor;

typedef enum {
	Idle,
	Running
} OtonariState;

typedef enum {
	Run01Go,
	Run02Stop,
	Run03Back
} RunningState;

static OtonariState otonariState = Idle;
static RunningState runningState = Run01Go;

static int targetCount;
static int currentCount;
static unsigned long targetTime;
static unsigned long currentTime;

void RMD_init(void)
{
	leftMotor = new Motor(PORT_A);
	rightMotor = new Motor(PORT_B);
	otonariState = Idle;
	runningState = Run01Go;
	targetCount = 0;
	currentCount = 0;
	targetTime = 0;
	currentTime = 0;
}

static void onIdle() {
	leftMotor->setPWM(0);
	rightMotor->setPWM(0);
	return;
}

static void onRunning() {
	switch (runningState) {
		case Run01Go:
			// 50cm前進
			leftMotor->setPWM(40);
			rightMotor->setPWM(40);
			if (currentCount > targetCount) {
				runningState = Run02Stop;
				targetTime = currentTime + 8500;
			}
			break;
		case Run02Stop:
			// 10秒間停止
			leftMotor->setPWM(0);
			rightMotor->setPWM(0);
			if (currentTime > targetTime) {
				runningState = Run03Back;
				targetCount = currentCount - 1040;
			}
			break;
		case Run03Back:
			// 50cmバック
			leftMotor->setPWM(-40);
			rightMotor->setPWM(-40);
			if (currentCount < targetCount) {
				runningState = Run01Go;
				otonariState = Idle;
				ev3_speaker_stop();
			}
			break;
		default:
			runningState = Run01Go;
			break;
	}
	return;
}

void RMD_main(void)
{
	memfile_t soundFile = { .buffer = NULL };

	RMD_init();
	ev3_sensor_config(EV3_PORT_1, TOUCH_SENSOR);
	SW_Button_init();
	ev3_speaker_set_volume(50);

	while(1) {
		SW_Button_update();
		currentTime += 10;
		currentCount = (rightMotor->getCount() + leftMotor->getCount()) / 2;
		// otonari state transition
		switch (otonariState) {
			case Idle:
				// on StartButton Pressed;
				if (SW_Button_isChanged(StartButton) && SW_Button_isPressed(StartButton)) {
					otonariState = Running;

					// on RunningStete enterd
					runningState = Run01Go;
					targetCount = currentCount + 1040;

					ev3_speaker_set_volume(15);
					if (soundFile.buffer != NULL) {
						ev3_memfile_free(&soundFile);
					}
					ev3_memfile_load("/ev3rt/res/500Hz_sin_2sec.wav", &soundFile);
					ev3_speaker_play_file(&soundFile, SOUND_MANUAL_STOP);

				}
				break;
			case Running:
				// on StartButton Pressed;
				if (SW_Button_isChanged(StartButton) && SW_Button_isPressed(StartButton)) {
					otonariState = Idle;
					ev3_speaker_stop();
				}
				break;
			default:
				otonariState = Idle;
			break;
		}

		switch (otonariState) {
			case Idle:
				onIdle();
				break;
			case Running:
				onRunning();
				break;
			default:
				break;
		};

		{
			char text[100];
			ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
			ev3_lcd_set_font(EV3_FONT_MEDIUM);
			sprintf(text, "PUSH RIGHT 800Hz");
			ev3_lcd_draw_string(text, 0, 0);
			sprintf(text, "PUSH LEFT 500Hz");
			ev3_lcd_draw_string(text, 0, 20);
			if (otonariState == Running) {
				sprintf(text, "RUNNING");
			} else {
				sprintf(text, "IDLE");
			}
			ev3_lcd_draw_string(text, 0, 50);
		}

		tslp_tsk(10);
	}
}
