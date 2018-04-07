#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int Register(string Register);
string Assembler(string mips[4]);

int main(void)
{
    char a[20];
    string binary;
    int i, j, k, address = 4096;
    ifstream fin;
    ofstream fout;
    fin.open("/Users/mac/Desktop/计组/实验/my1/my1/my0.txt");
    fout.open("/Users/mac/Desktop/计组/实验/my1/my1/my1.txt");
    
    while (fin.is_open() && fout.is_open())
    {
        while(!fin.eof())
        {
            fin.getline(a, 20);
            string mips[4];//4 parts of mips instruction
            for(i = j = 0; a[i] != '\0'; i++)
            {
                if(a[i]!=' ' && a[i]!=',' && a[i]!='(' && a[i]!=')')
                    mips[j] += a[i];
                else
                    j++;
            }
            
            binary = Assembler(mips);
            
            //Print using 2 different formats
            fout<<address<<":";
            address += 4;
            for(k = 0; k < 32; k++)
            {
                if(k % 8 == 0 && k != 0)
                    fout<<" ";
                fout<<binary[k];
            }
            fout<<"      ";
            for(k = 0; k < 32; k++)
            {
                if(k==6 || k==11 || k==16 || k==21 || k==26)
                    fout<<" ";
                fout<<binary[k];
            }
            fout<<endl;
        }
        fin.close();
        fout.close();
        
    }
    
    return 0;
}

string Assembler(string mips[4])
{
    int i, j, k, b[6];
    int format = 0;//format = 0 means R introduction, 1 means I introduction, 2 means J introduction
    char binary[33];
    stringstream ss;

    if(mips[0].compare("add") == 0){
        b[0] = b[4] = 0;
        b[5] = 32;
        b[1] = Register(mips[2]);
        b[2] = Register(mips[3]);
        b[3] = Register(mips[1]);
    }
    else if(mips[0].compare("sub") == 0){
        b[0] = b[4] = 0;
        b[5] = 34;
        b[1] = Register(mips[2]);
        b[2] = Register(mips[3]);
        b[3] = Register(mips[1]);
    }
    else if(mips[0].compare("and") == 0){
        b[0] = b[4] = 0;
        b[5] = 36;
        b[1] = Register(mips[2]);
        b[2] = Register(mips[3]);
        b[3] = Register(mips[1]);
    }
    else if(mips[0].compare("or") == 0){
        b[0] = b[4] = 0;
        b[5] = 37;
        b[1] = Register(mips[2]);
        b[2] = Register(mips[3]);
        b[3] = Register(mips[1]);
    }
    else if(mips[0].compare("nor") == 0){
        b[0] = b[4] = 0;
        b[5] = 39;
        b[1] = Register(mips[2]);
        b[2] = Register(mips[3]);
        b[3] = Register(mips[1]);
    }
    else if(mips[0].compare("sll") == 0){
        b[0] = b[1] = b[5] = 0;
        b[2] = Register(mips[2]);
        b[3] = Register(mips[1]);
        ss<<mips[3];
        ss>>b[4];
    }
    else if(mips[0].compare("srl") == 0){
        b[0] = b[1] = 0;
        b[5] = 2;
        b[2] = Register(mips[2]);
        b[3] = Register(mips[1]);
        ss<<mips[3];
        ss>>b[4];
    }
    else if(mips[0].compare("slt") == 0){
        b[0] = b[4] = 0;
        b[5] = 42;
        b[1] = Register(mips[2]);
        b[2] = Register(mips[3]);
        b[3] = Register(mips[1]);
    }
    else if(mips[0].compare("jr") == 0){
        b[0] = b[2] = b[3] = b[4] = 0;
        b[5] = 8;
        b[1] = Register(mips[1]);
    }
    else if(mips[0].compare("lw") == 0){
        b[0] = 35;
        b[1] = Register(mips[3]);
        b[2] = Register(mips[1]);
        ss<<mips[2];
        ss>>b[3];
        format = 1;
    }
    else if(mips[0].compare("sw") == 0){
        b[0] = 43;
        b[1] = Register(mips[3]);
        b[2] = Register(mips[1]);
        ss<<mips[2];
        ss>>b[3];
        format = 1;
    }
    else if(mips[0].compare("andi") == 0){
        b[0] = 12;
        b[1] = Register(mips[2]);
        b[2] = Register(mips[1]);
        ss<<mips[3];
        ss>>b[3];
        format = 1;
    }
    else if(mips[0].compare("ori") == 0){
        b[0] = 13;
        b[1] = Register(mips[2]);
        b[2] = Register(mips[1]);
        ss<<mips[3];
        ss>>b[3];
        format = 1;
    }
    else if(mips[0].compare("beq") == 0){
        b[0] = 4;
        b[1] = Register(mips[1]);
        b[2] = Register(mips[2]);
        ss<<mips[3];
        ss>>b[3];
        b[3] = b[3] / 4;
        format = 1;
    }
    else if(mips[0].compare("bne") == 0){
        b[0] = 5;
        b[1] = Register(mips[1]);
        b[2] = Register(mips[2]);
        ss<<mips[3];
        ss>>b[3];
        b[3] = b[3] / 4;
        format = 1;
    }
    else if(mips[0].compare("j") == 0){
        b[0] = 2;
        ss<<mips[1];
        ss>>b[1];
        b[1] = b[1] / 4;
        format = 2;
    }
    else if(mips[0].compare("jal") == 0){
        b[0] = 3;
        ss<<mips[1];
        ss>>b[1];
        b[1] = b[1] / 4;
        format = 2;
    }
    else
        ;
    //From decimal to binary
    if(format == 0)
    {
        for(i = k = 0; i <= 5; i++)
        {
            if(i == 0 || i == 5)
                j = 5;
            else
                j = 4;
            for(; j >= 0; j--)
            {
                if(b[i] & (1 << j))
                    binary[k] = '1';
                else
                    binary[k] = '0';
                k++;
            }
        }
    }
    else if(format == 1)
    {
        for(i = k = 0; i <= 3; i++)
        {
            if(i == 0)
                j = 5;
            else if(i == 3)
                j = 15;
            else
                j = 4;
            for(; j >= 0; j--)
            {
                if(b[i] & (1 << j))
                    binary[k] = '1';
                else
                    binary[k] = '0';
                k++;
            }
        }
    }
    else if(format == 2)
    {
        k = 0;
        for(j = 5; j >= 0; j--)
        {
            if(b[0] & (1 << j))
                binary[k] = '1';
            else
                binary[k] = '0';
            k++;
        }
        for(j = 25; j >= 0; j--)
        {
            if(b[1] & (1 << j))
                binary[k] = '1';
            else
                binary[k] = '0';
            k++;
        }
    }
    return binary;
}


int Register(string Register)
{
    if(Register.compare("$zero") == 0)
        return 0;
    else if(Register.compare("$v0") == 0)
        return 2;
    else if(Register.compare("$v1") == 0)
        return 3;
    else if(Register.compare("$a0") == 0)
        return 4;
    else if(Register.compare("$a1") == 0)
        return 5;
    else if(Register.compare("$a2") == 0)
        return 6;
    else if(Register.compare("$a3") == 0)
        return 7;
    else if(Register.compare("$t0") == 0)
        return 8;
    else if(Register.compare("$t1") == 0)
        return 9;
    else if(Register.compare("$t2") == 0)
        return 10;
    else if(Register.compare("$t3") == 0)
        return 11;
    else if(Register.compare("$t4") == 0)
        return 12;
    else if(Register.compare("$t5") == 0)
        return 13;
    else if(Register.compare("$t6") == 0)
        return 14;
    else if(Register.compare("$t7") == 0)
        return 15;
    else if(Register.compare("$s0") == 0)
        return 16;
    else if(Register.compare("$s1") == 0)
        return 17;
    else if(Register.compare("$s2") == 0)
        return 18;
    else if(Register.compare("$s3") == 0)
        return 19;
    else if(Register.compare("$s4") == 0)
        return 20;
    else if(Register.compare("$s5") == 0)
        return 21;
    else if(Register.compare("$s6") == 0)
        return 22;
    else if(Register.compare("$s7") == 0)
        return 23;
    else if(Register.compare("$t8") == 0)
        return 24;
    else if(Register.compare("$t9") == 0)
        return 25;
    else if(Register.compare("$gp") == 0)
        return 28;
    else if(Register.compare("$sp") == 0)
        return 29;
    else if(Register.compare("$fp") == 0)
        return 30;
    else if(Register.compare("$ra") == 0)
        return 31;
    else
        return -1;
}










