#include "ev3api.h"

#include "SW_ButtonController.h"

typedef struct {
	unsigned char isPressed;
	unsigned char wasPressed;
} ButtonState;

static ButtonState button[NumOfButton];

static bool buttonIsPressed(StopWatchButton id) {
	bool pressed = false;
	switch (id) {
		case StartButton:
		pressed = ev3_touch_sensor_is_pressed(EV3_PORT_1);
		break;
		case ResetButton:
		pressed = ev3_button_is_pressed(LEFT_BUTTON);
		break;
		case UpButton:
		pressed = ev3_button_is_pressed(UP_BUTTON);
		break;
		case DownButton:
		pressed = ev3_button_is_pressed(DOWN_BUTTON);
		break;
		case LeftButton:
		pressed = ev3_button_is_pressed(LEFT_BUTTON);
		break;
		case RightButton:
		pressed = ev3_button_is_pressed(RIGHT_BUTTON);
		break;
		default:
		break;
	}
	return pressed;
}

void SW_Button_init()
{
	StopWatchButton id = StartButton;
	for (id = StartButton; id < NumOfButton; id = static_cast<StopWatchButton>(id + 1)) {
		button[id].isPressed = buttonIsPressed(id);
		button[id].wasPressed = button[id].isPressed;
	}
    return;
}

void SW_Button_update()
{
	StopWatchButton id = StartButton;
	for (id = StartButton; id < NumOfButton; id = static_cast<StopWatchButton>(id + 1)) {
		button[id].wasPressed = button[id].isPressed;
		button[id].isPressed = buttonIsPressed(id);
	}
    return;
}

bool SW_Button_isPressed(StopWatchButton id)
{
        if (id >= NumOfButton) {
                return false;
        }
        return button[id].isPressed;
}

bool SW_Button_isChanged(StopWatchButton id)
{
        if (id >= NumOfButton) {
                return false;
        }
        return (button[id].isPressed != button[id].wasPressed);
}

void SW_Button_setOnChangedListener(void (*listener)(StopWatchButton))
{
    return;
}
