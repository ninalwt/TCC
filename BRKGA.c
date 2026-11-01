#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//---------------------------------------------------------------------------------------------------------------------------------------------
/* struct vert, guarda as duas coordenadas de um vertice*/
typedef struct _vertice{
    double x;
    double y;
}vert;
//---------------------------------------------------------------------------------------------------------------------------------------------
/* struct pol, guarda o numero de vertices e o endereco de onde teremos um vetor de vertices*/
typedef struct _poligono{
    int n; //numero de vertices
    vert *ponto; //ponto[0].x  ponto[0].y - guarda o endereco de algum lugar que vai ter o vetor de pontos
}pol;
//---------------------------------------------------------------------------------------------------------------------------------------------
/* struc nfp, guarda o numero de partes do nfp e o endereco para o vetor de cada parte (que nem um item, mas sem infos extras)*/
typedef struct _nfp{
    int partes; //numero de partes do nfp
    pol *polig; //cada parte eh um poligono
}nfp;
//---------------------------------------------------------------------------------------------------------------------------------------------
/* struct item, guarda todas as informacoes necessarias de cada item*/
typedef struct _item{
    int partes; //numero de partes do item
    pol *polig; //cada parte do item eh um poligono
    double esquerda; //ponto mais a esquerda
    double direita; //ponto mais a direita
    double alto; //ponto mais alto
    double baixo; //ponto mais baixo
    int copias; //demanda do item
    nfp *nfps; //guarda o endereco de um lugar que vai ter uma struct tipo pol (nfp desse item com cada item)
    vert *pfinal; //guarda o endereco de um lugar que vai ter uma struct tipo vert (onde cada copia do item foi alocada)
    int cop_alocad; //quantidade de quantas copias ja foram alocadas
}item;  
//---------------------------------------------------------------------------------------------------------------------------------------------
/* struct cromossomo, que associa uma key (um racional de 0 a 1) a um item*/
typedef struct _cromossomo{
    int item; //numero de algum item da instancia
    double key; //valor aleatorio associado aquele item
}cromo;
//---------------------------------------------------------------------------------------------------------------------------------------------
/* struct individuo, que guarda uma ordenacao especifica dos itens, ou seja, uma solucao da instancia*/
typedef struct _individuo{
    cromo *indice; //o indice com as keys que constituem o individuo - depende do numero total de itens da instancia
    double *key_ordem_original; //guarda as keys na ordem certa original (batendo com o vetor de itens ordenado)
    double fitness; //valor usado pra avaliar quao bom eh o individuo (nesse caso, largura final)
}ind;  
//---------------------------------------------------------------------------------------------------------------------------------------------
/* struct populacao, que guarda todos os individuos que serao comparados a cada geracao*/
typedef struct _populacao{
    ind *individuos; //ponteiro para os individuos de uma populacao
    int total_ind; //colocar quantos individuos quero por geracao aqui
    int total_ger; //numero de geracoes que o codigo inteiro deve rodar
    int qtd_elite; //qual a quantidade de cada geracao sera dado como elite
    int qtd_cruz; //qual a quantidade de cada geracao sera feita a partir de cruzamento
    int qtd_mut; //qual a quantidade de cada geracao sera feita a partir da mutacao.
    double chances_cruz; //guarda quais as chances de, durante o cruzamento, a key vir da elite
    ind *lixo; //ponteiro para individuos novos criados por cruzamento
}pop;  
//---------------------------------------------------------------------------------------------------------------------------------------------
//=============================================================================================================================================
/* funcao para elevar um valor ao quadrado*/
double sq(double x){
    return (x * x);
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que abre todos os arquivos de NFPs e aloca as informacoes recebidas*/
int LerNFPs(item *itens, int numitens, char *endereco){
    char lixo;
    char nome[400];
    int i, j, k, m;

    FILE *lenfp;

    for(i = 0; i<numitens; i++){        
        itens[i].nfps = (nfp*)malloc((numitens)*sizeof(nfp));
        if(itens[i].nfps == NULL){
            printf("erro no malloc dos nfps do item %d", i);
            return -1; //caso vazio, retorna -1
        }

        for(j = 0; j<numitens; j++){
            sprintf(nome, "%s/NFP/NFP_%d_0_%d_0.txt", endereco, j+1, i+1); //i eh o NFP girando em torno de j
            //note que, como os itens sao dados a partir de 1 e os dados contamos de 0 em diante, vou olhar o nfp com os numeros em 1 a mais
            lenfp = fopen(nome, "r");
            if(lenfp == NULL){
                printf("erro na leitura de algum arquivo de NFP");
            }else{

                do{
                    fscanf(lenfp, "%c", &lixo);
                }while(lixo != '#');

                fscanf(lenfp, "%d", &itens[i].nfps[j].partes);

                itens[i].nfps[j].polig = (pol*)malloc((itens[i].nfps[j].partes*sizeof(pol)));
                if(itens[i].nfps[j].polig == NULL){
                    printf("erro no malloc do vertices das partes do nfp %d do item %d",j, i);
                    return -1;
                }

                for(k = 0; k < itens[i].nfps[j].partes; k++){
                    do{
                        fscanf(lenfp, "%c", &lixo);
                    }while(lixo != '#');

                    fscanf(lenfp, "%d", &itens[i].nfps[j].polig[k].n);
                    itens[i].nfps[j].polig[k].ponto = (vert*)malloc((itens[i].nfps[j].polig[k].n)*sizeof(vert));
                    if(itens[i].nfps[j].polig[k].ponto == NULL){
                        printf("erro no malloc do vertices da parte %d do nfp %d do item %d", k, j, i);
                        return -1;
                    }

                    do{
                        fscanf(lenfp, "%c", &lixo);
                    }while(lixo != '#');

                    for(m = 0; m<(itens[i].nfps[j].polig[k].n); m++){ //le as coordenadas de cada vertice do NFP
                        fscanf(lenfp, "%lf %lf", &itens[i].nfps[j].polig[k].ponto[m].x, &itens[i].nfps[j].polig[k].ponto[m].y);
                    }
                }    
                fclose(lenfp);
        }
        }    
    }
    return 0;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que abre arquivos para ler as informacoes gerais (altura, numero de itens, demanda de cada item) e aloca-las no vetor de itens*/
item *LerDados(int *numitens, double *altura, char *endereco){
    char lixo, nome[21];
    int i, j, k, numvertices, checarNFP, cortes, defeitos, centro[2];
    int it; //utilizar outro contador quando estiver checando qual item estou vendo no arquivo, para caso esteja fora de ordem
    FILE *infos, *listait;
    double largura;
    char texto[70];

    sprintf(texto, "%s/general_data.txt", endereco);
    infos = fopen(texto, "r");
    if(infos == NULL){
        printf("deu erro na leitura dos dados gerais");
        return NULL;
    }else{
        do{
            fscanf(infos, "%c", &lixo);
        }while(lixo != '#');

        fscanf(infos, "%lf", &largura);

        do{
            fscanf(infos, "%c", &lixo);
        }while(lixo != '#');

        fscanf(infos, "%lf", altura);

        do{
            fscanf(infos, "%c", &lixo);
        }while(lixo != '#');

        fscanf(infos, "%d", &cortes);

        do{
            fscanf(infos, "%c", &lixo);
        }while(lixo != '#');

        fscanf(infos, "%d", &defeitos);

        do{
            fscanf(infos, "%c", &lixo);
        }while(lixo != '#');

        fscanf(infos, "%d", numitens);

        item *itens;
        itens = (item*) malloc((*numitens)*sizeof(item));
        if(itens == NULL){
            printf("erro do malloc dos itens");
            return NULL;
        }

        for(i = 0; i<*numitens; i++){
            itens[i].copias = 0;
            do{
                fscanf(infos, "%c", &lixo);
            }while(lixo != '#');

            fscanf(infos, "%d", &it); //variavel de qual eh o item - caso fora de ordem
            it--; // -------> Como os itens comecam de 1 e o vetor comeca de 0, precisa subtrair 1 // os itens estarao no espaco 0 ate m-1
            do{
                fscanf(infos, "%c", &lixo);
            }while(lixo != '#');

            fscanf(infos, "%d", &itens[it].copias);

            do{
                fscanf(infos, "%c", &lixo);
            }while(lixo != '#');

            fscanf(infos, "%c", &lixo); //rotacoes nao estao sendo usadas nesse codigo

            do{
                fscanf(infos, "%c", &lixo);
            }while(lixo != '#');

            fscanf(infos, "%c %c", &lixo, &lixo);
        }
        fclose(infos);

        for(i = 0; i<*numitens; i++){
            sprintf(nome, "%s/piece%d.txt", endereco, i+1); //note que, como os itens sao dados a partir de 1 e os dados contamos de 0 em diante, vou olhar o nfp com os numeros em 1 a mais
            listait = fopen(nome, "r");
            if(listait == NULL){
                printf("deu erro na leitura de um arquivo de item");
                return NULL;
            }else{
                do{
                    fscanf(listait, "%c", &lixo);
                }while(lixo != '#');

                fscanf(listait, "%d %d", &centro[0], &centro[1]);

                do{
                    fscanf(listait, "%c", &lixo);
                }while(lixo != '#');

                fscanf(listait, "%d", &itens[i].partes);//li o numero de partes do item
                itens[i].polig = (pol*)malloc((itens[i].partes)*sizeof(pol));
                if(itens[i].polig == NULL){
                    printf("erro no malloc das partes do item %d", it);
                    return NULL;
                }

                for(j = 0; j < itens[i].partes; j++){
                    do{
                        fscanf(listait, "%c", &lixo);
                    }while(lixo != '#');


                    fscanf(listait, "%d", &itens[i].polig[j].n);
                    numvertices = itens[i].polig[j].n;


                    itens[i].polig[j].ponto = (vert*) malloc(numvertices*sizeof(vert));
                    if(itens[i].polig[j].ponto == NULL){
                        printf("erro do malloc dos vertices do item %d", it);
                        return NULL;
                    }

                    do{
                        fscanf(listait, "%c", &lixo);
                    }while(lixo != '#');

                    for(k = 0; k<numvertices; k++){
                        fscanf(listait, "%lf %lf", &itens[i].polig[j].ponto[k].x, &itens[i].polig[j].ponto[k].y);
                    }
                }
                fclose(listait);
            }
        }

        checarNFP = LerNFPs(itens, *numitens, endereco);
        if(checarNFP != 0){
            printf("algo deu errado checando nfps...\n");
        }

        return itens;

    }
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que calcula o numero total de itens, considerando a quantidade de copias de cada um*/
int NumTotal(item *itens, int numitens){
    int i, numtotal = 0;

    for(i=0; i<numitens; i++){
        numtotal += itens[i].copias;
    }

    return numtotal;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para calculo da area de um poligono, a partir da formula de determinantes com vertices, que precisam estar ordenados. 
se os vertices estiverem no sentido horario, o resultado eh o oposto, entao realizamos essa correcao*/
double Area(item it_atual){
    double area;
    int i, j;
    area = 0;

    for(i = 0; i<it_atual.partes; i++){
        for(j = 0; j<(it_atual.polig[i].n); j++){
            area += (it_atual.polig[i].ponto[j].x*it_atual.polig[i].ponto[(j+1)%it_atual.polig[i].n].y) - (it_atual.polig[i].ponto[(j+1)%it_atual.polig[i].n].x*it_atual.polig[i].ponto[j].y);
        }
    }
    area = area/2;

    if(area < 0 ){
        return -area;
    }
    return area;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para calcular o ponto mais a esquerda de um poligono*/
double Esquerda(item it_atual){
    double esquerda;
    int i, j;

    esquerda = it_atual.polig[0].ponto[0].x;
    for(i = 0; i<it_atual.partes; i++){
        for(j = 0; j<it_atual.polig[i].n; j++){
            if(it_atual.polig[i].ponto[j].x < esquerda){
                esquerda = it_atual.polig[i].ponto[j].x;
            }
        }
    }
    return esquerda;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para calcular o ponto mais a direita de um poligono*/
double Direita(item it_atual){
    double direita;
    int i, j;

    direita = it_atual.polig[0].ponto[0].x;
    for(i = 0; i<it_atual.partes; i++){
        for(j = 0; j<it_atual.polig[i].n; j++){
            if(it_atual.polig[i].ponto[j].x > direita){
                direita = it_atual.polig[i].ponto[j].x;
            }
        }
    }
    return direita;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para calcular o ponto mais acima de um poligono*/
double Alto(item it_atual){
    double alto;
    int i, j;

    alto = it_atual.polig[0].ponto[0].y;
    for(i = 0; i<it_atual.partes; i++){
        for(j = 0; j<it_atual.polig[i].n; j++){
            if(it_atual.polig[i].ponto[j].y > alto){
                alto = it_atual.polig[i].ponto[j].y;
            }
        }
    }
    return alto;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para calcular o ponto mais abaixo de um poligono*/
double Baixo(item it_atual){
    double baixo;
    int i, j;

    baixo = it_atual.polig[0].ponto[0].y;
    for(i = 0; i<it_atual.partes; i++){
        for(j = 0; j<it_atual.polig[i].n; j++){
            if(it_atual.polig[i].ponto[j].y < baixo){
                baixo = it_atual.polig[i].ponto[j].y;
            }
        }
    }
    return baixo;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para calcular o comprimento de um poligono (diferenca entre maior e menor x)*/
double Comprimento(item it_atual){
    double comp;

    comp = it_atual.direita - it_atual.esquerda;
    return comp;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para calcular a largura de um poligono (diferenca entre maior e menor y)*/
double Largura(item it_atual){
    double larg;

    larg = it_atual.alto - it_atual.baixo;
    return larg;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para calcular o maior comprimento possivel do recipiente*/
double MuitoGrande(item *itens, int numitens){
    double mg = 0;
    int i;

    for(i = 0; i<numitens; i++){
        mg += (itens[i].direita - itens[i].esquerda)*itens[i].copias;
    }
    return mg+1;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que constroi um cromossomo com as keys referentes as areas de cada item*/
void ListarArea(item *itens, int numtotal, int numitens, ind individuo){
    int i, j, k = 0;
    double maior = 0;
    for(i = 0; i<numitens; i++){
        for(j = 0; j<itens[i].copias; j++){
            individuo.indice[k].key = Area(itens[i]);
            if(individuo.indice[k].key > maior){
                maior = individuo.indice[k].key; //ve qual maior valor
            }
            k++;
        }
    }

    for(i = 0; i<numtotal; i++){
        //quero ordenar de forma crescente as keys mas de forma a ficar decrescente das areas, ent troca pra 1 menos o valor
        individuo.indice[i].key = 1 - individuo.indice[i].key/maior; //normaliza todas as keys
        individuo.key_ordem_original[i] = individuo.indice[i].key;
    }

}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que constroi um cromossomo com as keys referentes aos menores retangulos que englobam cada item*/
void ListarRetangulos(item *itens, int numtotal, int numitens, ind individuo){
    int i, j, k = 0;
    double maior = 0;
    for(i = 0; i<numitens; i++){
        for(j = 0; j<itens[i].copias; j++){
            individuo.indice[k].key = (itens[i].direita - itens[i].esquerda)*(itens[i].alto - itens[i].baixo);
            if(individuo.indice[k].key > maior){
                maior = individuo.indice[k].key;
            }
            k++;
        }
    }

    for(i = 0; i<numtotal; i++){
        //quero ordenar de forma crescente as keys mas de forma a ficar decrescente das areas, ent troca pra 1 menos o valor
        individuo.indice[i].key = 1 - individuo.indice[i].key/maior;
        individuo.key_ordem_original[i] = individuo.indice[i].key;
    }

}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que constroi um cromossomo com as keys referentes aos comprimentos (horizontal) de cada item*/
void ListarX(item *itens, int numtotal, int numitens, ind individuo){
    int i, j, k = 0;  
    double maior = 0;

    for(i = 0; i<numitens; i++){
        for(j = 0; j<itens[i].copias; j++){
            individuo.indice[k].key = itens[i].direita - itens[i].esquerda;
            if(individuo.indice[k].key > maior){
                maior = individuo.indice[k].key;
            }
            k++;
        }
    }

    for(i = 0; i<numtotal; i++){
        //quero ordenar de forma crescente as keys mas de forma a ficar decrescente dos comprimentos, ent troca pra 1 menos o valor
        individuo.indice[i].key = 1 - individuo.indice[i].key/maior;
        individuo.key_ordem_original[i] = individuo.indice[i].key;
    }
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que constroi um cromossomo com as keys referentes as proporcoes entre a area e o menor retangulo que enquadra cada item*/
void ListarPropAreas(item *itens, int numtotal, int numitens, ind individuo){
    int i, j, k = 0;
    for(i = 0; i<numitens; i++){
        for(j = 0; j<itens[i].copias; j++){
            individuo.indice[k].key = Area(itens[i])/((itens[i].direita - itens[i].esquerda)*(itens[i].alto - itens[i].baixo));
            individuo.key_ordem_original[k] = individuo.indice[k].key;
            k++; //como esse eh o unico metodo que quero ordenar de forma decrescente, nao preciso inverter a ordem
        }
    }
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para calcular a interseccao entre dois segmentos. recebe 4 verts p - lista dos dois segmentos e endereco do espaco para de 2 vert "atual" - que sera alterado com os valores recebidos (caso segmentos sejam colineares - o mesmo - retorna os 2 pontos mais extremos da interseccao)*/
int Intersec(vert* p, vert*atual){

    double num1, num2, t, u, denom, maiord, dist;
    int i, j, pontoa, pontod;

    denom = ((p[3].x-p[2].x)*(p[1].y-p[0].y))-((p[3].y-p[2].y)*(p[1].x-p[0].x));
    num1 = ((p[3].x-p[2].x)*(p[2].y-p[0].y))-((p[3].y-p[2].y)*(p[2].x-p[0].x));
    num2 = ((p[1].x-p[0].x)*(p[2].y-p[0].y))-((p[1].y-p[0].y)*(p[2].x-p[0].x));

    t = num1/denom;
    u = num2/denom;

    maiord = -1;

    if((fabs(denom)) <= 1.0e-5 && fabs(num1) <= 1.0e-5){ //caso onde os 4 pontos sao colineares
        if((((p[0].x<=p[2].x)&&(p[2].x<=p[1].x))&&((p[0].y<=p[2].y)&&(p[2].y<=p[1].y)))||(((p[0].x<=p[3].x)&&(p[3].x<=p[1].x))&&((p[0].y<=p[3].y)&&(p[3].y<=p[1].y)))||(((p[1].x<=p[2].x)&&(p[2].x<=p[0].x))&&((p[1].y<=p[2].y)&&(p[2].y<=p[0].y)))||(((p[1].x<=p[3].x)&&(p[3].x<=p[0].x))&&((p[1].y<=p[3].y)&&(p[3].y<=p[0].y)))){//checar se se interceptam
            for(i=0; i<3; i++){
                for(j=1; j<4; j++){
                    dist = sqrt(sq(p[j].x-p[i].x) + sq(p[j].y-p[i].y));
                    if(dist>maiord){
                        maiord = dist;
                        pontoa = i;
                        pontod = j;
                    }
                }
            }
            for(i=0; i<4; i++){
                if((i!=pontoa)&&(i!=pontod)){
                    atual[0] = p[i];
                    for(j = i+1; j<4; j++){
                        if((j!=pontoa)&&(j!=pontod)){
                            atual[1] = p[j];
                            return 2; //calculou 2 interseccoes
                        }
                    }
                }
            }
        }
    }else if ((fabs(denom)) >= 1.0e-5){ //caso os segmentos nao sejam paralelos
        if((-1.0e-5<=t)&&(t<=(1+1.0e-5))&&(-1.0e-5<=u)&&(u<=(1+1.0e-5))){
            atual[0].x = p[0].x + t*(p[1].x - p[0].x);
            atual[0].y = p[0].y + t*(p[1].y - p[0].y);
            return 1; //calculou 1 interseccao
        }
    }
     return 0; //calculou 0 interseccoes
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que checa se o vert p ta fora do pol nfp deslocado (para a posicao final do item)*/
int Fora(vert p, nfp nfps, vert desloca){
    int i, j, k, fora = 0;
    double valor;
    nfp nfp_desloc;

    nfp_desloc.polig = (pol*)malloc(nfps.partes*sizeof(pol));
    if(nfp_desloc.polig == NULL){
        printf("deu erro na criacao das partes do nfp deslocado");
        return -1;
    }

    for(i = 0; i < nfps.partes; i++){
        nfp_desloc.polig[i].ponto = (vert*)malloc((nfps.polig[i].n)*sizeof(vert));
        if(nfp_desloc.polig[i].ponto == NULL){
            printf("deu erro na parte %d do nfp deslocado", i);
            return -1;
        }
    }

    for(i = 0; i<nfps.partes; i++){
        for(j = 0; j<nfps.polig[i].n; j++){
            nfp_desloc.polig[i].ponto[j].x = nfps.polig[i].ponto[j].x + desloca.x;
            nfp_desloc.polig[i].ponto[j].y = nfps.polig[i].ponto[j].y + desloca.y;
        }
    }

    for(i = 0; i<nfps.partes; i++){
        for(j = 0; j<nfps.polig[i].n; j++){
            valor = ((nfp_desloc.polig[i].ponto[j].x-nfp_desloc.polig[i].ponto[(j+1)%nfps.polig[i].n].x)*(nfp_desloc.polig[i].ponto[j].y-p.y))-((nfp_desloc.polig[i].ponto[j].y-nfp_desloc.polig[i].ponto[(j+1)%nfps.polig[i].n].y)*(nfp_desloc.polig[i].ponto[j].x-p.x));
            if(valor <=1.0e-5){
                fora++;
                break;
            }
        }
    }


    if(fora>=nfps.partes){
        for(k = 0; k < nfps.partes; k++){
            free(nfp_desloc.polig[k].ponto);
        }
        free(nfp_desloc.polig);
        return 1; //verdadeiro - esta fora
    }

    for(k = 0; k < nfps.partes; k++){
        free(nfp_desloc.polig[k].ponto);
    }
    free(nfp_desloc.polig);
    return 0; //falso - esta dentro
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que verifica se um ponto eh valido para alocar um item, checando se esta fora do ifp ou dentro de algum nfp*/
int Valido(vert pt_atual, int it_atual, item *itens, int numitens, double altura){
    int i, j;

    if((pt_atual.x<(-itens[it_atual].esquerda))||(pt_atual.y>(altura - itens[it_atual].alto))||(pt_atual.y<(-itens[it_atual].baixo))){
        return 0; //invalido - fora do ifp
    }

    for(i=0; i<numitens; i++){
        for(j = 0; j<itens[i].cop_alocad; j++){
            if(Fora(pt_atual, itens[it_atual].nfps[i], itens[i].pfinal[j]) == 0){
                return 0; //invalido - dentro de algum nfp
            }
        }
    }
    return 1; //valido
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que aloca uma copia de um item, analisando cada interseccao possivel e, caso um ponto seja melhor que
o candidato anterior, vendo se ele eh um ponto valido para alocacao. caso seja, vira o novo candidato*/
vert AlocaUm(int it_atual, item *itens, int numitens, double mtgd, double altura){
    int i, j, k, m, n, n_int, f, g, h, alfa, beta;
    vert candidato, ifp[4];
    candidato.x = mtgd;
    candidato.y = 0;

    //checando o ponto inferior esquerdo do ifp primeiro - melhor alocacao possivel
    ifp[1].x = -itens[it_atual].esquerda;
    ifp[1].y = -itens[it_atual].baixo;
    if(Valido(ifp[1], it_atual, itens, numitens, altura) == 1){
        return ifp[1];
    }

    //checando as interseccoes entre ifps e nfps
    ifp[0].x = mtgd;
    ifp[0].y = -itens[it_atual].baixo;

    ifp[2].x = -itens[it_atual].esquerda;;
    ifp[2].y = altura - itens[it_atual].alto;

    ifp[3].x = mtgd;
    ifp[3].y = altura - itens[it_atual].alto;

    vert* p = malloc(4*sizeof(vert));
    if(p == NULL){
        printf("erro no malloc dos quatro pontos p - utilizados para verificar as interseccoes entre dois segmentos");
        return candidato;
    }

    vert* atual = malloc(2*sizeof(vert));
    if(atual == NULL){
        printf("erro no malloc dos vertices atuais");
        return candidato;
    }

    for(i = 0; i<numitens; i++){ //para cada item i
        for(j = 0; j<itens[i].cop_alocad; j++){ // ve quantas copias foram alocadas
            for(alfa = 0; alfa < itens[it_atual].nfps[i].partes; alfa++){ //alfa olha cada parte do nfp
                for(k = 0; k<itens[it_atual].nfps[i].polig[alfa].n; k++){ // k passa por cada aresta da parte alfa do nfp
                    p[0].x = itens[it_atual].nfps[i].polig[alfa].ponto[k].x + itens[i].pfinal[j].x; //os dois primeiros pontos sao nfps deslocados para a posicao da copia j
                    p[0].y = itens[it_atual].nfps[i].polig[alfa].ponto[k].y + itens[i].pfinal[j].y;
                    p[1].x = itens[it_atual].nfps[i].polig[alfa].ponto[(k+1)%itens[it_atual].nfps[i].polig[alfa].n].x + itens[i].pfinal[j].x;
                    p[1].y = itens[it_atual].nfps[i].polig[alfa].ponto[(k+1)%itens[it_atual].nfps[i].polig[alfa].n].y + itens[i].pfinal[j].y;
                    for(m = 0; m<3; m++){ //os outros dois pontos sao as arestas do ifp - tirando a aresta vertical da direita (infinita)
                        p[2] = ifp[m]; 
                        p[3] = ifp[m+1];
                        n_int = Intersec(p, atual); //checa as interseccoes e devolve quantas sao
                        for(n = 0; n<n_int; n++){ //passa por todas as intersec pra ver se sao validas
                            if((atual[n].x <candidato.x)||(fabs(atual[n].x-candidato.x)<= 1.0e-5 && atual[n].y<candidato.y)){
                                if(Valido(atual[n], it_atual, itens, numitens, altura) == 1){
                                    candidato = atual[n];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //checando as interseccoes entre nfps
    for(i = 0; i<numitens; i++){ //para cada item
        for(j = 0; j<itens[i].cop_alocad; j++){ //ve quantas copias foram alocadas
            for(alfa = 0; alfa<itens[it_atual].nfps[i].partes; alfa++){ //alfa olha cada parte do nfp
                for(k = 0; k<itens[it_atual].nfps[i].polig[alfa].n; k++){ // k passa por cada aresta da parte alfa do nfp
                    p[0].x = itens[it_atual].nfps[i].polig[alfa].ponto[k].x + itens[i].pfinal[j].x; //os dois primeiros pontos sao nfps deslocados para a posicao da copia j
                    p[0].y = itens[it_atual].nfps[i].polig[alfa].ponto[k].y + itens[i].pfinal[j].y;
                    p[1].x = itens[it_atual].nfps[i].polig[alfa].ponto[(k+1)%itens[it_atual].nfps[i].polig[alfa].n].x + itens[i].pfinal[j].x;
                    p[1].y = itens[it_atual].nfps[i].polig[alfa].ponto[(k+1)%itens[it_atual].nfps[i].polig[alfa].n].y + itens[i].pfinal[j].y;
                    for(g = j; g<itens[i].cop_alocad; g++){ //checa contra todas as >outras< copias ja alocadas desse mesmo item
                        for(beta = 0; beta<itens[it_atual].nfps[i].partes; beta++){ //passa por todas as partes de cada nfp
                            for(h = 0; h<itens[it_atual].nfps[i].polig[beta].n; h++){ 
                                p[2].x = itens[it_atual].nfps[i].polig[beta].ponto[h].x + itens[i].pfinal[g].x;
                                p[2].y = itens[it_atual].nfps[i].polig[beta].ponto[h].y + itens[i].pfinal[g].y;
                                p[3].x = itens[it_atual].nfps[i].polig[beta].ponto[(h+1)%itens[it_atual].nfps[i].polig[beta].n].x + itens[i].pfinal[g].x;
                                p[3].y = itens[it_atual].nfps[i].polig[beta].ponto[(h+1)%itens[it_atual].nfps[i].polig[beta].n].y + itens[i].pfinal[g].y;
                                n_int = Intersec(p, atual); //checa as interseccoes e devolve quantas sao
                                for(n = 0; n<n_int; n++){ //passa por todas as intersec pra ver se sao validas
                                    if((atual[n].x <candidato.x)||(fabs(atual[n].x-candidato.x)<= 1.0e-5 && atual[n].y<candidato.y)){
                                        if(Valido(atual[n], it_atual, itens, numitens, altura) == 1){
                                            candidato = atual[n];
                                        }
                                    }
                                }
                            }
                        }
                    }

                    for(f = i+1; f<numitens; f++){ //os outros dois pontos sao dos nfps dos >itens seguintes<
                        for(g = 0; g<itens[f].cop_alocad; g++){ //checa contra >todas< as copias ja alocadas do item
                            for(beta = 0; beta < itens[it_atual].nfps[f].partes; beta++){
                                for(h = 0; h<itens[it_atual].nfps[f].polig[beta].n; h++){ 
                                    p[2].x = itens[it_atual].nfps[f].polig[beta].ponto[h].x + itens[f].pfinal[g].x;
                                    p[2].y = itens[it_atual].nfps[f].polig[beta].ponto[h].y + itens[f].pfinal[g].y;
                                    p[3].x = itens[it_atual].nfps[f].polig[beta].ponto[(h+1)%itens[it_atual].nfps[f].polig[beta].n].x + itens[f].pfinal[g].x;
                                    p[3].y = itens[it_atual].nfps[f].polig[beta].ponto[(h+1)%itens[it_atual].nfps[f].polig[beta].n].y + itens[f].pfinal[g].y;
                                    n_int = Intersec(p, atual); //checa as interseccoes e devolve quantas sao
                                    for(n = 0; n<n_int; n++){ //passa por todas as intersec pra ver se sao validas
                                        if((atual[n].x <candidato.x)||(fabs(atual[n].x-candidato.x)<= 1.0e-5 && atual[n].y<candidato.y)){
                                            if(Valido(atual[n], it_atual, itens, numitens, altura) == 1){
                                                candidato = atual[n];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    free(atual);
    free(p);

    return candidato;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que aloca todos os itens de um individuo por meio da heuristica Bottom-Left, dado a ordenacao das keys*/
double BL(item *itens, int numitens, int numtotal, double altura, ind *individuo, double mtgd){
    int i;
    double aux, fitness = 0;

    for(i = 0; i<numitens; i++){ //toda vez que for montar um individuo, zera as copias alocadas de cada item
        itens[i].cop_alocad = 0;
    }

    for(i = 0; i<numtotal; i++){
        itens[individuo->indice[i].item].pfinal[itens[individuo->indice[i].item].cop_alocad] = AlocaUm(individuo->indice[i].item, itens, numitens, mtgd, altura);

        aux = itens[individuo->indice[i].item].pfinal[itens[individuo->indice[i].item].cop_alocad].x + itens[individuo->indice[i].item].direita;

        if(aux > fitness){ // guarda sempre o maior valor no eixo X ocupado por um item como o fitness
            fitness = aux;
        }
        itens[individuo->indice[i].item].cop_alocad++;
    }

    return fitness;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para criar keys dos itens no inicio do programa, algumas com as funcoes de calculo de propriedades dos itens e outros de forma aleatoria*/
void GeraInicio(item *itens, int numtotal, int numitens, pop populacao){
    int h, i, j, k;

    for(h = 0; h<populacao.total_ind; h++){
        k = 0;
        for(i = 0; i<numitens; i++){
            for(j=0; j<itens[i].copias; j++){
                populacao.individuos[h].indice[k].item = i; //cada espaco do indice recebe o numero do item associado a ele (tem o mesmo numero de copias de um item com seu valor no vetor)
                k++;
            }
        }
    }


    ListarArea(itens, numtotal, numitens, populacao.individuos[0]);
    
    ListarRetangulos(itens, numtotal, numitens, populacao.individuos[1]);

    ListarX(itens, numtotal, numitens, populacao.individuos[2]);

    ListarPropAreas(itens, numtotal, numitens, populacao.individuos[3]);

    for(h = 4; h<populacao.total_ind; h++){
        // gera as keys aleatoriamente
        for(i=0; i<numtotal; i++){
            populacao.individuos[h].indice[i].key = (double)rand()/(double)RAND_MAX;
            populacao.individuos[h].key_ordem_original[i] = populacao.individuos[h].indice[i].key; //mesma key no vetor que guarda elas na ordem os itens
        }
        
    }
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que apenas gera keys de forma aleatoria, utilizada para os caras de mutacao*/
void GeraKeysMut(item *itens, int numtotal, int numitens, pop populacao, int inicio, int fim){
    int i, j, h, k;

    for(h = inicio; h<=fim; h++){
        k = 0;
        for(i = 0; i<numitens; i++){
            for(j=0; j<itens[i].copias; j++){
                populacao.individuos[h].indice[k].item = i; //cada espaco do indice recebe o numero do item associado a ele (tem o mesmo numero de copias de um item com seu valor no vetor)
                k++;
            }
        }
        for(i = 0; i<numtotal; i++){
            populacao.individuos[h].indice[i].key = (double)rand()/(double)RAND_MAX;
            populacao.individuos[h].key_ordem_original[i] = populacao.individuos[h].indice[i].key; //mesma key no vetor que guarda elas na ordem os itens
        }
    }
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para ordenar um indicide, o cromossomo de um individuo.*/
void OrdenaIndice(int numtotal, cromo *indice){
    int i, j;
    cromo auxlocal;

    for(i = 0; i<(numtotal-1); i++){
        for(j = i+1; j<numtotal; j++){
            if((indice[i].key - indice[j].key)>1e-3){ // verifica se a cada duas keys a 1 eh maior que a 2
                auxlocal = indice[j]; // caso sim, altera
                indice[j] = indice[i];
                indice[i] = auxlocal;
            }
        }
    }

}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que chama a bottom-left para todos os individuos da populacao, utilizando o comprimento final (horizontal) resultante como o fitness do individuo*/
void GeraFitness(pop populacao, item* itens, int numitens, int numtotal, double altura, double mtgd){
    int i;

    for(i= 0; i<populacao.total_ind; i++){
        populacao.individuos[i].fitness = BL(itens, numitens, numtotal, altura, &(populacao.individuos[i]), mtgd); //gera cada fitness a partir da bl
    }
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que que chama a bottom-left para cada individuos nao elite da populacao, utilizando o comprimento final (horizontal) resultante como o fitness do individuo*/
void GeraFitnessCruzMut(pop populacao, item* itens, int numitens, int numtotal, double altura, double mtgd){
    int i;

    for(i= populacao.qtd_elite; i<populacao.total_ind; i++){
        populacao.individuos[i].fitness = BL(itens, numitens, numtotal, altura, &(populacao.individuos[i]), mtgd); //gera cada fitness a partir da bl
    }
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que dada a populacao inteira, ordena a elite a partir do valor do fitness*/
void OrdenaElite(pop populacao){
    int i, j;
    ind aux;
    
    for(i = 0; i < populacao.qtd_elite; i++){
        for(j = i; j < populacao.total_ind; j++){
            if(populacao.individuos[j].fitness<populacao.individuos[i].fitness){
                aux = populacao.individuos[j];
                populacao.individuos[j] = populacao.individuos[i];
                populacao.individuos[i] = aux;
            }
        }
    }
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para gerar os individuos por cruzamento entre dois outros, ou seja, de maneira aleatoria escolher para cada item qual key vai ser utilizada no individuo gerado, a partir do indice/cromossomo de key dos dois pais*/
void GeraCruzamento(item *itens, int numtotal, int numitens, pop populacao){
    int i, elite, plebe, j, h, k;
    double p;

    for(h = 0; h<populacao.qtd_cruz; h++){
        k = 0;
        for(i = 0; i<numitens; i++){
            for(j=0; j<itens[i].copias; j++){
                populacao.lixo[h].indice[k].item = i; //cada espaco do indice recebe o numero do item associado a ele (tem o mesmo numero de copias de um item com seu valor no vetor)
                k++;
            }
        }
    }


    for(i = 0; i<populacao.qtd_cruz; i++){
        elite = rand()%(populacao.qtd_elite);

        plebe = populacao.qtd_elite + rand()%(populacao.total_ind - populacao.qtd_elite -1);

        for(j = 0; j<numtotal; j++){
            p = (double)rand()/(double)RAND_MAX;
            
            if(p<=populacao.chances_cruz){// se o vies escolhido for 0.7 e p for 0.6 por exemplo, sera escolhida a key proveniente da elite
                populacao.lixo[i].indice[j].key = populacao.individuos[elite].key_ordem_original[j];
                populacao.lixo[i].key_ordem_original[j] = populacao.lixo[i].indice[j].key;

            }else{
                populacao.lixo[i].indice[j].key = populacao.individuos[plebe].key_ordem_original[j];
                populacao.lixo[i].key_ordem_original[j] = populacao.lixo[i].indice[j].key;
            }
        }
    }
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que apaga 80% da populacao do vetor de individuos, deixando apenas a elite, e copia o vetor dos gerados por cruzamento (atualmente aguardando no vetor lixo)*/
void SubstituiIndCruz(pop populacao){
    int i, j;
    ind aux;

    i = populacao.qtd_elite;
    for(j = 0; j<populacao.qtd_cruz; j++){
        aux = populacao.individuos[i];
        populacao.individuos[i] = populacao.lixo[j];
        populacao.lixo[j] = aux;
        i++;
    }
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que encontra qual o melhor individuo da populacao*/
int ProcuraMelhor(pop populacao, double mtgd){
    int i;
    int atual = 0;

    for(i = 0; i < populacao.total_ind; i++){
        if(populacao.individuos[i].fitness < mtgd){
            mtgd = populacao.individuos[i].fitness;
            atual = i;
        }
    }

    return atual;
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao que imprime as posicoes finais da alocacao em forma de leiaute com linguagem TikZ, para LateX*/
void Imprimir(item *itens, int numitens, int numtotal, double altura, clock_t t, char *instancia, char *endereco, double chances_cruz){
    int i, j, k, alfa, aux = 0;
    double comp_total = 0;
    double alt_total = 0;
    int colors[23];
    double escala; // pra facilitar a impressao em LaTeX
    char endereco1[39];

    for(i = 0; i<23 ; i++){
        colors[i] = 65+i;
    }

    for(i = 0; i<numitens; i++){
        for(j = 0; j<itens[i].copias; j++){
            if(comp_total < (itens[i].direita + itens[i].pfinal[j].x)){
                comp_total = itens[i].direita + itens[i].pfinal[j].x;
            }
            if(alt_total < itens[i].alto + itens[i].pfinal[j].y){
                alt_total = itens[i].alto + itens[i].pfinal[j].y;
            }
        }
    }

    if(alt_total>comp_total){
        escala = 55/alt_total;
    }else{
        escala = 60/comp_total;
    }

    FILE *fout, *ftable;
    sprintf(endereco, "/home/nina_lwt/Desktop/solucoes-BRKGA/desenho-%s-%.2lf.txt", instancia, chances_cruz);
    fout = fopen(endereco, "w");
    if(fout == NULL){
        printf("deu erro na hora de encontrar o arquivo de impressao");
        return;
    }else{
        fprintf(fout, "%%%%%%%%%%%%%%%s - BRKGA [bias: %.2lf]\n", instancia, chances_cruz);
        fprintf(fout, "\n\\begin{tikzpicture}");
        for(i = 0; i<numitens; i++){
            for(j = 0; j<itens[i].copias; j++){
                for(alfa = 0; alfa < itens[i].partes; alfa++){
                    fprintf(fout, "\n  %% item %d copia %d \n\\filldraw [fill= \\cor%c] ", i, j, (char)(colors[(aux)%(23)]));
                    for(k = 0; k<itens[i].polig[alfa].n; k++){
                        fprintf(fout, " (%.3lf,%.3lf) --", ((itens[i].polig[alfa].ponto[k].x + itens[i].pfinal[j].x)*escala), ((itens[i].polig[alfa].ponto[k].y + itens[i].pfinal[j].y)*escala));
                    }
                    fprintf(fout, " cycle;\n");
                }
                aux++; // troca a cor cada vez que olhamos uma nova copia alocada
            }
        }
        fprintf(fout, "\n   \\draw[blue, very thick] (%.2lf, 0) -- (0,0) -- (0,%.2lf) -- (%.2lf, %.2lf);\n", 1.2*comp_total*escala, altura*escala, 1.2*comp_total*escala, altura*escala);
        fprintf(fout, "\n   \\draw[dotted, very thick] (%.2lf, 0) -- (%.2lf,%.2lf);\n", comp_total*escala, comp_total*escala, altura*escala);
        fprintf(fout, "\n\\end{tikzpicture}");
        fprintf(fout, "\n%%escala = %.3lf", (escala));
        fprintf(fout, "\n%%tempo = %.3lfs\n", (((double)t)/CLOCKS_PER_SEC));
        fclose(fout);
    }

    sprintf(endereco1, "/home/nina_lwt/Desktop/IC/tabela.txt");
    ftable = fopen(endereco1, "a");
    if(ftable == NULL){
        printf("deu erro na tabela final\n");
        return;
    }else{
        fprintf(ftable, "\n %s & %d & BRKGA [bias: %.2lf] & %.2lf & %.3lfs", instancia, numtotal, chances_cruz, comp_total, (((double)t)/CLOCKS_PER_SEC));
        fclose(ftable);
    }

}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao para limpar os mallocs feitos ao longo do programa*/
void Limpa(item *itens, int numitens, pop populacao){
    int i, j, k;
    for(i = 0; i<numitens; i++){
        for(j = 0; j<numitens; j++){
            for(k = 0; k<itens[i].nfps[j].partes; k++){
                free(itens[i].nfps[j].polig[k].ponto);
            }
            free(itens[i].nfps[j].polig);
        }

        for(j = 0; j<itens[i].partes; j++){
            free(itens[i].polig[j].ponto);
        }
        free(itens[i].polig);
        free(itens[i].nfps);
        free(itens[i].pfinal);
    }
    free(itens);

    for(i = 0; i<populacao.total_ind; i++){
        free(populacao.individuos[i].indice);
        free(populacao.individuos[i].key_ordem_original);
    }
    for(i = 0; i<populacao.qtd_cruz; i++){
        free(populacao.lixo[i].indice);
        free(populacao.lixo[i].key_ordem_original);
    }
    free(populacao.individuos);
    free(populacao.lixo);
}
//=============================================================================================================================================
//=============================================================================================================================================
/* funcao principal, responsavel pela parte estrategia do BRKGA*/
int main(int argc, char **argv) {
    srand(time(NULL));
    int numitens; //numero de ITENS (ITEM = poligono que queremos alocar)
    int i, numtotal, geracao_atual, melhor_ind;
    double altura; // altura do recipiente
    double mtgd;
    clock_t t;
    char endereco[75];

    printf("\nagrv1: %s\n", argv[1]);
    sprintf(endereco, "/home/nina_lwt/Desktop/Instancias_euler/%s", argv[1]);
    item *itens;
    itens = LerDados(&numitens, &altura, endereco);
    for(i = 0; i<numitens; i++){
        itens[i].esquerda = Esquerda(itens[i]);
        itens[i].alto = Alto(itens[i]);
        itens[i].baixo = Baixo(itens[i]);
        itens[i].direita = Direita(itens[i]);
        itens[i].cop_alocad = 0;
        itens[i].pfinal = (vert*)malloc((itens[i].copias)*sizeof(vert));
        if(itens[i].pfinal == NULL){
            printf("erro do malloc do vetor de pontos finais do item %d\n", i);
            return 1;
        }
    }

    mtgd = MuitoGrande(itens, numitens); // maior tamanho possivel pro recipiente

    pop populacao;
    populacao.total_ind = atoi(argv[2]); //transforma string em int
    populacao.total_ger = atoi(argv[3]);
    populacao.qtd_elite = populacao.total_ind * strtod(argv[4], NULL); //transforma string em double
    populacao.qtd_cruz = populacao.total_ind * strtod(argv[5], NULL);
    populacao.qtd_mut = populacao.total_ind - populacao.qtd_elite - populacao.qtd_cruz;
    if(populacao.qtd_mut <= 0){
        printf("erro ao decidir o tamanho das parcelas da populacao, verifique os numeros\n");
        return 0;
    }
    populacao.chances_cruz = strtod(argv[6], NULL);
    
    populacao.individuos = (ind*)malloc((populacao.total_ind)*sizeof(ind));
    if(populacao.individuos == NULL){
        printf("erro no malloc do vetor de individuos\n");
        return 1;
    }

    populacao.lixo = (ind*)malloc((populacao.qtd_cruz)*sizeof(ind));
    if(populacao.lixo == NULL){
        printf("erro no malloc do vetor que guarda os individuos futuramente descartados\n");
        return 1;
    }

    t = clock();

    numtotal = NumTotal(itens, numitens);
    
    for(i = 0; i<populacao.total_ind; i++){ // alocacao do indice e keys ordenadas de todos os individuos
        populacao.individuos[i].indice = (cromo*) malloc((numtotal)*sizeof(cromo));
        if(populacao.individuos[i].indice == NULL){
            printf("erro do malloc das keys do individuo %d\n", i);
            return 1;
        }
        populacao.individuos[i].key_ordem_original = (double*)malloc((numtotal)*sizeof(double));
        if(populacao.individuos[i].key_ordem_original == NULL){
            printf("erro no malloc das keys ordenadas do individuo %d\n", i);
            return 1;
        }
    }

    for(i = 0; i<populacao.qtd_cruz; i++){ // alocacao do indice e keys ordenadas do vetor que guarda o cruzamento temporariamente
        populacao.lixo[i].indice = (cromo*) malloc((numtotal)*sizeof(cromo));
        if(populacao.lixo[i].indice == NULL){
            printf("erro do malloc das keys do lixo %d\n", i);
            return 1;
        }
        populacao.lixo[i].key_ordem_original = (double*)malloc((numtotal)*sizeof(double));
        if(populacao.lixo[i].key_ordem_original == NULL){
            printf("erro no malloc das keys ordenadas do lixo %d\n", i);
            return 1;
        }
    }
    GeraInicio(itens, numtotal, numitens, populacao); //inicia a populacao - geracao 1

    for(i = 0; i<populacao.total_ind; i++){ //ordena o indice/cromossomo de cada individuo da primeira geracao
        OrdenaIndice(numtotal, populacao.individuos[i].indice);
    }

    GeraFitness(populacao, itens, numitens, numtotal, altura, mtgd); //chama a BL para montar a solucao da instancia para cada individuo a partir da ordenacao do cromossomo, retornando o valor fitness

    geracao_atual = 2;
    while(geracao_atual <= populacao.total_ger){ //para todas as geracoes calculadas (nossa condicao de parada)
        OrdenaElite(populacao); //ordena a elite da populacao baseado no fitness de cada individuo

        GeraCruzamento(itens, numtotal, numitens, populacao); //gera o cruzamento enviesado a partir de dois pais

        SubstituiIndCruz(populacao); //substitui os individuos criados por cruzamento apenas apos terminar o processo de cruzamento em si

        GeraKeysMut(itens, numtotal, numitens, populacao, populacao.total_ind - populacao.qtd_mut, populacao.total_ind-1); //gera keys novas aleatorias para novos individuos, a chamada mutacao

        for(i = populacao.qtd_elite; i<populacao.total_ind; i++){ //ordena o indice/cromossomo dos individuos que acabaram de ser criados por mutacao e por cruzamento
            OrdenaIndice(numtotal, populacao.individuos[i].indice);
        }

        GeraFitnessCruzMut(populacao, itens, numitens, numtotal, altura, mtgd); //chama a BL para calcular a solucao final dos novos individuos e toma o cromprimento final como fitness

        geracao_atual++;
    }
    

    melhor_ind = ProcuraMelhor(populacao, mtgd); //assim que termina, ve qual o melhor individuo

    populacao.individuos[melhor_ind].fitness = BL(itens, numitens, numtotal, altura, &(populacao.individuos[melhor_ind]), mtgd); //para entao chamar a BL novamente, para que os valores de alocacao salvos no final do codigo sejam dele e sejam portanto impressos a seguir

    t = clock() - t;

    Imprimir(itens, numitens, numtotal, altura, t, argv[1], endereco, populacao.chances_cruz);

    Limpa(itens, numitens, populacao);

    return 0;
}