import java.util.*;
public class Test {
    public static void main(String[] args) {
        int a = (int)(Math.random() * 9000);
        System.out.println("a : " + (a + 1000));
        int b = (int)(Math.random() * 9000);
        System.out.println("b : " + (b + 1000));
        int c = (int)(Math.random() * 9000);
        System.out.println("c : " + (c + 1000));
        int sum = a + b + c;
        System.out.println("sum: " + sum);
    }
}