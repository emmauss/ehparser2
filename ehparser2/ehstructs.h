#pragma once
#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;


struct mangadb {
	string names;
	long int gid;
	string tk;
	long int id;
	string url;
	string tag;
	long int mangaID;
	string temp;
};
struct ehviewer {
	const char *temp;
	long int galleryid;
	string token;
	long int iden;
	string gurl;
	string gtag;
};
ifstream input;
char *zErrMsg = 0;
ofstream output;
sqlite3 *db;
const char *sql;
const char* datam = "";
mangadb store[30000];
ehviewer receipt[30000];
int counter = 0;
int j = 0;
int k = 0;
int l = 0;
long int incre = 0;
long int addi = 0;
string request;
int h = 0;
long int count1 = 0;
string sqltemp;
string strtemp;