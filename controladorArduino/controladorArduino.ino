int cima_apertado = 0;
int direita_apertado = 0;
int baixo_apertado = 0;
int esquerda_apertado = 0;

int a_apertado = 0;
int s_apertado = 0;
int d_apertado = 0;
int f_apertado = 0;

int z_apertado = 0;
int x_apertado = 0;
int c_apertado = 0;
int v_apertado = 0;

int pino_da_tecla_cima = 13; // Fio laranja
int pino_da_tecla_direita = 12; // Fio verde
int pino_da_tecla_baixo = 11; // Fio vermelho
int pino_da_tecla_esquerda = 10; // Fio amarelo

int pino_da_tecla_a = 9;
int pino_da_tecla_s = 8;
int pino_da_tecla_d = 7;
int pino_da_tecla_f = 6;

int pino_da_tecla_z = 5;
int pino_da_tecla_x = 4;
int pino_da_tecla_c = 3;
int pino_da_tecla_v = 2;

char teclasParaEnviar[10];

void setup() {
  configurar_pino(pino_da_tecla_cima);
  configurar_pino(pino_da_tecla_direita);
  configurar_pino(pino_da_tecla_baixo);
  configurar_pino(pino_da_tecla_esquerda);
  configurar_pino(pino_da_tecla_a);
  configurar_pino(pino_da_tecla_s);
  configurar_pino(pino_da_tecla_d);
  configurar_pino(pino_da_tecla_f);
  configurar_pino(pino_da_tecla_z);
  configurar_pino(pino_da_tecla_x);
  configurar_pino(pino_da_tecla_c);
  configurar_pino(pino_da_tecla_v);

  // Inicia a comunicação com a máquina via porta COM
  Serial.begin(9600);
}

void configurar_pino(int numero_do_pino) {
  configurar_escuta_de_entrada_no_pino(numero_do_pino);
  registrar_escrita_em_pino_digital(numero_do_pino);
}

void configurar_escuta_de_entrada_no_pino(int numero_do_pino) {
  pinMode(numero_do_pino, INPUT);
}

void registrar_escrita_em_pino_digital(int numero_do_pino) {
  // O que faz ficar em modo PullUp é o HIGH
  digitalWrite(numero_do_pino, HIGH);
}

void loop() {
  analisar_contato(&cima_apertado, pino_da_tecla_cima, "c", "-c");
  analisar_contato(&direita_apertado, pino_da_tecla_direita, "d", "-d");
  analisar_contato(&baixo_apertado, pino_da_tecla_baixo, "b", "-b");
  analisar_contato(&esquerda_apertado, pino_da_tecla_esquerda, "e", "-e");
  analisar_contato(&a_apertado, pino_da_tecla_a, "9", "-9");
  analisar_contato(&s_apertado, pino_da_tecla_s, "8", "-8");
  analisar_contato(&d_apertado, pino_da_tecla_d, "7", "-7");
  analisar_contato(&f_apertado, pino_da_tecla_f, "6", "-6");
  analisar_contato(&z_apertado, pino_da_tecla_z, "5", "-5");
  analisar_contato(&x_apertado, pino_da_tecla_x, "4", "-4");
  analisar_contato(&c_apertado, pino_da_tecla_c, "3", "-3");
  analisar_contato(&v_apertado, pino_da_tecla_v, "2", "-2");

  if (teclasParaEnviar != NULL && teclasParaEnviar[0] != 0) {
    Serial.println(teclasParaEnviar);
  }  
  
  teclasParaEnviar[0] = 0;

  delay(10);
}

void analisar_contato(int *estado_do_comando, int pino_da_tecla, char* comandoKeyDown, char* comandoKeyUp) {
  if (*estado_do_comando == 0 && digitalRead(pino_da_tecla) == 0) {
    *estado_do_comando = 1;
    strcat(teclasParaEnviar, comandoKeyDown);
  }

  if (*estado_do_comando == 1 && digitalRead(pino_da_tecla) == 1) {
    *estado_do_comando = 0;
    strcat(teclasParaEnviar, comandoKeyUp);
  }
}
