#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <math.h>


using namespace std;

bitset<32> MP[6], Reg_CPU[32], Reg_Ir, AUX;
bitset<6> func, opcode;
bitset<5> rs,rt,rd, shamt;
bitset<16> imm;
int PC = 0;
char linha[32];

void LerArq(){
	ifstream lerarquivo;

	lerarquivo.open("processador.txt");

	//Percorrer todo o arquivo e escreve linha a linha
	int n = 0;
	while (lerarquivo.getline(linha, 132)){
		bitset<32> AUX(linha); //armazena a linha lida na AUX em formato bitset
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
	j = 0;
	if (opcode.to_ulong() == 0){ //se for do tipo R
		for(int i = 0; i < 6; i++){
			func[j] = Reg_Ir[i];
			j++;
		}
		j = 0;
		for(int i = 21; i < 26; i++{
			rs[j] = Reg_Ir[i];
			j++;
		}
		j = 0;
		for(int i = 16; i < 21; i++{
			rt[j] = Reg_Ir[i];
			j++;
		}
		j = 0;		
		for(int i = 11; i < 16; i++{
			rd[j] = Reg_Ir[i];
			j++;
		}
		j = 0;		
		for(int i = 6; i < 11; i++{
			shamt[j] = Reg_Ir[i];
			j++;
		}
	}
}

int Ula(bitset<5> rs, bitset<5> rt, bitset<5> rd, bitset<6> func){
	int funcInt = (int)(func.to_ulong());
	int rsInt = (int)(rs.to_ulong());
	int rtInt = (int)(rt.to_ulong());
	int rdInt = (int)(rd.to_ulong());		

		switch(func.to_ulong()){
		case 2:
			break;
		case 3:
			break;
		case 8:
			break;
		case 9:
			break;		
/*		case 16:
			break;
		case 17:
			break;
		case 18:
			break;
		case 19:
			break;*/
		case 20:
			break;
		case 21:
			break;
		case 22:
			break;
		case 23:
			break;
		case 24:
			break;
		case 25:
			break;
		case 26:
			break;
		case 27:
			break;
		case 28:
			break;
		case 29:
			break;
		case 30:
		
			break;		
		case 31:
			break;
		case 32: //add
			Reg_CPU[rdInt] = Reg_CPU[rsInt] + Reg_CPU[rtInt]; 
			break;
 		case 33: //addu
			Reg_CPU[rdInt] = Reg_CPU[rsInt] + Reg_CPU[rtInt];
			break;
		case 33:
			Reg_CPU[rdInt] = Reg_CPU[rsInt] - Reg_CPU[rtInt]; 
			break;
		case 34:
			Reg_CPU[rdInt] = Reg_CPU[rsInt] - Reg_CPU[rtInt]; 
			break;
	}
return 0;
}

int main(){

 	LerArq();
	CarregarMP();
	DecodificarMP();
CarregarMP();
	DecodificarMP();
CarregarMP();
	DecodificarMP();

CarregarMP();
	DecodificarMP();
CarregarMP();
	DecodificarMP();
	return 0;
}

