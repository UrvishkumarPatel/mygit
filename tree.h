#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <bits/stdc++.h>
using namespace std;

////////

  write_tree: function(_) {
    files.assertInRepo();
    return objects.writeTree(files.nestFlatTree(index.toc()));
  },
  def write_tree(){
      return writeTree(nestFlatTree(index_toc()));
  }

//////////////  

toc: function() {
    var idx = index.read();
    return Object.keys(idx)
      .reduce(function(obj, k) { return util.setIn(obj, [k.split(",")[0], idx[k]]); }, {});
  },

obj index_toc(){
    std::vector<string> keys, values;
    for(std::map<std::string, std::string>::iterator it = m.begin(); it != m.end(); ++it) {
        keys.push_back(it->first);
        values.push_back(it->second);
    }

    
}

/////////////
 nestFlatTree: function(obj) {
    return Object.keys(obj).reduce(function(tree, wholePath) {
      return util.setIn(tree, wholePath.split(nodePath.sep).concat(obj[wholePath]));
    }, {});
  },

  def nestFlatTree(obj){

  }
/////////////
//////////////////////////
bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

string key(string path, string stage){
    return path+","+stage;
}

// read: function() {
//     var indexFilePath = files.gitletPath("index");
//     return util.lines(fs.existsSync(indexFilePath) ? files.read(indexFilePath) : "\n")
//       .reduce(function(idx, blobStr) {
//         var blobData = blobStr.split(/ /);
//         idx[index.key(blobData[0], blobData[1])] = blobData[2];
//         return idx;
//       }, {});
//   },
std::map<std::string, std::string> idx;
std::map<std::string, std::string> read_index() {
    // ifstream inFile;
    // char *fileName = ".git\\index"
    // inFile.open(filename);

    //// consider input as array of lines ////////
    string lines[]= {"100644 e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 0       asjdk.txt",
                     "100644 9f225ac2e9be2ca7aa303fde7470e7e5130479c3 0       hello/hello.txt"};
    int nlines = *(&lines + 1) - lines; //2;
    

    for (int i = 0; i < nlines; i++)
    {
        string blobData[4];
        char *token = strtok(lines[i], " "); 
        blobData[0] = token;
        int j=1;
        while (token != NULL) 
        {
            token = strtok(NULL, " ");
            blobData[j++];
        }

        
        idx[key(blobData[0], blobData[1])] = blobData[2];
        
    }
    return idx;

}
///////

setIn: function(obj, arr) {
    if (arr.length === 2) {
      obj[arr[0]] = arr[1];
    } else if (arr.length > 2) {
      obj[arr[0]] = obj[arr[0]] || {};
      util.setIn(obj[arr[0]], arr.slice(1));
    }

    return obj;
  },


//////////////////








// class staged {
//   public:
//     string type_;
//     string mode;
//     string path;
//     string hash;
//     string* hashof(string path, string* hash){
//         hash_object(string content, string type)//todo
//         return &hash;
//     }

// };

