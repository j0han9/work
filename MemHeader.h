
#pragma once

//***************************************************************************************
//****************************** 以下为共享内存的数据内容 *******************************
//***************************************************************************************


#define WAVE_CONTROL_POINTS		1000L		//波形控件点数

#define MEMORY_RAWDATA_SIZE		4000L		//原始数据缓冲区大小
#define MEMORY_WIDTHDATA_SIZE	200L		//宽度计算临时缓冲区大小
#define MEMORY_STEELCURVE_SIZE	6000L		//带钢曲线缓冲区大小
#define MEMORY_WARNING_SIZE		100L		//告警信息缓冲区大小

#define WIDTH_FREQUENCY			50L			//宽度计算频率，一般定为 50Hz


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
	StructModifyPix modify;//修正参数
	double C1x;					//C1(x,y)
	double C1y;
	double C2x;					//C2(x,y)
	double C2y;
	double P1[3];
	double P2[3];
	double s_midY;//最终拟合的坐标原点
	double s_midCCD[2];//最终拟合的原点对应的像素
	double s_LowOffset[MAX_EDGE_NUM];
	double s_HighOffset[MAX_EDGE_NUM];

	double dis12_34;
};

struct StructRawData
{
	BYTE CCD11[5000];	//CCD1的原始灰度数据
	BYTE CCD12[5000];	//CCD2的原始灰度数据
	BYTE CCD21[5000];	//CCD3的原始灰度数据
	BYTE CCD22[5000];	//CCD4的原始灰度数据
	float Speed;		//无意义，只为和旧的波形数据统一。
};


struct StructRawDataSpace
{
	StructRawData RData[MEMORY_RAWDATA_SIZE];	//原始数据FIFO
	LONG WriteIndex;							//当前写索引
};

struct StructWidthData
{
	LONG RawIndex;				//宽度数据对应的原始数据Index
	float Speed;				//带钢瞬时速度

	BOOL HaveSteel;				//两个通道均有钢（满足计算条件，但也可能宽度计算不正确）
	LONG CCD1Edge[2];			//CCD1边沿值
	LONG CCD2Edge[2];			//CCD2边沿值
	float x1,y1;				//钢板左边沿实际坐标
	float x2,y2;				//钢板右边沿实际坐标
	float Angle;				//钢板倾斜角度
	float RealWidth;			//单次宽度值
	float RealCenter;			//单次中心线值

	BOOL IsWidthValid;			//宽度有效（宽度计算是正确的）
	float AvgWidth;				//均值滤波宽度
	float AvgCenter;			//均值滤波中心线
};

struct StructWidthDataSpace
{
	StructWidthData WData[MEMORY_WIDTHDATA_SIZE];	//宽度值FIFO
	LONG WriteIndex;								//宽度值写索引
};

struct StructWarningItem
{
	__time64_t Time;			//告警发生时间
	LONG Type;					//告警类别 0信息 1警告 2严重错误
	TCHAR Info[60];				//告警信息
};

struct StructWarningItemSpace
{
	StructWarningItem WarnData[MEMORY_WARNING_SIZE];	//告警FIFO
	LONG WriteIndex;									//告警写索引
};

struct StructSteelInfoSpace
{
	//二级传递部分
	TCHAR CoilID[32];			//带钢编号
	TCHAR Material[16];			//钢种材料
	float ProductWidth;			//成品宽度（仅用于信息显示）
	float ProductThickness;		//成品厚度

	//一级传递部分
	float StdWidth;				//道次宽度（目标宽度）
	LONG CurrentPass;			//当前道次
	LONG TotalPass;				//总道次
	float Speed;				//速度
	LONG Temperature;			//温度

	//自带部分
	TCHAR BatchCode[16];	    //带钢批号
	TCHAR Ban[4];				//班号（已废弃）
	float StdCenter;			//辊道中心线位置
	float ColdRatio;			//冷缩系数
};

struct StructOtherInfoSpace
{
	BOOL DeviceHealthy;			//测宽仪设备健康信号（输出）
	LONG DeviceTemperature;		//检测箱温度，范围-50至100度，1至5V（输入）
	LONG TodayCoilCount;		//当日根数统计

	//-----------注意：曝光控制是分开进行的--------------
	UINT LightThreshold;		//光强门限，用于和光强均值做比较的值。
	LONG AutoIntegrationCCD11;	//自动积分增益控制CCD11
	LONG AutoIntegrationCCD12;	//自动积分增益控制CCD12
	LONG AutoIntegrationCCD21;	//自动积分增益控制CCD21
	LONG AutoIntegrationCCD22;	//自动积分增益控制CCD22
	UINT AvgGrayCCD11;			//CCD11平均灰度
	UINT AvgGrayCCD12;			//CCD12平均灰度
	UINT AvgGrayCCD21;			//CCD21平均灰度
	UINT AvgGrayCCD22;			//CCD22平均灰度

	//---------------------宽度修正---------------------
	BOOL UseCorrection;			//使用分段修正功能。
	LONG CorrectionCount;		//修正点数量
	float MeasuredWidth[10];	//测量出的宽度（最多存10个点）
	float RealWidth[10];		//实际宽度

	//---------------------冷轧换卷信号---------------------
	BOOL NoneCoilSign;			//当该变量为真时，强制写入无钢波形，模拟换卷。


	//---------------------含碳量信息（用于计算冷态宽度）---------------------
	LONG MatCount;				//含碳量表的实际大小
	TCHAR MatArray[40][16];		//表中的钢种名称
	float Carben[40];			//钢种对应的含碳量

};

struct StructSystemParamSpace
{
	LONG CCDPixel;				//相机像素
	UINT AvgFilterWindow;		//均值滤波窗大小
	LONG CutHeadPoints;			//去除头部点数
	LONG CutTailPoints;			//去除尾部点数
	BOOL UseBackgroundLamp;		//使用背景光测量模式
	BOOL UseAutoIntegration;	//使用自动曝光控制
	BOOL RecordWave;			//录制原始波形
};

/**************************************************************************************

	重要：

	IsMeasuring、IsValid 是专门用于显示进程的。
	m_CoilInView、HaveSteel、IsWidthValid 是专用于计算进程的。
	
	这样设计的目的，就是为了把计算和显示完全分开。（计算和显示的数据分别在不同的区域）
	尽管两套变量的意义非常相近。

	另外，由于“去头去尾”功能的加入，显示的数据总是比计算的数据滞后，所以
	IsMeasuring 要比 m_CoilInView 滞后，但是 IsValid 和 IsWidthValid 意义相同。

**************************************************************************************/

struct StructSteelCurveSpace
{
	__time64_t CoilArriveTime;						//带钢到达时间
	float DisplayWidth;								//当前宽度（过钢结束时显示均值）
	float DisplayWidthDev;							//当前宽度偏差
	float DisplayCenter;							//当前带钢中点位置
	float DisplayCenterDev;							//当前带钢中点偏差
	float MaxWidth;									//宽度最大值
	float MinWidth;									//宽度最小值
	float AvgWidth;									//宽度最终平均值
	StructSteelInfoSpace ThisCoilInfo;				//本带钢信息（仅在钢头时被复制一次，以免过钢时SteelInfo变化）

	BOOL  IsMeasuring;								//正在过钢、测量中。。（类似CoilInView信号）
	BOOL  IsValid;									//数据有效（有数据、且数据正确）
	LONG  PointCount;								//带钢曲线的点数
	float Width[MEMORY_STEELCURVE_SIZE];			//带钢宽度曲线
	float CenterDiff[MEMORY_STEELCURVE_SIZE];		//带钢中心线偏差曲线
	float Length[MEMORY_STEELCURVE_SIZE];			//带钢长度曲线
	BOOL  DataValid[MEMORY_STEELCURVE_SIZE];		//带钢数据有效（重要：有效或无效的瞬时状态，从这里取得）
};

struct StructMem
{
	StructRawDataSpace rd;		//原始数据区域
	StructWidthDataSpace wd;	//宽度数据区域
	StructWarningItemSpace wi;	//告警信息区域
	StructSteelInfoSpace si;	//标准带钢信息区域
	StructOtherInfoSpace oi;	//其它信息区域
	StructSystemParamSpace sp;	//系统参数信息区域
	StructSteelCurveSpace sc;	//带钢曲线区域
};





//*********************************************************************************
//****************************** 以下为各进程结构体 *******************************
//*********************************************************************************


typedef StructSteelCurveSpace StructHistoryData;


//struct StructCalcParam
//{
//	float CCD1Table[2][5000];		//CCD1像素所对应数据
//	float CCD2Table[2][5000];		//CCD2像素所对应数据
//	float C1x[2];					//C1(x,y)
//	float C1y[2];
//	float C2x[2];					//C2(x,y)
//	float C2y[2];
//	float dis12_34;//CCD12与34的距离
//};

struct StructHMI_1
{
	//************************* 带钢信息 ***************************
	__time64_t CoilArriveTime;						//带钢到达时间
	StructSteelInfoSpace ThisCoilInfo;				//本带钢信息

	//************************* 宽度数码管 *************************
	float DisplayWidth;								//宽度（过钢结束时显示均值）
	float DisplayWidthDev;							//宽度偏差
	float MaxWidth;									//宽度最大值
	float MinWidth;									//宽度最小值
	float AvgWidth;									//平均宽度

	//************************* 告警数据 ***************************
	TCHAR WarningTime[20][16];
	LONG WarningType[20];
	TCHAR WarningEvent[20][60];

	//************************* 波形数据 ***************************
	BOOL IsMeasuring;								//正在测量标识
	BOOL IsValid;									//宽度正常标识
	LONG AppendWave;								//附加波形
	LONG PointCount;								//带钢曲线的点数（与SteelCurve一致）
	LONG WavePointCount;							//主界面波形的点数
	float WaveWidth[WAVE_CONTROL_POINTS];			//主界面宽度波形
	float WaveCenterDiff[WAVE_CONTROL_POINTS];		//主界面中心线偏差波形

	LONG WidthRange;								//宽度偏差范围
	LONG CenterRange;								//中心线偏差范围
	LONG WidthUpperLimit;							//宽度上控差
	LONG WidthLowerLimit;							//宽度下控差
	LONG WaveXBegin;								//波形横坐标起点
	LONG WaveXEnd;									//波形横坐标终点
};	
