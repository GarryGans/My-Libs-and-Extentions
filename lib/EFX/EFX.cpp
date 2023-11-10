#include "EFX.h"

// EFX::EFX() : U8G2_SSD1306_128X64_NONAME_1_HW_I2C(U8G2_R0, /* reset=*/U8X8_PIN_NONE)
EFX::EFX() : U8G2_SH1106_128X64_NONAME_1_HW_I2C(U8G2_R0, /* reset=*/U8X8_PIN_NONE)
{
}

EFX::~EFX()
{
}

void EFX::customX(byte x)
{
    setX = x;
}

void EFX::customY(byte y)
{
    setY = y;
}

void EFX::alignSimbols(byte W, byte H, PosX pos_x, PosY pos_y)
{
    switch (pos_x)
    {
    case PosX::center:
        x = (screenWidth - W) / 2;
        break;

    case PosX::centerFrame:
        x = (screenWidth - W) / 2 + width + width / 2;
        break;

    case PosX::left:
        x = 0;
        break;

    case PosX::leftSpace:
        x = W / 8;
        break;

    case PosX::leftHalf:
        x = (screenWidth / 2 - W) / 2;
        break;

    case PosX::right:
        x = screenWidth - W;
        break;

    case PosX::rightSpace:
        x = screenWidth - (W + W / 8);
        break;

    case PosX::rightHalf:
        x = (screenWidth + screenWidth / 2 - W) / 2;
        break;

    case PosX::rightFrameSide:
        x = screenWidth - width - (screenWidth - W) / 2;
        break;

    case PosX::rightFrameHalfSide:
        x = screenWidth - width - (screenWidth / 2 - W) / 2;
        break;

    case PosX::custom:
        x = setX;
        break;

    case PosX::customFrame:
        x = setX - borderW / 2;
        break;

    default:
        break;
    }

    switch (pos_y)
    {
    case PosY::center:
        y = (screenHeight + H) / 2;
        break;

    case PosY::up:
        y = H;
        break;

    case PosY::upSpace:
        y = H + H / 4;
        break;

    case PosY::upHalf:
        y = (screenHeight / 2 - H) / 2 + H;
        break;

    case PosY::down:
        y = screenHeight;
        break;

    case PosY::downSpace:
        y = screenHeight - H / 4;
        break;

    case PosY::downHalf:
        y = (screenHeight + screenHeight / 2 - H) / 2 + H;
        break;

    case PosY::centerFrame:
        y = (screenHeight - H) / 2;
        break;

    case PosY::upFrame:
        y = 0;
        break;

    case PosY::upFrameHalf:
        y = (screenHeight / 2 - H) / 2;
        break;

    case PosY::downFrame:
        y = screenHeight - H;
        break;

    case PosY::downFrameSpace:
        y = screenHeight - H - H / 4;
        break;

    case PosY::downFrameHalf:
        y = (screenHeight + screenHeight / 2 - H) / 2;
        break;

    case PosY::custom:
        y = setY;
        break;

    default:
        break;
    }
}

byte EFX::nextY(byte num, byte id)
{
    byte Y;

    Y = (screenHeight / num + height) / 2 + (screenHeight / num) * id;

    return Y;
}

template <typename type>
byte EFX::getDigWidth(type value)
{
    byte count = 2;

    if (value != 0)
    {
        count = byte(log10(value) + 2);
    }

    char val[count];
    String(value).toCharArray(val, count);

    return getStrWidth(val);
}

void EFX::setHeight(const uint8_t *font)
{
    setFont(font);

    if (font == u8g2_font_courB08_tn || font == u8g2_font_courB08_tf)
    {
        height = 6;
    }

    else if (font == u8g2_font_pressstart2p_8f)
    {
        height = 8;
    }

    else if (font == u8g2_font_t0_12b_tf || font == u8g2_font_pixelmordred_tf || font == u8g2_font_HelvetiPixelOutline_tr)
    {
        height = 12;
    }

    else if (font == u8g2_font_profont22_tn || font == u8g2_font_9x18_tn || font == u8g2_font_crox4h_tf || font == u8g2_font_crox4hb_tf || font == u8g2_font_luBS14_te)
    {
        height = 14;
    }
    else if (font == u8g2_font_crox5tb_tf || font == u8g2_font_inb16_mf || font == u8g2_font_inb16_mf)
    {
        height = 16;
    }
    else if (font == u8g2_font_ncenB18_tf || font == u8g2_font_ncenR18_tf)
    {
        height = 18;
    }
    // else
    // {
    // Serial.println("un");
    // }
}

void EFX::textAlign(const char *string, PosX pos_x, PosY pos_y)
{
    alignSimbols(getStrWidth(string), height, pos_x, pos_y);

    setCursor(x, y);
    print(string);
}

void EFX::stringAlign(String str, PosX pos_x, PosY pos_y)
{
    char light[str.length() + 1];

    String(str).toCharArray(light, str.length() + 1);

    textAlign(light, pos_x, pos_y);
}

void EFX::digStringAlign(byte dig, const char *string, PosX pos_x, PosY pos_y)
{
    alignSimbols(getDigWidth(dig) + getStrWidth(string), height, pos_x, pos_y);

    setX = x;

    setCursor(x, y);

    print(dig);
    print(string);
}

void EFX::strDigAlign(const char *string, byte dig, PosX pos_x, PosY pos_y)
{
    String space;

    byte strW;

    if (getStrWidth(string) > getStrWidth("WW"))
    {
        space = " ";
        strW = getStrWidth(" ");
    }
    else
    {
        space = "  ";
        strW = getStrWidth("  ");
    }

    alignSimbols(getStrWidth(string) + strW + getDigWidth(dig), height, pos_x, pos_y);

    setX = x;

    setCursor(x, y);

    print(string);
    print(space);
    print(dig);
}

void EFX::strDigAlign(const String string, byte dig, PosX pos_x, PosY pos_y)
{
    char str[string.length() + 1];
    String(string).toCharArray(str, string.length() + 1);

    String space;

    byte strW;

    if (getStrWidth(str) > getStrWidth("WW"))
    {
        space = " ";
        strW = getStrWidth(" ");
    }
    else
    {
        space = "  ";
        strW = getStrWidth("  ");
    }

    alignSimbols(getStrWidth(str) + strW + getDigWidth(dig), height, pos_x, pos_y);

    setX = x;

    setCursor(x, y);

    print(str);
    print(space);
    print(dig);
}

template <typename type>
void EFX::digAlign(type dig, PosX pos_x, PosY pos_y)
{
    alignSimbols(getDigWidth(dig), height, pos_x, pos_y);

    setCursor(x, y);
    print(dig);
}

template void EFX::digAlign<byte>(byte, PosX, PosY);

template void EFX::digAlign<int>(int, PosX, PosY);

template void EFX::digAlign<double>(double, PosX, PosY);

void EFX::setPosition(const char *format, PosX pos_x, PosY pos_y)
{
    alignSimbols(getStrWidth(format), height, pos_x, pos_y);

    setCursor(x, y);
}

void EFX::setPositionMoveStr(const String format, PosX pos_x, PosY pos_y)
{
    char str[format.length() + 1];
    String(format).toCharArray(str, format.length() + 1);

    alignSimbols(getStrWidth(str), height, pos_x, pos_y);

    setCursor(x, y);
}

void EFX::iconAlign(int icon, byte iconWH, PosX pos_x, PosY pos_y)
{
    alignSimbols(iconWH, iconWH, pos_x, pos_y);
    drawGlyph(x, y, icon);
}

void EFX::frameAlign(byte W, byte H, PosX pos_x, PosY pos_y)
{
    borderW = 6;
    borderH = 6;

    W += borderW;
    H += borderH;

    alignSimbols(W, H, pos_x, pos_y);
    drawFrame(x, y, W, H);
}

void EFX::blinkFrame(int value, PosX pos_x, PosY pos_y, boolean tempBlock, boolean dig)
{
    if (timer[0].blink(blinkMil, tempBlock))
    {
        // byte width;

        if (dig)
        {
            if (value < 10)
            {
                width = getDigWidth(value) * 2;
            }
            else
            {
                width = getDigWidth(value);
            }
        }
        else
        {
            width = getDigWidth(value);
        }

        frameAlign(width, height, pos_x, pos_y);
    }
}

void EFX::blinkFrame(const char *format, byte digAmount, PosX pos_x, PosY pos_y, boolean tempBlock)
{
    if (timer[1].blink(blinkMil, tempBlock))
    {
        // byte width;

        width = getMaxCharWidth() * digAmount;

        setPosition(format, pos_x, pos_y);

        borderW = 6;
        borderH = 6;

        width += borderW;
        height += borderH;

        drawFrame(x - borderW / 2, y - borderH / 2, width, height);
    }
}

void EFX::blinkFrame(const char *format, byte digAmount, byte x, PosY pos_y, boolean tempBlock)
{
    if (timer[1].blink(blinkMil, tempBlock))
    {
        // byte width;

        width = getMaxCharWidth() * digAmount;

        setPosition(format, pos_x, pos_y);

        borderW = 12;
        borderH = 12;

        width += borderW;
        height += borderH;

        drawFrame(x - borderW / 2, 1 + y - borderH / 2, width, height);
    }
}

void EFX::deepMover(stringPoint &sp)
{
    if (sp.moveLeft)
    {
        sp.move_x--;

        if (sp.move_x == sp.start_x - sp.deep_x)
        {
            sp.moveLeft = false;
            sp.moveRight = true;
        }
    }

    else if (sp.moveRight)
    {
        sp.move_x++;

        if (sp.move_x == sp.start_x + sp.deep_x)
        {
            sp.moveRight = false;
            sp.moveLeft = true;
        }
    }

    together_X = sp.move_x;
}

void EFX::padMover(stringPoint &sp)
{
    if (sp.moveLeft)
    {
        sp.move_x--;

        if (sp.move_x == sp.padding)
        {
            sp.moveLeft = false;
            sp.moveRight = true;
        }
    }

    else if (sp.moveRight)
    {
        sp.move_x++;

        if (sp.move_x == sp.start_x + sp.start_x - sp.padding)
        {
            sp.moveRight = false;
            sp.moveLeft = true;
        }
    }

    together_X = sp.move_x;
}

bool EFX::moveStr::operator==(const moveStr &s) const
{
    return (string == s.string && pos_x == s.pos_x && pos_y == s.pos_y && time == s.time);
}

void EFX::moveStringDeep(const String string, PosX pos_x, PosY pos_y, byte deep_x, int time)
{
    moveStr strNow = {string, pos_x, pos_y, time};

    for (byte i = 0; i < strMov.size(); i++)
    {
        if (strMov[i] == strNow)
        {
            id = i;
        }
    }

    if (strMov.empty() || !(strNow == strMov[id]))
    {
        stringPoint spNow;
        spNow.move = false;

        strMov.push_back(strNow);
        sp.push_back(spNow);

        Timer timer;
        ti.push_back(timer);

        id = strMov.size() - 1;
    }

    setPositionMoveStr(string, pos_x, pos_y);

    if (!sp[id].move)
    {
        sp[id].move = true;
        sp[id].move_x = sp[id].start_x = x;

        sp[id].moveLeft = true;
        sp[id].moveRight = false;

        if (deep_x == 0)
        {
            sp[id].deep_x = sp[id].start_x;
        }
        else
        {
            sp[id].deep_x = deep_x;
        }
    }

    setCursor(sp[id].move_x, y);
    print(string);

    if (ti[id].wait(time))
    {
        deepMover(sp[id]);
        // together_X = sp[id].deep_x;
    }
}

void EFX::moveStringPad(const String string, PosX pos_x, PosY pos_y, byte padding, int time)
{
    moveStr strNow = {string, pos_x, pos_y, time};

    for (byte i = 0; i < strMov.size(); i++)
    {
        if (strMov[i] == strNow)
        {
            id = i;
        }
    }

    if (strMov.empty() || !(strNow == strMov[id]))
    {
        stringPoint spNow;
        spNow.move = false;

        strMov.push_back(strNow);
        sp.push_back(spNow);

        Timer timer;
        ti.push_back(timer);

        id = strMov.size() - 1;
    }

    setPositionMoveStr(string, pos_x, pos_y);

    if (!sp[id].move)
    {
        sp[id].move = true;
        sp[id].move_x = sp[id].start_x = x;

        sp[id].padding = padding;

        sp[id].moveLeft = true;
        sp[id].moveRight = false;
    }

    setCursor(sp[id].move_x, y);
    print(string);

    if (ti[id].wait(time))
    {
        padMover(sp[id]);
    }
}

void EFX::autoBar(byte &time, boolean &escape, boolean increase, boolean reset)
{
    if (reset)
    {
        barWidth = screenWidth;

        temp = sec;

        escBar = true;
    }

    if (escBar)
    {
        time = timer[3].reduceCounter(time, reset, temp);

        temp_2 = (double)time * (double)sec / (double)screenWidth;

        barWidth = timer[2].reduceCounter(barWidth, reset, temp_2);

        if (time == 0 && barWidth == 0)
        {
            escape = true;
            escBar = false;
        }

        drawBox(x_bar, y_bar, barWidth, h_bar);
    }
}

void EFX::autoBrickBar(byte time, boolean &escape, boolean increase, boolean reset)
{
    if (!escBar && !escape)
    {
        blockWidth = screenWidth / time;
        escBar = true;
        // Serial.println("escBar");
    }

    if (escBar)
    {
        amount = timer[4].counter(time, increase, reset, time);

        if ((increase && amount == time) || (!increase && amount == 0))
        {
            escape = true;
            escBar = false;
            // Serial.println("FULL");
        }
    }

    byte width = blockWidth * amount;
    drawBox(x_bar, y_bar, width, h_bar);
}

void EFX::escapeBar(byte amount, boolean reset)
{
    if (reset)
    {
        barWidth = screenWidth;

        prewAmount = 0;
    }

    // if (barWidth != 0) // EATS 6 BYTES
    // {
    if (amount != prewAmount)
    {
        temp = (double)amount * (double)1000 / (double)barWidth;

        prewAmount = amount;
    }

    barWidth = timer[5].reduceCounter(barWidth, reset, temp);

    // if (amount == 0) // EATS 10 BYTES
    // {
    //     while (barWidth > 0)
    //         barWidth--;
    // }

    drawBox(x_bar, y_bar, barWidth, h_bar);
    // }
}

void EFX::escapeBrickBar(byte amount, boolean reset)
{
    if (reset)
    {
        brick = (double)screenWidth / (double)amount;
        // Serial.println("escBar");
    }

    double width = brick * (double)amount;
    drawBox(x_bar, y_bar, width, h_bar);
}

void EFX::progressBar(byte amount, boolean reset)
{
    if (reset)
    {
        barWidth = 0;
    }

    if (timer[6].wait(amount * 1000 / screenWidth))
    {
        if (barWidth < screenWidth)
        {
            barWidth++;
        }
    }

    drawBox(x_bar, y_bar, barWidth, h_bar);
}

void EFX::progressBrickBar(byte amount, boolean reset)
{
    if (reset)
    {
        tempAmount = amount;
        brick = (double)screenWidth / (double)amount;
        // Serial.println("escBar");
    }

    double width = brick * (tempAmount - (double)amount);
    drawBox(x_bar, y_bar, width, h_bar);
}

void EFX::sleepMode()
{
    if (sleep)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_courB08_tf);
            textAlign("SLEEP", PosX::center, PosY::center);
        } while (nextPage());
    }
}
