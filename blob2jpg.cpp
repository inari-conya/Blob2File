#include <iostream>
#include <fstream>
#include "blob2jpg.h"

blob2jpg::blob2jpg(string user, string passwd, string db){
	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, passwd, db);
	}
	catch (SQLException e) {
		cout <<e.getErrorCode()<<endl;
		cout << e.getMessage() << endl;
		exit(1);
	}
}

blob2jpg::~blob2jpg() {
	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
}

void blob2jpg::getjpg(string path, string sql) {
	int bloblen = 0;
	Blob tmpBlob(conn);
	unsigned char* buffer = NULL;
	ofstream out;
	string fname;

	pStmt = conn->createStatement(sql);
	if (NULL == pStmt) {
		cout<<"createStatement error.\n"<<endl;
		return;
	}

	try
	{
		ResultSet *rs = pStmt->executeQuery();
		while (rs->next()) {
			fname = path;
			if(rs->isNull(2)) {
				//cout<<"nothing in row"<<endl;
				continue;
			}

			fname += rs->getString(1);
			fname += ".jpg";
			//cout << fname << endl;

			tmpBlob = rs->getBlob(2);
			if(tmpBlob.isNull()) {
				tmpBlob.close();
				//cout<<"nothing in blob"<<endl;
				continue;
			}

			tmpBlob.open(OCCI_LOB_READONLY);
			bloblen = tmpBlob.length();
			buffer = new unsigned char[bloblen]();
			if(buffer == NULL) {
				cout<<"no enough memory"<<endl;
				continue;
			}
			tmpBlob.read(bloblen, buffer, bloblen, 1);
			tmpBlob.close();

			out.open(fname, ios::out|ios::binary);
			if (out.is_open()) {
				out.write((char*)buffer, bloblen);
				out.close();
				bloblen = 0;
				delete []buffer;
				buffer = NULL;
				continue;
			} else {
				cout<<"open file failed!"<<endl;
				bloblen = 0;
				delete []buffer;
				buffer = NULL;
				continue;
			}
		}
		pStmt->closeResultSet(rs);

		// ÖÕÖ¹Statement¶ÔÏó    
		conn->terminateStatement(pStmt);
	}
	catch (SQLException e) {
		cout << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
		exit(1);
	}
}

