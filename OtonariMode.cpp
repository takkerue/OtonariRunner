#include "OtonariMode.h"

static OtonariState otonariState = Idle;
static RunningState runningState = Run01Go;

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
				runningState = Run04Complete;
				otonariState = Idle;
				ev3_speaker_stop();
			}
		case Run04Complete:
			leftMotor->setPWM(0);
			rightMotor->setPWM(0);
			break;
		default:
			runningState = Run01Go;
			break;
	}

void transitOtonariState() {
	OtonariState nextState = otonariState;
	switch (otonariState) {
		case Idle:
			// on StartButton Pressed;
			if (SW_Button_isChanged(StartButton) && SW_Button_isPressed(StartButton)) {
				nextState = Running;
			}
			break;
		case Running:
			// on StartButton Pressed;
			if (SW_Button_isChanged(StartButton) && SW_Button_isPressed(StartButton)) {
				nextState = Idle;
			}
			// on RunningFinished
			break;
		default:
			nextState = Idle;
			break;
	}

	if (nextState != otonariState) {
		exitOtonariState(otonariState);
		entryOtonariState(nextState);
		otonariState = nextState;
	}
}

static entryOtonariState(OtonariState state)
{
	switch (state) {
		case Idle:
			break;
		case Running:
			entryRunningState(Run01Go);
			runningState = Run01Go;

			targetCount = currentCount + 1040;
			ev3_speaker_set_volume(15);
			if (soundFile.buffer != NULL) {
				ev3_memfile_free(&soundFile);
			}
			ev3_memfile_load("/ev3rt/res/500Hz_sin_2sec.wav", &soundFile);
			ev3_speaker_play_file(&soundFile, SOUND_MANUAL_STOP);
			break;
		default:
			break;
	}
}

static exitOtonariState(OtonariState state)
{
	switch (state) {
		case Idle:
			break;
		case Running:
			ev3_speaker_stop();
			break;
		default:
			break;
	}
}


static transitRunningState()
{
	RunningState nextState = runningState;
	switch (runningState) {
		case Run01Go:
			if (currentCount > targetCount) {
				nextState = Run02Stop;
			}
			break;
		case Run02Stop:
			if (currentTime > targetTime) {
				nextState = Run03Back;
			}
			break;
		case Run03Back:
			if (currentCount < targetCount) {
				nextState = Run01Go;
				otonariState = Idle;	//TODO
			}
			break;
		default:
			break;
	}
	return;
}


break;
case Run02Stop:
// 10秒間停止
leftMotor->setPWM(0);
rightMotor->setPWM(0);

break;
case Run03Back:
// 50cmバック
leftMotor->setPWM(-40);
rightMotor->setPWM(-40);





static entryRunningState(RunningState state)
{
	switch (runningState) {
		case Run01Go:
			break;
		case Run02Stop:
			break;
		case Run03Back:
			break;
		default:
			break;
	}
	return;
}

static exitRunningState(RunningState state)
{
	switch (runningState) {
		case Run01Go:
			break;
		case Run02Stop:
			break;
		case Run03Back:
			break;
		default:
			break;
	}
	return;
}

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
