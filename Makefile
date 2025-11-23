.PHONY: build
build:
	gcc src/*.c -Isrc -o webserver -O2

.PHONY: update
update:
	scp -i "$(HOME)/.key/ssh-key-frigo-server.key" "webserver" ubuntu@144.22.210.65:/home/ubuntu/
	scp -r -i "$(HOME)/.key/ssh-key-frigo-server.key" "static" ubuntu@144.22.210.65:/home/ubuntu/

.PHONY: clear
clear:
	rm webserver