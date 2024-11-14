#include <iostream>
#include <fstream>
using namespace std;

//Registro utilizada no código.
struct TimeFutebol{
	int identificador;
	char nome[40];
	char local[40];
	int anoFundacao;
	int titulos;
};

//Leitura do arquivo csv, usando redimensionamento.
TimeFutebol* leituraArquivo(ifstream &arquivo_csv, int &NumRegistros, int &Capacidade){
	char lixo;
	TimeFutebol* dados = new TimeFutebol[Capacidade];
	int i = 0;
	int aux;
	while(arquivo_csv >> aux){
		if (Capacidade == i){
			Capacidade += 10;

			TimeFutebol* novos_dados = new TimeFutebol[Capacidade];

			for (int j = 0; j < i; j++){
				novos_dados[j] = dados[j];
			}
			delete [] dados;
			dados = novos_dados;
		}	
		dados[i].identificador = aux;
		arquivo_csv >> lixo;
		arquivo_csv.getline(dados[i].nome, 40, ',');
		arquivo_csv.getline(dados[i].local, 40, ',');
		arquivo_csv >> dados[i].anoFundacao;
		arquivo_csv >> lixo;
		arquivo_csv >> dados[i].titulos;
		arquivo_csv.ignore(); 

		i++;

	}
	NumRegistros = i;
	return dados;
}

//Salvar os dados do arquivo CSV em um arquivo binário.
void salvarEmBinario(TimeFutebol *dados, int &NumRegistros) {
	ofstream arquivoBinario("times.bin", ios::binary);
	arquivoBinario.write((char*)dados, sizeof(TimeFutebol) * NumRegistros);
	arquivoBinario.close();
}

//Leitura do arquivo binário, usando redimensionamento.
TimeFutebol* leituraBinario(ifstream &arquivo_bin, int &NumRegistros, int &Capacidade){
	TimeFutebol* dados = new TimeFutebol[Capacidade];
	TimeFutebol aux;
	int i =0;
	while (arquivo_bin.read((char *)(&aux),sizeof(TimeFutebol))){
		if(i == Capacidade){
			Capacidade += 10;
			TimeFutebol* novo = new TimeFutebol[Capacidade];
			for (int j = 0; j < i ; j++){
				novo[j] = dados[j];
			}
			delete []dados;
			dados = novo;
		}
		dados[i] = aux;
		i++; 
	}
	NumRegistros = i;
	return dados;
}

//Procedimento utilizado para impressão.
void MostrarArquivo(TimeFutebol *dados, int NumRegistros){ 
	for (int i = 0; i < NumRegistros; i++){
		cout << "--------------------------------" << endl
		<< "Posicao no Ranking: "<< dados[i].identificador << endl
		<< "Nome do Clube: " << dados[i].nome << endl
		<< "Cidade (Pais): " << dados[i].local << endl
		<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
		<< "Quantidade Total de Titulos: " << dados[i].titulos << endl 
		<< "--------------------------------" << endl << endl;
	}
}

//Algoritmo de busca binária aplicado para encontrar um clube pelo seu ranking.
void BuscaRanking(TimeFutebol *dados, int PosInicial, int PosFinal, int NumRegistros){
	int meio;
	int Ranking;
	bool encontrado = false;
	cout << "Digite a posicao no ranking(1-" << NumRegistros << "): ";
	cin >> Ranking;
	cout << endl;

	while (PosInicial <= PosFinal and !encontrado){
		meio = (PosFinal + PosInicial)/2;
		if(Ranking == dados[meio].identificador){
			cout << "Veja abaixo as informacoes do clube que ocupa a posicao " << Ranking << " no ranking." << endl;
			cout << "--------------------------------" << endl
			<< "Posicao no Ranking: " << dados[meio].identificador << endl
			<< "Nome do Clube: " << dados[meio].nome << endl
			<< "Cidade (Pais): " << dados[meio].local << endl
			<< "Ano de Fundacao: " << dados[meio].anoFundacao << endl
			<< "Quantidade Total de Titulos: " << dados[meio].titulos << endl 
			<< "--------------------------------" << endl << endl;
			encontrado = true;
		}
		else if(dados[meio].identificador < Ranking)
		PosInicial = meio + 1;
		else
		PosFinal = meio - 1;
	}
	if (!encontrado)
	cout << "Nenhum clube encontrado na posicao " << Ranking << "." << endl << endl;
}

//Algoritmo de busca binária aplicado para encontrar um clube específico pelo seu nome.
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
			cout << "Aqui estao as informacoes do clube!" << endl;  
			cout << "--------------------------------" << endl
			<< "Posicao no Ranking: " << dados[meio].identificador << endl
			<< "Nome do Clube: " << dados[meio].nome << endl
			<< "Cidade (Pais): " << dados[meio].local << endl
			<< "Ano de Fundacao: " << dados[meio].anoFundacao << endl
			<< "Quantidade Total de Titulos: " << dados[meio].titulos << endl 
			<< "--------------------------------" << endl << endl;
			encontrado = true;
		}
		else if(dados[meio].nome < NomeClube)
		PosInicial = meio + 1;
		else
		PosFinal = meio - 1;
	}
	if(!encontrado)
	cout << "O clube " << NomeClube << " nao foi encontrado no banco de dados!" << endl << endl;
}

//Particionamento do Quick Sort utilizado para ordenar os titulos em ordem crescente.
int ParticionamentoTitulos_Crescente(TimeFutebol *dados, int c, int f){ 
	int pivo = dados[c].titulos;
	TimeFutebol PivoPrincipal = dados[c];
	int i = c+1, j = f;
	while (i <= j){
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

//Quick Sort utilizado para ordenar os titulos em ordem crescente.
void QuickSortTitulosCrescente(TimeFutebol *dados, int PosPivo, int fim){
	int PosNovoPivo;
	if (PosPivo < fim){
		PosNovoPivo = ParticionamentoTitulos_Crescente(dados, PosPivo, fim);
		QuickSortTitulosCrescente(dados, PosPivo, PosNovoPivo - 1); 
		QuickSortTitulosCrescente(dados, PosNovoPivo + 1, fim); 
	}
}

//Particionamento do Quick Sort utilizado para ordenar os titulos em ordem decrescente.
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

//Quick Sort utilizado para ordenar os titulos em ordem decrescente.
void QuickSortTitulosDecrescente(TimeFutebol *dados, int PosPivo, int fim){
	int PosNovoPivo;         
	if (PosPivo < fim) {  
		PosNovoPivo = ParticionamentoTitulos_Decrescente(dados, PosPivo, fim);
		QuickSortTitulosDecrescente(dados, PosPivo, PosNovoPivo - 1); 
		QuickSortTitulosDecrescente(dados, PosNovoPivo + 1, fim); 
	}
}

//Particionamento do Quick Sort utilizado para ordenar o nome dos clubes em ordem alfabética crescente.
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

//Quick Sort utilizado para ordenar o nome dos clubes em ordem alfabética crescente.
void QuickSortClubesCrescente(TimeFutebol *dados, int pos_pivo, int fim){
	int pos_novo_pivo;
	if (pos_pivo < fim) { 
		pos_novo_pivo = ParticionamentoClubes_Cresecente(dados, pos_pivo, fim);
		QuickSortClubesCrescente(dados, pos_pivo, pos_novo_pivo - 1); 
		QuickSortClubesCrescente(dados, pos_novo_pivo + 1, fim); 
	}
}

//Particionamento do Quick Sort utilizado para ordenar o nome dos clubes em ordem alfabética decrescente.
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

//Quick Sort utilizado para ordenar o nome dos clubes em ordem alfabética decrescente.
void QuickSortClubesDecrecente(TimeFutebol *dados, int PosPivo, int fim){
	int PosNovoPivo;
	if(PosPivo < fim){
		PosNovoPivo = ParticionamentoClubes_Decrescentes(dados, PosPivo, fim);
		QuickSortClubesDecrecente(dados, PosPivo, PosNovoPivo - 1);
		QuickSortClubesDecrecente(dados, PosNovoPivo + 1, fim);
	}
}

//Particionamento do Quick Sort utilizado para ordenar o ano de fundação em ordem crescente.
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

//Quick Sort utilizado para ordenar o ano de fundação em ordem crescente.
void QuickSortAnoCrescente(TimeFutebol *dados, int PosPivo, int fim){
	int PosNovoPivo;
	if (PosPivo < fim){
		PosNovoPivo = ParticionamentoAno_Crescente(dados, PosPivo, fim);
		QuickSortAnoCrescente(dados, PosPivo, PosNovoPivo - 1);
		QuickSortAnoCrescente(dados, PosNovoPivo + 1, fim);
	}
}

//Particionamento do Quick Sort utilizado para ordenar o ano de fundação em ordem decrescente.
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

//Quick Sort utilizado para ordenar o ano de fundação em ordem decrescente.
void QuickSortAnoDecrescente(TimeFutebol *dados, int PosPivo, int fim){
	int PosNovoPivo;
	if (PosPivo < fim){
		PosNovoPivo = ParticionamentoAno_Decrescente(dados, PosPivo, fim);
		QuickSortAnoDecrescente(dados, PosPivo, PosNovoPivo -1);
		QuickSortAnoDecrescente(dados, PosNovoPivo + 1, fim);
	}
}

//Particionamento do Quick Sort utilizado para ordenar a posição no ranking em ordem crescente.
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

//Quick Sort utilizado para ordenar a posição no ranking em ordem crescente.
void QuickSortPosicaoCrescente(TimeFutebol *dados, int PosPivo, int fim){
	int PosNovoPivo;
	if (PosPivo < fim){
		PosNovoPivo = ParticionamentoPosicao_Crescente(dados, PosPivo, fim);
		QuickSortPosicaoCrescente(dados, PosPivo, PosNovoPivo -1);
		QuickSortPosicaoCrescente(dados, PosNovoPivo + 1, fim);
	}
}

//Procedimento utlizado para fazer uma pesquisa no arquivo, a partir de uma posicao inicial até uma posicao final.
void PesquisarPosicao(TimeFutebol *dados, int NumRegistros, int PosicaoInicial, int PosicaoFinal){
	if(PosicaoInicial <= PosicaoFinal){
		if (PosicaoInicial < NumRegistros and PosicaoFinal <= NumRegistros){
			for (int i = PosicaoInicial; i < PosicaoFinal + 1; i++){
				cout << "--------------------------------" << endl
				<< "Posicao no Ranking: "<< dados[i].identificador << endl
				<< "Nome do Clube: " << dados[i].nome << endl
				<< "Cidade (Pais): " << dados[i].local << endl
				<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
				<< "Quantidade Total de Titulos: " << dados[i].titulos << endl 
				<< "--------------------------------" << endl << endl;
			}
		}
		if (PosicaoInicial > NumRegistros)
			cout << "A linha inicial selecionada excede o numero total de registros no banco de dados!" << endl;
		if (PosicaoFinal > NumRegistros)
			cout << "A linha final selecionada excede o numero total de registros no banco de dados!"<< endl;
	}
	else
		cout << "A linha inicial deve ser menor que a linha final!" << endl;
}

// Confirmar se as alterações devem ser salvas no arquivo binário.
void GravarArquivo(TimeFutebol *dados, int NumRegistros){
	int opcao;

	cout << "Deseja salvar as alteracoes no arquivo binario?" << endl;
	cout << "[1] Sim" << endl << "[2] Nao" << endl;
	cout << "Digite sua escolha: ";

	cin >> opcao;
	cout << endl;
	if (opcao == 1){
		for (int i = 0; i < NumRegistros; i++){
			salvarEmBinario(dados, NumRegistros);
		}
		cout << "As alteracoes foram salvas com sucesso!" << endl << endl;
	}
	else
	cout << "As Alteracoes nao foram salvas no arquivo!" << endl << endl;
}

//Algoritmo de inserção para adicionar um novo clube na última posição do banco de dados.
void NovoElemento(TimeFutebol* &dados, int &NumRegistros){
	TimeFutebol* aumentar = new TimeFutebol[NumRegistros + 1];

	for (int i = 0; i < NumRegistros; i++){
		aumentar[i] = dados[i];
	}

	cout << "Insira as informacoes do novo clube!" << endl;
	cout << "Posicao no Ranking: " << NumRegistros + 1 << endl;
	aumentar[NumRegistros].identificador = NumRegistros + 1;
	cout << "Nome do Clube: ";
	cin.ignore();
	cin.getline(aumentar[NumRegistros].nome, 40);
	cout << "Cidade (Pais): ";
	cin.getline(aumentar[NumRegistros].local, 40);
	cout << "Ano de Fundacao: ";
	cin >> aumentar[NumRegistros].anoFundacao;
	cout << "Quantidade Total de Titulos: ";
	cin >> aumentar[NumRegistros].titulos;

	delete[] dados;
	dados = aumentar;
	NumRegistros++;

	GravarArquivo(dados, NumRegistros);

	cout << "Novo clube adicionado e arquivo binario atualizado!" << endl;
}

//Remover um clube de um vetor de acordo com sua posição no ranking.
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
		else
			j++;
	}

	if(encontrado){
		for (int i = j; i < NumRegistros; i++){
            dados[i].identificador--;  
        }
		GravarArquivo(dados, NumRegistros);
	}

	if (!encontrado){
		cout << "A posicao buscada nao foi encontrada!" << endl;
	}
}

void ExportarCSV(TimeFutebol *dados, int NumRegistros){
	ofstream arquivo("TimesFutebol.csv");
    for (int i = 0; i < NumRegistros; ++i){
        arquivo << dados[i].identificador << ',';
        arquivo << dados[i].nome << ',';
        arquivo << dados[i].local << ',';
        arquivo << dados[i].anoFundacao << ',';
        arquivo << dados[i].titulos << endl;
    }
    cout << "Arquivo exportado com sucesso!" << endl << endl;
}

int main(){
	int NumRegistros = 0, Capacidade = 40;
	int EscolherArquivo, escolha1, escolha2, escolha3, PosicaoInicial, PosicaoFinal;
	bool Repetir = true;

	cout << "[1] Converter a leitura do arquivo CSV para o formato binario." << endl;
	cout << "[2] Acessar arquivo binario." << endl;
	cout << "Digite um valor: ";
	cin >> EscolherArquivo;
	cout << endl;
	if (EscolherArquivo == 1){
		ifstream Arquivo("TimesFutebol.csv");
		if (not (Arquivo)) {
			cout << "Erro ao abrir o arquivo CSV!" << endl;
			return 0;
		}
		else{
		TimeFutebol* dados1 = leituraArquivo(Arquivo, NumRegistros, Capacidade);
		salvarEmBinario(dados1, NumRegistros);
		delete[] dados1;
		Arquivo.close();
		cout << "O arquivo binario foi criado!" << endl;
		}
	}
	
	if (EscolherArquivo == 2){
		ifstream binario("times.bin", ios::binary);
		if (not (binario)) {
			cout << "Erro ao abrir o arquivo binario!" << endl;
			return 0;
		}
		TimeFutebol* dados2 = leituraBinario(binario, NumRegistros, Capacidade);
		binario.close();

		while (Repetir) {
			cout << "Escolha uma das opcoes disponiveis:" << endl
			<< "[1] Buscar um clube" << endl
			<< "[2] Ordenar a lista de clubes" << endl
			<< "[3] Pesquisar por linha" << endl
			<< "[4] Adicionar um clube" << endl
			<< "[5] Remover um clube" << endl
			<< "[6] Visualizar o arquivo binario" << endl
			<< "[7] Exportar arquivo para CSV" << endl
			<< "[-1] Sair do programa" << endl;
			cout << "Digite sua escolha: ";
			cin >> escolha1;
			cout << endl;
			switch (escolha1) {
				// O caso 1 faz a busca de um elemento no arquivo.
				case 1:
				cout << "[1] Buscar clube por ranking" << endl
				<< "[2] Buscar clube por nome" << endl;
				cout << "Digite sua escolha: ";
				cin >> escolha2;
				cout << endl;
				switch (escolha2) {
					case 1:
						QuickSortPosicaoCrescente(dados2, 0, NumRegistros - 1);
						BuscaRanking(dados2, 0, NumRegistros - 1, NumRegistros);
						break;
					case 2:
						QuickSortClubesCrescente(dados2, 0, NumRegistros - 1);
						BuscaNomeClube(dados2, 0, NumRegistros - 1);
						break;
					default:
						cout << "Escolha Invalida!" << endl << endl;
						break;
					}
				break;

				// O caso 2 faz a ordenação em um arquivo binário.
				case 2:
				cout << "Escolha o campo que deseja ordenar:" << endl
				<< "[1] Posicao no ranking" << endl
				<< "[2] Nome do clube" << endl
			 	<< "[3] Ano de fundacao" << endl
				<< "[4] Numero de titulos" << endl;
				cout << "Digite sua escolha: ";
				cin >> escolha2;
				cout << endl;
				switch (escolha2) {
					case 1:
						QuickSortPosicaoCrescente(dados2, 0, NumRegistros -1);
						GravarArquivo(dados2, NumRegistros);
						break;
					case 2:
						cout << "Como deseja ordenar?" << endl
						<< "[1] Ordem alfabetica crescente" << endl
						<< "[2] Ordem alfabetica decrescente" << endl;
						cout << "Digite sua escolha: ";
						cin >> escolha3;
						cout << endl;
						switch (escolha3) {
							case 1:
								QuickSortClubesCrescente(dados2, 0, NumRegistros - 1);
								GravarArquivo(dados2, NumRegistros);
								break;
							case 2:
								QuickSortClubesDecrecente(dados2, 0, NumRegistros - 1);
								GravarArquivo(dados2, NumRegistros);
								break;
							default:
								cout << "Escolha Invalida!" << endl << endl;
								break;
							}
						break;

					case 3:
						cout << "Como deseja ordenar?" << endl
						<< "[1] Crescente" << endl 
						<< "[2] Decrescente" << endl;
						cout << "Digite sua escolha: ";
						cin >> escolha3;
						cout << endl;
						switch (escolha3){
							case 1:
								QuickSortAnoCrescente(dados2, 0, NumRegistros - 1);
								GravarArquivo(dados2, NumRegistros);
								break;
							case 2:
								QuickSortAnoDecrescente(dados2, 0, NumRegistros - 1);
								GravarArquivo(dados2, NumRegistros);
								break;
							default:
								cout << "Escolha Invalida!" << endl << endl;
								break;
						}
						break;

					case 4:
						cout << "Como deseja ordenar?" << endl
						<< "[1] Crescente" << endl
						<< "[2] Decrescente" << endl;
						cout << "Digite um valor: ";
						cin >> escolha3;
						cout << endl;
						switch (escolha3) {
							case 1:
								QuickSortTitulosCrescente(dados2, 0, NumRegistros - 1);
								GravarArquivo(dados2, NumRegistros);
								break;
							case 2:
								QuickSortTitulosDecrescente(dados2, 0, NumRegistros - 1);
								GravarArquivo(dados2, NumRegistros);
								break;
							default:
								cout << "Escolha Invalida!" << endl << endl;
								break;
						}
						break;
					default:
						cout << "Escolha Invalida!" << endl << endl;
						break;
				}
				break;

				//O caso 3 lê de o arquivo a partir de uma linha inicial até uma linha final.
				case 3:
				cout << "O vetor vai da posicao 0 ate a posicao " << NumRegistros - 1 << "." << endl;
				cout << "Digite a posicao inicial: ";
				cin >> PosicaoInicial;
				cout << "Digite a posicao final: ";
				cin >> PosicaoFinal;
				cout << endl;
				PesquisarPosicao(dados2, NumRegistros, PosicaoInicial, PosicaoFinal);
				break;

				//O caso 4 faz a inserção de um novo clube no arquivo.
				case 4:
				QuickSortPosicaoCrescente(dados2, 0, NumRegistros - 1);
				NovoElemento(dados2, NumRegistros);
				break;

				//O caso 5 faz a remoção de um clube do arquivo.
				case 5:
				int RankingProcurado;
				cout << "Digite a posicao do clube que deseja remover: ";
				cin >> RankingProcurado;
				cout << endl;
				QuickSortPosicaoCrescente(dados2, 0, NumRegistros - 1);
				ExcluirElemento(dados2, NumRegistros, RankingProcurado);
				break;

				//O caso 6 serve para mostrar o arquivo binário com as alterações feitas.
				case 6:
				MostrarArquivo(dados2, NumRegistros);
				break;
				
				case 7:
				ExportarCSV(dados2, NumRegistros);
				break;

				//Sair do programa.
				case -1:
				cout << "Operacao concluida. Obrigado por usar o programa!" << endl;
				Repetir = false;
				break;

				default:
				cout << "Escolha invalida!" << endl;
				break;
			}
		}
		delete[] dados2;
	}
	return 0;
}
