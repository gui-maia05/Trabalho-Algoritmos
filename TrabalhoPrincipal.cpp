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

TimeFutebol* leituraArquivo (ifstream &arquivo_csv, int NumRegistros){
	char lixo;
	TimeFutebol* dados = new TimeFutebol[NumRegistros];
	
	for (int i = 0; i < NumRegistros; i++){
		//le uma linha do arquivo();
		arquivo_csv >> dados[i].identificador;
		arquivo_csv >> lixo;
		getline(arquivo_csv, dados[i].nome, ',');
		getline(arquivo_csv, dados[i].local, ',');
		arquivo_csv >> dados[i].anoFundacao;
		arquivo_csv >> lixo;
		arquivo_csv >> dados[i].titulos;
		arquivo_csv.ignore(); //pula o fim de linha
	}
	return dados;
}

void CriarNovoArquivo(string nomearquivo, TimeFutebol *dados, int NumRegistros){
	ofstream Arquivo_saida(nomearquivo);
	Arquivo_saida << "#Ranking Mundial de Clubes,Nome do Time,Cidade (País),Ano de Fundação, Numero de Títulos" << endl;
	Arquivo_saida << NumRegistros << endl;
	for (int i = 0; i < NumRegistros; i++){
		Arquivo_saida << dados[i].identificador << ","
		<< dados[i].nome << "," 
		<< dados[i].local << ","
		<< dados[i].anoFundacao << ","
		<< dados[i].titulos << endl;
	}
}


void BuscaRanking(TimeFutebol *dados, int PosInicial, int PosFinal){
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
            << "Quantidade Total de Titulos: " << dados[meio].titulos << endl;
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

void BuscaNomeClube(TimeFutebol *dados, int PosInicial, int PosFinal){
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
            << "Quantidade Total de Titulos: " << dados[meio].titulos << endl;
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



int ParticionamentoTitulos_Crescente(TimeFutebol *dados, int c, int f) { 
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

void QuickSortTitulosCrescente(TimeFutebol *dados, int PosPivo, int fim) {
   int PosNovoPivo;         
   if (PosPivo < fim) {  
      PosNovoPivo = ParticionamentoTitulos_Crescente(dados, PosPivo, fim);
      QuickSortTitulosCrescente(dados, PosPivo, PosNovoPivo - 1); 
      QuickSortTitulosCrescente(dados, PosNovoPivo + 1, fim); 
   }
}

int ParticionamentoTitulos_Decrescente(TimeFutebol *dados, int c, int f) { 
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

void QuickSortTitulosDecrescente(TimeFutebol *dados, int PosPivo, int fim) {
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

void MostrarArquivo(TimeFutebol *dados, int NumRegistros){
	for (int i = 0; i < NumRegistros; i++){
		cout << "Posicao no Ranking: "<< dados[i].identificador << endl
		<< "Nome do Clube: " << dados[i].nome << endl
		<< "Cidade (Pais): " << dados[i].local << endl
		<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
		<< "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
	}
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
		cout << endl << "Escolha uma das Opcoes Disponiveis:" << endl
		<< "[1] Realizar uma busca" << endl
		<< "[2] Ordenar o vetor" << endl
        << "[3] Pesquisar a partir de uma linha inicial ate uma linha final" << endl
		<< "[-1] Sair do programa" << endl;
		cout << "Digite um valor: ";
		cin >> escolha1;
        cout << endl;
		switch (escolha1){
			case 1:
			cout << "[1] Realizar uma busca pelo ranking dos clubes " << endl
			<< "[2] Realizar uma busca pelo nome do clube" << endl;
			cout << "Digite um valor: ";
			cin >> escolha2;
			switch (escolha2){
				case 1:
				BuscaRanking(dados, 0, NumRegistros -1);
				break;

				case 2:
                QuickSortClubesCrescente(dados, 0, NumRegistros -1);
				BuscaNomeClube(dados, 0, NumRegistros -1);
			}
			break;
			
			case 2:
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
                << "[1] Crescente" << endl
                << "[2] Decrescente" << endl;
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

            case 3:
            cout << "Digite a linha Inicial: ";
            cin >> LinhaInicial;
            cout << "Digite a linha Final: ";
            cin >> LinhaFinal;
            cout << endl;
            PesquisarLinhas(dados, NumRegistros, LinhaInicial, LinhaFinal);
            break;

			case -1:
			cout << "Obrigado por testar!" << endl;
			Repetir = false;
			break;

			default:
			cout << "Opcao Invalida!" << endl;
			break;
		}
	}

	delete [] dados;
	Arquivo.close();
    return 0;
}
