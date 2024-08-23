#include <iostream>
#include <fstream>
using namespace std;

//Estrutura utilizada no código.
struct TimeFutebol{
	short identificador;
	char nome[40];
	char local[40];
	int anoFundacao;
	int titulos;
};

//Salvar os dados em um arquivo binário.
void salvarEmBinario(TimeFutebol *dados, int NumRegistros) {
	ofstream arquivoBinario("times.bin", ios::binary);
	arquivoBinario.write((char*)dados, sizeof(TimeFutebol) * NumRegistros);
	arquivoBinario.close();
	cout << "Dados salvos em arquivo binario com sucesso!" << endl << endl;
}

//Leitura do arquivo csv, usando redimensionamento.
TimeFutebol* leituraArquivo(ifstream &arquivo_csv, int &NumRegistros, int &Capacidade){
	char lixo;
	TimeFutebol* dados = new TimeFutebol[NumRegistros];
	int i = 0;

	while(i < NumRegistros){
		if (Capacidade == i){
			Capacidade += 5;

			TimeFutebol* novos_dados = new TimeFutebol[Capacidade];

			for (int j = 0; j < i; j++){
				novos_dados[j] = dados[j];
			}
			delete [] dados;
			dados = novos_dados;
		}	
		arquivo_csv >> dados[i].identificador;
		arquivo_csv >> lixo;
		arquivo_csv.getline(dados[i].nome, 40, ',');
		arquivo_csv.getline(dados[i].local, 40, ',');
		arquivo_csv >> dados[i].anoFundacao;
		arquivo_csv >> lixo;
		arquivo_csv >> dados[i].titulos;
		arquivo_csv.ignore(); // Pula o fim de linha

		i++;
	}
	return dados;
}

//Procedimento utilizado para imprimir o arquivo csv.
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

//Algoritmo de busca binária aplicado para encontrar um clube específico pelo seu ranking.
void BuscaRanking(TimeFutebol *dados, int PosInicial, int PosFinal, int NumRegistros){
	int meio;
	int Ranking;
	bool encontrado = false;
	cout << "Digite a posicao no Ranking(1-" << NumRegistros << "): ";
	cin >> Ranking;
	cout << endl;

	while (PosInicial <= PosFinal and !encontrado){
		meio = (PosFinal + PosInicial)/2;
		if(Ranking == dados[meio].identificador){
			cout << "Aqui estão as informações do clube na posição " << Ranking << " do ranking!" << endl;  
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
	cout << "Nenhum clube foi encontrado na posicao " << Ranking <<  "!" << endl << endl;
}

//Algoritmo de busca binária aplicado para encontrar um clube específico pelo seu nome.
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
			cout << "Aqui estão as informações do clube!" << endl;  
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
	cout << "O clube " << NomeClube << " nao esta no banco de dados!" << endl << endl;
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

//Procedimento utlizado para fazer uma pesquisa no vetor, a partir de uma linha inicial até uma linha final.
void PesquisarPosicao(TimeFutebol *dados, int NumRegistros, int PosicaoInicial, int PosicaoFinal){
	if(PosicaoInicial <= PosicaoFinal){
		if (PosicaoInicial < NumRegistros and PosicaoFinal <= NumRegistros){
			for (int i = PosicaoInicial - 1; i < PosicaoFinal; i++){
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
			cout << "A linha incial escolhida e maior que o numero de registros!" << endl;
		if (PosicaoFinal > NumRegistros)
			cout << "A linha final escolhida e maior que o numero de registros!" << endl;
	}
	else
		cout << "A linha inicial deve ser menor que a linha final!" << endl;
}

//Confirmar a gravação das alterações em um arquivo.
void GravarArquivo(TimeFutebol *dados, int NumRegistros){
	int opcao;

	cout << endl << "Gostaria de gravar as alteracoes no arquivo csv e no arquivo binario?" << endl
	<< "[1] Sim" << endl << "[2] Nao" << endl;
	cout << "Digite um valor: ";

	cin >> opcao;
	cout << endl;
	if (opcao == 1){
		salvarEmBinario(dados, NumRegistros);
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
		cout << "As alteracoes foram gravadas com sucesso!" << endl << endl;
	}
	else
	cout << "As alteracoes nao foram gravadas em nenhum arquivo!" << endl << endl;
}

//Algoritmo de inserção em um vetor para adicionar um novo clube em uma posição específica.
void NovoElemento(TimeFutebol* &dados, int &NumRegistros){
	int Ranking;
	TimeFutebol* aumentar = new TimeFutebol[NumRegistros + 1];

	for (int i = 0; i < NumRegistros; i++){
		aumentar[i] = dados[i];
	}

	cout << "Insira as informacoes do novo clube!" << endl;
	cout << "Posicao no Ranking: ";
	cin >> Ranking;
	aumentar[NumRegistros].identificador = Ranking - 1;
	cout << "Nome do Clube: ";
	cin.ignore();
	cin.getline(aumentar[NumRegistros].nome, 40);
	cout << "Cidade (Pais): ";
	cin.getline(aumentar[NumRegistros].local, 40);
	cout << "Ano de Fundacao: ";
	cin >> aumentar[NumRegistros].anoFundacao;
	cout << "Quantidade Total de Titulos: ";
	cin >> aumentar[NumRegistros].titulos;

	int posicao = NumRegistros;

	while (posicao > 0 and aumentar[posicao].identificador < aumentar[posicao - 1].identificador){
		swap(aumentar[posicao], aumentar[posicao -1]);
		posicao--;
	}

	delete[] dados;
	dados = aumentar;
	NumRegistros++;

	GravarArquivo(dados, NumRegistros);
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
		j++;
	}

	if (!encontrado){
		cout << "Não foi encontrada a posicao no arquivo!" << endl;
	}

	if(encontrado){
		GravarArquivo(dados, NumRegistros);
	}
}

int main(){
	string linha;
	int NumRegistros, Capacidade = 40;
	int escolha1, escolha2, escolha3, PosicaoInicial, PosicaoFinal;
	bool Repetir = true;

	ifstream Arquivo("TimesFutebol.csv");
	if (not(Arquivo)){
		cout << "Nao foi possivel acessar o arquivo! " << endl;
	}
	else{
		getline(Arquivo, linha); //Descarta a  primeira linha do arquivo
		Arquivo >> NumRegistros;
		Arquivo.ignore();//Pula o fim de linha
	}

	TimeFutebol* dados;
	dados = leituraArquivo(Arquivo, NumRegistros, Capacidade);

	if(Arquivo){
		salvarEmBinario(dados, NumRegistros);
		while(Repetir){ //Interface do programa.
			cout << "Escolha uma das Opcoes Disponiveis:" << endl
			<< "[1] Realizar uma Busca" << endl
			<< "[2] Ordenar o Vetor" << endl
			<< "[3] Ver o Arquivo" << endl
			<< "[4] Adicionar um novo Clube" << endl
			<< "[5] Excluir um Clube" << endl
			<< "[-1] Sair do programa" << endl;
			cout << "Digite um valor: ";
			cin >> escolha1;
			cout << endl;
			switch (escolha1){

				case 1: //Chama a busca binária.
					cout << "[1] Realizar uma busca pelo ranking dos clubes " << endl
					<< "[2] Realizar uma busca pelo nome do clube" << endl << endl;
					cout << "Digite um valor: ";
					cin >> escolha2;
					cout << endl;
					switch (escolha2){
						case 1:
						QuickSortPosicaoCrescente(dados, 0, NumRegistros-1);
						BuscaRanking(dados, 0, NumRegistros -1, NumRegistros);
						break;

						case 2:
						QuickSortClubesCrescente(dados, 0, NumRegistros -1);
						BuscaNomeClube(dados, 0, NumRegistros -1);
						break;
						
						default:
						cout << "Opcao Invalida!" << endl << endl;
						break;
					}
				break;

				case 2: //Chama os métodos de ordenação.
					cout << "Escolha um dos campos que deseja ordenar:" << endl
					<< "[1] Nome do Clube" << endl
					<< "[2] Ano de Fundacao" << endl
					<< "[3] Numero de Titulos" << endl;
					cout << "Digite um valor: ";
					cin >> escolha2;
					cout << endl;
					switch (escolha2){
						case 1: //Escolhe se o metodo de ordenação sera em ordem crescente ou decrescente.
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

							default:
							cout << "Opcao Invalida!" << endl << endl;
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

							default:
							cout << "Opcao Invalida!" << endl << endl;
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

						default:
						cout << "Opcao Invalida!" << endl << endl;
						break;
					}
				break;

				case 3: //Ver o arquivo completo ou pesquisar a partir de uma posição inicial até uma final.
					cout << "[1] Ver arquivo completo" << endl
					<< "[2] Pesquisar a partir de uma posicao inicial ate uma posicao final no vetor" << endl;
					cout << "Digite um valor: ";
					cin >> escolha2;
					cout << endl;
					switch (escolha2){
						case 1:
						QuickSortPosicaoCrescente(dados, 0, NumRegistros -1);
						MostrarArquivo(dados, NumRegistros);
						break;

						case 2:
						cout << "O vetor comeca na posicao 0 e vai até a posicao " << NumRegistros << "!" << endl;
						cout << "Digite a posicao inicial: ";
						cin >> PosicaoInicial;
						cout << "Digite a posicao final: ";
						cin >> PosicaoFinal;
						cout << endl;
						QuickSortPosicaoCrescente(dados, 0, NumRegistros-1);
						PesquisarPosicao(dados, NumRegistros, PosicaoInicial, PosicaoFinal);
						break;

						default:
						cout << "Opcao Invalida!" << endl << endl;
						break;
					}
				break;

				case 4: //Chama o procedimento de inserção de um novo clube.
					QuickSortPosicaoCrescente(dados, 0, NumRegistros -1);
					NovoElemento(dados, NumRegistros);
					Repetir = false;
					break;
				
				case 5: //Chama o procedimento de exclusão de um clube.
					int RankingProcurado;
					cout << "Digite a posicao que deseja excluir: ";
					cin >> RankingProcurado;
					cout << endl;
					QuickSortPosicaoCrescente(dados, 0, NumRegistros -1);
					ExcluirElemento(dados, NumRegistros, RankingProcurado);
					Repetir = false;
					break;

				case -1: //Sair do programa.
					cout << "Obrigado por testar, volte sempre!" << endl;
					Repetir = false;
					break;

				default:
					cout << "Opcao Invalida!" << endl << endl;
					break;
			}
		}
	}

	delete [] dados;
	Arquivo.close();
	return 0;
}




































#include <iostream>
#include <fstream>
using namespace std;

//Estrutura utilizada no código.
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

//Salvar os dados em um arquivo binário.
void salvarEmBinario(TimeFutebol *dados, int &NumRegistros) {
	ofstream arquivoBinario("times.bin", ios::binary);
	arquivoBinario.write((char*)dados, sizeof(TimeFutebol) * NumRegistros);
	arquivoBinario.close();
}

TimeFutebol* leituraBinario(ifstream &arquivo_bin, int &NumRegistros, int &capacidade){
	TimeFutebol* dados = new TimeFutebol[capacidade];
	TimeFutebol aux;
	int i =0;
	while (arquivo_bin.read((char *)(&aux),sizeof(TimeFutebol))){
		if(i == capacidade){
			capacidade += 10;
			TimeFutebol* novo = new TimeFutebol[capacidade];
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

//Procedimento utilizado para imprimir o arquivo csv.
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

//Algoritmo de busca binária aplicado para encontrar um clube específico pelo seu ranking.
void BuscaRanking(TimeFutebol *dados, int PosInicial, int PosFinal, int NumRegistros){
	int meio;
	int Ranking;
	bool encontrado = false;
	cout << "Digite a posicao no Ranking(1-" << NumRegistros << "): ";
	cin >> Ranking;
	cout << endl;

	while (PosInicial <= PosFinal and !encontrado){
		meio = (PosFinal + PosInicial)/2;
		if(Ranking == dados[meio].identificador){
			cout << "Aqui estão as informações do clube na posição " << Ranking << " do ranking!" << endl;  
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
	cout << "Nenhum clube foi encontrado na posicao " << Ranking <<  "!" << endl << endl;
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
			cout << "Aqui estão as informações do clube!" << endl;  
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
	cout << "O clube " << NomeClube << " nao esta no banco de dados!" << endl << endl;
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

//Procedimento utlizado para fazer uma pesquisa no vetor, a partir de uma linha inicial até uma linha final.
void PesquisarPosicao(TimeFutebol *dados, int NumRegistros, int PosicaoInicial, int PosicaoFinal){
	if(PosicaoInicial <= PosicaoFinal){
		if (PosicaoInicial < NumRegistros and PosicaoFinal <= NumRegistros){
			for (int i = PosicaoInicial - 1; i < PosicaoFinal; i++){
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
			cout << "A linha incial escolhida e maior que o numero de registros!" << endl;
		if (PosicaoFinal > NumRegistros)
			cout << "A linha final escolhida e maior que o numero de registros!" << endl;
	}
	else
		cout << "A linha inicial deve ser menor que a linha final!" << endl;
}

//Confirmar a gravação das alterações em um arquivo.
void GravarArquivo(TimeFutebol *dados, int NumRegistros){
	int opcao;

	cout << "Gostaria de gravar as alteracoes no arquivo binario?" << endl
	<< "[1] Sim" << endl << "[2] Nao" << endl;
	cout << "Digite um valor: ";

	cin >> opcao;
	cout << endl;
	if (opcao == 1){
		for (int i = 0; i < NumRegistros; i++){
			salvarEmBinario(dados, NumRegistros);
		}
		cout << "As alteracoes foram gravadas com sucesso!" << endl << endl;
	}
	else
	cout << "As alteracoes nao foram gravadas em nenhum arquivo!" << endl << endl;
}

//Algoritmo de inserção em um vetor para adicionar um novo clube em uma posição específica.
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

	int posicao = NumRegistros;

	while (posicao > 0 and aumentar[posicao].identificador < aumentar[posicao - 1].identificador){
		swap(aumentar[posicao], aumentar[posicao -1]);
		posicao--;
	}

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
		j++;
	}

	if (!encontrado){
		cout << "Não foi encontrada a posicao no arquivo!" << endl;
	}

	if(encontrado){
		GravarArquivo(dados, NumRegistros);
	}
}

int main(){
	int NumRegistros = 0, Capacidade = 40;
	int escolha, escolha1, escolha2, escolha3, PosicaoInicial, PosicaoFinal;
	bool Repetir = true;

    cout << "[1] Converter a leitura do arquivo CSV para o formato binario." << endl;
    cout << "[2] Acessar arquivo binario." << endl;
    cout << "Digite um valor: ";
    cin >> escolha;
	cout << endl;
	
	if (escolha == 1){
		ifstream Arquivo("TimesFutebol.csv");
		if (!Arquivo.is_open()) {
			cout << "Erro ao abrir o arquivo CSV!" << endl;
			return 1;
		}
		TimeFutebol* dados1 = leituraArquivo(Arquivo, NumRegistros, Capacidade);
		salvarEmBinario(dados1, NumRegistros);
		delete[] dados1;
		Arquivo.close();
		cout << "O arquivo binario foi criado!" << endl;
	}
	
	if (escolha == 2){
		ifstream binario("times.bin", ios::binary);
		if (!binario.is_open()) {
			cout << "Erro ao abrir o arquivo binario!" << endl;
			return 1;
		}
		TimeFutebol* dados2 = leituraBinario(binario, NumRegistros, Capacidade);
		binario.close();

		while (Repetir) {
			cout << "Escolha uma das Opcoes Disponiveis:" << endl
			<< "[1] Realizar uma Busca" << endl
			<< "[2] Ordenar o Vetor" << endl
			<< "[3] Pesquisar por Linhas" << endl
			<< "[4] Adicionar um novo Clube" << endl
			<< "[5] Excluir um Clube" << endl
			<< "[6] Ver o Arquivo Binario" << endl
			<< "[-1] Sair do Programa" << endl;
			cout << "Digite um valor: ";
			cin >> escolha1;
			cout << endl;
			switch (escolha1) {
				case 1:
				cout << "[1] Realizar uma busca pelo ranking dos clubes" << endl
				<< "[2] Realizar uma busca pelo nome do clube" << endl << endl;
				cout << "Digite um valor: ";
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

					case 2:
						cout << "Escolha um dos campos que deseja ordenar:" << endl
						<< "[1] Nome do Clube" << endl
						<< "[2] Ano de Fundacao" << endl
						<< "[3] Numero de Titulos" << endl;
						cout << "Digite um valor: ";
						cin >> escolha2;
						cout << endl;
						switch (escolha2) {
							case 1:
								cout << "Como deseja ordenar?" << endl
								<< "[1] Ordem Alfabética Crescente" << endl
								<< "[2] Ordem Alfabética Decrescente" << endl;
								cout << "Digite um valor: ";
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

							case 2:
								cout << "Como deseja ordenar?" << endl
								<< "[1] Crescente" << endl 
								<< "[2] Decrescente" << endl;
								cout << "Digite um valor: ";
								cin >> escolha3;
								cout << endl;
								switch (escolha3) {
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

							case 3:
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

					case 3:
						cout << "O vetor começa na posição 0 e vai ate a posicao " << NumRegistros - 1 << "!" << endl;
						cout << "Digite a posição inicial: ";
						cin >> PosicaoInicial;
						cout << "Digite a posição final: ";
						cin >> PosicaoFinal;
						cout << endl;
						QuickSortPosicaoCrescente(dados2, 0, NumRegistros - 1);
						PesquisarPosicao(dados2, NumRegistros, PosicaoInicial, PosicaoFinal);
						break;

					case 4:
						QuickSortPosicaoCrescente(dados2, 0, NumRegistros - 1);
						NovoElemento(dados2, NumRegistros);
						Repetir = false;
						break;

					case 5:
						int RankingProcurado;
						cout << "Digite a posição que deseja excluir: ";
						cin >> RankingProcurado;
						cout << endl;
						QuickSortPosicaoCrescente(dados2, 0, NumRegistros - 1);
						ExcluirElemento(dados2, NumRegistros, RankingProcurado);
						Repetir = false;
						break;

					case 6:
						MostrarArquivo(dados2, NumRegistros);
						break;

					case -1:
						cout << "Obrigado por testar, volte sempre!" << endl;
						Repetir = false;
						break;

					default:
						cout << "Escolha invalida!" << endl;
						break;
				}
			}
		delete[] dados2;
	}
	else
	cout << "Escolha Invalida!" << endl;




	return 0;
}
