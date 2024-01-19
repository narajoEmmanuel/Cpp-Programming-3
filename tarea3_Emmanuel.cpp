/*
Nombre: Emmanuel Naranjo
Fecha creacion:11/9/19
Ultima modificacion:18/9/19
*/
//Directivas para el compilador
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>

using namespace std;


//Declaraciones globales
const string tipos_de_arduino[] = {
        "UNO",
        "TRE",
        "Zero",
        "Zero Pro",
        "BT",
        "Mega",
        "Ethernet",
        "Pro",
        "Pro Mini",
        "Micro",
        "Primo",
        "Nano",
        "Industrial 101",
        "LilyPad",
        "Esplora" };

//Definicion de estructuras
struct produccion
{
    string arduino;
    double cantidad=0;
};

//Definicion de funciones

/*
 * Funcion: Agrega los arduinos y su cantidad a producir a un vector vacio.
 * Entradas: tipo de arduino, cantidad de unidades, vector de produccion.
 * Salidas:No tiene.
 */
void insertar_produccion(string producto, int unidades, vector <produccion> &vector_produccion) {
    produccion datos;
    int band=1;
    for(int j=0; j<15; j++){
        if(tipos_de_arduino[j]==producto){
            band=2;
        }
    }
    if(band==2){
        int x=0;
        for (auto i : vector_produccion) {
            if (i.arduino == producto) {
                i.cantidad+=unidades;
                vector_produccion[x]=i;
                return;
            }
            x++;
        }
        datos.arduino = producto;
        datos.cantidad += unidades;
        vector_produccion.push_back(datos);
    }
    else{cout<<"El producto ingresado no se produce en esta fabrica."<<endl;}
}

/*
 * Funcion: Permite ver la cantidad de unidades a producir para un tipo de arduino específico.
 * Entradas: tipo de arduino a consultar, vector de produccion.
 * Salidas: tipo de arduino y cantidad a producir.
 */
void consultar_produccion(string producto, vector <produccion> &vector_produccion) {
    for (auto i: vector_produccion) {
        if(i.arduino == producto){
            cout << "Arduino: " << i.arduino << endl;
            cout << "Cantidad: " << i.cantidad << endl;
            break;
        }
        else{cout<<"Arduino no encontrado."<<endl;}
    }
}

/*
 * Funcion: Elimina las unidaddes deseadas de un producto especifico. Si estas llegan a 0, el producto se elimina.
 * Entradas: tipo de arduino, unidades a eliminar, vector produccion.
 * Salidas: No tiene.
 */
void eliminar_pedido(string producto, int unidades, vector <produccion> &vector_produccion) {
    int j=0;
    for (auto i: vector_produccion) {
        if(i.arduino==producto){
            if(i.cantidad>=unidades){
                i.cantidad-=unidades;
                if(i.cantidad==0){
                    vector_produccion.erase(vector_produccion.begin()+j);
                    cout << "Datos eliminados correctamente" << endl;
                    break;
                }
            }
            else {cout<<"ERROR: La cantidad a eliminar sobrepasa los arduinos a producir ya establecidos"<<endl;}
            vector_produccion[j]=i;
            break;
        }
        else {cout<<"Arduino no encontrado"<<endl;}
        j++;
    }
}

/*
 * Funcion: Muestra los productos que se van a fabricar.
 * Entradas: vector produccion.
 * Salidas: Productos, unidades a producir, cantidad total de productos y el porcentaje del total por producto.
 */
void consultar_total(vector <produccion> &vector_produccion) {
    int total=0;
    double porcentaje;
    cout<<"TIPO DE ARDUINO"<<left<<setw(15)<<right<<setw(20)<<"CANTIDAD"<<right<<setw(25)<<"% PRODUCCION"<<endl;
    for (auto j : vector_produccion) {
        total+=j.cantidad;
    }
    for (auto i : vector_produccion) {
        porcentaje=i.cantidad*100/total;
        cout<<left<<setw(15)<<i.arduino<<right<<setw(20)<<i.cantidad<<right<<setw(25)<<porcentaje<<endl;
    }
    cout<<left<<setw(15)<<"\nTOTAL A PRODUCIR:"<<right<<setw(18)<<total<<right<<setw(25)<<"100"<<endl;
}

/*
 * Funcion: Muestra los productos que se pueden fabricar.
 * Entradas: No tiene.
 * Salidas: productos que se pueden fabricar.
 */
void tipos_en_fabrica(){
    cout<<"\nArduinos que se producen en la fabrica:"<<endl;
    for(const auto & i : tipos_de_arduino){
        cout<<i<<endl;
    }
    cout<<endl;
}

/*
 * Funcion: Muestra la hora y fecha del computador.
 * Entradas: No tiene.
 * Salidas: No tiene.
 */
const string currentDateTime() // Función encargada de imprimir la fecha y hora actual
{
    time_t now = time(0);
    struct tm tstruct{};
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y/%m/%d - %X", &tstruct);

    return buf; // Salida: Fecha y hora.
}

//Definicion de la funcion main
int main() {
    vector <produccion> vector_produccion;
    string producto;
    int unidades;
    int opcion;
    do {
        cout << "\nFABRICA DE ARDUINOS\t"<<currentDateTime()<<endl;
        cout << "\tPRODUCCION DE ARDUINOS\n";
        cout << "\t CONTROL DE PEDIDOS\n";
        cout << "1- Insertar pedido de produccion " << endl;
        cout << "2- Consultar produccion de un arduino " << endl;
        cout << "3- Eliminar pedido de produccion " << endl;
        cout << "4- Consultar tipos de arduinos que puede producir la fabrica " << endl;
        cout << "5- Consultar produccion total " << endl;
        cout << "6- Fin" << endl;
        cout << "Opcion: " << endl;
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Insertar pedido de produccion" << endl;
                cout << "-------------------------" << endl;
                //tipos_en_fabrica();
                cin.ignore();
                cout << "Tipo de arduino: ";
                getline(cin, producto);
                cout << endl;
                cout << "Unidades: "; cin >> unidades;
                if(unidades>0){insertar_produccion(producto, unidades, vector_produccion);}
                else{cout<<"ERROR: las cantidades a producir deben ser postivas."<<endl;}
                break;
            case 2:
                cout << "Consultar produccion de un arduino" << endl;
                cout << "-------------------------" << endl;
                cout << "Tipo de arduino: " << endl;
                cin.ignore();
                getline(cin, producto);
                consultar_produccion(producto,vector_produccion);
                break;
            case 3:
                cout << "Eliminar pedido de produccion" << endl;
                cout << "-------------------------" << endl;
                cout << "Tipo de arduino: " << endl;
                cin.ignore();
                getline(cin, producto);
                cout << "Unidades: " << endl;cin>>unidades;
                eliminar_pedido(producto,unidades,vector_produccion);
                break;
            case 4:{
                cout << "Consultar tipos de arduinos que puede producir la fabrica" << endl;
                cout << "-------------------------" << endl;
                tipos_en_fabrica();}
                break;
            case 5:
                cout << "Consultar produccion total" << endl;
                cout << "-------------------------" << endl;
                consultar_total(vector_produccion);
            case 6:
                break;
            default:
                cout << "Error: La opcion no es valida." << endl;
        }
    } while (opcion != 6);
    return 0;
}
