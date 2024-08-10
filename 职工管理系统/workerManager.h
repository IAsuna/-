#pragma once			//��ֹͷ�ļ��ظ�����
#include<iostream>		//������������
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"
#include<fstream>

#define FILENAME "empFile.txt"

using namespace std;	//��׼�����ռ�
	
class WorkerManager
{
public:
	WorkerManager();	//���캯��

					
	void Show_Menu();	//�˵�����

	void exitSystem();	//�˳�ϵͳ

	void Add_Emp();		//���ְ��

	void save();		//�����ļ�

	int get_EmpNum();	///ͳ���ļ��е�����

	void init_Emp();	

	int IsExist(int id);	//�ж��Ƿ����

	void ShowEmp();			//չʾ

	void Del_Emp();			//ɾ��

	void Mod_Emp();			//�޸�

	void Find_Emo();		//����

	void Sort_Emp();

	void Clean_File();

	~WorkerManager();	//��������
public:

	int m_EmpNum;		//��¼ְ������

	Worker** m_EmpArray;//ְ������ָ��

	bool m_FileIsEmpty; //�ж��ļ��Ƿ�Ϊ��
};