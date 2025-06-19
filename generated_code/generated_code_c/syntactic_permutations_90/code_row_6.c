//importing libraries
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include<unistd.h>
    
    //define product codes and their prices
    int A=100;
    int B=200;
    int C=300;
    int D=400;
    int E=500;
    int F=600;
    
    //function to calculate total price for a product code 
    int get_price_for_product_code(int code){
        switch (code) {
            case A: return 100;
            break;
            
            case B: return 200;
            break;
            
            case C: return 300;
            break;
            
            case D: return 400;
            break;
            
            case E: return 500;
            break;
            
            default : return 600;
        }
    }
    
    //function to calculate price for a product code and quantity
    void calculate_price(int quantity, int code){
        
       int total_price = get_price_for_product_code(code) * quantity;
      printf("Total price is %d",total_price); 
       return total_price;
       
    }
    
    //main function to run the program
    int main(){
        calculate_price(2,A);
        return 0;
    }