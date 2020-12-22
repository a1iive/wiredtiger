//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

typedef void* OBJ;

#define MAX_MAP_SIZE 200
static uint64_t max_uint64 = ~(uint64_t)0;

typedef struct {
    uint64_t bucketValues_[MAX_MAP_SIZE];
    uint64_t size_;
    uint64_t maxBucketValue_;
    uint64_t minBucketValue_;
} HistogramBucketMapper;

int CreateHistogramBucketMapper(HistogramBucketMapper* mapper);
void DeleteHistogramBucketMapper(HistogramBucketMapper* mapper);

typedef struct {
    HistogramBucketMapper bucketMapper_;

    uint64_t min_;
    uint64_t max_;
    uint64_t num_;
    uint64_t sum_;
    uint64_t sum_squares_;
    uint64_t buckets_[MAX_MAP_SIZE]; // 109==BucketMapper::BucketCount()
    uint64_t num_buckets_;
} HistogramStat;

int CreateHistogramStat(HistogramStat* stat);
void DeleteHistogramStat(HistogramStat* stat);

typedef struct {
    void (*Clear)(OBJ impl);
    int (*Empty)(OBJ impl);
    void (*Add)(OBJ impl, uint64_t value);
    void (*Merge)(OBJ impl, OBJ other);
    char* (*ToString)(OBJ impl);
    double (*Median)(OBJ impl);
    double (*Percentile)(OBJ impl, double p);
    double (*Average)(OBJ impl);
    double (*StandardDeviation)(OBJ impl);
    uint64_t (*Sum)(OBJ impl);
    uint64_t (*Min)(OBJ impl);
    uint64_t (*Max)(OBJ impl);
} HistogramInterface;

typedef struct{
    bool init_;
    HistogramStat stats_;
    // lock_t lock_;
    HistogramInterface interface;
} HistogramImpl;

typedef struct{
  uint64_t count_put_req;
  uint64_t count_put_clock;
  uint64_t count_get_req;
  uint64_t count_get_clock;
  HistogramImpl hist_put_lat;
  HistogramImpl hist_get_lat;
} MyStatistic;

int CreateHistogramImpl(HistogramImpl *histogram_impl);
void DeleteHistogramImpl(HistogramImpl *histogram_impl);

void InitStatistic();