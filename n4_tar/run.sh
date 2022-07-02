#!/bin/bash

echo Enter the number of threads:
read N

OMP_NUM_THREADS=$N ./task4

