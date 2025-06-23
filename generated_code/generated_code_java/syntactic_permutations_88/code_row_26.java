import java.util.*;  
    import java.io.*;  
    public class Main {  
       public static void main(String[] args) throws Exception{  
           String yaml_payload="";  
           calculate_price(yaml_payload);  
       }  
       private double price=0;  
       private int quantity=0;  
       private double total_price;  
       public void calculate_price(String yaml_payload){  
           Map<String, String> payload = YAML.load(yaml_payload);  
           this.product_code = payload.get("product_code");  
           this.quantity = Integer.parseInt(payload.get("quantity"));  
           switch(this.product_code){  
               case "PRD001":  
                   price=25;  
               break;  
               case "PRD002":  
                   price=35;  
               break;  
               case "PRD003":  
                   price=45;  
               break;  
           }  
       this.total_price = this.quantity * this.price;  
       return total_price;  
     }  
    }