#ifndef DEFS_H
#define DEFS_H

#include <cstdlib>
#include <ncurses.h>
#include "interface.hpp"

template <typename T>

struct node {
  T *data;
  node *next;

  node() {
    data = new T;
    next = nullptr;
  }

  ~node() { delete data; }

  void push_back(T *dat) {
    node *current = this;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = new node;
    current->next->data = new T;
    *(current->next->data) = *(dat);
  }

  void new_list(int len) {
    node *current = this;
    for (int i = 1; i < len; i++) {
      current->next = new node;
      current = current->next;
    }
  }

  int len() {
    node *current = this;
    int len = 0;
    while (current != nullptr) {
      current = current->next;
      len++;
    }
    return len;
  }
};

struct apple {
  ncvec pos;
  bool eaten;

  apple() {
    pos = ncvec();
    pos.x = rand() % 24;
    pos.y = rand() % 16;
    eaten = false;
  }

  void update() {
    if (eaten) {
      pos.x = rand() % 24;
      pos.y = rand() % 16;
      eaten = false;
    }
  }
};

struct snake {
  node<ncvec> *body;
  node<ncvec> *tail;
  bool grow;
  ncvec old_pos;

  snake() {
    body = new node<ncvec>;
    body->data->x = 5;
    body->data->y = 7;
    tail = body;
    grow = false;
  }

  ~snake() {
    node<ncvec> *current = body->next;
    while (current != nullptr) {
      node<ncvec> *previous = current;
      current = current->next;
      delete previous;
    }
  }

  void dir_update(int dir) {
    switch (dir) {
    case 0:
      body->data->y--;
      break;

    case 1:
      body->data->x++;
      break;

    case 2:
      body->data->y++;
      break;

    case 3:
      body->data->x--;
      break;

    default:
      break;
    }
    if (body->data->x < 0) {
      body->data->x = 23;
    }
      if (body->data->y < 0) {
      body->data->y = 15;
    }
    
    body->data->x = abs(body->data->x) % 24;
    body->data->y = abs(body->data->y) % 16;
  }

  void update(int dir, apple *apple, bool &lose) {
    // update snake's body
    node<ncvec> *seg = body->next;
    ncvec old1 = *body->data;
    ncvec old2;

    while (seg != nullptr) {
      old2 = *seg->data;
      *(seg->data) = old1;
      
      old1 = old2;
      old2 = *seg->data;
      seg = seg->next;
    }
    
    old_pos = *(tail->data);
    // update snake's head based on directional input
    this->dir_update(dir);

    // create new segment
    if (grow) {
      body->push_back(&old_pos);
      tail = tail->next;
      grow = false;
    }

    // run collision checks on apple
    if (body->data->x == apple->pos.x && body->data->y == apple->pos.y) {
      apple->eaten = true;
      grow = true;
    }

    // run collision checks on segments,
    node<ncvec> *collseg = body->next;
    while (collseg != nullptr) {
      if (body->data->x == collseg->data->x && body->data->y == collseg->data->y) {
        lose = true;
        break;
      }
      collseg = collseg->next;
    }
  }
};

struct Engine {
  int key;
  bool lose;
  
  Engine() {
    key = 1;
    lose = false;
  }

  void update(snake* snake, apple* apple) {
    switch (getch()) {
      default:
      break;

      case 'a':
        key = key - 1;
        if (key == -1) {
          key = 3;
        }
      break;
      
      case 'd':
        key = key + 1;
        if (key == 4) {
          key = 0;
        }
      break;
    }
    
    snake->update(key, apple, lose);
    apple->update();
  }
};

#endif