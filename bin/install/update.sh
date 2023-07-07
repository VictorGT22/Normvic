#!/bin/bash

cd "$HOME"/Normvic || exit

git fetch origin
git reset --hard origin
git submodule update --init

echo -e "\033[1;37mFrancinette is updated. You can use it again!\033[0m"

exec "$SHELL"
