char* cima_apertado = "nao";
char* direita_apertado = "nao";
char* baixo_apertado = "nao";
char* esquerda_apertado = "nao";

char* a_apertado = "nao";
char* s_apertado = "nao";
char* d_apertado = "nao";

int pino_da_tecla_cima = 13; // Fio laranja
int pino_da_tecla_direita = 12; // Fio verde
int pino_da_tecla_baixo = 11; // Fio vermelho
int pino_da_tecla_esquerda = 10; // Fio amarelo

int pino_da_tecla_a = 9;
int pino_da_tecla_s = 8;
int pino_da_tecla_d = 7;

char teclasParaEnviar[10];

void setup() {
  pinMode(pino_da_tecla_cima, INPUT);
  pinMode(pino_da_tecla_direita, INPUT);
  pinMode(pino_da_tecla_baixo, INPUT);
  pinMode(pino_da_tecla_esquerda, INPUT);
  pinMode(pino_da_tecla_a, INPUT);
  pinMode(pino_da_tecla_s, INPUT);
  pinMode(pino_da_tecla_d, INPUT);

  digitalWrite(pino_da_tecla_cima, HIGH);
  digitalWrite(pino_da_tecla_direita, HIGH);
  digitalWrite(pino_da_tecla_baixo, HIGH);
  digitalWrite(pino_da_tecla_esquerda, HIGH);
  digitalWrite(pino_da_tecla_a, HIGH);
  digitalWrite(pino_da_tecla_s, HIGH);
  digitalWrite(pino_da_tecla_d, HIGH);

  // Inicia a comunicação com a máquina via porta COM
  Serial.begin(9600);
}

void configurar_escuta_de_entrada_no_pino(int numero_do_pino) {
  pinMode(numero_do_pino, INPUT);
}

void registrar_escrita_em_pino_digital(int numero_do_pino) {
  // O que faz ficar em pullup é o HIGH
  digitalWrite(numero_do_pino, HIGH);
}

void loop_inativo() {
  analisar_contato(cima_apertado, pino_da_tecla_cima, "c");

  if (teclasParaEnviar != NULL && teclasParaEnviar[0] != 0) {
    Serial.println(teclasParaEnviar);
  }  
  
  teclasParaEnviar[0] = 0;

  delay(10);
}

void analisar_contato(char* estado_do_comando, int pino_da_tecla, char* comando) {
  if (estado_do_comando == "nao" && digitalRead(pino_da_tecla) == 0) {
    estado_do_comando = "sim";
    strcat(teclasParaEnviar, strcat(comando, "_"));
  }

  if (estado_do_comando == "sim" && digitalRead(pino_da_tecla) == 1) {
    estado_do_comando = "nao";
    strcat(teclasParaEnviar, strcat("_", comando));
  }
}

void loop() {
  if (cima_apertado == "nao" && digitalRead(pino_da_tecla_cima) == 0) {
    cima_apertado = "sim";
    strcat(teclasParaEnviar, "c_");
  }

  if (cima_apertado == "sim" && digitalRead(pino_da_tecla_cima) == 1) {
    cima_apertado = "nao";
    strcat(teclasParaEnviar, "_c");
  }
  
  if (baixo_apertado == "nao" && digitalRead(pino_da_tecla_baixo) == 0) {
    baixo_apertado = "sim";
    strcat(teclasParaEnviar, "b_");
  }

  if (baixo_apertado == "sim" && digitalRead(pino_da_tecla_baixo) == 1) {
    baixo_apertado = "nao";
    strcat(teclasParaEnviar, "_b");
  }

    if (direita_apertado == "nao" && digitalRead(pino_da_tecla_direita) == 0) {
    direita_apertado = "sim";
    strcat(teclasParaEnviar, "d_");
  }

  if (direita_apertado == "sim" && digitalRead(pino_da_tecla_direita) == 1) {
    direita_apertado = "nao";
    strcat(teclasParaEnviar, "_d");
  }
  
  if (esquerda_apertado == "nao" && digitalRead(pino_da_tecla_esquerda) == 0) {
    esquerda_apertado = "sim";
    strcat(teclasParaEnviar, "e_");
  }

  if (esquerda_apertado == "sim" && digitalRead(pino_da_tecla_esquerda) == 1) {
    esquerda_apertado = "nao";
    strcat(teclasParaEnviar, "_e");
  }
  
  if (a_apertado == "nao" && digitalRead(pino_da_tecla_a) == 0) {
    a_apertado = "sim";
    strcat(teclasParaEnviar, "a_");
  }

  if (a_apertado == "sim" && digitalRead(pino_da_tecla_a) == 1) {
    a_apertado = "nao";
    strcat(teclasParaEnviar, "_a");
  }
  
  if (s_apertado == "nao" && digitalRead(pino_da_tecla_s) == 0) {
    s_apertado = "sim";
    strcat(teclasParaEnviar, "s_");
  }

  if (s_apertado == "sim" && digitalRead(pino_da_tecla_s) == 1) {
    s_apertado = "nao";
    strcat(teclasParaEnviar, "_s");
  }
  
  if (d_apertado == "nao" && digitalRead(pino_da_tecla_d) == 0) {
    d_apertado = "sim";
    strcat(teclasParaEnviar, "r_");
  }

  if (d_apertado == "sim" && digitalRead(pino_da_tecla_d) == 1) {
    d_apertado = "nao";
    strcat(teclasParaEnviar, "_r");
  }

  if (teclasParaEnviar != NULL && teclasParaEnviar[0] != 0) {
    Serial.println(teclasParaEnviar);
  }  
  
  teclasParaEnviar[0] = 0;

  delay(10);
}
