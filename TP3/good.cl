class A {
};

Class BB__ inherits A {
};


class Pessoa {
  name: String <- "Joao";
};

Class Usuario inherits Pessoa {
  teste(): String {
    {
      "Helo";
      "World!";
    }
  };
};

Class Relogio {
  horas: Int <- 0;
  minutos: Int <- 0;

  incrementarMinutos(): Int {
    {
      minutos <- minutos + 1;
      minutos;
    }
  };
};
