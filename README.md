# Librería Arduino TimeoutTask
Librería para Arduino que implementa una tarea que evalua una determinada condición durante un intervalo de microsegundos especificado por el usuario, y ejecuta acciones en función del resultado obtenido durante la espera. 

Más información https://www.luisllamas.es/libreria-arduino-timeouttask/

## Instrucciones de uso
La clase TimeoutTask está pensada para la ejecución de tareas costosas computacionalmente, sin que afecte al bucle de ejecución principal. 

Por ejemplo en comunicaciones, podemos esperar una señal de inicio durante un breve periodo y, si se recibe la señal, iniciar el proceso de recepción/envío propiamente dicho. Otro ejemplo podría ser comprobar si el estado de unas entradas es el esperado, y en caso afirmativo realizar un cálculo o iniciar un actuador.

Por otro lado, TimeoutTask también es útil para implementar de forma sencilla un watchdog. Por ejemplo, encender un motor durante un cierto tiempo, y esperar que alcance un pulsador de fin de carrera. En caso de sobrepasar un tiempo razonable, detener el motor por seguridad.

Una instancia TimeoutTask dispone de una condición y dos funciones de callback, `OkCallback` y `TimeoutCallback`. Al ejecutar la tarea, se evalúa la condición continuamente durante el tiempo especificado. Si en algún momento la condición es cierta, se ejecuta la función de `OkCallback`. Si, por el contrario, expira el tiempo de Timeout, se ejecuta la acción `TimeoutCallback` y se devuelve el flujo de control.

Se dispone de dos formas de uso de la librería. Una es instanciar un objeto de la clase TimeoutTask, y llamar a su método `Run()`. La forma alternativa es llamar directamente al método estático `Run()`.


### Uso como objeto
La clase TimeoutTask puede instanciarse como un objeto a través de su constructor, y activarse con el método `Run()`.
```c++
// Constructor
TimeoutTask(unsigned long timeout, bool(*conditionFunc)(), 
	void(*okCallback)(), 
	void(*timeoutCallback)())
{
}

// Ejecuta la TimeoutTask
void Run() const;
```

### Uso como método estático
Alternativamente, podemos ejecutar la TimeoutTask a través del método estático `Run()`.

```c++
static void Run(unsigned long timeout, ConditionFunc conditionFunc, CallbackAction okCallback, CallbackAction timeoutCallback);
```


## Ejemplos
La librería Timeout Task incluye los siguientes ejemplos para ilustrar su uso.
* TimeoutTask: Ejemplo como instancia actuando como Timeout

```c++
#include "TimeoutTask.h"

const size_t dataLength = 10;
int data[dataLength];
const int bytesLengths = dataLength * sizeof data[0];

TimeoutTask timeoutTask(50000,
	[]() { return Serial.available() >= dataLength; },
	[]() { Serial.readBytes(reinterpret_cast<byte*>(data), dataLength * sizeof data[0]); },
	nullPtr);

void setup()
{
	timeoutTask.Run();
}

void loop()
{
}
```

* StaticTimeOutTask: Ejemplo con método estático `Run()`
```c++
#include "TimeoutTask.h"

const size_t dataLength = 10;
int data[dataLength];
const int bytesLengths = dataLength * sizeof data[0];

void setup()
{
  TimeoutTask::Run(50000,
	[]() { return Serial.available() >= dataLength; },
	[]() { Serial.readBytes(reinterpret_cast<byte*>(data), dataLength * sizeof data[0]); },
	[]() {});
}

void loop()
{
}
```

* Watchdog: Ejemplo como método estático actuando como Watchdog
```c++
#include "TimeoutTask.h"

const int pinA = 8;
const int pinB = 9;

void moveActuator() {}

void stopActuator() {}

void setup()
{
  TimeoutTask::Run(10000,
  []() { return digitalRead(pinA) && digitalRead(pinB); },
  moveActuator,
  stopActuator);
}

void loop()
{
}
```
