#include "trem.h"
#include <QtCore>
#include "mainwindow.h"
#include <iostream>


//Construtor
Trem::Trem(int ID, int x, int y){
    if(ID ==1){
        //inicializa os semáforos
        for(int i{0}; i<7; i++){
            regiao[i].release(1);
        }
        //inicializa o mutex
        mutex.release(1);
    }

    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 200;
}

void Trem::changeSpeed(int x){
    this->velocidade = x;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    //std::cout << "valor do semaforo 0: " << regiao[0].available() << "\n";
    while(true){
        if(velocidade == 200){
            while(velocidade == 200){
                msleep(1);
            }
        }
        switch(ID){
        case 1://Trem 1

            if (y == 30 && x <330){//se o Trem 1 estivre na aresta de cima
                if(x+10 == 320){//entrada na regiao critica 1
                    while(estado[0] == 0){//enquanto o estado do Trem 1 for 0, tenta acessar o mutex e mudar o estado
                        mutex.acquire(1);//trava o mutex para acessar o estado
                        if(estado[3]!= 3 && estado[1]!=4){//se o trem 4 não estiver na regiao 3 e o trem 2 não estiver na regiao 4
                            estado[0] = 1;//o trem 1 "pode" entrar na reigao 1, sem causa deadlock
                        }
                        mutex.release(1);//libera o mutex
                    }
                    if(estado[0]==1){//se o trem 1 puder entrar na regiao 1
                        regiao[0].acquire(1);//trava a regiao 1
                        //testa se pode avancar
                        //se puder entao avanca
                        x+=10;
                        //se nao puder fica parado
                    }
                }
                else x+=10;//enquanto nao chega na regiao critica avanca para a direita
            }

            else if (x == 330 && y < 150){//se o Trem 1 estiver na regiao critica 1
                if(y+10 == 140){//entrada na regiao 3
                    regiao[2].acquire(1);//trava a regiao 3
                    y+=10;//entra na regiao critica 3
                }

                else y+=10;//enquanto nao chega na regiao critica avanca para baixo
            }
            else if (x > 60 && y == 150){//se o trem 1 estiver na regiao critica 3
                if(x == 170){//se estiver na saida da regiao 3
                    x-=10;//sai da regiao
                    regiao[2].release(1);//libera a regiao 3
                }
                else if(x == 320){//ao entrar na regiao 3
                    mutex.acquire(1);//trava o mutex
                    estado[0] = 0;//muda o estado do trem 1 para 0 (saiu da regiao critica)
                    regiao[0].release(1);//libera a regiao 1
                    mutex.release(1);//libera o mutex
                    x-=10;//avanca
                }
                else x-=10;
            }
            else //se o Trem 1 estiver na aresta da esquerda
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2://Trem 2
            if (y == 30 && x <600){//se o Trem 2 na aresta de cima
                if(x == 350){//saindo da regiao 1
                    regiao[0].release(1);//libera a regiao 1
                    x+=10;//avanca

                }
                else if(x+10 == 590){//entrada na regiao critica 2, testa o mutex
                    //testa se pode avancar
                    if(regiao[4].available() && regiao[5].available()){//so tenta entrar na regiao 2 se as regioes 5 e 6 estiverem livres
                        //QThread::msleep(100);
                        regiao[1].acquire(1);//trava a regiao 2
                        //se puder avanca
                        x+=10;
                        //senao puder fica parado
                    }


                }
                else x+=10;//enquanto nao chega na regiao critica avanca para a direita
            }
            else if (x == 600 && y < 150){//se o Trem 2 estiver na regiao critica 2
                if(y+10 == 140){//entrada na regiao critica 5, testa o mutex
                    //testa se pode avancar
                    if(regiao[3].available() && regiao[6].available()){//so tenta entrar na 5 se a 4 e a 7 estiver livre
                        regiao[4].acquire(1);//trava a regiao 5
                        //se puder avanca
                        y+=10;
                        //senao puder fica parado
                    }

                }
                else y+=10;//enquanto nao chega na regiao critica avanca para baixo
            }
            else if (x > 330 && y == 150){//se o Trem 2 estiver na regiao critica 5
                if(x == 590){//saindo da regiao 2
                    regiao[1].release(1);//libera a regiao 2
                    x-=10;//avanca

                }
                else if(x-10 == 470){//entrada na regiao 4
                        while(estado[1] == 0){//enquanto o estado do Trem 2 for 0, tenta acessar o mutex e mudar o estado
                            mutex.acquire(1);//trava o mutex
                            if(estado[0] != 1 && estado[3] != 3){//se o Trem 1 não estiver na regiao 1 e o Trem 4 não estiver na regiao 3
                                estado[1] = 4;//Trem 2 "pode" entrar na regiao 4 sem causar deadlock
                            }
                            mutex.release(1);//libera o mutex
                        }
                        if(estado[1] == 4){//se o Trem 2 puder entrar na regiao 4
                            regiao[3].acquire(1);//trava a regiao 4
                            //se puder avanca
                            x-=10;
                        }
                }
                else if(x == 450){//se o Trem 2 estiver na regiao 4
                    regiao[4].release(1);//libera a regiao 5
                    x-=10;//avanca

                }

                else if(x-10 == 340){//entrando na regiao critica 1, testa o mutex
                    //testa se pode avancar
                    regiao[0].acquire(1);//trava a regiao 1
                    //se puder avanca
                    x-=10;
                    //senao fica parado

                }
                else x-=10;//enquanto nao chegar na regiao critica avanca para a esquerda

            }
            else//se o Trem 2 estiver na regiao critica 1
                if(y == 140){//saindo da regiao critica 4
                    mutex.acquire(1);//trava o mutex
                    estado[1] = 0;//muda o estado do Trem 2 para 0 (saiu da regiao critica)
                    regiao[3].release(1);//libera a regiao 4
                    mutex.release(1);
                    y-=10;//avanca
                }
               else y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x <870){//se o Trem 3 estiver na aresta de cima
                if(x == 620){//saindo da regiao critica 2
                    regiao[1].release(1);//libera a regiao 2
                    x+=10;//avanca
                }
                else x+=10;
            }

            else if (x == 870 && y < 150){//se o Trem 3 estiver na aresta da direita
                y+=10;
            }

            else if (x > 600 && y == 150){//se o Trem 3 estiver na aresta de baixo
                if(x-10 == 740){//entrada na regiao critica 6, testa o mutex
                    //testa se pode entrar
                    if(regiao[4].available() && regiao[1].available()){//so tenta entrar na regiao 6 se as regioes 5 e 2 estiverem livres
                        regiao[5].acquire(1);//trava a regiao 6
                        //se puder avanca
                        x-=10;
                        //senao fica parado

                    }

                }
                else if(x-10 == 610){//entrada na regiao critica 2, testa o mutex
                    //testa se pode entrar
                    regiao[1].acquire(1);//trava a regiao 2
                    //se puder avanca
                    x-=10;
                    //senao fica parado

                }
                else x-=10;//enquanto nao chegar na regiao critica, avanca para a esquerda
            }

            else{//se o Trem 3 estiver na regiao critica 2
                if(y == 140){//saindo da regiao critica 6
                    regiao[5].release(1);//libera a regiao 6
                    y-=10;//avanca

                }
                else y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <460){//se o Trem 4 estiver na aresta de cima
                if(x+10 == 320){//entrada na regiao 4
                    regiao[3].acquire(1);//trava a regiao 4
                    x+=10;//avanca

                }
                else if(x == 350){//saindo da regiao critica 3
                    mutex.acquire(1);//trava o mutex
                    estado[3] = 0;//muda o estado do trem 4 (saiu da regiao critica)
                    regiao[2].release(1);//libera a regiao 3
                    mutex.release(1);//libera o mutex
                    x+=10;//avanca

                }
                else if(x+10 == 450){//entrada na regiao critica 7, testa o mutex
                    //testat se pode entrar
                    regiao[6].acquire(1);//trava a regiao 7
                    //se puder avanca
                    x+=10;
                    //senao fica parado

                }
                else x+=10;//enquanto nao chegar na regiao critica, avanca para a direita
            }
            else if (x == 460 && y < 270){//se o Trem 4 estiver na regiao critica 7
                if(y == 160){
                    regiao[3].release(1);//libera a regiao 4
                    y+=10;//avanca
                }
                else y+=10;
            }
            else if (x > 190 && y == 270){//se o Trem 4 estiver na aresta de baixo
                if(x == 440){//saida da regiao critica 7
                    regiao[6].release(1);//libera a regiao 7
                    x-=10;//avanca
                }
                else x-=10;
            }
            else{//se o Trem 4 estiver na aresta da esquerda
                if(y-10 == 160){//entrada na regiao critica 3
                    while(estado[3] == 0){//enquanto o estado do trem 4 for 0, tenta acessar o mutex e mudar o estado
                        mutex.acquire(1);//trava o mutex
                        if(estado[0] != 1 && estado[1]!= 4){//se o trem 1 não estiver na regiao 1 e o trem 2 não estiver na regiao 4
                            estado[3] = 3;//trem 4 "pode" entrar na regiao 3 sem causar deadlock

                        }
                        mutex.release(1);//libera o mutex
                    }
                    if(estado[3] == 3){//se o trem 4 puder entrar na regiao 3
                        //testa se pode avancar
                        regiao[2].acquire(1);//trava a regiao 3
                        //se puder avanca
                        y-=10;
                        //senao fica parado
                    }
                }
                else y-=10;//enquanto nao chegar na regiao critica avanca para cima
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <730){//se o Trem 5 estiver na regiao critica 5
                if(x == 480){//saindo da regiao 7
                    regiao[6].release(1);//libera a regiao 7
                    x+=10;//avanca
                }
                else if(x == 620){//saida da regiao 5
                    regiao[4].release(1);//libera a regiao 5
                    x+=10;//avanca

                }
                else if(x+10 == 590){//entrada na regiao critica 6, testa o mutex
                    //testa se pode avancar
                    regiao[5].acquire(1);//trava a regiao 6
                    //se puder avanca
                    x+=10;
                    //senao fica parado

                }
                else x+=10;//enquanto nao chegar na regiao critica avanca para direita
            }
            else if (x == 730 && y < 270){//se o Trem 5 estiver na aresta da direita
                if(y == 170){//saida da regiao critica 6
                    regiao[5].release(1);//libera a regiao 6
                    y+=10;//avanca

                }
                else y+=10;
            }
            else if (x > 460 && y == 270){//se o Trem 5 estiver na aresta de baixo
                if(x-10 == 470){//entrada na regiao critica 7, testa o mutex
                    if(regiao[3].available() && regiao[4].available()){//so tenta entrar na regiao 7 se as regioes 4 e 5 estiverem livres
                        //testa se pode avancar
                        regiao[6].acquire(1);//trava a regiao 7
                        //se puder avanca
                        x-=10;
                        //senao fica parado
                    }


                }
                else x-=10;//enquanto nao chegar na regiao critica avanca para a esquerda
            }
            else{//se o Trem 5 estiver na regiao critica 7
                if(y-10 == 160){//entrada na regiao critica 5, testa o mutex
                    //testa se pode avancar
                    regiao[4].acquire(1);//trava a regiao 5
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
