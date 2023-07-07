#!/bin/bash

cd "$HOME" || exit

mkdir temp_____

cd temp_____ || exit
rm -rf normvic

# download github
git clone --recursive https://github.com/VictorGT22/NORMVIC.git

cp -r normvic "$HOME"

cd "$HOME" || exit
rm -rf temp_____

cd "$HOME"/normvic || exit


RC_FILE="$HOME/.zshrc"

if [ "$(uname)" != "Darwin" ]; then
	RC_FILE="$HOME/.bashrc"
	if [[ -f "$HOME/.zshrc" ]]; then
		RC_FILE="$HOME/.zshrc"
	fi
fi

echo "try to add alias in file: $RC_FILE"

# set up the alias
if ! grep "normvic=" "$RC_FILE" &> /dev/null; then
	echo "normvic alias not present"
	printf "\nalias normvic=%s/normvic/tester.sh\n" "$HOME" >> "$RC_FILE"
fi

exec "$SHELL"


