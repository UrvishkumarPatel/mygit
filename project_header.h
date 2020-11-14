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

using namespace std;


#define MAX_FILE_NAME_LENGTH 1024
#define REF_HEAD_PATH "git/refs/heads/"
#define GIT_PATH "git/"
#define HEAD_PATH "git/HEAD"
#define ROOT_PATH "."
#define PATH_INDEX "git/index"
#define TOKEN_NOS 10
#define git_dir "git"
#define ROOT_PATH "."
#define LOG_PATH "git/logs/refs/"
#define LOG_HEAD_PATH "git/logs/HEAD"
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

