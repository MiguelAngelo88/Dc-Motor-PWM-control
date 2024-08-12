#include <Modbus.h>
#include <ModbusSerial.h>

// Define as variáveis utilizadas
#define pinovelocidade 11
#define pinoInput1 12
#define pinoInput2 8
#define potenciometro A0

// Modbus Registers Offsets
#define VEL 0

int pot = 0;
int velocidade = 0;

// ModbusSerial object
ModbusSerial mb;

void setup() {

  // Config Modbus Serial (port, speed, byte format) 
  mb.config(&Serial, 9600, SERIAL_8N1);
  // Set the Slave ID (1-247)
  mb.setSlaveId(2);  
    
  // Define os pinos 
  pinMode(pinovelocidade, OUTPUT);  
  pinMode(pinoInput1, OUTPUT);  
  pinMode(pinoInput2, OUTPUT); 
  pinMode(potenciometro, INPUT); 

  Serial.begin(9600);

  // Holding register
  mb.addHreg(VEL);
}

void loop() {
   // Call once inside loop() - all magic here
   mb.task();
   
  // Faz a leitura do Potenciômetro 
  pot = analogRead(potenciometro);
  velocidade = map(pot, 0,1023,0,255);
  Serial.println(velocidade);

  // Define a velocidade de rotacao do motor 
  analogWrite(pinovelocidade, velocidade);   

  // Aciona o motor  
  digitalWrite(pinoInput1, HIGH);  
  digitalWrite(pinoInput2, LOW); 
}