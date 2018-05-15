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
	//��һ���ֶα����ڸñ���ֵΨһ���������ظ�ֵ����Ϊ��һ���ֶε�������ͼƬ����������ظ�ֵ������������ɵ�ͼƬ���������ɵ�ͼƬ���ǵ���������ڶ����ֶ�Ϊblob�ֶ���

	string name = "test";//��¼��
	string pass = "test2018";//��¼����
	string srvName = "192.168.0.233:1521/test";//���ݿ��ַ:�˿ں�/SID

	try{
		blob2jpg *demo = new blob2jpg(name, pass, srvName);
		demo->getjpg("D:\\xdh\\photo\\", sql);//��һ������������ͼƬ�Ĵ��·��
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