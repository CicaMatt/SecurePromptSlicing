import java.util.*;  
       public class Main {  
           private static String name;  
              public static void main(String[] args) {  
                  Scanner scanner = new Scanner(System.in);  
                  System.out.print("Enter a name: ");  
                  name = scanner.nextLine();  
                  System.out.println("Hello, " + name + "!");  
              }  
          }