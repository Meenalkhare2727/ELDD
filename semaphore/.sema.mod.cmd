cmd_/home/meenal/Desktop/ELDD/semaphore/sema.mod := printf '%s\n'   sema.o | awk '!x[$$0]++ { print("/home/meenal/Desktop/ELDD/semaphore/"$$0) }' > /home/meenal/Desktop/ELDD/semaphore/sema.mod
