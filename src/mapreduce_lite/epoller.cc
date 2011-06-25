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

#include "src/mapreduce_lite/epoller.h"

namespace mapreduce_lite {

Epoller::Epoller(int epoll_size) {
  epfd_ = epoll_create(epoll_size);
  CHECK_LE(0, epfd_);
}

Epoller::~Epoller() {
  Close();
}

void Epoller::Close() {
  if (epfd_ >= 0) {
    CHECK_EQ(0, close(epfd_));
    epfd_ = -1;
  }
}

int Epoller::FileNo() const {
  return epfd_;
}

bool Epoller::Register(int fd, uint32 eventmask) {
  return Control(EPOLL_CTL_ADD, fd, eventmask);
}

bool Epoller::Modify(int fd, uint32 eventmask) {
  return Control(EPOLL_CTL_MOD, fd, eventmask);
}

bool Epoller::Unregister(int fd) {
  return Control(EPOLL_CTL_DEL, fd, 0);
}

int Epoller::Poll(struct epoll_event *events, int max_events, int timeout) {
  return epoll_wait(epfd_, events, max_events, timeout);
}

bool Epoller::Control(int op, int fd, uint32 eventmask) {
  struct epoll_event ev;
  ev.data.fd = fd;
  ev.events = eventmask;
  return 0 == epoll_ctl(epfd_, op, fd, &ev);
}

}  // namespace mapreduce_lite
