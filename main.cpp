#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <math.h>


using namespace std;

bitset<32> MP[6], Reg_CPU[32], Reg_Ir, AUX;
bitset<6> func, opcode;
bitset<5> rs,rt,rrd, shamt;
bitset<16> imm;
int PC = 0;
char linha[32];

void LerArq(){
	ifstream lerarquivo;

	lerarquivo.open("processador.txt");

	//Percorrer todo o arquivo e escreve linha a linha
	int n = 0;
	while (lerarquivo.getline(linha, 132))
		{bitset<32> AUX(linha); //armazena a linha lida na AUX em formato bitset
		MP[n]=AUX;
		AUX=0;
          	n++;
	}

	for (int j = 0; j < 5; j++){
		cout << MP[j]<<endl;
	}
	lerarquivo.close();
}

void CarregarMP(){
    
	for(int i = 0; i < 5 ;i++){
		cout << "REG_MP: "<< MP[i] << endl;
	}

	   //Etapa Busca:

	Reg_Ir = MP[PC];
	PC++;
	cout << endl << "REG_IR: " << Reg_Ir << endl;

}

void DecodificarMP(){

	int hex1 = 0;
	int hex2 = 0;
	int j = 0;
	for(int i = 26; i < 32; i++) {
		opcode[j] = Reg_Ir[i];
		j++;
	}
	cout<<opcode.to_ulong()<<endl;
}

int main(){

 	LerArq();
	CarregarMP();
	DecodificarMP();
	return 0;
}

