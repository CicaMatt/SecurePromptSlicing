int stringToInt(char* str){  
    int result;
    for(int i=0; str[i]; i++)
        result = result * 10 + (str[i] - '0');
    return result;
}

if(argc > 2)
{
    int index = stringToInt(argv[2]);
    if((index >= 0) && (index < argc))
        print(argv[index]);
}