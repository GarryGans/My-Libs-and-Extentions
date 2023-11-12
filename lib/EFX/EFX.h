#ifndef EFX_H
#define EFX_H

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <Timer.h>
#include <ArduinoSTL.h>
#include <vector>

using namespace std;

#define sec 1000

#define x_bar 0
#define y_bar 58
#define h_bar 6

// class EFX : public U8G2_SSD1306_128X64_NONAME_1_HW_I2C
class EFX : public U8G2_SH1106_128X64_NONAME_1_HW_I2C
{
private:
    Timer timer[7];
    byte amount = 0;
    byte prewAmount = 0;

    unsigned long blinkMil = 500;

    const byte escapeCounter = 8;

    byte screenWidth = getWidth();
    byte screenHeight = getHeight();

    byte borderW;
    byte borderH;

    byte width;
    byte height;

    byte x;
    byte y;

    double blockWidth;
    double brick = 0;

    double temp;
    double temp_2;
    double factor;
    byte barWidth = 0;
    double prewBarWidth = 0;
    double tempAmount = 0;

    byte id = 0;

    int icon;
    int lock = 79;
    int unlock = 68;
    byte WH = 48;

    struct stringPoint
    {
        byte move_x;
        boolean move;
        boolean moveLeft;
        boolean moveRight;
        byte start_x;
        byte padding;
        byte deep_x;

        //  byte start_y;
    };

    vector<stringPoint> sp;

    vector<Timer> tiPad;
    vector<Timer> tiDeep;

    byte setX;
    byte setY;

public:
    enum class PosX
    {
        center,
        centerFrame,
        left,
        leftSpace,
        leftHalf,
        right,
        rightSpace,
        rightHalf,
        rightFrameSide,
        rightFrameHalfSide,
        custom,
        customFrame
    } pos_x;

    enum class PosY
    {
        center,
        up,
        upSpace,
        upHalf,
        down,
        downSpace,
        downHalf,
        centerFrame,
        upFrame,
        upFrameHalf,
        downFrame,
        downFrameSpace,
        downFrameHalf,
        custom
    } pos_y;

    struct moveStr
    {
        String string;
        PosX pos_x;
        PosY pos_y;
        int time;

        bool operator==(const moveStr &) const;
    };

    vector<moveStr> strMov;

    boolean escBar = false;
    boolean sleep = false;

    byte together_X;

    //
    //
    //
    //
    //

    EFX();
    ~EFX();

    void customX(byte x);
    void customY(byte y);

    byte nextY(byte num, byte id);

    template <typename type>
    byte getDigWidth(type value);

    void alignSimbols(byte WH, byte H, PosX pos_x, PosY pos_y);
    void frameAlign(byte W, byte H, PosX pos_x, PosY pos_y);
    void iconAlign(int icon, byte iconWH, PosX pos_x, PosY pos_y);
    void digStringAlign(byte dig, const char *string, PosX pos_x, PosY pos_y);
    void strDigAlign(const char *string, byte dig, PosX pos_x, PosY pos_y);
    void strDigAlign(const String string, byte dig, PosX pos_x, PosY pos_y);

    template <typename type>
    void digAlign(type dig, PosX pos_x, PosY pos_y);

    void setPosition(const char *format, PosX pos_x, PosY pos_y);
    void setPositionMoveStr(const String format, PosX pos_x, PosY pos_y);

    void textAlign(const char *string, PosX pos_x, PosY pos_y);

    void stringAlign(String str, PosX pos_x, PosY pos_y);

    void setHeight(const uint8_t *font);

    void deepMover(stringPoint &sp);
    void padMover(stringPoint &sp);

    void moveStringDeep(const String string, PosX pos_x, PosY pos_y, byte deep_x = 0, int time = 10);
    void moveStringPad(const String string, PosX pos_x, PosY pos_y, byte padding = 0, int time = 10);

    void autoBar(byte &time, boolean &escape, boolean increase = false, boolean reset = false);
    void autoBrickBar(byte time, boolean &escape, boolean increase = false, boolean reset = false);

    void escapeBar(byte amount, boolean reset);
    void escapeBrickBar(byte amount, boolean reset);

    void progressBar(byte amount, boolean reset);
    void progressBrickBar(byte amount, boolean reset);

    void blinkFrame(int value, PosX pos_x, PosY pos_y, boolean tempBlock = 0, boolean dig = 0);

    void blinkFrame(const char *format, byte digAmount, PosX pos_x, PosY pos_y, boolean tempBlock = false);

    void blinkFrame(const char *format, byte digAmount, byte x, PosY pos_y, boolean tempBlock = false);

    void sleepMode();
};

#endif