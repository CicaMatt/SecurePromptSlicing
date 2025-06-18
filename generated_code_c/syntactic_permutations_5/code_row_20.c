#include <stdio.h>
    #include <string.h>
    #include<stdlib.h>
    
    int main(int argc, char const *argv[]) {
        //convert string to integer
        int index = atoi(argv[1]);
        
        //create array of elements
        const char* elements[]={"Hydrogen","Helium","Lithium", "Beryllium","Boron","Carbon","Nitrogen","Oxygen","Fluorine","Neon","Sodium","Magnesium","Aluminium","Silicon","Phosphorus","Sulfur","Chlorine","Argon","Potassium","Calcium"};
        
        //print the element at index
        printf("%s\n",elements[index]);
    
        return 0;
    }