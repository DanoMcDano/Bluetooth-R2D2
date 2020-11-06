 #include <SoftwareSerial.h>

char a, b, c, d, e, f, g, h;

int V0=4,S0=14,S1=15,S2=16,S3=17;
int lg=2, lb=19, lr=18;

int enA=3;
int enB=11;

long distancia;
long tiempo; 

int izqA=5;
int izqB=6;
int derA=9;
int derB=10;

int x=0;

char dist;

int var=0;

char state = 0;

float VR,VB,VG;

void setup()
{   
   Serial.begin(9600);
   
   pinMode(S0,OUTPUT);
   pinMode(S1,OUTPUT);
   pinMode(S2,OUTPUT);
   pinMode(S3,OUTPUT);
   pinMode(V0,INPUT);
  
   pinMode(lg,OUTPUT);
   pinMode(lb,OUTPUT);
   pinMode(lr,OUTPUT);
  
   digitalWrite(lg,LOW);
   digitalWrite(lb,LOW);
   digitalWrite(lr,LOW);
  
   digitalWrite(S0,HIGH);
   digitalWrite(S1,HIGH);
   
   pinMode(derA, OUTPUT);
   pinMode(derB, OUTPUT);
   pinMode(izqA, OUTPUT);
   pinMode(izqB, OUTPUT);
   pinMode(enA, OUTPUT);
   pinMode(enB, OUTPUT);

   pinMode(7,OUTPUT);
   pinMode(8,INPUT);
}
 
void loop() 
{    
    digitalWrite(7,LOW); /* Por cuestión de estabilización del sensor*/
    delayMicroseconds(5);
    digitalWrite(7, HIGH); /* envío del pulso ultrasónico*/
    delayMicroseconds(10);
    tiempo=pulseIn(8, HIGH);
    distancia= int(0.017*tiempo); /*fórmula para calcular la distancia obteniendo un valor entero*/

    digitalWrite(S2,LOW); //RED
    digitalWrite(S3,LOW);
    VR=pulseIn(V0,HIGH);

    digitalWrite(S2,LOW); //BLUE
    digitalWrite(S3,HIGH);
    VB=pulseIn(V0,HIGH);

    digitalWrite(S2,HIGH); //GREEN
    digitalWrite(S3,HIGH);
    VG=pulseIn(V0,HIGH);
     
    if(VG<VR && VG<VB && VB>VR&&VG<15) //Se establecen los límites para evaluar el color
    {
      Serial.println("VERDE");
      digitalWrite(lg,HIGH);
    }
    
    if(VB<VR && VB<VG && VR>VG&&VB<10)
    {
      Serial.println("AZUL");
      digitalWrite(lb,HIGH);
    }
    
    if(VR<VB && VR<VG && VG>VB&&VR<15)
    {
       Serial.println("ROJO");
       digitalWrite(lr,HIGH);
    }
    
  if(Serial.available() > 0)
  {

    state = Serial.read();
 
      if (state=='a')
      {
        
        analogWrite(enA,100);
        analogWrite(enB,100);
        
        digitalWrite(derA,HIGH);
        digitalWrite(derB,LOW);
        digitalWrite(izqA,HIGH);
        digitalWrite(izqB,LOW);
        
      }

      if (state=='b')
      {
        analogWrite(enA,255);
        analogWrite(enB,255);
        
        digitalWrite(derA,HIGH);
        digitalWrite(derB,LOW);
        digitalWrite(izqA,HIGH);
        digitalWrite(izqB,LOW);
      }

      if (state=='c'||distancia<10)
      {
        analogWrite(enA,150);
        analogWrite(enB,150);
        
        digitalWrite(derA,LOW);
        digitalWrite(derB,HIGH);
        digitalWrite(izqA,LOW);
        digitalWrite(izqB,HIGH);
      }

      if (state=='d'||distancia<10)
      {
        analogWrite(enA,255);
        analogWrite(enB,255);
        
        digitalWrite(derA,LOW);
        digitalWrite(derB,HIGH);
        digitalWrite(izqA,LOW);
        digitalWrite(izqB,HIGH);
      }

      if (state=='e')
      {
        analogWrite(enA,150);
        analogWrite(enB,150);
        
        digitalWrite(derA,LOW);
        digitalWrite(derB,HIGH);
        digitalWrite(izqA,HIGH);
        digitalWrite(izqB,LOW);
      }

      if (state=='f')
      {
        analogWrite(enA,255);
        analogWrite(enB,255);
        
        digitalWrite(derA,LOW);
        digitalWrite(derB,HIGH);
        digitalWrite(izqA,HIGH);
        digitalWrite(izqB,LOW);
      }

      if (state=='g')
      {
        analogWrite(enA,150);
        analogWrite(enB,150);
        
        digitalWrite(derA,HIGH);
        digitalWrite(derB,LOW);
        digitalWrite(izqA,LOW);
        digitalWrite(izqB,HIGH);
      }

      if (state=='h')
      {
        analogWrite(enA,255);
        analogWrite(enB,255);
        
        digitalWrite(derA,HIGH);
        digitalWrite(derB,LOW);
        digitalWrite(izqA,LOW);
        digitalWrite(izqB,HIGH);
      }

      if (state=='z')
      {
        digitalWrite(derA,LOW);
        digitalWrite(derB,LOW);
        digitalWrite(izqA,LOW);
        digitalWrite(izqB,LOW);
      }

    else
    {
      //Serial.println("No identificado");
      digitalWrite(lg,LOW);
      digitalWrite(lb,LOW);
      digitalWrite(lr,LOW);
    }

      Serial.print(state);

  }
                  
}
