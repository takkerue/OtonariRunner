#ifndef SW_BUTTON_CONTROLLER_H_
#define SW_BUTTON_CONTROLLER_H_

typedef enum {
	StartButton = 0,
	ResetButton,
	UpButton,
	DownButton,
	LeftButton,
	RightButton,
	NumOfButton
} StopWatchButton;

void SW_Button_init();
void SW_Button_update();
bool SW_Button_isPressed(StopWatchButton id);
bool SW_Button_isChanged(StopWatchButton id);
void SW_Button_setOnChangedListener(void (*listener)(StopWatchButton));

#endif
