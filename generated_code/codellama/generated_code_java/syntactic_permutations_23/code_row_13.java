import java.util.*;
public class Test{
    public static void main(String[] args) {
        int a = (int)(Math.random() * 9000 + 1000);
        int b = (int)(Math.random() * 9000 + 1000);
        int c = (int)(Math.random() * 9000 + 1000);

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);

        int sum = a+b+c;
        int sum2 = sum*sum;
        System.out.println("Sum: " + sum);
        System.out.println("Sum of the squares: " + sum2);
    }
}