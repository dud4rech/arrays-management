/******************************************************************************

LPG0002 Linguagem de Programacao - Luciana Rita Guedes
Trabalho 01 - Gerenciamento de Conjuntos

Ana Beatriz Martins da Silva
Eduarda Stipp Rech

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define M 8
#define N 10

/**************Prototipos**************/

int menu(int n);
int verifica_conjunto_criado(int contador_conjuntos);
int verifica_tamanho_matriz(int contador_conjuntos, int matriz[contador_conjuntos][N]);
int verifica_existencia_conjunto(int conjunto_escolhido, int contador_conjuntos);
int inserir_vazio(int conjunto, int matriz[conjunto][N]);
void inserir_dados(int conjunto, int matriz[][N]);
void remover_conjunto(int conjunto, int matriz[conjunto][N]);
int conta_valores_conjunto(int matriz[M][N], int conjunto);
int conta_repetidos(int matriz[M][N], int primeiroconjunto, int segundoconjunto, int quantvaloresprimeiro, int quantvaloressegundo);
int verifica_uniao (int primeiroconjunto, int segundoconjunto, int matriz[M][N], int linha_uniao);
void uniao_conjuntos(int matriz[M][N], int primeiroconjunto, int segundoconjunto, int linha_uniao);
int verifica_interseccao(int matriz[M][N], int primeiroconjunto, int segundoconjunto);
void interseccao_conjuntos(int matriz[M][N], int primeiroconjunto, int segundoconjunto, int linha_interseccao);
void mostrar_um_conjunto(int matriz[M][N], int conjunto);
void mostrar_conjuntos(int matriz[M][N], int contador_conjuntos);
void busca_numero(int contador_conjuntos, int matriz[contador_conjuntos][N]);

/**************Principal**************/

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Portuguese");
	int opcao_menu, matriz[M][N], contador_conjuntos = -1, conjunto_escolhido, numero_buscado, primeiro_conjunto_escolhido, segundo_conjunto_escolhido, contprimeiro, contsegundo, i;
	
	do {	
		opcao_menu = menu(opcao_menu);
		
		switch(opcao_menu)
		{
    	    case 1:
    			contador_conjuntos = verifica_tamanho_matriz(contador_conjuntos, matriz);
    			break;
    			
    		case 2:
    			if(verifica_conjunto_criado(contador_conjuntos) == -1)
    				break;
    	
    			conjunto_escolhido = (verifica_existencia_conjunto(conjunto_escolhido, contador_conjuntos));
    			
    			if(conjunto_escolhido == -1)
    				break;
    			
    			inserir_dados(conjunto_escolhido, matriz);
    			break;
    			
    		case 3:
    			if(verifica_conjunto_criado(contador_conjuntos) == -1)
    				break;
    			
    			conjunto_escolhido = (verifica_existencia_conjunto(conjunto_escolhido, contador_conjuntos));
    			remover_conjunto(conjunto_escolhido, matriz);
    			contador_conjuntos--;
    			break;	
        	
        	case 4:
        		if(contador_conjuntos == -1 || contador_conjuntos == 0) {
    				printf("Voce precisa criar no minimo 2 conjuntos para realizar esta acao.\n");
    				break;
    			}
    			if(contador_conjuntos == M - 1) {
    			    printf("Voce ja atingiu o numero maximo de conjuntos. Remova um conjunto para realizar esta acao.\n");
    			    break;
    			}
    			else {
    			    printf("Digite dois conjuntos para unir: ");
    			    scanf("%d%d", &primeiro_conjunto_escolhido, &segundo_conjunto_escolhido);
    			    
    			    while(primeiro_conjunto_escolhido == segundo_conjunto_escolhido) {
    			        printf("Escolha conjuntos diferentes.\n");
    			        printf("Digite dois conjuntos para unir: ");
    			        scanf("%d%d", &primeiro_conjunto_escolhido, &segundo_conjunto_escolhido);
    			    }
    			    
    			    while(primeiro_conjunto_escolhido > contador_conjuntos || segundo_conjunto_escolhido > contador_conjuntos) {
    			        printf("Conjunto ainda nao foi criado.\nEscolha dois conjuntos ate %d\n", contador_conjuntos);
    			        printf("Digite dois conjuntos para unir: ");
    			        scanf("%d%d", &primeiro_conjunto_escolhido, &segundo_conjunto_escolhido);
    			    }
    			    
    			    mostrar_um_conjunto(matriz, primeiro_conjunto_escolhido); // imprime primeiro conjunto
                    mostrar_um_conjunto(matriz, segundo_conjunto_escolhido); // imprime segundo conjunto
                    
                    if(verifica_uniao(primeiro_conjunto_escolhido, segundo_conjunto_escolhido, matriz, contador_conjuntos)) { // Se for possivel unir os dois conjuntos
                        contador_conjuntos++; // Conjunto uniao sera na proxima linha disponivel
                        inserir_vazio(contador_conjuntos, matriz); 
                        uniao_conjuntos(matriz, primeiro_conjunto_escolhido, segundo_conjunto_escolhido, contador_conjuntos);
                    } else {
                        printf("\nErro: conjunto resultante maior que 10!\n");
                    }
    			}
    			break;
    			
    		case 5: 
    			if(contador_conjuntos == -1 || contador_conjuntos == 0) {
    				printf("Voce precisa criar no minimo 2 conjuntos para realizar esta acao.\n");
    				break;
    			}
    			if(contador_conjuntos == M - 1) {
    			    printf("Voce ja atingiu o numero maximo de conjuntos. Remova um conjunto para realizar esta acao.\n");
    			    break;
    			} 
    			else {
    			    printf("Digite dois conjuntos para interseccionar: ");
    			    scanf("%d%d", &primeiro_conjunto_escolhido, &segundo_conjunto_escolhido);
    			
    			    while(primeiro_conjunto_escolhido == segundo_conjunto_escolhido) {
    			        printf("Escolha conjuntos diferentes.\n");
    			        printf("Digite dois conjuntos para unir: ");
    			        scanf("%d%d", &primeiro_conjunto_escolhido, &segundo_conjunto_escolhido);
    			    }
    			
    		    	while(primeiro_conjunto_escolhido > contador_conjuntos || segundo_conjunto_escolhido > contador_conjuntos) {
    			        printf("Conjunto ainda nao foi criado.\nEscolha dois conjuntos ate %d\n", contador_conjuntos);
    			        printf("Digite dois conjuntos para unir: ");
    			        scanf("%d%d", &primeiro_conjunto_escolhido, &segundo_conjunto_escolhido);
    		    	}
    		    	
    		    	mostrar_um_conjunto(matriz, primeiro_conjunto_escolhido); // Imprime primeiro conjunto
                    mostrar_um_conjunto(matriz, segundo_conjunto_escolhido); // Imprime segundo conjunto
                    
                    if((verifica_interseccao(matriz, primeiro_conjunto_escolhido, segundo_conjunto_escolhido)) == 1) { // Se der para interseccionar os dois conjuntos
                        contador_conjuntos++;
                        inserir_vazio(contador_conjuntos, matriz);
                        interseccao_conjuntos(matriz, primeiro_conjunto_escolhido, segundo_conjunto_escolhido, contador_conjuntos);
                    } else {
                        printf("Erro: conjuntos nao tem valores iguais para realizar a interseccao!\n");
                    }
    			}
    			break;
    			
    		case 6:
    			if(verifica_conjunto_criado(contador_conjuntos) == -1)
    				break;
    			
    			conjunto_escolhido = (verifica_existencia_conjunto(conjunto_escolhido, contador_conjuntos));
                mostrar_um_conjunto(matriz, conjunto_escolhido);
        		break;
    						
    		case 7:
    			if(verifica_conjunto_criado(contador_conjuntos) == -1) 
    				break;
    			
    			mostrar_conjuntos(matriz, contador_conjuntos + 1);
    			break;
    			
    		case 8:
    			if(verifica_conjunto_criado(contador_conjuntos) == -1)
    				break;
    			
    			busca_numero(contador_conjuntos, matriz);
    			break;
    				
    		case 9:
    			printf("Programa encerrado.\n");
    			break;
    		
    		default:
    			printf("Opcao invalida. Digite novamente.\n\n");
    			break;
    	}
    	
    } while(opcao_menu != 9);
    	
    return 0;
}

/**************Funcoes**************/

// Case 1 - Criar um novo conjunto vazio
int inserir_vazio(int conjunto, int matriz[conjunto][N])
{
	int i;
	for(i = 0; i < 10; i++)
		matriz[conjunto][i] = 0; // Atribui ao conjunto o valor 0
}

// Case 2 - Inserir dados em um conjunto
void inserir_dados(int conjunto, int matriz[][N])
{
    int i, j, numero_digitado, verificador, final_conjunto = -1;
    for(i = 0; i < N ; i++) { // Procura pelo 0 (final) no conjunto
        if(matriz[conjunto][i] == 0) {
            final_conjunto = i;
            break;
        }
    }

    if(final_conjunto == -1) {
        printf("O conjunto %d ja esta com a capacidade maxima atingida.\n", conjunto);
        return;
    }

    printf("Insira os numeros inteiros desejados. Digite 0 para voltar ao menu.\n");

    for(i = final_conjunto; i <= N; i++) {
        scanf("%d", &matriz[conjunto][i]);
        numero_digitado = matriz[conjunto][i];
    
        for(j = 0; j < i; j++) {
        	verificador = matriz[conjunto][j];
        	
            if(verificador == numero_digitado) {
                printf("Valor repetido. Insira um numero diferente.\n");
                i--;
                break;
            }
    	}
		
        final_conjunto = i;
        if(final_conjunto == N -1) {
            printf("O conjunto %d ja esta com a capacidade maxima atingida.\n", conjunto);
            break;
        }
        
        if(numero_digitado == 0)
            break;
    }
}

// Case 3 - Remover um conjunto
void remover_conjunto(int conjunto, int matriz[conjunto][N])
{
	int i, j;
	inserir_vazio(conjunto, matriz);
	
	for(i = conjunto; i < M; i++) 
		for(j = 0; j < N; j++)
			matriz[i][j] = matriz[i + 1][j]; // O conjunto excluido recebe os valores da linha seguinte
	
	printf("Conjunto %d removido!\n", conjunto);
}

// Case 4 - Fazer a uniao entre dois conjuntos
void uniao_conjuntos(int matriz[M][N], int primeiroconjunto, int segundoconjunto, int linha_uniao)
{
	int i, j, k, cont_repetidos = 0, contprimeiro = 0, contsegundo = 0;
    for(i = 0; matriz[primeiroconjunto][i] != 0; i++) {
        matriz[linha_uniao][i] = matriz[primeiroconjunto][i]; // Conjunto uniao recebe valores do primeiro conjunto
        contprimeiro++; // Conta valores do primeiro conjunto
    }
            
    for(i = 0; matriz[segundoconjunto][i] != 0; i++) {
        matriz[linha_uniao][i + contprimeiro] = matriz[segundoconjunto][i]; // Conjunto uniao recebe valores do segundo conjunto a partir do indice disponivel
        contsegundo++; // Conta valores do segundo conjunto
    }
    
    int valores_preenchidos = contprimeiro + contsegundo; // Representa o total de valores 
    for(i = 0; i < valores_preenchidos; i++)
        for(j = i + 1; j < valores_preenchidos;) {
            if(matriz[linha_uniao][j] == matriz[linha_uniao][i]) { // Se o valor for igual ao anterior
                for(k = j; k < valores_preenchidos; k++) {
                    matriz[linha_uniao][k] = matriz[linha_uniao][k + 1]; // Preenche este valor com o proximo
                }
                valores_preenchidos--; // Se tira o valor repetido, o conjunto diminui de tamanho
            } else
                j++;
        }
        printf("Conjunto uniao %d = ", linha_uniao);
        for(i = 0; i < N && matriz[linha_uniao][i] != 0; i++)
		    printf("%d ", matriz[linha_uniao][i]);
		 
}

// Case 5 - Fazer a interseccao entre dois conjuntos
void interseccao_conjuntos(int matriz[M][N], int primeiroconjunto, int segundoconjunto, int linha_interseccao) 
{
    int i, j, contprimeiro = 0, contsegundo = 0, tamanho_interseccao = 0;
    for(i = 0; matriz[primeiroconjunto][i] != 0; i++) {
        for(j = 0; matriz[segundoconjunto][j] != 0; j++) {
            if(matriz[primeiroconjunto][i] == matriz[segundoconjunto][j]) { // Compara os dois conjuntos
                matriz[linha_interseccao][tamanho_interseccao] = matriz[primeiroconjunto][i]; // Guarda os valores iguais
                tamanho_interseccao++;
            }
        }
    }
    
    printf("Conjunto interseccao %d = ", linha_interseccao);
    for(i = 0; i < N && matriz[linha_interseccao][i] != 0; i++)
	    printf("%d ", matriz[linha_interseccao][i]);
		   
}

// Case 6 - Mostrar um conjunto
void mostrar_um_conjunto(int matriz[M][N], int conjunto_escolhido)
{
	int i;
	printf("Conjunto %d = ", conjunto_escolhido);
	if(matriz[conjunto_escolhido][0] == 0) { 
		printf("vazio\n"); // Se o conjunto tiver apenas o valor 0, eh exibido a palavra vazio.
	} else {
		for(i = 0; i < N && matriz[conjunto_escolhido][i] != 0; i++) {
			printf("%d ", matriz[conjunto_escolhido][i]);
		}
		printf("\n");
	}
}

// Case 7 - Mostrar todos os conjuntos
void mostrar_conjuntos(int matriz[M][N], int contador_conjuntos)
{
	int i, j;
	printf("Temos %d conjuntos:\n", contador_conjuntos);
	for(i = 0; i < contador_conjuntos; i++) {
		printf("Conjunto %d = ", i);
		
		for(j = 0; j < N && matriz[i][j] != 0; j++)
			printf("%d ", matriz[i][j]);
		
		for(j = 0; matriz[i][j] == 0; j++) {
			printf("vazio"); // Exibe a palavra "vazio" para os conjuntos que tiverem apenas o valor 0 
			break;
		}
	printf("\n");
	}
}

// Case 8 - Buscar valor
void busca_numero(int contador_conjuntos, int matriz[contador_conjuntos][N])
{
	int i, j, numero_matriz, numero_buscado, verificador = 0;
	printf("Qual numero voce quer buscar?\n");
	scanf("%d", &numero_buscado);
	printf("Conjuntos que contem o numero %d:\n", numero_buscado);
	
	for(i = 0; i <= contador_conjuntos; i++) {
		for(j = 0; j < N; j++) {
			numero_matriz = matriz[i][j];
			if(numero_matriz == numero_buscado) {
				printf("Conjunto %d \n", i);
				verificador = 1;
				break;	
			}
		}
	}
	
	if(verificador == 0)
		printf("O valor escolhido nao foi encontrado em nenhum conjunto.");
}

// Imprime opcoes do menu
int menu(int n)
{
		printf("\nGerenciamento de Conjuntos\n\n");
		printf("Menu\n\n");
		printf("1 - Criar um novo conjunto vazio\n");
		printf("2 - Inserir dados em um conjunto\n"); 
		printf("3 - Remover um conjunto\n");
		printf("4 - Fazer a uniao entre dois conjuntos\n");
		printf("5 - Fazer a interseccao entre dois conjuntos\n");
		printf("6 - Mostrar um conjunto\n"); 
		printf("7 - Mostrar todos os conjuntos\n"); 
		printf("8 - Fazer busca por um valor\n");
		printf("9 - Sair do programa\n\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &n);
		system("cls");

	return n;
}

// Verifica se algum conjunto ja foi criado
int verifica_conjunto_criado(int contador_conjuntos)
{
	while(contador_conjuntos == -1) {
		printf("Voce ainda nao criou nenhum conjunto!\n"); // Mensagem para alertar ao usuario que nao foi criado nenhum conjunto
		return -1;
	}
}

// Verifica se o tamanho da matriz ja foi atingido
int verifica_tamanho_matriz(int contador_conjuntos, int matriz[contador_conjuntos][N])
{
	if(contador_conjuntos == M - 1) {
		printf("Limite da matriz foi alcancado. Voce nao pode mais criar novos conjuntos.\n"); // Nao permite a criacao de mais de 8 conjuntos
		return contador_conjuntos;
	} else {
		contador_conjuntos++;
		printf("Conjunto %d criado!\n\n", contador_conjuntos);
		inserir_vazio(contador_conjuntos, matriz);
		return contador_conjuntos;
	}
}

// Verifica a existencia do conjunto escolhido
int verifica_existencia_conjunto(int conjunto_escolhido, int contador_conjuntos)
{
	conjunto_escolhido = -1;
	while(conjunto_escolhido > contador_conjuntos || conjunto_escolhido < 0) {
		printf("Escolha um conjunto entre 0 e %d:\n", contador_conjuntos);
		scanf("%d", &conjunto_escolhido);
				
		if(conjunto_escolhido > contador_conjuntos || conjunto_escolhido < 0) {
			printf("Erro: conjunto %d nao foi criado!\n", conjunto_escolhido);
			return -1;
		} else
			return conjunto_escolhido;
	}
}

// Conta valores em um conjunto
int conta_valores_conjunto(int matriz[M][N], int conjunto)
{
    int i, cont_valores = 0;
    for(i = 0; i < N; i++) {
        if(matriz[conjunto][i] != 0)
            cont_valores++;
    }

    return cont_valores;
}

// Conta repetidos
int conta_repetidos(int matriz[M][N], int primeiroconjunto, int segundoconjunto, int quantvaloresprimeiro, int quantvaloressegundo)
{
    int i, j, cont_repetidos = 0;
    for(i = 0; i < quantvaloresprimeiro; i++) { 
        for(j = 0; j < quantvaloressegundo; j++) 
            if(matriz[primeiroconjunto][i] == matriz[segundoconjunto][j]) 
                cont_repetidos++; // Se encontrar valores iguais, contador aumenta
    }

    return cont_repetidos;
}

// Verifica se eh possivel realizar uniao dos conjuntos escolhidos
int verifica_uniao (int primeiroconjunto, int segundoconjunto, int matriz[M][N], int linha_uniao)
{
	int contprimeiro = 0, contsegundo = 0, cont_repetidos = 0;
    contprimeiro = conta_valores_conjunto(matriz, primeiroconjunto); 
	contsegundo = conta_valores_conjunto(matriz, segundoconjunto); 
	cont_repetidos = conta_repetidos(matriz, primeiroconjunto, segundoconjunto, contprimeiro, contsegundo);

    if((contprimeiro + contsegundo - cont_repetidos) > 10) 
        return 0;
    else 
        return 1;

}

// Verifica se eh possivel fazer a interseccao dos conjuntos escolhidos
int verifica_interseccao(int matriz[M][N], int primeiroconjunto, int segundoconjunto)
{
    int contprimeiro = 0, contsegundo = 0;
    contprimeiro = conta_valores_conjunto(matriz, primeiroconjunto); 
	contsegundo = conta_valores_conjunto(matriz, segundoconjunto); 
    
    if(!conta_repetidos(matriz, primeiroconjunto, segundoconjunto, contprimeiro, contsegundo)) // Se nao tiver nenhum numero repetido retorna falso
        return 0;
    else
        return 1; // Se tiver numero repetido eh possivel realizar a interseccao e retorna verdadeiro
}
