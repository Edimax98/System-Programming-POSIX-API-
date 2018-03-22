//
//  main.cpp
//  пр№1
//
//  Created by Даниил Смирнов on 20.09.16.
//  Copyright © 2016 Даниил Смирнов. All rights reserved.
//

//
//  main.cpp
//  пр№1
//
// Условия задачи:
// В именах обычных файлов заменить символ $ на длину файла.

#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
using namespace std;

int main() {
	DIR *d;
	struct dirent *myDirent;
	struct stat buf;
	
	if ((d = opendir(".")) != 0) {
		
		char size = '\0';
		int i = 0, j = 0;
		char newNameOfFile[256] = "";
		string nameOfFile = "";
		string bufer = "";
		errno=0;
		
		while((myDirent = readdir(d)) != NULL) {
			
			if(myDirent->d_type == DT_REG) {
				
				nameOfFile = myDirent->d_name;
				
				for(i = 0; i < nameOfFile.length(); i++){
					
					if  (stat(myDirent->d_name,&buf) != 0) {
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
							cout << newNameOfFile[j];
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
				
				if (rename(myDirent->d_name,nameOfFile.c_str()) != 0) {
					cout << "Error in rename: " << strerror(errno) << endl;
				}
			}
			errno = 0;
		}
		if (errno != 0) {
			cout << "Error in colsedir" << strerror(errno);
		}
		
	} else {
		cout << "Error in opendir" << strerror(errno);
	}
	if(closedir(d) != 0) {
		cout << "Error in colsedir" << strerror(errno);
	}
	return 0;
}

