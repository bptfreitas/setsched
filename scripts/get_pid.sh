#!/bin/bash

if [[ "$1" == "" ]]; then
    echo "Usage: $0 <Process name>"
    exit 1
fi

procname="$1"

ps axjf > processes.out

grep "$procname" processes.out | tee processes_matched.out