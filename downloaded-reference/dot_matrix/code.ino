

int R[] = {2, 3, 4, 5, A3, A2, A1, A0}; //行
int C[] = {6, 7, 8, 9, 10, 11, 12, 13}; //列

/*协议定义*/
int incomingByte = 0;       // 接收到的 data byte
String inputString = "";         // 用来储存接收到的内容
boolean newLineReceived = false; // 前一次数据结束标志
boolean startBit  = false;  //协议开始标志

unsigned char biglove[8][8] =       //大“心型”的数据
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
};

unsigned char smalllove[8][8] =      //小“心型”的数据
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char DATA[8][8] =      //接收上位机数据显示
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};
void setup()
{
  //循环定义行列PIN 为输出模式
  Serial.begin(9600);//设置波特率为9600
  for (int i = 0; i < 8; i++)
  {
    pinMode(R[i], OUTPUT);
    pinMode(C[i], OUTPUT);
  }
  //初始化显示心
  for (int i = 0 ; i < 100 ; i++)       //循环显示100次
  {
    Display(biglove);                   //显示大”心形“
  }
  for (int i = 0 ; i < 50 ; i++)        //循环显示50次
  {
    Display(smalllove);                 //显示小“心形”
  }
}

void loop()
{
  for (int i = 0 ; i < 50 ; i++)        //循环显示50次
  {
    Display(DATA);                 //显示小“心形”
  }
  
}

void Display(unsigned char dat[8][8])   //显示函数
{
  for (int c = 0; c < 8; c++)
  {
    digitalWrite(C[c], LOW); //选通第c列

    //循环
    for (int r = 0; r < 8; r++)
    {
      digitalWrite(R[r], dat[r][c]);
    }
    //delay(1);
    Clear();  //清空显示去除余晖
  }
}

void Clear()                          //清空显示
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(R[i], LOW);
    digitalWrite(C[i], HIGH);
  }
}

/*串口协议解析数据*/
void Protocol(void)
{
  int num1 = 0, num2 = 0;
  while (newLineReceived)  //协议数据接收完毕一包
  {
    //判断是否是AR的协议
    if (inputString[1] != 'A' || inputString[2] != 'R')
    {
      inputString = "";   // clear the string
      newLineReceived = false;
      break;
    }
    //判断是否是风扇的协议数据
    if (inputString[4] != 'D' && inputString[5] != 'M' && inputString[6] != 'X')
    {
      inputString = "";   // clear the string
      newLineReceived = false;
      break;
    }

    if (inputString[10] == '0') //灭
    {
      num1 = inputString[7] - 0x30; //行位置
      num2 = inputString[8] - 0x30; //列位置
      DATA[num1][num2] = 0;

    }
    else if (inputString[10] == '1')	 //亮
    {
      num1 = inputString[7] - 0x30; //行位置
      num2 = inputString[8] - 0x30; //列位置
      DATA[num1][num2] = 1;
    }
    else if (inputString[10] == '2') //清屏
    {
      memset(DATA, 0x00, 64);
    }
    else if (inputString[10] == '3') //全亮
    {
      memset(DATA, 1, 64);
    }

    inputString = "";   // clear the string
    newLineReceived = false;
  }
}
//serialEvent()是IDE1.0及以后版本新增的功能，不清楚为什么大部份人不愿意用，这个可是相当于中断功能一样的啊!
void serialEvent()
{
  while (Serial.available())
  {
    incomingByte = Serial.read();              //一个字节一个字节地读，下一句是读到的放入字符串数组中组成一个完成的数据包
    if (incomingByte == '$')
    {
      startBit = true;
    }
    if (startBit == true)
    {
      inputString += (char) incomingByte;     // 全双工串口可以不用在下面加延时，半双工则要加的//
    }
    if (startBit == true && incomingByte == '#')
    {
      newLineReceived = true;
      startBit = false;
      Protocol();
    }
  }
}



