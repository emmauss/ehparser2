// ehparser2.cpp : Defines the entry point for the console application.
//
#include "cpprest/containerstream.h"
#include "cpprest/filestream.h"
#include "cpprest/http_client.h"
#include "cpprest/json.h"

#include "cpprest/producerconsumerstream.h"
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "sqlite3.h"
#include <fstream>
#include <string>
#include <sstream>
#include "callback.h"

using namespace std;
using namespace ::pplx;
using namespace utility;
using namespace concurrency::streams;

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;


static int parser(void *datam, int argc, char **argv, char **azColName);
static int extractgid(void *datam, int argc, char **argv, char **azColName);
static int extracttk(void *datam, int argc, char **argv, char **azColName);
static int mangaidex(void *datam, int argc, char **argv, char **azColName);
static int call(void *datam, int argc, char **argv, char **azColName);
//

//

//
//
//





int main(int argc , char* argv[])
{
//
	bool isOPENDB = false;
	int manDB = sqlite3_open("MangaDB.sqlite", &db);
	if (!manDB)
	{
		fprintf(stderr, "Opened database successfully\n");
		
		system("pause");
		
	}
	else
	{
		cout << "Database failed to open";
	}
//SQL select
	sql = "select title from manga";

	manDB = sqlite3_exec(db, sql, parser, (void*)datam, &zErrMsg);
	/*if (manDB!= SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}*/


	sql = "select MangaID from manga";

	manDB = sqlite3_exec(db, sql, mangaidex, (void*)datam, &zErrMsg);
	/*if (manDB != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}*/
	sqlite3_close(db);

	int ehview = sqlite3_open("data", &db);
	if (!ehview)
	{
		fprintf(stderr, "Opened database successfully\n");

		system("pause");

	}
	else
	{
		cout << "Database failed to open";
	}
	sql = "select gid from gallery";

	ehview = sqlite3_exec(db, sql, extractgid, (void*)datam, &zErrMsg);
	/*if (ehview != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}
	*/
	sql = "select token from gallery";

	ehview = sqlite3_exec(db, sql, extracttk, (void*)datam, &zErrMsg);
	/*if (ehview != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	/*else {
		fprintf(stdout, "Operation done successfully\n");
	}*/
	
	sqlite3_close(db);



	

//copy id and tokens
	for (int i = 0; i < counter; i++)
	{
		for (int m = 0; m < incre;m++)
		{
			if (store[i].gid == receipt[m].galleryid)
			{
				store[i].tk = receipt[m].token;
				
			}
		}
	}

	//URL forming
	
	for (int i = 0; i < counter;i++)
	{
		store[i].url = "http://exhentai.org/g/" + to_string(store[i].gid) + "/" + store[i].tk + "/";
		//cout << store[i].url  << endl;
		
		
	}
	
	// update queries
	int count2 = 0;
	manDB = sqlite3_open("MangaDB.sqlite", &db);
	for (int i = 0;i < counter; i++) {
		strtemp = store[i].names;
		strtemp.resize(6);
		//sqltemp = "UPDATE Manga SET GalleryURL='" + store[i].url + "' where GalleryURL IS null AND title LIKE'" + strtemp +"%'";
		sql = sqltemp.c_str();
		//cout << sql;
		sql = "update Manga set galleryurl = null where galleryurl  like '%//'";
		manDB = sqlite3_exec(db, sql, call, (void*)datam, &zErrMsg);
		if (manDB != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			cout << sql << endl;
			sqlite3_free(zErrMsg);
			count2++;
		}
		/*else {
			//fprintf(stdout, "Operation done successfully 7\n");
		}*/

		
	}
	cout << "There were " << count2 << " unsuccessful updates.";
	sqlite3_close(db);
//JSON requests
	//cout << store[1].gid << "\t" << store[1].mangaID;
	
	system("pause");
    return 0;
}



