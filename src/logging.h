#include "Arduino.h"

typedef bool (*functor)();

bool process(functor procedure, char *running_message, char *success_message, char *failure_message)
{
    Serial.print(running_message);
    bool success = procedure();

    Serial.print("\33[2K\r");

    if (success)
        Serial.print(success_message);
    else
        Serial.print(failure_message);

    Serial.print("\n\r");

    return success;
}