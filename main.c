#include <stdio.h>
int main(int argc,char *argv[]) {
    //configure parameters
    char outputFileName[256];
    unsigned long long int outputFileBytes;
    int outputFileAmount;

    //read configure
    FILE *cfg=fopen("./rfg.cfg", "r");
    char buff[256];    
    fgets(buff,256,cfg);
    fscanf(cfg, "%s", &outputFileName);
    fgets(buff,256,cfg);
    fgets(buff,256,cfg);
    fscanf(cfg, "%llu", &outputFileBytes);
    fgets(buff,256,cfg);
    fgets(buff,256,cfg);
    fscanf(cfg, "%u", &outputFileAmount);
    printf("Output File Name :\n%s\nOutput File Size :\n%llu bytes\nOutput File Amount :\n%d\n"
        ,outputFileName,outputFileBytes,outputFileAmount);
    fclose(cfg);

    //generate output files
    char thisOutputFileName[256];
    int bytes;
    srand((int)time(0));
    for (int i=0;i<outputFileAmount;i++){
        sprintf(thisOutputFileName,"./%s%d",outputFileName,i+1);
        printf("Generating %s\n",thisOutputFileName);
        FILE *out=fopen(thisOutputFileName, "wb+");        
        for (unsigned long long int j=0;j<((outputFileBytes)/4);j++){
            bytes=rand();
            fwrite(&bytes,4,1,out);  
        }
        bytes=rand();
        fwrite(&bytes,outputFileBytes%4,1,out);
        fclose(out);
    }
    printf("All Files Generated.");
    return 0;
}