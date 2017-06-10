#!/bin/bash

set -e

export DEVICE=mecdug
export DEVICE_COMMON=e8-common
export VENDOR=htc

export DEVICE_BRINGUP_YEAR=2015

./../e8-common/extract-files.sh $@
