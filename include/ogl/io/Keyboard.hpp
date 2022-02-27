#pragma once

#include <map>

namespace ogl
{

/**
 * @brief Keyboard Input Handling Abstraction
 */
class KeyBoard
{
private:
    static std::map<int, int> keymap;

public:
    /**
     * @brief get whether key is pressed, released or held down.
     */
    static int getKeyStatus(int key) { return keymap[key]; }

    /**
     * @brief update the status of a key
     *
     * @param key   Key to be modified
     * @param state The new state of the key
     */
    static void updateKeyState(int key, int state) { keymap[key] = state; }
};

std::map<int, int> KeyBoard::keymap{};

} // namespace ogl
