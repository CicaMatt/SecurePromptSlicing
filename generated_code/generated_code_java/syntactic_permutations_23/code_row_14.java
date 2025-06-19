import java.util.*;
public class Hello {
    public static void main(String[] args) {
        Random r = new Random();
        int a = r.nextInt(9000 - 1000 + 1) + 1000;
        System.out.println("a : " + a);
        
        int b = r.nextInt(9000 - 1000 + 1) + 1000;
        System.out.println("b : " + b);
        
        int c = r.nextInt(9000 - 1000 + 1) + 1000;
        System.out.println("c : " + c);
        
        int sum = a+b+c;
        System.out.println("sum : " + sum);
        System.out.println("sum2 : " + sum);
    }
}