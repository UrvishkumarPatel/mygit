## first checkpoint
- [ ] init
    - [ ] create subdirectories
    - [ ] create files
    -  can be implemeted independently
- [ ] objects
  - [ ]  blob
       - [ ] need the **hash-object** to be implemented before
          - undstand zlib and use it
       -  can be implemented independently

  - [ ] tree
       - tuple size 3 data strucute
       - has refferece to **blobs** and **tree**

  - [ ] commit
      - two objects are created -- **commit** and **tree**
      - how/ where is the data saved? will be handy while ***checkout***
      - needs **tree** object