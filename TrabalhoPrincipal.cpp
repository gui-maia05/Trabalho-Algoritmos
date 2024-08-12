#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

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
		for (int i = 0; i < NumRegistros; i++){
			if (dados[i].identificador == Ranking){
				cout << "Posicao no Ranking: "<< dados[i].identificador << endl
				<< "Time: " << dados[i].nome << endl
				<< "Cidade (Pais): " << dados[i].local << endl
				<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
				<< "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
			}
		}
		break;
	
		case 2:
		cout << "Digite o nome do clube: ";
		getline(cin, NomeTime);
		for (int i = 0; i < NumRegistros; i++){
			if (dados[i].nome == NomeTime){
				cout << "Posicao no Ranking: "<< dados[i].identificador << endl
				<< "Time: " << dados[i].nome << endl
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

void LimparTela(){
    #if defined(_WIN32) or defined(_WIN64)
        system("cls");   // Comando para Windows
    #else
        system("clear"); // Comando para Linux/Unix/macOS
    #endif
}

int main(){
	string linha;
	int NumRegistros;
	
	ifstream entrada("TimesFutebol.csv");
	if (not(entrada)){
		cout << " Nao foi possivel acessar o arquivo! " << endl;
	}
	else{
		getline(entrada, linha); //descarta a  primeira linha do arquivo
		entrada >> NumRegistros;
		entrada.ignore();//pula o fim de linha
	}
	
	TimeFutebol* dados;
	dados = leituraArquivo(entrada, NumRegistros);

	int entrada1, entrada2;
	
	bool Repetir = true;
	while(Repetir){
		cout << "Escolha uma das Opcoes Disponiveis:" << endl
		<< "[1] Realizar uma busca" << endl
		<< "[2] Ordenar o vetor" << endl
		<< "[3] Ver Banco de dados" << endl
		<< "[-1] Sair do programa" << endl;
		cout << "Digite um valor: ";
		cin >> entrada1;

		switch (entrada1){
			case 1:
			LimparTela();
			BuscaRanking_Time(dados, NumRegistros);
			break;
			
			case 2:
			cout << "Voce deseja ordenar em qual ordem?" << endl
			<< "[1] Crescente" << endl << "[2] Decrescente" << endl
			<< "Digite um valor: ";
			cin >> entrada2;
			switch (entrada2){
				case 1:
				LimparTela();
				ParticionamentoTitulos_Crescente(dados, 0, NumRegistros-1);
				QuickSortTitulosCrescente(dados, 0, NumRegistros - 1);
				for (int i = 0; i < NumRegistros; i++){
					cout << "Posicao no Ranking: "<< dados[i].identificador << endl
					<< "Time: " << dados[i].nome << endl
					<< "Cidade (Pais): " << dados[i].local << endl
					<< "Ano de Fundacao: " << dados[i].anoFundacao << endl
					<< "Quantidade Total de Titulos: " << dados[i].titulos << endl << endl;
				}
				break;
				
				case 2:
				LimparTela();
				ParticionamentoTitulos_Decrescente(dados, 0, NumRegistros-1);
				QuickSortTitulosDecrescente(dados, 0, NumRegistros - 1);
				for (int i = 0; i < NumRegistros; i++){
					cout << "Posicao no Ranking: "<< dados[i].identificador << endl
					<< "Time: " << dados[i].nome << endl
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
			LimparTela();
			leituraArquivo(entrada, NumRegistros);
			break;
			
			case -1:
			LimparTela();
			cout << "Obrigado por testar!" << endl;
			Repetir = false;
			break;
		}
	}

	delete [] dados;
	entrada.close();
return 0;
}
