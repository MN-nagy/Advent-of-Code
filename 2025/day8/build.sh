#!/bin/bash
set -xe

# Compile with useful flags
tsc --outDir compiled

node compiled/a.js
