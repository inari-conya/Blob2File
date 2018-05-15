#include "blob2jpg.h"
#include <iostream>

int main(int argc, char* argv[])
{
	string sql;
	if (argc > 1) {
		sql = string(argv[1]);
	} else {
		cout<<"please input sql"<<endl;
		system("pause");
		return 2;
	}
	//string sql = "select sjdh,zp from za.tb_wscp_photo where rownum<100"; 
	//第一个字段必须在该表中值唯一（必须无重复值，因为第一个字段的内容是图片名，如果有重复值，会出现先生成的图片被后来生成的图片覆盖的情况），第二个字段为blob字段名

	string name = "test";//登录名
	string pass = "test2018";//登录密码
	string srvName = "192.168.0.233:1521/test";//数据库地址:端口号/SID

	try{
		blob2jpg *demo = new blob2jpg(name, pass, srvName);
		demo->getjpg("D:\\xdh\\photo\\", sql);//第一个参数是生成图片的存放路径
		delete(demo);
	}
	catch (SQLException e) {
		cout << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
		return -1;
	}
	//system("pause");
	return 0;
}