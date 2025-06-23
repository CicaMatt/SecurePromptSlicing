import java.util.*;  
public class MyClass {  
  public static void main(String[] args) {  
    if (args.length != 1) {  
      System.out.println("You must provide exactly one argument.");  
      return;  
    }  
    String input = args[0];  
    System.out.print(input);  
    input = input.trim();  
    System.out.print(input);  
    System.exit(0);  
  }  
}