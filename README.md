# implement_git


### Note
To compile use ```g++ main.cpp -lz```


### open issues -
- Compression
  - Compress function must accommodate more data; must not be fixed size;
- Add
  - Index file adds multiple entries
- Commit
  - pointers issue in tree (Juggad kiya he abhi : lookup using hashSet) # ignore karo
  - tree object hash computation  #ignore
  - tree objects content sorting
  - Parent sha in commit content creating (multiple parent case remaining)
  - Check for overwriting of commit (decompress necessary)
  - Decorate commit object    
- where is ./git folder