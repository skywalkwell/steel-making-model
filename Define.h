#pragma once
using namespace std;
//头文件
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <math.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
//常用数定义
const double PI(3.1415926);
const string emptyStr("Null");
const string failStr("Fail");
const double dbZero(0.000001);
const double dbFail(999999);
const char lblDev(',');
const char valDev(':');
const char quiryDev('_');
//类型别名
using strVec = vector<string>;
using dbVec = vector<double>;
using uuPVec = vector<pair<unsigned, unsigned>>;
// 数据标识定义
enum class IDN :unsigned int
{
	//单质元素
	C = 1, Si = 2, Mn = 3, P = 4, S = 5, Cr = 6, Ni = 7, Mo = 8, Cu = 9, Al = 10, V = 11, Ti = 12, B = 13, N = 14, O = 15, Fe = 16,
	//氧化物元素
	CaO = 17, SiO2 = 18, MgO = 19, Al2O3 = 20, MnO = 21, FeO = 22, Fe2O3 = 23, P2O5 = 24, CaF2 = 25, Cr2O3 = 26, V2O3 = 27, Burnt = 28,
	//大类类别名称
	Stl = 29, Scrp = 30, Slag = 31, Flux = 32, Alloy = 33, Para = 34, State = 35, Enrg = 36,
	//钢液及炉渣中类别名称
	Ini = 37, Real = 38, Aim = 39, Low = 40, Upp = 41,
	//废钢中类别名称
	Wgh = 42, Light = 43, Return = 44,
	//副原料料仓
	Lime1 = 45, Lime2 = 46, Dolo1 = 47, Dolo2 = 48, Ore1 = 49, Ore2 = 50, Ore3 = 51, Ore4 = 52, Fluo = 53, PureMg = 54, Free1 = 55, Free2 = 56, Free3 = 57,
	//合金料仓
	FeSi = 58, FeMn = 59, Lime = 60, Dolo = 61, Ore = 62, FeSi1 = 63, FeSi2 = 64, FeMn1 = 65, FeMn2 = 66, FeCr = 67, FeCr1 = 68, FeCr2 = 69, FeNi = 70, FeNi1 = 71,
	FeNi2 = 72, FeMo = 73, FeMo1 = 74, FeMo2 = 75, FeSiMn = 76, BulkAl = 77, CoolSC = 78, CoolSC1 = 79, CoolSC2 = 80,
	//物质属性//
	Ratio = 81, Wgt = 82, Temp = 83, CWgt = 84, MElem1 = 85, MElem2 = 86, Thermal1 = 87, Thermal2 = 88,
	//参数中类别
	Basic = 89, PureFlux = 90, Lining = 91, Radio = 92, Static = 93, History = 94, GasType = 95,
	//参数名
	LSi = 96, USi = 97, LBa = 98, UBa = 99, CeqMn = 100, RedSi = 101, CMgO = 102, CCaF2 = 103, AveLen = 104, AveSqr = 105, TOne = 106, TTwo = 107,
	MouthSqr = 108, CaliHeats = 109, QtyFe = 110, QtyCr = 111, LLimTDelta = 112, ULimTDelta = 113, TSCC = 114, kTSC = 115, kTSO = 116, OxyFlow = 117,
	LastOxyAmt = 118, BottomFlow = 119, KeyTemp = 120, CoolMat = 121, N2 = 122, Ar = 123, O2 = 124,
	//热效应中类别
	Reac = 125, Oxid = 126, Elem = 127, Misc = 128, RadioK = 129,
	//状态类中类别
	Time = 130, Cons = 131, Score = 132, Atom = 133, Assess = 134, Spare = 135,
	//时间状态参数
	Prepare = 136, Start = 137, ScrpFeed = 138, HMFeed = 139, Ignition = 140, Blowing = 141, Meas1 = 142, BlowEnd = 143, Meas2 = 144, Meas3 = 145, Tapping = 146,
	Splash = 147, End = 148, TDiff = 149, StaticTemp = 150, Free = 151,
	//碱度及纯熔剂计算
	Result = 152, Basicity = 153, PureCaO = 154, PureMgO = 155, PureCaF2 = 156, MatFlux = 157, MEComp = 158,
	//熔池状态计算
	Old = 159, New = 160, OxyAlSi = 161, CO = 162, keyC = 163, kForC = 164, kForP = 165, iniP = 166, Set = 167,
	//预测计算
	LTempSyb = 168, HTempSyb = 169, LLTempSyb = 170, HHTempSyb = 171, OxyAmt = 172, LancePos = 173, HighH = 174, High = 175, Mid = 176, LowL = 177,
	//合金化
	BottomTime = 178,
	//标记
	Empty = 179, IDFail = 180
};
using idPVec = vector<pair<IDN, string>>;
using idVec = vector<IDN>;
//标识对照表：数字与字符串
idPVec pairID =
{
	//单质元素
	{IDN::C,"C"},{IDN::Si,"Si"},{IDN::Mn,"Mn"},{IDN::P,"P"},{IDN::S,"S"},{IDN::Cr,"Cr"},{IDN::Ni,"Ni"},{IDN::Mo,"Mo"},{IDN::Cu,"Cu"},{IDN::Al,"Al"},
	{IDN::V,"V"},{IDN::Ti,"Ti"},{IDN::B,"B"},{IDN::N,"N"},{IDN::O,"O"},{IDN::Fe,"Fe"},
	//氧化物元素
	{IDN::CaO,"CaO"},{IDN::SiO2,"SiO2"},{IDN::MgO,"MgO"},{IDN::Al2O3,"Al2O3"},{IDN::MnO,"MnO"},{IDN::FeO,"FeO"},{IDN::Fe2O3,"Fe2O3"},
	{IDN::P2O5,"P2O5"},{IDN::CaF2,"CaF2"},{IDN::Cr2O3,"Cr2O3"},{IDN::V2O3,"V2O3"},{IDN::Burnt,"Burnt"},
	//其他需数字化的名称
	{IDN::N2,"N2"}, {IDN::Ar,"Ar"}, {IDN::O2,"O2"},
	//大类及属性
	{IDN::Stl,"Stl"},{IDN::Scrp,"Scrp"},{IDN::Slag,"Slag"},{IDN::Flux,"Flux"},{IDN::Alloy,"Alloy"},{IDN::Para,"Para"},{IDN::State,"State"},{IDN::Enrg,"Enrg"},
	{IDN::Wgt,"Wgt"},{IDN::Temp,"Temp"},{IDN::CWgt,"CWgt"},{IDN::MElem1,"MElem1"},{IDN::MElem2,"MElem2"},{IDN::Thermal1,"Thermal1"},{IDN::Thermal2,"Thermal2"},
	{IDN::Ratio,"Ratio"},
	//中类
	{IDN::Ini, "Ini"},{IDN::Real,"Real"},{IDN::Aim,"Aim"},{IDN::Low,"Low"}, {IDN::Upp,"Upp"}, {IDN::Wgh,"Wgh"}, {IDN::Light,"Light"}, {IDN::Return,"Return"},{IDN::Free1,"Free1"},
	//料仓
	{IDN::Lime1,"Lime1"}, {IDN::Lime2,"Lime2"}, {IDN::Dolo1,"Dolo1"}, {IDN::Dolo2,"Dolo2"}, {IDN::Ore1,"Ore1"}, {IDN::Ore2,"Ore2"},{IDN::Fluo,"Fluo"},{IDN::Free2,"Free2"},
	{IDN::PureMg,"PureMg"}, {IDN::Free3,"Free3"},{IDN::Lime,"Lime"}, {IDN::Dolo,"Dolo"}, {IDN::Ore,"Ore"}, {IDN::Ore3,"Ore3"}, {IDN::Ore4,"Ore4"},
	//合金料仓
	{IDN::FeSi,"FeSi"},{IDN::FeMn,"FeMn"},{IDN::FeSi1,"FeSi1"}, {IDN::FeSi2,"FeSi2"}, {IDN::FeMn1,"FeMn1"}, {IDN::FeMn2,"FeMn2"}, {IDN::FeCr,"FeCr"},{IDN::FeCr1,"FeCr1"},
	{IDN::FeCr2,"FeCr2"}, {IDN::FeNi,"FeNi"}, {IDN::FeNi1,"FeNi1"},{IDN::FeNi2,"FeNi2"}, {IDN::FeMo,"FeMo"}, {IDN::FeMo1,"FeMo1"},{IDN::FeMo2,"FeMo2"},
	{IDN::FeSiMn,"FeSiMn"}, {IDN::BulkAl,"BulkAl"}, {IDN::CoolSC,"CoolSC"}, {IDN::CoolSC1,"CoolSC1"}, {IDN::CoolSC2,"CoolSC2"}, {IDN::Basic,"Basic"},
	//参数
	{IDN::PureFlux,"PureFlux"}, {IDN::Lining,"Lining"}, {IDN::Radio,"Radio"}, {IDN::Static,"Static"}, {IDN::History,"History"}, {IDN::LSi,"LSi"}, {IDN::USi,"USi"},	{IDN::LBa,"LBa"},
	{IDN::UBa,"UBa"}, {IDN::CeqMn,"CeqMn"}, {IDN::RedSi,"RedSi"}, {IDN::CMgO,"CMgO"}, {IDN::CCaF2,"CCaF2"},{IDN::AveLen,"AveLen"}, {IDN::AveSqr,"AveSqr"},
	{IDN::TOne,"TOne"}, {IDN::TTwo,"TTwo"}, {IDN::MouthSqr,"MouthSqr"}, {IDN::CaliHeats,"CaliHeats"}, {IDN::QtyFe,"QtyFe"},	{IDN::QtyCr,"QtyCr"},
	{IDN::LLimTDelta,"LLimTDelta"}, {IDN::ULimTDelta,"ULimTDelta"},	{IDN::TSCC,"TSCC"}, {IDN::kTSC,"kTSC"}, {IDN::kTSO,"kTSO"},{IDN::OxyFlow,"OxyFlow"},
	{IDN::LastOxyAmt,"LastOxyAmt"}, {IDN::BottomFlow,"BottomFlow"}, {IDN::KeyTemp,"KeyTemp"}, {IDN::CoolMat,"CoolMat"},{IDN::GasType,"GasType"},
	//热效应
	{IDN::Reac,"Reac"}, {IDN::Oxid,"Oxid"}, {IDN::Elem,"Elem"}, {IDN::Misc,"Misc"}, {IDN::RadioK,"RadioK"},
	//时间状态
	{IDN::Time,"Time"}, {IDN::Cons,"Cons"}, {IDN::Score,"Score"}, {IDN::Atom,"Atom"}, {IDN::Assess,"Assess"}, {IDN::Spare,"Spare"}, {IDN::Prepare,"Prepare"},
	{IDN::Start,"Start"},  {IDN::ScrpFeed,"ScrpFeed"}, {IDN::HMFeed,"HMFeed"}, {IDN::Ignition,"Ignition"}, {IDN::Blowing,"Blowing"}, {IDN::Meas1,"Meas1"},
	{IDN::BlowEnd,"BlowEnd"},	{IDN::Meas2,"Meas2"}, {IDN::Meas3,"Meas3"}, {IDN::Tapping,"Tapping"}, {IDN::Splash,"Splash"},	{IDN::End,"End"}, {IDN::TDiff,"TDiff"},
	{IDN::StaticTemp,"StaticTemp"},
	//熔剂计算
	{IDN::Result, "Result"}, {IDN::Basicity,"Basicity"}, {IDN::PureCaO,"PureCaO"}, {IDN::PureMgO,"PureMgO"}, {IDN::PureCaF2,"PureCaF2"}, {IDN::MatFlux, "MatFlux"},
	{IDN::MEComp, "MEComp"},
	//熔池状态计算
	{IDN::Old, "Old"}, {IDN::New, "New"}, {IDN::OxyAlSi, "OxyAlSi"}, {IDN::CO, "CO"}, {IDN::keyC,"keyC"}, {IDN::kForC,"kForC"}, {IDN::kForP,"kForP"}, {IDN::iniP,"iniP"},
	{IDN::Set,"Set"},
	//预测计算
	{IDN::LTempSyb,"LTempSyb"}, {IDN::HTempSyb,"HTempSyb"}, {IDN::LLTempSyb,"LLTempSyb"}, {IDN::HHTempSyb,"HHTempSyb"},{IDN::OxyAmt, "OxyAmt"},
	{IDN::LancePos,"LancePos"}, {IDN::HighH,"HighH"}, {IDN::High,"High"}, {IDN::Mid, "Mid"}, {IDN::LowL, "LowL"},
	//合金化
	{IDN::BottomTime,"BottomTime"},
	//标记
	{IDN::Free,"Free"}, {IDN::Empty,emptyStr},{IDN::IDFail,"IDFail"}
};
//类1：数据元——带标签的数据
class DataCell
{
private:
	const size_t lblCnt = 4; /*数据标签的数量*/
	idVec          Lable;        /*标签*/
	double        Val;           /*数据*/
public:
	DataCell();                                          /*构造函数：完成数据元的初始化*/
	size_t size() const;                              /*读取对象大小*/
	DataCell& operator = (string&);       /*重载：字符串赋值*/
	DataCell& operator = (DataCell&);  /*重载：元数据赋值*/
	DataCell& operator = (double);       /*重载：内部类型赋值*/
	double operator [] (size_t) const;     /*重载：下标运算-相当于读取函数，输入序号，输出double*/
	double operator + (double&);         /*重载：加法*/
	double operator - (double&);         /*重载：减法*/
	double operator * (double&);         /*重载：乘法*/
	double operator / (double&);         /*重载：除法*/
	bool     operator==(DataCell&) const;    /*重载：等号-元数据*/
	bool     operator==(string&) const;         /*重载：等号-字符串*/
	bool     operator>(double&) const;        /*重载：大于*/
	bool     operator<(double&) const;        /*重载：小于*/
	bool     operator>=(double&) const;     /*重载：大于等于*/
	bool     operator<=(double&) const;     /*重载：小于等于*/
	bool     Set(IDN, size_t);                          /*设定值*/
};
using myDC = DataCell;
using DCVec = vector<myDC>;
//类2：数据元向量操作接口
class DataOpe
{
private:
	DCVec  Vec;       /*数据向量，编译时确定*/
	uuPVec Index;    /*索引：静态数据向量*/
private:
	virtual bool     Cal() = 0;/*功能函数，由子类定义，仅有唯一启动入口——写入新数据*/
	size_t              meetType(DataCell&, DataCell&); /*元数据相等类型判断：返回0-完全相等；返回2:-完全不等；返回1:-部分相等（目标元数据标签被全部包含）*/
public:
	virtual bool     BuildIndex();                                                  /*建立索引*/
	virtual DCVec Read(DataCell&);                                          /*指定元数据批读取：部分相等*/
	virtual DCVec Read(string&);                                               /*指定字符串批读取：部分相等*/
	virtual myDC& Read(size_t);                                                /*指定向量序号单读取：根据索引*/
	virtual DCVec Get(size_t, size_t);                                         /*指定向量序号区间批读取：根据索引*/
	virtual bool     Write(DataCell&, bool);                                /*元数据单写入：必须完全相等才可写*/
	virtual bool     Write(string&, bool);                                     /*字符串单写入：必须完全相等才可写*/
	virtual bool     Write(size_t, double, bool);                           /*指定位置单写入：根据索引*/
	virtual bool     Set(DataCell&, double*, unsigned, bool);    /*元数据批写入：部分相等即可写*/
	virtual bool     Set(string&, double*, unsigned, bool);         /*字符串批写入：部分相等即可写*/
	virtual bool     Set(size_t, size_t, double*, bool);                 /*指定向量序号区间批写入：根据索引*/
	virtual bool     Add(DataCell&, bool);                                 /*元数据单增加：添加到末尾*/
	virtual bool     Add(string&, bool);                                      /*字符串单增加：添加到末尾*/
	virtual bool     Add(DCVec&, bool);                                   /*元数据批增加：添加到末尾*/
	virtual bool     Add(string&, size_t, bool);                           /*字符串单增加：添加到末尾*/
	virtual bool     Del(DataCell&, bool);                                  /*元数据单删除：指定删除*/
	virtual bool     Del(string&, bool);                                       /*字符串单删除：指定删除*/
	virtual uuPVec& GetIndex();                                               /*获取索引*/
};
//类3：数据输入及初步处理
class DataIO :public DataOpe
{
private:
	string fileName;   /*数据文件路径*/
private:
	void   Input();       /*从外部文件读入数据，并在程序中增加必要参数*/
	void   PreMass(); /*计算单个物质的铁含量或烧减含量*/
	void   PreEnrg();  /*计算单个物质的冷却系数1和冷却系数2，计算结果为：Thermal1-物理降温 , Thermal2--化学升温*/
	bool   Cal();         /*完成所有数据的初步处理工作*/
public:
	DataIO(int HeatNo);  /*构造函数*/
};
//类4：碱度及纯熔剂量计算，参数（数组的引用）有: LSi, USi, LBa, UBa, CeqMn, CMgO, CCaF2, IniSi, IniMn, RedSi, WStl，计算结果: Basic, pCaO, pMgO,pCaF2
class PureFlux :public DataOpe
{
private:
	DataIO* ptrIO;            /*外部数据操作指针*/
private:
	bool       Cal();            /*计算碱度，结果存入专用变量：15个固定参数，其中11个参数、4个结果*/
public:
	PureFlux(DataIO&);    /*构造函数*/
};
//类5：单个辅料用量，参数（数组的引用）有: pureCaO, pureMgO, pureCaF2, Basic, mainElem, MEComp, SiO2Comp, Ratio;计算结果: matFlux
class MatFlux :public DataOpe
{
private:
	DataIO* ptrIO;  /*外部数据操作指针*/
private:
	bool Cal();        /*功能函数*/
public:
	MatFlux(DataIO&); /*构造函数*/
};
//类6：熔池状态计算，参数有：上次吹炼时间（自动更新）、本次吹炼时间（外部输入）等；计算结果：钢液成分、温度及重量，炉渣成分、温度及重量
class BathState :public DataOpe
{
private:
	DataIO* ptrIO;                                   /*外部数据操作指针*/     
private: 
	idVec  elemName;                                                                                    /*8种氧化性元素的名称:Al/Si/V/Mn的顺序不能变*/
	idVec  oxidName;                                                                                     /*8种生成物名称*/
	dbVec elemOxy, elemTher;                                                                      /*8种氧化性元素的氧化系数*/
	dbVec oxyFlow, keyC, kForC;                                                                   /*临界碳及对应的k值*/
	size_t   elemN, seqAl, seqSi, seqV, seqMn, seqCr, seqP, seqFe, seqC;   /*8种氧化性元素元素在向量中的顺序*/
	double keyTemp, stlAimC, stlAimTemp, iniStlWgt, kForP, iniP;
	double oxyAlSi, iniC, nonCoxidTime;                                                       /*应在加入废钢及合金后进行更新*/
private:/*温度计算中的常用数*/
	double GasTher, BotFlow;                                                                       /*底吹用*/
	double k, s;                                                                                              /*辐射用*/
	double HeatVal, AveLen, AveSqr;                                                           /*炉衬传导用*/
	double slagTher;                                                                                     /*炉渣温度计算用*/
	IDN      BotType;                                                                                     /*底/侧吹类型*/
private:
	bool Cal();                                                                                               /*功能函数*/
public:
	BathState(DataIO&);                                                                              /*构造函数*/
};
//类7：策略规划，输入IO、熔池状态、纯熔剂及辅料类引用，输出：加料量、加料时点、氧枪枪位、变枪时点
class Predict :public DataOpe
{
private:
	DataIO* ptrIO;                   /*外部数据操作指针*/
	BathState* ptrBS, objBS;   /*本类功能计算单独使用的状态计算类对象及其指针*/
	PureFlux* ptrPF, objPF;      /*本类功能计算单独使用的纯熔剂计算类对象及其指针*/
	MatFlux* ptrMF, objMF;    /*本类功能计算单独使用的熔剂计算类对象及其指针*/
private:
	bool metalMass();                          /*金属料平衡*/
	bool fluxMass();                             /*辅料平衡*/
	bool oreCal();                                /*能量平衡*/
	bool oxyMass();                            /*氧平衡*/
	bool matFeed();                            /*加料方案*/
	bool oxyBlow();                             /*供氧方案*/
	bool Cal();                                    /*功能函数*/
public:
	Predict(DataIO&);                       /*构造函数：有参*/
};
//类8：吹炼中修正计算，参数有实时测量值：碳、温、时间，以及启动本功能的时点（获取实时测量值进行计算，否则只启动数据收集功能）
class InBlow :public DataOpe
{
private:
	BathState* ptrBS; /*熔池状态操作指针*/
	DataIO* ptrIO;     /*外部数据操作指针*/
	Predict* ptrPD;    /*规划数据结果操作指针*/
private:
	bool Cal();           /*功能函数*/
public:
	InBlow(BathState&, DataIO&, Predict&); /*带参初始化*/
};
//类9：合金化/还原（不锈钢）计算
class EndBlow :public DataOpe
{
private:
	BathState* ptrBS; /*熔池状态操作指针*/
	DataIO* ptrIO;     /*外部数据操作指针*/
private:
	bool           Cal(); /*功能函数*/
public:
	EndBlow(BathState&, DataIO&);  /*带参初始化*/
};
