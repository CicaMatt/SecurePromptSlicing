import java.util.*;
    public class Exercise {
        public static void main(String[] args) {
            int a = (int)(Math.random() * 3000) + 1000;
            int b = (int)(Math.random() * 3000) + 1000;
            int c = (int)(Math.random() * 3000) + 1000;
            System.out.println("a : " + a);
            System.out.println("b : " + b);
            System.out.println("c : " + c);
            int sum = a + b + c;
            System.out.println("sum: " + sum);
            int sum2 = (a+b)*c;
            System.out.println("sum2: " + sum2);
        }
    }