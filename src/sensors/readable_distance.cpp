#include <Arduino.h>
#include <sensors/readable_distance.hpp>

#define divisor 58.0
#define intervaloMedida 7 // MÁXIMO 35 mS PARA ATÉ 6,0M MIN 5mS PARA ATÉ 0,8M
#define qtdMedidas 60     // QUANTIDADE DE MEDIDAS QUE SERÃO FEITAS

#define pinTrigger D1
#define pinEcho D0

float calcularDistancia()
{

    float leituraSum = 0;
    float resultado = 0;

    for (int index = 0; index < qtdMedidas; index++)
    {

        delay(intervaloMedida);
        leituraSum += leituraSimples();
    }

    resultado = (float)leituraSum / qtdMedidas;
    resultado = resultado + 2.2;

    return resultado;
}

float leituraSimples()
{

    long duracao = 0;
    float resultado = 0;

    digitalWrite(pinTrigger, HIGH);

    delayMicroseconds(10);
    digitalWrite(pinTrigger, LOW);

    duracao = pulseIn(pinEcho, HIGH);

    resultado = ((float)duracao / divisor);

    return resultado;
}

void sonarBegin(byte trig, byte echo)
{

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    digitalWrite(trig, LOW); // DESLIGA O TRIGGER E ESPERA 500 uS
    delayMicroseconds(500);
}
