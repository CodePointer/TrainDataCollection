#include "CStorage.h"

StorageModule::StorageModule()
{
	this->m_matFilePath = "";
	this->m_matFileName = "";
	this->m_matFileSuffix = "";
	this->m_storagePath = "";
}

StorageModule::~StorageModule()
{

}

bool StorageModule::Store(Mat * pictures, int num)
{

	// 判断参数是否合法
	if (num <= 0)
		return false;

	bool status = true;

	// 存储
	for (int i = 0; i < num; i++)
	{
		string IdxtoStr;
		if (num == 1) {
			IdxtoStr = "";
		}
		else {
			std::strstream ss;
			ss << i;
			ss >> IdxtoStr;
		}

		status = imwrite(
			this->m_matFilePath	
			+ this->m_matFileName 
			+ IdxtoStr
			+ this->m_matFileSuffix,
			pictures[i]);
		if (!status)
		{
			// 创建目录
			string temp = this->m_matFilePath;
			for (int x = 0; x < temp.length(); x++)
			{
				if (temp[x] == '/')
					temp[x] = '\\';
			}
			system((string("mkdir ") + temp).c_str());
			status = imwrite(
				this->m_matFilePath 
				+ this->m_matFileName
				+ IdxtoStr 
				+ this->m_matFileSuffix,
				pictures[i]);
		}
	}
	//if (num == 1)
	//{
	//	status = imwrite(this->m_storagePath, *pictures);
	//	if (!status)
	//	{
	//		// 创建目录
	//		string temp = this->m_matFilePath;
	//		for (int i = 0; i < temp.length(); i++)
	//		{
	//			if (temp[i] == '/')
	//				temp[i] = '\\';
	//		}
	//		system((string("mkdir ") + temp).c_str());
	//		status = imwrite(this->m_storagePath, *pictures);
	//	}
	//}
	//else
	//{
	//	for (int i = 0; i < num; i++)
	//	{
	//		status = imwrite(this->m_storagePath, pictures[i]);
	//		if (!status)
	//		{
	//			// 创建目录
	//			string temp = this->m_matFilePath;
	//			for (int i = 0; i < temp.length(); i++)
	//			{
	//				if (temp[i] == '/')
	//					temp[i] = '\\';
	//			}
	//			system((string("mkdir ") + temp).c_str());
	//			status = imwrite(this->m_storagePath, pictures[i]);
	//		}
	//	}
	//}

	if (!status)
	{
		ErrorHandling("StorageModule.Store->imwrite Error.");
	}

	return true;
}

// 设定存储目录
bool StorageModule::SetMatFileName(string matFilePath,
	string matFileName,
	string matFileSuffix)
{

	// 变更参数
	this->m_matFilePath = matFilePath;
	this->m_matFileName = matFileName;
	this->m_matFileSuffix = matFileSuffix;

	// Create folder
	fstream file;
	file.open(matFileName + "test.txt", ios::out);
	if (!file) {
		string temp = matFilePath;
		for (int i = 0; i < temp.length(); i++)
		{
			if (temp[i] == '/')
				temp[i] = '\\';
		}
		system((string("mkdir ") + temp).c_str());
	}
	file.close();
	
	return true;
}

bool StorageModule::CreateFolder(string FilePath)
{
	bool status = true;

	// Create a dir
	string temp = FilePath;
	for (int i = 0; i < temp.length(); i++) {
		if (temp[i] == '/') {
			temp[i] = '\\';
		}
	}
	system((string("mkdir ") + temp).c_str());

	return status;
}