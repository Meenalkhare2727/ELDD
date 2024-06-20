cmd_/home/meenal/Desktop/ELDD/keyboard/keybrd.mod := printf '%s\n'   keybrd.o | awk '!x[$$0]++ { print("/home/meenal/Desktop/ELDD/keyboard/"$$0) }' > /home/meenal/Desktop/ELDD/keyboard/keybrd.mod
