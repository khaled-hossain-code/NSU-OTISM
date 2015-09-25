
#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); // RX, TX



String number1 = "+8801675395563";
String text;
char inchar;
byte gsmDriverPin[3] = {
  6,3};//The default digital driver pins for the GSM and GPS mode
int gsm_en = 6;
int gps_en = 3;
int panic_button = 5;
int light = 13;
int bluetooth_state = 11;
int sms_count = 0;
int signalF = 2;
int signalD = 12;
char bt_armed = 'N';
String smsBody;
// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {

  // initialize serial communication
  // (it is required for Teapot Demo output, but it's
  // really up to you depending on your project)
  pinMode(panic_button,INPUT);
  //Init the driver pins for GSM function
  for(int i = 0 ; i < 3; i++){
    pinMode(gsmDriverPin[i],OUTPUT);
  }
  digitalWrite(gsm_en,LOW);//Enable the GSM mode
  digitalWrite(gps_en,HIGH);//Disable the GPS mode
  delay(2000);
  Serial.begin(115200); //set the baud rate
  delay(200);
  mySerial.begin(9600);
  delay(200);
  Serial.print("AT+CMGF=1\r");  // set SMS mode to text
  delay(100);
  Serial.print("AT+CNMI=2,2,0,0,0\r"); 
  // blurt out contents of new SMS upon receipt to the GSM shield's serial out
  delay(100);
  Serial.println("AT+CLIP=1");
  delay(100);
  
  //************GPS Enable*************// 
  delay(500);//call ready
  Serial.println("System Ready");
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
  
  if (digitalRead(panic_button) == 0 && sms_count <= 2 )
  {
    Serial.println("Got panic button pressed");
    send_sms();// panic button pressed
    delay(1000);
    sendGpsLocation();
    //send sms
  }

  if(digitalRead(bluetooth_state) == 0 && sms_count <= 2 && bt_armed == 'E')
  {
    Serial.println("For Bluetooth Disconnected ");
    send_sms1(); // bluetooth is disconnected
    //if bluetooth is disconnected generate SMS
    sendGpsLocation();
  }

  while (mySerial.available())
  {
    bt_armed= mySerial.read();
  }

  if ( digitalRead(signalF) && sms_count <= 2)
  {
    Serial.println("Paitient has fallen down");
    send_sms2();
    delay(1000);
    sendGpsLocation();
        
  }

  if(digitalRead(signalD) && sms_count <= 2)
  {
    Serial.println("Paitient is not in Wheel chair");
    send_sms4();
    delay(1000);
    sendGpsLocation();
    
  }

}

void send_sms()
{
  digitalWrite(gsm_en,LOW);//Enable the GSM mode
  digitalWrite(gps_en,HIGH);//Disable the GPS mode
  delay(2000);

  //Send message
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+8801675844371\"");//Change the receiver phone number
  delay(1000);
  Serial.print("Panic Button Pressed!!! Need Emergency Help!!!");//the message you want to send
  delay(1000);
  Serial.write(26);
  sms_count = sms_count + 1; 
}

void send_sms1()
{
  digitalWrite(gsm_en,LOW);//Enable the GSM mode
  digitalWrite(gps_en,HIGH);//Disable the GPS mode
  delay(2000);

  //Send message
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+8801675844371\"");//Change the receiver phone number
  delay(1000);
  Serial.print("Paitient is Unattendent!!!!");//the message you want to send
  delay(1000);
  Serial.write(26);
  sms_count = sms_count + 1; 
}

void send_sms2()
{
  digitalWrite(gsm_en,LOW);//Enable the GSM mode
  digitalWrite(gps_en,HIGH);//Disable the GPS mode
  delay(2000);

  //Send message
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+8801675844371\"");//Change the receiver phone number
  delay(1000);
  Serial.print("Paintent is in Danger!!!Fall Down From chair!!!");//the message you want to send
  delay(1000);
  Serial.write(26);
  sms_count = sms_count + 1; 
}


void send_sms3()
{
  digitalWrite(gsm_en,LOW);//Enable the GSM mode
  digitalWrite(gps_en,HIGH);//Disable the GPS mode
  delay(2000);

  //Send message
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+8801675844371\"");//Change the receiver phone number
  delay(1000);
  Serial.print("Paintent is in Danger At Home!!!");//the message you want to send
  delay(1000);
  Serial.write(26);
  sms_count = sms_count + 1; 
}

void send_sms4()
{
  digitalWrite(gsm_en,LOW);//Enable the GSM mode
  digitalWrite(gps_en,HIGH);//Disable the GPS mode
  delay(2000);

  //Send message
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+8801675844371\"");//Change the receiver phone number
  delay(1000);
  Serial.print("Paintent is not in Chair!!!");//the message you want to send
  delay(1000);
  Serial.write(26);
  sms_count = sms_count + 1; 
}


void sendGpsLocation()
{
  float lat,lon;
  char latDir, lonDir;
  long counter = 0L;
  //Link:  "http://maps.google.com/maps?q=N23.829637527,E90.415573120"
  //turn on GPS power supply
  Serial.println("AT+CGPSPWR=1");
  delay(1000);
  //reset GPS in autonomy mode
  Serial.println("AT+CGPSRST=1");
  delay(1000);

  digitalWrite(gps_en,LOW);//Enable GPS mode
  digitalWrite(gsm_en,HIGH);//Disable GSM mode
  delay(2000);

  while(1)
  {
    if(lat_dir()== 'N' && lon_dir()=='E' && latitude() >= 0 && longitude() >= 0 )  
      //gps cordination formatted
    {
      lat = latitude();
      lon = longitude();
      latDir = lat_dir();
      lonDir = lon_dir();

      digitalWrite(gsm_en,LOW);//Enable the GSM mode
      digitalWrite(gps_en,HIGH);//Disable the GPS mode
      delay(2000);

      //Send message
      Serial.println("AT+CMGF=1");
      delay(1000);
      Serial.println("AT+CMGS=\"+8801675844371\"");//Change the receiver phone number
      delay(1000);
      Serial.print("http://maps.google.com/maps?q=");
      Serial.write(latDir);
      Serial.print(lat,7);
      Serial.write(',');
      Serial.write(lonDir);
      Serial.println(lon,7);
      Serial.write(26);
      sms_count = sms_count + 1; 
      return;
    }
    else
    {
      Serial.println("No Gps Data...");
      delay(1);
      //counter = counter + 1;

      //    if(counter > 30000)
      //    {
      //      send_sms3();
      //    }
      //    Serial.write(lat_dir());
      //    Serial.print(latitude(),7);
      //    Serial.write(',');
      //    Serial.write(lon_dir());
      //    Serial.println(longitude(),7);

    }
  }
}

double Datatransfer(char *data_buf,char num)//convert the data to the float type
{                                           //*data_buf£ºthe data array                                       
  double temp=0.0;                           //the number of the right of a decimal point
  unsigned char i,j;
  int degree;
  double minute;

  if(data_buf[0]=='-')
  {
    i=1;
    //process the data array
    while(data_buf[i]!='.')
      temp=temp*10+(data_buf[i++]-0x30);
    for(j=0;j<num;j++)
      temp=temp*10+(data_buf[++i]-0x30);
    //convert the int type to the float type
    for(j=0;j<num;j++)
      temp=temp/10;
    //convert to the negative numbe
    temp=0-temp;
  }
  else//for the positive number
  {
    i=0;
    while(data_buf[i]!='.')
      temp=temp*10+(data_buf[i++]-0x30);
    for(j=0;j<num;j++)
      temp=temp*10+(data_buf[++i]-0x30);
    for(j=0;j<num;j++)
      temp=temp/10 ;
  }
  degree = temp /100;
  minute = temp - (degree * 100);
  temp = degree + minute / 60.0;

  return temp;
}

char ID()//Match the ID commands
{ 
  char i=0;
  char value[6]={
    '$','G','P','G','G','A'        };//match the gps protocol
  char val[6]={
    '0','0','0','0','0','0'        };

  while(1)
  {
    if(Serial.available())
    {
      val[i] = Serial.read();//get the data from the serial interface
      if(val[i]==value[i]) //Match the protocol
      {    
        i++;
        if(i==6)
        {
          i=0;
          return 1;//break out after get the command
        }
      }
      else
        i=0;
    }
  } 
}

void comma(char num)//get ','
{   
  char val;
  char count=0;//count the number of ','

  while(1)
  {
    if(Serial.available())
    {
      val = Serial.read();
      if(val==',')
        count++;
    }
    if(count==num)//if the command is right, run return
      return;
  } 
}

float latitude()//get latitude
{
  char i;
  float latitude;
  char lat[10]={
    '0','0','0','0','0','0','0','0','0','0'
  };


  if( ID())
  {
    comma(2);
    while(1)
    {
      if(Serial.available())
      {
        lat[i] = Serial.read();
        i++;
      }
      if(i==10)
      {
        i=0;
        latitude = Datatransfer(lat,5);
        //Serial.println(latitude,7);//print latitude 
        return latitude;
      }  
    }
  }
}
char lat_dir()//get dimensions
{
  char i=0,val;

  if( ID())
  {
    comma(3);
    while(1)
    {
      if(Serial.available())
      {
        val = Serial.read();
        //Serial.write(val);
        //Serial.println();
        i++;
      }
      if(i==1)
      {
        i=0;
        return val;
      }  
    }
  }
}
float longitude()//get longitude
{
  char i;
  float longitude;
  char lon[11]={
    '0','0','0','0','0','0','0','0','0','0','0'
  };

  if( ID())
  {
    comma(4);
    while(1)
    {
      if(Serial.available())
      {
        lon[i] = Serial.read();
        i++;
      }
      if(i==11)
      {
        i=0;
        longitude = Datatransfer(lon,5);
        //Serial.println(longitude,7);
        return longitude;
      }  
    }
  }
}
char lon_dir()//get direction data
{
  char i=0,val;

  if( ID())
  {
    comma(5);
    while(1)
    {
      if(Serial.available())
      {
        val = Serial.read();
        //Serial.write(val); //Serial.println(val,BYTE);
        //Serial.println();
        i++;
      }
      if(i==1)
      {
        i=0;
        return val;
      }  
    }
  }
}




