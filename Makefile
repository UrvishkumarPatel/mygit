all: git

ROOT_PATH= $(shell pwd)

git:
	@echo "Building mygit..."
	@g++ src/main.cpp -w -o mygit
	@echo "Installing mygit..."
	@sudo cp mygit /usr/local/bin/mygit

test:
	@echo "runing test_lca"
	. tests/test_lca.sh

clean:
	@echo "Cleaning..."
	@rm -r mygit git

uninstall: 
	@echo "uninstalling mygit..."
	@sudo rm /usr/local/bin/mygit
