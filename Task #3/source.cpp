//
//  source.cpp
//  pr31
//
//  Created by Даниил Смирнов on 01.11.16.
//  Copyright © 2016 Даниил Смирнов. All rights reserved.
//

#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
using namespace std;

void ListDirectory(char *spath) {
	
    DIR *d;
    struct dirent *myDirent;
    struct stat buf;
    int i = 0, j = 0;
	char size = '\0';
    char newNameOfFile[256] = "";
    char buferName[300] = "";
    char bufForStat[300] = "";
    char buferNewName[300] = "";
    char path[300] = "";
    string nameOfFile = "";
    string bufer = "";
    strcpy(path, spath);
    errno=0;
    
    if ((d = opendir(path)) != 0) {
        
        while((myDirent = readdir(d)) != NULL) {
            
            if (myDirent->d_type == DT_DIR) {
                if(strcmp(myDirent->d_name,".")!= 0 && strcmp(myDirent->d_name, "..") != 0){
                    strcat(path, "/");
                    strcat(path, myDirent->d_name);
                    ListDirectory(path);
                    strcat(path,spath);
                }
            }
            
            if(myDirent->d_type == DT_REG) {
                
                nameOfFile = myDirent->d_name;
                
                strcpy(bufForStat,path);
                strcat(bufForStat, "/");
                strcat(bufForStat, myDirent->d_name);
                
                for(i = 0; i < nameOfFile.length(); i++){
                    
                    if  (stat(bufForStat,&buf) != 0) {
                        cout << "Error in stat: " << strerror(errno) << endl;
                    }

                    j = 0;
                    strcpy(newNameOfFile, "");
					
                    if(nameOfFile[i] == '$') {
                        int b = 0, a = buf.st_size;
						
                        while(a > 0) {
                            b = a % 10;
                            size = b + '0';
                            newNameOfFile[j++] = size;
                            a /= 10;
                        }
						
                        if (buf.st_size == 0) {
                            newNameOfFile[j++] = '0';
                        }
                        
                        newNameOfFile[j] = 0;
                        bufer = newNameOfFile;
                        reverse(bufer.begin(), bufer.end());
                        nameOfFile.erase(nameOfFile.begin()+i, nameOfFile.begin()+i+1);
                        nameOfFile.insert(i,bufer);
                    }
                }
                strcpy(buferName, path);
                strcat(buferName, "/");
                strcat(buferName, myDirent->d_name);
                
                strcpy(buferNewName, path);
                strcat(buferNewName, "/");
                strcat(buferNewName, nameOfFile.c_str());
                
                if (rename(buferName,buferNewName) != 0) {
                    cout << "Error in rename: " << strerror(errno) << endl;
                }
            }
            errno = 0;
        }
        if (errno != 0) {
            cout << "Error in colsedir" << strerror(errno);
        }
        
        if(closedir(d) != 0) {
            cout << "Error in colsedir" << strerror(errno);
        }
        
    } else {
        cout << "Error in opendir" << strerror(errno) << endl;
    }
}


int main() {
    
    ListDirectory("/Users/Danil/Desktop/test");
    
    return 0;
}

