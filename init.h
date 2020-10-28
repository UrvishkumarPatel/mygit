#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

int init(int argc, char* argv[]){
    string my_git_name="git";
    //0777 is for owner group and one who have permission to read and write
    if(argc==2){
        if(mkdir("git",0777)==-1){
            //Git reposistory already exists
            printf("Reinitialised existing Git repository in");
            return 1;
        }
        string path_obj=my_git_name + "/" +"objects";
        const char *path_o=path_obj.c_str();
        mkdir(path_o,0777);
        string path_info=path_obj+"/"+"info";
        const char *path_i=path_info.c_str();
        mkdir(path_i,0777);
        string path_pack=path_obj+"/"+"pack";
        const char *path_p=path_pack.c_str();
        mkdir(path_p,0777);
        fstream config;
        string path_config=my_git_name + "/" +"config";
        const char *path_c=path_config.c_str();

        config.open(path_c,ios::out);
        fstream des;
        string my_file=my_git_name+"/"+"description";
        const char *file=my_file.c_str();
        des.open(file,ios::out);
        fstream des1;
        string my_file1=my_git_name+"/"+"index";
        const char *file1=my_file1.c_str();
        des1.open(file1,ios::out);
        fstream Head;
        string path_head=my_git_name + "/" +"Head";
        const char *path_h=path_head.c_str();
        Head.open(path_h,ios::out);
        string path_refs=my_git_name + "/" +"refs";
        const char *path_r=path_refs.c_str();
        mkdir(path_r,0777);
        string path_heads=path_refs + "/" +"heads";
        const char *path_hs=path_heads.c_str();
        mkdir(path_hs,0777);
        string path_tags=path_refs + "/" +"tags";
        const char *path_t=path_tags.c_str();
        mkdir(path_t,0777);

    }
    else{
        //check if argc==2 is directory or not
        //if directory
            //create git repository
        struct stat fb;
        if(stat(argv[2],&fb)==0){
            if(S_ISDIR(fb.st_mode)!=1){
                printf("Error");
                return 1;
            }
            else{
                string dir=argv[2];
                string path=dir+"/"+my_git_name;
                const char *path_git=path.c_str();
                //printf("%s",path);
                if(mkdir(path_git,0777)==-1){
                        //Git reposistory already exists
                        printf("Reinitialised existing Git repository in");
                        return 1;
                }
                //subdirectories
                string path_obj=path + "/" +"objects";
                const char *path_o=path_obj.c_str();
                mkdir(path_o,0777);
                string path_info=path_obj+"/"+"info";
                const char *path_i=path_info.c_str();
                mkdir(path_i,0777);
                string path_pack=path_obj+"/"+"pack";
                const char *path_p=path_pack.c_str();
                mkdir(path_p,0777);
                fstream config;
                string path_config=path + "/" +"config";
                const char *path_c=path_config.c_str();
                config.open(path_c,ios::out);

                fstream des;
                string my_file=path+"/"+"description";
                const char *file=my_file.c_str();
                des.open(file,ios::out);
                fstream des1;
                string my_file1=path+"/"+"index";
                const char *file1=my_file1.c_str();
                des1.open(file1,ios::out);
                fstream Head;
                string path_head=path + "/" +"Head";
                const char *path_h=path_head.c_str();
                Head.open(path_h,ios::out);
                string path_refs=path + "/" +"refs";
                const char *path_r=path_refs.c_str();
                mkdir(path_r,0777);
                string path_heads=path_refs + "/" +"heads";
                const char *path_hs=path_heads.c_str();
                mkdir(path_hs,0777);
                string path_tags=path_refs + "/" +"tags";
                const char *path_t=path_tags.c_str();
                mkdir(path_t,0777);

            }
        }
        else{
            //

            string dir=argv[2];
            mkdir(argv[2],0777);
            string path=dir+"/"+my_git_name;
            const char *path_git=path.c_str();
            if(mkdir(path_git,0777)==-1){
                    //Git reposistory already exists
                    printf("Reinitialised existing Git repository in");
                    return 1;
            }
            //subdirectories
            string path_obj=path + "/" +"objects";
            const char *path_o=path_obj.c_str();
            mkdir(path_o,0777);
            string path_info=path_obj+"/"+"info";
            const char *path_i=path_info.c_str();
            mkdir(path_i,0777);
            string path_pack=path_obj+"/"+"pack";
            const char *path_p=path_pack.c_str();
            mkdir(path_p,0777);
            fstream config;
            string path_config=path + "/" +"config";
            const char *path_c=path_config.c_str();
            config.open(path_c,ios::out);

            fstream des;
            string my_file=path+"/"+"description";
            const char *file=my_file.c_str();
            des.open(file,ios::out);
            fstream des1;
            string my_file1=path+"/"+"index";
            const char *file1=my_file1.c_str();
            des1.open(file1,ios::out);
            fstream Head;
            string path_head=path + "/" +"Head";
            const char *path_h=path_head.c_str();
            Head.open(path_h,ios::out);
            string path_refs=path + "/" +"refs";
            const char *path_r=path_refs.c_str();
            mkdir(path_r,0777);
            string path_heads=path_refs + "/" +"heads";
            const char *path_hs=path_heads.c_str();
            mkdir(path_hs,0777);
            string path_tags=path_refs + "/" +"tags";
            const char *path_t=path_tags.c_str();
            mkdir(path_t,0777);
        }
    }

}