     ////////////////////////
    //  Trabalho Final	  //
   // Programação básica //
  //   Lorenzo Xavier   //
 //     2020101577     //
////////////////////////

//Declara as bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Define o máximo de caracteres que o título pode ter
#define MAX_TITULO 1000
//Define o número máximo de obras que a biblioteca pode ter
#define MAX_OBRAS 1000

//Define Livro como um tipo, com essa estrutura
typedef struct Estrutura{
	char Titulo[MAX_TITULO];
	int ISBN;
	float Valor;
	long unsigned int Quantidade_Estoque;
}Livro;

//Protótipos das funções
FILE* Init_Estoque();
FILE* Init_Saldo();
int Escolha();
void Cadastra_Livro(FILE *file_estoque, Livro* EstoqueLivros, int* numero_obras_diferentes_pointer);
void Consulta_Estoque(Livro* EstoqueLivros, int numero_obras_diferentes);
void vendeLivro(float* saldo_pointer, Livro* EstoqueLivros, int numero_obras_diferentes);
void consultaSaldo(float saldo);
void salvaDados(float saldo, Livro* EstoqueLivros, int numero_obras_diferentes);
int Puxa_Estoque(FILE* file_estoque, Livro* EstoqueLivros);
float Puxa_Saldo(FILE* file_saldo);
void consultaEstoqueTituloString(char* string, Livro* EstoqueLivros, int numero_obras_diferentes);
int consultaEstoqueTitulo(char* string, Livro* EstoqueLivros, int numero_obras_diferentes);
int consultaEstoqueISBN(int ISBN, Livro* EstoqueLivros, int numero_obras_diferentes);
int validadorNumeral(const char* texto);
int validadorISBN(const char* texto);
float validadorValor(const char* texto);

int main()
{	
	//Muda cor do terminal
	system("color 70");

	//Declara, inicializa e testa os ponteiro para o arquivo "saldo.txt"
	FILE* file_saldo = Init_Saldo();
	//Testa se file_saldo é válido
	if(file_saldo==NULL)
	{
		//Retorna -1 e finaliza o programa
		return -1;
	}
	
	//Declara, inicializa e testa os ponteiro para o arquivo "estoque.txt"
	FILE* file_estoque = Init_Estoque();
	//Testa se file_saldo é válido
	if(file_estoque==NULL)
	{
		//Retorna -1 e finaliza o programa
		return -1;
	}
	
	//Atualiza saldo
	float* saldo_pointer;
	float saldo;
	saldo = Puxa_Saldo(file_saldo);
	saldo_pointer = &saldo;
	
	//Inicialização do vetor de ponteiros do tipo Livro
	Livro* EstoqueLivros;
	EstoqueLivros = malloc( MAX_OBRAS*sizeof(Livro*) );
	int numero_obras_diferentes = numero_obras_diferentes=Puxa_Estoque(file_estoque, EstoqueLivros);
	int* numero_obras_diferentes_pointer = &numero_obras_diferentes;

	//Escolha() retorna a opcao selecionada pelo usuario
	int opcao=Escolha();
	
	switch(opcao)
	{
		case 1:
			Cadastra_Livro(file_estoque, EstoqueLivros, numero_obras_diferentes_pointer);
			fclose(file_estoque);
			fclose(file_saldo);
			salvaDados(saldo, EstoqueLivros, numero_obras_diferentes);
			break;
			
		case 2: 
			Consulta_Estoque(EstoqueLivros, numero_obras_diferentes);
			break;
			
		case 3:
			vendeLivro(saldo_pointer, EstoqueLivros, numero_obras_diferentes);
			fclose(file_estoque);
			fclose(file_saldo);
			salvaDados(saldo, EstoqueLivros, numero_obras_diferentes);
			break;
			
		case 4:
			consultaSaldo(saldo);
			break;
			
		case 5: 
			fclose(file_estoque);
			fclose(file_saldo);
			salvaDados(saldo, EstoqueLivros, numero_obras_diferentes);
			printf("\nSucesso em salvar dados!\n");
			break;
			
		default:
			printf("\nOpcao invalida!\n");
			break;
	}
	
	if(opcao==9)
	{
		//Limpa tela
		system("cls");
		printf("\nObrigado pelo acesso a biblioteca!\n");
    	//Libera a memória reservada pelo comando malloc
		free(EstoqueLivros);
		//Fecha os dois arquivos
		fclose(file_estoque);
		fclose(file_saldo);
		system("pause");
		//Retorna 0 e finaliza o programa
		return 0;
	}
	
	//Libera a memória reservada pelo comando malloc
	free(EstoqueLivros);

	//Fecha os dois arquivos
	fclose(file_estoque);
	fclose(file_saldo);
	
	//Chama main();
	main();
}

FILE* Init_Estoque()
{
	//Printf("Funcao \"estoque.txt\".\n");

	//Ponteiro para estoque.txt
	FILE* file_estoque;
	
	// r+ -> abre o arquivo para leitura e escrita, no inicio do arquivo. O arquivo tem que existir.
	if ( (file_estoque=fopen ("estoque.txt","r+"))==NULL )
	{
		printf ("Erro na abertura do arquivo \"estoque.txt\".\n");
		// a+ -> abre o arquivo para leitura e escrita, no final do arquivo. Se o arquivo não existir, função o cria.
		if ( (file_estoque=fopen ("estoque.txt","a+"))==NULL )
		{
			printf ("Erro na criacao do arquivo \"estoque.txt\".\n");
			//Exibe o erro
			perror("Error:");
			//Retorna null
			return NULL;
    	}
    	else
    	{
    		printf("Arquivo \"estoque.txt\" criado com sucesso.\n");
    		
    		//Imprime uma linha formatada incial
			char Titulo[MAX_TITULO]="null";
			int ISBN=0;
			float Valor=0;
			int Quantidade_Estoque=0;
    		fprintf(file_estoque,"%f %d %d %s\n", Valor, Quantidade_Estoque, ISBN, Titulo);
			fclose(file_estoque);
			//Chama a main();
			main();
		}
    }
    else
    {
		//printf("Arquivo \"estoque.txt\" aberto com sucesso.\n");
	}
	
	return file_estoque;
}

FILE* Init_Saldo()
{
	//printf("Funcao \"saldo.txt\".\n");

	//Ponteiro para saldo.txt
	FILE* file_saldo;
	
	// r+ -> abre o arquivo para leitura e escrita, no inicio do arquivo. O arquivo tem que existir.
	if ( (file_saldo=fopen ("saldo.txt","r+"))==NULL )
	{
		printf ("Erro na abertura do arquivo \"saldo.txt\".\n");
		// a+ -> abre o arquivo para leitura e escrita, no final do arquivo. Se o arquivo não existir, função o cria.
		if ( (file_saldo=fopen ("saldo.txt","a+"))==NULL )
		{
			printf ("Erro na criacao do arquivo \"saldo.txt\".\n");
			//Exibe o erro
			perror("Error:");
			//Retorna null
			return NULL;	
		}
	    else
  	    {
			printf("Arquivo \"saldo.txt\" criado com sucesso.\n");
			
			//Imprime uma linha formatada incial
			float h=0;
			fprintf(file_saldo,"%f\n",h);
			fclose(file_saldo);
			//Chama a main();
			main();
		}
    }
    else
    {
		//printf("Arquivo \"saldo.txt\" aberto com sucesso.\n");
	}	
	
	return file_saldo;
}

int Escolha()
{
	//printf("Funcao Menu.\n");

	//Inicialização variável local
	char string[100]=" ";
	
	//Interface de entrada de dados
	printf("\n\n##Menu##\n");
	printf("\n1. Cadastra Livro \
	\n2. Consulta Estoque \
	\n3. Vender um Livro \
	\n4. Consultar Saldo da loja \
	\n5. Salvar Dados \
	\n9. Sair ");
	
	//Utiliza validadorNumeral para receber uma entrada válida, e retorna esse valor validado
	return validadorNumeral("\nOpcao: ");
}

void Cadastra_Livro(FILE *file_estoque, Livro* EstoqueLivros, int* numero_obras_diferentes_pointer)
{
	//printf("Funcao cadastra livro.\n");
	
	//Inicialização de variaveis locais
	int i=0;
	char Titulo[MAX_TITULO]=" ";
	int ISBN=0;
	float Valor=0;
	long unsigned int Quantidade_Estoque=0;
	int consultaISBN=0;
	int consultaTitulo=0;
	
	//Interface de entrada de dados
	printf("\n\n##Cadastra Livro##\n");
	//Utiliza validadorISBN para receber um ISBN válido
	ISBN = validadorISBN("\nDigite o ISBN do livro:\t");
	
	//consultaEstoqueISBN(); retorna um numero maior ou igual a 0 se existir uma obra com o ISBN informado
	consultaISBN = consultaEstoqueISBN(ISBN, EstoqueLivros, *numero_obras_diferentes_pointer);
	if( consultaISBN>=0 )
	{
		printf("\nJa existe um livro com este ISBN!\n");
		//Utiliza validadorNumeral para receber uma entrada válida
		Quantidade_Estoque = validadorNumeral("\nDigite a quantidade para adicionar ao estoque:\t");
		EstoqueLivros[consultaISBN].Quantidade_Estoque += Quantidade_Estoque;
	}
	else
	{
		printf("\nDigite o Titulo do livro:\t");
		gets(Titulo);
		//Limpa o buffer do teclado
		fflush(stdin);
		//consultaEstoqueTitulo(); retorna -1 se não existir nenhuma obra com o Titulo informado
		consultaTitulo = consultaEstoqueTitulo(Titulo, EstoqueLivros, *numero_obras_diferentes_pointer);
		if( consultaTitulo == -1 )
		{
			Valor = validadorValor("\nDigite o Valor unitario:\t");
			//Utiliza validadorNumeral para receber uma entrada válida
			Quantidade_Estoque = validadorNumeral("\nDigite a quantidade em estoque:\t");
			//Limpa o buffer do teclado
			fflush(stdin);
			
			//Escreve em EstoqueLivros
			for(i=0; i<MAX_TITULO ;i++)
			{
				if(Titulo[i]==' ')
				{
					Titulo[i]='_';
				}
				EstoqueLivros[*numero_obras_diferentes_pointer].Titulo[i] = Titulo[i];
			}
			EstoqueLivros[*numero_obras_diferentes_pointer].ISBN = ISBN;
			EstoqueLivros[*numero_obras_diferentes_pointer].Quantidade_Estoque = Quantidade_Estoque;
			EstoqueLivros[*numero_obras_diferentes_pointer].Valor = Valor;
			
			//Incrementa numero de obras
			*numero_obras_diferentes_pointer = (*numero_obras_diferentes_pointer) + 1;
			printf("\nNova obra cadastrada com sucesso!\n");
		}
		else
		{
			printf("\nJa existe um livro com este Titulo!\n");
		}
	}
	
}
void Consulta_Estoque(Livro* EstoqueLivros, int numero_obras_diferentes)
{
	//printf("Funcao consulta estoque.\n");
	
	//Incialização de variáveis locais
	int opcao=0;
    int ISBN=0;
	int posicao=0;
	char string[MAX_TITULO]=" ";
	
	//Exibição do submenu
	printf("\n1.Consulta por titulo\
			\n2.Consulta por ISBN");
	//Utiliza validadorNumeral para receber uma entrada válida
	opcao = validadorNumeral("\nOpcao: ");
	
	switch(opcao)
	{
		case 1:
			printf("\nDigite o Titulo do livro:\t");
			//Pega a string digitada pelo usuário
			gets(string);
			//Limpa o buffer do teclado
			fflush(stdin);
			//Imprime as obras que tem a substring informada
			consultaEstoqueTituloString(string, EstoqueLivros, numero_obras_diferentes);
			break;
			
		case 2:
			//Utiliza validadorISBN para receber um ISBN válido
			ISBN = validadorISBN("Digite o ISBN da obra:\t");
			//consultaEstoqueISBN(); retorna um numero maior ou igual a 0 se existir uma obra com o ISBN informado
			posicao = consultaEstoqueISBN(ISBN, EstoqueLivros, numero_obras_diferentes);
			if( posicao>=0 )
			{
				//Interface de saída de dados
				printf("\n\n##Consulta Estoque##\n");
				printf("\nISBN do livro:");
				printf("\t%d\n", EstoqueLivros[posicao].ISBN);
				printf("\nTitulo do livro:");
				printf("\t%s\n", EstoqueLivros[posicao].Titulo);	
				printf("\nValor unitario:");
				printf("\tR$ %.3f\n ", EstoqueLivros[posicao].Valor);
				printf("\nQuantidade em estoque:");	
				printf("\t%d \n", EstoqueLivros[posicao].Quantidade_Estoque);
				printf("\nLivro consultado com sucesso!\n");
			}
			else
			{
				printf("\nNenhuma obra com esse ISBN encontrada!\n");
			}
			break;
			
		default:
			printf("\nOpcao invalida!\n");
			break;
	}		
}

void vendeLivro(float* saldo_pointer, Livro* EstoqueLivros, int numero_obras_diferentes)
{
	//printf("Funcao vende livro.\n");
	
	//Inicialização de variaveis locais
	int ISBN=0;
	int subtracao=0;
	int quantidade=0;
	int consulta=0;
	float venda=0;
	
	//Interface de entrada de dados
	//Utiliza validadorISBN para receber um ISBN válido
	ISBN=validadorISBN("Digite o ISBN da obra:\t");

	//Consulta ISBN
	consulta = consultaEstoqueISBN(ISBN, EstoqueLivros, numero_obras_diferentes);
	if( consulta>=0 )
	{
		printf("\nObra com esse ISBN encontrada!\n");
		//Utiliza validadorNumeral para receber uma entrada válida
		quantidade = validadorNumeral("\nDigite a quantidade desejada:\t");

		subtracao = EstoqueLivros[consulta].Quantidade_Estoque - quantidade;
		if( subtracao>=0 )
		{
			EstoqueLivros[consulta].Quantidade_Estoque = subtracao;
			venda = quantidade*(EstoqueLivros[consulta].Valor);
			*saldo_pointer += venda; //Incrementa saldo com venda
			printf("\nEstoque suficiente para efetuar a venda!\n");
			printf("\nValor da venda:%f\n", venda);

		}
		else
		{
			printf("\nNao tem estoque suficiente!\n");
		}
	}
	else
	{
		printf("\nNenhuma obra com esse ISBN encontrada!\n");
	}
	
}

void consultaSaldo(float saldo)
{
	//printf("Funcao consulta saldo.\n");
	
	printf("\nSaldo:\t%f\n",saldo);
}

void salvaDados(float saldo, Livro* EstoqueLivros, int numero_obras_diferentes)
{
	//printf("Funcao salva dados.\n");
	
	//Inicialização de variaveis locais
	int i=0,x=0;
	char Titulo[MAX_TITULO];
	int ISBN=0;
	float Valor=0;
	long unsigned int Quantidade_Estoque=0;
	
	//Ponteiro para estoque.txt
	FILE* file_estoque;

	// w+ -> abre o arquivo para leitura e escrita. Se já havia o arquivo ele é perdido.
	if ( (file_estoque=fopen ("estoque.txt","w+"))==NULL )
	{
		printf ("Erro salvaDados em \"estoque.txt\".\n");
    }
    else
    {
    	for(x=0; x<numero_obras_diferentes ;x++)// indica o fim de um arquivo
		{
			//Atribui EstoqueLivros[x] as respectivas variáveis locais
			for(i=0; i<MAX_TITULO ;i++)
			{
				Titulo[i]=EstoqueLivros[x].Titulo[i];
				if(Titulo[i]==' ')
				{
					Titulo[i]='_';
				}
			}
			ISBN=EstoqueLivros[x].ISBN;
			Valor=EstoqueLivros[x].Valor;
			Quantidade_Estoque=EstoqueLivros[x].Quantidade_Estoque;
			
			//Imprime variáveis locais
			fprintf(file_estoque,"%f %d %d %s\n", Valor, Quantidade_Estoque, ISBN, Titulo);
		}
		//printf("Sucesso salvaDados em \"estoque.txt\".\n");
	}
	
	
	//ponteiro para saldo.txt
	FILE* file_saldo;
	
	// w+ -> abre o arquivo para leitura e escrita. Se já havia o arquivo ele é perdido.
	if ( (file_saldo=fopen ("saldo.txt","w+"))==NULL )
	{
		printf ("Erro salvaDados em \"saldo.txt\".\n");
    }
    else
    {
    	//Salva todos o saldo em saldo.txt
    	fprintf(file_saldo,"%f\n",saldo);
    	fclose(file_saldo);
		//printf("Sucesso salvaDados em \"saldo.txt\".\n");
	}
	
}

int Puxa_Estoque(FILE* file_estoque, Livro* EstoqueLivros)
{
	//printf("Funcao puxa estoque.\n");
	
	//Inicialização de variaveis locais
	int i=0,x=0;
	char Titulo[MAX_TITULO];
	int ISBN=0;
	float Valor=0;
	long unsigned int Quantidade_Estoque=0;
	int numero_obras=0;
	
	//Le em estoque.txt
	for(; fscanf(file_estoque,"%f %d %d %s\n", &Valor, &Quantidade_Estoque, &ISBN, Titulo)!=EOF ;x++)// indica o fim de um arquivo
	{	
		//Testa se a linha é válida
		if( strcmp("null",&(Titulo[0])) )
		{
			numero_obras++;
			for(i=0; i<MAX_TITULO ;i++)
			{
				if(Titulo[i]=='_')
				{
					Titulo[i]=' ';
				}
				EstoqueLivros[x].Titulo[i]=Titulo[i];
			}
			EstoqueLivros[x].ISBN=ISBN;
			EstoqueLivros[x].Valor=Valor;
			EstoqueLivros[x].Quantidade_Estoque=Quantidade_Estoque;
		}
	}
	
	//Retorna o numero de obras diferentes que o arquivo "estoque.txt" possui
	return numero_obras;
}

float Puxa_Saldo(FILE* file_saldo)
{
	//printf("Funcao puxa saldo.\n");
	
	//Inicialização de variaveis locais
	float saldo=0;
	
	//Puxa saldo de "saldo.txt"
	fscanf(file_saldo,"%f",&saldo);
		
	return saldo;
}

void consultaEstoqueTituloString(char* string, Livro* EstoqueLivros, int numero_obras_diferentes)
{
	//printf("Funcao consulta estoque titulo string.\n");
	
	//Inicialização de variaveis locais
	int i=0;
	
	//Procura as obras por títulos
	for(i=0; i<numero_obras_diferentes ;i++)
	{
		if( strstr(&(EstoqueLivros[i].Titulo[0]), string)!=NULL )// Testa se há substring na string
		{
			//Interface de saída de dados
			printf("\n\n##Consulta Estoque##\n");
			printf("\nISBN do livro:");
			printf("\t%d\n", EstoqueLivros[i].ISBN);
			printf("\nTitulo do livro:");
			printf("\t%s\n", EstoqueLivros[i].Titulo);	
			printf("\nValor unitario:");
			printf("\tR$ %.3f\n ", EstoqueLivros[i].Valor);
			printf("\nQuantidade em estoque:");	
			printf("\t%d \n", EstoqueLivros[i].Quantidade_Estoque);
		}
	}
}

int consultaEstoqueTitulo(char* string, Livro* EstoqueLivros, int numero_obras_diferentes)
{
	//printf("Funcao consulta estoque titulo.\n");
	
	//Inicialização de variaveis locais
	int i=0;
	
	//Procura as obras por títulos
	for(i=0; i<numero_obras_diferentes ;i++)
	{
		if( !strcmp(string,&(EstoqueLivros[i].Titulo[0])) )//Testa se str1 é igual a str2.
		{
			return i;
		}
	}
	
	return -1;
}

int consultaEstoqueISBN(int ISBN, Livro* EstoqueLivros, int numero_obras_diferentes)
{
	//printf("Funcao consulta estoque ISBN.\n");
	
	//Inicialização de variaveis locais
	int i=0;
	
	//Procura as obras por ISBN
	for(i=0; i<numero_obras_diferentes ;i++)
	{
		if( ISBN==EstoqueLivros[i].ISBN )//Testa se o ISBN informado é igual a algum ISBN em EstoqueLivros
		{
			return i;
		}
	}
	
	return -1;
}

int validadorNumeral(const char* texto)
{
	//printf("Funcao validador numeral.\n");
	
	//Inicialização de variáveis locais
	char string[MAX_TITULO]=" ";
	int i=0;
	int caractere=0;
	
	//Exibição de texto
	printf("%s",texto);
	gets(string);
	
	//Limpa o buffer do teclado
	fflush(stdin);
	
	//Testa se a entrada é vazia
	if(string[0]=='\0')
	{
		printf("\nEntrada vazia!\n");
		return validadorNumeral(texto);
	}
	
	//Testa se a string e composta somente por numeros
	for(i=0; string[i]!='\0' ;i++)
	{	
		
		//Testa se string[i] e um numero
		if(string[i]>=48 && string[i]<=57)//Tabela ascii ((0 corresponde a 48)) e ((9 corresponde a 57))
		{
			//printf("%c",string[i]);
		}
		else
		{
			caractere=1;
		}
	}
	
	//Testa se a string tem pelo menos um caractere
	if(caractere==1)
	{
		printf("\nEntrada necessita ser composta somente por numeros!\n");
		return validadorNumeral(texto);
	}
	
	//Converte a string em inteiro e testa se é igual a 0
	if(atoi(string)==0)
	{
		printf("\nEntrada necessita ser diferente de zero!\n");
		return validadorNumeral(texto);
	}

	//Converte a string em um inteiro, e retorna esse valor
	return atoi(string);
}

int validadorISBN(const char* texto)
{
	//printf("Funcao validador ISBN.\n");
	
	//Inicialização de variáveis locais
	char string[MAX_TITULO]=" ";
	int i=0;
	int caractere=0;
	int numero=0;
	
	//Exibição de texto
	printf("%s",texto);
	gets(string);
	
	//Limpa o buffer do teclado
	fflush(stdin);
	
	//Testa se a entrada é vazia
	if(string[0]=='\0')
	{
		printf("\nEntrada vazia!\n");
		return validadorISBN(texto);
	}
	
	//Testa se a string e composta somente por numeros
	for(i=0; string[i]!='\0' ;i++)
	{	
		
		//Testa se string[i] e um numero
		if(string[i]>=48 && string[i]<=57)//Tabela ascii ((0 corresponde a 48)) e ((9 corresponde a 57))
		{
			numero++;
			//printf("-%c-",string[i]);
		}
		else
		{
			caractere=1;
		}
	}
	
	//Testa se a string tem pelo menos um caractere
	if(caractere==1)
	{
		printf("\nEntrada necessita ser composta somente por numeros!\n");
		return validadorISBN(texto);
	}
	
	//Testa se a string e composta por nove numeros
	else if(numero!=9)
	{
		printf("\nEntrada necessita ser composta por 9 numeros!\n");
		return validadorISBN(texto);
	}
	
	//Converte a string em um inteiro, e retorna esse valor
	return atoi(string);
}

float validadorValor(const char* texto)
{
	//printf("Funcao validador valor.\n");
	
	//Inicialização de variáveis locais
	char string[MAX_TITULO]=" ";
	int i=0;
	int caractere=0;
	int ponto=0;
	
	//Exibição de texto
	printf("%s",texto);
	gets(string);

	//Limpa o buffer do teclado
	fflush(stdin);
	
	//Testa se a entrada é vazia
	if(string[0]=='\0')
	{
		printf("\nEntrada vazia!\n");
		return validadorValor(texto);
	}
	
	//Testa se a string e composta somente por numeros
	for(i=0; string[i]!='\0' ;i++)
	{	
		
		if(string[i]==46)
		{
			ponto++;
		}
		//Testa se string[i] e um numero
		else if( string[i]>=48 && string[i]<=57 )//Tabela ascii ((0 corresponde a 48)) e ((9 corresponde a 57))
		{
			//printf("%c",string[i]);
		}
		else
		{
			caractere=1;
		}
	}
	
	//Testa se a string possui mais de um "."
	if(ponto>1)
	{
		printf("\nEntrada necessita ter somente um ponto!\n");
		return validadorValor(texto);
	}
	
	//Testa se a string possui pelo menos um termo diferente de numero
	if(caractere==1)
	{
		printf("\nEntrada necessita ser composta somente por numeros!\n");
		return validadorValor(texto);
	}

	//Converte a string em um float, e retorna esse valor
	return atof(string);
}
