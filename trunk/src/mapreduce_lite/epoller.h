/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301, USA.
*/
// Copyright 2010 Tencent Inc.
// Author: YAN Hao (charlieyan@tencent.com)

#ifndef MAPREDUCE_LITE_EPOLLER_H_
#define MAPREDUCE_LITE_EPOLLER_H_

#include <sys/epoll.h>

#include "src/base/common.h"

namespace mapreduce_lite {

// a simple wrapper of epoll
class Epoller {
 public:
  explicit Epoller(int epoll_size);
  ~Epoller();

  // Close the control file descriptor of the epoll object
  void Close();

  // Return the file descriptor number of the control fd
  int FileNo() const;

  // Register a socket descriptor with the epoll object
  // eventmask:
  //  EPOLLIN, EPOLLOUT, EPOLLRDHUP, EPOLLPRI, EPOLLERR,
  //  EPOLLHUP, EPOLLET, EPOLLONESHOT
  bool Register(int socket, uint32 eventmask);

  // Modify a register file descriptor
  bool Modify(int socket, uint32 eventmask);

  // Remove a registered file descriptor from the epoll object
  bool Unregister(int socket);

  // Wait for events. timeout in milliseconds.
  int Poll(struct epoll_event *events, int max_events, int timeout=-1);

 private:
  int epfd_;

  // A wrapper of epoll_ctl(), implement basic operations on the epoll object
  bool Control(int op, int socket, uint32 eventmask);
};

}  // namespace mapreduce_lite

#endif  // MAPREDUCE_LITE_EPOLLER_H_
