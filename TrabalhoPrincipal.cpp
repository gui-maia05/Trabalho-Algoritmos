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
				cout << "Posicao no Ranking de clubes: "<< dados[i].identificador << endl
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
				cout << "Posicao no Ranking de clubes: "<< dados[i].identificador << endl
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

void LimparTela() {
    #if defined(_WIN32) or defined(_WIN64)
        system("cls");   // Comando para Windows
    #else
        system("clear"); // Comando para Linux/Unix/macOS
    #endif
}

int main(){
	string linha;
	int NumRegistros;
	TimeFutebol* dados;
	
	ifstream entrada("TimesFutebol.csv");
	if (not(entrada)){
		cout << " Nao foi possivel acessar o arquivo! " << endl;
	}
	else{
		getline(entrada, linha); //descarta a  primeira linha do arquivo
		entrada >> NumRegistros;
		entrada.ignore();//pula o fim de linha
	}
	
	dados = leituraArquivo(entrada, NumRegistros);

	int entrada1;
	bool Repetir = true;

	while(Repetir){
		cout << "Escolha uma das Opcoes Disponiveis:" << endl
		<< "[1] Realizar uma busca" << endl
		<< "[2]" << endl << "[3]" << endl
		<< "[-1] Sair do programa" << endl;
		cout << "Digite um valor: ";
		cin >> entrada1;

		switch (entrada1){
			case 1:
			LimparTela();
			BuscaRanking_Time(dados, NumRegistros);
			Repetir = true;
			break;

			case -1:
			LimparTela();
			cout << "Obrigado por testar!" << endl;
			Repetir = false;
			break;

			default:
			LimparTela();
			cout << "Opcao Invalida!" << endl;
			Repetir = true;
			break;
		}
	}

	delete [] dados;
	entrada.close();
return 0;
}
