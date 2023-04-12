#include "test.h"

using namespace J0han::test;

Test::Test()
{
  Init();
}

Test::~Test()
{
  
}

void Test::GetWriteBuffer(StructSteelCurveSpace* pSrc, BYTE*& pBuffer, int step = 1)
{
  m_pStep = step;
  m_pSrc = pSrc;
  m_pBuffer = nullptr;
  
}

