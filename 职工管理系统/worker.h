#pragma once
#include<iostream>
#include<string>

using namespace std;

//员工基类
class Worker 
{
public:
	
	//显示信息
	virtual void showInfo() = 0;

	//获取岗位
	virtual string getDeptName() = 0;

	int m_Id;//职工编号
	string m_Name;//职工姓名
	int m_DeptId;//职工所在部门的名称
};
