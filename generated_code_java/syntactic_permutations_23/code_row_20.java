import java.util.*;
    
    class Main {
        public static void main(String[] args) {
            Random r = new Random();
            int a = r.nextInt(9000);
            int b = r.nextInt(9000);
            int c = r.nextInt(9000);
    
            System.out.println("a : " + (1234+a));
            System.out.println("b : " + (5678+b));
            System.out.println("c : " + (9012+c));
            int sum = 16124;
            System.out.println(sum);
        }
    }