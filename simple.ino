#include <SimpleModbusSlave.h>

// Define as variáveis utilizadas
#define pinovelocidade 3
#define pinoPonteH1 2
#define pinoPonteH2 7

//////////////// registers of your slave ///////////////////
enum 
{     
  VELOCIDADE_VAL,     
  HOLDING_REGS_SIZE // leave this one
  // total number of registers for function 3 and 16 share the same register array
  // i.e. the same address space
};

unsigned int holdingRegs[HOLDING_REGS_SIZE]; // function 3 and 16 register array
////////////////////////////////////////////////////////////

void setup()
{

  modbus_configure(&Serial, 115200, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs);

  // modbus_update_comms(baud, byteFormat, id) is not needed but allows for easy update of the
  // port variables and slave id dynamically in any function.
  modbus_update_comms(115200, SERIAL_8N1, 1);
  
  // Define os pinos como saida  
    pinMode(pinovelocidade, OUTPUT);  
    pinMode(pinoPonteH1, OUTPUT);  
    pinMode(pinoPonteH2, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
  // modbus_update() is the only method used in loop(). It returns the total error
  // count since the slave started. You don't have to use it but it's useful
  // for fault finding by the modbus master.
  
  modbus_update();

  int velocidade = constrain(holdingRegs[VELOCIDADE_VAL], 0, 255);
  Serial.println(velocidade);
  analogWrite(pinovelocidade, velocidade);   

  // Aciona o motor  
  digitalWrite(pinoPonteH1, LOW);  
  digitalWrite(pinoPonteH2, HIGH); 
  delay(10);
}

