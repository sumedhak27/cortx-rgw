// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=2 sw=2 expandtab ft=cpp

/*
 * Garbage Collector Classes for the CORTX Motr backend
 *
 * Copyright (C) 2022 Seagate Technology LLC and/or its Affiliates
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation. See file COPYING.
 *
 */

#ifndef __MOTR_GC_H__
#define __MOTR_GC_H__

#include "rgw_sal_motr.h"
#include "common/Thread.h"
#include <mutex>
#include <condition_variable>

class MotrGC : public Thread {
 private: 
  const DoutPrefixProvider *dpp;
  rgw::sal::Store *store;
  std::mutex mtx;
  std::condition_variable cv;
  bool stop_signalled = false;
  uint32_t gc_interval = 60*60;  // default: 24*60*60 sec
  uint32_t gc_obj_min_wait = 60*60;  // 60*60sec default

 public:
  MotrGC(const DoutPrefixProvider *_dpp, rgw::sal::Store* _store) :
         dpp(_dpp), store(_store) {}

  void *entry() override;

  void signal_stop() {
    std::lock_guard<std::mutex> lk_guard(mtx);
    stop_signalled = true;
    cv.notify_all();  
  }
};

#endif
