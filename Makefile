all: git

ROOT_PATH= $(shell pwd)

git:
	@echo "Building mygit..."
	@g++ src/main.cpp -w -o mygit
	# @sudo cp mygit /usr/local/bin/mygit
	# mkdir ../os_demo
	# cp -r tests/test_lca.sh tests/test.sh ../os_demo
test:
	@echo "runing test_lca"
	. tests/test_lca.sh

clean:
	@echo "Cleaning..."
	@rm -r mygit git

uninstall:
	@echo "uninstalling mygit..."
	@sudo rm /usr/local/bin/mygit
