#include <iostream>
#include <string>
#include<time.h>
#include<fstream>
using namespace std;

//struct de las preguntas 
struct pregunta{
    string texto_pregunta;
    string opciones_texto;
    int respuesta_de_opciones;
};

// struct de la lista de las preguntas que estara cada lista dentro de una mision
struct lista_preguntas{
    pregunta *pregunta;
    lista_preguntas *prox;
};

// struct de las misiones 
struct Mision
{
    string nombre; 
    string descripcion;
    int puntos_recompensa;
    int ID;
    int nivel;
    string tipo;
    lista_preguntas *preguntas;
    int num_preguntas_requeridas;
    int total_preguntas;
};

//struct de las listas de las misiones 
struct lista_Misiones
{
    Mision *mision;
    lista_Misiones *prox;
};

//struct Logro 
struct Logro
{
    string nombre;
    int puntaje;
    string descripcion;
    string distincion; 
    int fecha;
    int ID;
};

//struct de la lista de logros
struct lista_Logros
{
    Logro *logro;
    lista_Logros *prox;
};

//struct de los jugadores y cada uno tendra una lista de logros 
struct Player
{
    string nombre;
    string alias;
    int nivel;
    int puntaje_total;
    lista_Logros *logros; 
    int ID;
};

//struct de las listas de jugadores 
struct lista_Players
{
    Player *jugador;
    lista_Players *prox;
};

//struct de los perfiles y cada uno tendra una lista de jugadores 
struct Perfil
{
    string nombre;
    string contrasena;
    lista_Players *jugadores;
    int ID;
};

//struct de la lista de los diferentes perfiles que hay
struct lista_Perfiles
{
    Perfil *perfil;
    lista_Perfiles *prox;
};

// crea la pregunta y le asigna los datos 
pregunta *CrearPregunta(string texto_pregunta, string opciones_texto, int respuesta_de_opciones) {
    pregunta *nuevaPregunta = new pregunta;
    nuevaPregunta->texto_pregunta = texto_pregunta;
    nuevaPregunta->opciones_texto = opciones_texto;
    nuevaPregunta->respuesta_de_opciones = respuesta_de_opciones;
    return nuevaPregunta;
}

//agrega la pregunta a una lista de preguntas (se utiliza para meter una pregunta a una lista de preguntas dentro de cada mision)
void AgregarPreguntaAListaPreguntas(lista_preguntas **cabeza_lista_preguntas, pregunta *preguntaAAgregar) {
    lista_preguntas *nuevoNodo = new lista_preguntas;
    nuevoNodo->pregunta = preguntaAAgregar;
    nuevoNodo->prox = NULL;

    if (*cabeza_lista_preguntas == NULL) {
        *cabeza_lista_preguntas = nuevoNodo;
    } else {
        lista_preguntas *temp = *cabeza_lista_preguntas;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = nuevoNodo;
    }
}
 
//crea una mision y se le asignan los datos 
Mision *CrearMision(string nombre, string descripcion, string tipo, int num_preguntas_requeridas, int puntos_recompensa, int ID, int nivel , int preguntasTotales)
{
    Mision *nuevo = new Mision;
    nuevo->nombre = nombre;
    nuevo->descripcion = descripcion;
    nuevo->num_preguntas_requeridas = num_preguntas_requeridas;
    nuevo->puntos_recompensa = puntos_recompensa;
    nuevo->ID = ID;
    nuevo->tipo = tipo;
    nuevo->nivel = nivel;
    nuevo->preguntas = NULL;
    nuevo->total_preguntas = preguntasTotales ;
    return nuevo;
}

//Es una funcion que retorna la fecha en el momento al que se llama la funcion 
int fecha(){
    time_t now =time(0);
    tm *ltm = localtime(&now);
    int year = (1900+ltm->tm_year);
    int month = (1 + ltm->tm_mon);
    int day = (ltm->tm_mday);
    int dia = day*1000000;
    int mes = month*10000;
    int fecha = dia+mes+year;
    return fecha;
    
}

//se le asigna una nueva mision al final de la lista de las misiones
void AgregrarListaMision(lista_Misiones **lista, Mision *nuevamision)
{
    lista_Misiones *nuevo = new lista_Misiones;
    if (*lista == NULL)
    {
        nuevo->mision = nuevamision;
        nuevo->prox = *lista;
        *lista = nuevo;
    }
    else
    {
        lista_Misiones *aux = *lista;
        if (aux->prox == NULL)
        {
            nuevo->mision = nuevamision;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
        else
        {
            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            nuevo->mision = nuevamision;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
    }
}

//crea un logro y se le asignan los valores 
Logro *CrearLogro(string nombre, int puntaje, string descripcion, string distincion, int ID,int fecha)
{
    Logro *nuevo = new Logro;
    nuevo->nombre = nombre;
    nuevo->puntaje = puntaje;
    nuevo->descripcion = descripcion;
    nuevo->distincion = distincion;
    nuevo->ID = ID;
    nuevo->fecha= fecha;
    return nuevo;
}

// crea un jugador y se le asignan los valores 
Player *CrearPlayer(string nombre, string alias,int ID)
{
    Player *nuevo = new Player;
    nuevo->nombre = nombre;
    nuevo->alias = alias;
    nuevo->nivel = 1;
    nuevo->puntaje_total = 1;
    nuevo->logros = NULL;
    nuevo->ID=ID;
    return nuevo;
}

// crea un perfil y dentro del perfil pueden haber multiples jugadores
Perfil *CrearPerfil(string nombre, string contraseña, int ID)
{
    Perfil *nuevo = new Perfil;
    nuevo->nombre = nombre;
    nuevo->contrasena = contraseña;
    nuevo->jugadores = NULL;
    nuevo->ID= ID;
    return nuevo;
}

// agrega un jugador al final de la lista de jugadores
void AgregarListaJugadores(lista_Players **lista)
{
    string nombre, alias;int ID;
    cout << "Introduzca el nombre del jugador: ";
    getline(cin,nombre);
    cout << "Introduzca el alias del jugador: ";
    getline(cin,alias);
    cout << "introduza el ID del Jugador" << endl;
    while (true){
        cout << "introduzca el ID del perfil: " << endl;
        cin>>ID;
        if (cin.fail()){
            cout << "Entrada invalida introduce un numero para el ID" << endl;
            cin.clear();
            cin.ignore(200,'\n');
        }
        else{
            break;
        }
    }
    cin.ignore(200,'\n');
    Player *nuevoplayer = CrearPlayer(nombre, alias,ID);
    lista_Players *nuevo = new lista_Players;
    if (*lista == NULL)
    {
        nuevo->jugador = nuevoplayer;
        nuevo->prox = *lista;
        *lista = nuevo;
    }
    else
    {
        lista_Players *aux = *lista;
        if (aux->prox == NULL)
        {
            nuevo->jugador = nuevoplayer;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
        else
        {
            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            nuevo->jugador = nuevoplayer;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
    }
}

//elimina un jugador dentro del perfil 
void EliminarJugador(lista_Players **lista)
{
    if (*lista == NULL)
    {
        cout << "La Lista esta vacia" << endl;
        return;
    }
    lista_Players *mover = *lista;
    lista_Players *aux = NULL;
    string alias;
    cout << "Introduzca el alias del jugador a eliminar: ";
    getline(cin,alias);
    while (mover != NULL)
    {
        if (mover->jugador->alias == alias)
        {
            if (aux == NULL)
            {
                *lista = mover->prox;
            }
            else
            {
                aux->prox = mover->prox;
            }
            lista_Logros *logrosActual = mover->jugador->logros;
            while (logrosActual != NULL) {
                lista_Logros *tempLogro = logrosActual;
                logrosActual = logrosActual->prox;
                delete tempLogro->logro; 
                delete tempLogro;         
            }
            delete mover->jugador; 
            delete mover;
            return;
        }
        aux = mover;
        mover = mover->prox;
    }
    cout << "No se encontro un jugador con ese alias" << endl;
}
// Agrega un logro a una lista de logros, (al final)
void AgregrarListaLogro(lista_Logros **lista, Logro *nuevologro)
{
    lista_Logros *nuevo = new lista_Logros;
    if (*lista == NULL)
    {
        nuevo->logro = nuevologro;
        nuevo->prox = *lista;
        *lista = nuevo;
    }
    else
    {
        lista_Logros *aux = *lista;
        if (aux->prox == NULL)
        {
            nuevo->logro = nuevologro;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
        else
        {
            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            nuevo->logro = nuevologro;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
    }
}

// Se le agrega un logro manual a un jugador en especifico
void AgregarLogroManualAJugador(Player **jugador) {
    if (*jugador == NULL) {
        cout << "Error: No se ha seleccionado un jugador activo." << endl;
        return;
    }

    string nombre, descripcion, distincion;
    int puntaje, id_logro;

    int nextID; 

if ((*jugador)->logros != NULL) { 

    lista_Logros *temp = (*jugador)->logros;
    while (temp->prox != NULL) { 
        temp = temp->prox;
    }
    nextID = temp->logro->ID + 1; 
} else { 
    nextID = 1;
    }
    cout << "Ingrese el nombre del logro: ";
    getline(cin, nombre);

    cout << "Ingrese la descripcion del logro: ";
    getline(cin, descripcion);

    cout << "Ingrese la distincion del logro (ej. Bronce, Plata, Oro, Especial): ";
    getline(cin, distincion);

    cout << "Ingrese el puntaje asociado a este logro: ";
    cin >> puntaje;
    cin.ignore();

    
    int fecha1=fecha();
    id_logro = nextID; 

    Logro *nuevoLogro = CrearLogro(nombre, puntaje, descripcion, distincion, id_logro,fecha1);
    AgregrarListaLogro(&(*jugador)->logros, nuevoLogro);

    cout << "logro agregado correctamente" << endl;
}

// Esta funcion verifica si un jugador ya tiene un logro (se utiliza para no poner dos logros iguales a un jugador)
bool ExisteLogroJugador(Player *jugador,string nombre_logro){
    if (jugador->logros==NULL){
        return false;
    }
    else{
        lista_Logros *actual=jugador->logros;
        while (actual!=NULL){
            if (actual->logro->nombre==nombre_logro){
                return true;
            }
            else{
                actual=actual->prox;
            }
        }
        return false;
    }

}

// Este procedimiento lo que hace es que crea un logro y dependiendo de como le haya ido al jugador en la mision se le agrega a su lista de logros o se queda como esta, tambien verifica si el logro ya existe en el jugador.
void AgregarLogrosAutomaticosMision(Player **jugador, int nivel_jugador, int puntaje_mision) {
    if (*jugador == NULL) {
        cout << "Error: Jugador no encontrado para asignar logros automaticos." << endl;
        return;
    }

    int nextID; 

    if ((*jugador)->logros != NULL) {
        lista_Logros *temp = (*jugador)->logros;
        while (temp->prox != NULL) {
            temp = temp->prox; 
        }
        nextID = temp->logro->ID + 1; 
    } else {
        nextID = 1;
    }


    if (puntaje_mision < 3) {
        cout << "No se ha alcanzado el puntaje minimo (3) para obtener logros en esta mision." << endl;
        return;
    }
int fecha1;

if (nivel_jugador == 2 && !ExisteLogroJugador(*jugador,"Logro Bronce")) { 
    fecha1=fecha();
    Logro *nuevoLogro = CrearLogro("Logro Bronce", puntaje_mision, "¡Felicitaciones! Has alcanzado el nivel Bronce (Facil).", "Bronce", nextID++,fecha());
    AgregrarListaLogro(&(*jugador)->logros, nuevoLogro);
    cout << "-> Logro 'Logro Bronce' anadido." << endl;
} else if (nivel_jugador == 3 && !ExisteLogroJugador(*jugador,"Logro Plata")) {
    fecha1=fecha(); 
    Logro *nuevoLogro = CrearLogro("Logro Plata", puntaje_mision, "¡Felicitaciones! Has alcanzado el nivel Plata (Intermedio).", "Plata", nextID++,fecha());
    AgregrarListaLogro(&(*jugador)->logros, nuevoLogro);
    cout << "-> Logro 'Logro Plata' anadido." << endl;
} else if (nivel_jugador >= 4 && !ExisteLogroJugador(*jugador,"Logro Oro")) { 
    fecha1=fecha();
    Logro *nuevoLogro = CrearLogro("Logro Oro", puntaje_mision, "¡Felicitaciones! Has alcanzado el nivel Oro (Avanzado).", "Oro", nextID++,fecha());
    AgregrarListaLogro(&(*jugador)->logros, nuevoLogro);
    cout << "-> Logro 'Logro Oro' anadido." << endl;
}


if (puntaje_mision == 4) {
    if (nivel_jugador == 2 && !ExisteLogroJugador(*jugador,"Logro experto en Bronce")) { 
        fecha1=fecha();
        Logro *nuevoLogro2 = CrearLogro("Logro experto en Bronce", puntaje_mision, "Felicidades por obtener el puntaje perfecto en una mision de Nivel Facil!", "Bronce", nextID++,fecha1);
        AgregrarListaLogro(&(*jugador)->logros, nuevoLogro2);
        cout << "-> Logro 'Logro experto en Bronce' anadido." << endl;
    } else if (nivel_jugador == 3 && !ExisteLogroJugador(*jugador,"Logro experto en Plata")) { 
        fecha1=fecha();
        Logro *nuevoLogro2 = CrearLogro("Logro experto en Plata", puntaje_mision, "Felicidades por obtener el puntaje perfecto en una mision de Nivel Intermedio!", "Plata", nextID++,fecha1);
        AgregrarListaLogro(&(*jugador)->logros, nuevoLogro2);
        cout << "-> Logro 'Logro experto en Plata' anadido." << endl;
    } else if (nivel_jugador == 4 && !ExisteLogroJugador(*jugador,"Logro experto en Oro") ) { 
        fecha1=fecha();
        Logro *nuevoLogro2 = CrearLogro("Logro experto en Oro", puntaje_mision, "Felicidades por obtener el puntaje perfecto en una mision de Nivel Avanzado!", "Oro", nextID++,fecha());
        AgregrarListaLogro(&(*jugador)->logros, nuevoLogro2);
        cout << "-> Logro 'Logro experto en Oro' anadido." << endl;
    }
}   
else {
    cout << "No se otorgaron logros adicionales por el puntaje (requiere 4 puntos)." << endl;
}
    if (puntaje_mision == 8 && !ExisteLogroJugador(*jugador,"Logro experto en Estructura De Datos")){
        fecha1=fecha();
    Logro *nuevoLogroAleatorio= CrearLogro("Logro experto en Estructura De Datos" , puntaje_mision, "Felicitaciones! Eres un experto en la materia ESTRUCTURA DE DATOS por obtener puntaje perfecto" , "experto" , nextID++,fecha());
    AgregrarListaLogro(&(*jugador)->logros,nuevoLogroAleatorio);
    cout << "-> Logro experto en Estructuras De Datos anadido" << endl;
    }   
}

// esta funcion retorna el logro que se esta pidiendo, lo busca por la lista de logros y lo retorna.
Logro *seleccionarLogro(lista_Logros *listaLogros){
    lista_Logros *mover = listaLogros;
    int ID;
    if (listaLogros == NULL){
        cout << "No hay logros disponibles" << endl;
        return NULL;
    }
    cout << "introduzca el ID del logro a seleccionar: ";
    while (true){
        cout << "introduzca el ID del perfil: " << endl;
        cin>>ID;
        if (cin.fail()){
            cout << "Entrada invalida introduce un numero para el ID" << endl;
            cin.clear();
            cin.ignore(200,'\n');
        }
        else{
            break;
        }
    }
    cin.ignore(200,'\n');    
    while (mover != NULL){
        if (mover->logro->ID == ID){
            cout << "Logro seleccionado: " << mover->logro->nombre << endl;
            return mover->logro;
        }
        mover = mover->prox;
    }
    cout << "No se encontro el logro" << endl;
    return NULL;
}

// Este procedimiento lo que hace es modificar cualquier logro dentro de la lista de logros
void actualizarLogros(lista_Logros **listalogros){
    Logro *logro=seleccionarLogro(*listalogros);
    if (logro != NULL){
        cout << "Introduzca el nuevo puntaje: ";
        cin >> logro->puntaje;
        cin.ignore();
        cout << "Introduzca la nueva descripcion: ";
        getline(cin,logro->descripcion);
        cout << "Introduzca la nueva distincion: ";
        getline(cin,logro->distincion);

    }
    else{
        cout << "no se pudo actualizar o modificar el logro ya que no se encuentra en la lista de logros"<< endl;
    }
}

// Este procedimiento lo que hace es buscar el perfil dentro de la lista de perfiles y si lo encuentra poder modificarlo
void ActualizarPerfil(lista_Perfiles **perfiles){
    lista_Perfiles *perfilaux=*perfiles;
    if (*perfiles == NULL){
        cout << "no hay perfiles registrados para actualizar " << endl;
    }
    else{
        string nombre;
        cout << "cual el nombre del perfil a cambiar: " << endl;
        getline(cin,nombre);

        while (perfilaux !=NULL && perfilaux->perfil->nombre != nombre){
            perfilaux=perfilaux->prox;
        }
        if (perfilaux==NULL){
            cout << "perfil no encontrado para actualizar" << endl;
        }
        else{
            int opc;
            cout << "deseas cambiar el nombre? 1)si 2)no" << endl;
            cin>>opc;
            if (cin.fail()) { 
                cout << "Entrada invalida. Asumimos que no quiere cambiar el nombre" << endl;
                cin.clear();
                char c;
                while (cin.get(c) && c != '\n');
                opc=2;
                } else {
                char c;
                while (cin.get(c) && c != '\n');
                }
            if(opc==1) {
                string nombre;
                cout << "ingresa el nuevo nombre: " << endl;
                getline(cin,nombre);
                perfilaux->perfil->nombre=nombre;
                cout << "nombre cambiado a: " << nombre << endl;
            }
            if (opc!=1 && opc!=2){
                cout << "valor erroneo intente de nuevo " << endl;
            }
            int opc2;
            cout << "desea cambiar la contrasena? 1)si 2)no " << endl;
            cin >> opc2;
                if (cin.fail()) { 
                cout << "Entrada invalida. Asumimos que no quiere cambiar la contrasena" << endl;
                cin.clear();
                char c;
                while (cin.get(c) && c != '\n');
                opc2=2;
                
                } else {
                char c;
                while (cin.get(c) && c != '\n');
                }

            if (opc2==1){
                string contrasena;
                cout << "ingresa la nueva contrasena: " << endl;
                getline(cin,contrasena);
                perfilaux->perfil->contrasena=contrasena;
                cout << "contrasena cambiada a: " << contrasena << endl;
                }
                else{
                    if (opc2!=1 && opc2!=2){
                        cout << "valor erroneo intente de nuevo " << endl;
                    }
                    else{
                        cout << "saliendo de actualizar perfil..." << endl;
                    }
                }
            }
        }

     }

// Este procedimiento lo que hace es mostrar la lista de jugadores que en este caso la lista de jugadores que puede tener un perfil.
void MostrarListaJugadores(lista_Players *lista)
{
    if (lista == NULL)
    {
        cout << "No hay jugadores creados" << endl;
        return;
    }
    lista_Players *mover = lista;
    while (mover != NULL)
    {
        cout << "Jugador: " << mover->jugador->alias << " nivel:" << mover->jugador->nivel << "ID: " <<  mover->jugador->ID << endl;
        mover = mover->prox;
    }
}

// Esta funcion lo que hace es retornar un jugador o seleccion un jugador que es con el que voy a ejecutar las misiones o preguntar por sus logros, puntaje etc..
Player *SeleccionarJugador(lista_Players *lista)
{
    lista_Players *mover = lista;
    string alias;
    cout << "Introduzca el alias de su personaje: ";
    getline(cin,alias);
    while (mover != NULL)
    {
        if (alias == mover->jugador->alias)
        {
            cout << "Jugador Seleccionado: " << mover->jugador->alias << endl;
            return mover->jugador;
        }
        mover = mover->prox;
    }
    cout<< "jugador no enontrado " << endl;
    return NULL;
}

// Este procedimiento lo que hace es que busca un jugador de una lista de jugadores y muestra sus datos(nommbre,nivel,puntaje).
void DatosPlayer(lista_Players *lista)
{
    Player *jugador = SeleccionarJugador(lista);
    if (jugador == NULL)
    {
        cout << "No se encontro el jugador" << endl;
        return;
    }
    cout << "Nombre de jugador: " << jugador->nombre << endl;
    cout << "El Jugador esta en el nivel: " << jugador->nivel << endl;
    cout << "El puntaje del jugador es: " << jugador->puntaje_total << endl;
}

// Este procedimiento lo que hace es que consulta las estadisticas de una lista de jugadores de un perfil.
void consultarEstadisticas(lista_Players *ListaJugadores) {
    if (ListaJugadores == NULL) {
        cout << "No hay jugadores creados." << endl;
        return; 
    }

    int estadistica;
    cout << "Que estadisticas quisieras consultar?" << endl;
    cout << "  1) Jugador con mas puntos" << endl;
    cout << "  2) Jugador con menos puntos" << endl;
    cout << "  3) Jugador con mas nivel" << endl;
    cout << "  4) Jugador con menos nivel" << endl;
    cout << "Ingrese su opcion: ";
    cin >> estadistica;
    cin.ignore();

    lista_Players *actual = ListaJugadores;

    int mayorPuntos = actual->jugador->puntaje_total;
    int menorPuntos = actual->jugador->puntaje_total;
    int mayorNivel = actual->jugador->nivel;
    int menorNivel = actual->jugador->nivel;

    Player *jugadorMasPuntos = actual->jugador;
    Player *jugadorMenosPuntos = actual->jugador;
    Player *jugadorMasNivel = actual->jugador;
    Player *jugadorMenosNivel = actual->jugador;

    
    while (actual != NULL) {
        if (actual->jugador->puntaje_total > mayorPuntos) {
            mayorPuntos = actual->jugador->puntaje_total;
            jugadorMasPuntos = actual->jugador;
        }
        if (actual->jugador->puntaje_total < menorPuntos) {
            menorPuntos = actual->jugador->puntaje_total;
            jugadorMenosPuntos = actual->jugador;
        }
        if (actual->jugador->nivel > mayorNivel) {
            mayorNivel = actual->jugador->nivel;
            jugadorMasNivel = actual->jugador;
        }
        if (actual->jugador->nivel < menorNivel) {
            menorNivel = actual->jugador->nivel;
            jugadorMenosNivel = actual->jugador;
        }
        actual = actual->prox;
    }
    cout << endl; 
    switch (estadistica) {
        case 1:
            cout << "Jugador con mas puntos es: " << jugadorMasPuntos->alias << " Puntaje: " << mayorPuntos << "" << endl;
            break;
        case 2:
            cout << "Jugador con menos puntos es: " << jugadorMenosPuntos->alias << " Puntaje: " << menorPuntos << "" << endl;
            break;
        case 3:
            cout << "Jugador con mas nivel es: " << jugadorMasNivel->alias << " Nivel: " << mayorNivel << "" << endl;
            break;
        case 4:
            cout << "Jugador con menos nivel es: " << jugadorMenosNivel->alias << " Nivel: " << menorNivel << "" << endl;
            break;
        default:
            cout << "Opcion de estadistica no valida." << endl;
            break;
    }
}


/*Esta funcion lo que hace es retornar una mision, 
comparando el nivel del jugador con el nivel de la mision y mostrando las misiones que si puede jugar incluyendo los logros que puede obtener si la gana.
Despues pregunta por el ID de la mision que desea jugar el jugador y retorna esa mision.*/

Mision *seleccionarMision(lista_Misiones *listaMisiones, Player *jugadorActual) {
    if (listaMisiones == NULL) {
        cout << "No hay misiones disponibles para seleccionar." << endl;
        return NULL;
    }
    if (jugadorActual == NULL) {
        cout << "Error: No se ha seleccionado un jugador activo." << endl;
        return NULL;
    }

    cout << " Misiones Disponibles para tu nivel: " << jugadorActual->nivel << endl;
    lista_Misiones *actual = listaMisiones;

    while (actual != NULL) {
        if (jugadorActual->nivel >= actual->mision->nivel) { 
            cout << "ID: " << actual->mision->ID
                 << " Nombre: " << actual->mision->nombre
                 << " Nivel Requerido: " << actual->mision->nivel
                 << " Recompensa: " << actual->mision->puntos_recompensa << " puntos" << endl;
            cout << " posibles logros a ganar: " << endl;

            if (actual->mision->nivel == 1 && !ExisteLogroJugador(jugadorActual, "Logro Bronce")) {
                cout << "Logro Bronce (Nivel 1)"<< endl;
            } 
            
            if (actual->mision->nivel == 2 && !ExisteLogroJugador(jugadorActual, "Logro Plata")) {
                cout << "Logro Plata (Nivel 2)" << endl;
            } 
            
            if (actual->mision->nivel >= 3 && !ExisteLogroJugador(jugadorActual, "Logro Oro")) {
                cout << "Logro Oro (Nivel >=3)" << endl;
            }

            if (actual->mision->nivel == 1 && !ExisteLogroJugador(jugadorActual, "Logro experto en Bronce")) {
                cout << "Logro experto en Bronce (Nivel 2, con 4 pts)" << endl;
            } 
            
            if (actual->mision->nivel == 2 && !ExisteLogroJugador(jugadorActual, "Logro experto en Plata")) {
                cout << "Logro experto en Plata (Nivel 3, con 4 pts)" << endl;
            } 
            
            if (actual->mision->nivel == 3 && !ExisteLogroJugador(jugadorActual, "Logro experto en Oro")) {
                cout << "Logro experto en Oro (Nivel 4, con 4 pts)" << endl;
            }
            if (actual->mision->ID==7721 && !ExisteLogroJugador(jugadorActual,"Logro experto en Estructura De Datos")){
                cout << "logro experto en Estructura De Datos (nivel 6) " << endl;
            }

        }
        actual = actual->prox;
    }

 
    

    int id_seleccionado;
    cout << " Introduce el ID de la mision que quieres hacer: " << endl;
    cin >> id_seleccionado;
    cin.ignore(); 

    actual = listaMisiones; 
    while (actual != NULL) {
        if (actual->mision->ID == id_seleccionado) {
            if (jugadorActual->nivel >= actual->mision->nivel) { 
                cout << "Has seleccionado la mision: " << actual->mision->nombre << endl;
                return actual->mision;
            } else {
                cout << "La mision '" << actual->mision->nombre << "' requiere un nivel superior ("
                     << actual->mision->nivel << " Tu nivel actual es " << jugadorActual->nivel << endl;
                return NULL;
            }
        }
        actual = actual->prox;
    }

    cout << "No se encontro una mision con el ID " << id_seleccionado << endl;
    return NULL;
}

/*Esta funcion lo que hace es rotornar un boleano dependiendo si pudo completar la mision o no,
si la completo lo que se hace es asignarle los puntos y si puedo pasar el requerimiento para pasar de nivel tambien se le cambia el nivel,
tambien se llama a la funcion de asignar logros para ver que logros obtiene dependiendo se su puntaje en la mision*/

bool ejecutarMision(Mision *mision, Player *jugadorActual) {
    if (mision == NULL) {
        cout << "Error: La mision no existe." << endl;
        return false;
    }
    if (jugadorActual == NULL) {
        cout << "Error: No hay un jugador activo." << endl;
        return false;
    }

    if (jugadorActual->nivel < mision->nivel) {
        cout << "no puedes realizar esta mision porque no tienes los puntos necesarios" << endl;
        return false;
    }

    if (mision->preguntas == NULL) {
        cout << "La mision '" << mision->nombre << "' no tiene preguntas" << endl;
        return false;
    }
    cout << "mision iniciada" << endl;
    cout << "Descripcion: " << mision->descripcion << endl;
    cout << "Nivel de dificultad: " << mision->nivel << endl;
    cout << "Necesitas responder correctamente " << mision->num_preguntas_requeridas
         << " de " << mision->total_preguntas << " preguntas para completar la mision." << endl;
    cout << "---------------------------------------" << endl;

    int respuestasCorrectas = 0;
    int preguntasRespondidas = 0;
    lista_preguntas *preguntaActual = mision->preguntas;

    while (preguntaActual != NULL && preguntasRespondidas < mision->total_preguntas) {
        cout << " Pregunta " << (preguntasRespondidas + 1) << " ---" << endl;
        cout << "===============================================" << endl;
        cout << preguntaActual->pregunta->texto_pregunta << endl;
        cout << "===============================================" << endl;
        cout << "Opciones: " << "\n" << preguntaActual->pregunta->opciones_texto << endl; 
        cout << "--------------------------------------------------------------" << endl;

        int respuestaUsuario;
        cout << "Tu respuesta (numero de opcion): ";
        cin >> respuestaUsuario;
        if (cin.fail()) { 
        cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
        cin.clear();
        char c;
        while (cin.get(c) && c != '\n'){ 
        respuestaUsuario=99999;
        } 
        }else {
        char c;
        while (cin.get(c) && c != '\n');
        }



        if (respuestaUsuario == preguntaActual->pregunta->respuesta_de_opciones) {
            cout << "Respuesta correcta!" << endl;
            respuestasCorrectas++;
        } else {
            cout << "Respuesta incorrrecta.. La respuesta correcta era: " << preguntaActual->pregunta->respuesta_de_opciones << endl;
        }

        preguntasRespondidas++;
        preguntaActual = preguntaActual->prox;
    }

    cout << " RESULTADOS DE LA MISION: " << mision->nombre << endl;
    cout << "Total de preguntas respondidas: " << preguntasRespondidas << endl;
    cout << "Respuestas correctas: " << respuestasCorrectas << endl;
    cout << "Preguntas requeridas para aprobar: " << mision->num_preguntas_requeridas << endl;

    if (respuestasCorrectas >= mision->num_preguntas_requeridas) {
        cout << " Has completado la mision " << mision->nombre << "'." << endl;
        jugadorActual->puntaje_total += mision->puntos_recompensa; 

        if (jugadorActual->puntaje_total >= (jugadorActual->nivel + 1) * 50) { 
             jugadorActual->nivel++;
             cout << "Felicidades Has subido al nivel " << jugadorActual->nivel << "!" << endl;
        }

        cout << "Recompensa obtenida: " << mision->puntos_recompensa << " puntos." << endl;
        cout << "Tu nuevo puntaje total es: " << jugadorActual->puntaje_total << endl;
        cout << "Tu nivel actual es: " << jugadorActual->nivel << endl;

        AgregarLogrosAutomaticosMision(&jugadorActual, jugadorActual->nivel, respuestasCorrectas);
        
        return true;
    } else {
        cout << " No has logrado completar la mision. Necesitas mas respuestas correctas." << endl;
        cout << "!intentalo de nuevo mas tarde!" << endl;
        return false;
    }
}


// Esta funcion lo que hace es que muestra los logros de una lista de logros (se utiliza para mostrar los logros de un jugador pasandole como parametro jugador->logros)
void MostrarListaLogros(lista_Logros *lista) {
    if (lista == NULL) {
        cout << "Este jugador no tiene logros registrados." << endl;
        return;
    }
    cout << " Logros disponibles: " << endl;
    lista_Logros *mover = lista;
    while (mover != NULL) {
        cout << "  Nombre: " << mover->logro->nombre << endl;
        cout << "  ID: " << mover->logro->ID << endl;
        cout << "  Puntaje: " << mover->logro->puntaje << endl;
        cout << "  Descripcion: " << mover->logro->descripcion << endl;
        cout << "  Distincion: " << mover->logro->distincion << endl;
        cout << " fecha de obtencion: " << mover->logro->fecha << endl;
        cout << "------------------------" << endl;
        mover = mover->prox;
    }
}

// Esta funcion lo que hace es mostrar la lista de Perfiles de todo el juego 
void MostrarListaPerfiles(lista_Perfiles *lista) {
    if (lista == NULL) {
        cout << "No hay perfiles de usuario registrados." << endl;
        return;
    }
    cout << " Perfiles de Usuario " << endl;
    lista_Perfiles *mover = lista;
    while (mover != NULL) {
        cout << "  Nombre de Perfil: " << mover->perfil->nombre << endl;
        cout << "  Contrasena: " << mover->perfil->contrasena << endl;
        cout << "  ID: " << mover->perfil->ID << endl;
        cout << " Jugadores asociados a este perfil " << endl;
        MostrarListaJugadores(mover->perfil->jugadores);
        cout << "---------------------------------------" << endl;
        mover = mover->prox;
    }
}

/*Esta funcion pregunta por un perfil a eliminar, tambien antes de eliminar el perfil elimina todo lo que esta adentro de ese perfil,
todos sus jugadores que contiene y todos sus logros para que no queden direcciones de memoria en el vacio*/
void EliminarPerfil(lista_Perfiles **lista) {
    if (*lista == NULL) {
        cout << "La lista de perfiles esta vacia." << endl;
        return;
    }

    string nombrePerfilAEliminar;
    cout << "Introduzca el nombre del perfil a eliminar: ";
    getline(cin,nombrePerfilAEliminar);

    lista_Perfiles *mover = *lista;
    lista_Perfiles *aux = NULL; 

    while (mover != NULL) {
        if (mover->perfil->nombre == nombrePerfilAEliminar) {
            if (aux == NULL) {
                *lista = mover->prox;
            } else {
                aux->prox = mover->prox;
            }
            
            lista_Players *jugadoresActual = mover->perfil->jugadores;
            while (jugadoresActual != NULL) {
                lista_Players *tempJugador = jugadoresActual;
                lista_Logros *logrosActual = tempJugador->jugador->logros;
                while (logrosActual != NULL) {
                    lista_Logros *tempLogro = logrosActual;
                    logrosActual = logrosActual->prox;
                    delete tempLogro->logro; 
                    delete tempLogro;        
                }
                delete tempJugador->jugador; 
                jugadoresActual = jugadoresActual->prox;
                delete tempJugador;          
            }

            delete mover->perfil; 
            delete mover;         
            cout << "Perfil '" << nombrePerfilAEliminar << "' eliminado exitosamente." << endl;
            return;
        }
        aux = mover;
        mover = mover->prox;
    }
    cout << "No se encontro un perfil con el nombre '" << nombrePerfilAEliminar << "'." << endl;
}

//Esta funcion lo que hace es crear un perfil nuevo y lo agrega al final de una lista de perfiles
void AgregarListaPerfiles(lista_Perfiles **lista)
{
    string nombre, contrasena;int ID;
    cout << "Introduzca el nombre del perfil:";
    getline(cin,nombre);
    cout << "Introduzca la contrasena del jugador:";
    getline(cin,contrasena);
    while (true){
        cout << "introduzca el ID del perfil: " << endl;
        cin>>ID;
        if (cin.fail()){
            cout << "Entrada invalida introduce un numero para el ID" << endl;
            cin.clear();
            cin.ignore(200,'\n');
        }
        else{
            break;
        }
    }
    cin.ignore(200,'\n');

    
    Perfil *nuevoperfil = CrearPerfil(nombre, contrasena,ID);
    lista_Perfiles *nuevo = new lista_Perfiles;
    if (*lista == NULL)
    {
        nuevo->perfil = nuevoperfil;
        nuevo->prox = *lista;
        *lista = nuevo;
    }
    else
    {
        lista_Perfiles *aux = *lista;
        if (aux->prox == NULL)
        {
            nuevo->perfil = nuevoperfil;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
        else
        {
            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            nuevo->perfil = nuevoperfil;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
    }
}

// Esta funcion lo que hace es preguntar por un perfil y retornarlo 
Perfil *SeleccionarPerfil(lista_Perfiles *lista)
{
    lista_Perfiles *mover = lista;
    string nombre;
    cout << "Introduzca el nombre del perfil : ";
    getline(cin,nombre);
    while (mover != NULL)
    {
        if (nombre == mover->perfil->nombre)
        {
            cout << "Perfil Seleccionado: " << mover->perfil->nombre << endl;
            return mover->perfil;
        }
        mover = mover->prox;
    }
    return NULL;
}

// Esta funcion lo que hace es que viendo si el jugador esta en la lista de perfiles te pregunta el nombre y la contrasena para acceder a el, retorna un booleano dependiendo si pudo entrar o no
bool IngresarPerfil(lista_Perfiles *lista)
{
    Perfil *aux = SeleccionarPerfil(lista);
    if (aux == NULL)
    {
        return false;
    }
    string contrasena;
    int n = 3;
    while (n != 0)
    {
        cout << "Ingrese su contrasena" << endl;
        getline(cin,contrasena);
        if (aux->contrasena == contrasena)
        {
            cout << "Contrasena correcta";
            return true;
        }
        cout << "Contrasena incorrecta " << n - 1 << " Intentos posibles" << endl;
        n--;
    }
        cout << "Intentos posibles excedidos. Perfil bloqueado. Cree un nuevo perfil";
        return false;
}

/*Esta funcion lo que hace es que agrega un jugador a una lista de jugadores que es el Leaderboard(agregas los jugadores al final de la lista (despues con una funcion la lista se ordena))*/
void AgregarJugadoresListaLeaderboard(lista_Players **listaleaderboard, Player *jugador){
    lista_Players *nuevo= new lista_Players;
    nuevo->jugador=jugador;
    nuevo->prox=NULL;
    if (*listaleaderboard==NULL){
        *listaleaderboard=nuevo;
        nuevo->prox=NULL;
    }
    else{
        lista_Players *actual = *listaleaderboard;
        while (actual->prox!=NULL){
            actual =actual->prox;       
        }
        actual->prox=nuevo;
        nuevo->prox=NULL;
    }
}

/* Aqui lo que se utiliza es un algoritmo de ordenamiento (BubbleSort) para ordenar la lista del leaderboard,
se ordena de manera ascendente y la condicion para ordenarlo es el puntaje del jugador y si el puntaje es el mismo compara los niveles*/
void OrdenarListaLeaderBoard(lista_Players **listaleaderBoard){
    if (*listaleaderBoard==NULL || (*listaleaderBoard)->prox==NULL){
        return;
    }
    lista_Players *actual=*listaleaderBoard;
    lista_Players *anterior=NULL;
    bool cambio=true;

    while (cambio){
        cambio=false;
        actual=*listaleaderBoard;
        
        while (actual->prox!=anterior){
            Player *jugador1=actual->jugador;
            Player *jugador2=actual->prox->jugador;
            bool cambiar=false;
            if (jugador1->puntaje_total<jugador2->puntaje_total){
                cambiar = true;
            }
            else if(jugador1->puntaje_total==jugador2->puntaje_total && jugador1->nivel<jugador2->nivel){
                cambiar = true;
            }

            if (cambiar==true){
                Player *tempjugador = actual->jugador;
                actual->jugador=actual->prox->jugador;
                actual->prox->jugador=tempjugador;
                cambio=true;
            }
            actual=actual->prox;
        }
        anterior=actual;
    }
}

/*Este procedimiento lo que hace es mostrar la lista del leaderboard de manera que muestre su posicion el nombre, el puntaje, el nivel y el alias*/
void mostrarLeaderBoard(lista_Perfiles *perfiles){
    if (perfiles == NULL){
        cout << "no hay perfiles registrados, por lo tanto no hay jugadores en el LeaderBoard" << endl;
    } 
    else{
        lista_Players *listaLeaderBoard=NULL;
        lista_Perfiles *listaAuxPerfiles=perfiles;

        while(listaAuxPerfiles!=NULL){
            Perfil *perfilAux=listaAuxPerfiles->perfil;
            if(perfilAux!=NULL && perfilAux->jugadores!=NULL){
                lista_Players *listajugadoresPerfil=perfilAux->jugadores;
                while(listajugadoresPerfil!=NULL){
                    AgregarJugadoresListaLeaderboard(&listaLeaderBoard,listajugadoresPerfil->jugador);
                    listajugadoresPerfil=listajugadoresPerfil->prox;
                }
            }
            listaAuxPerfiles=listaAuxPerfiles->prox;
        }

        if (listaLeaderBoard==NULL){
            cout << "no hay jugadores registrados en ningun perfil " << endl;
        }
        else{
            OrdenarListaLeaderBoard(&listaLeaderBoard);

            cout << "----- LEADERBOARD -----" << endl;
            cout << "======================" << endl;

            lista_Players *auxlista=listaLeaderBoard;
            int posicion=0;
            while(auxlista!=NULL){
                posicion++;
                cout << "POSICION: " << posicion << "  PUNTAJE: " << auxlista->jugador->puntaje_total << endl;
                cout << "---------------------" << endl;
                cout << "NOMBRE: " << auxlista->jugador->nombre << endl;
                cout << "NIVEL: " << auxlista->jugador->nivel << endl;
                cout << "ALIAS: " << auxlista->jugador->alias << endl;
                cout << "================================================" << endl;
                auxlista=auxlista->prox;
            }

        }
    }

}

// Esta funcion lo que hace es extraer los datos de un logro y guardarlo en un archivo (se hace un procedimiento aparte para no repetir el mismo codigo dentro del while si no solo llamar al procedimiento)
void GuardarLogro (ofstream& archivoLogros,Logro *logro,int jugador_que_pertenece){
    if (archivoLogros.is_open() && logro!=NULL){
        archivoLogros<< logro->ID << ";" << logro->nombre << ";" << logro->puntaje << ";" << logro->descripcion << ";" << logro->distincion << ";" << logro->fecha << ";" << jugador_que_pertenece << endl;

    }
    else{
        cout << "Error no se pudo escribir el logro, el archivo no esta abierto o el logro esta vacio" << endl;
    }
}

// Este procedimiento lo que hace es que se le pasa una lista de logros, que seria la lista de logros de un jugador en especifico y va guardando en el archivo que se pasa como parametro (se le pasa tambien como parametro un id, cada logro tendra un id del jugador al que le pertenece para en el momento de cargar se sepa a quien le pertenece ese logro)
void GuardarListaLogros (ofstream& archivoLogros, lista_Logros *listalogros, int jugador_que_pertenece){
    lista_Logros *actual = listalogros;
    while (actual!=NULL){
        if (actual->logro!=NULL){
        GuardarLogro(archivoLogros,actual->logro,jugador_que_pertenece);
        }
        actual=actual->prox;
    }
}

// Este procedimiento lo que hace es guardar todos los datos del jugador en el archivo y tambien llama al procedimiento de guardar la lista de logros ya que para cada jugador pueden haber varios logros (se utiliza la misma logica de poner un id al que pertenece el jugador ya que un mimso perfil puede tener varios jugadores)
void GuardarJugador (ofstream& archivoJugadores,ofstream& archivoLogros, Player *jugador, int perfil_que_pertenece){
    if (archivoJugadores.is_open()&&archivoLogros.is_open()&&jugador!=NULL){
        archivoJugadores<< jugador->ID << ";" << jugador->nombre << ";" << jugador->alias << ";" << jugador->nivel << ";" << jugador->puntaje_total << ";" << perfil_que_pertenece << endl;
        GuardarListaLogros(archivoLogros,jugador->logros,jugador->ID);
    }
    else{
        cout << "no se pudo escribir el jugador, los archivos no estan abiertos o el jugador es NULL" << endl;
    }
}

// Este procedimiento recorre todos los jugadores de un perfil y llama a la funcion de guardar jugador por cada jugador que pasa
void GuardarListaJugadores (ofstream& archivojugadores,ofstream& archivoLogros,lista_Players *listajugadores, int perfil_que_pertenece){
    lista_Players *actual=listajugadores;
    while (actual!=NULL){
        if (actual->jugador!=NULL){
            GuardarJugador(archivojugadores,archivoLogros,actual->jugador,perfil_que_pertenece);
        }
        actual=actual->prox;
    }

}

// Este procedimiento guarda en un archivo de perfiles un perfil y sus datos, tambien se llama al procedimiento de guardar lista de jugadores, para guardar en el archivo de jugadores, todos los jugadores de ese perfil
void GuardarPerfil(ofstream& archivoPerfiles,ofstream& archivoJugadores, ofstream& archivoLogros, Perfil *perfil){
    if (archivoPerfiles.is_open() && archivoJugadores.is_open() && archivoLogros.is_open() && perfil != NULL){
        archivoPerfiles << perfil->ID << ";" << perfil->nombre << ";" << perfil->contrasena << endl;
        GuardarListaJugadores(archivoJugadores,archivoLogros,perfil->jugadores,perfil->ID);
    }
    else{
        cout << "No se pudo escribir el jugador ya que los archivos no estan abiertos o perfil esta vacio" << endl;
    }
}

//  Este procedimiento recorre una lista de perfiles y por cada perfil que pasa llama al procedimiento de guardar perfil mandandole tambien su id para que los jugadores al momento de cargar tengan una relacion con un perfil
void GuardarListaPerfiles (ofstream& archivoPerfiles,ofstream& archivoJugadores, ofstream& archivoLogros, lista_Perfiles *listaperfiles){
    lista_Perfiles *actual=listaperfiles;
    while (actual!=NULL){
        if (actual->perfil!=NULL){
            GuardarPerfil(archivoPerfiles,archivoJugadores,archivoLogros,actual->perfil);
        }  
        actual=actual->prox;
    }
}

// Esta es otra multilista que utiliza la misma logica de la lista anteror (se guarda la pregunta con un id de la mision a la que la pregunta pertenece)
void GuardarPregunta (ofstream& archivoPreguntas, pregunta *pregunta, int mision_que_pertenece){
    if (archivoPreguntas.is_open()&&pregunta!=NULL){
        archivoPreguntas << pregunta->texto_pregunta << ";" << pregunta->opciones_texto << ";" << pregunta->respuesta_de_opciones << ";" << mision_que_pertenece << endl;
    }
    else{
        cout << " Error el archivo no esta abierto o la pregunta esta vacia, no se pudo escribir las preguntas" << endl;
    }
}

//  Aqui recorre toda la lista de preguntas y guardando las preguntas en el archivo de preguntas
void GuardarListaDePreguntas (ofstream& archivoPreguntas, lista_preguntas *listapreguntas, int mision_que_pertenece){
    lista_preguntas *actual=listapreguntas;
    while (actual!=NULL){
        if (actual->pregunta!=NULL){
            GuardarPregunta(archivoPreguntas,actual->pregunta,mision_que_pertenece);
        }
        actual=actual->prox;
    }
}

// Aqui guarda la mision pasando todos los datos que puede tener una mision al archivo de misiones, tambien llama a guardar lista de preguntas
void GuardarMision(ofstream& archivoMisiones, ofstream& archivoPreguntas, Mision *mision){
    if (archivoMisiones.is_open()&&archivoPreguntas.is_open()&&mision !=NULL){
        archivoMisiones << mision->ID << ";" << mision->descripcion << ";" << mision->nombre << ";" << mision->nivel << ";" << mision->num_preguntas_requeridas << ";" << mision->puntos_recompensa << ";" << mision->tipo << ";" << mision->total_preguntas << endl;
        GuardarListaDePreguntas(archivoPreguntas,mision->preguntas,mision->ID);
    }
    else{
        cout << "no se pudo escribir la mision ya que los archivos no estan abiertos o la mision esta vacia " << endl;
    }
}
 // Aqui recorre toda la lista de misiones y va llamando al otro procedimiento que se encarga de guardar cada mision y sus respectivas preguntas
void GuardarListaDeMisiones(ofstream& archivoMisiones, ofstream& archivoPreguntas, lista_Misiones *listamisiones){
    lista_Misiones *actual=listamisiones;
    while (actual!=NULL){
        if (actual->mision!=NULL){
            GuardarMision(archivoMisiones,archivoPreguntas,actual->mision);
        }
        actual=actual->prox;
    }
}

// Esta es una funcion que nos ayudara a validar si al momento de cargar el archivo y convertir un string a entero con stoi verificar si no tiene ni una sola letra, para que no haya error 
bool EsSoloDigitos(string texto){
    if (texto.empty()){
        return false;
    }
    else{
        for (size_t i=0;i<texto.length();i++){
            if (texto[i] < '0' || texto[i] > '9'){
                return false;
            }
        }
        return true;
    }
}

/*Esta funcion abre el archivo de misiones y con un metodo de utilizar list.find que parte de una posicion hasta encontrar el delimitador
 y list.substr que trata de agarrar una parte de la linea pasandole posiciones donde empezar y terminar (es utilizado este metodo ya que no sabia si se podia utilizar una libreria externa sstream)
 el procedimiento consiste en que va recorriendo todas las lineas y va recogiendo texto entre los delimitadores y va asignando a la mision(valida los numeros enteros y valida por si no se encuentra un delimitador) */
void CargarListaMisiones(lista_Misiones **misiones){
    string linea;
    ifstream archivoMisiones("misiones.txt");
    if (!archivoMisiones.is_open()){
        cout << "Error No se pudo abrir el archivo de misiones" << endl;
        *misiones=NULL;
        return;
    }

        *misiones=NULL;
        while(getline(archivoMisiones,linea)){
            Mision *nuevaMision=new Mision;
            nuevaMision->preguntas=NULL;
            int actualPos=0;
            int delimPos;
            string texto;

            delimPos=linea.find(";",actualPos);
            if (delimPos==-1){
                cout << "Error en el archivo de misiones" << endl;
                delete nuevaMision;
                return;
            }
            else{
                texto=linea.substr(actualPos,delimPos-actualPos);
                if (EsSoloDigitos(texto)){
                    nuevaMision->ID=stoi(texto);
                }
                else{
                    cout << "Error en al cargar el ID de la mision" << endl;
                    delete nuevaMision;
                    return;
                }
                actualPos=delimPos+1;
                delimPos=linea.find(";",actualPos);
                if (delimPos==-1){
                    cout << "Error en el archivo de misiones" << endl;
                    delete nuevaMision;
                    return;
                }
                else{
                    texto=linea.substr(actualPos,delimPos-actualPos);
                    nuevaMision->descripcion=texto;
                    actualPos=delimPos+1;
                    delimPos=linea.find(";",actualPos);
                    if (delimPos==-1){
                        cout << "Error en el archivo de misiones" << endl;
                        delete nuevaMision;
                        return;
                    }
                    else{
                        texto=linea.substr(actualPos,delimPos-actualPos);
                        nuevaMision->nombre=texto;
                        actualPos=delimPos+1;
                        delimPos=linea.find(";",actualPos);
                        if (delimPos==-1){
                            cout << "Error al momento de cargar el archivo de misiones" << endl;
                            delete nuevaMision;
                            return;
                        }
                        else{
                            texto=linea.substr(actualPos,delimPos-actualPos);
                            if (EsSoloDigitos(texto)){
                                nuevaMision->nivel=stoi(texto);
                            }
                            else{
                                cout << "Error al momento de cargar el archivo de misiones por valor invalido en el nivel de la mision" << endl;
                                delete nuevaMision;
                                return;
                            }
                            actualPos=delimPos+1;
                            delimPos=linea.find(";",actualPos);
                            if (delimPos==-1){
                                cout << "Error al momento de cargar el archivo de misiones" << endl;
                                delete nuevaMision;
                                return;
                            }
                            else{
                                texto=linea.substr(actualPos,delimPos-actualPos);
                                if (EsSoloDigitos(texto)){
                                    nuevaMision->num_preguntas_requeridas=stoi(texto);

                                }
                                else{
                                    cout << "Error al momento de cargar las preguntas requeridas del archivo de misiones" << endl;
                                    delete nuevaMision;
                                    return;
                                }
                                actualPos=delimPos+1;
                                delimPos=linea.find(";",actualPos);
                                if (delimPos==-1){
                                   cout << "error al momento de cargar el archivo de misiones" << endl; 
                                   delete nuevaMision;  
                                   return;  
                                }
                                else{
                                    texto=linea.substr(actualPos,delimPos-actualPos);
                                    if (EsSoloDigitos(texto)){
                                        nuevaMision->puntos_recompensa=stoi(texto);
                                    }
                                    else{
                                        cout << "Error al momento de cargar los puntos de recompensa en el archivo de misiones" << endl;
                                        delete nuevaMision;
                                        return;
                                    }
                                    actualPos=delimPos+1;
                                    delimPos=linea.find(";",actualPos);
                                    if (delimPos==-1){
                                        cout << "Error al momento de la carga de archivos de misiones" << endl;
                                        delete nuevaMision;
                                        return;
                                    }
                                    else{
                                            texto=linea.substr(actualPos,delimPos-actualPos);
                                            nuevaMision->tipo=texto;
                                            actualPos=delimPos+1;
                                            texto=linea.substr(actualPos);
                                            if(EsSoloDigitos(texto)){
                                                nuevaMision->total_preguntas=stoi(texto);
                                            }
                                            else{
                                                cout << "Error al momento de cargar el total de poreguntas en el archivo de misiones" << endl;
                                                delete nuevaMision;
                                                return;
                                            }

                                        }
                                }
                            }
                        }

                    }
                }
            }
            AgregrarListaMision(&*misiones,nuevaMision);
        }
        archivoMisiones.close();
        cout<<"carga de MISIONES completada" << endl;
    }

// procedimiento necesario para retornar la mision en la que pertenece la pregunta
Mision* BuscarIDdeMision (lista_Misiones *misiones, int ID){
    lista_Misiones *actual=misiones;
    while (actual!=NULL){
        if (actual->mision->ID==ID){
            return actual->mision;
        }
        actual=actual->prox;
    }
    return NULL;
}

// procedmiento que se encarga de retornar un booleando dependiendo si se encontro la mision o no
bool EncontraIDdeMision(lista_Misiones *misiones,int ID){
    lista_Misiones *actual=misiones;
    if(misiones==NULL){
        return false;
    }
    else{
        while (actual!=NULL){
            if (actual->mision->ID==ID){
                return true;
            }
            actual=actual->prox;
        }
        return false;
    }
}

// prodecdimiento que se encarga de abrir el archivo de preguntas y con la logica de list.find list.substr y los indices de las posiciones ir extrayendo todos los datos de la pregunta y al final encontrar a que mision pertenece para anadirla
void CargarlistaPreguntasEnMisiones(lista_Misiones **misiones){
    ifstream archivoPregunta("preguntas.txt");
    string linea;
    if (!archivoPregunta.is_open()){
        cout << "Error no se pudo abrir el archivo de preguntas" << endl;
        return;
    }
    while (getline(archivoPregunta,linea)){
        pregunta *nuevapregunta=new pregunta;
        int id_que_pertenece=-1;
        int actualPos=0;
        int delimPos;
        string texto;

        delimPos=linea.find(";",actualPos);
        if (delimPos==-1){
            cout << "Error al momento de cargar el archivo de preguntas" << endl;
            delete nuevapregunta;
            return;
        }
        else{
            texto=linea.substr(actualPos,delimPos-actualPos);
            nuevapregunta->texto_pregunta=texto;
            actualPos=delimPos+1;
            delimPos=linea.find(";",actualPos);
            if (delimPos==-1){
                cout << "Error al momento de cargar el archivo de preguntas" << endl;
                delete nuevapregunta;
                return;
            }
            else{
                
                texto=linea.substr(actualPos,delimPos-actualPos);
                nuevapregunta->opciones_texto=texto;
                actualPos=delimPos+1;
                delimPos=linea.find(";",actualPos);
                if (delimPos==-1){
                    cout << "Error al momento de cargar del archivo de preguntas" << endl;
                    delete nuevapregunta;
                    return;
                }
                else{
                    texto=linea.substr(actualPos,delimPos-actualPos);
                    if (EsSoloDigitos(texto)){
                        nuevapregunta->respuesta_de_opciones=stoi(texto);
                    }
                    else{
                        cout << "Eroor al momento de cargar la respuesta de las opciones en una pregunta del archivo de preguntas" << endl;
                        delete nuevapregunta;
                        return;
                    }
                    actualPos=delimPos+1;
                    texto=linea.substr(actualPos);
                    if(EsSoloDigitos(texto)){
                        id_que_pertenece=stoi(texto);
                    }
                    else{
                        cout << "Error al momento de cargar el ID ya que no tiene alguna letra" << endl;
                        delete nuevapregunta;
                        return;
                    }
                }
            }

        }
        Mision *misionQuePertenece=BuscarIDdeMision(*misiones,id_que_pertenece);
        if (misionQuePertenece==NULL){
            cout << "Error al momento de encontrar el ID al que pertence una de las preguntas de el archivo de preguntas" << endl;
            return;
        }
        else{
        AgregarPreguntaAListaPreguntas(&misionQuePertenece->preguntas,nuevapregunta);
        }
        
    }
    archivoPregunta.close();
    cout<< "carga de PREGUNTAS A MISIONES completada" << endl;
}

// Este es un procedmiento parecido a agregar lista perfiles pero aqui ya se pasa el perfil como parametro en cambio en la otra pregunta por los datos
void agregarListaPerfiles2 (lista_Perfiles **perfiles,Perfil *nuevoperfil){
    lista_Perfiles *nuevo = new lista_Perfiles;
    if (*perfiles == NULL)
    {
        nuevo->perfil = nuevoperfil;
        nuevo->prox = *perfiles;
        *perfiles = nuevo;
    }
    else
    {
        lista_Perfiles *aux = *perfiles;
        if (aux->prox == NULL)
        {
            nuevo->perfil = nuevoperfil;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
        else
        {
            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            nuevo->perfil = nuevoperfil;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
    }
}

// Este procedimiento utiliza la misma logica que cargar misiones y preguntas, primero se cargan todos los perfiles que haya en el archivo y se van agregando en la lista de perfiles
void CargarListaPerfiles (lista_Perfiles **perfiles){
    string linea;
    ifstream archivoPerfiles("perfiles.txt");
    if (!archivoPerfiles.is_open()){
        cout << "Error no se pudo abrir el archivo de perfiles " << endl;
        return;
    }
    while (getline(archivoPerfiles,linea)){
        int actualPos=0;
        int delimPos;
        string texto;
        Perfil *perfilnuevo=new Perfil;
        delimPos=linea.find(";",actualPos);
        if (delimPos==-1){
            cout << "Error al momento de cargar el archivo de perfiles " << endl;
            delete perfilnuevo;
            return;
        }
        else{
            texto=linea.substr(actualPos,delimPos-actualPos);
            if (EsSoloDigitos(texto)){
                perfilnuevo->ID=stoi(texto);
            }
            else{
                cout << "Error al momento de cargar el Id por haber alguna letra" << endl;
                delete perfilnuevo;
                return;
            }
            actualPos=delimPos+1;
            delimPos=linea.find(";",actualPos);
            if (delimPos==-1){
                cout << "Error al momento de cargar el archivo de perfiles " << endl;
                delete perfilnuevo;
                return;
            }
            else{
                texto=linea.substr(actualPos,delimPos-actualPos);
                perfilnuevo->nombre=texto;
                actualPos=delimPos+1;
                texto=linea.substr(actualPos);
                perfilnuevo->contrasena=texto;

                


            }

        }
        perfilnuevo->jugadores=NULL;
        agregarListaPerfiles2(&*perfiles,perfilnuevo);
    }
    archivoPerfiles.close();
    cout<<"carga de PERFILES completada" << endl;
}

// este procedimeinto se encarga de retornar el perfil al que pertenece el jugador
Perfil* BuscarIDdePerfil (lista_Perfiles *perfiles, int ID){
    lista_Perfiles *actual=perfiles;
    while (actual!=NULL){
        if (actual->perfil->ID==ID){
            return actual->perfil;
        }
        actual=actual->prox;
    }
    return NULL;
}

// Este procedimiento agrega jugadores a una lista de jugadores pero ya se le pasa el nuevo jugador por parametro
void agregarListaJugadores2 (lista_Players **jugadores,Player *nuevoplayer){
    lista_Players *nuevo = new lista_Players;
    if (*jugadores == NULL)
    {
        nuevo->jugador = nuevoplayer;
        nuevo->prox = *jugadores;
        *jugadores = nuevo;
    }
    else
    {
        lista_Players *aux = *jugadores;
        if (aux->prox == NULL)
        {
            nuevo->jugador = nuevoplayer;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
        else
        {
            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            nuevo->jugador = nuevoplayer;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
    }
}

// Este procedimiento abre el archivo de jugadores va extrayendo sus datos y introduciendolos en un nuevo jugador para despues agregarlo en la lista de jugadores del perfil a donde pertenece
void CargarJugadoresAperfiles(lista_Perfiles **perfiles){
    string linea;
    ifstream archivoJugadores("jugadores.txt");
    if (!archivoJugadores.is_open()){
        cout << "Error no se pudo abrir el archivo de preguntas" << endl;
        return;
    }
    while(getline(archivoJugadores,linea)){
        int actualPos=0;
        int delimPos;
        int perfil_que_pertenece;
        string texto;
        Player *nuevojugador=new Player;
        nuevojugador->logros=NULL;

        delimPos=linea.find(";",actualPos);
        if (delimPos==-1){
            cout << "Error al momento de cargar el archivo de jugadores " << endl;
            delete nuevojugador;
            return;
        }
        else{
            texto=linea.substr(actualPos,delimPos-actualPos);
            if (EsSoloDigitos(texto)){
                nuevojugador->ID=stoi(texto);
            }
            else{
                cout<< "Error al momento de cargar el id de los jugadores del archivo de jugadores " << endl;
                delete nuevojugador;
                return;
            }
            actualPos=delimPos+1;
            delimPos=linea.find(";",actualPos);
            if (delimPos==-1){
                cout<< "Error al cargar un delimitador del archivo de jugadores" << endl;
                delete nuevojugador;
                return;
            }
            else{
                texto=linea.substr(actualPos,delimPos-actualPos);
                nuevojugador->nombre=texto;
                actualPos=delimPos+1;
                delimPos=linea.find(";",actualPos);
                if (delimPos==-1){
                    cout<< "Error al cargar un delimitador del archivo de jugadores" << endl;
                    delete nuevojugador;
                    return;
                }
                else{
                    texto=linea.substr(actualPos,delimPos-actualPos);
                    nuevojugador->alias=texto;
                    actualPos=delimPos+1;
                    delimPos=linea.find(";",actualPos);
                    if (delimPos==-1){
                        cout<< "Error al cargar un delimitador del archivo de jugadores" << endl;
                        delete nuevojugador;
                        return;
                    }
                    else{
                        texto=linea.substr(actualPos,delimPos-actualPos);
                        if (EsSoloDigitos(texto)){
                            nuevojugador->nivel=stoi(texto);
                        }
                        else{
                            cout<< "Error al momento de cargar el nivel de los jugadores del archivo de jugadores " << endl;
                            delete nuevojugador;
                            return;
                        }
                        actualPos=delimPos+1;
                        delimPos=linea.find(";",actualPos);
                        if (delimPos==-1){
                            cout<< "Error al cargar un delimitador del archivo de jugadores" << endl;
                            delete nuevojugador;
                            return;
                        }
                        else{
                            texto=linea.substr(actualPos,delimPos-actualPos);
                            if (EsSoloDigitos(texto)){
                            nuevojugador->puntaje_total=stoi(texto);
                            }
                            else{
                            cout<< "Error al momento de cargar el puntaje total de los jugadores del archivo de jugadores " << endl;
                            delete nuevojugador;
                            return;
                            }
                            actualPos=delimPos+1;
                            texto=linea.substr(actualPos);
                            if(EsSoloDigitos(texto)){
                                perfil_que_pertenece=stoi(texto);
                            }
                            else{
                                cout << "Error al momento de cargar el ID al que pertenece el jugador en el archivo de jugadores ya que puede tener una letra" << endl;
                                delete nuevojugador;
                                return;
                            }
                        }
                    }
                }
            }
        
        }   
        Perfil *perfilid = BuscarIDdePerfil(*perfiles,perfil_que_pertenece);
        if (perfilid == NULL){
            cout << "Error al momento de encontrar el Id del perfil al que pertenece el jugador" << endl;
            delete nuevojugador;
            return;
        }
        else{
            agregarListaJugadores2(&perfilid->jugadores,nuevojugador);
        }
    }
    archivoJugadores.close();
    cout<< "carga de JUGADORES A PERFILES completada" << endl;   
}

// Esta funcion retornar el jugador al que pertenece el logro, va pasando por todos los jugadores de cada perfil hasta encontrarlo
Player* BuscarIDdeJugador(lista_Perfiles *perfiles, int ID) {
    lista_Perfiles *actualPerfil = perfiles;
    while (actualPerfil != NULL) {
        lista_Players *actualJugador = actualPerfil->perfil->jugadores;
        while (actualJugador != NULL) {
            if (actualJugador->jugador->ID == ID) {
                return actualJugador->jugador;
            }
            actualJugador = actualJugador->prox;
        }
        actualPerfil = actualPerfil->prox;
    }
    return NULL; 
}

// Este procedimiento agrega logros a una lista de logros que en esta caso seria para perfil->jugador->logros pero pasandole el logro nuevo por parametro
void agregarListaLogros2 (lista_Logros **logros,Logro *nuevologro){
    lista_Logros *nuevo = new lista_Logros;
    if (*logros == NULL)
    {
        nuevo->logro = nuevologro;
        nuevo->prox = *logros;
        *logros = nuevo;
    }
    else
    {
        lista_Logros *aux = *logros;
        if (aux->prox == NULL)
        {
            nuevo->logro = nuevologro;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
        else
        {
            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            nuevo->logro = nuevologro;
            nuevo->prox = NULL;
            aux->prox = nuevo;
        }
    }
}

// Este procedimiento abre el archivo de logros va extrayendo sus datos y cargandolos en un nuevo logro y al final se agrega a la lista de logros del jugador que le pertenece dentro de tambien al perfil que le pertenece
void CargarLogrosEnJugadoresPerfil(lista_Perfiles **perfiles){
    string linea;
    ifstream archivoLogros("logros.txt");
    if (!archivoLogros.is_open()){
        cout << "Error no se pudo abrir el archivo de Logros" << endl;
        return;
    }
    while (getline(archivoLogros,linea)){
        int actualPos=0;
        int jugador_que_pertenece=-1;
        int delimPos;
        string texto;
        Logro *nuevo=new Logro;
        delimPos=linea.find(";",actualPos);
        if (delimPos==-1){
            cout << "Error al momento de buscar el delimitador del archivo de logros" << endl;
            delete nuevo;
            return;
        }
        else{
            texto=linea.substr(actualPos,delimPos-actualPos);
            if (EsSoloDigitos(texto)){
                nuevo->ID=stoi(texto);
            }
            else{
                cout << "Error al cargar el ID del logro porque puede tener una letra" << endl;
                delete nuevo;
                return;
            }
            actualPos=delimPos+1;
            delimPos=linea.find(";",actualPos);
            if (delimPos==-1){
                cout << "Error al momento de buscar el delimitador del archivo de logros" << endl;
                delete nuevo;
                return;
            }
            else{
                texto=linea.substr(actualPos,delimPos-actualPos);
                nuevo->nombre=texto;
                actualPos=delimPos+1;
                delimPos=linea.find(";",actualPos);
                if (delimPos==-1){
                    cout << "Error al momento de buscar el delimitador del archivo de logros" << endl;
                    delete nuevo;
                    return;
                }
                else{
                    texto=linea.substr(actualPos,delimPos-actualPos);
                    if (EsSoloDigitos(texto)){
                        nuevo->puntaje=stoi(texto);
                    }
                    else{
                        cout << "Error al cargar el puntaje del logro porque puede tener una letra" << endl;
                        delete nuevo;
                        return;
                    }
                    actualPos=delimPos+1;
                    delimPos=linea.find(";",actualPos);
                    if (delimPos==-1){
                        cout << "Error al momento de buscar el delimitador del archivo de logros" << endl;
                        delete nuevo;
                        return;
                    }
                    else{
                        texto=linea.substr(actualPos,delimPos-actualPos);
                        nuevo->descripcion=texto;
                        actualPos=delimPos+1;
                        delimPos=linea.find(";",actualPos);
                        if (delimPos==-1){
                            cout << "Error al momento de buscar el delimitador del archivo de logros" << endl;
                            delete nuevo;
                            return;
                        }
                        else{
                            texto=linea.substr(actualPos,delimPos-actualPos);
                            nuevo->distincion=texto;
                        }
                        actualPos=delimPos+1;
                        delimPos=linea.find(";",actualPos);
                        if (delimPos==-1){
                            cout << "Error al momento de buscar el delimitador del archivo de logros" << endl;
                            delete nuevo;
                            return;
                        }
                        else{
                            texto=linea.substr(actualPos,delimPos-actualPos);
                            if (EsSoloDigitos(texto)){
                                nuevo->fecha=stoi(texto);
                            }
                            else{
                                cout << "Error al cargar la fecha del logro porque puede tener una letra" << endl;
                                delete nuevo;
                                return;
                            }
                            actualPos=delimPos+1;
                            texto=linea.substr(actualPos);
                            if (EsSoloDigitos(texto)){
                                jugador_que_pertenece=stoi(texto);
                            }
                            else{
                                cout << "Error al cargar el ID del jugador al que pertenece el logro porque puede tener una letra" << endl;
                                delete nuevo;
                                return;
                            }

                        }
                    }
                }
            }  
        }
        Player *jugadorquePertenece=BuscarIDdeJugador(*perfiles,jugador_que_pertenece);
        if (jugadorquePertenece==NULL){
            cout << "no se pudo encontrar el id del jugador al que pertenece el logro" << endl;
            delete nuevo;
            return;
        }
        else{
            agregarListaLogros2(&jugadorquePertenece->logros,nuevo);
        }
    }
    archivoLogros.close();
    cout << "Carga de LOGROS completada" << endl;
}

// Procedimiento general que llama a todas las funciones para cargar los archivos (el archivo de ranking no es necesario ya que se fija en los jugadores actualizados, no depende de una estructura individual, si no que extrae la informacion de los jugadores que estan en el sistema)
void CargarlistasyDatos(lista_Perfiles **perfiles , lista_Misiones **misiones){
    cout << "INICIANDO CARGA DE LOS ARCHIVOS" << endl;
    cout <<"------------------------------------" << endl;
    CargarListaPerfiles(perfiles);
    CargarJugadoresAperfiles(perfiles);
    CargarLogrosEnJugadoresPerfil(perfiles);
    CargarListaMisiones(misiones);
    CargarlistaPreguntasEnMisiones(misiones);
    cout << "-----------------------------------" << endl;
    cout << "==TERMINADA LA CARGA DE ARCHIVOS==(Si es tu primera vez jugando al cargar los archivos dara 'error' no te preocupes)" << endl;

}

// Este procedimiento es para cuando el jugador quiera salir del juego y se tenga que guardar todos los cambios generados mientras jugaba 
void GuardarCambiosYSalir(lista_Perfiles *perfiles, lista_Misiones *misiones) {
   ofstream archivoPerfiles;
   ofstream archivoJugadores;
   ofstream archivoLogros;
   ofstream archivoPreguntas;
   ofstream archivoMisiones;

   archivoPerfiles.open("perfiles.txt", ios::out);
   archivoJugadores.open("jugadores.txt", ios::out);
   archivoLogros.open("logros.txt", ios::out);
   archivoPreguntas.open("preguntas.txt", ios::out);
   archivoMisiones.open("misiones.txt", ios::out);

    if (archivoPerfiles.is_open() && archivoJugadores.is_open() && archivoLogros.is_open()&&archivoMisiones.is_open() && archivoPreguntas.is_open()){
        cout << "guardando cambios en los archivos ..." << endl;
        GuardarListaPerfiles(archivoPerfiles,archivoJugadores,archivoLogros,perfiles);
        GuardarListaDeMisiones(archivoMisiones,archivoPreguntas,misiones);
    }
    else{
        cout << " Error, no se pudieron abrir todos los archivos para guardar todos los datos" << endl;
    }

    archivoPerfiles.close();
    archivoJugadores.close();
    archivoLogros.close();
    archivoPreguntas.close();
    archivoMisiones.close();

}


main() { 
    lista_Misiones *Misiones = NULL;
    lista_Perfiles *Perfiles = NULL;
    Perfil *perfilActivo = NULL;
    Player *jugadorActivo = NULL;

    CargarlistasyDatos(&Perfiles,&Misiones);



    
    Mision *mision1 = CrearMision("CULTURA GENERAL BASICA", "PON A PRUEBA TUS CONOCIMIENTOS BASICOS", "facil", 3, 100, 1234, 1, 4); 
    if (!EncontraIDdeMision(Misiones,mision1->ID)){
    AgregarPreguntaAListaPreguntas(&mision1->preguntas, CrearPregunta("EN QUE ANO LLEGO CRISTOBAL COLON A AMERICA?", "1) 1492   2) 1502   3) 1512", 1));
    AgregarPreguntaAListaPreguntas(&mision1->preguntas, CrearPregunta("CUAL ES EL ANIMAL TERRESTRE MAS RAPIDO?", "1) LEOPARDO  2) GUEPARDO  3) TIGRE", 2));
    AgregarPreguntaAListaPreguntas(&mision1->preguntas, CrearPregunta("QUE CIENTIFICO FORMULO LA TEORIA DE LA RELATIVIDAD?", "1) ISAAC NEWTON  2) ALBERT EINSTEIN  3) STEPHEN HAWKING", 2));
    AgregarPreguntaAListaPreguntas(&mision1->preguntas, CrearPregunta("EN QUE DEPORTE SE UTILIZA UNA RAQUETA Y UNA RED, PERO NO UNA PELOTA?", "1) TENIS  2) BADMINTON  3) SQUASH", 2));
    AgregrarListaMision(&Misiones, mision1);}
    else{
        lista_preguntas *actual_pregunta = mision1->preguntas;
        while (actual_pregunta != NULL) {
            lista_preguntas *temp_pregunta = actual_pregunta;
            actual_pregunta = actual_pregunta->prox;
            delete temp_pregunta->pregunta; 
            delete temp_pregunta;           
        }
        delete mision1;
    }

    
    Mision *mision2 = CrearMision("GEOGRAFIA MUNDIAL", "DEMUESTRA CUANTO SABES DE GEOGRAFIA", "intermedio", 3, 150, 5678, 2, 4); 
    if (!EncontraIDdeMision(Misiones,mision2->ID)){
    AgregarPreguntaAListaPreguntas(&mision2->preguntas, CrearPregunta("CUAL ES LA CAPITAL DE FRANCIA?", "1) BERLIN  2) PARIS  3) ROMA", 2));
    AgregarPreguntaAListaPreguntas(&mision2->preguntas, CrearPregunta("CUAL ES EL RIO MAS LARGO DEL MUNDO?", "1) AMAZONAS  2) NILO  3) MISISIPI", 1));
    AgregarPreguntaAListaPreguntas(&mision2->preguntas, CrearPregunta("QUE CONTINENTE ES EL MAS GRANDE EN TAMANO?", "1) AMERICA  2) EUROPA  3) ASIA", 3));
    AgregarPreguntaAListaPreguntas(&mision2->preguntas, CrearPregunta("CUAL ES EL OCEANO MAS GRANDE Y PROFUNDO DE LA TIERRA?", "1) OCEANO ATLANTICO  2) OCEANO INDICO  3) OCEANO PACIFICO", 3));
    AgregrarListaMision(&Misiones, mision2);}
    else{
        lista_preguntas *actual_pregunta = mision2->preguntas;
        while (actual_pregunta != NULL) {
            lista_preguntas *temp_pregunta = actual_pregunta;
            actual_pregunta = actual_pregunta->prox;
            delete temp_pregunta->pregunta; 
            delete temp_pregunta;           
        }
        delete mision2;
    }

  
    Mision *mision3 = CrearMision("CIENCIA BASICA", "EXPLORA CONCEPTOS CIENTIFICOS FUNDAMENTALES", "dificil", 3, 200, 9101, 3, 4);
    if (!EncontraIDdeMision(Misiones,mision3->ID)){
    AgregarPreguntaAListaPreguntas(&mision3->preguntas, CrearPregunta("QUE ELEMENTO QUIMICO ES EL MAS ABUNDANTE EN LA CORTEZA TERRESTRE?", "1) HIERRO  2) OXIGENO  3) SILICIO", 2));
    AgregarPreguntaAListaPreguntas(&mision3->preguntas, CrearPregunta("CUAL ES LA FORMULA QUIMICA DEL AGUA?", "1) CO2  2) O2  3) H2O", 3));
    AgregarPreguntaAListaPreguntas(&mision3->preguntas, CrearPregunta("QUE PLANETA ES CONOCIDO COMO EL 'PLANETA ROJO'?", "1) MARTE  2) JUPITER  3) VENUS", 1));
    AgregarPreguntaAListaPreguntas(&mision3->preguntas, CrearPregunta("CUAL ES LA UNIDAD BASICA DE LA HERENCIA EN LOS SERES VIVOS?", "1) CELULA  2) GEN  3) TEJIDO", 2));
    AgregrarListaMision(&Misiones, mision3);}
    else{
        lista_preguntas *actual_pregunta = mision3->preguntas;
        while (actual_pregunta != NULL) {
            lista_preguntas *temp_pregunta = actual_pregunta;
            actual_pregunta = actual_pregunta->prox;
            delete temp_pregunta->pregunta; 
            delete temp_pregunta;           
        }
        delete mision3;
    }

    Mision *mision4 = CrearMision("MISION FINAL", "PREGUNTAS IMPOSIBLES " , "EXTREMO" , 8, 500, 7721, 6, 8);
    if (!EncontraIDdeMision(Misiones,mision4->ID)){
    AgregarPreguntaAListaPreguntas(&mision4->preguntas, CrearPregunta("CUAL ES LA CARACTERISTICA PRINCIPAL DE UNA LISTA ENLAZADA SIMPLE?", "1) --ALMACENA ELEMENTOS EN UBICACIONES DE MEMORIA CONTIGUAS--  2) --CADA ELEMENTO (NODO) CONTIENE UN DATO Y UN PUNTERO AL SIGUIENTE--  3) --SE ACCEDE A LOS ELEMENTOS SOLO POR SU INDICE--", 2));
    AgregarPreguntaAListaPreguntas(&mision4->preguntas, CrearPregunta("QUE ESTRUCTURA DE DATOS SIGUE EL PRINCIPIO FIFO (FIRST-IN, FIRST-OUT)?", "1) --PILA (STACK)--  2) --LISTA ENLAZADA DOBLE--  3) --COLA--", 3));
    AgregarPreguntaAListaPreguntas(&mision4->preguntas, CrearPregunta("CUAL DE LAS SIGUIENTES AFIRMACIONES ES VERDADERA SOBRE UN ARBOL BINARIO DE BUSQUEDA (BST)?", "1) --LOS NODOS HOJA SIEMPRE TIENEN DOS HIJOS--  2) --CADA NODO TIENE COMO MAXIMO DOS HIJOS, Y EL HIJO IZQUIERDO ES MENOR QUE EL PADRE, Y EL DERECHO ES MAYOR--  3) --ES UNA ESTRUCTURA DE DATOS LINEAL--", 2));
    AgregarPreguntaAListaPreguntas(&mision4->preguntas, CrearPregunta("QUE ES UN GRAFO (GRAPH) EN EL CONTEXTO DE LAS ESTRUCTURAS DE DATOS?", "1) --UNA COLECCION DE ELEMENTOS ORDENADOS LINEALMENTE--  2) --UNA ESTRUCTURA JERARQUICA CON UN UNICO NODO RAIZ--  3) --UN CONJUNTO DE VERTICES (NODOS) Y ARISTAS (CONEXIONES) QUE LOS UNEN--", 3));
    AgregarPreguntaAListaPreguntas(&mision4->preguntas, CrearPregunta("CUAL ES EL PROPOSITO PRINCIPAL DE UNA ESTRUCTURA DE DATOS DE MONTON (HEAP)?", "1) --ALMACENAR PARES CLAVE-VALOR PARA BUSQUEDA RAPIDA--  2) --PERMITIR LA INSERCION Y EXTRACCION EFICIENTE DEL ELEMENTO DE MAYOR O MENOR PRIORIDAD--  3) --GARANTIZAR UN ORDEN ESPECIFICO DE LOS ELEMENTOS EN MEMORIA--", 3));
    AgregarPreguntaAListaPreguntas(&mision4->preguntas, CrearPregunta("CUAL ES LA PRINCIPAL DESVENTAJA DE UTILIZAR UNA LISTA ENLAZADA SOBRE UN ARREGLO PARA ALMACENAR DATOS?", "1) --OCUPA MENOS ESPACIO EN MEMORIA--  2) --NO PERMITE LA INSERCION O ELIMINACION RAPIDA--  3) --REQUIERE MAS MEMORIA POR PUNTEROS Y NO PERMITE ACCESO DIRECTO POR INDICE--", 3));
    AgregarPreguntaAListaPreguntas(&mision4->preguntas, CrearPregunta("QUE TIPO DE ALMACENAMIENTO DE DATOS ES MAS ADECUADO PARA UN CONJUNTO DE ELEMENTOS QUE NECESITAN SER RECUPERADOS EN EL ORDEN EN QUE FUERON INSERTADOS Y LUEGO ELIMINADOS?", "1) --PILA--  2) --TABLA HASH--  3) --COLA--", 2));
    AgregarPreguntaAListaPreguntas(&mision4->preguntas, CrearPregunta("QUE PROBLEMA PUEDE OCURRIR EN UNA TABLA HASH SI LA FUNCION HASH NO ES EFICIENTE?", "1) --DESBORDAMIENTO DE PILA--  2) --SOBRECARGA DE LA COLA--  3) --EXCESO DE COLISIONES--", 3));
    AgregrarListaMision(&Misiones, mision4);}
    else{
        lista_preguntas *actual_pregunta = mision4->preguntas;
        while (actual_pregunta != NULL) {
            lista_preguntas *temp_pregunta = actual_pregunta;
            actual_pregunta = actual_pregunta->prox;
            delete temp_pregunta->pregunta; 
            delete temp_pregunta;           
        }
        delete mision4;
    }


    int opcionPrincipal;
    do {
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Crear Perfil" << endl;
        cout << "2. Ingresar a Perfil" << endl;
        cout << "3. Mostrar Perfiles" << endl;
        cout << "4. Eliminar Perfil" << endl;
        cout << "5. Mostrar leaderboard" << endl;
        cout << "6. Actualizar Perfil" << endl;
        cout << "7. Guardar cambios y Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcionPrincipal;
        if (cin.fail()) { 
            cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
            cin.clear();
            char c;
            while (cin.get(c) && c != '\n'){
            opcionPrincipal = 0; 
            } 
            }else {
            char c;
            while (cin.get(c) && c != '\n');
        }

        switch (opcionPrincipal) {
            case 1:
                AgregarListaPerfiles(&Perfiles);
                break;
            case 2:
                perfilActivo = SeleccionarPerfil(Perfiles);
                if (perfilActivo != NULL) {
                    if (IngresarPerfil(Perfiles)) {  
                        int opcionPerfil;
                        do {
                            cout << "\n--- MENU DE PERFIL (" << perfilActivo->nombre << ") ---" << endl;
                            cout << "1. Crear Jugador" << endl;
                            cout << "2. Seleccionar Jugador" << endl;
                            cout << "3. Eliminar Jugador" << endl;
                            cout << "4. Mostrar Jugadores del Perfil" << endl;
                            cout << "5. Gestionar Logros de Jugador (Manual)" << endl;
                            cout << "6. Consultar Estadisticas de Jugadores" << endl;
                            cout << "7. Realizar Mision" << endl;
                            cout << "8. Volver al Menu Principal" << endl;
                            cout << "Ingrese su opcion: ";
                            cin >> opcionPerfil;
                            if (cin.fail()) { 
                                 cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
                                cin.clear();
                                char c;
                                while (cin.get(c) && c != '\n'){
                                    opcionPerfil = 0; 
                                }
                                } else {
                                    char c;
                                while (cin.get(c) && c != '\n');
                                }

                            switch (opcionPerfil) {
                                case 1:
                                    AgregarListaJugadores(&perfilActivo->jugadores);
                                    break;
                                case 2:
                                    jugadorActivo = SeleccionarJugador(perfilActivo->jugadores);
                                    if (jugadorActivo != NULL) {
                                        int opcionJugador;
                                        do {
                                            cout << "\n--- MENU DE JUGADOR (" << jugadorActivo->alias << ") ---" << endl;
                                            cout << "1. Ver Datos del Jugador" << endl;
                                            cout << "2. Ver Logros del Jugador" << endl;
                                            cout << "3. Volver al Menu de Perfil" << endl;
                                            cout << "Ingrese su opcion: ";
                                            cin >> opcionJugador;
                                            if (cin.fail()) { 
                                                cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
                                                cin.clear();
                                                char c;
                                                while (cin.get(c) && c != '\n'){ 
                                                opcionJugador = 0; 
                                                } 
                                                }else {
                                                char c;
                                                while (cin.get(c) && c != '\n');
                                                }

                                            switch (opcionJugador) {
                                                case 1:
                                                    DatosPlayer(perfilActivo->jugadores);
                                                    break;
                                                case 2:
                                                    MostrarListaLogros(jugadorActivo->logros);
                                                    break;
                                                case 3:
                                                    cout << "Volviendo al menu de perfil..." << endl;
                                                    break;
                                                default:
                                                    cout << "Opcion invalida." << endl;
                                                    break;
                                            }
                                        } while (opcionJugador != 3);
                                    }
                                    break;
                                case 3:
                                    EliminarJugador(&perfilActivo->jugadores);
                                    break;
                                case 4:
                                    MostrarListaJugadores(perfilActivo->jugadores);
                                    break;
                                case 5:
                                    if (jugadorActivo != NULL) {
                                        AgregarLogroManualAJugador(&jugadorActivo);
                                    } else {
                                        cout << "Por favor, selecciona un jugador primero." << endl;
                                    }
                                    break;
                                case 6:
                                    consultarEstadisticas(perfilActivo->jugadores);
                                    break;
                                case 7:
                                    if (jugadorActivo != NULL) {
                                        Mision *misionSeleccionada = seleccionarMision(Misiones, jugadorActivo);
                                        if (misionSeleccionada != NULL) {
                                            ejecutarMision(misionSeleccionada, jugadorActivo);
                                        }
                                    } else {
                                        cout << "Por favor, selecciona un jugador primero para realizar una mision." << endl;
                                    }
                                    break;
                                case 8:
                                    cout << "Volviendo al menu principal..." << endl;
                                    break;
                                default:
                                    cout << "Opcion invalida." << endl;
                                    break;
                            }
                            system("pause");
                            system("cls");
                        } while (opcionPerfil != 8);
                    } else {
                        cout << "Fallo al ingresar al perfil." << endl;
                        perfilActivo = NULL;
                    }
                } else {
                    cout << "Perfil no encontrado." << endl;
                }
                break;
            case 3:
                MostrarListaPerfiles(Perfiles);
                break;
            case 4:
                EliminarPerfil(&Perfiles);
                break;
            case 5:
                mostrarLeaderBoard(Perfiles);
                break;
            case 6:
                ActualizarPerfil(&Perfiles);
                break;
            case 7:
                GuardarCambiosYSalir(Perfiles,Misiones);
                break;
            default:
                cout << "ingrese un numero del (1-6)" << endl;
                break;   
        }
        system("pause");
        system("cls");
    } while (opcionPrincipal != 7);

}









