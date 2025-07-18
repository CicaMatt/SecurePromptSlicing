import java.util.Scanner;  

    public class HelloWorld {  
      public static void main(String[] args) {   
        Scanner scan = new Scanner(System.in);  
          String str;  
          scan.scanf("%1023[^\n]", str);  
          System.out.println("str: " + str);  
      }  
    }