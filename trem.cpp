#include "trem.h"
#include <QtCore>
#include "mainwindow.h"
#include <iostream>


//Construtor
Trem::Trem(int ID, int x, int y){
    if(ID ==1){
        for(int i{0}; i<7; i++)
            regiao[i].release(1);
    }

    std::cout <<"trem" << ID << " valor do semaforo 0: " << regiao[0].available() << "\n";
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 50;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    //std::cout << "valor do semaforo 0: " << regiao[0].available() << "\n";
    while(true){
        switch(ID){
        case 1://Trem 1

            if (y == 30 && x <330){//se o Trem 1 estivre na aresta de cima

                if(x+10 == 330){//entrada na regiao critica 1, testa o mutex q
                    //regiao[0].acquire(1);//trava a regiao 1
                    //testa se pode avancar
                    //se puder entao avanca
                    x+=10;
                    //se nao puder fica parado
                }
                else x+=10;//enquanto nao chega na regiao critica avanca para a direita
            }

            else if (x == 330 && y < 150){//se o Trem 1 estiver na regiao critica 1

                if(y+10 == 150){//entrada na regiao critica 3, testa o mutex

                    //testa se pode avancar
                    //se puder avanca
                    y+=10;//entra na regiao critica 3
                    //se nao puder fica parado
                }
                else y+=10;//enquanto nao chega na regiao critica avanca para baixo
            }
            else if (x > 60 && y == 150){//se o trem 1 estiver na regiao critica 3
                if(x == 320){
                    //regiao[0].release(1);
                }
                x-=10;
            }
            else //se o Trem 1 estiver na aresta da esquerda
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2://Trem 2
            if (y == 30 && x <600){//se o Trem 2 estiver prestes a aresta de cima

                if(x==340){
                    //regiao[0].release(1);//libera a regiao critica 1
                    x+=10;//avanca
                }

                else if(x+10 == 600){//entrada na regiao critica 2, testa o mutex
                    //testa se pode avancar
                    //se puder avanca
                    x+=10;
                    //senao puder fica parado
                }
                else x+=10;//enquanto nao chega na regiao critica avanca para a direita
            }
            else if (x == 600 && y < 150){//se o Trem 2 estiver na regiao critica 2
                if(y+10 == 150){//entrada na regiao critica 5, testa o mutex
                    //testa se pode avancar
                    //se puder avanca
                    y+=10;
                    //senao puder fica parado
                }
                else y+=10;//enquanto nao chega na regiao critica avanca para baixo
            }
            else if (x > 330 && y == 150){//se o Trem 2 estiver na regiao critica 5
                if(x-10 == 460){//entrada na regiao critica 4, testa o mutex
                    //testa se pode avancar
                    //se puder avanca
                    x-=10;
                    //senao fica parado
                }
                else if(x-10 == 330){//entrando na regiao critica 1, testa o mutex
                    //regiao[0].acquire(1);//trava a regiao 1
                    //testa se pode avancar
                    //se puder avanca
                    x-=10;
                    //senao fica parado

                }
                else x-=10;//enquanto nao chegar na regiao critica avanca para a esquerda

            }
            else//se o Trem 2 estiver na regiao critica 1
               y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x <870){//se o Trem 3 estiver na aresta de cima
                x+=10;
            }

            else if (x == 870 && y < 150){//se o Trem 3 estiver na aresta da direita
                y+=10;
            }

            else if (x > 600 && y == 150){//se o Trem 3 estiver na aresta de baixo
                if(x-10 == 730){//entrada na regiao critica 6, testa o mutex
                    //testa se pode entrar
                    //se puder avanca
                    x-=10;
                    //senao fica parado

                }
                else if(x-10 == 600){//entrada na regiao critica 2, testa o mutex
                    //testa se pode entrar
                    //se puder avanca
                    x-=10;
                    //senao fica parado

                }
                else x-=10;//enquanto nao chegar na regiao critica, avanca para a esquerda
            }

            else//se o Trem 3 estiver na aresta da esquerda
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <460){//se o Trem 4 estiver na aresta de cima
                if(x+10 == 330){//entrada na regiao critica 4, testa o mutex
                    //testa se pode entrar
                    //se puder avanca
                    x+=10;
                    //senao fica parado

                }
                else if(x+10 == 460){//entrada na regiao critica 7, testa o mutex
                    //testat se pode entrar
                    //se puder avanca
                    x+=10;
                    //senao fica parado

                }
                else x+=10;//enquanto nao chegar na regiao critica, avanca para a direita
            }
            else if (x == 460 && y < 280){//se o Trem 4 estiver na regiao critica 7
                y+=10;
            }
            else if (x > 190 && y == 280){//se o Trem 4 estiver na aresta de baixo
                x-=10;
            }
            else{//se o Trem 4 estiver na aresta da esquerda
                if(y-10 == 150){//entrada na regiao critica 3, testa o mutex
                    //testa se pode avancar
                    //se puder avanca
                    y-=10;
                    //senao fica parado

                }
                else y-=10;//enquanto nao chegar na regiao critica avanca para cima
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <730){//se o Trem 5 estiver na regiao critica 5
                if(x+10 == 600){//entrada na regiao critica 6, testa o mutex
                    //testa se pode avancar
                    //se puder avanca
                    x+=10;
                    //senao fica parado

                }
                else x+=10;//enquanto nao chegar na regiao critica avanca para direita
            }
            else if (x == 730 && y < 280){//se o Trem 5 estiver na aresta da direita
                y+=10;
            }
            else if (x > 460 && y == 280){//se o Trem 5 estiver na aresta de baixo
                if(x-10 == 460){//entrada na regiao critica 7, testa o mutex
                    //testa se pode avancar
                    //se puder avanca
                    x-=10;
                    //senao fica parado

                }
                else x-=10;//enquanto nao chegar na regiao critica avanca para a esquerda
            }
            else{//se o Trem 5 estiver na regiao critica 7
                if(y-10 == 150){//entrada na regiao critica 5, testa o mutex
                    //testa se pode avancar
                    //se puder avanca
                    y-=10;
                    //senao fica parado

                }
                else y-=10;//enquanto nao chegar na regiao critica avanca para cima
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}
