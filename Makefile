.PHONY: build
build:
	gcc src/*.c -Isrc -o webserver -O2

.PHONY: update
update:
	./update-server.sh "webserver"
	./update-server.sh "static"

.PHONY: clear
clear:
	rm webserver
