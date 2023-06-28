// Juan Sebastian Cifuentes CODIGO 2179800
// Maria Alejandra Carvajal CODIGO 2178495

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Organiza los elementos de una instruccion en un vector.
Siempre devuelve un vector de 5 elementos.

Por ejemplo:
organizador("SET D1 1") => {"SET", "D1", "1", "", ""}
organizador("SET D1 1 NULL NULL") => {"SET", "D1", "1", "NULL", "NULL"}
organizador("ADD D1 D2 NULL") => {"ADD", "D1", "D2", "NULL", ""}
*/
vector<string> organizador_di(string instruccion) {
  std::string elemendo_1;
  std::string elemendo_2;
  std::string elemendo_3;
  std::string elemendo_4;
  std::string elemendo_5;

  size_t primera_d = instruccion.find(' ');
  size_t segunda_d = instruccion.find(' ', primera_d + 1);
  size_t tercera_d = instruccion.find(' ', segunda_d + 1);
  size_t cuarta_d = instruccion.find(' ', tercera_d + 1);
  size_t quinta_d = instruccion.find(' ', cuarta_d + 1);

  if (primera_d != std::string::npos) {
    elemendo_1 = instruccion.substr(0, primera_d);
    elemendo_2 = instruccion.substr(primera_d + 1, segunda_d - primera_d - 1);
    elemendo_3 = instruccion.substr(segunda_d + 1, tercera_d - segunda_d - 1);
    elemendo_4 = instruccion.substr(tercera_d + 1, cuarta_d - tercera_d - 1);
    elemendo_5 = instruccion.substr(cuarta_d + 1, quinta_d - cuarta_d - 1);
  }

  vector<string> instruccion_v = {elemendo_1, elemendo_2, elemendo_3,
                                  elemendo_4, elemendo_5};

  return instruccion_v;
}

/*
Convierte una direccion de una instruccion en un numero entero.

Por ejemplo:
conversor_ddm("D1") => 1
conversor_ddm("D2") => 2
conversor_ddm("D3") => 3
*/
int conversor_ddm(string direccion_dm) { return stoi(direccion_dm.substr(1)); }

void set_f(vector<string> &elementos_di, vector<string> &memoria) {
  memoria[conversor_ddm(elementos_di[1])] = elementos_di[2];
}

void ldr_f(vector<string> &elementos_di, vector<string> &memoria,
           float &acumulador) {
  acumulador = stof(memoria[conversor_ddm(elementos_di[1])]);
}

float add(float a, float b) { return a + b; }
float sub(float a, float b) { return a - b; }
float mul(float a, float b) { return a * b; }
float div(float a, float b) { return a / b; }

void alu(vector<string> &elementos_di, vector<string> &memoria,
         float &acumulador, string &icr, string &mar, string &mdr,
         float (*operacion)(float, float)) {

  if (elementos_di[2] == "NULL") {
    icr = elementos_di[0] + " " + elementos_di[1];
    mar = elementos_di[1];
    mdr = memoria[conversor_ddm(elementos_di[1])];
    acumulador =
        operacion(acumulador, stof(memoria[conversor_ddm(elementos_di[1])]));
  } else {
    if (elementos_di[3] == "NULL") {
      icr = elementos_di[0] + " " + elementos_di[1] + " " + elementos_di[2];
      mar = elementos_di[2];
      mdr = memoria[conversor_ddm(elementos_di[2])];
      acumulador = stof(memoria[conversor_ddm(elementos_di[1])]);
      memoria[conversor_ddm(elementos_di[2])] = to_string(
          operacion(stof(memoria[conversor_ddm(elementos_di[2])]), acumulador));
    } else {
      icr = elementos_di[0] + " " + elementos_di[1] + " " + elementos_di[2] +
            " " + elementos_di[3];
      mar = elementos_di[3];
      mdr = memoria[conversor_ddm(elementos_di[3])];
      acumulador = stof(memoria[conversor_ddm(elementos_di[1])]);
      acumulador =
          operacion(acumulador, stof(memoria[conversor_ddm(elementos_di[2])]));
      memoria[conversor_ddm(elementos_di[3])] = to_string(acumulador);
    }
  }
}

float inc(float a) { return a + 1; }
float dec(float a) { return a - 1; }

void alu_2(vector<string> &elementos_di, vector<string> &memoria,
           float &acumulador, string &icr, string &mar, string &mdr,
           float (*operacion)(float)) {
  icr = elementos_di[0] + " " + elementos_di[1];
  mar = elementos_di[1];
  memoria[conversor_ddm(elementos_di[1])] =
      to_string(operacion(stof(elementos_di[2])));
  mdr = memoria[conversor_ddm(elementos_di[1])];
}

void unidad_dc(vector<string> &elementos_di, vector<string> &memoria,
               float &acumulador, string &icr, string &mar, string &mdr) {

  if (elementos_di[0] == "SET") {
    icr = elementos_di[0] + " " + elementos_di[1] + " " + elementos_di[2];
    mar = elementos_di[1];
    mdr = elementos_di[2];
    set_f(elementos_di, memoria);
  }

  if (elementos_di[0] == "LDR") {
    icr = elementos_di[0] + " " + elementos_di[1];
    mar = elementos_di[1];
    mdr = memoria[conversor_ddm(elementos_di[1])];
    ldr_f(elementos_di, memoria, acumulador);
  }

  if (elementos_di[0] == "ADD") {
    alu(elementos_di, memoria, acumulador, icr, mar, mdr, add);
  }

  if (elementos_di[0] == "SUB") {
    alu(elementos_di, memoria, acumulador, icr, mar, mdr, sub);
  }

  if (elementos_di[0] == "MUL") {
    alu(elementos_di, memoria, acumulador, icr, mar, mdr, mul);
  }

  if (elementos_di[0] == "DIV") {
    alu(elementos_di, memoria, acumulador, icr, mar, mdr, div);
  }

  if (elementos_di[0] == "INC") {
    alu_2(elementos_di, memoria, acumulador, icr, mar, mdr, inc);
  }

  if (elementos_di[0] == "DEC") {
    alu_2(elementos_di, memoria, acumulador, icr, mar, mdr, dec);
  }

  if (elementos_di[0] == "MOV") {
    icr = elementos_di[0] + " " + elementos_di[1] + " " + elementos_di[2];
    mar = elementos_di[2];
    memoria[conversor_ddm(elementos_di[2])] =
        memoria[conversor_ddm(elementos_di[1])];
    memoria[conversor_ddm(elementos_di[1])] = "";
    mdr = memoria[conversor_ddm(elementos_di[2])];
  }

  if (elementos_di[0] == "STR") {
    icr = elementos_di[0] + " " + elementos_di[1];
    mar = elementos_di[1];
    memoria[conversor_ddm(elementos_di[1])] = to_string(acumulador);
    mdr = memoria[conversor_ddm(elementos_di[1])];
  }

  if (elementos_di[0] == "BEQ") {
    if (elementos_di[2] == "NULL") {
      icr = elementos_di[0] + " " + elementos_di[1];
      mar = elementos_di[1];
      mdr = memoria[conversor_ddm(elementos_di[1])];
      if (sub(stof(memoria[conversor_ddm(elementos_di[1])]), acumulador) == 0) {
        memoria[conversor_ddm(elementos_di[1])] =
            memoria[conversor_ddm(elementos_di[1])];
      }
    } else {
      if (elementos_di[3] == "NULL") {
        icr = elementos_di[0] + " " + elementos_di[1] + " " + elementos_di[2];
        mar = elementos_di[2];
        mdr = memoria[conversor_ddm(elementos_di[1])];
        if (sub(stof(memoria[conversor_ddm(elementos_di[1])]),
                stof(memoria[conversor_ddm(elementos_di[2])])) == 0) {
          memoria[conversor_ddm(elementos_di[1])] =
              memoria[conversor_ddm(elementos_di[1])];
        }
      } else {
        icr = elementos_di[0] + " " + elementos_di[1] + " " + elementos_di[2] +
              " " + elementos_di[3];
        mar = elementos_di[3];
        mdr = memoria[conversor_ddm(elementos_di[1])];
        if (sub(stof(memoria[conversor_ddm(elementos_di[1])]),
                stof(memoria[conversor_ddm(elementos_di[2])])) == 0) {
          memoria[conversor_ddm(elementos_di[3])] =
              memoria[conversor_ddm(elementos_di[1])];
        }
      }
    }
  }

  if (elementos_di[0] == "SHW") {
    if (elementos_di[1] == "ACC") {
      cout << acumulador;
    }
    if (elementos_di[1] == "ICR" || elementos_di[1] == "UC") {
      cout << icr;
    }
    if (elementos_di[1] == "MAR") {
      cout << mar;
    }
    if (elementos_di[1] == "MDR") {
      cout << mdr;
    }
    if (elementos_di[1] != "ACC" && elementos_di[1] != "ICR" &&
        elementos_di[1] != "MAR" && elementos_di[1] != "MDR") {
      cout << stof(memoria[conversor_ddm(elementos_di[1])]); // << endl;
    }
  }

  if (elementos_di[0] == "AND") {
    if (mul(stof(memoria[conversor_ddm(elementos_di[1])]),
            stof(memoria[conversor_ddm(elementos_di[2])])) != 0) {
      cout << "true";
    } else {
      cout << "false";
    }
  }

  if (elementos_di[0] == "OR") {
    if (add(stof(memoria[conversor_ddm(elementos_di[1])]),
            stof(memoria[conversor_ddm(elementos_di[2])])) != 0) {
      cout << "true";
    } else {
      cout << "false";
    }
  }
}

int main() {

  vector<string> memoria(1000);
  float acumulador;
  string icr;
  string mar;
  string mdr;

  int indicador_dpee = true;
  std::string instruccion;

  while (indicador_dpee == true) {
    getline(std::cin, instruccion);
    vector<string> elementos_di = organizador_di(instruccion);

    unidad_dc(elementos_di, memoria, acumulador, icr, mar, mdr);
    // PARA QUE FUNCIONE END LA INSTRUCCIÓN DEBE SER END NULL
    if (elementos_di[0] == "END") {
      indicador_dpee = false;
    }
  }
  return 0;
}
