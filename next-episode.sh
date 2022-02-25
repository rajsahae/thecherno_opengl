#!/bin/bash

latest_episode=$1
next_episode=$2

latest_path=$(realpath "$latest_episode")
next_path=$(realpath "$next_episode")

latest_name=$(basename "$latest_path")
next_name=$(basename "$next_path")

echo Copying "$latest_name -> $next_name"
cp --recursive "$latest_path" "$next_path"
rm -rf "$next_path"/{build,nbproject}
sed --in-place "s/$latest_name/$next_name/g" "$next_path/meson.build"
