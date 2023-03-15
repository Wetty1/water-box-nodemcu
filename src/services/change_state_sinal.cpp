#include <services/change_state_sinal.hpp>
#include <services/http_api_client.hpp>
#include <Arduino.h>
#include <global_variables.hpp>

#define largura 1.54
#define comprimento 1.95
#define alturaSensor 102
#define poucaAgua 600
#define caixaCheia 2250

extern float aguaEmLitros;
extern float diffSensorAgua;
extern int stateSinal;

int countToOff;
int countToOn;
int countToNeuter;

bool sendMessage = false;

void checkStateSinal()
{
    float alturaAgua = (float)alturaSensor - diffSensorAgua;

    aguaEmLitros = comprimento * largura * (alturaAgua / 100) * 1000;
    Serial.println("diff: " + String(diffSensorAgua) + "; litros: " + String(aguaEmLitros));

    Serial.println("state: " + String(stateSinal));

    delay(600);

    if (stateSinal != 2)
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
    else
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }

    if (aguaEmLitros > caixaCheia)
    {
        countToOff++;
        countToOn = 0;
        countToNeuter = 0;
    }
    if (aguaEmLitros < poucaAgua)
    {
        countToOn++;
        countToNeuter = 0;
        countToOff = 0;
    }
    if (aguaEmLitros > poucaAgua && aguaEmLitros < caixaCheia)
    {
        countToNeuter++;
        countToOff = 0;
        countToOn = 0;
    }

    if (countToOff > 5)
    {
        if (stateSinal != 0)
        {
            sendMessage = false;
        }
        stateSinal = 0;
        countToNeuter = 0;
    }

    if (countToOn > 5)
    {
        if (stateSinal != 1)
        {
            sendMessage = false;
        }
        stateSinal = 1;
    }

    if (countToNeuter > 5)
    {
        if (stateSinal != 2)
        {
            sendMessage = false;
        }
        stateSinal = 2;
    }

    if (!sendMessage)
    {
        sendMessage = sendChangeSinal(diffSensorAgua, aguaEmLitros, stateSinal);
    }
}