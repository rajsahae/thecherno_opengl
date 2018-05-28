#!/bin/bash -x

latest_episode=$1
next_episode=$2

latest_path=$(realpath "$latest_episode")
next_path=$(realpath "$next_episode")

latest_name=$(basename "$latest_path")
next_name=$(basename "$next_path")

cp -va "$latest_path" "$next_path"
rm -f "$next_path/opengl.session"
sed -e "s/$latest_name/$next_name/g" "$latest_path/opengl.session" > "$next_path/opengl.session"
