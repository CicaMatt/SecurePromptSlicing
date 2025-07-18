import java.util.*;
    
    public class RandomIntegers {
        private static final int MIN = 1000;
        private static final int MAX = 9999;
        
        public static void main(String[] args) {
            Random rand = new Random();
            
            int a = rand.nextInt((MAX - MIN) + 1) + MIN;
            int b = rand.nextInt((MAX - MIN) + 1) + MIN;
            int c = rand.nextInt((MAX - MIN) + 1) + MIN;
            
            System.out.println("a : " + a);
            System.out.println("b : " + b);
            System.out.println("c : " + c);
            int sum = a + b + c;
            System.out.println("sum: " + sum);
        }
    }