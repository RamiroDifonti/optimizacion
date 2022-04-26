 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */

#include "grafo.h"

void GRAFO :: destroy()
{
	for (unsigned i=0; i< n; i++)
    {
      
		LS[i].clear();
		A[i].clear();
		if (dirigido == 1)
        {
            LP[i].clear();
        };
	}

	LS.clear();
	LP.clear();
	A.clear();

}

void GRAFO :: build (char nombrefichero[85], int &errorapertura)
{
    ElementoLista     dummy;
	ifstream textfile;
	textfile.open(nombrefichero);
	if (textfile.is_open())
    {
		unsigned i, j, k;
		// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
		// los nodos internamente se numeran desde 0 a n-1
		// creamos las n listas de sucesores
		LS.resize(n);
    LP.resize(n);
    A.resize(n);
    for(int l{0};l<n;l++){
      A[l].resize(n);
      for(int z{0};z<n;z++)
      A[l][z].j=0;
    }
	        // leemos los m arcos
		for (k=0;k<m;k++)
        	{
      errorapertura=0;
			textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
            //i: de donde viene
            //j: a donde va
            //dummy.c = coste
            //dummy tiene que tener su j que es a donde va y su coste que es cuanto sale
            if(dirigido==0)
              if(i!=j){

                dummy.j=j-1;
                LS[i-1].push_back(dummy);
                dummy.j=i-1;
                LS[j-1].push_back(dummy);

                A[j-1][i-1].j=1;
                A[j-1][i-1].c=dummy.c;

              }else{

                dummy.j=j-1;
                LS[i-1].push_back(dummy);

              }
            else{

              dummy.j=j-1;
              LS[i-1].push_back(dummy);
            }
            A[i-1][j-1].j=1;
            A[i-1][j-1].c=dummy.c;  
			//damos los valores a dummy.j y dummy.c
			//situamos en la posici�n del nodo i a dummy mediante push_backM
			//pendiente de hacer un segundo push_back si es no dirigido. O no.
			//pendiente la construcci�n de LP, si es dirigido
			//pendiente del valor a devolver en errorapertura
        }  
    }   
}

void GRAFO::ListaPredecesores()
{
  LP.resize(n);
  ElementoLista dummy;
  for(int i{0}; i<n ;i++)
    for(int j{0}; j<LS[i].size() ;j++){
    dummy.c=LS[i][j].c;
    dummy.j=i;
    LP[LS[i][j].j].push_back(dummy);
    }
    
  
}

GRAFO::~GRAFO()
{
	destroy();
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
	build (nombrefichero, errorapertura);
}

void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
{
    //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido()
{
return (dirigido==0)?0:1;
}

void GRAFO::Info_Grafo()
{
dirigido==0? std::cout<<"Grafo no dirigido  | nodos "<<n<<" |  aristas "<<m<<std::endl:
             std::cout<<"Grafo dirigido  | nodos "<<n<<" |  arcos "<<m<<std::endl;
}

void Mostrar_Lista(vector<LA_nodo> L)
{
  for(int j{0};j<L.size();++j){

    std::cout<<"["<<j+1<<"] : ";
    for(int i{0};i<L[j].size();i++)
      std::cout<<L[j][i].j+1<<" : ("<<L[j][i].c<<") ";
    if(L[j].size()==0)
      std::cout<<"null";
    std::cout<<"\n";

}
}

void GRAFO :: Mostrar_Listas (int l){
  l==-1 ? ListaPredecesores(),Mostrar_Lista(LP) :Mostrar_Lista(LS);
}

void GRAFO::Mostrar_Matriz() //Muestra la matriz de adyacencia, tanto los nodos adyacentes como sus costes
{
  for(int i{0};i<A[0].size();i++){
    std::cout<<" | ";
    for(int j{0};j<A[i].size();j++)
      A[i][j].j==1?std::cout<<" 1 ": std::cout<<" 0 ";
    std::cout<<" |\n";
  }
std::cout<<"\nMatriz de costes\n";
  for(int i{0};i<A[0].size();i++){
    std::cout<<" | ";
    for(int j{0};j<A[i].size();j++)
      A[i][j].j==1?std::cout<<" "<<A[i][j].c<<" ": std::cout<<" 1000000 ";
    std::cout<<" |\n";
  }
}

void GRAFO::dfs_num(unsigned i, vector<LA_nodo>  L, vector<bool> &visitado, vector<unsigned> &prenum, unsigned &prenum_ind, vector<unsigned> &postnum, unsigned &postnum_ind) //Recorrido en profundidad recursivo con recorridos enum y postnum
{
	visitado[i] = true;
    prenum.push_back(i);
    //asignamos el orden de visita prenum que corresponde el nodo i
    for (unsigned j=0;j<L[i].size();j++)
             if (!visitado[L[i][j].j])
                {
                dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
                };
    postnum[postnum_ind++]=i;//asignamos el orden de visita posnum que corresponde al nodo i
}

void GRAFO::RecorridoProfundidad() {
  vector<bool> visitado(n);
  vector<unsigned> prenum,postnum(n);
  unsigned prenum_ind=0,postnum_ind=0, resultado;

  std::cout<<"Elije nodo de partida? [1-"<<LS.size()<<"]: ";
  std::cin>> resultado;
  std::cout<<"Orden de visita de los nodos en preorden\n";
  
  dfs_num(resultado-1,LS,visitado,prenum,prenum_ind,postnum,postnum_ind);

  std::cout<<"["<<prenum[0]+1<<"]";
  if(prenum.size()!=0)
    for(int i=1;i<prenum.size();++i)
      if(prenum[i]!=prenum[0])
        std::cout<<" -> ["<<prenum[i]+1<<"]";

  std::cout<<"\nOrden de visita de los nodos en postorden\n";

  std::cout<<"["<<postnum[0]+1<<"]";
  int k{0};
  while(postnum[k++]!=prenum[0])
    std::cout<<" -> ["<<postnum[k]+1<<"]";
  std::cout<<"\n";
}

void GRAFO::bfs_num(	unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) //vector de distancias a nodo i+1
//Recorrido en amplitud con la construcci�n de pred y d: usamos la cola
{
    vector<bool> visitado; //creamos e iniciamos el vector visitado
    visitado.resize(n, false);  
    visitado[i] = true;
 
    pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);

    pred[0] = i;
    d[0] = 0;
    int m{0},l{1};
    queue<unsigned> cola; //creamos e inicializamos la cola
    cola.push(i);//iniciamos el recorrido desde el nodo i+1
 
    while (!cola.empty()) //al menos entra una vez al visitar el nodo i+1 y contin�a hasta que la cola se vac�e
    {   unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
        cola.pop(); //lo sacamos de la cola
        //Hacemos el recorrido sobre L desde el nodo k+1
        for (unsigned j=0;j<L[k].size();j++)
            //Recorremos todos los nodos u adyacentes al nodo k+1
            //Si el nodo u no est� visitado
            {
              if (!visitado[L[k][j].j]){
                ++m;
                visitado[L[k][j].j]=true;
                cola.push(L[k][j].j);
                pred[m]=L[k][j].j;
                d[m]=k+1;         
              }
            //Lo visitamos
            //Lo metemos en la cola
            //le asignamos el predecesor
            //le calculamos su etiqueta distancia
            };
        
        //Hemos terminado pues la cola est� vac�a
    };
    //std::cout<<" "<<pred[0]<<pred[1]<<pred[2]<<pred[3]<<pred[4]<<pred[5]<<"\n";
    //std::cout<<" "<<d[0]<<d[1]<<d[2]<<d[3]<<d[4]<<d[5]<<"\n";
    //std::cout<<"hola";
}

void GRAFO::RecorridoAmplitud() //Construye un recorrido en amplitud desde un nodo inicial
{
  vector<unsigned> pred,d;
  unsigned resultado;

  std::cout<<"Elije nodo de partida? [1-"<<LS.size()<<"]: ";
  std::cin>> resultado;
  std::cout<<"Nodo inicial: "<<resultado;
  std::cout<<"\n\nNodos segun distancia al nodo inicial en numero de aristas\n";
  bfs_num(resultado-1,LS,pred,d);
  for(int i=0,j=0;i<d.size();){
    std::cout<<"Distancia "<<j++<<" aristas";
    do{
      std::cout<<" : "<<pred[i]+1;
    }while(d[i]==d[++i]);
    std::cout<<"\n";
    }
  std::cout<<"\nRamas de conexion en el recorrido\n";
  
  for(int i=0,j=1;i<d.size();i++){
    
    while(d[++i]==j){
        std:cout<<pred[0]+1;
        std::cout<<" - "<<pred[i]+1;
        std::cout<<"\n";
      }
    ++j;
    }
    
  }
  
void GRAFO::FloydWarshall(void) {//Algoritmo de FW para caminos mínimos entre cualquier par de nodos;

  vector <LA_nodo> P; //Usaremos la misma estructura de datos de LS para guardar P y D
  //Inicializamos P y D en P
  //Creamos P
  P.resize(n); //Ya tenemos las posiciones P[0] a P[n-1]
  for (unsigned i=0; i<n; i++) 
      P[i].resize(n); //Ya tenemos la matriz cuadrada
  for (unsigned i=0;i<n;i++)
    for (unsigned j=0;j<n;j++){
      if (i != j){ //Inicialización base
        P[i][j].j = 0; //en el campo .j ponemos el predecesor
        P[i][j].c = maxint; // en el campo .c ponemos el coste
      } else { //Inicializamos los bucles
        P[i][j].c = 0; //El coste en el caso de un bucle
        P[i][j].j = i+1; //El predecesor en el caso de un bucle
      }
    };
//Recorremos LS para inicializar P, su predecesor en .j y su distancia en .c
  for (unsigned i=0;i<n;i++)
    for (unsigned j=0;j<LS[i].size();j++) {
      P[i][LS[i][j].j].j = i+1;
      P[i][LS[i][j].j].c= LS[i][j].c;
  };
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      if(i!=j)
        for(int k=0;k<n;k++)
          if(i!=k)
            if(P[j][k].c > (P[j][i].c + P[i][k].c)){
              P[j][k].c = P[j][i].c + P[i][k].c;
              P[j][k].j = P[i][k].j;
            }

  cout<<"Matrices de Distancias finales"<<endl;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(P[i][j].c>=0 && P[i][j].c<100000 )
        cout<<" "<<P[i][j].c<<" |";
      else if(P[i][j].c>100000)
        cout<<" Inf |";
      else
        cout<<P[i][j].c<<" |";

    }
    cout<<endl;
  }
  cout<<"Matrices de Predecesores finales"<<endl;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(P[i][j].j==0)
        cout<<"- | ";
      else
        cout<<P[i][j].j<<" | ";  
    }
    cout<<endl;
  } 

  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      if(P[i][j].c<100000 && i!=j){
        std::vector<int> temp;
        int k{j};
        cout<<"Camino minimo de "<<i+1<<" a "<<j+1<<" coste "<<P[i][j].c<<" : ";
          while(k!=i){     
              temp.push_back(P[i][k].j);
              k=P[i][k].j-1;
            if(k==j)break;
          }
            for(int i=temp.size()-1;i>=0;i--)
              cout<<temp[i]<<" - ";
          cout<<j+1<<endl;
      }
}









