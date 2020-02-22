#include <Keyboard.h>

#define KEY_RIGHT_SHIFT    0x85
#define KEY_RIGHT_ALT  0x86
#define KEY_RIGHT_GUI  0x87

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

void up() {
    Keyboard.press(KEY_UP_ARROW);
    delay(random(45, 55));
    Keyboard.release(KEY_UP_ARROW);
}
void down() {
    Keyboard.press(KEY_DOWN_ARROW);
    delay(random(45, 55));
    Keyboard.release(KEY_DOWN_ARROW);
}
void left() {
    Keyboard.press(KEY_LEFT_ARROW);
    delay(random(45, 55));
    Keyboard.release(KEY_LEFT_ARROW);
}
void right() {
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(random(45, 55));
    Keyboard.release(KEY_RIGHT_ARROW);
}
void loop()
{
    if (Serial.available() > 0) {
        String info = Serial.readStringUntil('\n');
        char buf[sizeof(info)];
        info.toCharArray(buf, sizeof(buf));
        char* p = buf;
        char* s;
        int delayTime = random(25, 40);
        while ((s = strtok_r(p, ";", &p)) != NULL) {
            String str(s);
            if (str == "u") {
                up();
                delay(delayTime);
            }
            else if (str == "d") {
                down();
                delay(delayTime);
            }
            else if (str == "l") {
                left();
                delay(delayTime);
            }
            else if (str == "r") {
                right();
                delay(delayTime);
            }
        }
        Serial.println(info);
    }
    delay(1);
}