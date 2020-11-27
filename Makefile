all: git

ROOT_PATH= $(shell pwd)

git:
	g++ main.cpp -w -o mygit
	@export PATH=$$PATH:$(ROOT_PATH)/mygit
clean:
	@echo "Cleaning..."
	@rm -r mygit git