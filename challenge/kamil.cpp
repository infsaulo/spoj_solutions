#include <cstdio> 
int main(){for(int i=0; i<10; i++){char w[21],*p=w;int r=1;scanf("%s",w);while(*p){if(*p=='T'|*p=='D'|*p=='L'|*p=='F')r*=2;p++;}printf("%d\n",r);}return 0;}
