#ifndef BUFFERLAYER__RC__INC
#define BUFFERLAYER__RC__INC
#include <windows.h>
namespace RedContritio
{
	class BUFFERLAYER
	{
		private :
			HDC hBufferLayer ;
			HBITMAP hBitmap ;
			HBITMAP hPrevBitmap ;
			void DeleteAll(void );
			void BuildAll(HWND );
		public :
			BUFFERLAYER(void );
			BUFFERLAYER(HWND );
			HDC getHdc(void );
			void AdjustSize(HWND );
			void ResetBufferLayer(HWND );
			void DeleteBufferLayer(void );
			~BUFFERLAYER(void );
	};
}
#endif
