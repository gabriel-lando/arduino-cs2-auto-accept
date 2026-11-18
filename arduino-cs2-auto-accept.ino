// Arduino Leonardo/Micro sketch
// CS2 Auto Accept: while Scroll Lock is ON, moves the pointer to the CS2
// "ACCEPT" button and clicks it, over and over.
// Obs.: For Elitebook, use Fn + C to toggle Scroll Lock
//
// The pointer is repositioned right before EVERY click, so bumping the
// physical mouse between clicks doesn't matter.
//
// The Arduino acts as an absolute pointing device (like a tablet), so it
// jumps straight to the target. Coordinates are normalized, so it works for
// any resolution as long as the game fills the primary screen.
//
// Install HID-Project library from NicoHood (https://github.com/NicoHood/HID)
#include "HID-Project.h"

// ---------------------------------------------------------------------------
// Configuration
// ---------------------------------------------------------------------------

// Game resolution (what CS2 renders at, not the monitor's native resolution).
const int SCREEN_W = 1920;
const int SCREEN_H = 1080;

// ACCEPT button center, in game pixels.
// Button bounds (approx.): X 870..1050, Y 385..425
const int TARGET_X = 960;
const int TARGET_Y = 405;

// Time between click attempts while Scroll Lock is ON.
const unsigned long CLICK_INTERVAL_MS = 2000;

// Pause between positioning the pointer and pressing the button, so the
// UI registers the hover before the click.
const unsigned long SETTLE_MS = 40;

// How long the left button stays pressed.
const unsigned long PRESS_MS = 60;

// ---------------------------------------------------------------------------

unsigned long g_ulLastClick = 0;
bool g_bWasEnabled = false;

void setup() {
  AbsoluteMouse.begin();
  BootKeyboard.begin();
}

bool GetScrollLockStatus() {
  return (BootKeyboard.getLeds() & LED_SCROLL_LOCK);
}

// HID-Project AbsoluteMouse range is -32768..32767 across the whole screen
// (0 is the center).
int16_t PixelToAbsolute(long px, long size) {
  return (int16_t)(-32768L + (px * 65535L + size / 2) / size);
}

void MoveToTarget() {
  AbsoluteMouse.moveTo(PixelToAbsolute(TARGET_X, SCREEN_W),
                       PixelToAbsolute(TARGET_Y, SCREEN_H));
}

void Click() {
  AbsoluteMouse.press(MOUSE_LEFT);
  delay(PRESS_MS);
  AbsoluteMouse.release(MOUSE_LEFT);
}

void MoveAndClick() {
  MoveToTarget();
  delay(SETTLE_MS);
  MoveToTarget();  // re-assert in case the physical mouse moved meanwhile
  Click();
}

void loop() {
  delay(10);

  bool bEnabled = GetScrollLockStatus();

  if (bEnabled) {
    unsigned long ulNow = millis();
    // Click immediately when enabled, then every CLICK_INTERVAL_MS.
    if (!g_bWasEnabled || ulNow - g_ulLastClick >= CLICK_INTERVAL_MS) {
      MoveAndClick();
      g_ulLastClick = ulNow;
    }
  } else if (g_bWasEnabled) {
    AbsoluteMouse.releaseAll();
  }

  g_bWasEnabled = bEnabled;
}
