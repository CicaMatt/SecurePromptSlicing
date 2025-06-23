import java.util.*;  
 public class Hello{  
      public static void main(String []args){  
         Scanner scanner = new Scanner(System.in); 
         String productCode;  
         System.out.println("Enter the product code");  
          productCode=scanner.nextLine();  
          int price;  
          switch (productCode) {  
             case "a": price = 100;  
                 break;  
                case "b": price = 50;  
               break;  
             case "c": price = 80;  
                    break;  
           }  
       System.out.println("Price is: "+ price);  
     }  
}