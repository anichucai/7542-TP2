using namespace std;
#include <iostream>
#include <fstream>
#include "dgraph.h"

void prueba_addChildren(){
    DGraph graph;
    graph.addChild(1,11);
    graph.addChild(1,12);
    graph.addChild(1,13);
    graph.addChild(1,13);
    graph.addChild(1,14);
    graph.addChild(2,21);
    graph.addChild(2,22);
    graph.addChild(2,23);
    graph.addChild(2,23);
    graph.addChild(2,24);
    graph.addChild(2,1);
    graph.addChild(3,2);
    graph.addChild(3,2);
    graph.addChild(5,2);

    cout<< "Expected 12, got:" << graph.cantNodes() <<endl;
}



void prueba_dfs1_ciclo_simple(){
    DGraph graph;
    graph.addChild(0,1);
    graph.addChild(0,2);
    graph.addChild(1,2);
    graph.addChild(2,0);
    graph.addChild(2,3);
    graph.addChild(3,3);
    cout << "Expected 1, got: " << graph.isCyclicDfs(0)<< endl;
}

void prueba_dfs1_ciclo_2_vertices(){
    DGraph graph;
    graph.addChild(0,1);
    graph.addChild(1,0);
    cout << "Expected 1, got: " << graph.isCyclicDfs(0) << endl;
}

void prueba_dfs1_ciclo_1_vertices(){
    DGraph graph;
    graph.addChild(0,0);
    cout << "Expected 1, got: " << graph.isCyclicDfs(0) << endl;
}

void prueba_dfs1_sin_ciclo_1(){
    DGraph graph;
    graph.addChild(0,1);
    graph.addChild(0,2);
    graph.addChild(1,3);
    cout << "Expected 0, got: " << graph.isCyclicDfs(0)<< endl;
}

void prueba_dfs1_sin_ciclo_2(){
    DGraph graph;
    graph.addChild(0,1);
    graph.addChild(2,0);
    cout << "Expected 0, got: " << graph.isCyclicDfs(0) << endl;

}

void prueba_dfs1_sin_ciclo_3(){
    DGraph graph;
    graph.addChild(0,1);
    cout << "Expected 0, got: " << graph.isCyclicDfs(0) << endl;
}

int main(){
    cout << "PROBANDING"<< true;
    prueba_addChildren();
    prueba_dfs1_ciclo_simple();
    prueba_dfs1_ciclo_2_vertices();
    prueba_dfs1_ciclo_1_vertices();
    prueba_dfs1_sin_ciclo_1();
    prueba_dfs1_sin_ciclo_2();
    prueba_dfs1_sin_ciclo_3();
    return 0;
}
