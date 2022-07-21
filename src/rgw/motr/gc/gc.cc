// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=2 sw=2 expandtab ft=cpp

/*
 * Garbage Collector implementation for the CORTX Motr backend
 *
 * Copyright (C) 2022 Seagate Technology LLC and/or its Affiliates
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation. See file COPYING.
 *
 */

#include "gc.h"

void *MotrGC::GCWorker::entry() {
  // std::unique_lock<std::mutex> lk(lock);
  // ldpp_dout(dpp, 10) << __func__ << ": Motr GC started" << dendl;
  
  // do {
  //   ldpp_dout(dpp, 10) << __func__ << ": In a Motr GC loop." << dendl;
  //   cv.wait_for(lk, std::chrono::milliseconds(gc_interval * 10));
  // } while (! stop_signalled);

  // ldpp_dout(dpp, 0) << __func__ << ": Stop signalled called.#" 
  //   << stop_signalled << dendl;
  return nullptr;
}

void MotrGC::initialize(CephContext *_cct, rgw::sal::Store* _store) {
  cct = _cct;
  store = _store;
  // fetch num_max_queue from config
  // create all gc queues in motr index store
}

void MotrGC::start_processor() {
  // fetch max_concurrent_io i.e. max_threads to create from config.
  // start all the gc_worker threads
}

void MotrGC::stop_processor() {
  // in case of stop signal,
  // gracefully shutdown all the gc threads.
  down_flag = true;
  for (auto& worker : workers) {
    worker->stop();
    worker->join();
  }
  workers.clear();
}

void MotrGC::GCWorker::stop() {
  std::lock_guard l{lock};
  cv.notify_all();
}
