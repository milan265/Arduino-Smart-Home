#define SensorTempPin A0
#define ResistorPin A1
const int SwitchPinNo = 12;
const int RelayPinNo = 13;

String poruka;
String zaSlanje;

unsigned long pocetno;
unsigned long trenutno;
unsigned long vreme;
unsigned long interval = 1000; // na 1000ms Arduino1 salje podatke Arduinu2

int temp;
int osvetljenje;
  
  
void setup()
{
  Serial.begin(9600);
  pinMode(SwitchPinNo,OUTPUT);
  pinMode(RelayPinNo,OUTPUT);
  digitalWrite(SwitchPinNo,HIGH);
  digitalWrite(RelayPinNo,LOW);
  pocetno = millis();
}

void procitajPoruku(){
  poruka = Serial.readString();
  if(poruka=="m\r\n"){
    digitalWrite(SwitchPinNo,HIGH);
  	digitalWrite(RelayPinNo,LOW);
  }else{
   	digitalWrite(SwitchPinNo,LOW);
   	if(poruka=="upali\r\n"){
   	  digitalWrite(RelayPinNo,HIGH);
    }else if(poruka=="ugasi\r\n"){
       digitalWrite(RelayPinNo,LOW);
    }
  }
}
void ocitajIPosalji(){
  temp = analogRead(SensorTempPin);
  temp = (temp*0.00488-0.5)*100;
  osvetljenje = analogRead(ResistorPin);
  zaSlanje = String(temp)+" "+String(osvetljenje)+"k";
  Serial.print(zaSlanje);
  zaSlanje = "";
}

void loop()
{
  if(Serial.available()>0){
  	procitajPoruku();
  }
  trenutno = millis();
  if((trenutno-pocetno)>interval){
  	pocetno = trenutno;
    ocitajIPosalji();
  }
}