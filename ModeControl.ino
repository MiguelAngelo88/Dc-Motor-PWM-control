#include <Modbus.h>
#include <ModbusSerial.h>

// Define as variáveis utilizadas
#define pinoVelocidade 11
#define pinoInput1 12
#define pinoInput2 8
#define potenciometro A0

// Modbus Registers Offsets
#define VEL 0
#define POT 1
#define MODE 2

int pot = 0;
int velocidade = 0;
int mode = 0; // 0: Potenciômetro, 1: Supervisório

// ModbusSerial object
ModbusSerial mb;

void setup() {
  // Config Modbus Serial (port, speed, byte format) 
  mb.config(&Serial, 9600, SERIAL_8N1);
  // Set the Slave ID (1-247)
  mb.setSlaveId(2);  
    
  // Define os pinos 
  pinMode(pinoVelocidade, OUTPUT);  
  pinMode(pinoInput1, OUTPUT);  
  pinMode(pinoInput2, OUTPUT); 
  pinMode(potenciometro, INPUT); 

  // Registers
  mb.addHreg(VEL);
  mb.addIreg(POT);
  mb.addHreg(MODE); // Registrador para o modo de controle
}

void loop() {
  // Call once inside loop() - all magic here
  mb.task();
  
  // Lê o modo de controle do ScadaBr
  mode = mb.Hreg(MODE);
  
  if (mode == 0) {
    // Modo potenciômetro
    pot = analogRead(potenciometro);
    velocidade = map(pot, 0, 1023, 0, 255);
  } else {
    // Modo supervisório
    velocidade = constrain(mb.Hreg(VEL), 0, 255);
  }
  
  // Define a velocidade de rotação do motor 
  analogWrite(pinoVelocidade, velocidade); 

  // Aciona o motor  
  digitalWrite(pinoInput1, HIGH);  
  digitalWrite(pinoInput2, LOW); 
}
