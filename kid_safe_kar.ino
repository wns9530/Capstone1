#include <SHT1x.h> //SH11 센서 관련 라이브러리 선언   
#include <Stepper.h>
#include<SoftwareSerial.h>
SoftwareSerial mySerial(A11, A10);


byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
byte response[9];
String ppmString = " ";
const int stepsPerRevolution = 900; //윈도우 모터 열리는 각도

int DataPin = 28;   //Data 핀 번호 변수에 정의  
int ClockPin = 29; //Clock 핀 번호 변수에 정의  

SHT1x sht1x(DataPin, ClockPin); //I2C 핀 설정  
float g_fTempC = 0; //온도 관련 변수 선언   

// 모터 드라이브에 연결된 핀 IN4, IN2, IN3, IN1
Stepper myStepper(stepsPerRevolution,17,16,15,14);             

void setup() {
  
  myStepper.setSpeed(14);
  
  Serial.begin(9600);
  Serial1.begin(38400);
  mySerial.begin(9600);
  Serial.println("TEMP/HUMI Sensor Reading Start");   
  pinMode(9, INPUT);
  

}
void loop() {
   mySerial.read();
   mySerial.write(cmd,9);
   mySerial.readBytes(response, 9);
   int i = 0;
   char someChar[9] = "dangerous";
   byte chck = 0;


   g_fTempC = sht1x.readTemperatureC() - 5; //온도 값 Read 후 변수에 저장   
  int ppm = (response[2] << 8)|response[3];

  Serial.print("PPM ");
  Serial.println(ppm);
   Serial.print("TEMP : "); //시리얼 모니터에 "TEMP" 메시지 표시   
  Serial.println(g_fTempC); //시리얼 모니터에 온도 값 표시 후 개행  
  

  if(g_fTempC>15 && ppm>300){
   myStepper.step(-stepsPerRevolution);
   Serial1.print(someChar);
   Serial.print("S:");
   Serial.print(someChar);
  }

  delay(500);
}
