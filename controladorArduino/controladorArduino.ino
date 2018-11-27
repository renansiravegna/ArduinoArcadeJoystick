int pino_da_tecla_cima = 13; // Fio vermelho
bool cima_apertado = false;

int pino_da_tecla_esquerda = 12; // Fio verde
bool esquerda_apertado = false;

int pino_da_tecla_baixo = 11; // Fio laranja
bool baixo_apertado = false;

int pino_da_tecla_direita = 10; // Fio amarelo
bool direita_apertado = false;

int pino_da_tecla_a = 9;
bool a_apertado = false;

int pino_da_tecla_s = 8;
bool s_apertado = false;

int pino_da_tecla_d = 7;
bool d_apertado = false;

int pino_da_tecla_f = 6;
bool f_apertado = false;

int pino_da_tecla_z = 5;
bool z_apertado = false;

int pino_da_tecla_x = 4;
bool x_apertado = false;

int pino_da_tecla_c = 3;
bool c_apertado = false;

int pino_da_tecla_v = 2;
bool v_apertado = false;

int pino_da_tecla_start = A0;
bool start_apertado = false;

int pino_da_tecla_select = A1;
bool select_apertado = false;

int pino_da_tecla_home = A2;
bool home_apertado = false;


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
  configurar_pino(pino_da_tecla_start);
  configurar_pino(pino_da_tecla_select);
  configurar_pino(pino_da_tecla_home);

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
  analisar_contato(&start_apertado, pino_da_tecla_start, "r", "-r");
  analisar_contato(&select_apertado, pino_da_tecla_select, "l", "-l");
  analisar_contato(&home_apertado, pino_da_tecla_home, "h", "-h");

  delay(10);
}

void analisar_contato(bool *estado_do_comando, int pino_da_tecla, const char* comando_key_down, const char* comando_key_up) {
  int leitura_do_pino = digitalRead(pino_da_tecla);
  
  if (!*estado_do_comando && leitura_do_pino == 0) {
    *estado_do_comando = 1;
    enviar_comando(comando_key_down);
  }

  else if (*estado_do_comando && leitura_do_pino == 1) {
    *estado_do_comando = 0;
    enviar_comando(comando_key_up);
  }
}

void enviar_comando(const char* comando) {
	Serial.println(comando);	
}
