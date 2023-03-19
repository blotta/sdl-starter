#include "sdl_utils.h"
#include "game_utils.h"

typedef struct {
    SDL_KeyCode key; // char
    bool pressed;
    bool just_pressed;
    bool just_released;
} _keyState;

typedef struct {
    Uint8 button; // SDLMouseButton
    bool pressed;
    bool just_pressed;
    bool just_doublepressed;
    bool just_released;
} _mouseButtonState;

#define MOUSE_BUTTONS_LENGTH 3

typedef struct {
    union
    {
        struct {
            _mouseButtonState left;
            _mouseButtonState middle;
            _mouseButtonState right;
        };
        _mouseButtonState buttons[MOUSE_BUTTONS_LENGTH];
    };
    uint32_t x;
    uint32_t y;
} _mouseState;

static struct {
    _keyState* keyStates;
    size_t capacity;
    size_t length;
    bool requested_quit;

    _mouseState mouse;
} _inputs;

void sdlu_input_mapper_init(uint8_t capacity) {
    _inputs.capacity = capacity;
    _inputs.length = 0;
    _inputs.keyStates = (_keyState*)malloc((uint32_t)capacity * sizeof(_keyState));
    _inputs.requested_quit = false;

    _inputs.mouse.left.button = SDL_BUTTON_LEFT;
    _inputs.mouse.middle.button = SDL_BUTTON_MIDDLE;
    _inputs.mouse.right.button = SDL_BUTTON_RIGHT;
}

void sdlu_input_mapper_deinit() {
    free(_inputs.keyStates);
}

void sdlu_input_mapper_track(SDL_KeyCode kc) {
    if (_inputs.length + 1 > _inputs.capacity) {
        return; // not dynamic
    }
    _keyState k = {
        .key = kc,
        .just_pressed = 0,
        .just_released = 0,
        .pressed = 0
    };
    _inputs.keyStates[_inputs.length] = k;
    _inputs.length += 1;
}

bool sdlu_input_key_pressed(SDL_KeyCode key) {
    for (size_t i = 0; i < _inputs.length; i++) {
        if (_inputs.keyStates[i].key == key && _inputs.keyStates[i].pressed) {
            return true;
        }
    }
    return false;
}

bool sdlu_input_key_justpressed(SDL_KeyCode key) {
    for (size_t i = 0; i < _inputs.length; i++) {
        if (_inputs.keyStates[i].key == key && _inputs.keyStates[i].just_pressed) {
            return true;
        }
    }
    return false;
}

bool sdlu_input_mouse_pressed(Uint8 btn) {
    if (btn > 0 && btn <= MOUSE_BUTTONS_LENGTH) {
        return _inputs.mouse.buttons[btn - 1].pressed;
    }
    return false;
}

bool sdlu_input_mouse_justpressed(Uint8 btn) {
    if (btn > 0 && btn <= MOUSE_BUTTONS_LENGTH) {
        return _inputs.mouse.buttons[btn - 1].just_pressed;
    }
    return false;
}

bool sdlu_input_mouse_justdoublepressed(Uint8 btn) {
    if (btn > 0 && btn <= MOUSE_BUTTONS_LENGTH) {
        return _inputs.mouse.buttons[btn - 1].just_doublepressed;
    }
    return false;
}


bool sdlu_input_mouse_justreleased(Uint8 btn) {
    if (btn > 0 && btn <= MOUSE_BUTTONS_LENGTH) {
        return _inputs.mouse.buttons[btn - 1].just_released;
    }
    return false;
}


bool sdlu_input_requested_quit() {
    return _inputs.requested_quit;
}

void sdlu_pollevents() {

    // reset keyboard
    for (size_t i = 0; i < _inputs.length; i++) {
        _inputs.keyStates[i].just_pressed = false;
        _inputs.keyStates[i].just_released = false;
    }

    // reset mouse
    for (size_t i = 0; i < MOUSE_BUTTONS_LENGTH; i++) {
        _inputs.mouse.buttons[i].just_pressed = false;
        _inputs.mouse.buttons[i].just_doublepressed = false;
        _inputs.mouse.buttons[i].just_released = false;
    }

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                _inputs.requested_quit = true;
                break;
            case SDL_KEYDOWN:
                for (size_t i = 0; i < _inputs.length; i++) {
                    if (event.key.keysym.sym  == _inputs.keyStates[i].key) {
                        _inputs.keyStates[i].just_pressed = !_inputs.keyStates[i].pressed;
                        _inputs.keyStates[i].pressed = true;
                    }
                }
                break;
            case SDL_KEYUP:
                for (size_t i = 0; i < _inputs.length; i++) {
                    if (event.key.keysym.sym  == _inputs.keyStates[i].key) {
                        _inputs.keyStates[i].just_released = _inputs.keyStates[i].pressed;
                        _inputs.keyStates[i].pressed = false;
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN: {
                    SDL_MouseButtonEvent* e = (SDL_MouseButtonEvent*)&event;
                    for (size_t i = 0; i < MOUSE_BUTTONS_LENGTH; i++) {
                        if (e->button == _inputs.mouse.buttons[i].button) {
                            // printf("button %d pressed\n", e->button);
                            _inputs.mouse.buttons[i].pressed = true;
                            _inputs.mouse.buttons[i].just_pressed = true;

                            if (e->clicks == 2) {
                                // printf("button %d pressed twice\n", e->button);
                                _inputs.mouse.buttons[i].just_doublepressed = true;
                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP: {
                    SDL_MouseButtonEvent* e = (SDL_MouseButtonEvent*)&event;
                    for (size_t i = 0; i < MOUSE_BUTTONS_LENGTH; i++) {
                        if (e->button == _inputs.mouse.buttons[i].button) {
                            // printf("button %d released\n", e->button);
                            _inputs.mouse.buttons[i].just_released = true;
                            _inputs.mouse.buttons[i].pressed = false;
                        }
                    }
                }
                break;
            
        }
    }
}