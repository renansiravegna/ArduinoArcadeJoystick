bool cima_apertado = false;
bool direita_apertado = false;
bool baixo_apertado = false;
bool esquerda_apertado = false;

bool a_apertado = false;
bool s_apertado = false;
bool d_apertado = false;
bool f_apertado = false;

bool z_apertado = false;
bool x_apertado = false;
bool c_apertado = false;
bool v_apertado = false;

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

  delay(10);
}

void analisar_contato(bool *estado_do_comando, int pino_da_tecla, char* comando_key_down, char* comando_key_up) {
  if (!*estado_do_comando && digitalRead(pino_da_tecla) == 0) {
    *estado_do_comando = 1;
    enviar_comando(comando_key_down);
  }

  if (*estado_do_comando && digitalRead(pino_da_tecla) == 1) {
    *estado_do_comando = 0;
    enviar_comando(comando_key_up);
  }
}

void enviar_comando(char* comando) {
	Serial.println(comando);	
}