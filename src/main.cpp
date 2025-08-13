#include "../include/defs.hpp"
#include <ctime>
#include <ncurses.h>
#include <print>
#include <thread>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
  int wait;
  
  switch (argv[1][0]) {
    default:
      println("ERR: Invalid argument '{}'", argv[1][0]);
    return 1;
    
    case 's':
      wait = 500;
    break;

    case 'm':
      wait = 200;
    break;

    case 'f':
      wait = 100;
    break;

    case 'e':
      wait = 50;
    break;

    case 'z':
      wait = 0;
    break;

    case 'h':
      println("snake [SPEED]");
      println("s: slow");
      println("m: medium");
      println("f: fast");
      println("e: extreme");
      println("z: zero-time (no wait between frames)");
    return 0;
  }
  
  srand(time(0));
  init();
  snake jake;
  apple jeff;
  Engine engine;
  
  while (!engine.lose) {
    engine.update(&jake, &jeff);
    node<ncvec> *current = jake.body;
    
    init_pair(colornum(COLOR_GREEN, COLOR_BLACK), COLOR_GREEN, COLOR_BLACK);
    init_pair(colornum(COLOR_RED, COLOR_BLACK), COLOR_RED, COLOR_BLACK);

    clear();
    start_color();
    while (current != nullptr) {
      move(current->data->y, current->data->x);
      attron(COLOR_PAIR(colornum(COLOR_GREEN, COLOR_BLACK)));
      printw("#");
      attroff(COLOR_PAIR(colornum(COLOR_GREEN, COLOR_BLACK)));
      current = current->next;
    }
    
    move(jeff.pos.y, jeff.pos.x);
    attron(COLOR_PAIR(colornum(COLOR_RED, COLOR_BLACK)));
    printw("O");
    attroff(COLOR_PAIR(colornum(COLOR_RED, COLOR_BLACK)));
    refresh();
    this_thread::sleep_for(std::chrono::milliseconds(wait));
  }
  
  endwin();
  println("\nFinal length was {} metres!\n", jake.body->len());
}