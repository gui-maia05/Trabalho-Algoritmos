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

void CriarNovoArquivo(TimeFutebol dados[], int NumRegistros){
	ofstream Arquivo_saida("saida.csv");
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


void BuscaRanking_Time(TimeFutebol dados[], int NumRegistros){
	int entrada, Ranking;
	string NomeTime;

	cout << "[1] Realizar uma busca pelo ranking dos clubes" << endl
	<< "[2] Realizar uma busca pelo nome do clube" << endl;
	cout << "Digite um valor: ";
	cin >> entrada;
	cin.ignore();
	switch (entrada){
		case 1:
		cout << "Digite a posicao no Ranking(1-100): ";
		cin >> Ranking;
		cout << endl;
		for (int i = 0; i < NumRegistros; i++){
			if (dados[i].identificador == Ranking){
				cout << "Posicao no Ranking: "<< dados[i].identificador << endl
				<< "Nome do Clube: " << dados[i].nome << endl
				<< "Cidade (Pais): " << dados[i].local << endl
				<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
				<< "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
			}
		}
		break;
	
		case 2:
		cout << "Digite o nome do clube: ";
		getline(cin, NomeTime);
		cout << endl;
		for (int i = 0; i < NumRegistros; i++){
			if (dados[i].nome == NomeTime){
				cout << "Posicao no Ranking: "<< dados[i].identificador << endl
				<< "Nome do Clube: " << dados[i].nome << endl
				<< "Cidade (Pais): " << dados[i].local << endl
				<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
				<< "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
			}
		}
		break;

		default:
		cout << "Opcao Invalida!" << endl;
	}
}


int ParticionamentoTitulos_Crescente(TimeFutebol dados[], int c, int f) { 
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

void QuickSortTitulosCrescente(TimeFutebol dados[], int PosPivo, int fim) {
   int PosNovoPivo;         
   if (PosPivo < fim) {  
      PosNovoPivo = ParticionamentoTitulos_Crescente(dados, PosPivo, fim);
      QuickSortTitulosCrescente(dados, PosPivo, PosNovoPivo - 1); 
      QuickSortTitulosCrescente(dados, PosNovoPivo + 1, fim); 
   }
}

int ParticionamentoTitulos_Decrescente(TimeFutebol dados[], int c, int f) { 
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

void QuickSortTitulosDecrescente(TimeFutebol dados[], int PosPivo, int fim) {
   int PosNovoPivo;         
   if (PosPivo < fim) {  
      PosNovoPivo = ParticionamentoTitulos_Decrescente(dados, PosPivo, fim);
      QuickSortTitulosDecrescente(dados, PosPivo, PosNovoPivo - 1); 
      QuickSortTitulosDecrescente(dados, PosNovoPivo + 1, fim); 
   }
}

int ParticionamentoLocais_Cresecente(TimeFutebol dados[], int c, int f){ 
   string pivo = dados[c].local;
   TimeFutebol PivoPrincipal = dados[c];
   int i = c+1, j = f;
   while (i <= j) {
       if (dados[i].local <= pivo) i++;
       else if (pivo <= dados[j].local) j--; 
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

void QuickSortLocaisCrescente(TimeFutebol dados[], int pos_pivo, int fim){
   int pos_novo_pivo;         
   if (pos_pivo < fim) {  
      pos_novo_pivo = ParticionamentoLocais_Cresecente(dados, pos_pivo, fim);
      QuickSortLocaisCrescente(dados, pos_pivo, pos_novo_pivo - 1); 
      QuickSortLocaisCrescente(dados, pos_novo_pivo + 1, fim); 
   }
}

int ParticionamentoLocais_Decrescentes(TimeFutebol dados[], int c, int f){
	string pivo = dados[c].local;
	TimeFutebol PivoPrincipal = dados[c];
	int i = c+1, j = f;
	while(i <= j){
		if (dados[i].local >= pivo) i++;
		else if(pivo >= dados[i].local) j--;
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

void QuickSortLocaisDecrecente(TimeFutebol dados[], int PosPivo, int fim){
	int PosNovoPivo;
	if(PosPivo < fim){
		PosNovoPivo = ParticionamentoLocais_Decrescentes(dados, PosPivo, fim);
		QuickSortLocaisDecrecente(dados, PosPivo, PosNovoPivo - 1);
		QuickSortLocaisDecrecente(dados, PosNovoPivo + 1, fim);
	}
}

void MostrarArquivo(TimeFutebol dados[], int NumRegistros){
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

	int entrada1, entrada2;
	bool Repetir = true;

	while(Repetir){
		cout << "Escolha uma das Opcoes Disponiveis:" << endl
		<< "[1] Realizar uma busca" << endl
		<< "[2] Ordenar o vetor por titulos" << endl
		<< "[3] Ordenar o vetor pelas cidades" << endl
		<< "[4] Ver Banco de dados" << endl
		<< "[-1] Sair do programa" << endl;
		cout << "Digite um valor: ";
		cin >> entrada1;

		switch (entrada1){
			case 1:
			BuscaRanking_Time(dados, NumRegistros);
			break;
			
			case 2:
			cout << "Voce deseja ordenar em qual ordem?" << endl
			<< "[1] Crescente" << endl << "[2] Decrescente" << endl
			<< "Digite um valor: ";
			cin >> entrada2;
			switch (entrada2){
				case 1:
				ParticionamentoTitulos_Crescente(dados, 0, NumRegistros-1);
				QuickSortTitulosCrescente(dados, 0, NumRegistros - 1);
				for (int i = 0; i < NumRegistros; i++){
					cout << "Posicao no Ranking: "<< dados[i].identificador << endl
					<< "Nome do Clube: " << dados[i].nome << endl
					<< "Cidade (Pais): " << dados[i].local << endl
					<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
					<< "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
				}
				break;
				
				case 2:
				ParticionamentoTitulos_Decrescente(dados, 0, NumRegistros-1);
				QuickSortTitulosDecrescente(dados, 0, NumRegistros -1);
				for (int i = 0; i < NumRegistros; i++){
					cout << "Posicao no Ranking: "<< dados[i].identificador << endl
					<< "Nome do Clube: " << dados[i].nome << endl
					<< "Cidade (Pais): " << dados[i].local << endl
					<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
					<< "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
				}
				break;
				
				default:
				cout << "Opcao Invalida!" << endl;
				}
			break;

			case 3:
			cout << "Voce deseja organizar o vetor em qual ordem?" 
			<< endl << "[1] Crescente" 
			<< endl << "[2] Decresente"
			<< endl << "Digite um valor: ";
			cin >> entrada2;
			switch(entrada2){
				case 1:
				ParticionamentoLocais_Cresecente(dados, 0, NumRegistros -1);
				QuickSortLocaisCrescente(dados, 0, NumRegistros -1);
				for(int i = 0; i < NumRegistros; i++){
				cout << "Posicao no Ranking: "<< dados[i].identificador << endl
					<< "Nome do Clube: " << dados[i].nome << endl
					<< "Cidade (Pais): " << dados[i].local << endl
					<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
					<< "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
				}
				break;

				case 2:
				ParticionamentoLocais_Decrescentes(dados, 0, NumRegistros -1);
				QuickSortLocaisDecrecente(dados, 0, NumRegistros -1);
				for (int i = 0; i < NumRegistros; i++){
					cout << "Posicao no Ranking: "<< dados[i].identificador << endl
					<< "Nome do Clube: " << dados[i].nome << endl
					<< "Cidade (Pais): " << dados[i].local << endl
					<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
					<< "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
				}
				break;
			}
			break;

			case 4:
			MostrarArquivo(dados, NumRegistros);
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
