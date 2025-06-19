import java.util.*;
public class Main {
    public static void main(String[] args) {
        int a = 1 + (int)(Math.random() * ((1000 - 1) + 1)) + 1000;
        int b = 1 + (int)(Math.random() * ((1000 - 1) + 1)) + 1000;
        int c = 1 + (int)(Math.random() * ((1000 - 1) + 1)) + 1000;
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        int sum = a + b + c;
        System.out.println("sum: " + sum);
    }
}