
#pragma once

//***************************************************************************************
//****************************** ����Ϊ�����ڴ���������� *******************************
//***************************************************************************************


#define WAVE_CONTROL_POINTS		1000L		//���οؼ�����

#define MEMORY_RAWDATA_SIZE		4000L		//ԭʼ���ݻ�������С
#define MEMORY_WIDTHDATA_SIZE	200L		//��ȼ�����ʱ��������С
#define MEMORY_STEELCURVE_SIZE	6000L		//�������߻�������С
#define MEMORY_WARNING_SIZE		100L		//�澯��Ϣ��������С

#define WIDTH_FREQUENCY			50L			//��ȼ���Ƶ�ʣ�һ�㶨Ϊ 50Hz


#define MAX_EDGE_NUM 40
struct StructCCDModify
{
	double pix[MAX_EDGE_NUM];
	double CCDModify[MAX_EDGE_NUM];
};
struct StructModifyPix
{
	int num;
	StructCCDModify CCD1Modify;
	StructCCDModify CCD2Modify;
};

struct StructCalcParam
{
	StructModifyPix modify;//��������
	double C1x;					//C1(x,y)
	double C1y;
	double C2x;					//C2(x,y)
	double C2y;
	double P1[3];
	double P2[3];
	double s_midY;//������ϵ�����ԭ��
	double s_midCCD[2];//������ϵ�ԭ���Ӧ������
	double s_LowOffset[MAX_EDGE_NUM];
	double s_HighOffset[MAX_EDGE_NUM];

	double dis12_34;
};

struct StructRawData
{
	BYTE CCD11[5000];	//CCD1��ԭʼ�Ҷ�����
	BYTE CCD12[5000];	//CCD2��ԭʼ�Ҷ�����
	BYTE CCD21[5000];	//CCD3��ԭʼ�Ҷ�����
	BYTE CCD22[5000];	//CCD4��ԭʼ�Ҷ�����
	float Speed;		//�����壬ֻΪ�;ɵĲ�������ͳһ��
};


struct StructRawDataSpace
{
	StructRawData RData[MEMORY_RAWDATA_SIZE];	//ԭʼ����FIFO
	LONG WriteIndex;							//��ǰд����
};

struct StructWidthData
{
	LONG RawIndex;				//������ݶ�Ӧ��ԭʼ����Index
	float Speed;				//����˲ʱ�ٶ�

	BOOL HaveSteel;				//����ͨ�����и֣����������������Ҳ���ܿ�ȼ��㲻��ȷ��
	LONG CCD1Edge[2];			//CCD1����ֵ
	LONG CCD2Edge[2];			//CCD2����ֵ
	float x1,y1;				//�ְ������ʵ������
	float x2,y2;				//�ְ��ұ���ʵ������
	float Angle;				//�ְ���б�Ƕ�
	float RealWidth;			//���ο��ֵ
	float RealCenter;			//����������ֵ

	BOOL IsWidthValid;			//�����Ч����ȼ�������ȷ�ģ�
	float AvgWidth;				//��ֵ�˲����
	float AvgCenter;			//��ֵ�˲�������
};

struct StructWidthDataSpace
{
	StructWidthData WData[MEMORY_WIDTHDATA_SIZE];	//���ֵFIFO
	LONG WriteIndex;								//���ֵд����
};

struct StructWarningItem
{
	__time64_t Time;			//�澯����ʱ��
	LONG Type;					//�澯��� 0��Ϣ 1���� 2���ش���
	TCHAR Info[60];				//�澯��Ϣ
};

struct StructWarningItemSpace
{
	StructWarningItem WarnData[MEMORY_WARNING_SIZE];	//�澯FIFO
	LONG WriteIndex;									//�澯д����
};

struct StructSteelInfoSpace
{
	//�������ݲ���
	TCHAR CoilID[32];			//���ֱ��
	TCHAR Material[16];			//���ֲ���
	float ProductWidth;			//��Ʒ��ȣ���������Ϣ��ʾ��
	float ProductThickness;		//��Ʒ���

	//һ�����ݲ���
	float StdWidth;				//���ο�ȣ�Ŀ���ȣ�
	LONG CurrentPass;			//��ǰ����
	LONG TotalPass;				//�ܵ���
	float Speed;				//�ٶ�
	LONG Temperature;			//�¶�

	//�Դ�����
	TCHAR BatchCode[16];	    //��������
	TCHAR Ban[4];				//��ţ��ѷ�����
	float StdCenter;			//����������λ��
	float ColdRatio;			//����ϵ��
};

struct StructOtherInfoSpace
{
	BOOL DeviceHealthy;			//������豸�����źţ������
	LONG DeviceTemperature;		//������¶ȣ���Χ-50��100�ȣ�1��5V�����룩
	LONG TodayCoilCount;		//���ո���ͳ��

	//-----------ע�⣺�ع�����Ƿֿ����е�--------------
	UINT LightThreshold;		//��ǿ���ޣ����ں͹�ǿ��ֵ���Ƚϵ�ֵ��
	LONG AutoIntegrationCCD11;	//�Զ������������CCD11
	LONG AutoIntegrationCCD12;	//�Զ������������CCD12
	LONG AutoIntegrationCCD21;	//�Զ������������CCD21
	LONG AutoIntegrationCCD22;	//�Զ������������CCD22
	UINT AvgGrayCCD11;			//CCD11ƽ���Ҷ�
	UINT AvgGrayCCD12;			//CCD12ƽ���Ҷ�
	UINT AvgGrayCCD21;			//CCD21ƽ���Ҷ�
	UINT AvgGrayCCD22;			//CCD22ƽ���Ҷ�

	//---------------------�������---------------------
	BOOL UseCorrection;			//ʹ�÷ֶ��������ܡ�
	LONG CorrectionCount;		//����������
	float MeasuredWidth[10];	//�������Ŀ�ȣ�����10���㣩
	float RealWidth[10];		//ʵ�ʿ��

	//---------------------���������ź�---------------------
	BOOL NoneCoilSign;			//���ñ���Ϊ��ʱ��ǿ��д���޸ֲ��Σ�ģ�⻻��


	//---------------------��̼����Ϣ�����ڼ�����̬��ȣ�---------------------
	LONG MatCount;				//��̼�����ʵ�ʴ�С
	TCHAR MatArray[40][16];		//���еĸ�������
	float Carben[40];			//���ֶ�Ӧ�ĺ�̼��

};

struct StructSystemParamSpace
{
	LONG CCDPixel;				//�������
	UINT AvgFilterWindow;		//��ֵ�˲�����С
	LONG CutHeadPoints;			//ȥ��ͷ������
	LONG CutTailPoints;			//ȥ��β������
	BOOL UseBackgroundLamp;		//ʹ�ñ��������ģʽ
	BOOL UseAutoIntegration;	//ʹ���Զ��ع����
	BOOL RecordWave;			//¼��ԭʼ����
};

/**************************************************************************************

	��Ҫ��

	IsMeasuring��IsValid ��ר��������ʾ���̵ġ�
	m_CoilInView��HaveSteel��IsWidthValid ��ר���ڼ�����̵ġ�
	
	������Ƶ�Ŀ�ģ�����Ϊ�˰Ѽ������ʾ��ȫ�ֿ������������ʾ�����ݷֱ��ڲ�ͬ������
	�������ױ���������ǳ������

	���⣬���ڡ�ȥͷȥβ�����ܵļ��룬��ʾ���������Ǳȼ���������ͺ�����
	IsMeasuring Ҫ�� m_CoilInView �ͺ󣬵��� IsValid �� IsWidthValid ������ͬ��

**************************************************************************************/

struct StructSteelCurveSpace
{
	__time64_t CoilArriveTime;						//���ֵ���ʱ��
	float DisplayWidth;								//��ǰ��ȣ����ֽ���ʱ��ʾ��ֵ��
	float DisplayWidthDev;							//��ǰ���ƫ��
	float DisplayCenter;							//��ǰ�����е�λ��
	float DisplayCenterDev;							//��ǰ�����е�ƫ��
	float MaxWidth;									//������ֵ
	float MinWidth;									//�����Сֵ
	float AvgWidth;									//�������ƽ��ֵ
	StructSteelInfoSpace ThisCoilInfo;				//��������Ϣ�����ڸ�ͷʱ������һ�Σ��������ʱSteelInfo�仯��

	BOOL  IsMeasuring;								//���ڹ��֡������С���������CoilInView�źţ�
	BOOL  IsValid;									//������Ч�������ݡ���������ȷ��
	LONG  PointCount;								//�������ߵĵ���
	float Width[MEMORY_STEELCURVE_SIZE];			//���ֿ������
	float CenterDiff[MEMORY_STEELCURVE_SIZE];		//����������ƫ������
	float Length[MEMORY_STEELCURVE_SIZE];			//���ֳ�������
	BOOL  DataValid[MEMORY_STEELCURVE_SIZE];		//����������Ч����Ҫ����Ч����Ч��˲ʱ״̬��������ȡ�ã�
};

struct StructMem
{
	StructRawDataSpace rd;		//ԭʼ��������
	StructWidthDataSpace wd;	//�����������
	StructWarningItemSpace wi;	//�澯��Ϣ����
	StructSteelInfoSpace si;	//��׼������Ϣ����
	StructOtherInfoSpace oi;	//������Ϣ����
	StructSystemParamSpace sp;	//ϵͳ������Ϣ����
	StructSteelCurveSpace sc;	//������������
};





//*********************************************************************************
//****************************** ����Ϊ�����̽ṹ�� *******************************
//*********************************************************************************


typedef StructSteelCurveSpace StructHistoryData;


//struct StructCalcParam
//{
//	float CCD1Table[2][5000];		//CCD1��������Ӧ����
//	float CCD2Table[2][5000];		//CCD2��������Ӧ����
//	float C1x[2];					//C1(x,y)
//	float C1y[2];
//	float C2x[2];					//C2(x,y)
//	float C2y[2];
//	float dis12_34;//CCD12��34�ľ���
//};

struct StructHMI_1
{
	//************************* ������Ϣ ***************************
	__time64_t CoilArriveTime;						//���ֵ���ʱ��
	StructSteelInfoSpace ThisCoilInfo;				//��������Ϣ

	//************************* �������� *************************
	float DisplayWidth;								//��ȣ����ֽ���ʱ��ʾ��ֵ��
	float DisplayWidthDev;							//���ƫ��
	float MaxWidth;									//������ֵ
	float MinWidth;									//�����Сֵ
	float AvgWidth;									//ƽ�����

	//************************* �澯���� ***************************
	TCHAR WarningTime[20][16];
	LONG WarningType[20];
	TCHAR WarningEvent[20][60];

	//************************* �������� ***************************
	BOOL IsMeasuring;								//���ڲ�����ʶ
	BOOL IsValid;									//���������ʶ
	LONG AppendWave;								//���Ӳ���
	LONG PointCount;								//�������ߵĵ�������SteelCurveһ�£�
	LONG WavePointCount;							//�����沨�εĵ���
	float WaveWidth[WAVE_CONTROL_POINTS];			//�������Ȳ���
	float WaveCenterDiff[WAVE_CONTROL_POINTS];		//������������ƫ���

	LONG WidthRange;								//���ƫ�Χ
	LONG CenterRange;								//������ƫ�Χ
	LONG WidthUpperLimit;							//����Ͽز�
	LONG WidthLowerLimit;							//����¿ز�
	LONG WaveXBegin;								//���κ��������
	LONG WaveXEnd;									//���κ������յ�
};	
