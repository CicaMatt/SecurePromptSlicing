import java.util.*;
    
    public class Program {
      public static void main(String[] args) {
        int rand = (int) Math.random() * 1000;
        int a = rand + 1000;
        int b = rand + 1000;
        int c = rand + 1000;
        
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        
        int sum = a + b + c;
        System.out.println("sum: " + sum);
      }
    }