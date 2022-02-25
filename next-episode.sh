#!/bin/bash

ROOT=$(dirname "$0")

latest_episode=$1
next_episode=$2

latest_path=$(realpath "$latest_episode")
next_path=$(realpath "$next_episode")

latest_name=$(basename "$latest_path")
next_name=$(basename "$next_path")

echo Copying "$latest_name -> $next_name"
cp --recursive "$latest_path" "$next_path"
if ! grep -q "$next_name" "$ROOT/meson.build" ;  then
  echo "subdir('$next_name')" >> "$ROOT/meson.build"
fi
