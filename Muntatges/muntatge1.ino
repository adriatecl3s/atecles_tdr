#include <Stepper.h>

// Definir los pines de control de los motores
const int stepsPerRevolution = 2038;
Stepper motorA = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper motorB = Stepper(stepsPerRevolution, 2, 4, 3, 5);


void setup() {
  // Inicializar la comunicación serial
  Serial.begin(9600);

  // Establecer la velocidad de los motores
  motorA.setSpeed(10);
  motorB.setSpeed(10);
}

void loop() {
  if (Serial.available() > 0) {
    // Leer el comando del monitor serial
    String comando = Serial.readStringUntil('\n');

    // Dividir el comando en motor y grados
    int comaIndex = comando.indexOf(',');
    if (comaIndex != -1) {
      String motor = comando.substring(0, comaIndex);
      int grados = comando.substring(comaIndex + 1).toInt();

      // Girar el motor especificado a la cantidad de grados
      if (motor == "a") {
        int pasos = map(grados, 0, 360, 0, stepsPerRevolution);
        motorA.step(pasos);
      } else if (motor == "b") {
        int pasos = map(grados, 0, 360, 0, stepsPerRevolution);
        motorB.step(pasos);
      }
    }
  }
}
