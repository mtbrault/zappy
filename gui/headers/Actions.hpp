//
// EPITECH PROJECT, 2018
// IRC
// File description:
// Actions
//

#ifndef ACTIONS_HPP_
# define ACTIONS_HPP_

# include <utility>

struct Actions {
    bool    up = false;
    bool    down = false;
    bool    right = false;
    bool    left = false;
    bool    space = false;
    bool    escape = false;
    bool    enter = false;
    bool    Z = false;
    bool    D = false;
    bool    S = false;
    bool    W = false;
    bool    Q = false;
    bool    click = false;
    int    buttonPressed = -1;
    std::pair<int, int> lastMouseClick;
};

void clearAction(Actions &actions);
void displayAction(Actions &ctions);

#endif /* ACTIONS_HPP_ */
