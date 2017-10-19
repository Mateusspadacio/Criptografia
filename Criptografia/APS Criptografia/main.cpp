#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Este programa criptografa mensagens e descriptografa mensagens, é uma criptografia simetrica que utiliza a mesma chave para as duas operações, Criptografar/Descriptografar*/

//Chave para criptografia-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char CHAVE[128]; 					//variavel para recebimento da chave digitada pelo usuario
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************************************************************************************************/
//vetor que vai ler a mensagem digitada pelo usuario--------------------------------------------------------------------------------------------------------------------------------------------------------
char TEXTO[128];							//variavel global
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************************************************************************************************/
//variavel que recebe o texto em numeros---------------------------------------------------------------------------------------------------------------------------------------------------------------------
int TEXTO_CRIPT[128];						//variavel global
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------						
/*************************************************************************************************************************************************************************************************************/
//Criptografando mensagem e gerando arquivo criptografado txt--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Criptografar(){
	int CHAVE_2;
	char pause;
	printf("Digite a chave: ");
	gets(CHAVE);												//recebe a chave digitada pelo usuario
	fflush(stdin);
	printf("\nDigite uma mensagem de no maximo 128 caracteres: \n");
	gets(TEXTO);												//recebe o texto digitado pelo usuario
	if(strlen(TEXTO) > 128){                                      
		printf("\n\nMensagem excede numero de caracteres ! \n\n");   //tratamento do erro, o maximo de caracteres que pode ser digitado e até 128
		system("pause");
		exit (0);
	}
	int TAMANHO_CHAVE=strlen(CHAVE);		//transformando os caracteres da chave em numeros
	printf("\n\nProcessando...\n\n");
	for(int i=0; i < strlen(TEXTO); i++){  //este for ira correr todo o texto digitado até a condição i, depois ele atribuira o texto que é uma variavel int transformando todos os caracteres em numeros
		TEXTO_CRIPT[i]=TEXTO[i];		  //int recebendo char
	}
																						
	for(int aux=0; aux < strlen(TEXTO); ){					//este "for" impede que a minha chave acabe e que ele retorne sempre para o começo da chave até que a condição sejá satisfeita
	for(int i=0; i < TAMANHO_CHAVE; i++){						//este "for" percorre a chave  
		CHAVE_2 = CHAVE[i];								//ele atribui a chave para uma variavel auxiliar 
		TEXTO_CRIPT[aux] = TEXTO_CRIPT[aux] * CHAVE_2;  	//aqui ele está multiplicando o indice que no exemplo é posição 0 valor 109 com a posição 0 da chave que no caso é "a" de valor 97
		aux++;												//este "aux++" mudara a posição do "TEXTO_CRIPT" conforme o "for" for sendo executado, EX: ele começa com 0, ai o aux++ adiciona 1 ai ele não e mais 0 e sim 1, ele vai ler a posição 1 na proxima execução, assim sucessivamente com 2, 3, 4 com todas as posições, multiplicando cada uma delas
	}													
}
	
	FILE *arquivo;
	arquivo = fopen("c:\\cript\\arquivos_gerados\\criptografado.txt","wt"); //ele ira abrir este destino, cria um arquivo txt e irá escrever o conteudo gerado das linhas de codigo abaixo
    for(int i=0; i < strlen(TEXTO); i++){				//o "for" fara esse retiramento um de cada vez de todos os caracteres do texto até a condiçaõ cessar,ou sejá, até o fim do texto
    fprintf(arquivo,"%d ",TEXTO_CRIPT[i]); 				//"arquivo" vai ser o ponteiro onde quero gravar o conteudo, no caso o destino acima, o "%d" é o que vai ser gravado no caso numeros inteiros, e o "TEXTO_CRIPT[i]" é a variavel que será tirada essas informações, o "fprintf" fará essa transição
    	}
    printf("Mensagem criptografada com sucesso ! \n");
	fclose(arquivo);									//finalizando o arquivo, "tudo que se abre tem que ser fechado"
    printf("\n\nPressione enter para abrir a pasta do arquivo gerado!\n"); //aqui simulei um "system("pause")" para melhor controle do usuario
	scanf("%c",&pause);
    setbuf(stdin,NULL);									//esté codigo ele limpa o cache do teclado, evitando possíveis bugs
    system("explorer c:\\cript\\arquivos_gerados\\");	//aqui ele abrirá a pasta onde o arquivo criptografado.txt foi salvo
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************
************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
//Descriptografando mensagem e gerando arquivo txt--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Descriptografar(){
	FILE *arquivo;
	char pause;
	int TAMANHO_CHAVE;
	int result;
    int aux_chave;		//variavel auxiliar
    int aux_texto;		//variavel auxiliar
    printf("+---Instrucoes para descriptografar o arquivo---+ \n\n");				//Um pequeno guia de instruções para o usuario utilizar o software
    printf("1- Copiar arquivo criptografado.txt para a pasta que sera aberta a seguir \n\n");
    printf("2- Depois de colado o arquivo,feche a pasta e continue com a aplicacao \n\n");
    printf("3- Digite a chave a seguir para descriptografar o arquivo \n\n");
    printf("\n Digite a chave: ");
    gets(CHAVE);
    fflush(stdin);
    TAMANHO_CHAVE=strlen(CHAVE);
    printf("Pressione enter para abrir a pasta \n\n");								//simula um "system("pause")", como se fosse aguardando o retorno do usuario para continuar o processo
    scanf("%c", &pause);
    system("explorer c:\\cript\\arquivos_recebidos\\");
    printf("Pressione enter para descriptografar o arquivo \n\n");
    scanf("%c", &pause);
    printf("Processando... \n\n");
	arquivo = fopen("c:\\cript\\arquivos_recebidos\\criptografado.txt","r");		//lendo o arquivo criptografado
	if(arquivo==NULL){
		printf("Nao foi possivel descriptografar o arquivo \n\n");					//tratamento de erro caso não hajá arquivo nenhum na pasta para ser descriptografado
		system("pause");
		exit (0);																	//finalizando o programa caso o erro ocorra
	}
	aux_chave=0;
    aux_texto=0;
    while(!feof(arquivo)){					//enquanto o arquivo não estiver acabado ou seja,quando ele ainda tiver caracteres para processar ele fara esta condição,quando não houver mais caracteres ele saira deste loop
        fscanf(arquivo,"%d",&result);		//ele está lendo o arquivo e jogando os dados para a variavel "result"
        result /= CHAVE[aux_chave];			//divide os valores do arquivo criptografado com os valores da "CHAVE" em relação a posição de "aux_chave"
        TEXTO[aux_texto] = (char)result;		//"TEXTO" em relação com a posição de "aux_texto" recebe o valor já processado em tipo caracter e não mais em tipo inteiro, a uma mudança de tipo para que ela volte a ser um texto
        aux_texto++;
        if(aux_chave==TAMANHO_CHAVE-1){			//tratamento do erro para que a chave não acabe EX:minha "TAMANHO_CHAVE" tem 8 bits que vai de 0 a 7 então se minha "aux_chave" for igual a 8-1=7 minha "aux_chave" é zerada
            aux_chave=0;
        }else{								//se não ela avança mais uma posição
            aux_chave++;
        }
    }
    fclose(arquivo);
    system("cls");
    printf("A mensagem e:  %s\n\n",TEXTO);		//exibe a mensagem totalmente descriptografada
    printf("Pressione enter para salvar esta mensagem \n\n");
    scanf("%c", &pause);
	FILE *arquivo2;
    arquivo2 = fopen("c:\\cript\\mensagens\\mensagem.txt","wt");		//salva a mensagem em um arquivo txt		
    fprintf(arquivo2,"%s ",TEXTO);				
    printf("Processando... \n\n");
    printf("Salvo com sucesso ! \n\n");
    fclose(arquivo2);
    printf("Pressione enter para abrir a pasta onde a mensagen foi salva \n\n");  
    scanf("%c", &pause);
    system("explorer c:\\cript\\mensagens\\"); 			//abre a pasta onde o arquivo foi salvo
    system("cls");
    printf("Pressione enter para voltar ao Menu inicial ! \n\n");
    scanf("%c", &pause);
	
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************************************************************************************/
// A interface do programa, onde o usuario interage e escolhe as opções que deseja---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Menu(){
    int opcao;
    while(1){												//enquanto for verdadeiro, o 1 na linguagem C é verdadeiro
        system("cls");
        printf("\n\n+---Menu criptografia de mensagem---+\n");
        printf("\n\n 1 - Criptografar mensagem \n");
        printf("\n\n 2 - Descriptografar mensagem \n");
        printf("\n\n 3 - Sair \n");
        printf("\n\n Informe a opcao desejada: ");
        scanf("%d",&opcao);									//conforme mostrado acima, o scanf vai ler o numero da opção desejada e o switch aplicara a opção
        setbuf(stdin,NULL);
        switch(opcao){
        case 1:												//se a pessoa digitar 1 o case vai ler o numero 1 e vai aplicar os codigos dentro do seu case, e assim são com os outros 
            system("cls");
            Criptografar();									//função
            break;
        case 2:
            system("cls");									//este codigo limpa a tela, evitando assim acumulo de informações no executavel, para que o programa fique mais limpo
            Descriptografar();								//função
            break;
        case 3:
            printf("\n\nFinalizando...\n\n");
            exit(0);										//este codigo fecha o programa, finaliza
            break;
        default:
            printf("\n\nOpcao invalida! Tente novamente...\n\n");	//caso o usuario digite um numero diferente de 1, 2 ou 3, ele apresentara está mensagem
            system("pause");
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*****************************************************************************************************************************************************************************************************************************************
******************************************************************************************************************************************************************************************************************************************/
//Main o espaço principal-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(){

    Menu();													//isto é uma função, ao executar o programa ela é chamada e executada, utilizar funções evita programar diretamente no main, alem de ser mais organizado

    return 0;
}
//Fim do programa--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
