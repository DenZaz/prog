#ifndef MYREADKEY_H
#define MYREADKEY_H

enum Keys {UP, DOWN,LEFT, RIGHT, F5, F6, ESC, ENTER, LOAD, SAVE, RUN, STEP, RESET, QUIT, EDIT, NONE};

void termInit();
void defaultTermSettings(struct termios *);
int rk_readKey(enum Keys *key);
int rk_myTermSave(struct termios *);
int rk_myTermRestore(struct termios *);
int rk_myTermRegime(struct termios const*, int, int, int, int, int);
#endif