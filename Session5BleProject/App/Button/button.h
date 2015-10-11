#ifndef BUTTON_H_
#define BUTTON_H_

#define LONG_PERIOD	2000

/**
 * Button event enumeration
 */
typedef enum  {
    buttonNone = 0,
    buttonPressed,
    buttonPressedReleased,
    buttonReleased,
    buttonLongPressed,
} button_event_t;

void Button_Init(void);
void Button_Process(void);
button_event_t Button_Get_Last_Event(void);

void Button_Button_Pressed_CB(void);
void Button_Button_Released_CB(void);
void Button_Button_Pressed_And_Released_CB(void);
void Button_Button_Long_Pressed_CB(void);

#endif /* BUTTON_H_ */
