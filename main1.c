#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 50

int contar_linhas_arquivo(const char *nome_arquivo) {
    FILE *arquivo;
    int contador_linhas = 1;
    int caractere;

    //Abrir o arquivo no modo de leitura ("r")
    arquivo = fopen(nome_arquivo, "r");

    //Verificar se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        // Imprime uma mensagem de erro
        perror("Erro ao abrir o arquivo"); 
        // Retorna -1 para indicar falha
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
int main() {
	FILE *arquivo; 
	
		//criando uma Struct para aluno
		typedef	struct  {
		char nome[MAX_STRING];
	    char ra[10];   //precisamos de 2 char a mais para evitar erros     
	    char turma[MAX_STRING];
	    float nota1;
	    float nota2;
	    float media;
					} Aluno ;
	
	
	
    while (1==1) 
	{
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("[1] portugues.txt\n");
        printf("[2] matematica.txt\n");
        printf("[3] historia.txt\n");
        printf("[4] ciencias.txt\n");
        printf("[5] Sair\n");
        printf("Selecione uma opcao: ");
        
        
		//português,matematica,historia,ciencias
		
		
		
		int op=0; //criando a variavel opção para o switch
        scanf("%d",&op);// pedindo a opção para o usuario

        switch (op) {
        	case 1:
                printf("portugues\n");
				
				
					
                break;
        	
            case 2:
              ;
			    Aluno aluno_mat[MAX_STRING];//vetor de structs para armazenar varios alunos
			    int i=0;// contador para percorrer vetor de structs
			    int linhas = contar_linhas_arquivo("matematica.txt");//saber quantas linhas, se dividir por 4 e for diferente de zero tem algo errado, 4 linhas = 1 aluno
                //printf("%d",linhas);
                
			
                
                arquivo = fopen("matematica.txt", "r");// arquivo agora aponta pra o txt que queremos
                if (arquivo == NULL) {
                    perror("Erro ao abrir o arquivo matematica.txt"); 
                
                    break; // Sai do 'case 2' se o arquivo não puder ser aberto
					}
                
                
		while (linhas !=0){
		
		fgets(aluno_mat[i].nome, MAX_STRING, arquivo);
		aluno_mat[i].nome[strcspn(aluno_mat[i].nome, "\n")] = '\0';
		         
		fgets(aluno_mat[i].ra, 10, arquivo);
		aluno_mat[i].ra[strcspn(aluno_mat[i].ra, "\n")] = '\0';
		
		         
		fgets(aluno_mat[i].turma, MAX_STRING, arquivo);
		aluno_mat[i].turma[strcspn(aluno_mat[i].turma, "\n")] = '\0';
		         
		fscanf(arquivo, "%f %f ", &aluno_mat[i].nota1, &aluno_mat[i].nota2);
		
		aluno_mat[i].media = calcular_media(aluno_mat[i].nota1, aluno_mat[i].nota2);
		         
		printf("DISCIPLINA: Matematica");
		printf("--------------------------------------------------\n");
		printf("Nome: %s\n", aluno_mat[i].nome);
		printf("RA: %s\n", aluno_mat[i].ra);
		printf("Turma: %s\n", aluno_mat[i].turma);
		printf("Nota 1: %.2f\n", aluno_mat[i].nota1);
		printf("Nota 2: %.2f\n", aluno_mat[i].nota2);
		printf("Média: %.2f\n", aluno_mat[i].media);
		printf("--------------------------------------------------\n");
		linhas = linhas-4;// se o arquivo tem 12 linhas, 4 delas formam uma struct, e entao começa a proxima iteraçao
		i= i+1;// aumenta o contador para percorrer o vetor de structs
		}
		
		fclose(arquivo);
                
                
                
				break;
                
            case 3:
                printf("programac...\n");
                break;
            case 4:
                printf("programac...\n");
                break;
            case 5:
                printf("Encerrando...\n");
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                continue;
        }

     
    }
    return 0;
}
