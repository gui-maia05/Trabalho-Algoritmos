#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct TimeFutebol{
	int identificador;
	string nome;
	string local;
	short anoFundacao;
	int titulos;
};

TimeFutebol* leituraArquivo(ifstream &arquivo_csv, int &NumRegistros){
    char lixo;
    TimeFutebol* dados = new TimeFutebol[NumRegistros];
    
    for(int i = 0; i <  NumRegistros; i++){
		arquivo_csv >> dados[i].identificador;
        arquivo_csv >> lixo;
        getline(arquivo_csv, dados[i].nome, ',');
        getline(arquivo_csv, dados[i].local, ',');
        arquivo_csv >> dados[i].anoFundacao;
        arquivo_csv >> lixo;
        arquivo_csv >> dados[i].titulos;
        arquivo_csv.ignore(); // Pula o fim de linha
    }
    return dados;
}

void MostrarArquivo(TimeFutebol *dados, int NumRegistros){ //Ver o arquivo
	for (int i = 0; i < NumRegistros; i++){
		cout << "Posicao no Ranking: "<< dados[i].identificador << endl
		<< "Nome do Clube: " << dados[i].nome << endl
		<< "Cidade (Pais): " << dados[i].local << endl
		<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
		<< "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
	}
}

void BuscaRanking(TimeFutebol *dados, int PosInicial, int PosFinal){ //Busca Binaria pelo Ranking de Clubes
	int meio;
	int Ranking;
	bool encontrado = false;
	cout << "Digite a posicao no Ranking(1-100): ";
    cin >> Ranking;
    cout << endl;

	while (PosInicial <= PosFinal and !encontrado){
		meio = (PosFinal + PosInicial)/2;
		if(Ranking == dados[meio].identificador){
			cout << "Posicao no Ranking: " << dados[meio].identificador << endl
            << "Nome do Clube: " << dados[meio].nome << endl
            << "Cidade (Pais): " << dados[meio].local << endl
            << "Ano de Fundacao: " << dados[meio].anoFundacao << endl
            << "Quantidade Total de Titulos: " << dados[meio].titulos << endl << endl;
			encontrado = true;
		}
		else if(dados[meio].identificador < Ranking)
		PosInicial = meio + 1;
		else
		PosFinal = meio - 1;
	}
	if (!encontrado)
	cout << "Nenhum clube foi encontrado na posicao " << Ranking <<  "!" << endl;
}

void BuscaNomeClube(TimeFutebol *dados, int PosInicial, int PosFinal){ //Busca Binaria por Nome do Clube
	int meio;
	string NomeClube;
	bool encontrado = false;
	cout << "Digite o nome do clube: ";
    cin.ignore();
	getline(cin, NomeClube);

	cout << endl;

	while(PosInicial <= PosFinal and !encontrado){
		meio = (PosInicial + PosFinal)/2;
		if(NomeClube == dados[meio].nome){
			cout << "Posicao no Ranking: " << dados[meio].identificador << endl
            << "Nome do Clube: " << dados[meio].nome << endl
            << "Cidade (Pais): " << dados[meio].local << endl
            << "Ano de Fundacao: " << dados[meio].anoFundacao << endl
            << "Quantidade Total de Titulos: " << dados[meio].titulos << endl << endl;
			encontrado = true;
		}
		else if(dados[meio].nome < NomeClube)
		PosInicial = meio + 1;
		else
		PosFinal = meio - 1;
	}
	if(!encontrado)
	cout << "O clube " << NomeClube << " nao esta no banco de dados!";
}

int ParticionamentoTitulos_Crescente(TimeFutebol *dados, int c, int f){ 
   int pivo = dados[c].titulos;
   TimeFutebol PivoPrincipal = dados[c];
   int i = c+1, j = f;
   while (i <= j) {
       if (dados[i].titulos <= pivo) i++;
       else if (pivo <= dados[j].titulos) j--; 
       else { 
           swap (dados[i],dados[j]);
           i++;
           j--;
       }
   }                  
   dados[c] = dados[j];
   dados[j] = PivoPrincipal;
   return j; 
}

void QuickSortTitulosCrescente(TimeFutebol *dados, int PosPivo, int fim){
   int PosNovoPivo;         
   if (PosPivo < fim) {  
      PosNovoPivo = ParticionamentoTitulos_Crescente(dados, PosPivo, fim);
      QuickSortTitulosCrescente(dados, PosPivo, PosNovoPivo - 1); 
      QuickSortTitulosCrescente(dados, PosNovoPivo + 1, fim); 
   }
}

int ParticionamentoTitulos_Decrescente(TimeFutebol *dados, int c, int f){ 
   int pivo = dados[c].titulos;
   TimeFutebol PivoPrincipal = dados[c];
   int i = c+1, j = f;
   while (i <= j) {
       if (dados[i].titulos >= pivo) i++;
       else if (pivo >= dados[j].titulos) j--; 
       else { 
           swap (dados[i],dados[j]);
           i++;
           j--;
       }
   }                  
   dados[c] = dados[j];
   dados[j] = PivoPrincipal;
   return j; 
}

void QuickSortTitulosDecrescente(TimeFutebol *dados, int PosPivo, int fim){
   int PosNovoPivo;         
   if (PosPivo < fim) {  
      PosNovoPivo = ParticionamentoTitulos_Decrescente(dados, PosPivo, fim);
      QuickSortTitulosDecrescente(dados, PosPivo, PosNovoPivo - 1); 
      QuickSortTitulosDecrescente(dados, PosNovoPivo + 1, fim); 
   }
}

int ParticionamentoClubes_Cresecente(TimeFutebol *dados, int c, int f){ 
   string pivo = dados[c].nome;
   TimeFutebol PivoPrincipal = dados[c];
   int i = c+1, j = f;
   while (i <= j) {
       if (dados[i].nome <= pivo) i++;
       else if (pivo <= dados[j].nome) j--; 
       else { 
           swap (dados[i],dados[j]);
           i++;
           j--;
       }
   }                
   dados[c] = dados[j];
   dados[j] = PivoPrincipal;
   return j; 
}

void QuickSortClubesCrescente(TimeFutebol *dados, int pos_pivo, int fim){
   int pos_novo_pivo;         
   if (pos_pivo < fim) {  
      pos_novo_pivo = ParticionamentoClubes_Cresecente(dados, pos_pivo, fim);
      QuickSortClubesCrescente(dados, pos_pivo, pos_novo_pivo - 1); 
      QuickSortClubesCrescente(dados, pos_novo_pivo + 1, fim); 
   }
}

int ParticionamentoClubes_Decrescentes(TimeFutebol *dados, int c, int f){
	string pivo = dados[c].nome;
	TimeFutebol PivoPrincipal = dados[c];
	int i = c+1, j = f;
	while(i <= j){
		if (dados[i].nome >= pivo) i++;
		else if(pivo >= dados[j].nome) j--;
		else{
			swap(dados[i], dados[j]);
			i++;
			j--;
		}
	}
	dados[c] = dados[j];
	dados[j] = PivoPrincipal;
	return j;
}

void QuickSortClubesDecrecente(TimeFutebol *dados, int PosPivo, int fim){
	int PosNovoPivo;
	if(PosPivo < fim){
		PosNovoPivo = ParticionamentoClubes_Decrescentes(dados, PosPivo, fim);
		QuickSortClubesDecrecente(dados, PosPivo, PosNovoPivo - 1);
		QuickSortClubesDecrecente(dados, PosNovoPivo + 1, fim);
	}
}

int ParticionamentoAno_Crescente(TimeFutebol *dados, int c, int f){
	int pivo = dados[c].anoFundacao;
	TimeFutebol PivoPrincipal = dados[c];
	int i = c+1, j = f;
	while (i <= j){
		if (dados[i].anoFundacao <= pivo) i++;
		else if(pivo <= dados[j].anoFundacao) j--;
		else{
			swap(dados[i], dados[j]);
			i++;
			j--;
		}
	}
	dados[c] = dados[j];
	dados[j] = PivoPrincipal;
	return j;
}

void QuickSortAnoCrescente(TimeFutebol *dados, int PosPivo, int fim){
	int PosNovoPivo;
	if (PosPivo < fim){
		PosNovoPivo = ParticionamentoAno_Crescente(dados, PosPivo, fim);
		QuickSortAnoCrescente(dados, PosPivo, PosNovoPivo - 1);
		QuickSortAnoCrescente(dados, PosNovoPivo + 1, fim);
	}
}

int ParticionamentoAno_Decrescente(TimeFutebol *dados, int c, int f){
    int pivo = dados[c].anoFundacao;
    TimeFutebol PivoPrincipal = dados[c];
    int i = c+1, j = f;
    while(i <= j){
        if(dados[i].anoFundacao >= pivo) i++;
        else if(pivo >= dados[j].anoFundacao) j--;
        else{
            swap(dados[i], dados[j]);
            i++;
            j--;
        }
    }
    dados[c] = dados[j];
    dados[j] = PivoPrincipal;
    return j;
}

void QuickSortAnoDecrescente(TimeFutebol *dados, int PosPivo, int fim){
    int PosNovoPivo;
    if (PosPivo < fim){
        PosNovoPivo = ParticionamentoAno_Decrescente(dados, PosPivo, fim);
        QuickSortAnoDecrescente(dados, PosPivo, PosNovoPivo -1);
        QuickSortAnoDecrescente(dados, PosNovoPivo + 1, fim);
    }
}

int ParticionamentoPosicao_Crescente(TimeFutebol *dados, int c, int f){
	int pivo = dados[c].identificador;
	TimeFutebol PivoPrincipal = dados[c];
	int i = c+1, j = f;
	while (i <= j){
		if (dados[i].identificador <= pivo) i++;
		else if(pivo <= dados[j].identificador) j--;
		else{
			swap(dados[i], dados[j]);
			i++;
			j--;
		}
	}
	dados[c] = dados[j];
	dados[j] = PivoPrincipal;
	return j;
}

void QuickSortPosicaoCrescente(TimeFutebol *dados, int PosPivo, int fim){
	int PosNovoPivo;
	if (PosPivo < fim){
		PosNovoPivo = ParticionamentoPosicao_Crescente(dados, PosPivo, fim);
		QuickSortPosicaoCrescente(dados, PosPivo, PosNovoPivo -1);
		QuickSortPosicaoCrescente(dados, PosNovoPivo + 1, fim);
	}
}

void PesquisarLinhas(TimeFutebol *dados, int NumRegistros, int LinhaInicial, int LinhaFinal){
    if(LinhaInicial <= LinhaFinal){
        if (LinhaInicial < NumRegistros and LinhaFinal <= NumRegistros){
            for (int i = LinhaInicial - 1; i < LinhaFinal; i++){
                cout << "Posicao no Ranking: "<< dados[i].identificador << endl
		        << "Nome do Clube: " << dados[i].nome << endl
		        << "Cidade (Pais): " << dados[i].local << endl
		        << "Ano de Fundacao: " << dados[i].anoFundacao << endl
		        << "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
            }
        }
        if (LinhaInicial > NumRegistros)
        cout << "A linha incial escolhida e maior que o numero de registros!" << endl;
        if (LinhaFinal > NumRegistros)
        cout << "A linha final escolhida e maior que o numero de registros!" << endl;
    }
    else
    cout << "A linha inicial deve ser menor que a linha final!" << endl;
}

void NovoElemento(TimeFutebol* &dados, int &NumRegistros){
	TimeFutebol* aumentar = new TimeFutebol[NumRegistros + 1];

	for (int i = 0; i < NumRegistros; i++){
		aumentar[i] = dados[i];
	}
	int x;

	cout << "Insira as informacoes do novo clube!" << endl;
	cout << "Posicao no Ranking: ";
	cin >> x;
	cout << "Nome do Clube: ";
	cin.ignore();
	getline(cin, aumentar[NumRegistros].nome);
	cout << "Cidade (Pais): ";
	getline(cin, aumentar[NumRegistros].local);
	cout << "Ano de Fundacao: ";
	cin >> aumentar[NumRegistros].anoFundacao;
	cout << "Quantidade Total de Titulos: ";
	cin >> aumentar[NumRegistros].titulos;

	aumentar[NumRegistros].identificador = x - 1;

	int posicao = NumRegistros;

	while (posicao > 0 and aumentar[posicao].identificador < aumentar[posicao - 1].identificador){
		swap(aumentar[posicao], aumentar[posicao -1]);
		posicao--;
	}

	delete[] dados;
	dados = aumentar;
	NumRegistros++;

	//Gravar os dados em um arquivo
	int opcao;
	string nome_arquivo;

	cout << "Gostaria de gravar a alteracao em um arquivo?" << endl
	<< "[1] Sim" << endl << "[2] Nao" << endl;
	cout << "Digite um valor: ";

	cin >> opcao;

	if (opcao == 1){
		cout << "Qual o nome do arquivo que deseja gravar?" << endl;
		cin >> nome_arquivo;
		ofstream arquivo(nome_arquivo);
		arquivo << "#Ranking Mundial de Clubes,Nome do Time,Cidade (País),Ano de Fundação,Numero de Títulos" << endl;
		arquivo << NumRegistros;
		arquivo << endl;
		for (int i = 0; i < NumRegistros; i++){
			arquivo << i + 1 << ',' 
			<< dados[i].nome << ','
			<< dados[i].local << ','
			<< dados[i].anoFundacao << ','
			<< dados[i].titulos << endl;
		}
		cout << endl << "Novo clube inserido no banco de dados!" << endl << endl;
	}
	else
	cout << "As alteracoes nao foram gravadas em nehum arquivo!" << endl << endl;	
}

void ExcluirElemento(TimeFutebol* &dados, int &NumRegistros, int RankingProcurado){
	int Ranking;
	bool encontrado = false;
	int j = 0;

	while(j < NumRegistros and !encontrado){
		Ranking = dados[j].identificador;

		if (RankingProcurado == Ranking){
			for (int i = j; i < NumRegistros - 1; i++){
                dados[i] = dados[i + 1];
			}
			NumRegistros--;
			encontrado = true;
		}
		j++;
	}

	if (!encontrado){
		cout << " Não foi encontrada a posicao no arquivo!" << endl;
	}

	//Gravar os dados em um arquivo
	int opcao;
	string nome_arquivo;

	cout << "Gostaria de gravar a alteracao no arquivo?" << endl
	<< "[1] Sim" << endl << "[2] Nao" << endl;
	cout << "Digite um valor: ";

	cin >> opcao;

	if (opcao == 1){
		ofstream arquivo("TimesFutebol.csv");
		arquivo << "#Ranking Mundial de Clubes,Nome do Time,Cidade (País),Ano de Fundação,Numero de Títulos" << endl;
		arquivo << NumRegistros;
		arquivo << endl;
		for (int i = 0; i < NumRegistros; i++){
			arquivo << i + 1 << ',' 
			<< dados[i].nome << ','
			<< dados[i].local << ','
			<< dados[i].anoFundacao << ','
			<< dados[i].titulos << endl;
		}
		cout << endl << "Clube excluido com sucesso!" << endl << endl;
	}
	else
	cout << "As alteracoes nao foram gravadas no arquivo!" << endl << endl;
}

int main(){
	string linha;
	int NumRegistros;
	
	ifstream Arquivo("TimesFutebol.csv");
	if (not(Arquivo)){
		cout << " Nao foi possivel acessar o arquivo! " << endl;
	}
	else{
		getline(Arquivo, linha); //descarta a  primeira linha do arquivo
		Arquivo >> NumRegistros;
		Arquivo.ignore();//pula o fim de linha
	}
	TimeFutebol* dados;
	dados = leituraArquivo(Arquivo, NumRegistros);

	int escolha1, escolha2, escolha3;
    int LinhaInicial, LinhaFinal;
	bool Repetir = true;

	while(Repetir){
		cout << "Escolha uma das Opcoes Disponiveis:" << endl
		<< "[1] Realizar uma busca" << endl
		<< "[2] Ordenar o vetor" << endl
        << "[3] Ver o Arquivo" << endl
		<< "[4] Adicionar um novo elemento" << endl
		<< "[5] Excluir um elemento" << endl
		<< "[-1] Sair do programa" << endl;
		cout << "Digite um valor: ";
		cin >> escolha1;
        cout << endl;
		switch (escolha1){

			case 1: //Chama as funções de busca
				cout << "[1] Realizar uma busca pelo ranking dos clubes " << endl
				<< "[2] Realizar uma busca pelo nome do clube" << endl;
				cout << "Digite um valor: ";
				cin >> escolha2;
				switch (escolha2){
					case 1:
					QuickSortPosicaoCrescente(dados, 0, NumRegistros-1);
					BuscaRanking(dados, 0, NumRegistros -1);
					break;

					case 2:
                	QuickSortClubesCrescente(dados, 0, NumRegistros -1);
					BuscaNomeClube(dados, 0, NumRegistros -1);
					break;
				}
			break;
			
			case 2://Chama as funções de ordenação
				cout << "Escolha um dos campos que deseja ordenar" << endl
				<< "[1] Nome do Clube" << endl
				<< "[2] Ano de Fundacao" << endl
				<< "[3] Numero de Titulos" << endl;
				cout << "Digite um valor: ";
				cin >> escolha2;
           		cout << endl;
				switch (escolha2){
			    	case 1:
			    	cout << "Como deseja ordenar?" << endl
			    	<< "[1] Ordem Alfabetica Crescente" << endl
			    	<< "[2] Ordem Alfabetica Decrescente" << endl;
			    	cout << "Digite um valor: ";
			    	cin >> escolha3;
                	cout << endl;
			    	switch(escolha3){
				    	case 1:
				    	QuickSortClubesCrescente(dados, 0, NumRegistros -1);
                    	MostrarArquivo(dados, NumRegistros);
				    	break;

                    	case 2:
                    	QuickSortClubesDecrecente(dados, 0 , NumRegistros -1);
                    	MostrarArquivo(dados,NumRegistros);
                    	break;
			    	}
			    	break;

                	case 2:
                	cout << "Como deseja ordenar?" << endl
                	<< "[1] Crescente" << endl << "[2] Decrescente" << endl;
                	cout << "Digite um valor: ";
                	cin >> escolha3;
                	cout << endl;
                	switch(escolha3){
                    	case 1:
                    	QuickSortAnoCrescente(dados, 0, NumRegistros -1);
                    	MostrarArquivo(dados, NumRegistros);
                    	break;

                    	case 2:
                    	QuickSortAnoDecrescente(dados, 0, NumRegistros -1);
                    	MostrarArquivo(dados, NumRegistros);
                    	break;
                	}
                	break;

            		case 3:
                	cout << "Como deseja ordenar?" << endl
               		<< "[1] Crescente" << endl
                	<< "[2] Decrescente" << endl;
                	cout << "Digite um valor: ";
                	cin >> escolha3;
                	cout << endl;
                	switch(escolha3){
                    	case 1:
                    	QuickSortTitulosCrescente(dados, 0, NumRegistros -1);
                    	MostrarArquivo(dados, NumRegistros);
                    	break;

                    	case 2:
                    	QuickSortTitulosDecrescente(dados, 0, NumRegistros -1);
                    	MostrarArquivo(dados, NumRegistros);
                    	break;
                	}
                	break;
				}
            break;

            case 3: //Pesquisar por linhas
				cout << "[1] Ver arquivo completo" << endl
				<< "[2] Pesquisar a partir de uma linha inicial ate uma linha final" << endl;
				cout << "Digite um valor: ";
				cin >> escolha2;
				switch (escolha2){
					case 1:
					QuickSortPosicaoCrescente(dados, 0, NumRegistros -1);
					MostrarArquivo(dados, NumRegistros);
					break;
			
					case 2:
					cout << "Digite a linha Inicial: ";
            		cin >> LinhaInicial;
            		cout << "Digite a linha Final: ";
            		cin >> LinhaFinal;
            		cout << endl;
					QuickSortPosicaoCrescente(dados, 0, NumRegistros-1);
            		PesquisarLinhas(dados, NumRegistros, LinhaInicial, LinhaFinal);
            		break;
				}
			break;

			case 4: //Chama a função de Adicionar um novo elemento
				QuickSortPosicaoCrescente(dados, 0, NumRegistros -1);
				NovoElemento(dados, NumRegistros);
				Repetir = false;
				break;
			
			case 5:
				int RankingProcurado;
				cout << "Digite a posicao que deseja excluir: ";
				cin >> RankingProcurado;
				QuickSortPosicaoCrescente(dados, 0, NumRegistros -1);
				ExcluirElemento(dados, NumRegistros, RankingProcurado);
				break;


			case -1: //Sair
			cout << "Obrigado por testar!" << endl;
			Repetir = false;
			break;

			default:
			cout << "Opcao Invalida!" << endl << endl;
			break;
		}
	}

	delete [] dados;
	Arquivo.close();
    return 0;
}
