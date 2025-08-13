#include <ncurses.h>

void init() {
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  scrollok(stdscr, false);
  timeout(0);
}

int colornum(int fg, int bg) {
  int B, bbb, ffff;
  B = 1 << 7;
  bbb = (7 & bg) << 4;
  ffff = 7 & fg;
  return (B | bbb | ffff);
}