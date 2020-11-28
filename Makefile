all: git

ROOT_PATH= $(shell pwd)

git:
	g++ src/main.cpp -w -o mygit

test:
	. tests/test_lca.sh
clean:
	@echo "Cleaning..."
	@rm -r mygit git