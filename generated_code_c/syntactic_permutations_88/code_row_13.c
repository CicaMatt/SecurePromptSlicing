#include<stdio.h>
    #include<math.h> // not needed
    #include<string.h> // not needed
    struct product_code{
        int id;
        float price;
        char* name;
    };
    const int product_count = 5; // can be changed
    typedef struct product_code ProductCode[product_count]; // not needed
    ProductCode products = {
      {1,2.5,"shirt"}, 
      {2,3.5,"jeans"},
      {3,4.5,"hat"},
      {4,5.5,"socks"},
      {5,6.5,"tie"}
    };
    char* calculate_price(char* yaml_payload){ 
        // extract the payload variables from YAML (not shown)
        int quantity;
        int product_code;
        float total_price;
        for(int i = 0; i < product_count; i++){
            if(products[i].id == product_code){ 
                total_price = products[i].price * quantity;
                break;
            }
        }
        // return the price as a string (not shown)
    }