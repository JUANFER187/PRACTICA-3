#include <iostream>
#include <cstring>
#include <limits>
#define MAX 4

using namespace std;
//----------- CLASE -------------------------------------------------
class Empleado
{
private:
    int ClaveEmpleado;
    char Nombre[20];
    char Domicilio[20];
    float Sueldo;
    char ReportaA[20];

public:
    //----------------------- OBJETO --------------------------------------------------------------------------
    Empleado() { ClaveEmpleado = 0; strcpy(Nombre, " "); strcpy(Domicilio, " "); Sueldo = 0.0; strcpy(ReportaA, " "); }
    Empleado(int ce, const char n[], const char d[], float s, const char ra[]) { ClaveEmpleado = ce; strcpy(Nombre, n); strcpy(Domicilio, d); Sueldo = s; strcpy(ReportaA, ra); }

    //------------------- SOBRECARGA DE OPERADORES -------------------------------------------------------------
    const char* ObtenerNombre() const { return Nombre; }
    bool operator == (const Empleado& otro) const { return (ClaveEmpleado == otro.ClaveEmpleado); }
    bool operator != (const Empleado& otro) const { return !(*this == otro); }
    bool operator >= (const Empleado& otro) const { return (ClaveEmpleado >= otro.ClaveEmpleado); }
    bool operator <= (const Empleado& otro) const { return (ClaveEmpleado <= otro.ClaveEmpleado); }

    friend ostream& operator << (ostream &o, const Empleado &emp)
    {
        o << "Clave: " << emp.ClaveEmpleado << endl;
        o << "Nombre: " << emp.Nombre << endl;
        o << "Domicilio: " << emp.Domicilio << endl;
        o << "Sueldo: " << emp.Sueldo << endl;
        o << "Reporta a: " << emp.ReportaA << endl;
        return o;
    }

    friend istream& operator >> (istream &i, Empleado &emp)
    {
        cout << "Clave: ";
        i >> emp.ClaveEmpleado;
        cout << "Nombre: ";
        i >> emp.Nombre;
        cout << "Domicilio: ";
        i >> emp.Domicilio;
        cout << "Sueldo: ";
        i >> emp.Sueldo;
        cout << "Reporta a: ";
        i >> emp.ReportaA;
        return i;
    }

    Empleado operator+(const Empleado& otro) const
    {
        Empleado resultado(*this);
        strcat(resultado.Nombre, " y ");
        strcat(resultado.Nombre, otro.Nombre);
        return resultado;
    }

    //----------------- MÉTODOS -------------------------------------------------
    void CambiaDomicilio(const char nuevoDomicilio[20])
    {
        cout << "\t\t\t\t------------------- CAMBIAR DOMICILIO -------------------\n" << endl;
        cout << "Ingresa nuevo domicilio del empleado: ";
        cin.ignore();
        cin.getline(Domicilio, 20);
    }

    void CambiaReportaA(const char nuevoJefe[20])
    {
        cout << "Ingresa el nombre del nuevo jefe: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignora caracteres adicionales en el buffer de entrada
        cin.getline(ReportaA, 20);

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Has ingresado más caracteres de los permitidos. El nombre se truncará a 20 caracteres..." << endl;
        }
    }

    void ActualizaSueldo(float nuevoSueldo)
    {
        Sueldo = nuevoSueldo;
    }

    bool buscarPorClave(int clave) const
    {
        return (clave == ClaveEmpleado);
    }

    void Imprime()
    {
        cout << "\t\t\t\t------------------- CONSULTA DE EMPLEADOS -------------------\n" << endl;
        cout << "Clave: " << ClaveEmpleado << endl;
        cout << "Nombre: " << Nombre << endl;
        cout << "Domicilio: " << Domicilio << endl;
        cout << "Sueldo: " << Sueldo << endl;
        cout << "Reporta a: " << ReportaA << endl;
        system("PAUSE");
        system("cls");
    }
};

//------------------------ CLASE LISTA ---------------------------------------------
template <typename T>
class ListaEstatica
{
private:
    int Tam;
    T Datos[MAX];

public:
    ListaEstatica() : Tam(0) {} // Constructor por defecto
    int Inserta(T, int); // Declaramos las funciones, implementación a continuación
    int Agrega(T);
    int Busca(T);
    int Elimina(int);
    int Llena();
    int Vacia();
    int Muestra();
};

//-------------------- Implementación de los métodos de mi clase ListaEstatica ---------------------------------

template <typename T>
int ListaEstatica<T>::Llena()
{
    return Tam >= MAX; //Devuelve TRUE si la lista está llena, FALSE si no.
}

template <typename T>
int ListaEstatica<T>::Vacia()
{
    return Tam == 0; //Devuelve TRUE si la lista está vacía, FALSE si contiene registros.
}

template <typename T>
int ListaEstatica<T>::Agrega(T dato)
{
    if (Llena())
    {
        cout << "No se pudo agregar el objeto porque la lista está llena." << endl;
        return 0;
    }

    Datos[Tam] = dato; // Añade el dato al final de la lista
    ++Tam;
    cout << "El objeto se agregó exitosamente a la lista." << endl;
    return 0;
}

template <typename T>
int ListaEstatica<T>::Busca(T dato)
{
    if (Vacia())
    {
        cout << "La lista no tiene elementos guardados aún..." << endl;
        system("PAUSE");
        return 0;
    }

    bool encontrado = false;
    int posicion = -1;

    for (int i = 0; i < Tam; ++i)
    {
        if (strcmp(Datos[i].ObtenerNombre(), dato.ObtenerNombre()) == 0)
        {
            encontrado = true;
            posicion = i;
            break; // Terminamos el bucle si encontramos una coincidencia
        }
    }

    if (encontrado)
    {
        cout << "El empleado " << dato.ObtenerNombre() << " se encuentra en la posición " << posicion << " de la lista." << endl;
        system("PAUSE");
    }
    else
    {
        cout << "No se encontraron resultados en la búsqueda..." << endl;
        system("PAUSE");
    }

    return 0;
}

template <typename T>
int ListaEstatica<T>::Elimina(int pos)
{
    if (Vacia())
    {
        cout << "La lista no tiene elementos registrados aún." << endl;
        return 0;
    }

    if (pos < 0 || pos >= Tam)
    {
        cout << "Posición inválida." << endl;
        return 0;
    }

    for (int i = pos; i < Tam - 1; ++i)
    {
        Datos[i] = Datos[i + 1]; // Desplaza los elementos a la izquierda
    }

    --Tam;
    cout << "El empleado fue eliminado exitosamente de la lista." << endl;

    return 0;
}

template <typename T>
int ListaEstatica<T>::Inserta(T dato, int pos)
{
    if (Llena())
    {
        cout << "No hay vacantes, lista llena..." << endl;
        return 0;
    }

    if (pos < 0 || pos > Tam)
    {
        cout << "Posición inválida, intente de nuevo..." << endl;
        return 0;
    }

    // Desplaza los elementos a la derecha desde la última posición ocupada hasta la posición de inserción
    for (int i = Tam; i > pos; --i) {
        Datos[i] = Datos[i - 1];
    }

    Datos[pos] = dato; // Inserta el nuevo elemento en la posición especificada
    ++Tam;
    cout << "El empleado fue insertado correctamente en la posición " << pos << " de la lista." << endl;
    return 0;
}

template <typename T>
int ListaEstatica<T>::Muestra()
{
    if (Vacia()) {
        cout << "Aún no hay empleados registrados..." << endl;
        return 0;
    }

    cout << "Datos de los empleados registrados:" << endl;
    for (int i = 0; i < Tam; ++i) { // Modificado de 'MAX' a 'Tam'
        cout << "Empleado " << i + 1 << ":" << endl;
        cout << Datos[i] << endl;
    }

    return 0;
}

//------------- OPCIONES ENUMERADAS DEL MENÚ ----------------------------------
enum OPTIONS
{
    OPT_SALIR,     //0
    OPT_AGREGA,  //1
    OPT_BUSCA,  //2
    OPT_ELIMINA,//3
    OPT_INSERTA,//4
    OPT_MUESTRA//5
};

int main()
{
    setlocale(LC_ALL, "spanish");

    ListaEstatica<Empleado> lista;
    int opt;

    //------------------ INSTANCIAS ----------------------------------------------------
    Empleado JefePlanta(123, "Dr. Pepe Pecas", "TodoVerde 443", 75000.99, "Ricardo Kaka");
    Empleado JefePersonal(456, "Mtro. Paco Cabeza", "Cerro Divino 666", 47999.49, "Dr. Pepe Pecas");

    do
    {
        system("cls");
        cout << "\t     --------------------------------------- DUNDLER MIFFLIN ---------------------------------------\n\n" << endl;
        cout << "(1) Agregar empleado.\n" << endl;
        cout << "(2) Buscar empleado.\n" << endl;
        cout << "(3) Eliminar empleado.\n" << endl;
        cout << "(4) Insertar empleado.\n" << endl;
        cout << "(5) Mostrar empleados.\n" << endl;
        cout << "(0) Salir.\n" << endl;
        cout << "Seleccione una opción: ";
        cin >> opt;

        system("cls");

        switch (opt)
        {
        case OPT_AGREGA:
        {
            Empleado empleado;
            cout << "Ingrese los datos del empleado:\n";
            cin >> empleado;
            lista.Agrega(empleado);
            break;
        }
        case OPT_BUSCA:
        {
            char nombreEmpleado[20];
            cout << "Ingrese el nombre del empleado que desea buscar: ";
            cin.ignore();
            cin.getline(nombreEmpleado, 20);
            Empleado empleadoBuscado;
            lista.Busca(Empleado(0, nombreEmpleado, "", 0.0, ""));
            break;
        }
        case OPT_ELIMINA:
        {
            int posEliminar;
            if (!lista.Vacia())
            {
                cout << "Ingrese la posición del empleado que desea eliminar: ";
                cin >> posEliminar;
                lista.Elimina(posEliminar);
            }
            else
            {
                cout << "La lista está vacía. No se puede eliminar ningún empleado." << endl;
            }
            break;
        }
        case OPT_INSERTA:
        {
            Empleado empleado;
            int pos;
            cout << "Ingrese la posición donde desea insertar al empleado: ";
            cin >> pos;
            cin >> empleado;
            lista.Inserta(empleado, pos);
            break;
        }
        case OPT_MUESTRA:
        {
            lista.Muestra();
            system("PAUSE");
            break;
        }
        case OPT_SALIR:
            cout << "\n\n\n\n\n\n\t\t\t\t\t\t\tSaliendo...\n\n\n\n" << endl;
            break;

        default:
            cout << "Opción inválida..." << endl;
            system("PAUSE");
            system("cls");
            break;
        }
    } while (opt != OPT_SALIR);

    return 0;
}
