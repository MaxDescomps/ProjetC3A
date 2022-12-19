OBJ="obj"
BIN="bin"
SAVE="saves"

if [ -d "$OBJ" ]; then
  echo "Le dossier ${OBJ} existe bien !"
else
  echo "Création du dossier ${OBJ}"
  mkdir ${OBJ}
fi

if [ -d "$BIN" ]; then
  echo "Le dossier ${BIN} existe bien !"
else
  echo "Création du dossier ${BIN}"
  mkdir ${BIN}
fi

if [ -d "$SAVE" ]; then
  echo "Le dossier ${SAVE} existe bien !"
else
  echo "Création du dossier ${SAVE}"
  mkdir ${SAVE}
fi