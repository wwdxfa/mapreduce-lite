// Copyright 2010 Tencent Inc.
// Author: Yi Wang (yiwang@tencent.com)
//
#include "paralgo/base/common.h"
#include "gflags/gflags.h"
#include "paralgo/mapreduce_lite/flags.h"
#include "paralgo/mapreduce_lite/mapreduce_lite.h"

namespace mapreduce_lite {
bool IAmMapWorker();
bool Initialize();
void Finalize();
void MapWork();
void ReduceWork();
}  // namespace mapreduce_lite

//-----------------------------------------------------------------------------
// The pre-defined main function
//-----------------------------------------------------------------------------

int main(int argc, char** argv) {
  // Parse command line flags, leaving argc unchanged, but rearrange
  // the arguments in argv so that the flags are all at the beginning.
  google::ParseCommandLineFlags(&argc, &argv, false);

  if (!mapreduce_lite::Initialize()) {
    LOG(ERROR) << "Initialization of MapReduce Lite failed.";
    return -1;
  }

  LOG(INFO) << "I am a " << (mapreduce_lite::IAmMapWorker() ? "map worker" :
                             "reduce worker");

  if (mapreduce_lite::IAmMapWorker()) {
    mapreduce_lite::MapWork();
  } else {
    mapreduce_lite::ReduceWork();
  }

  mapreduce_lite::Finalize();
  return 0;
}
