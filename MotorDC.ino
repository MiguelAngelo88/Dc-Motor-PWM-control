// Define as variáveis utilizadas
#define pinovelocidade 11
#define pinoInput1 12
#define pinoInput2 8
#define potenciometro A0

int pot;
int velocidade;
   
void setup()  
{  
  // Define os pinos como saida  
  pinMode(pinovelocidade, OUTPUT);  
  pinMode(pinoInput1, OUTPUT);  
  pinMode(pinoInput2, OUTPUT); 

  // Define o pino do potenciômetro como entrada
  pinMode(potenciometro, INPUT); 
  Serial.begin(9600);
}  
   
void loop(){  
  
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