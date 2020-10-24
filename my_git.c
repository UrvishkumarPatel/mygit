#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
char *update_path(char *ori_path,char *dir){
    char *new_path=malloc(strlen(ori_path)+strlen("/")+strlen(dir)+1);
    strcpy(new_path,ori_path);
    strcat(new_path,"/");
    strcat(new_path,dir);
    return new_path;
}
int init(int argc, char* argv[]){
    char *my_git_name=".git";
    //0777 is for owner group and one who have permission to read and write
    if(argc==2){
        if(mkdir(my_git_name,0777)==-1){
            //Git reposistory already exists
            printf("Reinitialised existing Git repository");
            return 1;
        }
        char *path_obj=update_path(my_git_name,"objects");
        mkdir(path_obj,0777);
        char *path_info=update_path(path_obj,"info");
        mkdir(path_info,0777);
        char *path_pack=update_path(path_obj,"pack");
        mkdir(path_pack,0777);
        char *path_config=update_path(my_git_name,"config");
        mkdir(path_config,0777);
        char *path_des=update_path(my_git_name,"description");
        mkdir(path_des,0777);
        char *path_head=update_path(my_git_name,"HEAD");
        mkdir(path_head,0777);
        char *path_refs=update_path(my_git_name,"refs");
        mkdir(path_refs,0777);
        char *path_heads=update_path(path_refs,"heads");
        mkdir(path_heads,0777);
        char *path_tags=update_path(path_refs,"tags");
        mkdir(path_tags,0777);

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
                char *path_dir=update_path("./",argv[2]);
                char *path_git=update_path(path_dir,my_git_name);
                if(mkdir(path_git,0777)==-1){
                        //Git reposistory already exists
                        printf("Reinitialised existing Git repository");
                        return 1;
                }
                //subdirectories
                char *path_obj=update_path(path_git,"objects");
                mkdir(path_obj,0777);
                char *path_info=update_path(path_obj,"info");
                mkdir(path_info,0777);
                char *path_pack=update_path(path_obj,"pack");
                mkdir(path_pack,0777);
                char *path_config=update_path(path_git,"config");
                mkdir(path_config,0777);
                char *path_des=update_path(path_git,"description");
                mkdir(path_des,0777);
                char *path_head=update_path(path_git,"HEAD");
                mkdir(path_head,0777);
                char *path_refs=update_path(path_git,"refs");
                mkdir(path_refs,0777);
                char *path_heads=update_path(path_refs,"heads");
                mkdir(path_heads,0777);
                char *path_tags=update_path(path_refs,"tags");
                mkdir(path_tags,0777);
                
            }
        }
        else{
            //
            char *path_dir=update_path("./",argv[2]);
            mkdir(path_dir,0777);
            char *path_git=update_path(path_dir,my_git_name);
            if(mkdir(path_git,0777)==-1){
                    //Git reposistory already exists
                    printf("Reinitialised existing Git repository");
                    return 1;
            }
            //subdirectories
            char *path_obj=update_path(path_git,"objects");
            mkdir(path_obj,0777);
            char *path_info=update_path(path_obj,"info");
            mkdir(path_info,0777);
            char *path_pack=update_path(path_obj,"pack");
            mkdir(path_pack,0777);
            char *path_config=update_path(path_git,"config");
            mkdir(path_config,0777);
            char *path_des=update_path(path_git,"description");
            mkdir(path_des,0777);
            char *path_head=update_path(path_git,"HEAD");
            mkdir(path_head,0777);
            char *path_refs=update_path(path_git,"refs");
            mkdir(path_refs,0777);
            char *path_heads=update_path(path_refs,"heads");
            mkdir(path_heads,0777);
            char *path_tags=update_path(path_refs,"tags");
            mkdir(path_tags,0777);
        }
    }        

}
        
int main(int argc, char* argv[]){
    if(strcmp(argv[1],"init")==0){
        init(argc,argv);
    }
}
