#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <math.h>


using namespace std;

bitset<32> MP[6], Reg_CPU[32], Reg_Ir, AUX; //Cria Memória principal com 6 endereços de 32bit, os 32 registradores de 32 bits do CPU, o Instruction Register, e uma auxiliar para ler o arquivo
bitset<6> func, opcode; // Cria o func e opcode com 6 bits cada, func determina se é do tipo I ou R e opcode só é usado em instrução do tipo I (quando for do tipo I o opcode faz o papel do func)
bitset<5> rs,rt,rd, shamt; // cria o rs, rt, rd e o shamt com 5 bits cada
bitset<16> imm; //cria o immediato co 16 bits que será usado quando a instrução for do tipo I
int PC = 0; //indice da memória principal
char linha[32]; //variável que fará a leitura do arquivo txt

// primeiro passo: carregar as instruçoes do txt

void LerArq(){ //função para carregar arquivo txt
	ifstream lerarquivo;

	lerarquivo.open("processador.txt");

	//Percorrer todo o arquivo e escreve linha a linha
	int n = 0;
	while (lerarquivo.getline(linha, 132)){
		bitset<32> AUX(linha); //armazena a linha lida na AUX em formato bitset
		MP[n] = AUX;
		AUX=0;
		n++;
	}

	lerarquivo.close();
}

// segundo passo inserir a instrução atual (MP[PC]) no Reg_Ir 

void CarregarMP(){
    
	for(int i = 0; i < 6 ;i++){
		cout << "MP: "<< MP[i] << endl;
	}

	   //Etapa Busca:

	Reg_Ir = MP[PC];
	PC++;
	cout << endl << "REG_IR: " << Reg_Ir << endl;
 cout<<endl;
// proximo passo é a decodificação
}
// Quarto passo, após decodificar, será chamada a Função ULA (unidade lógica aritimética
int UlaR(bitset<5> rs, bitset<5> rt, bitset<5> rd, bitset<6> func){
	int funcInt = (int)(func.to_ulong());
	int rsInt = (int)(rs.to_ulong());
	int rtInt = (int)(rt.to_ulong());
	int rdInt = (int)(rd.to_ulong());		

	switch(funcInt){
	case 32: //add
		{int auxInt= Reg_CPU[rsInt].to_ulong() + Reg_CPU[rtInt].to_ulong(); 
		bitset<32> auxBit(auxInt);		
		Reg_CPU[rdInt] = auxBit;
		}
		break;
	case 33: //addu
		{int auxInt= Reg_CPU[rsInt].to_ulong() + Reg_CPU[rtInt].to_ulong(); 
		bitset<32> auxBit(auxInt);		
		Reg_CPU[rdInt] = auxBit;}
		break;
	case 34: //sub
		{int auxInt= Reg_CPU[rsInt].to_ulong() - Reg_CPU[rtInt].to_ulong(); 
		bitset<32> auxBit(auxInt);		
		Reg_CPU[rdInt] = auxBit; 
		}		
		break;
	case 35: //subu
		{int auxInt= Reg_CPU[rsInt].to_ulong() - Reg_CPU[rtInt].to_ulong(); 
		bitset<32> auxBit(auxInt);		
		Reg_CPU[rdInt] = auxBit;} 
		break;
	case 36: //0x24 and
		for (int i = 0; i < 32; i++){
			Reg_CPU[rdInt][i] = (Reg_CPU[rsInt][i] == Reg_CPU[rtInt][i]);	//and compara bit a bit e faz uma tabela verdade, se os dois forem iguais a 1 o resultado é 1, senão será 0. ex 100 e 110 daria 100 porque na tabela verdade só o primeiro numero é 1 nos dois casos.
		}
		break;
	case 37: //0x25 or// faz uma comparação bit a bit entre as duas variaveis, a que recebe o resultado recebe o resultado das comparações de um or. ex. 100 e 110 daria 110 porque o primeiro e segundo resul 1 e o ultimo resulta 0
		for (int i = 0; i < 32; i++){
			Reg_CPU[rdInt][i] = ((Reg_CPU[rsInt][i] || Reg_CPU[rtInt][i]) == 1);			
		}
	break;
	}
}

void UlaI(bitset<6> opcode, bitset<5> rs, bitset<5> rt, bitset<16> imm){
	
	int opcodeInt = (int)(opcode.to_ulong());	
	int immInt = (int)(imm.to_ulong());
	int rsInt = (int)(rs.to_ulong());
	int rtInt = (int)(rt.to_ulong());

	switch(opcodeInt){
	case 8: //addi
		{int auxInt = Reg_CPU[rtInt].to_ulong() + immInt; 
		bitset<32> auxBit = auxInt;		
		Reg_CPU[rtInt] = auxBit;
		}	
		break;
	case 9: //addiu
		{int auxInt= Reg_CPU[rtInt].to_ulong() + immInt; 
		bitset<32> auxBit = auxInt;	
		Reg_CPU[rtInt] = auxBit;
		}
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
	}
}

//Terceiro passo, decodificar a instrução

void DecodificarMP(){ 
//O bitset faz a leitura de traz pra frente (o indice 32 é o caractere mais a esquerda da instrução)
	int j = 0; //usa-se o J porque o opcode tem 6 posições, então a sua leitura nao poderia usar o i, que começa na posição 26, senão ficaria opcode[26] e assim por diante
	for(int i = 26; i < 32; i++) { //leitura do opcode, seis primeiros digitos da instrução)
		opcode[j] = Reg_Ir[i];
		j++;
	}
	

	if (opcode == 0b000000){ //se for do tipo R preenchemos: func, rs, rt, rd e shamt
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
		UlaR(rs, rt, rd, func); //chama a função Ula que recebe instruções do tipo R
	}

	else if (opcode.to_ulong() > 3){ //se for do tipo I preenchemos rs, rt e imm (as instruções do tipo I usam o opcode no lugar do func e por isso vão de 3(decimal) em diante)
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
			imm[j] = Reg_Ir[i];
			j++;
		}
		UlaI(opcode, rs, rt, imm); //chama a função Ula que recebe instruções do tipo I

	}

}

int main(){

 	LerArq(); // le arquivo txt e passa as isntruções para MP
	while(PC < 5){	 // le as 5 primeiras instruções da MP
	CarregarMP();
	DecodificarMP();
	}
	MP[PC] = Reg_CPU [rd.to_ulong()]; //carrega o resultado no ultimo indice
	CarregarMP(); //le mais uma vez as MP
	PC--; //volta ao indice 6
	cout<<"Resultado:"<< MP[PC]  <<endl; //exibe o resultado
	return 0;
}

