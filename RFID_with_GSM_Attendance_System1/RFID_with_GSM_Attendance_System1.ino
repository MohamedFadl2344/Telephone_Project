#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <DS3231.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial sim(8, 9);

String number = "+201285892570"; // +20 is the country code

int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state5 = 0;


#define buzzerPin  A1
#define RST_PIN    A0
#define SDA_PIN    10

MFRC522 mfrc522(SDA_PIN, RST_PIN);
DS3231  rtc(SDA, SCL);

void setup() {

  lcd.begin();
  // Turn on the blacklight
  lcd.backlight();
  Serial.begin(9600);
  sim.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  rtc.begin();

  pinMode(buzzerPin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("  WELCOME TO  ");
  lcd.setCursor(0, 1);
  lcd.print("The IoT Projects");
  delay(4000);
  lcd.clear();
}

void loop() {
  RTC();
  rfid();
}

void RTC()
{
  //rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(08, 50, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(10, 12, 2021);   // Set the date to January 1st, 2014

  lcd.setCursor(0, 0);
  lcd.print("Put Your Card to" );
  lcd.setCursor(0, 1);
  lcd.print("the Reader......");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(rtc.getTimeStr());
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(rtc.getDateStr());
  delay(2000);
  lcd.clear();
}

void rfid()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())  // التحقق من وجود بطاقة جديدة
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  // readCardUID();
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();   // تحويل UID إلى أحرف كبيرة

// التحقق من UID مقابل UIDs المعرفة مسبقًا وتنفيذ الإجراءات المناسبة
  if (content.substring(1) == "93 2C 6A FA" && state1 == 0) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Mohamed   ");
    lcd.setCursor(7, 1);
    lcd.print("000001");
    info();
    SendMohamed();
    state1 = 1;
  }
  else if (content.substring(1) == "93 2C 6A FA" && state1 == 1) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Mohamed    ");
    lcd.setCursor(7, 1);
    lcd.print("000001");
    info();
    SendMohamed();
    state1 = 0;
  }
  else if (content.substring(1) == "23 65 A5 2A" && state2 == 0) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Abdullah    ");
    lcd.setCursor(7, 1);
    lcd.print("000002");
    info();
    SendAbdullah();
    state2 = 1;
  }
  else if (content.substring(1) == "23 65 A5 2A" && state2 == 1) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Abdullah   ");
    lcd.setCursor(7, 1);
    lcd.print("000002");
    info();
    SendAbdullah();
    state2 = 0;
  }
  else if (content.substring(1) == "A1 6E B5 D4" && state3 == 0) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Ahmed   ");
    lcd.setCursor(7, 1);
    lcd.print("000003");
    info();
    SendAhmed();
    state3 = 1;
  }
  else if (content.substring(1) == "A1 6E B5 D4" && state3 == 1) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Ahmed    ");
    lcd.setCursor(7, 1);
    lcd.print("000003");
    info();
    SendAhmed();
    state3 = 0;
  }
  else if (content.substring(1) == "F1 72 62 D5" && state4 == 0) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Hazem  ");
    lcd.setCursor(7, 1);
    lcd.print("000004");
    info();
    SendHazem();
    state4 = 1;
  }
  else if (content.substring(1) == "F1 72 62 D5" && state4 == 1) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Hazem    ");
    lcd.setCursor(7, 1);
    lcd.print("000004");
    info();
    SendHazem();
    state4 = 0;
  }
  else if (content.substring(1) == "21 BD 21 D5" && state5 == 0) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Amr ");
    lcd.setCursor(7, 1);
    lcd.print("000005");
    info();
    SendAmr();
    state5 = 1;
  }
  else if (content.substring(1) == "21 BD 21 D5" && state5 == 1) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Amr  ");
    lcd.setCursor(7, 1);
    lcd.print("000005");
    info();
    SendAmr();
    state5 = 0;
  }
  else   {
    digitalWrite(buzzerPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ID : ");
    lcd.print("Unknown");
    lcd.setCursor(0, 1);
    lcd.print("Access denied");
    Serial.println(" Access denied");
    delay(1500);
    digitalWrite(buzzerPin, LOW);
    lcd.clear();
  }
}
// دوال لإرسال رسائل قصيرة للمستخدمين المختلفين
void smsSend()
{
  lcd.setCursor(0, 0);
  lcd.print("Sending SMS");
  for (int x = 11; x < 16; x++)
  {
    lcd.setCursor(x, 0);
    lcd.print(".");
    delay(1000);
  }

}
void beepON()
{
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
  delay(100);
}
void info()
{
  lcd.setCursor(0, 0);
  lcd.print("Name : ");
  lcd.setCursor(0, 1);
  lcd.print("ID   : ");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Authorized Access");
  delay(1000);
  lcd.clear();
}

void SendMohamed()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  if (state1 == 0) {
    const char Mohamed[] = "No: 000001 Mohamed Fadl has joined school at ";
    sim.print(Mohamed);
  }
  else if (state1 == 1) {
    const char Mohamed[] = "No: 000001 Mohamed Fadl has gone from school at ";
    sim.print(Mohamed);
  }
  sim.println(rtc.getTimeStr());
  delay(100);
  sim.println((char)26);
  smsSend();
}

void SendAbdullah()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  if (state2 == 0) {
    const char Abdullah[] = "No: 000002 Abdullah has joined school at ";
    sim.print(Abdullah);
  }
  else if (state2 == 1) {
    const char Abdullah[] = "No: 000002 Abdullah has gone from school at ";
    sim.print(Abdullah);
  }
  sim.println(rtc.getTimeStr());
  delay(100);
  sim.println((char)26);
  smsSend();
}
void SendAhmed()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  if (state3 == 0) {
    const char Ahmed[] = "No: 000003  Ahmed has joined school at ";
    sim.print(Ahmed);
  }
  else if (state3 == 1) {
    const char Ahmed[] = "No: 000003 Ahmed has gone from school at ";
    sim.print(Ahmed);
  }
  sim.println(rtc.getTimeStr());
  delay(100);
  sim.println((char)26);
  smsSend();
}
void SendHazem()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  if (state4 == 0) {
    const char Hazem[] = "No: 000004 Hazem has joined school at ";
    sim.print(Hazem);
  }
  else if (state4 == 1) {
    const char Hazem[] = "No: 000004 Hazem has gone form school at";
    sim.print(Hazem);
  }
  sim.println(rtc.getTimeStr());
  delay(100);
  sim.println((char)26);
  smsSend();
}
void SendAmr()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  if (state5 == 0) {
    const char Amr[] = "No: 000005 Amr has joined school at ";
    sim.print(Amr);
  }
  else if (state5 == 1) {
    const char Amr[] = "No: 000005 Amr has gone form school at ";
    sim.print(Amr);
  }
  sim.println(rtc.getTimeStr());
  delay(100);
  sim.println((char)26);
  smsSend();
}