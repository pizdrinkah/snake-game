#ifndef RENDER_H
#define RENDER_H

struct ncvec {
  int y;
  int x;

  ncvec() {
    y = 0;
    x = 0;
  }
};


void init();

int colornum(int fg, int bg);

#endif