#!/bin/bash

cd "$HOME" || exit

# download github
git clone --recursive https://github.com/VictorGT22/Normvic.git

cd "$HOME"/Normvic || exit


alias_name="normvic"
alias_command="echo "$1""

##Verifica si el archivo .bashrc existe y no contiene ya el alias

if [[ -f "$HOME/.bashrc" ]]; then
    if ! grep -qF "alias $alias_name=" "$HOME/.bashrc"; then
        echo "alias $alias_name=\"$alias_command\"" >> "$HOME/.bashrc"
        echo "Alias added to the .bashrc file"
    else
        echo "Alias already exists in the .bashrc file"
    fi

else if [[ -f "$HOME/.zshrc" ]]; then
    if ! grep -qF "alias $alias_name=" "$HOME/.zshrc"; then
        echo "alias $alias_name=\"$alias_command\"" >> "$HOME/.zshrc"
        echo "Alias added to the .zshrc file"
    else
        echo "Alias already exists in the .zshrc file"
    fi
fi

exec "$SHELL"

