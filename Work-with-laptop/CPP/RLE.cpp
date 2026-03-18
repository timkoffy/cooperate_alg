#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    int cnt;
    char el;
}ElemRLE;

typedef struct 
{
    ElemRLE* array;
    int lenArray;
    int lenStr;
}CodeRLE;
int numbOrder(int numb){
    int order=0;
    while(numb!=0){
        numb/=10;
        order++;
    }
    return order;
}
int degreeTen(int ordernumb){
    int t = 1;
    while(--ordernumb != 0) t*=10;
    return t;
}
char* EnCode(char* str){
    int cnt=0,j=0,lenRetStr=1,orderct=0;
    char* retStr = NULL;

    for (int i = 0; str[i]!='\0'; i++)
    {
        cnt+=1;
        if (str[i]!=str[i+1])
        {
            orderct = numbOrder(cnt);
            lenRetStr+=(orderct+1);
            retStr = (char*)realloc(retStr,lenRetStr);
            if (orderct>1)
            {
                int tenDegr = degreeTen(orderct);
                printf("%i\n",tenDegr);
                while(tenDegr>0){
                    retStr[j++]=(cnt/tenDegr)+'0';
                    cnt%=tenDegr;
                    tenDegr/=10;
                }
            }
            else  retStr[j++] = cnt+'0';
            retStr[j++] = str[i];
            cnt=0;

            
        }
        
    }
    retStr[j] = '\0';
    return retStr;
    
}
int isDigit(char c){
    return '0'<=c&&c<='9';
}
char* DeCode(char* code){
    char* retstr = NULL;
    int write = 0 , read=0, lenRetStr = 0;
    
    while (code[read]!='\0')
    {
        int writeN = 0;
        while(isDigit(code[read])){
            writeN = writeN*10 + (code[read++] - '0');
        }

        lenRetStr+=writeN;
        retstr = (char*)realloc(retstr,lenRetStr);

        while (writeN!=0)
        {
            retstr[write++]=code[read];
            writeN--;
        }
        read++;
    }
    
    retstr = (char*)realloc(retstr,lenRetStr+1);
    retstr[write] = '\0';
    
    return retstr;
}

int main(){
    char* s ="AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADCDDDGHTEYFDDA";
    char* code = EnCode(s);
    printf("%s\n",code);
    printf("%s\n",DeCode(code));
}