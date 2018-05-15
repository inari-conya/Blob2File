#ifndef BLOB2JPG_H
#define BLOB2JPG_H

#ifndef OCCI_ORACLE
#include <occi.h>
#endif
#include <string>

using namespace std;
using namespace oracle::occi;

class blob2jpg
{
	private:

	Statement *pStmt;
	Environment *env;
	Connection *conn;

	public:

	blob2jpg(string user, string passwd, string db);

	~blob2jpg();

	void getjpg(string path, string sql);
};

#endif
