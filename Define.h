#pragma once
using namespace std;
//ͷ�ļ�
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <math.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
//����������
const double PI(3.1415926);
const string emptyStr("Null");
const string failStr("Fail");
const double dbZero(0.000001);
const double dbFail(999999);
const char lblDev(',');
const char valDev(':');
const char quiryDev('_');
//���ͱ���
using strVec = vector<string>;
using dbVec = vector<double>;
using uuPVec = vector<pair<unsigned, unsigned>>;
// ���ݱ�ʶ����
enum class IDN :unsigned int
{
	//����Ԫ��
	C = 1, Si = 2, Mn = 3, P = 4, S = 5, Cr = 6, Ni = 7, Mo = 8, Cu = 9, Al = 10, V = 11, Ti = 12, B = 13, N = 14, O = 15, Fe = 16,
	//������Ԫ��
	CaO = 17, SiO2 = 18, MgO = 19, Al2O3 = 20, MnO = 21, FeO = 22, Fe2O3 = 23, P2O5 = 24, CaF2 = 25, Cr2O3 = 26, V2O3 = 27, Burnt = 28,
	//�����������
	Stl = 29, Scrp = 30, Slag = 31, Flux = 32, Alloy = 33, Para = 34, State = 35, Enrg = 36,
	//��Һ��¯�����������
	Ini = 37, Real = 38, Aim = 39, Low = 40, Upp = 41,
	//�ϸ����������
	Wgh = 42, Light = 43, Return = 44,
	//��ԭ���ϲ�
	Lime1 = 45, Lime2 = 46, Dolo1 = 47, Dolo2 = 48, Ore1 = 49, Ore2 = 50, Ore3 = 51, Ore4 = 52, Fluo = 53, PureMg = 54, Free1 = 55, Free2 = 56, Free3 = 57,
	//�Ͻ��ϲ�
	FeSi = 58, FeMn = 59, Lime = 60, Dolo = 61, Ore = 62, FeSi1 = 63, FeSi2 = 64, FeMn1 = 65, FeMn2 = 66, FeCr = 67, FeCr1 = 68, FeCr2 = 69, FeNi = 70, FeNi1 = 71,
	FeNi2 = 72, FeMo = 73, FeMo1 = 74, FeMo2 = 75, FeSiMn = 76, BulkAl = 77, CoolSC = 78, CoolSC1 = 79, CoolSC2 = 80,
	//��������//
	Ratio = 81, Wgt = 82, Temp = 83, CWgt = 84, MElem1 = 85, MElem2 = 86, Thermal1 = 87, Thermal2 = 88,
	//���������
	Basic = 89, PureFlux = 90, Lining = 91, Radio = 92, Static = 93, History = 94, GasType = 95,
	//������
	LSi = 96, USi = 97, LBa = 98, UBa = 99, CeqMn = 100, RedSi = 101, CMgO = 102, CCaF2 = 103, AveLen = 104, AveSqr = 105, TOne = 106, TTwo = 107,
	MouthSqr = 108, CaliHeats = 109, QtyFe = 110, QtyCr = 111, LLimTDelta = 112, ULimTDelta = 113, TSCC = 114, kTSC = 115, kTSO = 116, OxyFlow = 117,
	LastOxyAmt = 118, BottomFlow = 119, KeyTemp = 120, CoolMat = 121, N2 = 122, Ar = 123, O2 = 124,
	//��ЧӦ�����
	Reac = 125, Oxid = 126, Elem = 127, Misc = 128, RadioK = 129,
	//״̬�������
	Time = 130, Cons = 131, Score = 132, Atom = 133, Assess = 134, Spare = 135,
	//ʱ��״̬����
	Prepare = 136, Start = 137, ScrpFeed = 138, HMFeed = 139, Ignition = 140, Blowing = 141, Meas1 = 142, BlowEnd = 143, Meas2 = 144, Meas3 = 145, Tapping = 146,
	Splash = 147, End = 148, TDiff = 149, StaticTemp = 150, Free = 151,
	//��ȼ����ۼ�����
	Result = 152, Basicity = 153, PureCaO = 154, PureMgO = 155, PureCaF2 = 156, MatFlux = 157, MEComp = 158,
	//�۳�״̬����
	Old = 159, New = 160, OxyAlSi = 161, CO = 162, keyC = 163, kForC = 164, kForP = 165, iniP = 166, Set = 167,
	//Ԥ�����
	LTempSyb = 168, HTempSyb = 169, LLTempSyb = 170, HHTempSyb = 171, OxyAmt = 172, LancePos = 173, HighH = 174, High = 175, Mid = 176, LowL = 177,
	//�Ͻ�
	BottomTime = 178,
	//���
	Empty = 179, IDFail = 180
};
using idPVec = vector<pair<IDN, string>>;
using idVec = vector<IDN>;
//��ʶ���ձ��������ַ���
idPVec pairID =
{
	//����Ԫ��
	{IDN::C,"C"},{IDN::Si,"Si"},{IDN::Mn,"Mn"},{IDN::P,"P"},{IDN::S,"S"},{IDN::Cr,"Cr"},{IDN::Ni,"Ni"},{IDN::Mo,"Mo"},{IDN::Cu,"Cu"},{IDN::Al,"Al"},
	{IDN::V,"V"},{IDN::Ti,"Ti"},{IDN::B,"B"},{IDN::N,"N"},{IDN::O,"O"},{IDN::Fe,"Fe"},
	//������Ԫ��
	{IDN::CaO,"CaO"},{IDN::SiO2,"SiO2"},{IDN::MgO,"MgO"},{IDN::Al2O3,"Al2O3"},{IDN::MnO,"MnO"},{IDN::FeO,"FeO"},{IDN::Fe2O3,"Fe2O3"},
	{IDN::P2O5,"P2O5"},{IDN::CaF2,"CaF2"},{IDN::Cr2O3,"Cr2O3"},{IDN::V2O3,"V2O3"},{IDN::Burnt,"Burnt"},
	//���������ֻ�������
	{IDN::N2,"N2"}, {IDN::Ar,"Ar"}, {IDN::O2,"O2"},
	//���༰����
	{IDN::Stl,"Stl"},{IDN::Scrp,"Scrp"},{IDN::Slag,"Slag"},{IDN::Flux,"Flux"},{IDN::Alloy,"Alloy"},{IDN::Para,"Para"},{IDN::State,"State"},{IDN::Enrg,"Enrg"},
	{IDN::Wgt,"Wgt"},{IDN::Temp,"Temp"},{IDN::CWgt,"CWgt"},{IDN::MElem1,"MElem1"},{IDN::MElem2,"MElem2"},{IDN::Thermal1,"Thermal1"},{IDN::Thermal2,"Thermal2"},
	{IDN::Ratio,"Ratio"},
	//����
	{IDN::Ini, "Ini"},{IDN::Real,"Real"},{IDN::Aim,"Aim"},{IDN::Low,"Low"}, {IDN::Upp,"Upp"}, {IDN::Wgh,"Wgh"}, {IDN::Light,"Light"}, {IDN::Return,"Return"},{IDN::Free1,"Free1"},
	//�ϲ�
	{IDN::Lime1,"Lime1"}, {IDN::Lime2,"Lime2"}, {IDN::Dolo1,"Dolo1"}, {IDN::Dolo2,"Dolo2"}, {IDN::Ore1,"Ore1"}, {IDN::Ore2,"Ore2"},{IDN::Fluo,"Fluo"},{IDN::Free2,"Free2"},
	{IDN::PureMg,"PureMg"}, {IDN::Free3,"Free3"},{IDN::Lime,"Lime"}, {IDN::Dolo,"Dolo"}, {IDN::Ore,"Ore"}, {IDN::Ore3,"Ore3"}, {IDN::Ore4,"Ore4"},
	//�Ͻ��ϲ�
	{IDN::FeSi,"FeSi"},{IDN::FeMn,"FeMn"},{IDN::FeSi1,"FeSi1"}, {IDN::FeSi2,"FeSi2"}, {IDN::FeMn1,"FeMn1"}, {IDN::FeMn2,"FeMn2"}, {IDN::FeCr,"FeCr"},{IDN::FeCr1,"FeCr1"},
	{IDN::FeCr2,"FeCr2"}, {IDN::FeNi,"FeNi"}, {IDN::FeNi1,"FeNi1"},{IDN::FeNi2,"FeNi2"}, {IDN::FeMo,"FeMo"}, {IDN::FeMo1,"FeMo1"},{IDN::FeMo2,"FeMo2"},
	{IDN::FeSiMn,"FeSiMn"}, {IDN::BulkAl,"BulkAl"}, {IDN::CoolSC,"CoolSC"}, {IDN::CoolSC1,"CoolSC1"}, {IDN::CoolSC2,"CoolSC2"}, {IDN::Basic,"Basic"},
	//����
	{IDN::PureFlux,"PureFlux"}, {IDN::Lining,"Lining"}, {IDN::Radio,"Radio"}, {IDN::Static,"Static"}, {IDN::History,"History"}, {IDN::LSi,"LSi"}, {IDN::USi,"USi"},	{IDN::LBa,"LBa"},
	{IDN::UBa,"UBa"}, {IDN::CeqMn,"CeqMn"}, {IDN::RedSi,"RedSi"}, {IDN::CMgO,"CMgO"}, {IDN::CCaF2,"CCaF2"},{IDN::AveLen,"AveLen"}, {IDN::AveSqr,"AveSqr"},
	{IDN::TOne,"TOne"}, {IDN::TTwo,"TTwo"}, {IDN::MouthSqr,"MouthSqr"}, {IDN::CaliHeats,"CaliHeats"}, {IDN::QtyFe,"QtyFe"},	{IDN::QtyCr,"QtyCr"},
	{IDN::LLimTDelta,"LLimTDelta"}, {IDN::ULimTDelta,"ULimTDelta"},	{IDN::TSCC,"TSCC"}, {IDN::kTSC,"kTSC"}, {IDN::kTSO,"kTSO"},{IDN::OxyFlow,"OxyFlow"},
	{IDN::LastOxyAmt,"LastOxyAmt"}, {IDN::BottomFlow,"BottomFlow"}, {IDN::KeyTemp,"KeyTemp"}, {IDN::CoolMat,"CoolMat"},{IDN::GasType,"GasType"},
	//��ЧӦ
	{IDN::Reac,"Reac"}, {IDN::Oxid,"Oxid"}, {IDN::Elem,"Elem"}, {IDN::Misc,"Misc"}, {IDN::RadioK,"RadioK"},
	//ʱ��״̬
	{IDN::Time,"Time"}, {IDN::Cons,"Cons"}, {IDN::Score,"Score"}, {IDN::Atom,"Atom"}, {IDN::Assess,"Assess"}, {IDN::Spare,"Spare"}, {IDN::Prepare,"Prepare"},
	{IDN::Start,"Start"},  {IDN::ScrpFeed,"ScrpFeed"}, {IDN::HMFeed,"HMFeed"}, {IDN::Ignition,"Ignition"}, {IDN::Blowing,"Blowing"}, {IDN::Meas1,"Meas1"},
	{IDN::BlowEnd,"BlowEnd"},	{IDN::Meas2,"Meas2"}, {IDN::Meas3,"Meas3"}, {IDN::Tapping,"Tapping"}, {IDN::Splash,"Splash"},	{IDN::End,"End"}, {IDN::TDiff,"TDiff"},
	{IDN::StaticTemp,"StaticTemp"},
	//�ۼ�����
	{IDN::Result, "Result"}, {IDN::Basicity,"Basicity"}, {IDN::PureCaO,"PureCaO"}, {IDN::PureMgO,"PureMgO"}, {IDN::PureCaF2,"PureCaF2"}, {IDN::MatFlux, "MatFlux"},
	{IDN::MEComp, "MEComp"},
	//�۳�״̬����
	{IDN::Old, "Old"}, {IDN::New, "New"}, {IDN::OxyAlSi, "OxyAlSi"}, {IDN::CO, "CO"}, {IDN::keyC,"keyC"}, {IDN::kForC,"kForC"}, {IDN::kForP,"kForP"}, {IDN::iniP,"iniP"},
	{IDN::Set,"Set"},
	//Ԥ�����
	{IDN::LTempSyb,"LTempSyb"}, {IDN::HTempSyb,"HTempSyb"}, {IDN::LLTempSyb,"LLTempSyb"}, {IDN::HHTempSyb,"HHTempSyb"},{IDN::OxyAmt, "OxyAmt"},
	{IDN::LancePos,"LancePos"}, {IDN::HighH,"HighH"}, {IDN::High,"High"}, {IDN::Mid, "Mid"}, {IDN::LowL, "LowL"},
	//�Ͻ�
	{IDN::BottomTime,"BottomTime"},
	//���
	{IDN::Free,"Free"}, {IDN::Empty,emptyStr},{IDN::IDFail,"IDFail"}
};
//��1������Ԫ��������ǩ������
class DataCell
{
private:
	const size_t lblCnt = 4; /*���ݱ�ǩ������*/
	idVec          Lable;        /*��ǩ*/
	double        Val;           /*����*/
public:
	DataCell();                                          /*���캯�����������Ԫ�ĳ�ʼ��*/
	size_t size() const;                              /*��ȡ�����С*/
	DataCell& operator = (string&);       /*���أ��ַ�����ֵ*/
	DataCell& operator = (DataCell&);  /*���أ�Ԫ���ݸ�ֵ*/
	DataCell& operator = (double);       /*���أ��ڲ����͸�ֵ*/
	double operator [] (size_t) const;     /*���أ��±�����-�൱�ڶ�ȡ������������ţ����double*/
	double operator + (double&);         /*���أ��ӷ�*/
	double operator - (double&);         /*���أ�����*/
	double operator * (double&);         /*���أ��˷�*/
	double operator / (double&);         /*���أ�����*/
	bool     operator==(DataCell&) const;    /*���أ��Ⱥ�-Ԫ����*/
	bool     operator==(string&) const;         /*���أ��Ⱥ�-�ַ���*/
	bool     operator>(double&) const;        /*���أ�����*/
	bool     operator<(double&) const;        /*���أ�С��*/
	bool     operator>=(double&) const;     /*���أ����ڵ���*/
	bool     operator<=(double&) const;     /*���أ�С�ڵ���*/
	bool     Set(IDN, size_t);                          /*�趨ֵ*/
};
using myDC = DataCell;
using DCVec = vector<myDC>;
//��2������Ԫ���������ӿ�
class DataOpe
{
private:
	DCVec  Vec;       /*��������������ʱȷ��*/
	uuPVec Index;    /*��������̬��������*/
private:
	virtual bool     Cal() = 0;/*���ܺ����������ඨ�壬����Ψһ������ڡ���д��������*/
	size_t              meetType(DataCell&, DataCell&); /*Ԫ������������жϣ�����0-��ȫ��ȣ�����2:-��ȫ���ȣ�����1:-������ȣ�Ŀ��Ԫ���ݱ�ǩ��ȫ��������*/
public:
	virtual bool     BuildIndex();                                                  /*��������*/
	virtual DCVec Read(DataCell&);                                          /*ָ��Ԫ��������ȡ���������*/
	virtual DCVec Read(string&);                                               /*ָ���ַ�������ȡ���������*/
	virtual myDC& Read(size_t);                                                /*ָ��������ŵ���ȡ����������*/
	virtual DCVec Get(size_t, size_t);                                         /*ָ�����������������ȡ����������*/
	virtual bool     Write(DataCell&, bool);                                /*Ԫ���ݵ�д�룺������ȫ��Ȳſ�д*/
	virtual bool     Write(string&, bool);                                     /*�ַ�����д�룺������ȫ��Ȳſ�д*/
	virtual bool     Write(size_t, double, bool);                           /*ָ��λ�õ�д�룺��������*/
	virtual bool     Set(DataCell&, double*, unsigned, bool);    /*Ԫ������д�룺������ȼ���д*/
	virtual bool     Set(string&, double*, unsigned, bool);         /*�ַ�����д�룺������ȼ���д*/
	virtual bool     Set(size_t, size_t, double*, bool);                 /*ָ���������������д�룺��������*/
	virtual bool     Add(DataCell&, bool);                                 /*Ԫ���ݵ����ӣ���ӵ�ĩβ*/
	virtual bool     Add(string&, bool);                                      /*�ַ��������ӣ���ӵ�ĩβ*/
	virtual bool     Add(DCVec&, bool);                                   /*Ԫ���������ӣ���ӵ�ĩβ*/
	virtual bool     Add(string&, size_t, bool);                           /*�ַ��������ӣ���ӵ�ĩβ*/
	virtual bool     Del(DataCell&, bool);                                  /*Ԫ���ݵ�ɾ����ָ��ɾ��*/
	virtual bool     Del(string&, bool);                                       /*�ַ�����ɾ����ָ��ɾ��*/
	virtual uuPVec& GetIndex();                                               /*��ȡ����*/
};
//��3���������뼰��������
class DataIO :public DataOpe
{
private:
	string fileName;   /*�����ļ�·��*/
private:
	void   Input();       /*���ⲿ�ļ��������ݣ����ڳ��������ӱ�Ҫ����*/
	void   PreMass(); /*���㵥�����ʵ����������ռ�����*/
	void   PreEnrg();  /*���㵥�����ʵ���ȴϵ��1����ȴϵ��2��������Ϊ��Thermal1-������ , Thermal2--��ѧ����*/
	bool   Cal();         /*����������ݵĳ���������*/
public:
	DataIO(int HeatNo);  /*���캯��*/
};
//��4����ȼ����ۼ������㣬��������������ã���: LSi, USi, LBa, UBa, CeqMn, CMgO, CCaF2, IniSi, IniMn, RedSi, WStl��������: Basic, pCaO, pMgO,pCaF2
class PureFlux :public DataOpe
{
private:
	DataIO* ptrIO;            /*�ⲿ���ݲ���ָ��*/
private:
	bool       Cal();            /*�����ȣ��������ר�ñ�����15���̶�����������11��������4�����*/
public:
	PureFlux(DataIO&);    /*���캯��*/
};
//��5������������������������������ã���: pureCaO, pureMgO, pureCaF2, Basic, mainElem, MEComp, SiO2Comp, Ratio;������: matFlux
class MatFlux :public DataOpe
{
private:
	DataIO* ptrIO;  /*�ⲿ���ݲ���ָ��*/
private:
	bool Cal();        /*���ܺ���*/
public:
	MatFlux(DataIO&); /*���캯��*/
};
//��6���۳�״̬���㣬�����У��ϴδ���ʱ�䣨�Զ����£������δ���ʱ�䣨�ⲿ���룩�ȣ�����������Һ�ɷ֡��¶ȼ�������¯���ɷ֡��¶ȼ�����
class BathState :public DataOpe
{
private:
	DataIO* ptrIO;                                   /*�ⲿ���ݲ���ָ��*/     
private: 
	idVec  elemName;                                                                                    /*8��������Ԫ�ص�����:Al/Si/V/Mn��˳���ܱ�*/
	idVec  oxidName;                                                                                     /*8������������*/
	dbVec elemOxy, elemTher;                                                                      /*8��������Ԫ�ص�����ϵ��*/
	dbVec oxyFlow, keyC, kForC;                                                                   /*�ٽ�̼����Ӧ��kֵ*/
	size_t   elemN, seqAl, seqSi, seqV, seqMn, seqCr, seqP, seqFe, seqC;   /*8��������Ԫ��Ԫ���������е�˳��*/
	double keyTemp, stlAimC, stlAimTemp, iniStlWgt, kForP, iniP;
	double oxyAlSi, iniC, nonCoxidTime;                                                       /*Ӧ�ڼ���ϸּ��Ͻ����и���*/
private:/*�¶ȼ����еĳ�����*/
	double GasTher, BotFlow;                                                                       /*�״���*/
	double k, s;                                                                                              /*������*/
	double HeatVal, AveLen, AveSqr;                                                           /*¯�Ĵ�����*/
	double slagTher;                                                                                     /*¯���¶ȼ�����*/
	IDN      BotType;                                                                                     /*��/�വ����*/
private:
	bool Cal();                                                                                               /*���ܺ���*/
public:
	BathState(DataIO&);                                                                              /*���캯��*/
};
//��7�����Թ滮������IO���۳�״̬�����ۼ������������ã������������������ʱ�㡢��ǹǹλ����ǹʱ��
class Predict :public DataOpe
{
private:
	DataIO* ptrIO;                   /*�ⲿ���ݲ���ָ��*/
	BathState* ptrBS, objBS;   /*���๦�ܼ��㵥��ʹ�õ�״̬�����������ָ��*/
	PureFlux* ptrPF, objPF;      /*���๦�ܼ��㵥��ʹ�õĴ��ۼ������������ָ��*/
	MatFlux* ptrMF, objMF;    /*���๦�ܼ��㵥��ʹ�õ��ۼ������������ָ��*/
private:
	bool metalMass();                          /*������ƽ��*/
	bool fluxMass();                             /*����ƽ��*/
	bool oreCal();                                /*����ƽ��*/
	bool oxyMass();                            /*��ƽ��*/
	bool matFeed();                            /*���Ϸ���*/
	bool oxyBlow();                             /*��������*/
	bool Cal();                                    /*���ܺ���*/
public:
	Predict(DataIO&);                       /*���캯�����в�*/
};
//��8���������������㣬������ʵʱ����ֵ��̼���¡�ʱ�䣬�Լ����������ܵ�ʱ�㣨��ȡʵʱ����ֵ���м��㣬����ֻ���������ռ����ܣ�
class InBlow :public DataOpe
{
private:
	BathState* ptrBS; /*�۳�״̬����ָ��*/
	DataIO* ptrIO;     /*�ⲿ���ݲ���ָ��*/
	Predict* ptrPD;    /*�滮���ݽ������ָ��*/
private:
	bool Cal();           /*���ܺ���*/
public:
	InBlow(BathState&, DataIO&, Predict&); /*���γ�ʼ��*/
};
//��9���Ͻ�/��ԭ������֣�����
class EndBlow :public DataOpe
{
private:
	BathState* ptrBS; /*�۳�״̬����ָ��*/
	DataIO* ptrIO;     /*�ⲿ���ݲ���ָ��*/
private:
	bool           Cal(); /*���ܺ���*/
public:
	EndBlow(BathState&, DataIO&);  /*���γ�ʼ��*/
};
