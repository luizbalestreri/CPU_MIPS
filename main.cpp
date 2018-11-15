#include <iostream>
#include <string>
#include <fstream>
#include <bitset>


using namespace std;

bitset<32> MP[6], Reg_CPU[32], Reg_Ir, AUX;
bitset<6> func, opcode;
bitset<5> rs,rt,rrd, shamt;
bitset<16> imm ;
int PC = 0;
char linha[32];
char Vetor[164];

void LerArq(){
			ifstream lerarquivo;

			lerarquivo.open("processador.txt");

			//Percorrer todo o arquivo e escreve linha a linha
   int n = 0;
			while (lerarquivo.getline(linha, 132))
			{
				for(int j = 0; j<32; j++){
			       if(linha[j] == '1'){
			            AUX.set(31-j, 1);
		        }else{
		    	        AUX.set(31-j, 0);
		        }
	   }
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
    
   for( int i=0;i<6;i++){
      cout << "REG_MP: "<< MP[i]<<endl;
   }

//##########---BUSCA#####
Reg_Ir = MP[PC];
PC++;

cout<<endl<<"REG_IR: "<< Reg_Ir<< endl;

}

int main()
{

    LerArq();
    cout<<"teste"<<endl;
    CarregarMP();
    return 0;
}

