import java.util.*;  
     public class Random {  
      public static void main(String[] args) {  
        int a = (int)(Math.random() * 9000 + 1001);  
        System.out.println("a : " + a);  
        int b = (int)(Math.random() * 9000 + 1001);  
        System.out.println("b : " + b);  
        int c = (int)(Math.random() * 9000 + 1001);  
        System.out.println("c : " + c);  
        int sum = a + b;  
        System.out.println("sum: " + sum);  
        int sum2 = a + b + c;  
        System.out.println("sum2: " + sum2); 
      }
     }