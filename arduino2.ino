#include <LiquidCrystal.h>

const int DispHeight = 16;
const int DispWidth = 2;

const int RSPinNo = 12;
const int EnablePinNo = 11;
const int D4PinNo = 4;
const int D5PinNo = 5;
const int D6PinNo = 6;
const int D7PinNo = 7;

const int Button1PinNo = 3;
const int Button2PinNo = 2;

bool manuelanRezimRada = true;
bool diodaUpaljena = false; 

String poruka;

LiquidCrystal LCD(RSPinNo,EnablePinNo,D4PinNo,D5PinNo,D6PinNo,D7PinNo);

void promeniRezimRada(){
  manuelanRezimRada = !manuelanRezimRada;
  if(manuelanRezimRada){
  	diodaUpaljena = false;
    Serial.println("m");
    stampajNaLcdUDvaReda("Manuelan","rezim rada");
  }else{
  	Serial.println("a");
    stampajNaLcdUDvaReda("Automatski","rezim rada");
  }
}

void promeniStanjeDiode(){
  if(!manuelanRezimRada){
  	diodaUpaljena = !diodaUpaljena;
    if(diodaUpaljena){
    	Serial.println("upali");
      	stampajNaLcd("Dioda upaljena");
    }else{
    	Serial.println("ugasi");
      	stampajNaLcd("Dioda ugasena");
    }
  }else{
  	stampajNaLcdUDvaReda("Manuelan","rezim rada");
  }
}

void stampajNaLcd(String poruka){
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print(poruka);
}
void stampajNaLcdUDvaReda(String poruka1, String poruka2){
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print(poruka1);
  LCD.setCursor(0,1);
  LCD.print(poruka2);
}

void setup()
{
  Serial.begin(9600);
  LCD.begin(DispHeight,DispWidth);
  pinMode(Button1PinNo,INPUT);
  pinMode(Button2PinNo,INPUT);
  attachInterrupt(digitalPinToInterrupt(Button1PinNo), promeniRezimRada, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button2PinNo), promeniStanjeDiode, FALLING);
}

void procitajPoruku(){
  poruka = Serial.readString();
  String temp = "";
  String osvetljenje = "";
  int i = 0;
  while(poruka[i]!=' '){
    temp += poruka[i];
  	i++;
  }
  i++;
  while(poruka[i]!='k'){
  	osvetljenje += poruka[i];
    i++;
  }
  stampajNaLcdUDvaReda("Temp: "+temp+"C","Osv:  " + osvetljenje +"Lm"); 
}

void loop()
{
  if(Serial.available()>0){
  	procitajPoruku();
  }
}