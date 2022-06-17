github網址:
Youtube網址:

檔案說明:
由於本次作業相當大，我分成了許多header檔與cpp檔去儲存class的資料。
因為是用visual studio跑的，我會把整個程式包含debug丟上來。

*由於題目的資訊不完整(沒有特別給每個instruction需要多少執行時間)，這邊假設+-*/的時間分別為2,2,4,8，
導致答案有點出入，但實作應該沒有問題才對。


每個檔案名稱存的class:
s1091509_proj_3_2.cpp 		==> main function
Computer.h 				==> class computer
Instruction.h 			==> class instruction, class registerTemp
RegisterAllocationTable.h 	==> class RegisterAllocation, class RegisterAllocationTable
ReservationStation.h		==> class station, class ReservationStation
ArithmetricLogicUnit.h		==> class ArithmetricLogicUnit


程式說明:
main function :
	呼叫了一個computer物件，在computer還未跑完時，會持續進到下一個cycle，並且顯示output。

class computer :
	存入的資料型態包含:	1、RF				==>存放register的值
					2、cycleTime 		==>確認執行到第幾個cycle
					3、decodeNumber		==>decode完幾個instructions
					4、instructions		==>將字串讀入，轉換成較好辨識的指令
					5、RAT			==>RegisterAllocationTable
					6、RS				==>兩個暫存器，我把它寫在同一個class裡
					7、ALU1, ALU2		==>執行運算的物件

	函式:	1、初始化		==>cin讀入，並把結果存到instructions裡
		2、check()		==>是否所有動作已執行完畢
		3、cycle()		==>decode instructions進到RS，呼叫ALU執行
		4、output()		==>輸出標準輸出

class instruction:
	記入type(+-*/)、r1,r2,r3，會幫忙做字串轉換int。

class registerTemp (RF):
	記住register的值，還有該值的順序，避免覆蓋錯誤。

class RegisterAllocation:
	RAT的其中一欄，紀錄自己對應到的RS與順序。

class RegisterAllocationTable:
	存入五個RegisterAllocation，並對整個表格做管理。

class station:
	RS中所存的其中一個資訊，本身會記錄是否已經獲取到所有應該獲得的值，如果沒有，會等待ALU做更新。
	
class ReservationStation:
	管理五個station，在程式方面，是把1~3與4~5的station合併一起放。會根據type或函式的不同，去選擇要怎麼時做。

class ArithmetricLogicUnit:
	ALU，幫忙做計算，計算完後會呼叫RF、RAT、RS，並幫這三者做更新。
