# mygit (simple git implementation)

This is our implementation of git using C and C++. 
We have implemented the following commands (flags not included):-

- init
- add
- commit
- branch
- checkout
- merge
- log
- reflog
- stash
- reset
- included support for ".gitignore" file

## Git objects
Everything in git is stored in form of objects.
There are mainly 3 types of objects:-

- blob
- tree
- commit

![Git objects](img/0005.jpg "Git objects")

## **mygit** init
Initialise a new git repository 
![mygit init](img/0007.jpg "mygit init")

## **mygit** add <dir/file>
Add files to staging area.
![mygit add](img/0008.jpg "mygit add")

## Index file
File to represent the staging area
![Index file](img/0009.jpg "Index file")

## **mygit** commit -m "commit message"
Commit the changes in staging area. A new commit object and tree structure is created accordingly.
![mygit commit](img/0012.jpg "mygit commit")

## **mygit** branch <branch_name>
Create a new branch, if not specified print all branches
![mygit branch](img/0014.jpg "mygit branch")
## **mygit** checkout <branch_name>
Checkout to the branch_name
![mygit checkout](img/0016.jpg "mygit commit")
## **mygit** stash -m "stash message"
Stash the contents of staging area if we do not want to commit
``` stash ```
![stash](img/0018.jpg "stash")
``` stash pop```
![stash pop](img/0019.jpg "stash pop")

## **mygit** merge <branch_name>
Merge the contents of current branch with the branch specified
```Fast Forward Merge```
![Alt text](img/0021.jpg "fast forward merge")
``` Three Way Merge```
![Alt text](img/0023.jpg "Three way merge")
## **mygit** log 
Gives the information about all the commits done by the user of current branch.
![log](img/0025.jpg "log")
## **mygit** reflog
Gives information about merges, checkouts, commits done by user till that point.
![reflog](img/0026.jpg "reflog")


### Setup
#### clone the project --
```
git clone https://github.com/UrvishkumarPatel/mygit.git
```
#### Install **mygit** 
```
 run make
```


### Usage

-  [x] **mygit init** :-Initialises the git reposistory
-  [x] **mygit add <dir/file>**:-Adds the file in the stagging area(Index file)
-  [x] **mygit commit -m "commit message"**:-Commits the added file with the message given.
-  [x] **mygit branch <branch_name>**:- Creates a new branch with branch name.
-  [x] **mygit checkout <branch_name>**:- Checkouts to the branch specified.
-  [x] **mygit merge <branch_name>**:- Merges current branch with specified branch.
-  [x] **mygit log <branch_name>**:- Gives the information about all the commits done by the user of current branch.
-  [x] **mygit reflog <branch_name>**:-Gives information about merges, checkouts, commits done by user till that point.
-  [x] **mygit stash -m "commit message"**:- Stash the contents of the staging area, commit is not required after that.

## Note
```
Files specified in .gitignore are ignored while adding and commiting
```
