#include "TetrisGame.h"
#include "windows.h"
#include <stdlib.h>
#include "winbase.h"

CTetrisGame::CTetrisGame(void)
: m_Together(0)
{
	InitGame();
}

CTetrisGame::~CTetrisGame(void)
{
}

void CTetrisGame::InitGame(void){
	DynBoard.cX = 0;
	DynBoard.cY = 0;
	for (int x = 0;x<4;x++)
	{
		for (int y = 0;y<4;y++)
		{
			DynBoard.Board[x][y] = false;
			GenBoard.Board[x][y] = false;
		}
	}//Tạo mảng động và mảng next tất cả bằng 0
	GenBoard.cX = GenBoard.cY = 0;
	GenNext();
	DynBoard = GenBoard;
	Sleep(10);
	GenNext();
	for (int x = 0;x < 10;x++)
	{
		for (int y = 0;y<22;y++)
		{
			m_Board[x][y] = false;
		}
	}//Khởi tạo mảng chính tất cả bằng 0
	m_Difficulty = 1;//Độ khó 1
	m_isPause = true; //Chưa chạy cho đến khi bấm F2
	m_Score = 0;
}

void CTetrisGame::SetDifficulty(int i)
{
	m_Difficulty = i;
}

int CTetrisGame::GetDifficulty(void)
{
	return m_Difficulty;
}
int CTetrisGame::AddScore()
{
	switch (m_Together)
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 4;
	case 3:
		return 8;
	case 4:
		return 15;
	}//Trả về số điểm theo hệ số
	return 0;
}
int CTetrisGame::ArrToInt(bool arr[4][4])
{
	int a = 15;
	int ReturnValue = 0;
	for (int y = 0;y<4;y++)
	{
		for (int x = 0;x<4;x++)
		{
			if (arr[x][y])
			{
				ReturnValue+=LuyThua2(a);
			}
			a--;
		}
	}
	return ReturnValue;
}
// Tính 2 mũ i
int CTetrisGame::LuyThua2(int i)
{
	if (i == 0)
	{
		return 1;
	}
	if (i == 1)
	{
		return 2;
	}
	return 2*LuyThua2(i-1);
}
bool CTetrisGame::CheckLose()
{
	for (int i = 0;i<10;i++)
	{
		if (m_Board[i][3])
		{
			return true;
		}
	}
	return false;
}
void CTetrisGame::CheckRow()
{
	int a = 0;
	for (int i = 21;i>3;i--)
	{
		for (int x = 0;x<10;x++)
		{
			if (m_Board[x][i])
			{
				a++;
			}
		}
		if (a == 10)
		{
			m_Together++;
			MoveRow(i);
			CheckRow();
		}
		else
		{
			a = 0;
		}
	}
	m_Score +=AddScore();
	m_Together = 0;
}
bool CTetrisGame::Drop()
{
	for (int y = 0;y<4;y++)
	{
		for (int x = 0;x<4;x++)
		{
			if (DynBoard.Board[x][y] && (m_Board[DynBoard.cX+x][DynBoard.cY+y+1]||DynBoard.cY+y>20))
			{
				for (int yy = 0;yy<4;yy++)
				{
					for (int xx = 0;xx<4;xx++)
					{
						if (DynBoard.Board[xx][yy])
						{
							m_Board[xx+DynBoard.cX][yy+DynBoard.cY] = true;
						}
					}
				}// Biến khối gạch thành hiện thực
				DynBoard = GenBoard;
				GenNext();
				return false;//Trả về giá trị false
			}
		}
	}
	DynBoard.cY++;
	return true;
}
void CTetrisGame::GenNext(){
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	srand (time.QuadPart);
	int i=rand()%7;
	switch (i)
	{
	case 0:
		IntToArr(GenBoard.Board,17476);//Que dọc
		break;
	case 1:
		IntToArr(GenBoard.Board,2188);//L xuôi
		break;
	case 2:
		IntToArr(GenBoard.Board,1100);//L ngược
		break;
	case 3:
		IntToArr(GenBoard.Board,612);//S xuôi
		break;
	case 4:
		IntToArr(GenBoard.Board,1122);//S ngược
		break;
	case 5:
		IntToArr(GenBoard.Board,78);//T nằm ngửa
		break;
	case 6:
		IntToArr(GenBoard.Board,204);//Vuông
		break;
	}
	GenBoard.cX = 3;GenBoard.cY = 0;
}
int CTetrisGame::GetBoardCell(int x,int y)
{
	if (m_Board[x][y])
	{
		return 1;
	}
	if ((DynBoard.cX-1<x)&&(DynBoard.cX+4>x)&&(DynBoard.cY-1<y)&&(DynBoard.cY+4>y))
	{
		if (DynBoard.Board[x-DynBoard.cX][y-DynBoard.cY])
		{
			return -1;
		}
	}
	return 0;
}
bool CTetrisGame::GetNext(int x,int y)
{
	return GenBoard.Board[x][y];
}
void CTetrisGame::IntToArr(bool arr[4][4],int i)
{
	for (int y = 3;y>=0;y--)
	{
		for (int x = 3;x>=0;x--)
		{
			if (i%2 == 1)
			{
				arr[x][y] = true;
			}
			else
			{
				arr[x][y] = false;
			}
			i/=2;
		}
	}
}
bool CTetrisGame::MoveDown()
{
	if (m_isPause)
	{
		return false;
	}
	do 
	{
	} while (Drop());
	CheckRow();
	return CheckLose();
}
void CTetrisGame::MoveLeft()
{
	if (m_isPause)
	{
		return;
	}
	for (int y = 0;y<4;y++)
	{
		for(int x = 0;x<4;x++)
		{
			if (DynBoard.Board[x][y] && m_Board[x+DynBoard.cX-1][y+DynBoard.cY])
			{
				return;
			}
			if (DynBoard.Board[x][y] && (DynBoard.cX+x<1))
			{
				return;
			}
		}
	}
	DynBoard.cX--;
}
void CTetrisGame::MoveRight()
{
	if (m_isPause)
	{
		return;
	}
	for (int y = 0;y<4;y++)
	{
		for (int x = 0;x<4;x++)
		{
			if (DynBoard.Board[x][y] && m_Board[x+DynBoard.cX+1][y+DynBoard.cY])
			{
				return;
			}
			if (DynBoard.Board[x][y] && (DynBoard.cX+x>8))
			{
				return;
			}
		}
	}
	DynBoard.cX++;
}
void CTetrisGame::MoveRow(int Row)
{
	for (int i = Row;i>0;i--)
	{
		for (int x = 0;x<10;x++)
		{
			m_Board[x][i] = m_Board[x][i-1];
		}
	}
	for (int x =0;x<10;x++)
	{
		m_Board[x][0] = false;
	}
}
void CTetrisGame::Rotate()
{
	DynamicBoard FutureBoard;
	FutureBoard = DynBoard;
	switch (ArrToInt(DynBoard.Board))
	{
	case 17476:
		IntToArr(FutureBoard.Board,3840);
		break;
	case 3840:
		IntToArr(FutureBoard.Board,17476);
		break;
	case 2188:
		IntToArr(FutureBoard.Board,232);
		break;
	case 232:
		IntToArr(FutureBoard.Board,3140);
		break;
	case 3140:
		IntToArr(FutureBoard.Board,46);
		break;
	case 46:
		IntToArr(FutureBoard.Board,2188);
		break;
	case 612:
		IntToArr(FutureBoard.Board,1584);
		break;
	case 1584:
		IntToArr(FutureBoard.Board,612);
		break;
	case 1122:
		IntToArr(FutureBoard.Board,864);
		break;
	case 864:
		IntToArr(FutureBoard.Board,1122);
		break;
	case 78:
		IntToArr(FutureBoard.Board,2248);
		break;
	case 2248:
		IntToArr(FutureBoard.Board,3648);
		break;
	case 3648:
		IntToArr(FutureBoard.Board,1220);
		break;
	case 1220:
		IntToArr(FutureBoard.Board,78);
		break;
	case 1100:
		IntToArr(FutureBoard.Board,142);
		break;
	case 142:
		IntToArr(FutureBoard.Board,3208);
		break;
	case 3208:
		IntToArr(FutureBoard.Board,226);
		break;
	case 226:
		IntToArr(FutureBoard.Board,1100);
		break;
	case 204:
		return;
	}
	for (int y = 0;y<4;y++)
	{
		for (int x = 0;x<4;x++)
		{
			if (FutureBoard.Board[x][y] && (x+FutureBoard.cX>9 ||  y+FutureBoard.cY>21))
			{
				return;
			}
			if (FutureBoard.Board[x][y]&&(x+FutureBoard.cX<0))
			{
				return;
			}
			if (FutureBoard.Board[x][y] && m_Board[x+FutureBoard.cX][y+FutureBoard.cY])
			{
				return;
			}
		}
	}
	DynBoard = FutureBoard;
}
bool CTetrisGame::UpdateGame()
{
	if (m_isPause)
	{
		return false;
	}
	if (!Drop())
	{
		CheckRow();
		return CheckLose();
	}
	return false;
}
void CTetrisGame::PauseGame(void)
{
	m_isPause = true;
}

void CTetrisGame::ResumeGame(void)
{
	m_isPause = false;
}

int CTetrisGame::GetScore(void)
{
	return m_Score;
}
