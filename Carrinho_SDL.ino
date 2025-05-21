#include <Servo.h>

Servo servoEsquerda;
Servo servoDireita;

void setup() {
  Serial.begin(9600);

  servoEsquerda.attach(5);  // Servo da roda esquerda
  servoDireita.attach(6);   // Servo da roda direita

  // Inicialmente parado
  servoEsquerda.write(90);
  servoDireita.write(90);
}

void loop() {
  int sensorEsquerda = analogRead(A4);
  int sensorDireita = analogRead(A5);

  Serial.print("Sensor E: ");
  Serial.print(sensorEsquerda);
  Serial.print(" | Sensor D: ");
  Serial.println(sensorDireita);

  // Define limite de detecção do preto
  bool esquerdaNoPreto = sensorEsquerda < 400;
  bool direitaNoPreto = sensorDireita < 400;

  // Velocidade ajustada (mais próxima de 90 = mais lenta)
  int velocidadeEsquerda = 80;  // Vai para frente lentamente
  int velocidadeDireita = 100;  // Vai para frente lentamente

  if (!esquerdaNoPreto && !direitaNoPreto) {
    // Ambos no branco: andar reto
    servoEsquerda.write(velocidadeEsquerda);
    servoDireita.write(velocidadeDireita);
  }
  else if (esquerdaNoPreto && !direitaNoPreto) {
    // Sensor esquerdo no preto: parar roda esquerda
    servoEsquerda.write(90);  // Parado
    servoDireita.write(velocidadeDireita);
  }
  else if (!esquerdaNoPreto && direitaNoPreto) {
    // Sensor direito no preto: parar roda direita
    servoEsquerda.write(velocidadeEsquerda);
    servoDireita.write(90);  // Parado
  }
  else {
    // Ambos sensores detectam preto: parar
    servoEsquerda.write(90);
    servoDireita.write(90);
  }

  delay(100);  // Pequena pausa para estabilidade

}
