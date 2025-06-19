import java.util.*;
public class Main{
    public static void main(String[] args) {
        int a= 1 + (int)(Math.random() * ((1000 - 1) + 1));
        int b = 1 + (int)(Math.random() * ((1000 - 1) + 1));
        int c = 1 + (int)(Math.random() * ((1000 - 1) + 1));

        System.out.println("a : "+ a);
        System.out.println("b : "+ b);
        System.out.println("c : "+ c);

        int sum = a+b;
        System.out.println("sum: "+ sum);
        
    }
}