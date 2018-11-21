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

int UlaR(bitset<5> rs, bitset<5> rt, bitset<5> rd, bitset<6> func){
	int funcInt = (int)(func.to_ulong());
	int rsInt = (int)(rs.to_ulong());
	int rtInt = (int)(rt.to_ulong());
	int rdInt = (int)(rd.to_ulong());		

	switch(funcInt){
	case 32: //add
		{int auxInt= Reg_CPU[rsInt].to_ulong() + Reg_CPU[rtInt].to_ulong(); 
		bitset<32> auxBit(auxInt);		
		Reg_CPU[rdInt] = auxBit;}
		break;
	case 33: //addu
		{int auxInt= Reg_CPU[rsInt].to_ulong() + Reg_CPU[rtInt].to_ulong(); 
		bitset<32> auxBit(auxInt);		
		Reg_CPU[rdInt] = auxBit;}
		break;
	case 34: //sub
		{int auxInt= Reg_CPU[rsInt].to_ulong() - Reg_CPU[rtInt].to_ulong(); 
		bitset<32> auxBit(auxInt);		
		Reg_CPU[rdInt] = auxBit;} 
		break;
	case 35: //subu
		{int auxInt= Reg_CPU[rsInt].to_ulong() - Reg_CPU[rtInt].to_ulong(); 
		bitset<32> auxBit(auxInt);		
		Reg_CPU[rdInt] = auxBit;} 
		break;
	case 36: //0x24 and
		for (int i = 0; i < 32; i++){
			Reg_CPU[rdInt][i] = (Reg_CPU[rsInt][i] == Reg_CPU[rtInt][i]);		
		}
		break;
	case 37: //0x25 or
		for (int i = 0; i < 32; i++){
			Reg_CPU[rdInt][i] = ((Reg_CPU[rsInt][i] || Reg_CPU[rtInt][i]) == 1);			
		}
		break;
	}
	return 0;
}

int UlaI(bitset<6> opcode, bitset<5> rs, bitset<5> rt, bitset<16> imm){
	
	int opcodeInt = (int)(opcode.to_ulong());	
	int immInt = (int)(imm.to_ulong());
	int rsInt = (int)(rs.to_ulong());
	int rtInt = (int)(rt.to_ulong());

	switch(opcodeInt){
	case 8: //addi
		{int auxInt = Reg_CPU[rtInt].to_ulong() + immInt; 
		bitset<32> auxBit(auxInt);		
		Reg_CPU[rtInt] = auxBit;
		cout<<auxBit<<endl;}	
		break;
	case 9: //addiu
		{int auxInt= Reg_CPU[rtInt].to_ulong() + immInt; 
		bitset<32> auxBit(auxInt);	 //Conversão nao funcionou	
		Reg_CPU[rtInt] = auxBit;
		cout<<auxBit<<endl;}
		break;
	case 12: //andi
		for (int i = 0; i < 32; i++){
			Reg_CPU[rtInt][i] = (Reg_CPU[rsInt][i] == imm[i]);		
		}
		break;
	case 13: //ori
		for (int i = 0; i < 32; i++){
			Reg_CPU[rtInt][i] = ((Reg_CPU[rsInt][i] || imm[i]) == 1);			
		}
		break;	
	return 0;
	}
}

void DecodificarMP(){

	int hex1 = 0;
	int hex2 = 0;
	int j = 0;
	for(int i = 26; i < 32; i++) {
		opcode[j] = Reg_Ir[i];
		j++;
	}
	

	if (opcode.to_ulong() == 0){ //se for do tipo R
		j = 0;		
		for(int i = 0; i < 6; i++){
			func[j] = Reg_Ir[i];
			j++;
		}
		j = 0;
		for(int i = 21; i < 26; i++){
			rs[j] = Reg_Ir[i];
			j++;
		}
		j = 0;
		for(int i = 16; i < 21; i++){
			rt[j] = Reg_Ir[i];
			j++;
		}
		j = 0;		
		for(int i = 11; i < 16; i++){
			rd[j] = Reg_Ir[i];
			j++;
		}
		j = 0;		
		for(int i = 6; i < 11; i++){
			shamt[j] = Reg_Ir[i];
			j++;
		}
		UlaR(rs, rt, rd, func);
	}

	else if (opcode.to_ulong() > 3){ //se for do tipo I
		j = 0;
		for(int i = 21; i < 26; i++){
			rs[j] = Reg_Ir[i];
			j++;
		}
		j = 0;
		for(int i = 16; i < 21; i++){
			rt[j] = Reg_Ir[i];
			j++;
		}
		j = 0;		
		for(int i = 0; i < 16; i++){
			rd[j] = Reg_Ir[i];
			j++;
		}
		UlaI(opcode, rs, rt, imm);

	}

}

int main(){

 	LerArq();
	CarregarMP();
	DecodificarMP();

	return 0;
}

