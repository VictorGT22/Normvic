#!/bin/bash

cd "$HOME" || exit

# download github
git clone --recursive https://github.com/VictorGT22/Normvic.git

cd "$HOME"/Normvic || exit


alias_name="normvic"
alias_command="ls -l"

Verifica si el archivo .bashrc existe y no contiene ya el alias
if [ -f "$HOME/.bashrc" ] && !grep -qF "alias $alias_name=" "$HOME/.bashrc"; then
    echo "alias $alias_name=\"$alias_command\"" >> "$HOME/.bashrc"
    echo "Alias agregado al archivo .bashrc"
fi
exec "$SHELL"

