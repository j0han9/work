#include "MemHeader.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

namespace J0han{
  namespace test{
    class Test{
      public:
        Test();
        ~Test();

        void GetWriteBuffer(StructSteelCurveSpace* pSrc, BYTE*& pBuffer, int step = 1);

      private:
        string m_Path;
        int m_pStep;
        StructSteelCurveSpace* m_pSrc;
        BYTE* m_pBuffer;
    }
  }
};
