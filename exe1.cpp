// Created by NATSOFT Ronald Espitia.
#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Definición de constantes
const string UNIFIED = "unified.csv";
const string RESULT = "result.csv";
const vector<string> TITULOS = {
    "ID CONTRATO PROFESIONAL IS", "HONORARIO", "FECHA HONORARIO", "ID PACIENTE", "PLAN TARIFARIO",
    "PROCEDIMIENTO", "NOMBRE PROCEDIMIENTO", "SUBPROCEDIMIENTO", "NOMBRE SUBPROCEDIMIENTO",
    "ZONA", "UBICACIÓN", "VALOR EVOLUCION", "ESPECIALIDAD PROCEDIMIENTO", "FORMA PAGO",
    "ID PROFESIONAL", "CENTRO DE COSTO", "NIT", "CONCEPTO",
    "id honorario", "numero  contrato", "fecha  factura evolucion", "TIPO HONORARIO", "CLINICA",
    "ESPECIALIDAD PROFESIONAL", "NOMBRE PROFESIONAL", "CLASE NOMINA", "CONCEPTO HOMOLOGADO", "FECHA DEV"
};

// Implementación de la función exe1
void exe1() {
    vector<tuple<string, string, bool>> archivos = {
        {"GARD_Nuevos.csv", "GARANTIAS NEGATIVAS", true},
        {"HNE_Nuevos.csv", "HONORARIOS NEGATIVOS", true},
        {"HON_Nuevos.csv", "HONORARIOS POSITIVOS", false},
        {"GARP_Nuevos.csv", "GARANTIAS POSITIVAS", false}
    };
    vector<string> allData;
    vector<vector<string>> datos;
    vector<string> result;
    vector<vector<string>> vectorDeVectores;

    for (const auto& archivo : archivos) {
        string fileName = get<0>(archivo);
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error al leer el archivo: " << fileName << endl;
            continue;
        }

        string linea;
        while (getline(file, linea)) {
            vector<string> elementos;
            istringstream stream(linea);
            string token;

            while (getline(stream, token, ';')) {
                elementos.push_back(token);
            }

            vector<string> nuevosElementos = {"a1", "a2", "a3", "a4", "a5"};
            if (elementos.size() == 20) {
                string valor = elementos[16];
                elementos.push_back(get<1>(archivo));
                elementos.erase(elementos.begin() + 16);
                elementos.insert(elementos.begin() + 6, "");
                elementos.insert(elementos.begin() + 8, "");
                elementos.push_back(valor);
                elementos.insert(elementos.begin() + 22, nuevosElementos.begin(), nuevosElementos.end());
            } else if (elementos.size() == 19) {
                elementos.push_back(get<1>(archivo));
                elementos.insert(elementos.begin() + 6, "");
                elementos.insert(elementos.begin() + 8, "");
                elementos.emplace_back("_");
                elementos.insert(elementos.begin() + 22, nuevosElementos.begin(), nuevosElementos.end());
            }

            datos.push_back(elementos);
        }
        file.close();
    }

    datos.insert(datos.begin(), TITULOS);

    ofstream archivo(RESULT);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << RESULT << endl;
    }

    for (const auto& linea : datos) {
        for (size_t i = 0; i < linea.size(); ++i) {
            archivo << linea[i];
            if (i < linea.size() - 1) {
                archivo << ";";
            }
        }
        archivo << "\n";
    }
    archivo.close();
    cout << "Archivo CSV guardado correctamente: " << RESULT << endl;
}