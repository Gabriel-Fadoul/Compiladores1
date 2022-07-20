
(*
 *  execute "coolc bad.cl" to see the error messages that the coolc parser
 *  generates
 *
 *  execute "myparser bad.cl" to see the error messages that your parser
 *  generates
 *)

(* no error *)
class A {
};

(* error:  b is not a type identifier *)
Class b inherits A {
};

(* error:  a is not a type identifier *)
Class C inherits a {
};

(* error:  keyword inherits is misspelled *)
Class D inherts A {
};

(* error:  closing brace is missing *)
Class E inherits A {
;

class VirgulaErrada {
  teste(v1: Int, v2: Int): String { "Teste" };
  execTeste(): String { teste(2, 2,) };
};

class PVDuplo {
  teste(): String {
    {
      "Teste";;
    }
  };
};

class RetornoErrado {
  teste(): Int {
    {
      "Teste";;
    }
  };
};