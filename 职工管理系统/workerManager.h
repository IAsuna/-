#pragma once			//防止头文件重复包含
#include<iostream>		//基本输出输出流
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"
#include<fstream>

#define FILENAME "empFile.txt"

using namespace std;	//标准命名空间
	
class WorkerManager
{
public:
	WorkerManager();	//构造函数

					
	void Show_Menu();	//菜单函数

	void exitSystem();	//退出系统

	void Add_Emp();		//添加职工

	void save();		//保存文件

	int get_EmpNum();	///统计文件中的人数

	void init_Emp();	

	int IsExist(int id);	//判断是否存在

	void ShowEmp();			//展示

	void Del_Emp();			//删除

	void Mod_Emp();			//修改

	void Find_Emo();		//查找

	void Sort_Emp();

	void Clean_File();

	~WorkerManager();	//析构函数
public:

	int m_EmpNum;		//记录职工人数

	Worker** m_EmpArray;//职工数组指针

	bool m_FileIsEmpty; //判断文件是否为空
};