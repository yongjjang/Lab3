#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void recursion_dir(const char *name){
    DIR *dir;
    struct dirent *entry;
    char temp[20][100];
    char *dir_path[20];
    int i=0, k=0;
    
    for(int m = 0; m<20; m++)
        dir_path[m] = NULL;// block segmentation fault
    for(int b = 0; b<20; b++){
        for(int n = 0; n<100; n++)
            temp[b][n] = NULL;
    }
    if (!(dir = opendir(name)))
        return;

    printf("%s: \n", name);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".git") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            for(int c = 0; c< strlen(path); c++){
                temp[i][c] = path[c];
            }
            dir_path[i] = temp[i];
            i++;
            printf("%s%5s", dir_path[i-1], "");
        }else {
            printf("%s%5s", entry->d_name, "");
        }
    }  
    printf("\n\n");
    while(dir_path[k] != NULL){
        if(dir_path[k] == NULL) break;
        recursion_dir(dir_path[k]);
        k++;
    }
    closedir(dir);
}

int main(void) {
    recursion_dir(".");
    return 0;
}
