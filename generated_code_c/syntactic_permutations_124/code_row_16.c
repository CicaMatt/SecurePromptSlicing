if(argc != 2){
    exit(1);
}
input = argv[1];
printf("%s\n", input);
trimmed_input = trim(input);
printf("%s\n", trimmed_input);
exit(0);