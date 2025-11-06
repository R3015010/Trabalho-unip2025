#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Tam_max 50

// Criando a Struct Aluno fora da main para ser usada globalmente (boa prática)
typedef struct {
    char nome[Tam_max];
    char ra[10];
    char turma[Tam_max];
    float nota1;
    float nota2;
    float media;
} Aluno;

int contar_linhas_arquivo(const char *nome_arquivo) {
    FILE *arquivo;
    int contador_linhas = 1;// 1 porque ele começa na primeira linha, e vira 2 quando le a primeira quebra de linha
    int caractere;

    //Abrir o arquivo no modo de leitura ("r")
    arquivo = fopen(nome_arquivo, "r");

    //Verificar se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        return -1; 
    }
	
    //Ler o arquivo caractere por caractere até o final (EOF)
    while ((caractere = fgetc(arquivo)) != EOF) {
        // Se o caractere lido for uma quebra de linha, incrementa o contador
        if (caractere == '\n') {
            contador_linhas++;
        }
    }

    // 4. Fechar o arquivo
    fclose(arquivo);
    return contador_linhas;
	}

float calcular_media(float n1, float n2)
{
    return (n1 + n2) / 2.0;
}


int processar_arquivo_disciplina(const char *nome_arquivo, const char *nome_disciplina) {
    FILE *arquivo;
    // Tenta obter o número de linhas.
    int linhas = contar_linhas_arquivo(nome_arquivo);
    
    // Se cada aluno ocupa 4 linhas entao linhas / 4 = quantidade de alunos
    int num_alunos = linhas / 4;
    
    // Verifiçao caso linhas receba valor negativo
    if (linhas <= -1) 
	{
        fprintf(stderr,"Erro linhas negativas");
	}
    if (linhas % 4 != 0) {
        fprintf(stderr, "\nAviso: O arquivo %s esta incompleto ou nao existe \n", nome_arquivo);
        return -1;
    }
    if (num_alunos == 0) {
        printf("\nNenhum aluno encontrado no arquivo %s.\n", nome_arquivo);
        return 0; // nao é um erro, mas nao tem o que ler, roda normal
    }


    // le o arquivo, e verifica se ele existe
    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
    fprintf(stderr, "Erro: arquivo \"%s\" nao encontrado.\n", nome_arquivo); 
    return 1;
    }
    
	//vai criar uma instancia de aluno para cada 4 linhas do txt
    Aluno alunos[num_alunos];
    int i = 0; // Contador de alunos

    printf("\n=== DADOS DA DISCIPLINA: %s ===\n", nome_disciplina);
    
    //loop para ler os dados dos alunos, até o contador ser maior que a quantidade de alunos
    while (i < num_alunos) {

        if (fgets(alunos[i].nome, Tam_max, arquivo) == NULL) break;
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';

        if (fgets(alunos[i].ra, 10, arquivo) == NULL) break;
        alunos[i].ra[strcspn(alunos[i].ra, "\n")] = '\0';
        
        if (fgets(alunos[i].turma, Tam_max, arquivo) == NULL) break;
        alunos[i].turma[strcspn(alunos[i].turma, "\n")] = '\0';

        // O espaço após o segundo %f é necessario se nao da erro
        
        if (fscanf(arquivo, "%f %f ", &alunos[i].nota1, &alunos[i].nota2) != 2) break;
        
		// calculando a media esta aqui
        alunos[i].media = calcular_media(alunos[i].nota1, alunos[i].nota2);
        
        // Exibe os dados do aluno
        printf("--------------------------------------------------\n");
        printf("Nome: %s\n", alunos[i].nome);
        printf("RA: %s\n", alunos[i].ra);
        printf("Turma: %s\n", alunos[i].turma);
        printf("Nota 1: %.2f\n", alunos[i].nota1);
        printf("Nota 2: %.2f\n", alunos[i].nota2);
        printf("Média: %.2f\n", alunos[i].media);
        printf("--------------------------------------------------\n");
        
        i++; // aumenta o contador e vai para o próximo aluno
    }
    
    if (i < num_alunos) {
        printf("Erro na condicao do while");//garante que nao saiu do loop sem ler todos alunos
        return 1;
    }

    fclose(arquivo);
    return 0; // Retorna sucesso
}

void busca_ra(const char *nome_arquivo)
{
FILE *arquivo;
    // Tenta obter o número de linhas.
    int linhas = contar_linhas_arquivo(nome_arquivo);
    
    // Se cada aluno ocupa 4 linhas entao linhas / 4 = quantidade de alunos
    int num_alunos = linhas / 4;
    char ra2[10];//declara o ra que vamos buscar
    scanf("%9s", ra2);
    while (getchar() != '\n');

    arquivo = fopen(nome_arquivo, "r");

	//vai criar uma instancia de aluno para cada 4 linhas do txt
    Aluno alunos[num_alunos];
    int i = 0,encontrou=0; // Contador de alunos, verificador se encontrou


    
    //loop para ler os dados dos alunos, até o contador ser maior que a quantidade de alunos
    while (i < num_alunos) {

        if (fgets(alunos[i].nome, Tam_max, arquivo) == NULL) break;
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';

        if (fgets(alunos[i].ra, 10, arquivo) == NULL) break;
        alunos[i].ra[strcspn(alunos[i].ra, "\n")] = '\0';
        
        if (fgets(alunos[i].turma, Tam_max, arquivo) == NULL) break;
        alunos[i].turma[strcspn(alunos[i].turma, "\n")] = '\0';

        // O espaço após o segundo %f é necessario se nao da erro
        
        if (fscanf(arquivo, "%f %f ", &alunos[i].nota1, &alunos[i].nota2) != 2) break;
        
		// calculando a media esta aqui
        alunos[i].media = calcular_media(alunos[i].nota1, alunos[i].nota2);
        
        if (strcmp(ra2, alunos[i].ra) == 0){
		
        	printf("\nEsse RA pertence ao aluno(a) %s",alunos[i].nome);
        	encontrou = 1;
        	break;
 		 }
      
        
        i++; // aumenta o contador e vai para o próximo aluno
    }
    if (encontrou == 0)
    printf("\nNao foi encontrato nenhum aluno com esse RA");
    

    fclose(arquivo);
}

int main() {

    while (1) {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("[1] Portugues\n");
        printf("[2] Matematica\n");
        printf("[3] Historia\n");
        printf("[4] Ciencias\n");
        printf("[5] Busca por RA\n");
        printf("[6] Sair\n");
        printf("Selecione uma opcao: ");
        
        int op = 0,op2 = 0;
        // Verifica e limpa o buffer
        if (scanf("%d", &op) != 1) {
             printf("Entrada invalida. Por favor, digite um numero.\n");
             while (getchar() != '\n');
             continue;
        }
        
        switch (op) {
            case 1:
                processar_arquivo_disciplina("portugues.txt", "Portugues");
                break;
                
            case 2:

                processar_arquivo_disciplina("matematica.txt", "Matematica");
                break;
                
            case 3:

                processar_arquivo_disciplina("historia.txt", "Historia");
                break;
                
            case 4:

                processar_arquivo_disciplina("ciencias.txt", "Ciencias");
                break;
                
            case 5:
            			printf("Qual a disciplina do aluno?\n");
            	        printf("[1] Portugues\n");
				        printf("[2] Matematica\n");
				        printf("[3] Historia\n");
				        printf("[4] Ciencias\n");
				       if (scanf("%d", &op2) != 1) {
             printf("Entrada invalida. Por favor, digite um numero.\n");
             while (getchar() != '\n');
             continue;
        }
            	switch(op2)
				{
	            	case 1:
	            		busca_ra("portugues.txt");
	            		break;
					case 2:
						busca_ra("matematica.txt");
	            		break;
					case 3:
						busca_ra("historia.txt");
	            		break;
					case 4:
						busca_ra("ciencias.txt");
	            		break;
	            		default:
                printf("Opcao invalida. Escreva um valor de 1 a 4.\n");
                break;
				}
               
			   
			    break;
            
			case 6:
                printf("Encerrando...\n");
                return 0;
                
            default:
                printf("Opcao invalida. Escreva um valor de 1 a 6.\n");
                break;
        }
    }
    
    return 0;
}
