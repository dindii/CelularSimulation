#pragma once

#include <stdint.h>

namespace CS
{
    enum class KeyCodes : uint8_t
    {
        CS_MOUSE_LBUTTON = 0x01,          // Left mouse button
        CS_MOUSE_RBUTTON = 0x02,          // Right mouse button
        CS_CANCEL = 0x03,                 // Control-break processing
        CS_MOUSE_MBUTTON = 0x04,          // Middle mouse button (three-button mouse)
        CS_MOUSE_XBUTTON1 = 0x05,         // X1 mouse button
        CS_MOUSE_XBUTTON2 = 0x06,         // X2 mouse button
        CS_BACKSPACE = 0x08,              // BACKSPACE key
        CS_TAB = 0x09,                    // TAB key
        CS_CLEAR = 0x0C,                  // CLEAR key
        CS_ENTER = 0x0D,                  // ENTER key
        CS_SHIFT = 0x10,                  // SHIFT key
        CS_CONTROL = 0x11,                // CTRL key
        CS_ALT = 0x12,                    // ALT key
        CS_PAUSE = 0x13,                  // PAUSE key
        CS_CAPSLOCK = 0x14,               // CAPS LOCK key
        CS_KANA = 0x15,                   // IME Kana mode
        CS_HANGUEL = 0x15,                // IME Hanguel mode (maintained for compatibility; use VK_HANGUL)
        CS_HANGUL = 0x15,                 // IME Hangul mode
        CS_IME_ON = 0x16,                 // IME On
        CS_JUNJA = 0x17,                  // IME Junja mode
        CS_FINAL = 0x18,                  // IME final mode
        CS_HANJA = 0x19,                  // IME Hanja mode
        CS_KANJI = 0x19,                  // IME Kanji mode
        CS_IME_OFF = 0x1A,                // IME Off
        CS_ESCAPE = 0x1B,                 // ESC key
        CS_CONVERT = 0x1C,                // IME convert
        CS_NONCONVERT = 0x1D,             // IME nonconvert
        CS_ACCEPT = 0x1E,                 // IME accept
        CS_MODECHANGE = 0x1F,             // IME mode change request
        CS_SPACE = 0x20,                  // SPACEBAR
        CS_PAGEUP = 0x21,                 // PAGE UP key
        CS_PAGEDOWN = 0x22,               // PAGE DOWN key
        CS_END = 0x23,                    // END key
        CS_HOME = 0x24,                   // HOME key
        CS_LEFT = 0x25,                   // LEFT ARROW key
        CS_UP = 0x26,                     // UP ARROW key
        CS_RIGHT = 0x27,                  // RIGHT ARROW key
        CS_DOWN = 0x28,                   // DOWN ARROW key
        CS_SELECT = 0x29,                 // SELECT key
        CS_PRINT = 0x2A,                  // PRINT key
        CS_EXECUTE = 0x2B,                // EXECUTE key
        CS_SNAPSHOT = 0x2C,               // PRINT SCREEN key
        CS_INSERT = 0x2D,                 // INS key
        CS_DELETE = 0x2E,                 // DEL key
        CS_HELP = 0x2F,                   // HELP key
        CS_0 = 0x30
    };
}