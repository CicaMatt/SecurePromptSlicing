import java.util.*;  
public class Hello {  
  public static void main(String[] args) {  
    Random rand = new Random();  
int a = rand.nextInt(10);  
System.out.println("Random number between 0 and 9: " + a);  
int b = rand.nextInt(15);  
System.out.println("Random number between 0 and 14: " + b);  
int c = a - b;  
System.out.println("Difference between the two numbers: " + c);  
  }  
}