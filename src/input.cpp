#include "input.h"

// Begin new input frame (reset everything)
void Input::beginNewFrame() {
    mPressedKeys.clear();
    mReleasedKeys.clear();
}

// Handle a keydown event
void Input::keyDownEvent(const SDL_Event& event) {
    mPressedKeys[event.key.keysym.scancode] = true;
    mHeldKeys[event.key.keysym.scancode] = true;
}

// Handle a keyup event
void Input::keyUpEvent(const SDL_Event& event) {
    mReleasedKeys[event.key.keysym.scancode] = true;
    mHeldKeys[event.key.keysym.scancode] = false;
}

// Returns whether a key was pressed or not
bool Input::wasKeyPressed(SDL_Scancode key) {
    return mPressedKeys[key];
}

// Returns whether a key was released or not
bool Input::wasKeyReleased(SDL_Scancode key) {
    return mReleasedKeys[key];
}

// Returns whether a key was held or not
bool Input::wasKeyHeld(SDL_Scancode key) {
    return mHeldKeys[key];
}
