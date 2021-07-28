// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Simulates a producer and a consumer that share a bounded buffer

#ifndef CONSUMER_H
#define CONSUMER_H

#include <stdbool.h>
#include <stdio.h>
#include "goldbach_calculator.h"
#include "common.h"

void* consume(void* data);

#endif  // CONSUMER_H
