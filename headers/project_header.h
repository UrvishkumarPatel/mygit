#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <libgen.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <ctime>
#include <regex> 

using namespace std;
unordered_set<string> IGNORE_ENTRIES;

#define PATH_COMMIT_COUNT "git/commit_count"
#define PATH_STASH_COUNT "git/stash_count"
#define MAX_FILE_NAME_LENGTH 1024
#define REF_HEAD_PATH "git/refs/heads/"
#define GIT_PATH "git/"
#define HEAD_PATH "git/HEAD"
#define ROOT_PATH "."
#define PATH_INDEX "git/index"
#define TOKEN_NOS 10
#define GIT_DIR "git"
#define ROOT_PATH "."
#define LOG_PATH "git/logs/refs/"
#define LOG_HEAD_PATH "git/logs/HEAD"

#define IGNORE_PATH ".gitignore"
#define MY_GIT "mygit"

// #include "checkDir.h"
#include "helper.h"
#include "rm.h"
#include "sha1.hpp"
// #include "zlib.h"
// #include "object.h"
#include "object2.h"
#include "init.h"
#include "commit.h"
#include "branch.h"
#include "checkout.h"
#include "merge.h"
#include "log.h"
#include "reset.h"
#include "stash.h"
