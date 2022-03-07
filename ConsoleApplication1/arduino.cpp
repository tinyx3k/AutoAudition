#include <Keyboard.h>
#define KEY_CTRL   0x80
#define KEY_RIGHT_SHIFT    0x85
#define KEY_RIGHT_ALT  0x86
#define KEY_RIGHT_GUI  0x87


#define   KEY_NUMPAD_1 225
#define   KEY_NUMPAD_2 226
#define   KEY_NUMPAD_3 227
#define   KEY_NUMPAD_4 228
#define   KEY_NUMPAD_5 229
#define   KEY_NUMPAD_6 230
#define   KEY_NUMPAD_7 231
#define   KEY_NUMPAD_8 232
#define   KEY_NUMPAD_9 233
#define KEY_SPACE_BAR   0x20

#define KEY_UP_ARROW   0xDA
#define KEY_DOWN_ARROW 0xD9
#define KEY_LEFT_ARROW 0xD8
#define KEY_RIGHT_ARROW    0xD7
#define KEY_BACKSPACE  0xB2
#define KEY_TAB        0xB3
#define KEY_RETURN 0xB0
#define KEY_ESC        0xB1
#define KEY_INSERT 0xD1
#define KEY_DELETE 0xD4
#define KEY_PAGE_UP    0xD3
#define KEY_PAGE_DOWN  0xD6
#define KEY_HOME   0xD2
#define KEY_END        0xD5
#define KEY_CAPS_LOCK  0xC1
#define KEY_F1     0xC2
#define KEY_F2     0xC3
#define KEY_F3     0xC4
#define KEY_F4     0xC5
#define KEY_F5     0xC6
#define KEY_F6     0xC7
#define KEY_F7     0xC8
#define KEY_F8     0xC9
#define KEY_F9     0xCA
#define KEY_F10        0xCB
#define KEY_F11        0xCC
#define KEY_F12        0xCD

void setup() {
    Serial.begin(9600);
}

void one() {
    Keyboard.press(KEY_NUMPAD_1);
    delay(50);
    Keyboard.release(KEY_NUMPAD_1);
}

void two() {
    Keyboard.press(KEY_NUMPAD_2);
    delay(50);
    Keyboard.release(KEY_NUMPAD_2);
}

void three() {
    Keyboard.press(KEY_NUMPAD_3);
    delay(50);
    Keyboard.release(KEY_NUMPAD_3);
}

void four() {
    Keyboard.press(KEY_NUMPAD_4);
    delay(50);
    Keyboard.release(KEY_NUMPAD_4);
}

void six() {
    Keyboard.press(KEY_NUMPAD_6);
    delay(50);
    Keyboard.release(KEY_NUMPAD_6);
}


void seven() {
    Keyboard.press(KEY_NUMPAD_7);
    delay(50);
    Keyboard.release(KEY_NUMPAD_7);
}


void eight() {
    Keyboard.press(KEY_NUMPAD_8);
    delay(50);
    Keyboard.release(KEY_NUMPAD_8);
}

void nine() {
    Keyboard.press(KEY_NUMPAD_9);
    delay(50);
    Keyboard.release(KEY_NUMPAD_9);
}

void space() {
    Keyboard.press(KEY_CTRL);
    delay(30);
    Keyboard.release(KEY_CTRL);
}

void loop()
{
    if (Serial.available() > 0) {
        String info = Serial.readStringUntil('\n');
        char buf[sizeof(info)];
        info.toCharArray(buf, sizeof(buf));
        char* p = buf;
        char* s;
        int delayTime = 25;
        while ((s = strtok_r(p, ";", &p)) != NULL) {
            String str(s);
            if (str == "1") {
                one();
                delay(delayTime);
            }
            else if (str == "2") {
                two();
                delay(delayTime);
            }
            else if (str == "3") {
                three();
                delay(delayTime);
            }
            else if (str == "4") {
                four();
                delay(delayTime);
            }
            else if (str == "6") {
                six();
                delay(delayTime);
            }
            else if (str == "7") {
                seven();
                delay(delayTime);
            }
            else if (str == "8") {
                eight();
                delay(delayTime);
            }
            else if (str == "9") {
                nine();
                delay(delayTime);
            }
            else if (str == "s") {
                space();
            }
        }
        Serial.println(info);
    }
    delay(1);
}