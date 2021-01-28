#pragma once
#include "Define.h"
//常用函数模板，操作对象为数组
template<typename T>	/*计算数组平均值*/
T Ave(T* ptrArr, unsigned CntArr)
{
	if (CntArr != 0)
	{
		T Sum(0);
		for (unsigned i = 0; i < CntArr; i++)  Sum = Sum + (*(ptrArr + i));
		return Sum / CntArr;
	}
	else return 0;
}
template<typename T> /*计算数组标准偏差*/
T SDev(T* ptrArr, unsigned CntArr)
{
	T AveVal(0);
	AveVal = Ave(ptrArr, CntArr);
	if (CntArr != 0)
	{
		T Sum(0);
		for (unsigned i = 0; i < CntArr; i++) 	Sum = Sum + sqrt((*(ptrArr + i) - AveVal) * (*(ptrArr + i) - AveVal));
		return Sum / CntArr;
	}
	else return 0;
}
template<typename T> /*计算数组最大值*/
T Max(T* ptrArr, unsigned CntArr)
{
	T MaxVal(0);
	if (CntArr != 0)
	{
		MaxVal = (*ptrArr);
		for (unsigned i = 1; i < CntArr; i++)		if ((*(ptrArr + i)) >= MaxVal) MaxVal = (*(ptrArr + i));
		return MaxVal;
	}
	else return 0;
}
template<typename T>  /*计算数组最小值*/
T Min(T* ptrArr, unsigned CntArr)
{
	T MinVal(0);
	if (CntArr != 0)
	{
		MinVal = (*ptrArr);
		for (unsigned i = 1; i < CntArr; i++)  if ((*(ptrArr + i)) <= MinVal) MinVal = (*(ptrArr + i));
		return MinVal;
	}
	else return 0;
}
template<typename T>  /*查找数组中间值*/
T Mid(T* ptrArr, unsigned CntArr)
{
	if (CntArr != 0)
	{
		T MaxVal(0), MinVal(0), Medium(0);
		MaxVal = Max(ptrArr, CntArr);
		MinVal = Min(ptrArr, CntArr);
		Medium = (MaxVal + MinVal) / 2;
		vector<T>  DiffArr(CntArr);
		for (unsigned i = 0; i < CntArr; i++)
		{
			DiffArr[i] = (*(ptrArr + i)) - Medium;
			if (DiffArr[i] < 0)  DiffArr[i] = -DiffArr[i];
		}
		unsigned MinPos(0);
		MinVal = DiffArr[0];
		for (unsigned i = 1; i < CntArr; i++)
		{
			if (DiffArr[i] <= MinVal)
			{
				MinVal = DiffArr[i];
				MinPos = i;
			}
		}
		return *(ptrArr + MinPos);
	}
	else return 0;
}
template<typename T> /*化上三角法计算行列式*/
T Det(T* ptrArr, unsigned N)
{
	int Negative(1);
	vector<T> X;

	if (N == 0) return 0;
	else if (N == 1)	return *ptrArr;
	else if (N == 2)	return (*ptrArr) * (*(ptrArr + 3)) - (*(ptrArr + 1)) * (*(ptrArr + 2));
	else if (N == 3)  return (*ptrArr) * (*(ptrArr + 4)) * (*(ptrArr + 8)) + (*(ptrArr + 1)) * (*(ptrArr + 5)) * (*(ptrArr + 6)) + (*(ptrArr + 2)) * (*(ptrArr + 3)) * (*(ptrArr + 7)) - (*(ptrArr + 2)) * (*(ptrArr + 4)) * (*(ptrArr + 6)) - (*ptrArr) * (*(ptrArr + 5)) * (*(ptrArr + 7)) - (*(ptrArr + 1)) * (*(ptrArr + 3)) * (*(ptrArr + 8));
	else
	{
		vector<T> Y(N * N);
		for (unsigned i = 0; i < N * N; i++) Y[i] = (*(ptrArr + i));
		for (unsigned i = 0; i < N - 1; i++)/*进行N-1次循环，循环变量是当前所在行号*/
		{
			if (fabs(Y[i * N + i]) < dbZero)/*当前余子式第1个元素为0时，寻找同一行中不为0的列，并进行列互换*/
			{
				bool zeroFlag(false);
				for (unsigned j = i * N + i + 1; j < (i + 1) * N; j++)
				{
					if (fabs(Y[j]) > dbZero)
					{
						T tempVal(0);
						for (unsigned k = 0; k < N; k++)
						{
							tempVal = Y[k * N + i];
							Y[k * N + i] = Y[k * N + j];
							Y[k * N + j] = tempVal;
						}
						Negative = -Negative;
						X.push_back(Y[i * N + i]);
						zeroFlag = true;
						break;
					}
				}
				if (!zeroFlag)
				{
					X.push_back(0);
					break;
				}
			}
			else/*当前余子式第1个元素不为0时，从下一行开始，将余子式第1列的元素全部化为0*/
			{
				X.push_back(Y[i * N + i]);
				for (unsigned j = i + 1; j < N; j++)
				{
					T ConstVal(Y[j * N + i]);
					for (unsigned k = 0; k < N; k++)
					{
						Y[j * N + k] = (Y[j * N + k]) - (Y[i * N + k]) * ConstVal / (Y[i * N + i]);
					}
				}
			}
		}
		X.push_back(Y[N * N - 1]);
		for (unsigned i = 1; i < X.size(); i++) X[0] = X[0] * X[i];
		return Negative * X[0];
	}
}
template<typename T>/*矩阵方程求解*/
vector<T> Matrix(T* ptrA, T* ptrB, unsigned N)
{
	vector<T> X;
	vector<T> TP;
	T DetVal = Det(ptrA, N);
	for (unsigned i = 0; i < N * N; i++) TP.push_back(*(ptrA + i));
	for (unsigned i = 0; i < N; i++)
	{
		for (unsigned j = 0; j < N; j++) TP[j * N + i] = *(ptrB + j);
		X.push_back(Det(&TP[0], N) / DetVal);
		for (unsigned j = 0; j < N; j++) TP[j * N + i] = *(ptrA + j * N + i);
	}
	return X;
}
//数据标识转换
IDN    IDNTrans(string& Name)
{
	IDN ReVal;
	stringstream sin(Name);
	double x(0);
	if (!(sin >> x))
	{
		bool rFlag(false);
		for (size_t i = size_t(IDN::C); i < size_t(IDN::IDFail); i++)
		{
			if (Name == pairID[i - 1].second)
			{
				rFlag = true;
				ReVal = pairID[i - 1].first;
			}
		}
		if (!rFlag) ReVal = IDN::IDFail;
		return ReVal;
	}
	else
	{
		return IDN(stod(Name));
	}
}
template <typename decimalType>
string IDNTrans(decimalType objDecimal)
{
	IDN Name;
	Name = IDN(objDecimal);
	string ReVal;
	bool rFlag(false);

	for (size_t i = size_t(IDN::C); i < size_t(IDN::IDFail); i++)
	{
		if (Name == pairID[i - 1].first)
		{
			rFlag = true;
			ReVal = pairID[i - 1].second;
		}
	}
	if (!rFlag) ReVal = pairID[pairID.size() - 1].second;
	return ReVal;
}
//元数据操作函数
DataCell::DataCell() :Lable(lblCnt), Val(0)
{
	for (unsigned i = 0; i < lblCnt; i++) Lable[i] = IDN::Empty;
}
size_t        DataCell::size() const
{
	return Lable.size() + size_t(1);
}
DataCell& DataCell::operator=(string& dataStr)
{
	vector<char> noBlank;
	bool valFlag(false);
	bool quiryFlag(false);
	for (size_t i = 0; i < dataStr.size(); i++) /*去除字符串中的空格并记录是否有数据标记*/
	{
		if (dataStr[i] != ' ') noBlank.push_back(dataStr[i]);
		if (dataStr[i] == valDev) valFlag = true;
		if (dataStr[i] == quiryDev) quiryFlag = true;
	}
	if (noBlank.size() < 1)/*dataStr全为无效字符时*/
	{
		Val = 0;
		for (size_t i = 0; i < lblCnt; i++) Lable[i] = IDN::Empty;
	}
	else
	{
		if (quiryFlag)/*指定位置赋值时*/
		{
			string strPos(""), strVal("");
			size_t quiryPos(noBlank.size());
			for (size_t i = 0; i < noBlank.size(); i++)
			{
				if (noBlank[i] == quiryDev) quiryPos = i;
				if (i < quiryPos) strPos = strPos + noBlank[i];
				else if (i > quiryPos) strVal = strVal + noBlank[i];
			}
			stringstream checkStr1(strPos), checkStr2(strVal);
			double x(0);
			if (checkStr1 >> x && checkStr2 >> x)
			{
				size_t Pos(size_t(stod(strPos)));
				if (strVal == "") strVal = "0";
				if (Pos > 0 && Pos <= lblCnt) Lable[Pos - 1] = IDN(stod(strVal));
			}
			else
			{
				for (size_t i = 0; i < lblCnt; i++) Lable[i] = IDN::IDFail;
			}
		}
		else/*整体赋值时*/
		{
			string strLbl(""), strVal(""), strT("");
			if (valFlag)/*当字符串中有数据标记时*/
			{
				for (size_t i = 0; i < noBlank.size(); i++) strT = strT + noBlank[i];
				strVal = strT.substr(strT.find(valDev) + 1);
				strLbl = strT.substr(0, strT.find(valDev));
			}
			else
			{
				for (size_t i = 0; i < noBlank.size(); i++) strT = strT + noBlank[i];
				strVal = "";
				strLbl = strT;
			}
			//解析数据标签
			if (noBlank[noBlank.size() - 1] != lblDev) strLbl = strLbl + lblDev;
			size_t k(0);
			strT = "";
			for (size_t i = 0; i < strLbl.size(); i++)
			{
				if (strLbl[i] != lblDev)
				{
					strT = strT + strLbl[i];
				}
				else
				{
					if (strT == "")	strT = emptyStr;
					if (k < lblCnt)	Lable[k] = IDNTrans(strT);
					k++;
					strT = "";
				}
			}
			//解析数据数值
			if (strVal == "") Val = 0;
			else
			{
				bool Flag(false);
				for (int i = int(Lable.size()) - 1; i >= 0; i--)
				{
					if (Lable[i] == IDN::MElem1 || Lable[i] == IDN::MElem2 || Lable[i] == IDN::GasType)
					{
						Flag = true;
						break;
					}
				}
				//对值赋值
				if (!Flag) Val = stod(strVal);
				else Val = double(IDNTrans(strVal));
			}
		}
	}
	return *this;
}
DataCell& DataCell::operator=(DataCell& objData)
{
	this->Val = objData[0];
	for (size_t i = 1; i < this->size(); i++)
	{
		Lable[i - 1] = IDN(objData[i]);
	}
	return *this;
}
DataCell& DataCell::operator=(double dataVal)
{
	Val = dataVal;
	return *this;
}
double      DataCell::operator [] (size_t Index) const
{
	double reVal(0);

	if (Index < this->size() && Index > 0) reVal = double(Lable[Index - 1]);
	else if (Index == 0)                               reVal = Val;

	return reVal;
}
double      DataCell::operator+(double& objVal)
{
	return Val + objVal;
}
double      DataCell::operator-(double& objVal)
{
	return Val - objVal;
}
double      DataCell::operator*(double& objVal)
{
	return Val * objVal;
}
double      DataCell::operator/(double& objVal)
{
	if (fabs(objVal) > dbZero) return Val / objVal;
	else return dbFail;
}
bool          DataCell::operator==(DataCell& objCell) const
{
	bool reVal(false);
	if (fabs(objCell.Val - this->Val) < dbZero)
	{
		bool Flag(true);
		for (size_t i = 1; i < objCell.size(); i++)
		{
			if (IDN(objCell[i]) != this->Lable[i] && IDN(objCell[i]) != IDN::Empty)
			{
				Flag = false;
				break;
			}
		}
		if (Flag) reVal = true;
	}
	return reVal;
}
bool          DataCell::operator==(string& objStr) const
{
	DataCell objCell;
	objCell = objStr;
	return (*this == objCell);
}
bool          DataCell::operator>(double& objVal) const
{
	if (this->Val > objVal) return true;
	else return false;
}
bool          DataCell::operator<(double& objVal) const
{
	if (this->Val < objVal) return true;
	else return false;
}
bool          DataCell::operator>=(double& objVal) const
{
	if (this->Val >= objVal) return true;
	else return false;
}
bool          DataCell::operator<=(double& objVal) const
{
	if (this->Val <= objVal) return true;
	else return false;
}
bool          DataCell::Set(IDN objVal, size_t Seq)
{
	if (Seq >= 1 && Seq < this->size()) Lable[Seq] = objVal;
	else if (Seq == 0) Val = double(objVal);
	return true;
}
//元数据向量操作函数
bool DataOpe::BuildIndex()
{
	size_t Begin(0);
	if (Index.size() > 0) uuPVec().swap(Index);
	for (size_t i = 0; i < Vec.size(); i++)                                                               /*向量大循环*/
	{
		vector<size_t> Equal;
		for (size_t j = 1; j < Vec[i].size(); j++)                                                         /*对起始位的数据元与当前位置下一位的数据元进行比较*/
		{
			if (IDN(Vec[Begin][j]) != IDN::Empty && IDN(Vec[i][j]) != IDN::Empty)/*记录标签是否相等：不为空且相等取1，不为空且不等取0*/
			{
				if (IDN(Vec[Begin][j]) == IDN(Vec[i][j])) Equal.push_back(1);
				else Equal.push_back(0);
			}
		}
		size_t sumEqual(0);
		for (size_t j = 0; j < Equal.size(); j++)  sumEqual = sumEqual + Equal[j];
		if (i == Vec.size() - 1 && sumEqual == Equal.size()) Index.push_back({ i, i });/*最后一个与倒数第二个不等时*/
		else if (sumEqual < Equal.size())
		{
			size_t&& noEqual(Equal.size() - sumEqual);
			if (noEqual >= 2)
			{
				Index.push_back({ Begin, i - 1 });
				Begin = i;
				if (i == Vec.size() - 1) Index.push_back({ i, i });
			}
			else if (noEqual == 1)
			{
				if (Equal[Equal.size() - 1] == 1)
				{
					Index.push_back({ Begin,i - 1 });
					Begin = i;
				}
				else if (i == Vec.size() - 1) Index.push_back({ Begin, i });
				/*else if (Equal.size() == 2) 似应取消, 条件等价于Equal[0]==1
				{
					Index.push_back({ Begin,i - 1 });
					Begin = i;
				}*/
			}
		}
	}
	if (Index.size() > 0) return true;
	else return false;
}
size_t DataOpe::meetType(DataCell& thisCell, DataCell& objCell)
{
	size_t reVal(0);

	bool allEqual(true);
	for (size_t i = 1; i < objCell.size(); i++)	if (IDN(thisCell[i]) != IDN(objCell[i])) allEqual = false;
	if (allEqual)	reVal = 2;
	else
	{
		size_t validN(0), partN(0);
		for (size_t i = 1; i < objCell.size(); i++)/*记录有效标签相等的数量*/
		{
			if (IDN(objCell[i]) == IDN(thisCell[i]) && IDN(objCell[i]) != IDN::Empty)	partN++;
			if (IDN(objCell[i]) != IDN::Empty) validN++;
		}
		if (validN == partN) reVal = 1;
	}
	return reVal;
}
DCVec DataOpe::Read(DataCell& objCell)
{
	DCVec reVal;
	for (size_t i = 0; i < this->Index.size(); i++)
	{
		for (size_t j = this->Index[i].first; j <= this->Index[i].second; j++)
		{
			size_t&& Equal(meetType(Vec[j], objCell));
			if (Equal > 0) reVal.push_back(Vec[j]);
		}
	}
	return reVal;
}
DCVec DataOpe::Read(string& objStr)
{
	DataCell objCell;
	objCell = objStr;

	return Read(objCell);
}
myDC& DataOpe::Read(size_t Seq)
{
	return Vec[Seq];
}
DCVec DataOpe::Get(size_t Begin, size_t End)
{
	DCVec reVal;
	for (size_t i = Begin; i <= End; i++) reVal.push_back(Vec[i]);
	return reVal;
}
bool DataOpe::Write(DataCell& objCell, bool Cal)
{
	bool reVal(false);
	for (size_t i = 0; i < this->Index.size(); i++)
	{
		if (IDN(Vec[this->Index[i].first][1]) == IDN(objCell[1]))
		{
			for (size_t j = this->Index[i].first; j <= this->Index[i].second; j++)
			{
				size_t&& Equal(meetType(Vec[j], objCell));
				if (Equal == 2)
				{
					Vec[j] = objCell[0];
					reVal = true;
					break;
				}
			}
		}
		if (reVal) break;
	}
	if (reVal && Cal) this->Cal();
	return reVal;
}
bool DataOpe::Write(string& objStr, bool Cal)
{
	DataCell objCell;
	objCell = objStr;
	return Write(objCell, Cal);
}
bool DataOpe::Write(size_t Seq, double objVal, bool Cal)
{
	Vec[Seq] = objVal;
	if (Cal) this->Cal();
	return true;
}
bool DataOpe::Set(DataCell& objCell, double* ptrVal, unsigned N, bool Cal)
{
	bool reVal(false);
	size_t k(0);
	for (size_t i = 0; i < this->Index.size(); i++)
	{
		if (IDN(Vec[this->Index[i].first][1]) == IDN(objCell[1]))
		{
			for (size_t j = this->Index[i].first; j <= this->Index[i].second; j++)
			{
				size_t&& Equal(meetType(Vec[j], objCell));
				if (Equal > 0 && k < N)
				{
					Vec[j] = *(ptrVal + k);
					k++;
					reVal = true;
				}
			}
		}
		if (reVal) break;
	}
	if (reVal && Cal) this->Cal();
	return reVal;
}
bool DataOpe::Set(string& objStr, double* ptrVal, unsigned N, bool Cal)
{
	DataCell objCell;
	objCell = objStr;
	return Set(objCell, ptrVal, N, Cal);
}
bool DataOpe::Set(size_t Begin, size_t End, double* ptrVal, bool Cal)
{
	for (size_t i = Begin; i <= End; i++) Vec[i] = *(ptrVal + i);
	if (Cal) return this->Cal();
	return true;
}
bool DataOpe::Add(DataCell& objCell, bool BldIndex = false)
{
	Vec.push_back(objCell);
	if (BldIndex) BuildIndex();
	return true;
}
bool DataOpe::Add(string& objStr, bool BldIndex = false)
{
	DataCell objCell;
	objCell = objStr;

	return Add(objCell, BldIndex);
}
bool DataOpe::Add(DCVec& objVec, bool BldIndex = false)
{
	for (size_t i = 0; i < objVec.size(); i++)  Vec.push_back(objVec[i]);
	if (BldIndex) BuildIndex();
	return true;
}
bool DataOpe::Add(string& objStr, size_t N, bool BldIndex = false)
{
	myDC X;
	for (size_t i = 0; i < N; i++)
	{
		X = objStr;
		Add(X, BldIndex);
	}
	return true;
}
bool DataOpe::Del(DataCell& objCell, bool BldIndex = false)
{
	DCVec X(Vec.size());
	for (size_t i = 0; i < Vec.size(); i++) X[i] = Vec[i];
	DCVec().swap(Vec);
	Vec.reserve(X.size());
	for (size_t i = 0; i < X.size(); i++)
	{
		size_t&& EqualType(meetType(X[i], objCell));
		if (EqualType == 0) Vec.push_back(X[i]);
	}
	if (BldIndex) BuildIndex();
	return true;
}
bool DataOpe::Del(string& objStr, bool BldIndex = false)
{
	DataCell objCell;
	objCell = objStr;
	return Del(objCell, BldIndex);
}
uuPVec& DataOpe::GetIndex()
{
	return this->Index;
}
//外部数据读入及初步处理
DataIO::DataIO(int HeatNo = 0) :fileName("./应用文件/Data")
{
	//本类成员初始化
	if (HeatNo != 0) fileName = fileName + to_string(HeatNo) + ".txt";
	else fileName = fileName + ".txt";
	Input();
	BuildIndex();
	Cal();
}
void DataIO::Input()
{
	string fileData("");  /*存储数据文件的全部内容*/
	//将数据文件内容全部读到fileData
	{
		fstream fileObj(fileName, ios::ate | ios::in | ios::out);
		string fileDataLine;
		fileObj.seekp(0, fileObj.beg);
		while (!fileObj.eof())
		{
			getline(fileObj, fileDataLine);
			fileData = fileData + fileDataLine + '_';
		}
		fileObj.close();
	}
	//fileData去空白、单回车、单换行3种字符
	{
		size_t    symPos(0);
		while (fileData.find(' ') != fileData.npos || fileData.find('\r') != fileData.npos || fileData.find('\n') != fileData.npos)
		{
			if (fileData.find(' ') != fileData.npos)
			{
				symPos = int(fileData.find(' '));
				fileData = fileData.substr(0, symPos) + fileData.substr(symPos + 1);
				continue;
			}
			else if (fileData.find('\r') != fileData.npos)
			{
				symPos = int(fileData.find('\r'));
				fileData = fileData.substr(0, symPos) + fileData.substr(symPos + 1);
				continue;
			}
			else if (fileData.find('\n') != fileData.npos)
			{
				symPos = int(fileData.find('\n'));
				fileData = fileData.substr(0, symPos) + fileData.substr(symPos + 1);
				continue;
			}
		}
	}
	//将fileData和其他常数依次写入staticVec
	{
		string strData;
		while (fileData.find('_') != fileData.npos)
		{
			size_t sPos(size_t(fileData.find('_')) + 1);
			strData = fileData.substr(0, sPos - 1);
			fileData = fileData.substr(sPos);
			this->Add(strData);
		}
		//写入参数常量
		{
			string strT(""), myStr("State");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "Prepare" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "Start" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "ScrpFeed" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "HMFeed" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "Ignition" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "Blowing" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "Meas1" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "BlowEnd" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "Meas2" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "Meas3" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "Tapping" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "Splash" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Time" + lblDev + "End" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Cons" + lblDev + "O2" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Cons" + lblDev + "N2" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Cons" + lblDev + "Ar" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Score" + lblDev + "TDiff" + valDev + "-25");
			this->Add(strT = myStr + lblDev + "Assess" + lblDev + "StaticTemp" + valDev + "0");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "C" + valDev + "12");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Si" + valDev + "28");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Mn" + valDev + "55");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "P" + valDev + "31");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "S" + valDev + "32");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Cr" + valDev + "54");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Ni" + valDev + "59");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Mo" + valDev + "96");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Cu" + valDev + "64");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Al" + valDev + "27");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "V" + valDev + "51");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Ti" + valDev + "48");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "B" + valDev + "11");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "N" + valDev + "14");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "O" + valDev + "16");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Fe" + valDev + "55");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "CaO" + valDev + "56");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "SiO2" + valDev + "60");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "MgO" + valDev + "40");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Al2O3" + valDev + "102");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "MnO" + valDev + "71");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "FeO" + valDev + "72");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Fe2O3" + valDev + "160");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "P2O5" + valDev + "142");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "CaF2" + valDev + "78");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Cr2O3" + valDev + "156");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "V2O3" + valDev + "150");
			this->Add(strT = myStr + lblDev + "Atom" + lblDev + "Spare" + valDev + "0");
			myStr = "Enrg";
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "C" + valDev + "127.89");
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "Si" + valDev + "375.39");
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "Mn" + valDev + "83.14");
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "P" + valDev + "355.17");
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "Cr" + valDev + "158.15");
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "Fe" + valDev + "99.36");
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "V" + valDev + "137.62");
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "Al" + valDev + "344.63");
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "Burnt" + valDev + "-17");
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "Fe2O3" + valDev + "-14.96");
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "SiO2" + valDev + "24.05");                  /*成渣反应热*/
			this->Add(strT = myStr + lblDev + "Reac" + lblDev + "P2O5" + valDev + "58.52");                /*成渣反应热*/
			this->Add(strT = myStr + lblDev + "Oxid" + lblDev + "CaO" + valDev + "-13.97");
			this->Add(strT = myStr + lblDev + "Oxid" + lblDev + "SiO2" + valDev + "-19.46");
			this->Add(strT = myStr + lblDev + "Oxid" + lblDev + "MgO" + valDev + "-13.76");
			this->Add(strT = myStr + lblDev + "Oxid" + lblDev + "Al2O3" + valDev + "-25.04");
			this->Add(strT = myStr + lblDev + "Oxid" + lblDev + "CaF2" + valDev + "-25.19");
			this->Add(strT = myStr + lblDev + "Oxid" + lblDev + "FeO" + valDev + "-19.75");
			this->Add(strT = myStr + lblDev + "Oxid" + lblDev + "Fe2O3" + valDev + "-18.75");
			this->Add(strT = myStr + lblDev + "Oxid" + lblDev + "MnO" + valDev + "-18.15");
			this->Add(strT = myStr + lblDev + "Oxid" + lblDev + "Cr2O3" + valDev + "-12.06");
			this->Add(strT = myStr + lblDev + "Oxid" + lblDev + "V2O3" + valDev + "-14.44");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "Al" + valDev + "-0.006");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "C" + valDev + "-0.028");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "Cr" + valDev + "-0.008");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "Fe" + valDev + "-0.011");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "Mn" + valDev + "-0.011");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "Mo" + valDev + "-0.004");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "Ni" + valDev + "-0.007");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "Si" + valDev + "0.006");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "N2" + valDev + "-0.017");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "Ar" + valDev + "-0.011");
			this->Add(strT = myStr + lblDev + "Elem" + lblDev + "Slag" + valDev + "-0.015");
			this->Add(strT = myStr + lblDev + "Misc" + lblDev + "RadioK" + valDev + "0.0045344");      /*辐射系数*/
			this->Add(strT = myStr + lblDev + "Misc" + lblDev + "Lining" + valDev + "-2.69");                /*炉衬导热系数*/
		}
	}
}
void DataIO::PreMass()
{
	uuPVec thisIndex(this->GetIndex());
	for (size_t i = 0; i < thisIndex.size(); i++)
	{
		IDN&& matType(IDN(this->Read(thisIndex[i].first)[1]));
		if (matType == IDN::Stl || matType == IDN::Scrp || matType == IDN::Slag || matType == IDN::Flux || matType == IDN::Alloy)
		{
			double elemSum(0);
			for (size_t j = thisIndex[i].first; j <= thisIndex[i].second; j++)/*单一物质内：逐个元素成分相加*/
			{
				myDC X;
				X = this->Read(j);
				IDN elemName(IDN::IDFail);
				for (int k = X.size() - 1; k > 0; k--)/*当前元数据内，元素名称判断*/
				{
					if (IDN(X[k]) != IDN::Empty)
					{
						elemName = IDN(X[k]);
						break;
					}
				}
				if (elemName >= IDN::C && elemName < IDN::Fe)
				{
					elemSum = elemSum + X[0];
				}
				else if (elemName >= IDN::CaO && elemName < IDN::Burnt)
				{
					elemSum = elemSum + X[0];
				}
				else if (elemName == IDN::Fe || elemName == IDN::Burnt)
				{
					this->Write(j, 100 - elemSum, false);
					if (IDN(X[1]) == IDN::Scrp)/*废钢需考虑炉渣含量*/
					{
						for (size_t k = thisIndex[i].first; k <= thisIndex[i].second; k++)
						{
							myDC Y;
							Y = this->Read(k);
							IDN isSlag(IDN::IDFail);
							for (int p = Y.size() - 1; p > 0; p--)
							{
								if (IDN(Y[p]) != IDN::Empty)
								{
									isSlag = IDN(Y[p]);
									break;
								}
							}
							if (isSlag == IDN::Slag)
							{
								this->Write(j, this->Read(j)[0] - this->Read(k)[0], false);
								break;
							}
						}
					}
				}
			}
		}
	}
}
void DataIO::PreEnrg()
{
	uuPVec thisIndex(this->GetIndex());
	//首先：准备冷却系数
	vector<pair<IDN, double>> reacE, oxidE, elemE;
	for (size_t i = 0; i < thisIndex.size(); i++)
	{
		IDN Name(IDN(this->Read(thisIndex[i].first)[1]));
		if (Name == IDN::Enrg)
		{
			size_t vecCnt(thisIndex[i].second - thisIndex[i].first + 1);
			Name = IDN(this->Read(thisIndex[i].first)[2]);
			if (Name == IDN::Reac)
			{
				reacE.resize(vecCnt);
				for (size_t j = thisIndex[i].first; j <= thisIndex[i].second; j++)
				{
					Name = IDN(this->Read(j)[3]);
					reacE[j - thisIndex[i].first] = { Name, this->Read(j)[0] };
				}
			}
			else if (Name == IDN::Oxid)
			{
				oxidE.resize(vecCnt);
				for (size_t j = thisIndex[i].first; j <= thisIndex[i].second; j++)
				{
					Name = IDN(this->Read(j)[3]);
					oxidE[j - thisIndex[i].first] = { Name, this->Read(j)[0] };
				}
			}
			else if (Name == IDN::Elem)
			{
				elemE.resize(vecCnt);
				for (size_t j = thisIndex[i].first; j <= thisIndex[i].second; j++)
				{
					Name = IDN(this->Read(j)[3]);
					elemE[j - thisIndex[i].first] = { Name, this->Read(j)[0] };
				}
			}
		}
	}
	//其次：计算纯冷却-thermal1
	for (size_t i = 0; i < thisIndex.size(); i++) /*单个物质移动*/
	{
		bool Flag(false);                    /*参数准备*/
		vector<pair<IDN, double>> genE;
		IDN matType(IDN(this->Read(thisIndex[i].first)[1]));
		if (matType == IDN::Scrp || matType == IDN::Alloy) { genE = elemE; 	Flag = true; }
		else if (matType == IDN::Flux) { genE = oxidE;		Flag = true; }
		else if (matType == IDN::Slag) { genE.push_back(elemE[elemE.size() - 1]);	Flag = true; }
		if (Flag)
		{
			double sumEnrg(0), matTemp(0), genTemp(1250);;
			for (size_t m = thisIndex[i].first; m <= thisIndex[i].second; m++)/*读取物质温度*/
			{
				for (int n = this->Read(m).size() - 1; n > 0; n--)
				{
					if (IDN(this->Read(m)[n]) == IDN::Temp)
					{
						matTemp = this->Read(m)[0];
						break;
					}
				}
			}
			for (size_t m = thisIndex[i].first; m <= thisIndex[i].second; m++)/*物质内各元素移动*/
			{
				myDC X = this->Read(m);
				IDN matElem(IDN::IDFail);
				for (size_t n = X.size() - 1; n > 0; n--) /*确定当前向量的元素名称*/
				{
					if (IDN(X[n]) != IDN::Empty)
					{
						matElem = IDN(X[n]);
						break;
					}
				}
				if (matElem >= IDN::C && matElem <= IDN::Burnt)
				{
					for (size_t n = 0; n < genE.size(); n++)/*冷却系数向量各元素移动*/
					{
						if (matElem == genE[n].first)
						{
							if (matType == IDN::Flux)  sumEnrg = sumEnrg + X[0] / 100 * genE[n].second;  /*核心公式*/
							else 								        sumEnrg = sumEnrg + X[0] * (genTemp - matTemp) / 100 * genE[n].second;  /*核心公式*/
						}
						else if (matType == IDN::Slag) sumEnrg = genE[0].second * (genTemp - matTemp);
					}
				}
				else if (matElem == IDN::Thermal1) this->Write(m, sumEnrg, false);/*结果赋值*/
			}
		}
	}
	//最后：计算纯化学-thermal2
	for (size_t i = 0; i < thisIndex.size(); i++)/*单个物质移动*/
	{
		IDN matType(IDN(this->Read(thisIndex[i].first)[1]));  /*参数准备*/
		if (matType == IDN::Scrp || matType == IDN::Alloy || matType == IDN::Flux || matType == IDN::Stl)
		{
			double sumEnrg(0);
			for (size_t m = thisIndex[i].first; m <= thisIndex[i].second; m++)/*物质内各元素移动*/
			{
				myDC X = this->Read(m);
				IDN matElem(IDN::IDFail);
				for (size_t n = X.size() - 1; n > 0; n--) /*确定当前向量的元素名称*/
				{
					if (IDN(X[n]) != IDN::Empty)
					{
						matElem = IDN(X[n]);
						break;
					}
				}
				for (size_t n = 0; n < reacE.size(); n++)/*冷却系数向量各元素移动*/
				{
					if (matElem == reacE[n].first)
					{
						if (matElem >= IDN::C && matElem <= IDN::Burnt && matElem != IDN::Cr && matElem != IDN::Fe)
						{
							if (matType == IDN::Stl || matType == IDN::Scrp || matType == IDN::Flux)
							{
								sumEnrg = sumEnrg + X[0] * reacE[n].second / 100;
							}
							else if (matType == IDN::Alloy)
							{
								IDN mainElem1(IDN::IDFail), mainElem2(IDN::IDFail);/*先读出主元素：不参加化学反应*/
								for (size_t k = thisIndex[i].first; k <= thisIndex[i].second; k++)
								{
									DataCell Y = this->Read(k);
									for (int p = Y.size() - 1; p > 0; p--)
									{
										if (IDN(Y[p]) == IDN::MElem1) mainElem1 = IDN(Y[0]);
										else if (IDN(Y[p]) == IDN::MElem2) mainElem2 = IDN(Y[0]);
									}
								}
								if (matElem != mainElem1 && matElem != mainElem2) sumEnrg = sumEnrg + X[0] / 100 * reacE[n].second;
							}
						}
					}
				}
				if (matElem == IDN::Thermal2) this->Write(m, sumEnrg, false); /*结果赋值*/
			}
		}
	}
}
bool DataIO::Cal()
{
	/*uuPVec thisIndex(this->GetIndex());  test index
	for (size_t i = 0; i < thisIndex.size(); i++) cout << thisIndex[i].first << "  ";
	cout << endl;
	for (size_t i = 0; i < thisIndex.size(); i++) cout << thisIndex[i].second << "  ";
	cout << endl;
	for (unsigned i = 0; i < thisIndex.size(); i++)
	{
		DCVec X;
		for (size_t j = thisIndex[i].first; j <= thisIndex[i].second; j++) X.push_back(this->Read(j));
		for (size_t m = 0; m < X.size(); m++)
		{
			cout << thisIndex[i].first + m << "  ";
			for (size_t n = 1; n < X[m].size(); n++) cout << IDNTrans(IDN(X[m][n])) << "  ";
			cout << ":  " << X[m][0] << endl;
		}
	}*/
	PreMass();
	PreEnrg();
	return true;
}
//碱度及纯熔剂计算
PureFlux::PureFlux(DataIO& objIO)
{
	ptrIO = &objIO;
	strVec Para(15);
	string strT(IDNTrans(IDN::Para));
	strT = strT + lblDev;
	Para[0] = strT + IDNTrans(IDN::LSi) + valDev + "0.12";         Para[1] = strT + IDNTrans(IDN::USi) + valDev + "1.0";
	Para[2] = strT + IDNTrans(IDN::LBa) + valDev + "1.8";          Para[3] = strT + IDNTrans(IDN::UBa) + valDev + "3.5";
	Para[4] = strT + IDNTrans(IDN::CeqMn) + valDev + "0.25";	 Para[5] = strT + IDNTrans(IDN::RedSi) + valDev + "0";
	Para[6] = strT + IDNTrans(IDN::CMgO) + valDev + "6";        Para[7] = strT + IDNTrans(IDN::CCaF2) + valDev + "14";
	Para[8] = strT + IDNTrans(IDN::Ini) + lblDev + IDNTrans(IDN::Si) + valDev + "0.32";
	Para[9] = strT + IDNTrans(IDN::Ini) + lblDev + IDNTrans(IDN::Mn) + valDev + "0.25";
	Para[10] = strT + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Wgt) + valDev + "120000";
	strT = IDNTrans(IDN::Result) + lblDev;
	Para[11] = strT + IDNTrans(IDN::Basicity);       Para[12] = strT + IDNTrans(IDN::PureCaO);
	Para[13] = strT + IDNTrans(IDN::PureMgO);    Para[14] = strT + IDNTrans(IDN::PureCaF2);
	for (size_t i = 0; i < Para.size(); i++) this->Add(Para[i], false);
	this->BuildIndex();
}
bool  PureFlux::Cal()
{
	//不常改变的参数
	double&& LSi(this->Read(0)[0]), && USi(this->Read(1)[0]), && LBa(this->Read(2)[0]), && UBa(this->Read(3)[0]),
		&& CeqMn(this->Read(4)[0]), && CMgO(this->Read(6)[0]), && CCaF2(this->Read(7)[0]);
	//每次使用前都需重新接收的参数
	double&& IniSi(this->Read(8)[0]), && IniMn(this->Read(9)[0]), && RedSi(this->Read(5)[0])/*kg/t*/, && WStl(this->Read(10)[0])/*kg*/;
	//计算结果
	double&& Basicity(this->Read(11)[0]), && pureCaO(this->Read(12)[0]), && pureMgO(this->Read(13)[0]), && pureCaF2(this->Read(14)[0]);

	bool reVal(false);
	double a(0), b(0), x(0);
	if (int(RedSi) > 0) USi = USi + RedSi / 10;
	if (USi - LSi > 0)
	{
		a = (UBa - LBa) / (LSi - USi);
		b = (LBa * LSi - UBa * USi) / (LSi - USi);
		x = IniSi + RedSi + CeqMn * IniMn;
		Basicity = a * x + b;		 /*碱度*/
		pureCaO = 2.143 * (IniSi + RedSi / 10) * Basicity * WStl / 100;
		pureMgO = pureCaO * CMgO / 100;
		pureCaF2 = pureCaO * CCaF2 / 100;
		reVal = true;
	}
	//储存结果至本类
	this->Write(11, Basicity, false);
	this->Write(12, pureCaO, false);
	this->Write(13, pureMgO, false);
	this->Write(14, pureCaF2, false);

	return reVal;
}
//物料熔剂计算
MatFlux::MatFlux(DataIO& objIO)
{
	ptrIO = &objIO;
	strVec Para(9);
	string strT(IDNTrans(IDN::Para));
	strT = strT + lblDev;
	Para[0] = strT + IDNTrans(IDN::PureCaO) + valDev + "1000";    Para[1] = strT + IDNTrans(IDN::PureMgO) + valDev + "1000";
	Para[2] = strT + IDNTrans(IDN::PureCaF2) + valDev + "1000";   Para[3] = strT + IDNTrans(IDN::Basicity) + valDev + "2.5";
	Para[4] = strT + IDNTrans(IDN::MElem1) + valDev + "CaO";      Para[5] = strT + IDNTrans(IDN::MEComp) + valDev + "85";
	Para[6] = strT + IDNTrans(IDN::SiO2) + valDev + "6";                 Para[7] = strT + IDNTrans(IDN::Ratio) + valDev + "1";
	strT = IDNTrans(IDN::Result);
	strT = strT + lblDev;
	Para[8] = strT + IDNTrans(IDN::MatFlux) + valDev + "0";
	for (size_t i = 0; i < Para.size(); i++) this->Add(Para[i], false);
	this->BuildIndex();
}
bool  MatFlux::Cal()
{
	//来自pureFlux的结果
	double&& pureCaO(this->Read(0)[0]), && pureMgO(this->Read(1)[0]), && pureCaF2(this->Read(2)[0]), && Basicity(this->Read(3)[0]);
	//来自外部的参数
	double&& mainElem(this->Read(4)[0]), && MEComp(this->Read(5)[0]), && SiO2Comp(this->Read(6)[0]), && Ratio(this->Read(7)[0]);
	//计算结果
	double&& matFlux(this->Read(8)[0]);

	bool reVal(false);
	string strT("MatFlux");
	if (IDN(mainElem) == IDN::CaO)
	{
		strT = strT + lblDev + "Lime";
		if (fabs(MEComp - SiO2Comp * Basicity) > dbZero)
		{
			matFlux = pureCaO * (1 - pureMgO / pureCaO) * Ratio * 100 / (MEComp - SiO2Comp * Basicity);
			reVal = true;
		}
		else reVal = false;
	}
	else if (IDN(mainElem) == IDN::MgO)
	{
		strT = strT + lblDev + "Dolo";
		if (fabs(MEComp) > dbZero)
		{
			matFlux = pureMgO * Ratio * 100 / MEComp;
			reVal = true;
		}
		else reVal = false;
	}
	else if (IDN(mainElem) == IDN::CaF2)
	{
		strT = strT + lblDev + "Fluo";
		if (fabs(MEComp) > dbZero)
		{
			matFlux = pureCaF2 * Ratio * 100 / MEComp;
			reVal = true;
		}
		else reVal = false;
	}
	else
	{
		strT = strT + lblDev + emptyStr;
		reVal = false;
	}
	this->Write(8, matFlux, false);

	return reVal;
}
//熔池状态计算
BathState::BathState(DataIO& objIO) :elemN(8), seqAl(1), seqSi(2), seqV(3), seqMn(4), seqCr(5), seqP(6), seqFe(7), seqC(8), oxyAlSi(0), iniC(0)
{
	string strT(""), myStr("");
	DCVec qVec;
	ptrIO = &objIO;

	//常用数初始化
	elemName = { IDN::Al, IDN::Si,IDN::V,IDN::Mn,IDN::Cr,IDN::P,IDN::Fe,IDN::C };
	oxidName = { IDN::Al2O3,IDN::SiO2,IDN::V2O3,IDN::MnO,IDN::Cr2O3,IDN::P2O5,IDN::FeO,IDN::CO };
	elemOxy = { 0.622,0.8,0.329,0.204,0.311,0.903,0.2,0.933 };
	double keyCrTemp(1530);
	stlAimC = ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::C))[0][0];
	stlAimTemp = ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Temp))[0][0];
	double&& stlAimLCr = ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Low) + lblDev + IDNTrans(IDN::Cr))[0][0];
	/*读取所需的参数*/
	myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static);
	qVec = ptrIO->Read(myStr);
	kForP = 0;
	for (size_t i = 0; i < qVec.size(); i++)
	{
		if (IDN(qVec[i][3]) == IDN::keyC)            keyC.push_back(qVec[i][0]);
		else if (IDN(qVec[i][3]) == IDN::kForC)           kForC.push_back(qVec[i][0]);
		else if (IDN(qVec[i][3]) == IDN::OxyFlow)       oxyFlow.push_back(qVec[i][0]);
		else if (IDN(qVec[i][3]) == IDN::GasType)      BotType = IDN(qVec[i][0]);
		else if (IDN(qVec[i][3]) == IDN::BottomFlow) BotFlow = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::KeyTemp)     keyTemp = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::kForP)            kForP = qVec[i][0];
	}
	keyC.push_back(stlAimC);
	if (oxyFlow.size() != keyC.size())  for (size_t i = oxyFlow.size(); i <= keyC.size(); i++) oxyFlow.push_back(oxyFlow[oxyFlow.size() - 1]);
	/*读取元素的化学反应热*/
	myStr = IDNTrans(IDN::Enrg) + lblDev + IDNTrans(IDN::Reac);
	qVec = ptrIO->Read(myStr);
	elemTher.resize(elemN);
	for (size_t i = 0; i < elemN; i++)
	{
		for (size_t j = 0; j < qVec.size(); j++)  if (elemName[i] == IDN(qVec[j][3])) elemTher[i] = qVec[j][0];
	}
	/*读取底吹气体冷却系数及炉渣冷却系数*/
	myStr = IDNTrans(IDN::Enrg) + lblDev + IDNTrans(IDN::Elem);
	qVec = ptrIO->Read(myStr);
	for (size_t i = 0; i < qVec.size(); i++)
	{
		if (IDN(qVec[i][3]) == BotType) GasTher = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::Slag) slagTher = qVec[i][0];
	}
	/*读取辐射及传导用参数*/
	myStr = IDNTrans(IDN::Enrg) + lblDev + IDNTrans(IDN::Misc);
	qVec = ptrIO->Read(myStr);
	for (size_t i = 0; i < qVec.size(); i++)
	{
		if (IDN(qVec[i][3]) == IDN::RadioK) k = qVec[i][0];                   /*辐射*/
		else if (IDN(qVec[i][3]) == IDN::Lining) HeatVal = qVec[i][0];          /*炉衬传导*/
	}
	myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Radio);                    /*辐射*/
	qVec = ptrIO->Read(myStr);
	for (size_t i = 0; i < qVec.size(); i++)
	{
		if (IDN(qVec[i][3]) == IDN::MouthSqr)
		{
			s = qVec[i][0];
			s = s * s / 4 * PI;
			break;
		}
	}
	myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Lining);                   /*炉衬传导*/
	qVec = ptrIO->Read(myStr);
	for (size_t i = 0; i < qVec.size(); i++)
	{
		if (IDN(qVec[i][3]) == IDN::AveLen) AveLen = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::AveSqr) AveSqr = qVec[i][0];
	}

	//向量初始化
	strVec Para(13);
	strT = IDNTrans(IDN::Para) + lblDev;
	Para[0] = strT + IDNTrans(IDN::Old) + lblDev + IDNTrans(IDN::Time) + valDev + "0";
	Para[1] = strT + IDNTrans(IDN::New) + lblDev + IDNTrans(IDN::Time) + valDev + "0";
	Para[2] = strT + IDNTrans(IDN::Ini) + lblDev + IDNTrans(IDN::C) + valDev + "0";
	Para[3] = strT + IDNTrans(IDN::Ini) + lblDev + IDNTrans(IDN::OxyAlSi) + valDev + "0";
	Para[4] = strT + IDNTrans(IDN::KeyTemp) + valDev + "0";
	Para[5] = strT + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::Temp) + valDev + to_string(stlAimTemp);
	Para[6] = strT + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::C) + valDev + to_string(stlAimC);
	Para[7] = strT + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::Time) + valDev + "0";
	Para[8] = strT + IDNTrans(IDN::kForP) + valDev + to_string(kForP);
	iniP = 0;
	Para[9] = strT + IDNTrans(IDN::iniP) + valDev + to_string(iniP);
	Para[10] = strT + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::C) + valDev + to_string(stlAimC);
	Para[11] = strT + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Temp) + valDev + to_string(stlAimTemp);
	Para[12] = strT + IDNTrans(IDN::Old) + lblDev + IDNTrans(IDN::C) + valDev + "0";
	for (size_t i = 0; i < Para.size(); i++) this->Add(Para[i], false);
	if (stlAimLCr > dbZero)  keyTemp = keyCrTemp; /*是否存在Cr氧化，以使用不同的临界温度*/
	this->Write(4, keyTemp, false);

	/*初始化起始钢液和炉渣*/
	IDN iniType(IDN::Stl);
	for (unsigned i = 0; i < 2; i++)
	{
		if (i == 1) iniType = IDN::Slag;
		strT = IDNTrans(iniType) + lblDev + IDNTrans(IDN::Ini);
		DCVec&& iniData(ptrIO->Read(strT));
		for (unsigned j = 0; j < iniData.size(); j++)
		{
			for (int k = iniData[j].size() - 1; k > 0; k--)
			{
				if (IDN(iniData[j][k]) != IDN::Empty)
				{
					string myStr(IDNTrans(IDN::Para));
					strT = myStr + lblDev + IDNTrans(IDN(iniData[j][1])) + lblDev + IDNTrans(IDN(iniData[j][k])) + valDev + to_string(iniData[j][0]);
					iniData[j] = strT;
					break;
				}
			}
		}
		for (unsigned j = 0; j < iniData.size(); j++) this->Add(iniData[j]);
	}
	BuildIndex();
	iniStlWgt = this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Wgt))[0][0];
	//碳计算中常用数初始化
	myStr = IDNTrans(IDN::Para);
	myStr = myStr + lblDev + IDNTrans(IDN::Stl) + lblDev;

	iniC = this->Read(strT = myStr + IDNTrans(IDN::C))[0][0];                         /*读取起始碳含量*/
	this->Write(2, iniC, false);
	this->Write(12, iniC, false);
	iniP = this->Read(strT = myStr + IDNTrans(IDN::P))[0][0];
	this->Write(9, iniP, false);

	dbVec iniAlSi(4);  /*计算AlSi氧耗*/
	iniAlSi[0] = this->Read(strT = myStr + IDNTrans(IDN::Al))[0][0];
	iniAlSi[1] = this->Read(strT = myStr + IDNTrans(IDN::Si))[0][0];
	iniAlSi[2] = this->Read(strT = myStr + IDNTrans(IDN::V))[0][0];
	iniAlSi[3] = this->Read(strT = myStr + IDNTrans(IDN::Mn))[0][0];
	double stlWgt(this->Read(strT = myStr + IDNTrans(IDN::Wgt))[0][0]);
	dbVec elemLLim{ 0.003, 0.04,0.12,0.12 };
	for (unsigned i = seqAl - 1; i < seqMn; i++) 	oxyAlSi = oxyAlSi + (iniAlSi[i] - elemLLim[i]) * stlWgt / 100 * elemOxy[i];
	nonCoxidTime = oxyAlSi / oxyFlow[0] * 3600;
	this->Write(3, oxyAlSi, false);
	this->Write(7, oxyAlSi / oxyFlow[0], false);
}
bool BathState::Cal()
{
	string strT(""), myStr(IDNTrans(IDN::Para));
	DCVec qVec;

	double&& blowTime(this->Read(0)[0]);     /*吹炼时间*/
	double&& nowBlowTime(this->Read(1)[0]);
	double&& stlWgt(this->Read(strT = myStr + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
	double stlLastWgt(stlWgt);
	double&& stlTemp(this->Read(strT = myStr + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Temp))[0][0]);
	double stlLastTemp(stlTemp);
	double&& slagWgt(this->Read(strT = myStr + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
	double slagLastWgt(slagWgt);
	double&& slagTemp(this->Read(strT = myStr + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::Temp))[0][0]);
	double&& setTemp(this->Read(5)[0]);
	double&& setC(this->Read(6)[0]);
	stlAimC = this->Read(10)[0];
	keyC[keyC.size() - 1] = stlAimC;
	stlAimTemp = this->Read(11)[0];

	//先根据吹炼时间，更新熔池状态
	if (fabs(nowBlowTime - blowTime) > dbZero || fabs(setTemp - stlAimTemp) > dbZero || fabs(setC - stlAimC) > dbZero)
	{
		dbVec                                          oxidAmt{ 1.889,2.143,1.471,1.291,1.444,2.290,1.286,0 };
		vector<pair<double, double>> elemAmt{ {0.003,0}, {0.04,0},{0.12,0},{0.12,0},{0.5,0},{0.003,0},{1,0},{stlAimC,0} };     /*8种氧化性元素的下限及氧化量*/

		//数据准备
		double CriticalC(0), curK, curFlow(0), hereIniC(iniC), hereIniStlWgt(iniStlWgt);
		double&& SetTime(this->Read(7)[0]);
		myStr = IDNTrans(IDN::Para);
		myStr = myStr + lblDev + IDNTrans(IDN::Stl) + lblDev;
		for (size_t i = 0; i < elemN; i++)  elemAmt[i].second = this->Read(strT = myStr + IDNTrans(elemName[i]))[0][0];
		for (size_t i = 0; i < kForC.size(); i++)
		{
			if (elemAmt[seqC - 1].second > keyC[i])
			{
				CriticalC = keyC[i];
				curK = kForC[i];
				curFlow = oxyFlow[i];
				break;
			}
			else
			{
				if ((nowBlowTime - blowTime) < dbZero) SetTime = SetTime + hereIniStlWgt * (hereIniC - keyC[i]) / (100 - keyC[i]) * elemOxy[seqC - 1] / oxyFlow[i] * 3600;
				hereIniStlWgt = hereIniStlWgt * (100 - hereIniC) / (100 - keyC[i]);
				hereIniC = keyC[i];
			}
		}
		double&& OxyAmt(curFlow * (nowBlowTime - blowTime) / 3600);
		//以下按照氧化顺序依次计算各元素变化：实时更新钢水重量、温度、元素百分比含量及炉渣重量
		//三个约束择其最小值：成分下限、氧气量（时间）、温度
		if (elemAmt[seqC - 1].second - setC > dbZero)/*非C元素氧化*/
		{
			double limTemp(0);
			for (size_t i = seqAl - 1; i < seqFe; i++)
			{
				double elemOxid(0);
				if (setTemp < keyTemp) limTemp = setTemp;
				else                                  limTemp = keyTemp;
				if (stlTemp < limTemp)/*温度约束一定有：若钢液温度高于指定温度或临界温度，则非碳元素氧化量必为0*/
				{
					dbVec qtyX(2);
					/*成分约束*/
					if (elemAmt[i].second - elemAmt[i].first > 0)	qtyX[0] = stlWgt * (elemAmt[i].second - elemAmt[i].first) / (100 - elemAmt[i].first);
					else                                                                  qtyX[0] = 0;
					/*温度约束的氧化量*/
					qtyX[1] = stlWgt * (limTemp - stlTemp) / (100 * elemTher[i]);
					/*氧气量约束*/
					if (OxyAmt > dbZero)
					{
						qtyX.resize(3);
						qtyX[2] = OxyAmt / elemOxy[i];
					}
					elemOxid = Min(&qtyX[0], qtyX.size()); /*取最小值为元素氧化量*/
				}
				if ((i == seqAl - 1 || i == seqSi - 1) && fabs(limTemp - keyTemp) <= dbZero)/*无指定温度时，铝硅没有温度约束*/
				{
					dbVec qtyX(1);
					/*成分约束*/
					if (elemAmt[i].second - elemAmt[i].first > 0)	qtyX[0] = stlWgt * (elemAmt[i].second - elemAmt[i].first) / (100 - elemAmt[i].first);
					else                                                                  qtyX[0] = 0;
					/*氧量约束*/
					if (OxyAmt > dbZero)
					{
						qtyX.resize(2);
						qtyX[1] = OxyAmt / elemOxy[i];
					}
					elemOxid = Min(&qtyX[0], qtyX.size()); /*取最小值为元素氧化量*/
				}
				if (i == seqP - 1)                                                                                                                        /*对于P，当碱度约束不满足时，元素氧化量设为0*/
				{
					double&& bathCaO(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::CaO))[0][0]);
					double&& bathSiO2(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::SiO2))[0][0]);
					if (bathSiO2 < 1 || bathCaO / bathSiO2 < 2) elemOxid = 0;
					else if (stlTemp <= limTemp)
					{
						double&& bathFeO(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::FeO))[0][0]);
						double&& bathFe2O3(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::Fe2O3))[0][0]);
						double&& TFeO((bathFeO + 0.35 * bathFe2O3) / (100 + 0.35 * bathFe2O3) * 100);
						double&& calKforP(-0.002 * bathCaO / TFeO);
						if (calKforP < -0.008) calKforP = -0.008;
						else if (calKforP > -0.002) calKforP = -0.002;
						double&& setKforP(this->Read(8)[0]);
						double&& hereKp((calKforP + setKforP) / 2);
						double&& hereIniP(this->Read(9)[0]);
						double&& DePTime(nowBlowTime - oxyAlSi / (oxyFlow[0] / 3600));
						if (DePTime > dbZero)
						{
							double&& CalP(hereIniP * exp(hereKp * DePTime));
							if ((elemAmt[i].second * stlLastWgt - CalP * stlWgt) / 100 > dbZero && (elemAmt[i].second * stlLastWgt - CalP * stlWgt) / 100 < elemOxid)
							{
								elemOxid = (elemAmt[i].second * stlLastWgt - CalP * stlWgt) / 100;
							}
						}
					}
				}

				elemAmt[i].second = (stlWgt * elemAmt[i].second - 100 * elemOxid) / (stlWgt - elemOxid);/*更新元素氧化量*/

				stlTemp = stlTemp + elemTher[i] * elemOxid / stlWgt * 100 * (stlWgt - elemOxid) / stlWgt;/*更新钢液温度*/
				stlWgt = stlWgt - elemOxid;                                                                                                     /*更新钢液重量*/

				oxidAmt[i] = elemOxid * oxidAmt[i];                                                                                         /*更新生成物重量*/
				slagWgt = slagWgt + oxidAmt[i];                                                                                             /*更新炉渣重量*/

				if (OxyAmt > dbZero)                                                                                                               /*更新氧气量及时间*/
				{
					OxyAmt = OxyAmt - elemOxid * elemOxy[i];
					if (OxyAmt < 0) OxyAmt = 0;
				}
				if (OxyAmt < dbZero && fabs(nowBlowTime - blowTime) > dbZero)
				{
					OxyAmt = 0;
					this->Write(7, nowBlowTime, false);
					break;
				}
				else    this->Write(7, SetTime = SetTime + elemOxid * elemOxy[i] / curFlow * 3600, false);
			}
		}
		/*碳氧化*/
		bool tCal(true), TOK(false), eOK(false);
		if (fabs(nowBlowTime - blowTime) > dbZero && OxyAmt < dbZero) tCal = false;             /*需仍有余氧*/
		if (stlTemp >= keyTemp)                                                                       TOK = true;              /*需温度高于临界温度*/
		else if (stlTemp < keyTemp && (elemAmt[seqC - 1].second > setC || stlTemp < setTemp))
		{
			TOK = true;
		}
		if (stlTemp < keyTemp)
		{
			double&& TimeAlSi(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::Time))[0][0]);
			if (TimeAlSi > nonCoxidTime)   nonCoxidTime = TimeAlSi;
		}
		if (elemAmt[seqAl - 1].second - elemAmt[seqAl - 1].first <= dbZero)                                /*需铝硅已反应完毕*/
		{
			if (elemAmt[seqSi - 1].second - elemAmt[seqSi - 1].first <= dbZero)	  eOK = true;
		}
		if (TOK && tCal && eOK)
		{
			if (stlTemp < keyTemp)
			{
				double&& deltaT(keyTemp - stlTemp);
				if (unsigned(keyTemp) == 1530)
				{
					double&& deltaCr(stlWgt * deltaT / elemTher[seqCr - 1] / 100);
					elemAmt[seqCr - 1].second = (stlWgt * elemAmt[seqCr - 1].second / 100 - deltaCr) / (stlWgt - deltaCr) * 100;
					stlWgt = stlWgt - deltaCr;
					oxidAmt[seqCr - 1] = deltaCr * oxidAmt[seqCr - 1];
					slagWgt = slagWgt + oxidAmt[seqCr - 1];
				}
				else
				{
					double&& deltaFe(stlWgt * deltaT / elemTher[seqFe - 1] / 100);
					elemAmt[seqFe - 1].second = (stlWgt * elemAmt[seqFe - 1].second / 100 - deltaFe) / (stlWgt - deltaFe) * 100;
					stlWgt = stlWgt - deltaFe;
					oxidAmt[seqFe - 1] = deltaFe * oxidAmt[seqFe - 1];
					slagWgt = slagWgt + oxidAmt[seqFe - 1];
				}
				stlTemp = keyTemp + 2 * dbZero;
			}
			dbVec endC(2);
			/*成分约束*/
			if (setC - stlAimC < dbZero)		endC[0] = stlAimC;
			else                                              endC[0] = setC;
			/*温度约束*/
			if (fabs(setTemp - stlAimTemp) > dbZero)
			{
				double&& deltaT(setTemp - stlTemp);
				if (deltaT <= dbZero) endC[1] = elemAmt[seqC - 1].second;
				else                  			endC[1] = elemAmt[seqC - 1].second - deltaT / elemTher[seqC - 1];
			}
			else   endC[1] = stlAimC;
			/*时间及氧气量约束*/
			if (fabs(nowBlowTime - blowTime) > dbZero)
			{
				/*double&& curTime(nowBlowTime - nonCoxidTime);
				double&& curIniC(this->Read(2)[0]);
				endC.resize(3);
				for (size_t i = 0; i < keyC.size(); i++)
				{
					if (curIniC >= keyC[i])
					{
						endC[2] = curIniC * exp(kForC[i] * curTime);
						if (endC[2] < keyC[i])
						{
							curTime = curTime - log(keyC[i] / curIniC) / kForC[i];
							curIniC = keyC[i];
							endC[2] = curIniC * exp(kForC[i] * curTime);
						}
						else break;
					}
					else
					{
						curTime = curTime - log(keyC[i] / curIniC) / kForC[i];
					}
				}*/
				double&& curTime(nowBlowTime - blowTime);
				double&& curIniC(this->Read(12)[0]);
				if (nowBlowTime - nonCoxidTime < curTime) curTime = nowBlowTime - nonCoxidTime;
				endC.resize(3);
				for (size_t i = 0; i < keyC.size(); i++)
				{
					if (curIniC >= keyC[i])
					{
						endC[2] = curIniC * exp(kForC[i] * curTime);
						if (endC[2] < keyC[i])
						{
							curTime = curTime - log(keyC[i] / curIniC) / kForC[i];
							endC[2] = keyC[i] * exp(kForC[i] * curTime);
						}
						else break;
					}
				}
				this->Write(12, endC[2], false);
				/*氧气量约束*/
				if (OxyAmt > dbZero)
				{
					double&& COxid(100 * OxyAmt / elemOxy[seqC - 1]);
					double&& eCoxy((stlLastWgt * elemAmt[seqC - 1].second - COxid) / stlWgt);
					if (endC[2] < eCoxy)
					{
						double&& slgFeO(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::FeO))[0][0]);
						double limFeO(10);
						if (slgFeO < limFeO) endC[2] = eCoxy;
						else
						{
							double&& qTime(stlWgt * (elemAmt[seqC - 1].second - endC[2]) / (100 - endC[2]));
							double&& qOxy(stlWgt * (elemAmt[seqC - 1].second - eCoxy) / (100 - eCoxy));
							if (qTime - qOxy > dbZero)
							{
								double&& deltaFeO((qTime - qOxy) * elemOxy[seqC - 1] * 9);
								if ((slgFeO - limFeO) * slagWgt / 100 - deltaFeO > dbZero)
								{
									slgFeO = ((slgFeO - limFeO) * slagWgt / 100 - deltaFeO) / (slagWgt - deltaFeO) * 100;
								}
								else
								{
									double&& qC(stlWgt * elemAmt[seqC - 1].second / 100 - slagWgt * (slgFeO - limFeO) / 100 * 0.2222 / elemOxy[seqC - 1]);
									endC[2] = (stlWgt * elemAmt[seqC - 1].second - 100 * qC) / (stlWgt - qC);
									deltaFeO = slagWgt * (slgFeO - limFeO) / 100;
									slgFeO = limFeO;
								}
								slagWgt = slagWgt - deltaFeO;
								this->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::FeO) + valDev + to_string(slgFeO), false);
								stlWgt = stlWgt + deltaFeO * 0.7778;
							}
						}
					}
				}
			}

			double&& maxEndC(Max(&endC[0], endC.size())); /*确定endC*/


			if (OxyAmt > dbZero)
			{
				if (elemAmt[seqC - 1].second >= maxEndC) OxyAmt = OxyAmt - stlWgt * (elemAmt[seqC - 1].second - maxEndC) / (100 - maxEndC) * elemOxy[seqC - 1];
				else
				{
					OxyAmt = 0;

					double&& deltaC(stlWgt * (maxEndC - elemAmt[seqC - 1].second) / (100 - elemAmt[seqC - 1].second));
					double&& deltaFe(3.5 * deltaC * elemOxy[seqC - 1]);
					stlTemp = stlTemp + deltaFe / stlWgt * 100 * elemTher[seqFe - 1];
					elemAmt[seqFe - 1].second = (stlWgt * elemAmt[seqFe - 1].second - 100 * deltaFe) / (stlWgt - deltaFe);
					oxidAmt[seqFe - 1] = deltaFe * 1.2857;
					slagWgt = slagWgt + deltaFe * 1.2857;

					maxEndC = elemAmt[seqC - 1].second;
				}
			}
			else if (endC.size() == 2)
			{
				dbVec CRE = { 1,0.55,0.32,0.23,0.15 };
				size_t posC(0);
				for (size_t i = 0; i < keyC.size(); i++)
				{
					if (maxEndC > keyC[i])
					{
						posC = i;
						break;
					}
				}
				double beginC(elemAmt[seqC - 1].second), hereStlWgt(stlWgt);
				for (size_t i = 0; i <= posC; i++)
				{
					if (maxEndC <= keyC[i])
					{
						OxyAmt = OxyAmt + hereStlWgt * (beginC - keyC[i]) / (100 - keyC[i]) * elemOxy[seqC - 1] / CRE[i] * (1 - CRE[i]);
						beginC = keyC[i];
						hereStlWgt = hereStlWgt * (100 - beginC) / (100 - keyC[i]);
					}
					else
					{
						OxyAmt = OxyAmt + hereStlWgt * (beginC - maxEndC) / (100 - maxEndC) * elemOxy[seqC - 1] / CRE[i] * (1 - CRE[i]);
					}
				}
			}
			/*氧气不足时*/
			if (OxyAmt < dbZero)
			{
				OxyAmt = OxyAmt + stlWgt * (elemAmt[seqC - 1].second - maxEndC) / (100 - maxEndC) * elemOxy[seqC - 1];
				maxEndC = elemAmt[seqC - 1].second - OxyAmt / elemOxy[seqC - 1] / stlWgt * 100;
				OxyAmt = 0;
			}
			/*氧气过量时*//*缺：当setTemp或setC时，应将Fe或Cr的热效应返还给C，表现C的终点成分变化。为免繁琐，应用时setTemp及setC应设定为高碳区*/
			else
			{
				if (elemAmt[seqCr - 1].second - elemAmt[seqCr - 1].first > dbZero)
				{
					double deltaCr(OxyAmt / elemOxy[seqCr - 1]);
					elemAmt[seqCr - 1].second = (stlWgt * elemAmt[seqCr - 1].second / 100 - deltaCr) / (stlWgt - deltaCr) * 100;
					stlTemp = stlTemp + elemTher[seqCr - 1] * 2 * deltaCr / (2 * stlWgt - deltaCr) * 100;
					stlWgt = stlWgt - deltaCr;
					oxidAmt[seqCr - 1] = deltaCr * oxidAmt[seqCr - 1];
					slagWgt = slagWgt + oxidAmt[seqCr - 1];
				}
				else if (elemAmt[seqFe - 1].second - elemAmt[seqFe - 1].first > dbZero)
				{
					if (elemAmt[seqP - 1].second - elemAmt[seqP - 1].first > dbZero)
					{
						double&& Poxy((stlWgt * elemAmt[seqP - 1].second / 100 - OxyAmt / elemOxy[seqP - 1]) / (stlWgt - OxyAmt / elemOxy[seqP - 1]) * 100);

						double&& bathCaO(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::CaO))[0][0]);
						double&& bathFeO(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::FeO))[0][0]);
						double&& bathFe2O3(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::Fe2O3))[0][0]);
						double&& TFe(0.78 * bathFeO + 0.7 * bathFe2O3);
						double&& ratioP(pow(10, 22350 / (273.15 + stlTemp) - 16 + 0.08 * bathCaO + 2.5 * log10(TFe)));
						double&& slagP(0.4366 * this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::P2O5))[0][0]);
						double&& calP(slagP / ratioP);

						double endP(0);
						if (calP < Poxy || calP > elemAmt[seqP - 1].second)
						{
							OxyAmt = 0;
							endP = Poxy;
						}
						else
						{
							OxyAmt = OxyAmt - stlWgt * (elemAmt[seqP - 1].second - calP) / (100 - calP) * elemOxy[seqP - 1];
							endP = calP;
						}
						if (endP < elemAmt[seqP - 1].first) endP = elemAmt[seqP - 1].second;
						double&& deltaP(stlWgt * (elemAmt[seqP - 1].second - endP) / (100 - endP));
						stlTemp = stlTemp + elemTher[seqP - 1] * deltaP / (stlWgt - deltaP) * 100;
						stlWgt = stlWgt - deltaP;
						oxidAmt[seqP - 1] = deltaP * oxidAmt[seqP - 1];
						slagWgt = slagWgt + oxidAmt[seqP - 1];
						elemAmt[seqP - 1].second = endP;
					}
					double deltaFe(OxyAmt / elemOxy[seqFe - 1]);
					elemAmt[seqFe - 1].second = (stlWgt * elemAmt[seqFe - 1].second / 100 - deltaFe) / (stlWgt - deltaFe) * 100;
					stlTemp = stlTemp + elemTher[seqFe - 1] * deltaFe / (stlWgt - deltaFe) * 100;
					stlWgt = stlWgt - deltaFe;
					oxidAmt[seqFe - 1] = deltaFe * oxidAmt[seqFe - 1];
					slagWgt = slagWgt + oxidAmt[seqFe - 1];
				}
			}
			//更新钢液温度重量、成分及时间
			stlTemp = stlTemp + elemTher[seqC - 1] * (elemAmt[seqC - 1].second - maxEndC) * (100 - elemAmt[seqC - 1].second) / (100 - maxEndC);
			stlWgt = stlWgt * (100 - elemAmt[seqC - 1].second) / (100 - maxEndC);
			if (endC.size() < 3 || maxEndC - endC[2] > dbZero) SetTime = SetTime + stlLastWgt * (elemAmt[seqC - 1].second - maxEndC) / (100 - maxEndC) * elemOxy[seqC - 1] / curFlow * 3600;
			else                                                                             SetTime = nowBlowTime;
			elemAmt[seqC - 1].second = maxEndC;
			this->Write(7, SetTime, false);
		}
		//首先更新温度
		{/*考虑底吹冷却*/
			double&& HereGasTher(GasTher / ((stlLastWgt + stlWgt) / 2000) * stlWgt / stlLastWgt);
			stlTemp = stlTemp + HereGasTher * BotFlow / 3600 * (nowBlowTime - blowTime) * ((stlTemp + stlLastTemp) / 2 - 25);
		}
		{  /*考虑辐射冷却*/
			double&& t(nowBlowTime - blowTime), radioT((stlTemp + stlLastTemp) / 200);
			radioT = k * s * 0.007168 * t * pow(radioT, 4) / ((stlWgt + stlLastWgt) / 2000);/*℃/t钢*/
			stlTemp = stlTemp - radioT;
		}
		{   /*考虑炉衬散热冷却*/
			stlTemp = stlTemp + HeatVal / ((stlWgt + stlLastWgt) / 2000) * ((nowBlowTime - blowTime) / 60) * AveLen * AveSqr;
		}
		stlTemp = stlTemp + slagTher * slagLastWgt / stlWgt * 100 * (stlTemp - slagTemp);
		slagTemp = stlTemp;
		//更新钢水及炉渣成分信息
		qVec = this->Read(myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl));
		for (size_t i = 0; i < qVec.size(); i++)
		{
			bool Equal(false);
			IDN oxiElemName(IDN::IDFail);
			double oxiElemVal(0);
			for (size_t j = 0; j < elemN; j++)/*参与氧化的元素*/
			{
				if (IDN(qVec[i][3]) == elemName[j] && elemAmt[j].second - elemAmt[j].first > dbZero)
				{
					Equal = true;
					this->Write(strT = myStr + lblDev + IDNTrans(elemName[j]) + valDev + to_string(elemAmt[j].second), false);
					break;
				}
				else if (IDN(qVec[i][3]) == elemName[j])
				{
					oxiElemName = elemName[j];
					oxiElemVal = elemAmt[j].second;
				}
			}
			if (!Equal && IDN(qVec[i][3]) != IDN::Thermal1 && IDN(qVec[i][3]) != IDN::Thermal2)/*未参与氧化的元素*/
			{
				if (IDN(qVec[i][3]) != oxiElemName)
				{
					this->Write(strT = myStr + lblDev + IDNTrans(IDN(qVec[i][3])) + valDev + to_string(stlLastWgt * qVec[i][0] / stlWgt), false);
				}
				else
				{
					this->Write(strT = myStr + lblDev + IDNTrans(IDN(qVec[i][3])) + valDev + to_string(stlLastWgt * oxiElemVal / stlWgt), false);
				}
			}
		}
		qVec = this->Read(myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag));
		for (size_t i = 0; i < qVec.size(); i++)
		{
			bool Equal(false);
			for (size_t j = 0; j < elemN; j++)
			{
				if (IDN(qVec[i][3]) == oxidName[j])
				{
					Equal = true;
					this->Write(strT = myStr + lblDev + IDNTrans(oxidName[j]) + valDev + to_string((slagLastWgt * qVec[i][0] / 100 + oxidAmt[j]) / slagWgt * 100), false);
					break;
				}
			}
			if (!Equal && IDN(qVec[i][3]) != IDN::Thermal1 && IDN(qVec[i][3]) != IDN::Thermal2)
			{
				this->Write(strT = myStr + lblDev + IDNTrans(IDN(qVec[i][3])) + valDev + to_string(slagLastWgt * qVec[i][0] / slagWgt), false);
			}
		}
		this->Write(0, nowBlowTime, false);
	}
	//后根据加入的料，进一步更新熔池状态
	bool Flag[3] = { false, false, false };  /*加入的物料以Scrp或Flux或Alloy开头*/
	for (size_t i = 0; i < 3; i++)
	{
		if (i == 0) qVec = this->Read(myStr = IDNTrans(IDN::Scrp));
		else if (i == 1) qVec = this->Read(myStr = IDNTrans(IDN::Flux));
		else if (i == 2) qVec = qVec = this->Read(myStr = IDNTrans(IDN::Alloy));
		if (qVec.size() > 0)
		{
			Flag[i] = true;
			break;
		}
	}
	if (Flag[0] || Flag[1] || Flag[2])
	{
		//准备参数：输入的物质重量、温度
		double&& matWgt(this->Read(strT = IDNTrans(IDN(qVec[0][1])) + lblDev + IDNTrans(IDN(qVec[0][2])) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
		if (!Flag[0]) matWgt = matWgt + this->Read(strT = IDNTrans(IDN(qVec[0][1])) + lblDev + IDNTrans(IDN(qVec[0][2])) + lblDev + IDNTrans(IDN::CWgt))[0][0];
		double&& matTemp((this->Read(strT = IDNTrans(IDN(qVec[0][1])) + lblDev + IDNTrans(IDN(qVec[0][2])) + lblDev + IDNTrans(IDN::Temp))[0][0]));
		double&& matTher((this->Read(strT = IDNTrans(IDN(qVec[0][1])) + lblDev + IDNTrans(IDN(qVec[0][2])) + lblDev + IDNTrans(IDN::Thermal1))[0][0]));
		if (fabs(matWgt) > dbZero)
		{
			/*更新温度*/
			stlTemp = stlTemp + matTher * matWgt / stlWgt * 100 + slagTher * slagWgt / stlWgt * 100 * (stlTemp - slagTemp);
			slagTemp = stlTemp;
			/*更新成分*/
			if (Flag[2]) myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl);
			else if (Flag[1]) myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag);
			else if (Flag[0]) myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl);
			IDN matElem(IDN::IDFail);
			double elemBath(0);
			for (size_t i = 0; i < qVec.size(); i++)
			{
				matElem = IDN(qVec[i][3]);
				if (matElem <= IDN::Fe && matElem >= IDN::C)
				{
					elemBath = this->Read(strT = myStr + lblDev + IDNTrans(matElem))[0][0];
					this->Write(strT = myStr + lblDev + IDNTrans(matElem) + valDev + to_string((elemBath * stlWgt + qVec[i][0] * matWgt) / (stlWgt + matWgt)), false);
				}
				else if (matElem < IDN::Burnt && matElem >= IDN::CaO)
				{
					elemBath = this->Read(strT = myStr + lblDev + IDNTrans(matElem))[0][0];
					this->Write(strT = myStr + lblDev + IDNTrans(matElem) + valDev + to_string((elemBath * slagWgt + qVec[i][0] * matWgt) / (slagWgt + matWgt)), false);
				}
				else if (matElem == IDN::Burnt)  matWgt = matWgt * (100 - qVec[i][0]) / 100;
			}
			/*更新重量*/
			IDN objType;
			objType = IDN(qVec[0][1]);
			if (objType == IDN::Slag || objType == IDN::Flux)
			{
				slagWgt = slagWgt + matWgt;
			}
			else if (objType == IDN::Alloy)
			{
				stlWgt = stlWgt + matWgt;
			}
			else if (objType == IDN::Scrp)
			{
				double&& slagInScrp(this->Read(strT = IDNTrans(IDN::Scrp) + lblDev + IDNTrans(IDN(qVec[0][2])) + lblDev + IDNTrans(IDN::Slag))[0][0]);
				slagInScrp = matWgt * slagInScrp / 100;
				//由于废钢中的炉渣，需要先对其成分进行重新计算
				for (size_t i = 0; i < qVec.size(); i++)
				{
					matElem = IDN(qVec[i][3]);
					if (matElem <= IDN::Fe && matElem >= IDN::C)
					{
						elemBath = this->Read(strT = myStr + lblDev + IDNTrans(matElem))[0][0];
						this->Write(strT = myStr + lblDev + IDNTrans(matElem) + valDev + to_string((elemBath * stlWgt + qVec[i][0] * matWgt) / (stlWgt + matWgt - slagInScrp)), false);
					}
				}
				stlWgt = stlWgt + matWgt - slagInScrp;
				slagWgt = slagWgt + slagInScrp;

				/*更新iniC及oxyAlSi*/
				myStr = IDNTrans(IDN::Para);
				myStr = myStr + lblDev + IDNTrans(IDN::Stl) + lblDev;
				iniC = this->Read(strT = myStr + IDNTrans(IDN::C))[0][0];
				this->Write(2, iniC, false);

				dbVec iniAlSi(4);
				iniAlSi[0] = this->Read(strT = myStr + IDNTrans(IDN::Al))[0][0];
				iniAlSi[1] = this->Read(strT = myStr + IDNTrans(IDN::Si))[0][0];
				iniAlSi[2] = this->Read(strT = myStr + IDNTrans(IDN::V))[0][0];
				iniAlSi[3] = this->Read(strT = myStr + IDNTrans(IDN::Mn))[0][0];
				double stlWgt(this->Read(strT = myStr + IDNTrans(IDN::Wgt))[0][0]);
				dbVec elemLLim{ 0.003, 0.04,0.12,0.12 };
				double O2AlSi(0);
				for (size_t i = seqAl - 1; i < seqMn; i++) 	O2AlSi = O2AlSi + (iniAlSi[i] - elemLLim[i]) * stlWgt / 100 * elemOxy[i];
				this->Write(3, O2AlSi, false);
			}
		}
		if (Flag[0]) myStr = IDNTrans(IDN::Scrp);
		else if (Flag[1]) myStr = IDNTrans(IDN::Flux);
		else if (Flag[2]) myStr = IDNTrans(IDN::Alloy);
		this->Del(myStr, true);
	}
	//成分在上面已实现更新，现更新温度和重量信息（另，增加铁的转化）
	double&& slgFe2O3(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::Fe2O3))[0][0]);
	if (slgFe2O3 > dbZero)
	{
		double&& slgFeO(this->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::FeO))[0][0]);
		slgFeO = (1.35 * slgFe2O3 + slgFeO) * slagWgt / 100;
		stlWgt = stlWgt - slgFe2O3 * 0.35 * slagWgt / 100;
		slagWgt = slagWgt + slgFe2O3 * 0.35 * slagWgt / 100;
		slgFeO = slgFeO / slagWgt * 100;
		this->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::FeO) + valDev + to_string(slgFeO), false);
		this->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::Fe2O3) + valDev + "0", false);
	}
	this->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Wgt) + valDev + to_string(stlWgt), false);
	this->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Temp) + valDev + to_string(stlTemp), false);
	this->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::Wgt) + valDev + to_string(slagWgt), false);
	this->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::Temp) + valDev + to_string(slagTemp), false);

	return true;
}
//策略规划：加料量、加料时点、供氧量、枪位、变枪时点
Predict::Predict(DataIO& objIO) :objBS(objIO), objPF(objIO), objMF(objIO)
{
	string myStr(""), strT("");
	ptrIO = &objIO;
	ptrBS = &objBS;   	ptrPF = &objPF;   	ptrMF = &objMF;

	/*静态计算用的标志变量，在能量计算函数中最后更新*/
	myStr = IDNTrans(IDN::Para);
	this->Add(strT = myStr + lblDev + IDNTrans(IDN::LTempSyb) + valDev + "0", false);
	this->Add(strT = myStr + lblDev + IDNTrans(IDN::HTempSyb) + valDev + "0", false);
	this->Add(strT = myStr + lblDev + IDNTrans(IDN::LLTempSyb) + valDev + "0", false);
	this->Add(strT = myStr + lblDev + IDNTrans(IDN::HHTempSyb) + valDev + "0", false);
	this->BuildIndex();
}
bool Predict::metalMass()
{
	string strT(""), myStr("");
	DCVec qVec;
	//得到钢液初始状态：加入废钢
	uuPVec IOIndex(ptrIO->GetIndex());
	for (size_t i = 0; i < IOIndex.size(); i++)
	{
		if (IDN(ptrIO->Read(IOIndex[i].first)[1]) == IDN::Scrp)
		{
			for (size_t j = IOIndex[i].first; j <= IOIndex[i].second; j++)	ptrBS->Add(ptrIO->Read(j));
			ptrBS->BuildIndex();
			ptrBS->Write(0, 0, true);
		}
	}
	DCVec().swap(qVec);
	uuPVec().swap(IOIndex);
	//解合金用量线性方程组                                                                                                                          
	idVec   alloyElem, siloName, mainElem1, mainElem2;                                                                                            /*准备解线性方程组所需的向量*/
	dbVec compAim, compIni, Ratio, compME1, compME2, compFe, compCWgt;
	myStr = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Low) + lblDev;
	qVec = ptrIO->Read(myStr);
	for (size_t i = 0; i < qVec.size(); i++)
	{
		IDN elemName = IDN(qVec[i][4]);
		if (elemName == IDN::Cr || elemName == IDN::Ni || elemName == IDN::Mo || elemName == IDN::Cu)
		{
			if (qVec[i][0] > dbZero) alloyElem.push_back(elemName);
		}
	}
	if (alloyElem.size() > 0)
	{
		//矩阵方程参数：比例、主元素1/2的成分、铁成分、固定加入量、目标成分、起始成分
		myStr = IDNTrans(IDN::Alloy) + lblDev;
		qVec = ptrIO->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
		for (size_t i = 0; i < qVec.size(); i++)
		{
			IDN mainElem = IDN(qVec[i][0]);
			for (size_t j = 0; j < alloyElem.size(); j++)
			{
				if (mainElem == alloyElem[j])
				{
					mainElem1.push_back(mainElem);
					mainElem2.push_back(IDN(ptrIO->Read(strT = myStr + IDNTrans(IDN(qVec[i][2])) + lblDev + IDNTrans(IDN::MElem2))[0][0]));
					siloName.push_back(IDN(qVec[i][2]));
					compIni.push_back(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(mainElem))[0][0]);
					compAim.push_back(ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(mainElem))[0][0]);
					Ratio.push_back(ptrIO->Read(strT = myStr + IDNTrans(siloName[siloName.size() - 1]) + lblDev + IDNTrans(IDN::Ratio))[0][0]);
					compME1.push_back(ptrIO->Read(strT = myStr + IDNTrans(siloName[siloName.size() - 1]) + lblDev + IDNTrans(mainElem1[mainElem1.size() - 1]))[0][0]);
					DCVec X = ptrIO->Read(strT = myStr + IDNTrans(siloName[siloName.size() - 1]) + lblDev + IDNTrans(mainElem2[mainElem2.size() - 1]));
					if (X.size() == 1) compME2.push_back(X[0][0]);
					else                     compME2.push_back(0);
					compFe.push_back(ptrIO->Read(strT = myStr + IDNTrans(siloName[siloName.size() - 1]) + lblDev + IDNTrans(IDN::Fe))[0][0]);
					compCWgt.push_back(ptrIO->Read(strT = myStr + IDNTrans(siloName[siloName.size() - 1]) + lblDev + IDNTrans(IDN::CWgt))[0][0]);
					break;
				}
			}
		}
		//解矩阵方程
		dbVec equationA, equationB;                                                                                                                                /*矩阵系数A及B*/
		equationA.resize(compAim.size() * Ratio.size());
		for (size_t i = 0; i < compAim.size(); i++)                                                                                                              /*矩阵方程左侧*/
		{
			for (size_t j = 0; j < Ratio.size(); j++)
			{
				if (i == j)
				{
					equationA[i * compAim.size() + j] = compAim[i] * Ratio[i] - compME1[i];
				}
				else
				{
					equationA[i * compAim.size() + j] = compAim[i] * Ratio[i];
				}
			}
		}
		double&& cmbWgt(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
		equationB.resize(compIni.size());                                                                                                                           /*矩阵方程右侧*/
		for (size_t i = 0; i < compIni.size(); i++)   equationB[i] = cmbWgt * Ratio[i] * (compIni[i] - compAim[i]);
		dbVec alloyWgt(Matrix(&equationA[0], &equationB[0], size_t(equationB.size())));                                              /*解方程*/
		for (size_t i = 0; i < alloyWgt.size(); i++)                                                                                                                /*写入计算结果：合金重量*/
		{
			alloyWgt[i] = alloyWgt[i] * (compFe[i] + compME1[i] + compME2[i]) / 100 - compCWgt[i];
			qVec = ptrIO->Read(strT = IDNTrans(IDN::Alloy) + lblDev + IDNTrans(siloName[i]));
			for (size_t j = 0; j < qVec.size(); j++)
			{
				if (IDN(qVec[j][3]) == IDN::Wgt)
				{
					qVec[j] = alloyWgt[i];
					break;
				}
			}
			this->Add(qVec, false);
		}
		this->BuildIndex();
		return true;
	}
	else	return false;
}
bool Predict::fluxMass()
{
	string strT(""), myStr("");
	DCVec qVec;
	dbVec paraArr(11);                                                                                                          /*读取其他所需参数并初始化pureFlux所需的参数向量*/
	myStr = IDNTrans(IDN::Para);
	qVec = ptrIO->Read(strT = myStr + lblDev + IDNTrans(IDN::Basic));
	for (size_t i = 0; i < qVec.size(); i++)
	{
		if (IDN(qVec[i][3]) == IDN::LSi)        paraArr[0] = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::USi)        paraArr[1] = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::LBa)       paraArr[2] = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::UBa)      paraArr[3] = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::CeqMn) paraArr[4] = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::RedSi)    paraArr[5] = qVec[i][0];
	}
	qVec = ptrIO->Read(strT = myStr + lblDev + IDNTrans(IDN::PureFlux));
	for (size_t i = 0; i < qVec.size(); i++)
	{
		if (IDN(qVec[i][3]) == IDN::CMgO)   paraArr[6] = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::CCaF2)      paraArr[7] = qVec[i][0];
	}
	qVec = ptrBS->Read(strT = myStr + lblDev + IDNTrans(IDN::Stl));
	for (size_t i = 0; i < qVec.size(); i++)
	{
		if (IDN(qVec[i][3]) == IDN::Si)     paraArr[8] = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::Mn)   paraArr[9] = qVec[i][0];
		else if (IDN(qVec[i][3]) == IDN::Wgt) paraArr[10] = qVec[i][0];
	}
	//纯熔剂计算
	ptrPF->Set(myStr, &paraArr[0], size_t(paraArr.size()), true);

	//计算各物料所需重量
	dbVec().swap(paraArr);                                                                                                 /*准备计算所需的参数向量*/
	paraArr.resize(8);
	qVec = ptrPF->Read(strT = IDNTrans(IDN::Result));
	for (size_t i = 0; i < qVec.size(); i++)
	{
		if (IDN(qVec[i][2]) == IDN::PureCaO)  paraArr[0] = qVec[i][0];
		else if (IDN(qVec[i][2]) == IDN::PureMgO) paraArr[1] = qVec[i][0];
		else if (IDN(qVec[i][2]) == IDN::PureCaF2) paraArr[2] = qVec[i][0];
		else if (IDN(qVec[i][2]) == IDN::Basicity)    paraArr[3] = qVec[i][0];
	}
	DCVec paraME, paraMEC, paraSiO2, paraRatio;                                                           /*读取IO中的有关参数*/
	myStr = IDNTrans(IDN::Flux) + lblDev;
	paraME = ptrIO->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
	paraSiO2 = ptrIO->Read(strT = myStr + lblDev + IDNTrans(IDN::SiO2));
	paraRatio = ptrIO->Read(strT = myStr + lblDev + IDNTrans(IDN::Ratio));
	paraMEC.resize(paraME.size());                                                                                    /*读取主元素的含量*/
	for (size_t i = 0; i < paraME.size(); i++)
	{
		IDN mainElem = IDN(paraME[i][0]);
		if (mainElem != IDN::Empty && mainElem != IDN::IDFail && unsigned(mainElem) != 0)
		{
			paraMEC[i] = ptrIO->Read(strT = myStr + IDNTrans(IDN(paraME[i][2])) + lblDev + IDNTrans(IDN(paraME[i][0])))[0][0];
		}
		else
		{
			paraMEC[i] = 0;
		}
	}
	myStr = IDNTrans(IDN::Flux) + lblDev;                                                                          /*依次更新各料仓的参数向量，并计算其重量*/
	qVec = ptrIO->Read(strT = myStr + lblDev + IDNTrans(IDN::CWgt));
	dbVec cWgt(paraME.size());
	for (size_t i = 0; i < paraME.size(); i++)
	{
		for (size_t j = 0; j < qVec.size(); j++)
		{
			if (IDN(paraME[i][2]) == IDN(qVec[j][2]))
			{
				cWgt[i] = qVec[j][0];
				break;
			}
		}
	}
	//依次计算各料仓用量，并写入结果*/
	for (size_t i = 0; i < paraME.size(); i++)
	{
		paraArr[4] = paraME[i][0];                                                                                                                    /*参数准备*/
		paraArr[5] = paraMEC[i][0];
		paraArr[6] = paraSiO2[i][0];
		paraArr[7] = paraRatio[i][0];
		ptrMF->Set(strT = IDNTrans(IDN::Para), &paraArr[0], size_t(paraArr.size()), true);                             /*计算*/
		myStr = IDNTrans(IDN::Result);
		double&& siloWgt(ptrMF->Read(strT = myStr + lblDev + IDNTrans(IDN::MatFlux))[0][0] - cWgt[i]);
		ptrMF->Write(strT = myStr + lblDev + IDNTrans(IDN::MatFlux) + valDev + "0", false);

		IDN siloName = IDN(paraME[i][2]);                                                                                                      /*写入结果*/
		if (siloWgt > dbZero)
		{
			qVec = ptrIO->Read(strT = IDNTrans(IDN::Flux) + lblDev + IDNTrans(siloName));
			for (size_t j = 0; j < qVec.size(); j++)
			{
				if (IDN(qVec[j][3]) == IDN::Wgt)
				{
					qVec[j] = siloWgt;
					break;
				}
			}
			this->Add(qVec, true);
		}
	}
	return true;
}
bool Predict::oreCal()
{
	string strT(""), myStr("");
	double caliT(0);/*温度修正项*/
	{
		double CoeA(0), CoeB(0), VarX(0);
		DCVec lastTemp;
		dbVec LastTemp;
		lastTemp = ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::History) + lblDev + IDNTrans(IDN::Temp));
		LastTemp.resize(lastTemp.size());
		for (size_t i = 0; i < lastTemp.size(); i++) LastTemp[i] = lastTemp[i][0];

		CoeB = SDev(&LastTemp[0], unsigned(LastTemp.size()));
		CoeA = CoeB - Ave(&LastTemp[0], unsigned(LastTemp.size()));
		VarX = (CoeB - CoeA + Mid(&LastTemp[0], unsigned(LastTemp.size()))) / 2;
		if (VarX > 0) caliT = 2 * CoeA / PI * atan(VarX) - CoeB;
		else              caliT = -(2 * CoeA / PI * atan(VarX) + CoeB);
	}

	//汇总各项热量输入输出，得出温度差值，以决定需冷却或升温
	myStr = IDNTrans(IDN::Para);
	strT = myStr + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Temp);
	double&& stlT(ptrBS->Read(strT)[0][0]);
	strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Temp);
	double&& stlAimT(ptrIO->Read(strT)[0][0]);
	double&& deltaT = stlT + caliT - stlAimT;
	double&& deltaTLLim(ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev + IDNTrans(IDN::LLimTDelta))[0][0]);
	double&& deltaTULim(ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev + IDNTrans(IDN::ULimTDelta))[0][0]);
	if (deltaT < deltaTLLim)
	{
		this->Write(2, 1, false);
		deltaT = deltaTLLim;
	}
	else if (deltaT > deltaTULim)
	{
		this->Write(3, 1, false);
		deltaT = deltaTULim;
	}
	if (deltaT >= deltaTLLim && deltaT < 0)
	{
		this->Write(0, 1, false);
	}
	else if (deltaT <= deltaTULim && deltaT > 0)
	{
		this->Write(1, 1, false);

		IDN coolType(IDN::IDFail), coolMEName(IDN::IDFail);   /*确定冷却物料的类型*/
		if (unsigned(ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev + IDNTrans(IDN::CoolMat))[0][0]) == 0)
		{
			coolType = IDN::Flux;
			coolMEName = IDN::Fe2O3;
		}
		else
		{
			coolType = IDN::Alloy;
			coolMEName = IDN::Fe;
		}

		DCVec mainElem;
		IDN oreSilo;
		myStr = IDNTrans(coolType) + lblDev;
		mainElem = ptrIO->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
		for (size_t i = 0; i < mainElem.size(); i++)
		{
			if (IDN(mainElem[i][0]) == coolMEName)
			{
				oreSilo = IDN(mainElem[i][2]);
				double oreTher(0), oreRatio(0), oreCWgt(0);
				DCVec qVec(ptrIO->Read(strT = IDNTrans(coolType) + lblDev + IDNTrans(oreSilo)));
				for (size_t j = 0; j < qVec.size(); j++)
				{
					if (IDN(qVec[j][3]) == IDN::Thermal1)       oreTher = oreTher + qVec[j][0];
					else if (IDN(qVec[j][3]) == IDN::Thermal2)       oreTher = oreTher + qVec[j][0];
					else if (IDN(qVec[j][3]) == IDN::Ratio)              oreRatio = qVec[j][0];
					else if (IDN(qVec[j][3]) == IDN::CWgt)             oreCWgt = qVec[j][0];
				}

				myStr = IDNTrans(IDN::Para) + lblDev;
				double&& StlWgt(ptrBS->Read(strT = myStr + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Wgt))[0][0]);

				double&& oreWgt(-deltaT / oreTher / 100 * StlWgt * oreRatio - oreCWgt);
				if (oreWgt < dbZero) oreWgt = 0;

				for (size_t j = 0; j < qVec.size(); j++)     /*计算结果写入IO数据*/
				{
					if (IDN(qVec[j][3]) == IDN::Wgt)
					{
						qVec[j] = oreWgt;
						break;
					}
				}
				this->Add(qVec, false);
				this->BuildIndex();
			}
		}
	}
	return true;
}
bool Predict::oxyMass()
{
	string strT(""), myStr("");
	DCVec qVec;
	//计算固态氧
	double solidOxy(0);
	{
		myStr = IDNTrans(IDN::Flux) + lblDev;
		DCVec oreArr;
		qVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
		for (size_t i = 0; i < qVec.size(); i++)  if (IDN(qVec[i][0]) == IDN::Fe2O3) oreArr.push_back(qVec[i]);
		for (size_t i = 0; i < oreArr.size(); i++)
		{
			double siloWgt(0);
			IDN siloName = IDN(oreArr[i][2]);
			qVec = this->Read(strT = IDNTrans(IDN::Flux) + lblDev + IDNTrans(siloName));
			for (size_t j = 0; j < qVec.size(); j++)
			{
				if (IDN(qVec[j][3]) == IDN::Wgt)     siloWgt = qVec[j] + siloWgt;
				else if (IDN(qVec[j][3]) == IDN::CWgt)   siloWgt = qVec[j] + siloWgt;
			}
			for (size_t j = 0; j < qVec.size(); j++)
			{
				if (IDN(qVec[j][3]) == IDN::FeO)      solidOxy = solidOxy + qVec[j] * siloWgt * 16 / 7200;
				else if (IDN(qVec[j][3]) == IDN::Fe2O3)  solidOxy = solidOxy + qVec[j] * siloWgt * 48 / 16000;
			}
		}
		solidOxy = solidOxy * 22.4 / 32;
	}

	//根据三种原理计算气态氧量
	{
		dbVec oxyAmt(3);

		myStr = IDNTrans(IDN::Para);                                                                                        /*数据准备*/
		myStr = myStr + lblDev + IDNTrans(IDN::Ini) + lblDev;
		double&& IniC(ptrBS->Read(strT = myStr + IDNTrans(IDN::C))[0][0]);
		double&& OxySi(ptrBS->Read(strT = myStr + IDNTrans(IDN::OxyAlSi))[0][0]);
		myStr = IDNTrans(IDN::Para);
		myStr = myStr + lblDev + IDNTrans(IDN::Stl) + lblDev;
		double&& StlWgt(ptrBS->Read(strT = myStr + IDNTrans(IDN::Wgt))[0][0]);

		double&& AimC(ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::C))[0][0]);

		dbVec keyC, kForC, OxyFlow;
		double qtyFe(0), qtyCr(0);
		myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static);
		qVec = ptrIO->Read(myStr);
		for (size_t i = 0; i < qVec.size(); i++)
		{
			if (IDN(qVec[i][3]) == IDN::keyC)            keyC.push_back(qVec[i][0]);
			else if (IDN(qVec[i][3]) == IDN::kForC)           kForC.push_back(qVec[i][0]);
			else if (IDN(qVec[i][3]) == IDN::OxyFlow)       OxyFlow.push_back(qVec[i][0] / 3600);
			else if (IDN(qVec[i][3]) == IDN::QtyFe)           qtyFe = qVec[i][0] / 10;
			else if (IDN(qVec[i][3]) == IDN::QtyCr)           qtyCr = qVec[i][0] / 10;
			else if (IDN(qVec[i][3]) == IDN::LastOxyAmt) oxyAmt[2] = qVec[i][0];                                                 /*上次氧耗*/
		}
		keyC.push_back(AimC);
		double offsetOxy(OxyFlow[OxyFlow.size() - 1]);
		for (size_t i = 0; i < kForC.size() - OxyFlow.size(); i++) OxyFlow.push_back(offsetOxy);
		double hereIniC(IniC);                                                                                                                                  /*动力学*/
		oxyAmt[0] = OxySi - solidOxy;
		for (size_t i = 0; i < kForC.size(); i++)
		{
			oxyAmt[0] = oxyAmt[0] + OxyFlow[i] * log(keyC[i] / hereIniC) / kForC[i];
			hereIniC = keyC[i];
		}
		oxyAmt[1] = (IniC * 0.9339 + qtyFe * 0.2 + qtyCr * 0.311) * StlWgt / 100 - solidOxy + OxySi;                 /*静力学*/
		double oxyAmt_Max(Max(&oxyAmt[0], 3));                                                                                                /*计算并写入结果*/
		double oxyAmt_Min(Min(&oxyAmt[0], 3));
		double oxyAmt_Mid(Mid(&oxyAmt[0], 3));
		myStr = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::OxyAmt) + valDev;
		if (oxyAmt_Max - oxyAmt_Min > 500 && oxyAmt_Mid - oxyAmt_Min > 250)
		{
			this->Add(strT = myStr + to_string((oxyAmt_Max + oxyAmt_Mid) / 2));
		}
		else if (oxyAmt_Max - oxyAmt_Min > 500 && oxyAmt_Mid - oxyAmt_Min <= 250)
		{
			this->Add(strT = myStr + to_string((oxyAmt_Min + oxyAmt_Mid) / 2));
		}
		else
		{
			this->Add(strT = myStr + to_string((oxyAmt_Max + oxyAmt_Min) / 2));
		}
		this->BuildIndex();
	}
	return true;
}
bool Predict::matFeed()
{
	string strT(""), myStr("");
	DCVec qVec;

	vector<pair<double, pair<string, double> > > matMix;                                                /*加料规划：何时、何料、几何*/

	strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::KeyTemp);                                 /*脱碳临界温度*/
	double&& keyTemp(ptrBS->Read(strT)[0][0]);
	pair<double, double> slgMeltTemp(1250, 1300);                                                          /*化渣温度区间*/
	pair<double, double> midC(1.5, 3);                                                                                /*调渣碳量区间：碳含量不可太低，否则状态计算中无法考虑各阶段不同氧量*/

	//计算初始石灰类材料加入：护炉
	{
		double iniBasic(1.8);                                                                                                           /*起始护炉碱度*/
		double firstBtime(15);                                                                                                        /*起始护炉料的加入时间*/
		if (ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Low) + lblDev + IDNTrans(IDN::Cr))[0][0] > 6)
		{
			firstBtime = 0;
		}
		myStr = IDNTrans(IDN::Para) + lblDev;
		double&& iniSi(ptrBS->Read(strT = myStr + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Si))[0][0]);
		double&& iniStlWgt(ptrBS->Read(strT = myStr + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
		double&& iniCaO(ptrBS->Read(strT = myStr + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::CaO))[0][0]);
		double&& iniSiO2(ptrBS->Read(strT = myStr + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::SiO2))[0][0]);
		double&& iniSlgWgt(ptrBS->Read(strT = myStr + IDNTrans(IDN::Slag) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
		double&& requireCaO((iniStlWgt * iniSi * 2.14 + iniSlgWgt * iniSiO2) * iniBasic - iniSlgWgt * iniCaO);

		myStr = IDNTrans(IDN::Flux) + lblDev;
		qVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
		for (size_t i = 0; i < qVec.size(); i++)
		{
			if (IDN(qVec[i][0]) == IDN::CaO)
			{
				IDN siloName = IDN(qVec[i][2]);
				myStr = IDNTrans(IDN::Flux) + lblDev + IDNTrans(siloName) + lblDev;
				double&& siloCaO(this->Read(strT = myStr + IDNTrans(IDN::CaO))[0][0]);
				double&& siloSiO2(this->Read(strT = myStr + IDNTrans(IDN::SiO2))[0][0]);
				double&& siloWgt(this->Read(strT = myStr + IDNTrans(IDN::Wgt))[0][0]);
				if (requireCaO > dbZero)
				{
					double&& feedLime(requireCaO / (siloCaO - siloSiO2 * iniBasic));
					if (feedLime <= siloWgt)
					{
						matMix.push_back(make_pair(firstBtime, make_pair(IDNTrans(siloName), feedLime)));/*记录配料方案*/
						this->Write(strT = myStr + IDNTrans(IDN::Wgt) + valDev + to_string(siloWgt - feedLime), false);/*更新本类中的加料数据*/
						requireCaO = requireCaO - feedLime * (siloCaO - siloSiO2 * iniBasic);
					}
					else
					{
						matMix.push_back(make_pair(firstBtime, make_pair(IDNTrans(siloName), siloWgt)));
						this->Write(strT = myStr + IDNTrans(IDN::Wgt) + valDev + "0", false);
						requireCaO = requireCaO - siloWgt * (siloCaO - siloSiO2 * iniBasic);
					}
					DCVec tVec = this->Read(myStr);                                                                  /*更新钢液状态*/
					for (size_t j = 0; j < tVec.size(); j++)
					{
						if (IDN(tVec[j][3]) == IDN::Wgt)
						{
							tVec[j] = matMix[matMix.size() - 1].second.second;
						}
						else if (IDN(tVec[j][3]) == IDN::CWgt) tVec[j] = 0;
					}
					ptrBS->Add(tVec, true);
					strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::New) + lblDev + IDNTrans(IDN::Time) + valDev;
					strT = strT + to_string(matMix[matMix.size() - 1].first);
					ptrBS->Write(strT, true);
				}
			}
		}
	}
	//计算达到化渣温度时的石灰类材料加入：化渣；//矿石类材料：创造化渣条件、降低脱碳临界温度;
	{
		//确定加料时间
		double&& iniSetTemp(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::Temp))[0][0]);
		strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::Temp) + valDev + to_string((slgMeltTemp.first + slgMeltTemp.second) / 2);
		ptrBS->Write(strT, true);
		ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::Temp) + valDev + to_string(iniSetTemp), false);
		strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::Time);
		double&& secondBtime(ptrBS->Read(strT)[0][0]);

		idVec siloName;
		//确定石灰加料料仓及重量
		myStr = IDNTrans(IDN::Flux) + lblDev;
		qVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
		for (size_t i = 0; i < qVec.size(); i++) if (IDN(qVec[i][0]) == IDN::CaO) siloName.push_back(IDN(qVec[i][2]));
		for (size_t i = 0; i < siloName.size(); i++)
		{
			double&& siloWgt = this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt))[0][0];
			siloWgt = siloWgt + this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt))[0][0];
			matMix.push_back(make_pair(secondBtime, make_pair(IDNTrans(siloName[i]), siloWgt)));

			qVec = this->Read(strT = myStr + IDNTrans(siloName[i]));/*更新钢液状态*/
			ptrBS->Add(qVec, true);
			ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::New) + lblDev + IDNTrans(IDN::Time) + valDev + to_string(secondBtime), false);
			ptrBS->Write(0, secondBtime, true);
			this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt) + valDev + "0", false);
			this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt) + valDev + "0", false);
		}
		idVec().swap(siloName);

		//确定铁矿石加料料仓及重量
		double aimFeO(30);
		myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev;
		double&& iniFeO(ptrBS->Read(strT = myStr + IDNTrans(IDN::FeO))[0][0]);
		double&& iniFe2O3(ptrBS->Read(strT = myStr + IDNTrans(IDN::Fe2O3))[0][0]);
		iniFeO = (iniFeO + 1.35 * iniFe2O3) / (100 + 0.35 * iniFe2O3) * 100;
		double&& slgWgt(ptrBS->Read(strT = myStr + IDNTrans(IDN::Wgt))[0][0]);
		if (iniFeO < aimFeO)
		{
			myStr = IDNTrans(IDN::Flux) + lblDev;
			qVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
			for (size_t i = 0; i < qVec.size(); i++) if (IDN(qVec[i][0]) == IDN::Fe2O3) siloName.push_back(IDN(qVec[i][2]));
			double requireFeO(slgWgt * (aimFeO - iniFeO) / (100 - aimFeO));
			for (size_t i = 0; i < siloName.size(); i++)
			{
				double&& siloFeO(this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::FeO))[0][0]);             /*解得料仓FeO成分*/
				double&& siloFe2O3(this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Fe2O3))[0][0]);
				siloFeO = (siloFeO + 1.35 * siloFe2O3) / (100 + 0.35 * siloFe2O3) * 100;

				double&& requireOre(requireFeO / siloFeO * 100);
				double&& siloWgt(this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
				siloWgt = siloWgt + this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt))[0][0];
				if (siloWgt >= requireOre)
				{
					matMix.push_back(make_pair(secondBtime + 0, make_pair(IDNTrans(siloName[i]), requireOre)));
					requireFeO = requireFeO - requireOre * siloFeO / 100;
					qVec = this->Read(strT = myStr + IDNTrans(siloName[i]));
					for (size_t j = 0; j < qVec.size(); j++)
					{
						if (IDN(qVec[j][3]) == IDN::Wgt)   qVec[j] = requireOre;
						else if (IDN(qVec[j][3]) == IDN::CWgt) qVec[j] = 0;
					}
					ptrBS->Add(qVec, true);
					ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::New) + lblDev + IDNTrans(IDN::Time) + valDev + to_string(secondBtime), false);
					ptrBS->Write(0, secondBtime, true);
					this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt) + valDev + to_string(siloWgt - requireOre), false);
					this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt) + valDev + "0", false);
					break;
				}
				else
				{
					matMix.push_back(make_pair(secondBtime + 0, make_pair(IDNTrans(siloName[i]), siloWgt)));
					requireFeO = requireFeO - siloWgt * siloFeO / 100;
					qVec = this->Read(strT = myStr + IDNTrans(siloName[i]));
					ptrBS->Add(qVec, true);
					ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::New) + lblDev + IDNTrans(IDN::Time) + valDev + to_string(secondBtime), false);
					ptrBS->Write(0, secondBtime, true);
					this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt) + valDev + "0", false);
					this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt) + valDev + "0", false);
				}
			}
		}
	}
	//计算脱碳临界温度后的余料加入：护炉 - dolo
	{
		//确定加料时间
		myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev;
		double&& iniSetTemp(ptrBS->Read(strT = myStr + IDNTrans(IDN::Temp))[0][0]);
		ptrBS->Write(strT = myStr + IDNTrans(IDN::Temp) + valDev + to_string(keyTemp + 30), true);
		ptrBS->Write(strT = myStr + IDNTrans(IDN::Temp) + valDev + to_string(iniSetTemp), false);
		double&& thirdBtime(ptrBS->Read(strT = myStr + IDNTrans(IDN::Time))[0][0]);

		idVec siloName;
		//确定轻烧加料料仓及重量
		myStr = IDNTrans(IDN::Flux) + lblDev;
		qVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
		for (size_t i = 0; i < qVec.size(); i++) if (IDN(qVec[i][0]) == IDN::MgO) siloName.push_back(IDN(qVec[i][2]));
		for (size_t i = 0; i < siloName.size(); i++)
		{
			double&& siloWgt = this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt))[0][0];
			siloWgt = siloWgt + this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt))[0][0];
			matMix.push_back(make_pair(thirdBtime, make_pair(IDNTrans(siloName[i]), siloWgt)));

			qVec = this->Read(strT = myStr + IDNTrans(siloName[i]));/*更新钢液状态*/
			ptrBS->Add(qVec, true);
			ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::New) + lblDev + IDNTrans(IDN::Time) + valDev + to_string(thirdBtime), false);
			ptrBS->Write(0, thirdBtime, true);
			this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt) + valDev + "0", false);
			this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt) + valDev + "0", false);
		}
		idVec().swap(siloName);
	}
	//计算剩余矿石类材料加入：中期调渣
	{
		idVec siloName;
		myStr = IDNTrans(IDN::Flux) + lblDev;
		qVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
		for (size_t i = 0; i < qVec.size(); i++) if (IDN(qVec[i][0]) == IDN::Fe2O3) siloName.push_back(IDN(qVec[i][2]));
		//读取需加入的剩余矿石总量
		double restOre(0);
		for (size_t i = 0; i < siloName.size(); i++)
		{
			restOre = restOre + this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt))[0][0];
			restOre = restOre + this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt))[0][0];
		}
		//确定矿石加入次数及每次加入量
		size_t timesFeed(size_t((midC.second - midC.first) / 0.5 + 1));
		double&& stlWgt(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
		while (restOre / timesFeed < stlWgt * 0.5 / 100 && timesFeed > 1) timesFeed--;

		for (size_t i = 0; i < siloName.size(); i++)
		{
			double&& siloWgt(this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
			siloWgt = siloWgt + this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt))[0][0];
			for (size_t j = 0; j < timesFeed; j++)
			{
				double&& iniSetC(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::C))[0][0]);
				ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::C) + valDev + to_string(midC.second - j * 0.5), true);
				ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::C) + valDev + to_string(iniSetC), false);
				double&& fourthBtime(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::Time))[0][0]);
				if (siloWgt > restOre / timesFeed)
				{
					matMix.push_back(make_pair(fourthBtime, make_pair(IDNTrans(siloName[i]), restOre / timesFeed)));
					siloWgt = siloWgt - restOre / timesFeed;
					qVec = this->Read(strT = myStr + IDNTrans(siloName[i]));
					for (size_t k = 0; k < qVec.size(); k++) if (IDN(qVec[k][3]) == IDN::Wgt) qVec[k] = restOre / timesFeed;
					ptrBS->Add(qVec, true);
					ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::New) + lblDev + IDNTrans(IDN::Time) + valDev + to_string(fourthBtime), false);
					ptrBS->Write(0, fourthBtime, true);
					this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt) + valDev + to_string(siloWgt), false);
					restOre = restOre - restOre / timesFeed * j;
				}
				else if (siloWgt > dbZero)
				{
					matMix.push_back(make_pair(fourthBtime + 30, make_pair(IDNTrans(siloName[i]), siloWgt)));
					qVec = this->Read(strT = myStr + IDNTrans(siloName[i]));
					for (size_t k = 0; k < qVec.size(); k++) if (IDN(qVec[k][3]) == IDN::Wgt) qVec[k] = siloWgt;
					ptrBS->Add(qVec, true);
					ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::New) + lblDev + IDNTrans(IDN::Time) + valDev + to_string(fourthBtime), false);
					ptrBS->Write(0, fourthBtime, true);
					this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt) + valDev + "0", false);
					restOre = restOre - siloWgt;
					break;
				}
			}
		}
	}
	//萤石类材料：中期化渣
	{
		//确定加料时间
		myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev;
		double&& iniSetC(ptrBS->Read(strT = myStr + IDNTrans(IDN::C))[0][0]);
		ptrBS->Write(strT = myStr + IDNTrans(IDN::C) + valDev + to_string(midC.first), true);
		ptrBS->Write(strT = myStr + IDNTrans(IDN::C) + valDev + to_string(iniSetC), false);
		double&& fifthBtime(ptrBS->Read(strT = myStr + IDNTrans(IDN::Time))[0][0]);

		idVec siloName;
		//确定萤石加料料仓及重量
		myStr = IDNTrans(IDN::Flux) + lblDev;
		qVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
		for (size_t i = 0; i < qVec.size(); i++) if (IDN(qVec[i][0]) == IDN::CaF2) siloName.push_back(IDN(qVec[i][2]));
		for (size_t i = 0; i < siloName.size(); i++)
		{
			double&& siloWgt = this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt))[0][0];
			siloWgt = siloWgt + this->Read(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt))[0][0];
			matMix.push_back(make_pair(fifthBtime, make_pair(IDNTrans(siloName[i]), siloWgt)));

			qVec = this->Read(strT = myStr + IDNTrans(siloName[i]));/*更新钢液状态*/
			ptrBS->Add(qVec, true);
			ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::New) + lblDev + IDNTrans(IDN::Time) + valDev + to_string(fifthBtime), false);
			ptrBS->Write(0, fifthBtime, true);
			this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::Wgt) + valDev + "0", false);
			this->Write(strT = myStr + IDNTrans(siloName[i]) + lblDev + IDNTrans(IDN::CWgt) + valDev + "0", false);
		}
		idVec().swap(siloName);
	}
	//合金材料加入：
	{
		DCVec().swap(qVec);
		qVec = this->Read(strT = IDNTrans(IDN::Alloy));
		if (qVec.size() > 0)
		{
			strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Temp);
			double&& iniSetTemp(ptrIO->Read(strT)[0][0]);
			double&& hereSetTemp(iniSetTemp - 2 * dbZero);
			myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev;
			for (size_t i = 0; i < qVec.size(); i++)
			{
				//得到加料时间
				ptrBS->Write(strT = myStr + IDNTrans(IDN::Temp) + valDev + to_string(hereSetTemp), true);
				ptrBS->Write(strT = myStr + IDNTrans(IDN::Temp) + valDev + to_string(iniSetTemp), false);
				double&& alloyBtime(ptrBS->Read(strT = myStr + IDNTrans(IDN::Time))[0][0]);
				//获取加料种类
				IDN siloName;
				siloName = IDN(qVec[i][2]);
				//获取加料重量
				double&& siloWgt(this->Read(strT = IDNTrans(IDN::Alloy) + lblDev + IDNTrans(siloName) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
				siloWgt = siloWgt + this->Read(strT = IDNTrans(IDN::Alloy) + lblDev + IDNTrans(siloName) + lblDev + IDNTrans(IDN::CWgt))[0][0];
				//写入结果
				matMix.push_back(make_pair(alloyBtime, make_pair(IDNTrans(siloName), siloWgt)));
				//调整循环变量
				DCVec myVec;
				myVec = this->Read(strT = IDNTrans(IDN::Alloy) + lblDev + IDNTrans(siloName));
				i = i + myVec.size() - 1;
				//熔池加料更新
				ptrBS->Add(myVec, true);
				ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::New) + lblDev + IDNTrans(IDN::Time) + valDev + to_string(alloyBtime), false);
				ptrBS->Write(0, alloyBtime, true);
				//本类料仓信息更新
				this->Write(strT = IDNTrans(IDN::Alloy) + lblDev + IDNTrans(siloName) + lblDev + IDNTrans(IDN::Wgt) + valDev + "0", false);
				this->Write(strT = IDNTrans(IDN::Alloy) + lblDev + IDNTrans(siloName) + lblDev + IDNTrans(IDN::CWgt) + valDev + "0", false);
			}
		}
	}
	//写入结果
	qVec.resize(matMix.size() * 2);
	for (size_t i = 0; i < matMix.size(); i++)
	{
		myStr = IDNTrans(IDN::Result) + lblDev + matMix[i].second.first + lblDev;
		strT = myStr + IDNTrans(IDN::Time) + valDev + to_string(matMix[i].first);
		qVec[i * 2] = strT;
		strT = myStr + IDNTrans(IDN::Wgt) + valDev + to_string(matMix[i].second.second);
		qVec[i * 2 + 1] = strT;
	}
	this->Add(qVec, true);
	/*this->Add(qVec, false);
	DCVec myVec, resultVec;
	for (size_t i = 0; i < qVec.size() / 2; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			if (j == 0) myStr = IDNTrans(IDN::Flux) + lblDev;
			else          myStr = IDNTrans(IDN::Alloy) + lblDev;
			myVec = this->Read(strT = myStr + IDNTrans(IDN(qVec[i * 2][2])));
			if (myVec.size() > 0 && qVec[i * 2 + 1][0] > dbZero)
			{
				for (size_t m = 0; m < myVec.size(); m++)  if (IDN(myVec[m][3]) == IDN::Wgt) myVec[m] = qVec[i * 2 + 1][0];
				for (size_t m = 0; m < myVec.size(); m++) resultVec.push_back(myVec[m]);
				strT = IDNTrans(IDN::Result) + lblDev;
				for (size_t m = 0; m < 3; m++) strT = strT + lblDev;
				myVec[0] = strT;
				resultVec.push_back(myVec[0]);
				DCVec().swap(myVec);
			}
		}
	}
	this->Del(strT = IDNTrans(IDN::Flux));
	this->Del(strT = IDNTrans(IDN::Alloy));
	this->Add(resultVec, true);*/
	return true;
}
bool Predict::oxyBlow()
{
	string strT(""), myStr("");
	DCVec qVec;
	vector<pair<double, pair<double, double>>>  BlwPattern;/*时间 - 氧气 - 惰性气体*/
	/*碳钢根据温度及（FeO）确定；不锈钢根据钢液碳含量确定；Inert Gas由最大氧气量及最大IG量确定*/
	double&& AimCr(ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Low) + lblDev + IDNTrans(IDN::Cr))[0][0]);
	if (AimCr > 6)/*不锈钢*/
	{
		//数据准备
		double&& MaxOxyFlw(ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev + IDNTrans(IDN::OxyFlow))[0][0]);

		dbVec keyC;
		qVec = ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev + IDNTrans(IDN::keyC));
		for (size_t i = 0; i < qVec.size(); i++) keyC.push_back(qVec[i][0]);
		keyC.push_back(ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::C))[0][0]);

		//钢液更新
		myStr = IDNTrans(IDN::Result) + lblDev;
		DCVec timeVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::Time));
		DCVec wgtVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::Wgt));
		for (size_t i = 0; i < timeVec.size(); i++)
		{
			if (wgtVec[i][0] > dbZero)
			{
				for (size_t j = 0; j < 2; j++)
				{
					if (j == 0) myStr = IDNTrans(IDN::Flux) + lblDev;
					else          myStr = IDNTrans(IDN::Alloy) + lblDev;
					qVec = this->Read(strT = myStr + IDNTrans(IDN(timeVec[i][2])));
					if (qVec.size() > 0)
					{
						for (size_t m = 0; m < qVec.size(); m++) if (IDN(qVec[m][3]) == IDN::Wgt) qVec[m] = wgtVec[i][0];
						ptrBS->Add(qVec, true);
						ptrBS->Write(1, timeVec[i][0], true);
					}
				}
			}
		}

		double blwTime(0);
		for (size_t i = 0; i < keyC.size(); i++)
		{
			if (i != 0) blwTime = ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::Time))[0][0];
			strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::C) + valDev + to_string(keyC[i]);
			ptrBS->Write(strT, true);

			double Ratio(0);
			if (i == 0) Ratio = 6;
			else Ratio = 1 / i;
			BlwPattern.push_back(make_pair(blwTime, make_pair(MaxOxyFlw * Ratio / (Ratio + 1), MaxOxyFlw / (Ratio + 1))));
		}
		//写入结果
		myDC X;
		for (size_t i = 0; i < BlwPattern.size(); i++)
		{
			myStr = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::Blowing) + lblDev;
			strT = myStr + IDNTrans(IDN::Time) + valDev + to_string(BlwPattern[i].first);
			X = strT;
			this->Add(X);

			strT = myStr + IDNTrans(IDN::OxyFlow) + valDev + to_string(BlwPattern[i].second.first);
			X = strT;
			this->Add(X);

			IDN IGas;
			IGas = IDN(ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev + IDNTrans(IDN::GasType))[0][0]);
			strT = myStr + IDNTrans(IGas) + valDev + to_string(BlwPattern[i].second.second);
			X = strT;
			this->Add(X);
		}
		this->BuildIndex();
	}
	else              /*碳钢*/
	{
		double&& IGFlw(ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev + IDNTrans(IDN::BottomFlow))[0][0]);
		//读取枪位设定值
		double BlwHH(0), BlwH(0), BlwM(0), BlwL(0), BlwLL(0);
		{
			qVec = (ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::LancePos)));
			for (size_t i = 0; i < qVec.size(); i++)
			{
				if (IDN(qVec[i][3]) == IDN::HighH)  BlwHH = qVec[i][0];
				else if (IDN(qVec[i][3]) == IDN::High)    BlwH = qVec[i][0];
				else if (IDN(qVec[i][3]) == IDN::Mid)      BlwM = qVec[i][0];
				else if (IDN(qVec[i][3]) == IDN::Low)     BlwL = qVec[i][0];
				else if (IDN(qVec[i][3]) == IDN::LowL)   BlwLL = qVec[i][0];
			}
			DCVec().swap(qVec);
		}
		//读取加料时间戳
		myStr = IDNTrans(IDN::Result) + lblDev;
		DCVec resultVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::Time));
		qVec = resultVec;
		DCVec wgtVec = this->Read(strT = myStr + lblDev + IDNTrans(IDN::Wgt));
		dbVec timeStand;
		{
			timeStand.reserve(qVec.size());
			for (size_t i = 0; i < qVec.size() - 1; i++)
			{
				for (size_t j = i + 1; j < qVec.size(); j++)
				{
					if (fabs(qVec[i][0] - qVec[j][0]) < dbZero) qVec[j] = 9999;
				}
			}
			for (size_t i = 0; i < qVec.size(); i++) if (fabs(qVec[i][0] - 9999) > dbZero)  timeStand.push_back(qVec[i][0]);
			DCVec().swap(qVec);
		}
		//确定“点火”吹炼方案
		{
			//更新钢液信息
			for (size_t i = 0; i < resultVec.size(); i++)
			{
				if (fabs(timeStand[0] - resultVec[i][0]) < dbZero && wgtVec[i][0] > dbZero)
				{
					for (size_t j = 0; j < 2; j++)
					{
						if (j == 0) myStr = IDNTrans(IDN::Flux) + lblDev;
						else          myStr = IDNTrans(IDN::Alloy) + lblDev;
						qVec = this->Read(strT = myStr + IDNTrans(IDN(resultVec[i][2])));
						if (qVec.size() > 0)
						{
							for (size_t m = 0; m < qVec.size(); m++) if (IDN(qVec[m][3]) == IDN::Wgt) qVec[m] = wgtVec[i][0];
							ptrBS->Add(qVec, true);
							ptrBS->Write(1, timeStand[0], true);
						}
					}
				}
			}
			//确定点火期方案：根据温度（废钢比重）
			double&& LastTemp(ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Ini) + lblDev + IDNTrans(IDN::Temp))[0][0]);
			double&& NowTemp(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Temp))[0][0]);
			double firstBlwTime(0);
			if (NowTemp - LastTemp < -200) BlwPattern.push_back(make_pair(firstBlwTime, make_pair(BlwLL, IGFlw)));
			else                                                  BlwPattern.push_back(make_pair(firstBlwTime, make_pair(BlwL, IGFlw)));
		}
		//确定化渣温度时的吹炼方案
		{
			//更新钢液信息
			for (size_t i = 0; i < resultVec.size(); i++)
			{
				if (fabs(timeStand[1] - resultVec[i][0]) < dbZero && wgtVec[i][0] > dbZero)
				{
					for (size_t j = 0; j < 2; j++)
					{
						if (j == 0) myStr = IDNTrans(IDN::Flux) + lblDev;
						else          myStr = IDNTrans(IDN::Alloy) + lblDev;
						qVec = this->Read(strT = myStr + IDNTrans(IDN(resultVec[i][2])));
						if (qVec.size() > 0)
						{
							for (size_t m = 0; m < qVec.size(); m++) if (IDN(qVec[m][3]) == IDN::Wgt) qVec[m] = wgtVec[i][0];
							ptrBS->Add(qVec, true);
							ptrBS->Write(1, timeStand[1], true);
						}
					}
				}
			}
			//确定化渣期方案：根据碱度（起始硅）
			double&& Basicity(ptrPF->Read(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::Basicity))[0][0]);
			double&& UBa(ptrPF->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::UBa))[0][0]);
			double&& LBa(ptrPF->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::LBa))[0][0]);
			if (Basicity > (UBa + LBa) / 2) BlwPattern.push_back(make_pair(timeStand[1], make_pair(BlwHH, IGFlw)));
			else                                    BlwPattern.push_back(make_pair(timeStand[1], make_pair(BlwH, IGFlw)));
		}
		//确定临界温度时的吹炼方案
		double aimFeO(30);
		{
			//更新钢液信息
			for (size_t i = 0; i < resultVec.size(); i++)
			{
				if (fabs(timeStand[2] - resultVec[i][0]) < dbZero && wgtVec[i][0] > dbZero)
				{
					for (size_t j = 0; j < 2; j++)
					{
						if (j == 0) myStr = IDNTrans(IDN::Flux) + lblDev;
						else          myStr = IDNTrans(IDN::Alloy) + lblDev;
						qVec = this->Read(strT = myStr + IDNTrans(IDN(resultVec[i][2])));
						if (qVec.size() > 0)
						{
							for (size_t m = 0; m < qVec.size(); m++) if (IDN(qVec[m][3]) == IDN::Wgt) qVec[m] = wgtVec[i][0];
							ptrBS->Add(qVec, true);
							ptrBS->Write(1, timeStand[2], true);
						}
					}
				}
			}
			//确定脱碳初期方案
			myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev;
			double&& slgFeO(ptrBS->Read(strT = myStr + IDNTrans(IDN::FeO))[0][0]);
			double&& slgFe2O3(ptrBS->Read(strT = myStr + IDNTrans(IDN::Fe2O3))[0][0]);
			slgFeO = slgFeO / (100 + 0.35 * slgFe2O3) * 100;
			slgFe2O3 = 1.35 / (100 / slgFe2O3 + 0.35) * 100;
			slgFeO = slgFeO + slgFe2O3;
			if (slgFeO >= aimFeO)  BlwPattern.push_back(make_pair(timeStand[2], make_pair(BlwM, IGFlw)));
			else                                BlwPattern.push_back(make_pair(timeStand[2], make_pair(BlwH, IGFlw)));
		}
		//确定脱碳中末期吹炼方案
		{
			if (timeStand.size() == 2)
			{
				double&& O2Flw(ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev + IDNTrans(IDN::OxyFlow))[0][0]);
				double&& O2Amt(this->Read(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::OxyAmt))[0][0]);
				double&& TransiTime((O2Amt / (O2Flw / 3600) - timeStand[2]) / 2);

				ptrBS->Write(1, TransiTime, true); /*更新钢液状态*/

				myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev;
				double&& slgFeO(ptrBS->Read(strT = myStr + IDNTrans(IDN::FeO))[0][0]);
				double&& slgFe2O3(ptrBS->Read(strT = myStr + IDNTrans(IDN::Fe2O3))[0][0]);
				slgFeO = slgFeO / (100 + 0.35 * slgFe2O3) * 100;
				slgFe2O3 = 1.35 / (100 / slgFe2O3 + 0.35) * 100;
				slgFeO = slgFeO + slgFe2O3;
				if (slgFeO >= aimFeO)  BlwPattern.push_back(make_pair(TransiTime, make_pair(BlwM, IGFlw)));
				else                                BlwPattern.push_back(make_pair(TransiTime, make_pair(BlwH, IGFlw)));
			}
			else
			{
				ptrBS->Write(1, timeStand[timeStand.size() - 1], true); /*更新钢液状态*/

				myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Slag) + lblDev;
				double&& slgFeO(ptrBS->Read(strT = myStr + IDNTrans(IDN::FeO))[0][0]);
				double&& slgFe2O3(ptrBS->Read(strT = myStr + IDNTrans(IDN::Fe2O3))[0][0]);
				slgFeO = slgFeO / (100 + 0.35 * slgFe2O3) * 100;
				slgFe2O3 = 1.35 / (100 / slgFe2O3 + 0.35) * 100;
				slgFeO = slgFeO + slgFe2O3;
				if (slgFeO >= aimFeO)  BlwPattern.push_back(make_pair(timeStand[timeStand.size() - 1], make_pair(BlwM, IGFlw)));
				else                                BlwPattern.push_back(make_pair(timeStand[timeStand.size() - 1], make_pair(BlwH, IGFlw)));
			}
		}
		//写入结果
		myDC X;
		for (size_t i = 0; i < BlwPattern.size(); i++)
		{
			myStr = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::Blowing) + lblDev;
			strT = myStr + IDNTrans(IDN::Time) + valDev + to_string(BlwPattern[i].first);
			X = strT;
			this->Add(X);

			strT = myStr + IDNTrans(IDN::LancePos) + valDev + to_string(BlwPattern[i].second.first);
			X = strT;
			this->Add(X);

			IDN IGas;
			IGas = IDN(ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev + IDNTrans(IDN::GasType))[0][0]);
			strT = myStr + IDNTrans(IGas) + valDev + to_string(BlwPattern[i].second.second);
			X = strT;
			this->Add(X);
		}
		this->BuildIndex();
	}
	return true;
}
bool Predict::Cal()
{
	string strT(""), myStr("");
	DCVec qVec;
	uuPVec thisIndex;

	metalMass();                                                   /*金属平衡*/
	{
		//更新iniC及oxyAlSi
		double&& iniC_Scrp(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::C))[0][0]);
		ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Ini) + lblDev + IDNTrans(IDN::C) + valDev + to_string(iniC_Scrp), false);
		ptrBS->Write(12, iniC_Scrp, false);
		double&& iniP_Scrp(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::P))[0][0]);
		ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::iniP) + valDev + to_string(iniP_Scrp), false);
		double OxySi(0);
		dbVec iniAlSi(4);
		myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev;
		iniAlSi[0] = ptrBS->Read(strT = myStr + IDNTrans(IDN::Al))[0][0];
		iniAlSi[1] = ptrBS->Read(strT = myStr + IDNTrans(IDN::Si))[0][0];
		iniAlSi[2] = ptrBS->Read(strT = myStr + IDNTrans(IDN::V))[0][0];
		iniAlSi[3] = ptrBS->Read(strT = myStr + IDNTrans(IDN::Mn))[0][0];
		double&& stlWgt(ptrBS->Read(strT = myStr + IDNTrans(IDN::Wgt))[0][0]);
		dbVec elemLLim{ 0.003, 0.04,0.12,0.12 };
		dbVec elemOxy = { 0.622,0.8,0.329,0.204 };
		for (size_t i = 0; i < elemOxy.size(); i++) 	OxySi = OxySi + (iniAlSi[i] - elemLLim[i]) * stlWgt / 100 * elemOxy[i];
		ptrBS->Write(3, OxySi, false);
	}
	BathState BSforFeed(*ptrIO), BSforBlow(*ptrIO);
	BSforFeed = *ptrBS;
	BSforBlow = *ptrBS;

	thisIndex = this->GetIndex();                        /*辅料平衡*/
	{
		//将合金加入熔池                  
		for (size_t i = 0; i < thisIndex.size(); i++)
		{
			if (IDN(this->Read(thisIndex[i].first)[1]) == IDN::Alloy)
			{
				for (size_t j = thisIndex[i].first; j <= thisIndex[i].second; j++) qVec.push_back(this->Read(j));
				ptrBS->Add(qVec, true);
				ptrBS->Write(0, 0, true);
				DCVec().swap(qVec);
			}
		}
	}
	fluxMass();

	thisIndex = this->GetIndex();                        /*能量平衡准备：加入辅料+钢液元素氧化*/
	{
		//加入辅料
		for (size_t i = 0; i < thisIndex.size(); i++)
		{
			IDN siloName = IDN(this->Read(thisIndex[i].first)[2]);
			IDN TYPE = IDN(this->Read(thisIndex[i].first)[1]);
			if (IDN(this->Read(thisIndex[i].first)[1]) == IDN::Flux)
			{
				for (size_t j = thisIndex[i].first; j <= thisIndex[i].second; j++) qVec.push_back(this->Read(j));
				ptrBS->Add(qVec, true);
				ptrBS->Write(0, 0, true);
				DCVec().swap(qVec);
			}
		}
	}
	{
		//元素氧化
		double&& AimC(ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::C))[0][0]);
		AimC = AimC + 2 * dbZero;
		ptrBS->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev + IDNTrans(IDN::C) + valDev + to_string(AimC), true);
	}

	oreCal();                                                        /*冷料计算*/

	oxyMass();                                                     /*氧平衡*/

	ptrBS = &BSforFeed;                                    /*加料规划*/
	matFeed();

	ptrBS = &BSforBlow;                                   /*供氧规划*/
	oxyBlow();

	return true;
}
//吹炼中修正
InBlow::InBlow(BathState& objBathState, DataIO& objDataIO, Predict& objPredict)
{
	ptrBS = &objBathState;
	ptrIO = &objDataIO;
	ptrPD = &objPredict;
	string myStr(""), strT("");
	DCVec qVec;

	double collectRatio(0.7);
	double OxyFlow(0);
	qVec = ptrIO->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev + IDNTrans(IDN::OxyFlow));
	for (size_t i = 0; i < qVec.size(); i++) OxyFlow = OxyFlow + qVec[i][0] * 1.25 * 0.8 * pow(0.8, i + 1);
	OxyFlow = OxyFlow / 3600;
	double&& OxyAmt(ptrPD->Read(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::OxyAmt))[0][0]);
	myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Set) + lblDev;
	this->Add(strT = myStr + IDNTrans(IDN::Time) + valDev + to_string(OxyAmt / OxyFlow * collectRatio));

	myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Real) + lblDev;
	this->Add(strT = myStr + IDNTrans(IDN::C) + valDev + "0");
	this->Add(strT = myStr + IDNTrans(IDN::Temp) + valDev + "0");
	this->Add(strT = myStr + IDNTrans(IDN::Time) + valDev + "0");
	this->BuildIndex();
}
bool InBlow::Cal()
{
	string myStr(""), strT("");
	DCVec qVec;
	double&& measTime(this->Read(3)[0]), && measC(this->Read(1)[0]), && measTemp(this->Read(2)[0]);

	//收集钢液状态
	double&& limTime(this->Read(0)[0]);
	qVec = this->Read(strT = IDNTrans(IDN::Result));
	if (ptrBS->Read(0)[0] > limTime && measTime < dbZero && (measC < dbZero || measTemp < dbZero) && qVec.size() == 0)
	{
		myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Blowing) + lblDev + IDNTrans(IDN::Time);
		this->Add(strT = myStr + valDev + to_string(ptrBS->Read(0)[0]));
		myStr = IDNTrans(IDN::Para) + lblDev;
		this->Add(qVec = ptrBS->Read(strT = myStr + IDNTrans(IDN::Stl)));
		this->Add(qVec = ptrBS->Read(strT = myStr + IDNTrans(IDN::Slag)));
		this->BuildIndex();
	}
	//根据C、T、t状态开始计算
	if (measTime > dbZero && (measC > dbZero || measTemp > dbZero))
	{
		//提取与测量时点最接近的熔池状态（在该时点之前）
		DCVec calStl, calSlag;
		size_t posStl(0);
		uuPVec InBlowIndex(this->GetIndex());
		for (size_t i = 0; i < InBlowIndex.size(); i++)
		{
			myDC qCell = this->Read(InBlowIndex[i].first);
			if (IDN(qCell[1]) == IDN::Para && IDN(qCell[2]) == IDN::Blowing && IDN(qCell[3]) == IDN::Time && qCell[0] <= measTime) posStl = i + 1;
		}
		calStl = this->Get(InBlowIndex[posStl].first, InBlowIndex[posStl].second);
		calSlag = this->Get(InBlowIndex[posStl + 1].first, InBlowIndex[posStl + 1].second);
		//提取该时点的C、T计算值
		double calC(0), calTemp(0), && calTime(this->Read(InBlowIndex[posStl - 1].first)[0]), calWgt(0);
		for (size_t i = 0; i < calStl.size(); i++)
		{
			if (IDN(calStl[i][3]) == IDN::C) calC = calStl[i][0];
			else if (IDN(calStl[i][3]) == IDN::Temp) calTemp = calStl[i][0];
			else if (IDN(calStl[i][3]) == IDN::Wgt)    calWgt = calStl[i][0];
		}
		//修正时间引起的状态差异
		double&& deltaTime(measTime - calTime);
		/*数据准备*/
		double&& AimC(ptrIO->Read(strT = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::C))[0][0]);
		dbVec keyC, kC, O2Flow;
		myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static);
		qVec = ptrIO->Read(myStr);
		for (size_t i = 0; i < qVec.size(); i++)
		{
			if (IDN(qVec[i][3]) == IDN::keyC)             keyC.push_back(qVec[i][0]);
			else if (IDN(qVec[i][3]) == IDN::kForC)           kC.push_back(qVec[i][0]);
			else if (IDN(qVec[i][3]) == IDN::OxyFlow)       O2Flow.push_back(qVec[i][0]);
		}
		keyC.push_back(AimC);
		if (O2Flow.size() != keyC.size())  for (size_t i = O2Flow.size(); i <= keyC.size(); i++) O2Flow.push_back(O2Flow[O2Flow.size() - 1]);
		double reviseC(0);
		for (size_t i = 0; i < keyC.size(); i++)
		{
			if (calC > keyC[i])
			{
				reviseC = calC * exp(kC[i] * deltaTime);
				break;
			}
		}
		/*修正因时间差异引起的C、T变化*/
		double&& therC(ptrIO->Read(strT = IDNTrans(IDN::Enrg) + lblDev + IDNTrans(IDN::Reac) + lblDev + IDNTrans(IDN::C))[0][0]);
		calTemp = calTemp + (reviseC - calC) * therC;
		calC = reviseC;
		//分情况处置
		if (measTemp > calTemp)
		{
			DCVec().swap(qVec);
			myStr = IDNTrans(IDN::Flux) + lblDev;
			qVec = ptrIO->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
			IDN siloName(IDN::IDFail);
			for (size_t i = 0; i < qVec.size(); i++) if (IDN(qVec[i][0]) == IDN::Fe2O3)
			{
				siloName = IDN(qVec[i][2]);
				break;
			}
			double oreTher(ptrIO->Read(strT = myStr + IDNTrans(siloName) + lblDev + IDNTrans(IDN::Thermal1))[0][0]);
			oreTher = oreTher + ptrIO->Read(strT = myStr + IDNTrans(siloName) + lblDev + IDNTrans(IDN::Thermal2))[0][0];
			double&& oreWgt((calTemp - measTemp) / oreTher / 100 * calWgt * (100 + calC) / (100 + measC));
			this->Add(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::Ore) + lblDev + IDNTrans(IDN::Wgt) + valDev + to_string(oreWgt), true);
		}
		if (measC > calC)
		{
			double&& OxyAmt(ptrPD->Read(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::OxyAmt))[0][0]);
			double&& calO2(calWgt * (measC - calC) / (100 - measC) * 0.9339 + OxyAmt);
			this->Add(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::OxyAmt) + valDev + to_string(calO2), true);
		}
		//修正起始碳含量
		double&& caliIniC(measC - calC + (measTemp - calTemp) / therC);
		while (fabs(caliIniC) > 0.5) caliIniC = caliIniC / 2;
		this->Add(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::Assess) + lblDev + IDNTrans(IDN::C) + valDev + to_string(caliIniC), true);
		//修正目标碳含量
		double&& caliTemp((measC - calC) * therC + measTemp - calTemp);
		if (caliTemp < dbZero)
		{
			double caliAimC(caliTemp / therC / calC / 2);
			caliAimC = ptrBS->Read(10)[0] * (1 + caliAimC);
			ptrBS->Write(10, caliAimC, false);
			ptrBS->Write(6, caliAimC, false);
			this->Add(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN::C) + valDev + to_string(caliAimC), true);
		}
		//修正到当前时间
		double&& realTime(ptrBS->Read(0)[0]);/*当前时间，旧*/
		deltaTime = realTime - measTime;
		for (size_t i = 0; i < keyC.size(); i++)
		{
			if (measC > keyC[i])
			{
				reviseC = measC * exp(kC[i] * deltaTime);
				break;
			}
		}
		measTemp = measTemp + (reviseC - measC) * therC;
		measC = reviseC;
		//将修正过的熔池状态返回
		myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev;
		ptrBS->Write(strT = myStr + IDNTrans(IDN::C) + valDev + to_string(measC), false);
		ptrBS->Write(strT = myStr + IDNTrans(IDN::Temp) + valDev + to_string(measTemp), false);
		ptrBS->Write(strT = myStr + IDNTrans(IDN::Wgt) + valDev + to_string(calWgt * (100 + calC) / (100 + measC)), false);
		this->Write(1, 0, false);
		this->Write(2, 0, false);
		this->Write(3, 0, false);

		for (size_t i = 0; i < calStl.size(); i++)   this->Del(calStl[i]);
		for (size_t i = 0; i < calSlag.size(); i++) this->Del(calSlag[i]);
		this->Del(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Blowing) + lblDev + IDNTrans(IDN::Time), true);
	}
	return true;
}
//合金化/还原（不锈钢）计算
EndBlow::EndBlow(BathState& objBathState, DataIO& objIO)
{
	string strT("");
	ptrBS = &objBathState;
	ptrIO = &objIO;

	this->Add(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Start) + valDev + "0", true);
}
bool EndBlow::Cal()
{
	string myStr(""), strT("");
	DCVec qVec;

	double&& curC(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::C))[0][0]);
	double&& aimC(ptrBS->Read(10)[0]);
	if (curC - aimC < dbZero)
	{
		//数据准备
		double&& curT(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Temp))[0][0]);
		double eqlC(min(curC, aimC));
		double&& eqlCr(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Cr))[0][0]);

		double sumECr(0), sumEC(0);
		using sdPVec = vector<pair<string, double>>;
		sdPVec eCr = { {"Al",0},{"C",-0.12},{"Si",-0.0043},{"Mn",0},{"P",-0.053},{"S",-0.02},{"Cr",-0.0003},{"Ni",0.0002},{"Mo",0.0018},{"N",-0.19},{"Cu",0.016},{"O",-0.14} };
		sdPVec eC = { {"Al",0.043},{"C",0.14},{"Si",0.08},{"Mn",-0.012},{"S",0.051},{"Cr",-0.024},{"Ni",0.012},{"Mo",-0.0083},{"N",0.11},{"Cu",0.016},{"O",-0.34} };
		qVec = ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl));
		for (size_t i = 0; i < qVec.size(); i++)
		{
			for (size_t j = 0; j < eCr.size(); j++) 	if (IDN(qVec[i][3]) == IDNTrans(eCr[j].first))  sumECr = sumECr + qVec[i][0] * eCr[j].second;
			for (size_t j = 0; j < eC.size(); j++) if (IDN(qVec[i][3]) == IDNTrans(eC[j].first)) sumEC = sumEC = qVec[i][0] * eC[j].second;
		}
		sumEC = pow(10, sumEC);
		sumECr = pow(10, sumECr);
		//计算钢液实时氧含量
		double&& O_C(1 / pow(10, 1168 / (curT + 273.15) + 2.07) / eqlC);
		double&& O_Cr(pow(1 / pow(10, 46390 / (curT + 2731.5) - 17.24) / (sumECr * sumECr) / eqlCr, 1 / 3));
		double eqlO(min(O_C, O_Cr));
		//计算合金量
		idVec elemName;
		vector<pair<double, double>> elemAim;
		dbVec elemAtom;
		myStr = IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Aim) + lblDev;
		qVec = ptrIO->Read(strT = myStr + IDNTrans(IDN::Low));
		for (size_t i = 0; i < qVec.size(); i++)
		{
			if (IDN(qVec[i][4]) == IDN::Al || IDN(qVec[i][4]) == IDN::Si || IDN(qVec[i][4]) == IDN::Mn && qVec[i][0] > dbZero)
			{
				elemName.push_back(IDN(qVec[i][4]));
				elemAim.push_back({ ptrIO->Read(strT = myStr + IDNTrans(IDN::Aim) + lblDev + IDNTrans(IDN(qVec[i][4])))[0][0],qVec[i][0] });
				if (IDN(qVec[i][4]) == IDN::Al) elemAtom.push_back(27 * 0.6667);
				else if (IDN(qVec[i][4]) == IDN::Si) elemAtom.push_back(28 * 0.5);
				else if (IDN(qVec[i][4]) == IDN::Mn) elemAtom.push_back(55);
			}
		}
		myStr = IDNTrans(IDN::Alloy) + lblDev;
		qVec = ptrIO->Read(strT = myStr + lblDev + IDNTrans(IDN::MElem1));
		double&& stlWgt(ptrBS->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::Wgt))[0][0]);
		for (size_t i = 0; i < elemName.size(); i++)
		{
			if (eqlO * elemAtom[i] <= elemAim[i].first - elemAim[i].second)  eqlO = 0;
			else  eqlO = eqlO - (elemAim[i].first - elemAim[i].second) / elemAtom[i];
			elemAtom[i] = elemAim[i].first - elemAim[i].second;
			for (size_t j = 0; j < qVec.size(); j++)
			{
				if (elemName[i] == IDN(qVec[j][0]))
				{
					double&& alloyComp(ptrIO->Read(strT = myStr + IDNTrans(qVec[j][2]) + lblDev + IDNTrans(elemName[i]))[0][0]);
					elemAtom[i] = elemAtom[i] * stlWgt / alloyComp;
					this->Add(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(qVec[j][2]) + lblDev + IDNTrans(IDN::Wgt) + valDev + to_string(elemAtom[i]));
					break;
				}
			}
		}
		myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Static) + lblDev;
		IDN gasType(IDN::IDFail);
		gasType = IDN(ptrIO->Read(strT = myStr + IDNTrans(IDN::GasType))[0][0]);
		this->Add(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::GasType) + valDev + to_string(double(gasType)));
		double&& bottomFlow(ptrIO->Read(strT = myStr + IDNTrans(IDN::BottomFlow))[0][0]);
		this->Add(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::BottomFlow) + valDev + to_string(bottomFlow));
		double&& bottomTime(ptrIO->Read(strT = myStr + IDNTrans(IDN::BottomTime))[0][0]);
		this->Add(strT = IDNTrans(IDN::Result) + lblDev + IDNTrans(IDN::BottomTime) + valDev + to_string(bottomTime), true);
		this->Write(0, 1, false);
	}

	return true;
}
//功能演示
int main()
{
	system("color 78");
	string strT("");
	DataOpe* ptrOP;
	DataIO objIO, * ptrIO;
	ptrOP = &objIO;
	ptrIO = &objIO;
	//读取PREDICT结果
	double OxyAmt(0);
	DCVec matFeed, LanceMix;
	Predict objPD(objIO);
	ptrOP = &objPD;
	ptrOP->Write(0, 0, true);
	DCVec qVec;
	qVec = ptrOP->Read(strT = IDNTrans(IDN::Result));
	for (size_t i = 0; i < qVec.size(); i++)
		{
			if (IDN(qVec[i][2]) == IDN::OxyAmt) OxyAmt = qVec[i][0];
			else if (IDN(qVec[i][3]) == IDN::Wgt)
			{
				matFeed.push_back(qVec[i - 1]);
				matFeed.push_back(qVec[i]);
			}
			else
			{
				LanceMix.push_back(qVec[i - 1]);
				LanceMix.push_back(qVec[i]);
			}
		}
	//钢水状态计算（含加料）
	BathState objBS(objIO);
	ptrOP = &objBS;
	//加入废钢
	{
		string myStr("");
		uuPVec IOIndex(ptrIO->GetIndex());
		for (size_t i = 0; i < IOIndex.size(); i++)
		{
			if (IDN(ptrIO->Read(IOIndex[i].first)[1]) == IDN::Scrp)
			{
				for (size_t j = IOIndex[i].first; j <= IOIndex[i].second; j++)	ptrOP->Add(ptrIO->Read(j));
				ptrOP->BuildIndex();
				ptrOP->Write(0, 0, true);
			}
		}
		//更新iniC及oxyAlSi
		{
			double&& iniC_Scrp(ptrOP->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::C))[0][0]);
			ptrOP->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Ini) + lblDev + IDNTrans(IDN::C) + valDev + to_string(iniC_Scrp), false);
			ptrOP->Write(12, iniC_Scrp, false);
			double&& iniP_Scrp(ptrOP->Read(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev + IDNTrans(IDN::P))[0][0]);
			ptrOP->Write(strT = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::iniP) + valDev + to_string(iniP_Scrp), false);
			double OxySi(0);
			dbVec iniAlSi(4);
			myStr = IDNTrans(IDN::Para) + lblDev + IDNTrans(IDN::Stl) + lblDev;
			iniAlSi[0] = ptrOP->Read(strT = myStr + IDNTrans(IDN::Al))[0][0];
			iniAlSi[1] = ptrOP->Read(strT = myStr + IDNTrans(IDN::Si))[0][0];
			iniAlSi[2] = ptrOP->Read(strT = myStr + IDNTrans(IDN::V))[0][0];
			iniAlSi[3] = ptrOP->Read(strT = myStr + IDNTrans(IDN::Mn))[0][0];
			double&& stlWgt(ptrOP->Read(strT = myStr + IDNTrans(IDN::Wgt))[0][0]);
			dbVec elemLLim{ 0.003, 0.04,0.12,0.12 };
			dbVec elemOxy = { 0.622,0.8,0.329,0.204 };
			for (size_t i = 0; i < elemOxy.size(); i++) 	OxySi = OxySi + (iniAlSi[i] - elemLLim[i]) * stlWgt / 100 * elemOxy[i];
			ptrOP->Write(3, OxySi, false);
		}
	}
	//循环计算+动态+合金化
	InBlow objInBlow(objBS, objIO, objPD), * ptrIB;
	ptrIB = &objInBlow;
	EndBlow objEndBlow(objBS, objIO), * ptrEB;
	ptrEB = &objEndBlow;
	ptrIO->Write(strT = "Stl,Aim,Low,Al:0.02", false);
	ptrIO->Write(strT = "Stl,Aim,Aim,Al:0.04", false);
	time_t Begin(time(0));
	unsigned k(0);
	unsigned T(0);
	string myStr("Para,New,Time:"), testStr("");
	while (T <= 1100)
	{
		T = T + 5;
		strT = myStr + to_string(T);
		for (size_t i = 0; i < matFeed.size() / 2; i++)
			{
				if (T > unsigned(matFeed[i * 2][0]))
				{
					IDN siloName = IDN(matFeed[i * 2][2]);
					string qStr("");
					DCVec().swap(qVec);
					for (size_t j = 0; j < 2; j++)
					{
						if (j == 1) qStr = IDNTrans(IDN::Flux);
						else          qStr = IDNTrans(IDN::Alloy);
						qStr = qStr + lblDev + IDNTrans(siloName);
						qVec = ptrIO->Read(qStr);
						if (qVec.size() > 0)
						{
							for (size_t m = 0; m < qVec.size(); m++) if (IDN(qVec[m][3]) == IDN::Wgt)
							{
								qVec[m] = matFeed[i * 2 + 1][0];
								matFeed[i * 2] = 999999;
								matFeed[i * 2 + 1] = 0;
							}
							ptrOP->Add(qVec, true);
							ptrOP->Write(strT, true);
						}
					}
				}
			}
			
		ptrOP->Write(strT, true);
		double reviseTime(920);
		if (T != reviseTime)	ptrIB->Write(1, 0, true);
		else if (T == reviseTime)
		{
			ptrIB->Write(1, 0.35, false);
			ptrIB->Write(2, 1590, false);
			ptrIB->Write(3, T, true);
		}
		//输出结果
		DCVec X;
		X = ptrOP->Read(strT = "Para,Stl,");
		if (k == 0)
		{
			for (unsigned i = 0; i < X.size(); i++) testStr = testStr + IDNTrans(IDN(X[i][3])) + lblDev;
			testStr = testStr + '\r';
			k++;
		}
		for (unsigned i = 0; i < X.size(); i++)	testStr = testStr + to_string(X[i][0]) + ",";
		testStr = testStr + '\r';

		if (ptrEB->Read(0)[0] < dbZero) ptrEB->Write(0, 0, true);
	}
	cout << "Cal Time is:  " << time(0) - Begin << endl;
	fstream fileObj("./应用文件/Test.txt", ios::ate | ios::in | ios::out);
	fileObj.seekp(0, fileObj.beg);
	fileObj << testStr << endl;
	fileObj.close();

	uuPVec EBIndex(ptrEB->GetIndex());
	for (size_t i = 0; i < EBIndex.size(); i++)
	{
		for (size_t j = EBIndex[i].first; j <= EBIndex[i].second; j++)
		{
			myDC X = ptrEB->Read(j);
			cout << j << "-";
			for (size_t m = 1; m < X.size(); m++) if (IDN(X[m]) != IDN::Empty) cout << IDNTrans(IDN(X[m])) << ",";
			cout << X[0] << endl;
		}
	}
	system("pause");
	return 0;
}