class A {
};

Class BB__ inherits A {
};

class Pessoa {
  name: String <- "Joao";
};

class Usuario inherits Pessoa {
  teste(): String {
    {
      "Helo";
      "World!";
    }
  };
}

class Relogio {
  horas: Int <- 0;
  minutos: Int <- 0;

  incrementarMinutos(): Int {
    {
      minutos <- minutos + 1;
      minutos;
    }
  };
};