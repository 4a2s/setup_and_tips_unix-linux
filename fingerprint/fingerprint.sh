#!/bin/bash

FILE="/etc/pam.d/common-auth"
LINE="auth    sufficient  pam_fprintd.so"

# Vérifier si le script est exécuté en tant que root
if [[ $EUID -ne 0 ]]; then
    echo "Ce script doit être exécuté en tant que root. Utilisez sudo." >&2
    exit 1
fi

# Vérifier si la ligne est déjà présente
if grep -Fxq "$LINE" "$FILE"; then
    echo "L'empreinte digitale est déjà activée dans $FILE."
    exit 0
fi

# Ajouter la ligne en haut du fichier
TEMP_FILE=$(mktemp)
echo "$LINE" | cat - "$FILE" > "$TEMP_FILE" && mv "$TEMP_FILE" "$FILE"

echo "L'authentification par empreinte digitale a été ajoutée avec succès."
