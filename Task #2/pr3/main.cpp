//
//  main.cpp
//  pr3
//
//  Created by Даниил Смирнов on 27.09.16.
//  Copyright © 2016 Даниил Смирнов. All rights reserved.
//
// Условия задачи:
// Напишите программу mysubst, имеющую три аргумента: строку s1, строку s2 и имя файла, которая выводит содержимое файла, заменяя подстроки s1 на s2. Пример вызова: ./mysubst Миша Мишутка test.txt

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {

    string contentOfFile = "";
    string firstStr = argv[1];
    string secondStr = argv[2];
    size_t position = 0;
    
    ifstream fin(argv[3], ios::out);

    if (!fin) {
        cout << "Error" << endl;
        return 1;
    }
    
    getline(fin, contentOfFile, '\0');
    
    if (!fin) {
        cout << "Error" << endl;
        return 1;
    }
    
    cout << contentOfFile << endl;
    fin.close();
    
    do {
        position = contentOfFile.find(firstStr);
        contentOfFile.erase(contentOfFile.begin() + position,
                            contentOfFile.begin() + firstStr.length() + position);
        contentOfFile.insert(position, secondStr);
        
    } while(contentOfFile.find(firstStr) != std::string::npos);
    
    cout << "finished content -> " << contentOfFile << endl;
    cout << "First str -> " << firstStr << endl;
    cout << "Second str -> " << secondStr << endl;
    
    return 0;
}
