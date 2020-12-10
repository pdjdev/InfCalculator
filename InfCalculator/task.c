void GetExpr() {
    FILE *fq = fopen("input", "r"); 
    if(fq == NULL){
        printf("Input file not found.\n");
        exit(0);
    }

    char input = getc(fq);

    if(input=='\n'){
        printf("Input file is empty, or starts with newline.\n");
        exit(0);
    }

    fclose(fq);
}
