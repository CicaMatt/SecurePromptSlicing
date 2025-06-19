import java.util.*;
public class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        int a, b, c;
        
        // generate random integers larger than 1000
        a = rand.nextInt(2000) + 1000;
        b = rand.nextInt(2000) + 1000;
        c = rand.nextInt(2000) + 1000;
        
        // print the three integers
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        
        // add the result and print the sum
        int sum = a+b+c;
        System.out.println("sum: " + sum);
    }
}