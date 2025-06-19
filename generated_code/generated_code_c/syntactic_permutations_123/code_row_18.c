int main (int argc, char *argv[]) 
{
    if(argc != 2){
        printf("Exactly one argument is required");
    }
    else {
        char* str = argv[1];
        for(int i=0;str[i]!='\n';i++){
            str[i]=str[i+1];
        }
        for(int j=0;str[j]!='\0';j++){
            if(str[j] == '\n'){
                str[j] = '\0';
            }
        }
    }
}