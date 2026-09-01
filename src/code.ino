#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h> 

const int PINO_TRIG = 4;        
const int PINO_ECHO = 2;        
# define MOT_PIN1 18            
# define MOT_PIN2 19            
const int PINO_buzzer = 23;     

const int CH_MOTOR1 = 0;
const int CH_MOTOR2 = 1;
const int CH_BUZZER = 2;

const int PWM_FREQ_MOTORS = 20000; 
const int PWM_FREQ_BUZZER = 2000;  
const int PWM_RESOLUTION = 8;      


long duracao_us ;            
float distancia_us ;         
float media_distancia [5];   
float nova_distancia = 250;  
int indice = 0;               


unsigned long ultimoUltrassom = 0;  
const int intervaloUltrassom = 1000;

unsigned long ultimoControlarAtuadores = 0;
const int intervaloAtuadores = 500;

bool motoresAtivos = false ;   

void lerUltrassom ();
void controlarAtuadores ( float dist_us );


long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void setup () {
    Serial . begin (115200) ;     
    Serial.println("Inicializando ESP32...");
    
    pinMode ( PINO_TRIG , OUTPUT ) ;
    pinMode ( PINO_ECHO , INPUT ) ;
    
    pinMode ( MOT_PIN1 , OUTPUT ) ;
    pinMode ( MOT_PIN2 , OUTPUT ) ;
    
    
    ledcAttach ( MOT_PIN1, PWM_FREQ_MOTORS, PWM_RESOLUTION ); 
    
    ledcAttach ( MOT_PIN2, PWM_FREQ_MOTORS, PWM_RESOLUTION ); 

    ledcAttach ( PINO_buzzer, PWM_FREQ_BUZZER, PWM_RESOLUTION );
    
    Serial.println("Configuracao PWM LEDC concluida.");
}


void loop () {
    
    if ( millis () - ultimoUltrassom >= intervaloUltrassom ) {
        lerUltrassom () ;             
        ultimoUltrassom = millis () ;   
    }
    
    
    if ( millis () - ultimoControlarAtuadores >= intervaloAtuadores ) {
        controlarAtuadores ( distancia_us ) ;   
        ultimoControlarAtuadores = millis () ;  
    }
}


void lerUltrassom () {

    digitalWrite ( PINO_TRIG , LOW ) ;
    delayMicroseconds (2) ;
    digitalWrite ( PINO_TRIG , HIGH ) ;
    delayMicroseconds (10) ;
    digitalWrite ( PINO_TRIG , LOW ) ;
    
    duracao_us = pulseIn ( PINO_ECHO , HIGH , 60000) ; 
    
    
    if ( duracao_us == 0 || duracao_us > 17493) { 
        nova_distancia = 400.0; 
    } else {

        nova_distancia = ( (float)duracao_us * 0.0343) / 2.0;
    }
    

    media_distancia [ indice ] = nova_distancia ; 
    indice = ( indice + 1) % 5;                 
    

    distancia_us = 0.0;
    for (int i = 0; i < 5; i ++) {
        distancia_us += media_distancia [ i ];
    }
    distancia_us /= 5.0;
    

    Serial . print (" Ultrassom : ") ;
    Serial . print ( distancia_us ) ;
    Serial . println (" cm") ;
}

void controlarAtuadores ( float dist_us ) {
    

    if ( dist_us > 0 && dist_us <= 150.0) {

        ledcWrite (CH_BUZZER , 255) ;
        delay (500) ;
        ledcWrite (CH_BUZZER , 0) ;    
    } else {
        ledcWrite (CH_BUZZER , 0); 
    }
     
    if ( dist_us <= 300.0 && dist_us > 150.0) {

        int intensidade = map ( (long)dist_us , 300L , 150L , 150L , 255L) ;
        intensidade = constrain ( intensidade , 150 , 255) ; // Garante que a intensidade fique entre 150 e 255
        
        ledcWrite (CH_MOTOR1 , intensidade ) ;
        ledcWrite (CH_MOTOR2 , intensidade ) ;
        motoresAtivos = true ; 
        

        Serial . print (" Intensidade dos motores : ") ;
        Serial . println ( intensidade ) ;
    } else {

        if ( motoresAtivos ) {
            ledcWrite (CH_MOTOR1 , 0) ;
            ledcWrite (CH_MOTOR2 , 0) ;
            motoresAtivos = false ;
            Serial.println("Motores Desligados.");
        }
    }
}
